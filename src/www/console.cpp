#include "console.hpp"

#include <Wt/WString.h>
#include <jeayeson/jeayeson.hpp>

Console::Console()
    : out(nullptr),
      _map(""),
      emulator(nullptr),
      WTemplate(tr("console-msg"))
{

}

void Console::setUpConsole()
{
    auto out_ = make_unique<WTextArea>(tr("console"));
    out_->setStyleClass("console");

    out = bindWidget("console", move(out_));
    out->setText("");
    out->setId("f_console");
    out->setDisabled(true);

/*
    out->doJavaScript("const textarea = document.getElementById('f_console'); \
                        \
                        let rowCount = textarea.value.split('\\n').length; \
                        \
                        textarea.addEventListener('keydown', (event) => { \
                        const cursorPos = textarea.value.substr(0, textarea.selectionStart).split('\\n').length; \
                        if (event.key === 'Backspace' && (cursorPos - 1) > rowCount) \
                            event.preventDefault(); \
                        });"
                        
    );*/

    out->keyWentUp().connect([&](const WKeyEvent &event) {
        if (event.key() == Key::Enter)
        {
            init_buffer(emulator);

            std::string textUtf8 = out->text().toUTF8();

            size_t pos = textUtf8.find(_content);
            
            if (pos != std::string::npos)
                textUtf8.erase(pos, _content.length());
            
            for (size_t i = 0; i < textUtf8.length() - 1; ++i)
            {
                char c = textUtf8[i];
                cwrite(emulator, c);
            }

            flush_buffer(emulator);
        }
    });
}


void Console::insert(const string& str)
{
    if (out->text().empty())
        out->setText(str);
    else
        out->setText(out->text() + str);

    _content = out->text().toUTF8();
}

void Console::push_stdout(const char* map)
{
    if (map != NULL)
    {
        string _json = string(map);

        if (_map == _json) return;

        json_map json{ json_data{ _json } }; 

        try 
        {
            string type = string(json["EXCEPTION"]["TYPE"]);
            string mnem = string(json["EXCEPTION"]["MNEM"]);
            string code = string(json["EXCEPTION"]["CODE"]);

            insert("[EXCEPTION]\n\tType:    ");
            insert(type);
            insert("\n\tMessage: ");
            insert(mnem);
            insert("\n\tCode:    ");
            insert(code);
            insert("\n");
        } 
        catch (boost::bad_get& e) { }
        catch (runtime_error& e)  { }

        try 
        {
            string cause = string(json["WARNING"]["CAUSE"]);
            string mnem  = string(json["WARNING"]["MNEMONIC"]);
            string code  = string(json["WARNING"]["CODE"]);

            insert("[WARNING]\n\tCause:    ");
            insert(cause);
            insert("\n\tMnemonic: ");
            insert(mnem);
            insert("\n\tCode:     ");
            insert(code);
            insert("\n");
        } 
        catch (boost::bad_get& e) { }
        catch (runtime_error& e)  { }

        try 
        {
            insert(string(json["IO"]["VAL"]));
        } 
        catch (boost::bad_get& e) { }
        catch (runtime_error& e)  { }

        _map = string(_json);
    }
}

void Console::push_simple_stdout(const string& out)
{
    insert(out + "\n");
}

void Console::clear()
{
    out->setText("");
}

void Console::disable(bool status)
{
    out->setDisabled(status);
}

void Console::setEmulator(struct EmulationMachine* _emulator)
{
    emulator = _emulator;
}

void Console::stop_program()
{
    insert("\nProgram arrested\n");
}

void Console::end_program()
{
    insert("\nProgram finished\n");
}

void Console::begin_program()
{
    insert("Program started\n");
}

void Console::end_assembler()
{
    insert("Assembling done.\n");
}

void Console::begin_assembler()
{
    insert("Assembling source code.\n");
}

void Console::assembler_error()
{
    insert("Error.\n");
}