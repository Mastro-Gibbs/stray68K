#include "console.hpp"

#include <Wt/WString.h>
#include <jeayeson/jeayeson.hpp>

Console::Console()
    : self(nullptr),
      _map(""),
      emulatorInstance(nullptr),
      WTemplate(tr("console-msg"))
{

}

void Console::setUpConsole()
{
    auto out_ = make_unique<WTextArea>(tr("console"));
    out_->setStyleClass("console");

    self = bindWidget("console", move(out_));
    self->setText("");
    self->setId("f_console");
    self->setDisabled(true);

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

    self->keyWentUp().connect([&](const WKeyEvent &event) {
        if (event.key() == Key::Enter)
        {
            init_buffer(emulatorInstance);

            std::string textUtf8 = self->text().toUTF8();

            size_t pos = textUtf8.find(_content);
            
            if (pos != std::string::npos)
                textUtf8.erase(pos, _content.length());
            
            for (size_t i = 0; i < textUtf8.length() - 1; ++i)
            {
                char c = textUtf8[i];
                cwrite(emulatorInstance, c);
            }

            flush_buffer(emulatorInstance);
        }
    });
}


void Console::insert(const string& str)
{
    if (self->text().empty())
        self->setText(str);
    else
        self->setText(self->text() + str);

    _content = self->text().toUTF8();
}

void Console::pushStdout(const char* map)
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

void Console::pushText(const string& out)
{
    insert(out + "\n");
}

void Console::clear()
{
    self->setText("");
}

void Console::disable(bool status)
{
    self->setDisabled(status);
}

void Console::setEmulator(struct EmulationMachine* _emulator)
{
    emulatorInstance = _emulator;
}

void Console::writeProgramStopped()
{
    insert("\nProgram arrested\n");
}

void Console::writeProgramFinished()
{
    insert("\nProgram finished\n");
}

void Console::writeProgramStarted()
{
    insert("Program started\n");
}

void Console::writeAssemblingDone()
{
    insert("Assembling done.\n");
}

void Console::writeAssemblingStarted()
{
    insert("Assembling source code.\n");
}

void Console::writeAssemblingFail()
{
    insert("Error.\n");
}