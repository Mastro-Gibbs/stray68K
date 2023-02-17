#ifndef __console__68000__
#define __console__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTextArea.h>

#include "../emulator/motorolatypes.h"

using namespace Wt;
using namespace std;

extern "C" {
    void flush_buffer(struct EmulationMachine* emulator);

    void init_buffer(struct EmulationMachine* emulator);

    void cwrite(struct EmulationMachine* emulator, char _c);
}


class Console : public WTemplate
{
    public: 
        Console();

        void setUpConsole();

        void setEmulator(struct EmulationMachine* _emulator);

        void disable(bool status);

        void push_stdout(const char* map);
        void push_simple_stdout(const string& out);

        void begin_program();
        void end_program();
        void stop_program();

        void begin_assembler();
        void end_assembler();
        void assembler_error();

        void clear();

    private:
        WTextArea* out;

        string _map;
        string _content;

        struct EmulationMachine* emulator;

        void insert(const string& str);

};



#endif // __console__68000__