#include "dispatcher.hpp"

#include <fstream>
#include <algorithm>
#include <jeayeson/jeayeson.hpp>

#include <Wt/WServer.h>


unsigned long long FILE_COUNTER = 0;

/**
 * Class constructor
 * 
 * init all widget and set their behaviours
 */
Dispatcher::Dispatcher()
    : stackedWidget(nullptr),
    toogleEditorButton(nullptr),
    toogleMemoryButton(nullptr), 
    editorWidget(nullptr),
    toogleConsoleButton(nullptr),
    registerRenderWidget(nullptr),
    executeNextIstructionButton(nullptr),
    continueExecutionButton(nullptr),
    compileButton(nullptr),
    runButton(nullptr),
    debugButton(nullptr),
    emulatorInstance(nullptr),
    assemblerState(nullptr),
    quitThread_runBinaryThread(false),
    quitThread_nextIstructionThread(false),
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

    XMLTemplate = this->addWidget(make_unique<WTemplate>(tr("render-msg")));

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

    toogleEditorButton  = XMLTemplate->bindWidget("code",      move(c_btn));
    toogleMemoryButton  = XMLTemplate->bindWidget("memory",    move(m_btn));
    toogleConsoleButton = XMLTemplate->bindWidget("console",   move(k_btn));
    clearConsoleButton  = XMLTemplate->bindWidget("clear-btn", move(clear_c));

    compileButton = XMLTemplate->bindWidget("compile", move(comp_btn));
    runButton     = XMLTemplate->bindWidget("run",     move(r_btn));
    debugButton   = XMLTemplate->bindWidget("debug",   move(d_btn));

    executeNextIstructionButton  = XMLTemplate->bindWidget("next",      move(n_btn));
    stopExecutionButton          = XMLTemplate->bindWidget("stop",      move(s_btn));
    continueExecutionButton      = XMLTemplate->bindWidget("terminate", move(t_btn));
    clearRegistersButton         = XMLTemplate->bindWidget("clr",       move(clr_btn));

    executeNextIstructionButton->setDisabled(true);
    continueExecutionButton->setDisabled(true);
    stopExecutionButton->setDisabled(true);
    runButton->setDisabled(true);
    debugButton->setDisabled(true);
    clearConsoleButton->hide();

    auto stack = make_unique<Wt::WStackedWidget>();
    stackedWidget = XMLTemplate->bindWidget("widget", move(stack));

    auto reg_rend = make_unique<RegisterRender>();
    registerRenderWidget = XMLTemplate->bindWidget("register_render", move(reg_rend));

    editorWidget = stackedWidget->addWidget(make_unique<Editor>());
    editorWidget->setUpEditor();

    memoryWidget = stackedWidget->addWidget(make_unique<MemoryView>());
    memoryWidget->setUpMemory();

    consoleWidget = stackedWidget->addWidget(make_unique<Console>());
    consoleWidget->setUpConsole();

    stackedWidget->setCurrentWidget(editorWidget);
    toogleEditorButton->setStyleClass("button-box-item2-selected");

    toogleEditorButton->clicked().connect(this,      [=]{
        clearConsoleButton->hide();
        stackedWidget->setCurrentWidget(editorWidget);
        toogleEditorButton->setStyleClass("button-box-item2-selected");
        toogleMemoryButton->setStyleClass("button-box-item2");
        toogleConsoleButton->setStyleClass("button-box-item2");
    });

    toogleMemoryButton->clicked().connect(this,    [=]{
        clearConsoleButton->hide();
        stackedWidget->setCurrentWidget(memoryWidget);
        toogleEditorButton->setStyleClass("button-box-item2");
        toogleMemoryButton->setStyleClass("button-box-item2-selected");
        toogleConsoleButton->setStyleClass("button-box-item2");
    });

    toogleConsoleButton->clicked().connect(this,   [=]{
        clearConsoleButton->show();
        stackedWidget->setCurrentWidget(consoleWidget);
        toogleEditorButton->setStyleClass("button-box-item2");
        toogleMemoryButton->setStyleClass("button-box-item2");
        toogleConsoleButton->setStyleClass("button-box-item2-selected");
    });


    executeNextIstructionButton->clicked().connect(this, &Dispatcher::do_next);
    stopExecutionButton->clicked().connect(this,      &Dispatcher::do_stop);
    continueExecutionButton->clicked().connect(this, &Dispatcher::do_terminate);

    compileButton->clicked().connect(this, &Dispatcher::do_compile);
    runButton->clicked().connect(this,     &Dispatcher::do_run);
    debugButton->clicked().connect(this,   &Dispatcher::do_debug);

    editorWidget->text_changed.connect(this, [=] { 
                                                runButton->setDisabled(true);
                                                debugButton->setDisabled(true);
                                                compileButton->setDisabled(false);
                                            } 
                                        );

    clearConsoleButton->clicked().connect(this, [=] { consoleWidget->clear(); });

    clearRegistersButton->clicked().connect(this, [=] { registerRenderWidget->clear(); });

    emulationData.init();
}


