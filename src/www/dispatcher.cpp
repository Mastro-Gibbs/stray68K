#include "dispatcher.hpp"

#include <ctime>
#include <fstream>
#include <algorithm>
#include <jeayeson/jeayeson.hpp>

#include <Wt/WServer.h>
#include <Wt/WFileResource.h>


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
    clearConsoleButton(nullptr),
    downloadSourceCode(nullptr),
    executeNextIstructionButton(nullptr),
    continueExecutionButton(nullptr),
    assembleButton(nullptr),
    runButton(nullptr),
    debugButton(nullptr),
    emulatorInstance(nullptr),
    assemblerState(nullptr),
    quitThread_runBinaryThread(false),
    quitThread_nextIstructionThread(false),
    isDebugMode(false),
    isRunningOnRunThread(false),
    isDebugStarted(false),
    isNextButtonClicked(false),
    jsBreakpointRequest(this, "onEditorLineIndex_Signal"),
    breakpointLine(-1),
    WContainerWidget()
{
    setId("DispatcherCpp");

    WApplication* instance = WApplication::instance();

    instance->require("template/js/utils.js");
    
    instance->messageResourceBundle().use("template/xmls/editor");
    instance->useStyleSheet("template/css/editor.css"); 

    instance->messageResourceBundle().use("template/xmls/memory");
    instance->useStyleSheet("template/css/memory.css");

    instance->messageResourceBundle().use("template/xmls/console");
    instance->useStyleSheet("template/css/console.css");

    instance->messageResourceBundle().use("template/xmls/render");
    instance->useStyleSheet("template/css/render.css");

    XMLTemplate = this->addWidget(make_unique<WTemplate>(tr("render-msg")));

    // creating all buttons
    auto c_btn = make_unique<WPushButton>();
    c_btn->setText("Code");
    c_btn->setStyleClass("button-box-item2-selected");

    auto m_btn = make_unique<WPushButton>();
    m_btn->setText("Memory");
    m_btn->setStyleClass("button-box-item2");

    auto k_btn = make_unique<WPushButton>();
    k_btn->setText("Console");
    k_btn->setStyleClass("button-box-item2-2");

    auto n_btn = make_unique<WPushButton>();
    n_btn->setText("Next");
    n_btn->setStyleClass("button-box-item2");

    auto s_btn = make_unique<WPushButton>();
    s_btn->setText("Stop");
    s_btn->setStyleClass("button-box-item2");

    auto t_btn = make_unique<WPushButton>();
    t_btn->setText("Continue");
    t_btn->setStyleClass("button-box-item2");

    auto clr_btn = make_unique<WPushButton>();
    clr_btn->setText("Clear");
    clr_btn->setStyleClass("button-box-item2");

    auto comp_btn = make_unique<WPushButton>();
    comp_btn->setText("Assemble");
    comp_btn->setStyleClass("button-box-item2");

    auto r_btn = make_unique<WPushButton>();
    r_btn->setText("Run");
    r_btn->setStyleClass("button-box-item2");

    auto d_btn = make_unique<WPushButton>();
    d_btn->setText("Debug");
    d_btn->setStyleClass("button-box-item2");

    auto clear_c = make_unique<WPushButton>();
    clear_c->setStyleClass("button-box-item2");
    clear_c->setText("Clear");

    auto dload = make_unique<WPushButton>();
    dload->setStyleClass("button-box-item2");
    dload->setText("Download");


    // get instance of WStackedWidget
    auto stack = make_unique<Wt::WStackedWidget>();


    // get instance of RegisterRender
    auto reg_rend = make_unique<RegisterRender>();


    // binding all widgets
    stackedWidget = XMLTemplate->bindWidget("widget", move(stack));
    editorWidget = stackedWidget->addWidget(make_unique<Editor>());
    memoryWidget = stackedWidget->addWidget(make_unique<MemoryView>());    
    consoleWidget = stackedWidget->addWidget(make_unique<Console>());

    toogleEditorButton  = XMLTemplate->bindWidget("code",      move(c_btn));
    toogleMemoryButton  = XMLTemplate->bindWidget("memory",    move(m_btn));
    toogleConsoleButton = XMLTemplate->bindWidget("console",   move(k_btn));
    clearConsoleButton  = XMLTemplate->bindWidget("clear-btn", move(clear_c));
    downloadSourceCode  = XMLTemplate->bindWidget("download",  move(dload));

    assembleButton = XMLTemplate->bindWidget("compile", move(comp_btn));
    runButton      = XMLTemplate->bindWidget("run",     move(r_btn));
    debugButton    = XMLTemplate->bindWidget("debug",   move(d_btn));

    executeNextIstructionButton  = XMLTemplate->bindWidget("next",     move(n_btn));
    stopExecutionButton          = XMLTemplate->bindWidget("stop",     move(s_btn));
    continueExecutionButton      = XMLTemplate->bindWidget("continue", move(t_btn));
    clearRegistersButton         = XMLTemplate->bindWidget("clr",      move(clr_btn));

    registerRenderWidget = XMLTemplate->bindWidget("register_render", move(reg_rend));


    // button behavior connection
    executeNextIstructionButton->clicked().connect(this, &Dispatcher::do_next);
    stopExecutionButton->clicked().connect(this,         &Dispatcher::do_stop);
    continueExecutionButton->clicked().connect(this,     &Dispatcher::do_continue);

    assembleButton->clicked().connect(this, &Dispatcher::do_compile);
    runButton->clicked().connect(this,      &Dispatcher::do_run);
    debugButton->clicked().connect(this,    &Dispatcher::do_debug);


    // lambda func connections
    toogleEditorButton->clicked().connect(this,      [=]{
        clearConsoleButton->hide();
        stackedWidget->setCurrentWidget(editorWidget);
        toogleEditorButton->setStyleClass("button-box-item2-selected");
        toogleMemoryButton->setStyleClass("button-box-item2");
        toogleConsoleButton->setStyleClass("button-box-item2-2");
    });

    toogleMemoryButton->clicked().connect(this,    [=]{
        clearConsoleButton->hide();
        stackedWidget->setCurrentWidget(memoryWidget);
        toogleEditorButton->setStyleClass("button-box-item2");
        toogleMemoryButton->setStyleClass("button-box-item2-selected");
        toogleConsoleButton->setStyleClass("button-box-item2-2");
    });

    toogleConsoleButton->clicked().connect(this,   [=]{
        clearConsoleButton->show();
        stackedWidget->setCurrentWidget(consoleWidget);
        toogleEditorButton->setStyleClass("button-box-item2");
        toogleMemoryButton->setStyleClass("button-box-item2");
        toogleConsoleButton->setStyleClass("button-box-item2-2-selected");
    });

    editorWidget->onTextChange.connect(this, [=] { 
        runButton->setDisabled(true);
        debugButton->setDisabled(true);
        assembleButton->setDisabled(false);
        doJavaScript("\
            var editor = ace.edit('editor'); \
            var breakpoints = editor.session.getBreakpoints(); \
            for (var ln in breakpoints) { \
                editor.session.clearBreakpoint(ln); \
            }\
        ");
    });

    clearConsoleButton->clicked().connect(this, [=] { 
        consoleWidget->clear(); 
    });

    clearRegistersButton->clicked().connect(this, [=] { 
        registerRenderWidget->clear(); 
    });

    downloadSourceCode->clicked().connect(this, [=]{
        string content = escapeText(editorWidget->getText()).toUTF8();

        time_t now = std::time(nullptr);
        char buf[150];
        strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", localtime(&now));
        string dateTimeStr(buf);
        string filename = "source" + dateTimeStr + ".X68";

        downloadSourceCode->disable();

        downloadSourceCode->doJavaScript("downloadSourceFile('" + filename + "');");

        downloadSourceCode->enable();
    });


    editorWidget->onTextAvailable.connect(this, &Dispatcher::__compile);

    editorWidget->onBreakpointsAvavilable.connect(this, [=]{
        breakpointList = editorWidget->getBreakpointList();
    });

    jsBreakpointRequest.connect(std::bind(&Dispatcher::onBreakpointRequest, this, std::placeholders::_1));


    doNextHighlightInContinueMode.connect(this, [=]{
        doJavaScript("doLineHighLight();");
    });


    // init struct
    emulationData.init();


    // setting-up some buttons init state
    executeNextIstructionButton->setDisabled(true);
    continueExecutionButton->setDisabled(true);
    stopExecutionButton->setDisabled(true);
    runButton->setDisabled(true);
    debugButton->setDisabled(true);
    clearConsoleButton->hide();


    // setting-up some widgets
    memoryWidget->setUpMemory();
    consoleWidget->setUpConsole();

    stackedWidget->setCurrentWidget(editorWidget);

    doJavaScript("hidePopupConsoleDiv();");
}


