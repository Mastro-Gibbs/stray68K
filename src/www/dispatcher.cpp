#include "dispatcher.hpp"

#include <fstream>
#include <algorithm>
#include <jeayeson/jeayeson.hpp>

#include <Wt/WServer.h>




unsigned long long FILE_COUNTER = 0;


Dispatcher::Dispatcher()
    : stack_(nullptr),
    code(nullptr),
    memory(nullptr), 
    editor_(nullptr),
    console(nullptr),
    reg_rend_(nullptr),
    next_istr(nullptr),
    terminate(nullptr),
    compile(nullptr),
    run(nullptr),
    debug(nullptr),
    WContainerWidget()
{
    WApplication* instance = WApplication::instance();
    
    instance->messageResourceBundle().use("template/xmls/editor");
    instance->useStyleSheet("template/css/editor.css"); 

    instance->messageResourceBundle().use("template/xmls/memory");
    instance->useStyleSheet("template/css/memory.css");

    instance->messageResourceBundle().use("template/xmls/console");
    instance->useStyleSheet("template/css/console.css");

    instance->messageResourceBundle().use("template/xmls/render");
    instance->useStyleSheet("template/css/render.css");

    template_ = this->addWidget(make_unique<WTemplate>(tr("render-msg")));

    auto c_btn = make_unique<WPushButton>(tr("code"));
    c_btn->setText("Code");
    c_btn->setStyleClass("button-box-item2");

    auto m_btn = make_unique<WPushButton>(tr("memory"));
    m_btn->setText("Memory");
    m_btn->setStyleClass("button-box-item2");

    auto k_btn = make_unique<WPushButton>(tr("console"));
    k_btn->setText("Console");
    k_btn->setStyleClass("button-box-item2");

    auto n_btn = make_unique<WPushButton>(tr("next"));
    n_btn->setText("Next");
    n_btn->setStyleClass("button-box-item2");

    auto s_btn = make_unique<WPushButton>(tr("terminate"));
    s_btn->setText("Stop");
    s_btn->setStyleClass("button-box-item2");

    auto t_btn = make_unique<WPushButton>(tr("terminate"));
    t_btn->setText("Terminate");
    t_btn->setStyleClass("button-box-item2");

    auto clr_btn = make_unique<WPushButton>(tr("clr"));
    clr_btn->setText("Clear");
    clr_btn->setStyleClass("button-box-item2");

    auto comp_btn = make_unique<WPushButton>(tr("compile"));
    comp_btn->setText("Compile");
    comp_btn->setStyleClass("button-box-item2");

    auto r_btn = make_unique<WPushButton>(tr("run"));
    r_btn->setText("Run");
    r_btn->setStyleClass("button-box-item2");

    auto d_btn = make_unique<WPushButton>(tr("debug"));
    d_btn->setText("Debug");
    d_btn->setStyleClass("button-box-item2");

    auto clear_c = make_unique<WPushButton>();
    clear_c->setStyleClass("button-box-item2");
    clear_c->setText("Clear");

    code      = template_->bindWidget("code",      move(c_btn));
    memory    = template_->bindWidget("memory",    move(m_btn));
    console   = template_->bindWidget("console",   move(k_btn));

    clear_  = template_->bindWidget("clear-btn", move(clear_c));

    compile = template_->bindWidget("compile", move(comp_btn));
    run     = template_->bindWidget("run",     move(r_btn));
    debug   = template_->bindWidget("debug",   move(d_btn));

    next_istr  = template_->bindWidget("next",      move(n_btn));
    stop       = template_->bindWidget("stop",      move(s_btn));
    terminate  = template_->bindWidget("terminate", move(t_btn));
    clear_regs = template_->bindWidget("clr",       move(clr_btn));

    next_istr->setDisabled(true);
    terminate->setDisabled(true);
    stop->setDisabled(true);
    run->setDisabled(true);
    debug->setDisabled(true);
    clear_->hide();

    auto stack = make_unique<Wt::WStackedWidget>();
    stack_ = template_->bindWidget("widget", move(stack));

    auto reg_rend = make_unique<RegisterRender>();
    reg_rend_ = template_->bindWidget("register_render", move(reg_rend));

    editor_ = stack_->addWidget(make_unique<Editor>());
    editor_->setUpEditor();

    memory_ = stack_->addWidget(make_unique<MemoryView>());
    memory_->setUpMemory();

    console_ = stack_->addWidget(make_unique<Console>());
    console_->setUpConsole();

    stack_->setCurrentWidget(editor_);
    code->setStyleClass("button-box-item2-selected");

    code->clicked().connect(this,      &Dispatcher::show_editor);
    memory->clicked().connect(this,    &Dispatcher::show_memory);
    console->clicked().connect(this,   &Dispatcher::show_console);
    next_istr->clicked().connect(this, &Dispatcher::do_next);
    stop->clicked().connect(this,      &Dispatcher::do_stop);
    terminate->clicked().connect(this, &Dispatcher::do_terminate);

    compile->clicked().connect(this, &Dispatcher::compile_src);
    run->clicked().connect(this,     &Dispatcher::run_src);
    debug->clicked().connect(this,   &Dispatcher::debug_src);

    editor_->text_changed.connect(this, &Dispatcher::lock_btns);

    clear_->clicked().connect(this, [=] { console_->clear(); });

    clear_regs->clicked().connect(this, [=] { reg_rend_->clear(); });

    edata.init();
}