/**
 * ACTION compile 
 * 
 * no thread needed
 */
void Dispatcher::do_compile()
{
    clearConsoleButton->show();
    stackedWidget->setCurrentWidget(consoleWidget);
    toogleEditorButton->setStyleClass("button-box-item2");
    toogleMemoryButton->setStyleClass("button-box-item2");
    toogleConsoleButton->setStyleClass("button-box-item2-selected");

    WString src = editorWidget->text_();

    consoleWidget->begin_assembler();

    if (!src.empty())
    {
        string fname = "sources/src" + to_string(FILE_COUNTER++) + ".X68";

        emulationData.setSrc(fname);

        std::ofstream file(fname);
        if (file.is_open()) 
        {
            file << src;
            file.close();

            string bname = fname;
            replace(bname.begin(), bname.end(), 'X', 'B');

            assemblerState = obtain_semantic_state();

            if (assemblerState)
            {
                if (!assemble(assemblerState, fname.c_str()))
                {
                    consoleWidget->push_simple_stdout(string(assemblerState->_asseble_error));
                    emulationData.setValid(false);
                }
                else
                {
                    emulationData.setBin(bname);
                    emulationData.setValid(true);

                    consoleWidget->end_assembler();
                    runButton->setDisabled(false);
                    debugButton->setDisabled(false);
                    compileButton->setDisabled(true);
                }

                free_SemanticState(assemblerState);
            }
            else
            { consoleWidget->assembler_error(); emulationData.setValid(false); }  
        }
        else
        {   consoleWidget->assembler_error(); emulationData.setValid(false); }
    }
    else
    {   consoleWidget->push_simple_stdout("Empty source file.\n"); emulationData.setValid(false); }
}


/**
 * ACTION run source
 * 
 * detatching a thread to executing run task
 * enabling stop button that toggle a std::atomic<bool> to quit it
 */
void Dispatcher::do_run()
{
    WApplication *app = WApplication::instance();

    registerRenderWidget->clear();

    executeNextIstructionButton->setDisabled(true);
    continueExecutionButton->setDisabled(true);
    stopExecutionButton->setDisabled(false);
    runButton->setDisabled(true);
    debugButton->setDisabled(true);

    memoryWidget->enableFetch(true);

    consoleWidget->disable(false);

    if (emulationData.valid())
    {      
        emulatorInstance = obtain_emulation_machine(emulationData.bin().c_str());
        consoleWidget->setEmulator(emulatorInstance);
        memoryWidget->setEmulator(emulatorInstance);

        begin_emulator(emulatorInstance);

        init_buffer(emulatorInstance);

        memoryWidget->update(peek_ORG_from_file(emulatorInstance));

        consoleWidget->begin_program();

        app->enableUpdates(true);

        quitThread_runBinaryThread = false;
        
        if (runBinaryThread.joinable())
            runBinaryThread.join();
            
        runBinaryThread = std::thread(std::bind(&Dispatcher::doRun_WorkerThreadBody, this, app, emulatorInstance, std::ref(quitThread_runBinaryThread)));     
  
    }
}


/**
 * THREAD runBinaryThread
 * 
 * execute a .B68 file
 */
void Dispatcher::doRun_WorkerThreadBody(WApplication *app, struct EmulationMachine* em, std::atomic<bool>& quit)
{
    while (emulate(em) && !quit)
    {
        WApplication::UpdateLock uiLock(app);
    
        if (uiLock) 
        {
            consoleWidget->push_stdout(em->Machine.dump);
            registerRenderWidget->update(em->Machine.dump);
            memoryWidget->update();

            app->triggerUpdate();
        }
    }   
    
    WApplication::UpdateLock uiLock(app);
    
    if (uiLock) 
    {
        registerRenderWidget->update(em->Machine.dump);
        consoleWidget->push_stdout(emulatorInstance->Machine.dump);

        memoryWidget->update();
        memoryWidget->enableFetch(false);

        end_emulator(em);
        em = nullptr;

        consoleWidget->disable(true);
        consoleWidget->end_program();

        editorWidget->disable(false);
        runButton->setDisabled(false);
        debugButton->setDisabled(false);

        executeNextIstructionButton->setDisabled(true);
        continueExecutionButton->setDisabled(true);
        stopExecutionButton->setDisabled(true);

        consoleWidget->setEmulator(nullptr);
        memoryWidget->setEmulator(nullptr);

        app->triggerUpdate();

        app->enableUpdates(false);
    } 
    else 
    {
        end_emulator(em);
        em = nullptr;
        return;
    }
}


