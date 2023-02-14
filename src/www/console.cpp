#include "console.hpp"

#include <Wt/WString.h>
#include <jeayeson/jeayeson.hpp>

Console::Console()
    : out(nullptr),
      _map(""),
      WTemplate(tr("console-msg"))
{

}

void Console::setUpConsole()
{
    auto out_ = make_unique<WTextArea>(tr("console"));
    out_->setStyleClass("console");

    out = bindWidget("console", move(out_));
    out->setText("");
    // out->setDisabled(true);

    out->keyWentUp().connect([&](const WKeyEvent &event) {
        if (event.key() == Key::Enter)
        {
            init_buffer();

            std::string textUtf8 = out->text().toUTF8();

            size_t pos = textUtf8.find(_content);
            
            if (pos != std::string::npos)
                textUtf8.erase(pos, _content.length());
            
            for (size_t i = 0; i < textUtf8.length() - 1; ++i)
            {
                char c = textUtf8[i];
                cwrite(c);
            }

            flush_buffer();
        }
    });
}

void Console::insert(const WString& str)
{
    if (out->text().empty())
        out->setText(str);
    else
        out->setText(out->text() + str);

    _content = out->text().toUTF8();
}

void Console::push_stdout(const char* map)
{
    string _json = string(map);

    if (_map == _json) return;

    json_map json{ json_data{ _json } }; 

    try 
    {
        insert(string(json["IO"]["VAL"]));
    } 
    catch (boost::bad_get& e) { }
    catch (runtime_error& e)  { }

    _map = string(_json);
}

void Console::clear()
{
    out->setText("");
}

void Console::disable(bool status)
{
    out->setDisabled(status);
}