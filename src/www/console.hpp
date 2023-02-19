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

        void pushStdout(const char* map);
        void pushText(const string& out, bool nl = true);

        void writeProgramStarted();
        void writeProgramFinished();
        void writeProgramStopped();

        void writeAssemblingStarted();
        void writeAssemblingDone();
        void writeAssemblingFail();

        void clear();

    private:
        WTextArea* self;

        string _map;
        string _content;

        struct EmulationMachine* emulatorInstance;

        void insert(const string& str);

};



#endif // __console__68000__