void Dispatcher::show_editor()
{   
    clear_->hide();
    stack_->setCurrentWidget(editor_);
    code->setStyleClass("button-box-item2-selected");
    memory->setStyleClass("button-box-item2");
    console->setStyleClass("button-box-item2");
}

void Dispatcher::show_memory()
{
    clear_->hide();
    stack_->setCurrentWidget(memory_);
    code->setStyleClass("button-box-item2");
    memory->setStyleClass("button-box-item2-selected");
    console->setStyleClass("button-box-item2");
}

void Dispatcher::show_console()
{
    clear_->show();
    stack_->setCurrentWidget(console_);
    code->setStyleClass("button-box-item2");
    memory->setStyleClass("button-box-item2");
    console->setStyleClass("button-box-item2-selected");
}


void Dispatcher::do_next()
{
    if (!emulate())
        do_stop();
    else
    {
        reg_rend_->update(machine_status());
        console_->push_stdout(machine_status());
        memory_->update();
    }
}


void Dispatcher::do_stop()
{
    next_istr->setDisabled(true);
    terminate->setDisabled(true);
    stop->setDisabled(true);
    run->setDisabled(false);
    debug->setDisabled(false);

    editor_->disable(false);

    memory_->enableFetch(false);

    end_emulator();

    reg_rend_->update(machine_status());
    console_->push_stdout(machine_status());
    memory_->update();
}

void Dispatcher::do_terminate()
{
    WApplication *app = WApplication::instance();

    app->enableUpdates(true);
        
    if (terminateThread_.joinable())
        terminateThread_.join();
        
    terminateThread_ = std::thread(std::bind(&Dispatcher::doTerminate, this, app));
}

void Dispatcher::doTerminate(WApplication *app)
{
    while (emulate())
    {
        WApplication::UpdateLock uiLock(app);
    
        if (uiLock) 
        {
            console_->push_stdout(machine_status());

            app->triggerUpdate();
        }
    } 

    WApplication::UpdateLock uiLock(app);
    
    if (uiLock) 
    {
        reg_rend_->update(machine_status());
        console_->push_stdout(machine_status());
        memory_->update();
        memory_->enableFetch(false);

        end_emulator();

        next_istr->setDisabled(true);
        terminate->setDisabled(true);
        stop->setDisabled(true);
        run->setDisabled(false);
        debug->setDisabled(false);

        editor_->disable(false);

        app->triggerUpdate();

        app->enableUpdates(false);
    } 
    else{
        end_emulator();
        return;
    } 
}

void Dispatcher::compile_src()
{
    show_console();

    WString src = editor_->text_();

    console_->insert("Compiling source code.\n");

    if (!src.empty())
    {
        string fname = "sources/src" + to_string(FILE_COUNTER++) + ".X68";

        edata.setSrc(fname);

        std::ofstream file(fname);
        if (file.is_open()) 
        {
            file << src;
            file.close();

            string cmd = "> stray68k " + fname;

            console_->insert(cmd + "\n");

            if (!assemble(fname.c_str()))
            {
                WString err = WString(assemble_status());
                console_->insert(err + "\n");
                console_->insert("Could not assemble.\n");
                edata.setValid(false);
            }
            else
            {
                string bname = fname;
                replace(bname.begin(), bname.end(), 'X', 'B');
                edata.setBin(bname);
                edata.setValid(true);

                console_->insert("Success.\n");
                run->setDisabled(false);
                debug->setDisabled(false);
                compile->setDisabled(true);
            }
        }
        else
        {   console_->insert("Error.\n"); edata.setValid(false); }
    }
    else
    {   console_->insert("Empty source file.\n"); edata.setValid(false); }
}



void Dispatcher::run_src()
{
    WApplication *app = WApplication::instance();

    reg_rend_->clear();

    next_istr->setDisabled(true);
    terminate->setDisabled(true);
    stop->setDisabled(true);

    memory_->enableFetch(true);

    if (edata.valid())
    {      
        app->enableUpdates(true);
        
        if (runnerThread_.joinable())
            runnerThread_.join();
            
        runnerThread_ = std::thread(std::bind(&Dispatcher::doRun, this, app));       
    }
}

void Dispatcher::doRun(WApplication *app)
{
    begin_emulator(edata.bin().c_str());
    while (emulate())
    {
        WApplication::UpdateLock uiLock(app);
    
        if (uiLock) 
        {
            console_->push_stdout(machine_status());

            app->triggerUpdate();
        }
    }   
    
    WApplication::UpdateLock uiLock(app);
    
    if (uiLock) 
    {
        reg_rend_->update(machine_status());
        console_->push_stdout(machine_status());
        memory_->update();
        memory_->enableFetch(false);

        end_emulator();

        editor_->disable(false);

        app->triggerUpdate();

        app->enableUpdates(false);
    } 
    else 
    {
        end_emulator();
        return;
    }
}

void Dispatcher::debug_src()
{
    WApplication *app = WApplication::instance();
    reg_rend_->clear();

    editor_->disable(true);

    next_istr->setDisabled(false);
    terminate->setDisabled(false);
    stop->setDisabled(false);

    memory_->enableFetch(true);

    run->setDisabled(true);
    debug->setDisabled(true);

    if (edata.valid())
    {
        begin_emulator(edata.bin().c_str());
    }

}

void Dispatcher::lock_btns()
{
    run->setDisabled(true);
    debug->setDisabled(true);
    compile->setDisabled(false);
}
