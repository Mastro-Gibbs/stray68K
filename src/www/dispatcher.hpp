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

#include <thread>

#include "editor.hpp"
#include "memory.hpp"
#include "console.hpp"
#include "register.hpp"

using namespace Wt;
using namespace std;

extern "C" {

    int assemble(const char* filepath);

    void begin_emulator(const char *path);

    const char* assemble_status();

    void end_emulator();

    int emulate();

    const char* machine_status();

    int is_last_istr();

    void init_buffer();
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
            if (runnerThread_.get_id() != std::this_thread::get_id() &&
                runnerThread_.joinable())
            runnerThread_.join();

            if (terminateThread_.get_id() != std::this_thread::get_id() &&
                terminateThread_.joinable())
            terminateThread_.join();

            if (nextThread_.get_id() != std::this_thread::get_id() &&
                nextThread_.joinable())
            nextThread_.join();
        }

    private:
        EmulationData edata;

        WTemplate*      template_;
        WStackedWidget* stack_;

        WPushButton* code;
        WPushButton* memory;
        WPushButton* console;

        WPushButton* clear_;

        WPushButton* compile;
        WPushButton* run;
        WPushButton* debug;

        WPushButton* next_istr;
        WPushButton* terminate;
        WPushButton* stop;
        WPushButton* clear_regs;

        Editor*         editor_;
        MemoryView*     memory_;
        Console*        console_;
        RegisterRender* reg_rend_;
        
        void show_editor();
        void show_console();
        void show_memory();

        void compile_src();
        void run_src();
        void debug_src();

        void do_next();
        void do_stop();
        void do_terminate();

        void lock_btns();

        thread runnerThread_;
        thread terminateThread_;
        thread nextThread_;

        void doRun(WApplication *app);
        void doTerminate(WApplication *app);
        void doNext(WApplication* app);
};



#endif // __dispatcher__68000__