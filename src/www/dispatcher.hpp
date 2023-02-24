#ifndef __dispatcher__68000__
#define __dispatcher__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WAnchor.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WSignal.h>

#include <thread>

#include "editor.hpp"
#include "memory.hpp"
#include "console.hpp"
#include "register.hpp"

#include "../emulator/motorolatypes.h"
#include "../assembler/assemblertypes.h"

using namespace Wt;
using namespace std;

extern "C" {

    SemanticState* obtain_semantic_state();

    void free_SemanticState(SemanticState* state);

    int assemble(SemanticState* astatus, const char* filepath);

    struct EmulationMachine* obtain_emulation_machine(const char *path);

    int is_last_istr(struct EmulationMachine* emulatorInstance);

    void begin_emulator(struct EmulationMachine* emulatorInstance);

    void end_emulator(struct EmulationMachine* emulatorInstance);

    int emulate (struct EmulationMachine* emulatorInstance);

    void flush_buffer(struct EmulationMachine* emulatorInstance);

    void init_buffer(struct EmulationMachine* emulatorInstance);

    void cwrite(struct EmulationMachine* emulatorInstance, char _c);

    void set_buffering_enabled(struct EmulationMachine* emulatorInstance, c_bool _bool);

    u32 peek_ORG_from_file(struct EmulationMachine *emulatorInstance);

    c_bool is_next_inst_scan(struct EmulationMachine *emulator);
}

typedef struct __emulation_data__ 
{
    string _src;
    string _bin;
    bool   _can;

    void init() { _src = ""; _bin = ""; _can = false; }

    string src()    { return _src; }
    string bin()    { return _bin; }
    bool   valid()  { return _can; }

    void setSrc(string _src_) { _src = _src_; }
    void setBin(string _bin_) { _bin = _bin_; setValid(true); }
    void setValid(bool _can_) { _can = _can_; }

} EmulationData;


class Dispatcher : public WContainerWidget
{
    public:
        Dispatcher();

        virtual ~Dispatcher() {
            if (runBinaryThread.get_id() != std::this_thread::get_id() &&
                runBinaryThread.joinable())
            runBinaryThread.join();

            if (nextIstructionThread.get_id() != std::this_thread::get_id() &&
                nextIstructionThread.joinable())
            nextIstructionThread.join();
        }

    private:
        struct EmulationMachine* emulatorInstance;
        SemanticState*           assemblerState;

        EmulationData emulationData;

        WTemplate*      XMLTemplate;
        WStackedWidget* stackedWidget;

        WPushButton* toogleEditorButton;
        WPushButton* toogleMemoryButton;
        WPushButton* toogleConsoleButton;

        WPushButton* clearConsoleButton;
        WPushButton* downloadSourceCode;

        WPushButton* assembleButton;
        WPushButton* runButton;
        WPushButton* debugButton;

        WPushButton* executeNextIstructionButton;
        WPushButton* continueExecutionButton;
        WPushButton* stopExecutionButton;
        WPushButton* clearRegistersButton;

        Editor*         editorWidget;
        MemoryView*     memoryWidget;
        Console*        consoleWidget;
        RegisterRender* registerRenderWidget;
    
        thread runBinaryThread;
        thread nextIstructionThread;

        std::atomic<bool> quitThread_runBinaryThread;
        std::atomic<bool> quitThread_nextIstructionThread;

        std::atomic<bool> isDebugMode;
        std::atomic<bool> isRunningOnRunThread;
        std::atomic<bool> isDebugStarted;
        std::atomic<bool> isNextButtonClicked;

        std::vector<int>  breakpointList;
        std::atomic<int>  breakpointLine;

        JSignal<std::string>  jsBreakpointRequest;
        void                  onBreakpointRequest(std::string result);

        Signal<> doNextHighlightInContinueMode;

        void do_compile();
        void __compile();

        void do_run();
        void do_debug();

        void do_next();
        void do_stop();
        void do_continue();

        void doRun_WorkerThreadBody(WApplication *app,  struct EmulationMachine* em, std::atomic<bool>& quit);
        void doNext_WorkerThreadBody(WApplication* app, struct EmulationMachine* em, std::atomic<bool>& quit);
};



#endif // __dispatcher__68000__