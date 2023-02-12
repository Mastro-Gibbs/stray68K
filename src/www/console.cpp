#include "console.hpp"

#include <jeayeson/jeayeson.hpp>

Console::Console()
    : out(nullptr),
      WTemplate(tr("console-msg"))
{

}

void Console::setUpConsole()
{
    auto out_ = make_unique<WTextArea>(tr("console"));
    out_->setStyleClass("console");

    out = bindWidget("console", move(out_));
    out->setText("");
    out->setReadOnly(true);
}

void Console::insert(const WString& str)
{
    if (out->text().empty())
        out->setText(str);
    else
        out->setText(out->text() + str);
}

void Console::push_stdout(const char* map)
{
    string _json = string(map);

    json_map json{ json_data{ _json } }; 

    try 
    {
        insert(string(json["IO"]["VAL"]));
    } 
    catch (boost::bad_get& e) { }
    catch (runtime_error& e)  { }
}

void Console::clear()
{
    out->setText("");
}