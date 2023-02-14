#ifndef __console__68000__
#define __console__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTextArea.h>


using namespace Wt;
using namespace std;

extern "C" {
    void cwrite(char _c);

    void flush_buffer();

    void init_buffer();
}


class Console : public WTemplate
{
    public: 
        Console();

        void setUpConsole();

        void insert(const WString& str);

        void push_stdout(const char* map);

        void clear();

        void disable(bool status);

    private:
        WTextArea* out;

        string _map;
        string _content;

};



#endif // __console__68000__