/**
 * ACTION compile 
 * 
 * no thread needed
 */
void Dispatcher::do_compile()
{
    WApplication::instance()->require("template/js/ace-editor/ace_signal.js");
    doJavaScript("getACEEditorText();");
}

/**
 * PRIVATE method
 * 
 * callback, exetends do_compile()
 */
void Dispatcher::__compile()
{
    clearConsoleButton->show();
    stackedWidget->setCurrentWidget(consoleWidget);
    toogleEditorButton->setStyleClass("button-box-item2");
    toogleMemoryButton->setStyleClass("button-box-item2");
    toogleConsoleButton->setStyleClass("button-box-item2-2-selected");

    std::string src = editorWidget->getText();

    if (!src.empty())
    {
        consoleWidget->writeAssemblingStarted();
        
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
                int status = EXIT_FAILURE;
                status = assemble(assemblerState, fname.c_str());

                switch (status)
                {
                    case EXIT_FAILURE:
                        consoleWidget->pushText(string(assemblerState->_asseble_error));
                        emulationData.setValid(false);
                        break;

                    case EXIT_WARNING:
                        consoleWidget->pushText(string(assemblerState->_asseble_error), false);

                    case EXIT_SUCCESS:
                        emulationData.setBin(bname);
                        emulationData.setValid(true);
                        consoleWidget->writeAssemblingDone();
                        runButton->setDisabled(false);
                        debugButton->setDisabled(false);
                        assembleButton->setDisabled(true);
                        break;
                }

                free_SemanticState(assemblerState);

            }
            else
            { consoleWidget->writeAssemblingFail(); emulationData.setValid(false); }  
        }
        else
        {   consoleWidget->writeAssemblingFail(); emulationData.setValid(false); }
    }
    else
    {   consoleWidget->pushText("Empty source file."); emulationData.setValid(false); }

}