/**
 * ACTION debug
 * 
 * init emulatorInstance and pseudo-stdin
 * just it
 */
void Dispatcher::do_debug()
{
    WApplication *app = WApplication::instance();
    registerRenderWidget->clear();

    editorWidget->disable(true);

    executeNextIstructionButton->setDisabled(false);
    continueExecutionButton->setDisabled(false);
    stopExecutionButton->setDisabled(false);

    memoryWidget->enableFetch(true);

    runButton->setDisabled(true);
    debugButton->setDisabled(true);

    if (emulationData.valid())
    {
        emulatorInstance = obtain_emulation_machine(emulationData.bin().c_str());
        consoleWidget->setEmulator(emulatorInstance);
        memoryWidget->setEmulator(emulatorInstance);

        begin_emulator(emulatorInstance);

        init_buffer(emulatorInstance);

        memoryWidget->update(peek_ORG_from_file(emulatorInstance));

        consoleWidget->begin_program();

        consoleWidget->disable(false);
    }

}


/**
 * ACTION next
 * 
 * execute in detatched mode a single instruction
 * include std::atomic<bool> to kill it 
 */
void Dispatcher::do_next()
{
    WApplication *app = WApplication::instance();

    app->enableUpdates(true);

    quitThread_nextIstructionThread = false;

    executeNextIstructionButton->setDisabled(true);
        
    if (nextIstructionThread.joinable())
        nextIstructionThread.join();
        
    nextIstructionThread = std::thread(std::bind(&Dispatcher::doNext_WorkerThreadBody, this, app, emulatorInstance, std::ref(quitThread_nextIstructionThread)));
}


/**
 * THREAD nextIstructionThread
 * 
 * execute a single istruction, if ACTION stop will be triggered
 * or the emulation end, it will terminate the emulation and 
 * 'fetch and push' last data to widgets 
 * 
 */
void Dispatcher::doNext_WorkerThreadBody(WApplication* app, struct EmulationMachine* em, std::atomic<bool>& quit)
{
    if (emulate(emulatorInstance) && !quit)
    {
        WApplication::UpdateLock uiLock(app);
    
        if (uiLock) 
        {
            consoleWidget->push_stdout(em->Machine.dump);
            registerRenderWidget->update(em->Machine.dump);
            memoryWidget->update();

            executeNextIstructionButton->setDisabled(false); 

            app->triggerUpdate();

            app->enableUpdates(false);
        }
    }    
    else
    {
        WApplication::UpdateLock uiLock(app);
        
        if (uiLock) 
        {
            registerRenderWidget->update(em->Machine.dump);
            consoleWidget->push_stdout(emulatorInstance->Machine.dump);

            memoryWidget->update();
            memoryWidget->enableFetch(false);

            end_emulator(em);
            em = nullptr;

            consoleWidget->disable(true);
            consoleWidget->end_program();

            editorWidget->disable(false);
            runButton->setDisabled(false);
            debugButton->setDisabled(false);

            executeNextIstructionButton->setDisabled(true);
            continueExecutionButton->setDisabled(true);
            stopExecutionButton->setDisabled(true);

            consoleWidget->setEmulator(nullptr);
            memoryWidget->setEmulator(nullptr);

            app->triggerUpdate();

            app->enableUpdates(false);
        } 
        else 
        {
            end_emulator(em);
            em = nullptr;
            return;
        }       
    }
}


/**
 * ACTION terminate
 * 
 * execute in detatched mode the last part of .B68 file
 * include std::atomic<bool> to kill it 
 * 
 * use runBinaryThread to perform this task
 */
void Dispatcher::do_terminate()
{
    WApplication *app = WApplication::instance();

    app->enableUpdates(true);
        
    quitThread_runBinaryThread = false;
    
    if (runBinaryThread.joinable())
        runBinaryThread.join();
        
    runBinaryThread = std::thread(std::bind(&Dispatcher::doRun_WorkerThreadBody, this, app, emulatorInstance, std::ref(quitThread_runBinaryThread)));     
}



/**
 * ACTION stop
 * 
 * force to terminate all active threads,
 * also disable pseudo-stdin 
 */
void Dispatcher::do_stop()
{
    set_buffering_enabled(emulatorInstance, c_false);

    quitThread_runBinaryThread = true;
    quitThread_nextIstructionThread   = true;
}