/**
 * ACTION run source
 * 
 * detatching a thread to executing run task
 * enabling stop button that toggle a std::atomic<bool> to quit it
 */
void Dispatcher::do_run()
{
    if (emulationData.valid())
    { 
        WApplication *app = WApplication::instance();
        app->require("template/js/ace-editor/line-highlighter.js");

        registerRenderWidget->clear();
        editorWidget->disable(true);

        executeNextIstructionButton->setDisabled(true);
        continueExecutionButton->setDisabled(true);
        stopExecutionButton->setDisabled(false);
        runButton->setDisabled(true);
        debugButton->setDisabled(true);

        memoryWidget->enableFetch(true);
         
        emulatorInstance = obtain_emulation_machine(emulationData.bin().c_str());
        consoleWidget->setEmulator(emulatorInstance);
        memoryWidget->setEmulator(emulatorInstance);

        begin_emulator(emulatorInstance);

        init_buffer(emulatorInstance);

        memoryWidget->update(peek_ORG_from_file(emulatorInstance));

        consoleWidget->writeProgramStarted();

        app->enableUpdates(true);

        quitThread_runBinaryThread = false;

        isDebugMode = false;
        isRunningOnRunThread = false;
        isDebugStarted = false;

        doJavaScript("removeAllMarkers();");

        (is_next_inst_scan(emulatorInstance) == c_true) ? consoleWidget->disable(false) : consoleWidget->disable(true);
        
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
    while (!quit && emulate(em))
    {
        WApplication::UpdateLock uiLock(app);
    
        if (uiLock) 
        {
            (is_next_inst_scan(em) == c_true) ? consoleWidget->disable(false): consoleWidget->disable(true);

            consoleWidget->pushStdout(em->Machine.dump);
            registerRenderWidget->update(em->Machine.dump);
            memoryWidget->update();

            app->triggerUpdate();
        }
    }   
    
    WApplication::UpdateLock uiLock(app);
    
    if (uiLock) 
    {
        registerRenderWidget->update(em->Machine.dump);
        consoleWidget->pushStdout(emulatorInstance->Machine.dump);

        memoryWidget->update();
        memoryWidget->enableFetch(false);

        end_emulator(em);
        em = nullptr;

        consoleWidget->disable(true);

        quit ? consoleWidget->writeProgramStopped() : consoleWidget->writeProgramFinished();

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
    if (emulationData.valid())
    {
        WApplication *app = WApplication::instance();
        registerRenderWidget->clear();
        app->require("template/js/ace-editor/line-highlighter.js");

        editorWidget->disable(true);

        executeNextIstructionButton->setDisabled(false);
        continueExecutionButton->setDisabled(false);
        stopExecutionButton->setDisabled(false);

        memoryWidget->enableFetch(true);

        runButton->setDisabled(true);
        debugButton->setDisabled(true);
    
        emulatorInstance = obtain_emulation_machine(emulationData.bin().c_str());
        consoleWidget->setEmulator(emulatorInstance);
        memoryWidget->setEmulator(emulatorInstance);

        begin_emulator(emulatorInstance);

        init_buffer(emulatorInstance);

        memoryWidget->update(peek_ORG_from_file(emulatorInstance));

        consoleWidget->writeProgramStarted();

        isDebugMode = true;
        isDebugStarted = false;

        doJavaScript("removeAllMarkers();");
        doJavaScript("getLines();");
        doJavaScript("getBreakPoints();");
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
    app->require("template/js/ace-editor/line-highlighter.js");

    app->enableUpdates(true);

    doJavaScript("doLineHighLight();");

    quitThread_nextIstructionThread = false;

    executeNextIstructionButton->setDisabled(true);

    isDebugStarted = true;
    isNextButtonClicked = true;

    (is_next_inst_scan(emulatorInstance) == c_true) ? consoleWidget->disable(false) : consoleWidget->disable(true);
        
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
    if (!quit && emulate(emulatorInstance))
    {
        WApplication::UpdateLock uiLock(app);
    
        if (uiLock) 
        {
            consoleWidget->pushStdout(em->Machine.dump);
            registerRenderWidget->update(em->Machine.dump);
            memoryWidget->update();

            executeNextIstructionButton->setDisabled(false); 

            if (!isNextButtonClicked)
                doNextHighlightInContinueMode.emit();

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
            consoleWidget->pushStdout(em->Machine.dump);

            memoryWidget->update();
            memoryWidget->enableFetch(false);

            end_emulator(em);
            em = nullptr;

            doJavaScript("resetHighlightingIndex();");

            consoleWidget->disable(true);
            consoleWidget->writeProgramFinished();

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
 * ACTION continue
 * 
 * This method is invoked when the 'Continue' button has been triggered.
 * 
 * The main thing it does is execute doJavaScript("doLineHighLight();")
 * that triggers void Dispatcher::onBreakpointRequest(std::string result)
 * thanks to the JSingal associated.
 */
void Dispatcher::do_continue()
{
    WApplication *app = WApplication::instance();

    app->enableUpdates(true);

    executeNextIstructionButton->setDisabled(true);
    continueExecutionButton->setDisabled(true);

    isNextButtonClicked = false;
    isDebugStarted = true;
    
    doJavaScript("doLineHighLight();");
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
    quitThread_nextIstructionThread = true;

    doJavaScript("resetHighlightingIndex();");
    doJavaScript("removeAllMarkers();");

    if (isDebugMode && (!isRunningOnRunThread || !isDebugStarted))
    {
        registerRenderWidget->update(emulatorInstance->Machine.dump);
        consoleWidget->pushStdout(emulatorInstance->Machine.dump);

        memoryWidget->update();
        memoryWidget->enableFetch(false);

        end_emulator(emulatorInstance);
        emulatorInstance = nullptr;

        consoleWidget->disable(true);
        consoleWidget->writeProgramFinished();

        editorWidget->disable(false);
        runButton->setDisabled(false);
        debugButton->setDisabled(false);

        executeNextIstructionButton->setDisabled(true);
        continueExecutionButton->setDisabled(true);
        stopExecutionButton->setDisabled(true);

        consoleWidget->setEmulator(nullptr);
        memoryWidget->setEmulator(nullptr);      
    }
}


/**
 * CB Handler when line highlighting is done.
 * 
 * If breakpoints have been set and 'Continue' button has been clicked,
 * this CB will be invoked.
 * 
 * The execution of the program will definitely stop on the breakpoit's line.
 * 
 * If there are other instructions that can be executed, the degub state will remain active.
 * 
 * If there isn't any breakpoint and 'Continue' button has been clicked, the entire program will be executed.
 * 
 * Otherwise if the 'Next' button has been clicked, we have a defined behavior: execute next line.
 */
void Dispatcher::onBreakpointRequest(std::string result)
{
    breakpointLine = std::stoi(result);

    if (!breakpointList.empty() && !isNextButtonClicked)
    {
        if (std::find(breakpointList.begin(), breakpointList.end(), breakpointLine) != breakpointList.end())
        {
            continueExecutionButton->setDisabled(false);
            executeNextIstructionButton->setDisabled(false);
            breakpointLine = -1;
        }
        else
        {
            WApplication *app = WApplication::instance();
            app->require("template/js/ace-editor/line-highlighter.js");

            app->enableUpdates(true);

            quitThread_nextIstructionThread = false;

            executeNextIstructionButton->setDisabled(true);

            (is_next_inst_scan(emulatorInstance) == c_true) ? consoleWidget->disable(false) : consoleWidget->disable(true);

            if (nextIstructionThread.joinable())
                nextIstructionThread.join();
                
            nextIstructionThread = std::thread(std::bind(&Dispatcher::doNext_WorkerThreadBody, this, app, emulatorInstance, std::ref(quitThread_nextIstructionThread)));
        }
    }
    else if (breakpointList.empty() && !isNextButtonClicked)
    {
        WApplication *app = WApplication::instance();

        app->enableUpdates(true);
        
        quitThread_runBinaryThread = false;

        executeNextIstructionButton->setDisabled(true);
        continueExecutionButton->setDisabled(true);

        isRunningOnRunThread = true;

        doJavaScript("removeAllMarkers();");
        
        if (runBinaryThread.joinable())
            runBinaryThread.join();
            
        runBinaryThread = std::thread(std::bind(&Dispatcher::doRun_WorkerThreadBody, this, app, emulatorInstance, std::ref(quitThread_runBinaryThread)));     

    }
    
}