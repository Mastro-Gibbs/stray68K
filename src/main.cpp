#include <Wt/WApplication.h>

#include "www/header.hpp"
#include "www/dispatcher.hpp"
#include "www/footer.hpp"
#include "www/help.hpp"

#include <Wt/WServer.h>


void scheduledTask()
{
    system("rm sources/*");
}


class App : public Wt::WApplication
{
    public:
        App(const Wt::WEnvironment& env)
            : Wt::WApplication(env)
        {
            setTitle("Stray68K");

            useStyleSheet("template/css/base.css");

            header_     = root()->addWidget(std::make_unique<Header>());
            dispatcher_ = root()->addWidget(std::make_unique<Dispatcher>());
            footer_     = root()->addWidget(std::make_unique<Footer>());
        }

    private:
        Header* header_;
        Dispatcher* dispatcher_;
        Footer* footer_;
};


std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
    auto app = std::make_unique<App>(env);

    std::string editor_template  = "\\t; Stray68K Motorola68000-ASM Emulator\\n\\n\\n\\tORG\\t\\t$1000\\n\\n\\t\\n\\t; place code here\\n\\n\\n\\tEND"; 

    app->require("template/js/utils.js");
    app->require("template/js/ace-editor/ace.js");
    app->require("template/js/ace-editor/theme-tomorrow_night.js");
    app->require("template/js/ace-editor/ext-language_tools.min.js");
    app->require("template/js/ace-editor/highlight/motorola68000.js");
    app->require("template/js/ace-editor/editor-common.js");

    app->doJavaScript(" \
                        var editor = ace.edit('editor');  \
                        editor.setTheme('ace/theme/tomorrow_night');  \
                        editor.setFontSize(16);  \
                        editor.session.setMode('ace/mode/motorola68000');  \
                        \
                        editor.setValue('" + editor_template + "');  \
                        editor.focus(); \
                        editor.gotoLine(6, 1, true); \
                        editor.addEventListener('input', function(){  \
                            let prevMarkers = editor.session.getMarkers(); \
                            if (prevMarkers) { \
                                let prevMarkersArr = Object.keys(prevMarkers); \
                                for (let item of prevMarkersArr) \
                                    editor.session.removeMarker(prevMarkers[item].id); \
                            } \
                            Wt.emit('EditorCpp', 'onEditorInput_Signal');  \
                        });  \
                        \
                        editor.commands.addCommands( \
                            [ \
                                { \
                                    name: 'zoomin',  \
                                    bindKey: {win: 'Ctrl-Alt-I'}, \
                                    exec: function(editor) { \
                                        editor.setFontSize(editor.getFontSize() + 2); \
                                    }, \
                                    readOnly: false, \
                                },  \
                                { \
                                    name: 'zoomout', \
                                    bindKey: {win: 'Ctrl-Alt-D'}, \
                                    exec: function(editor) { \
                                        editor.setFontSize(editor.getFontSize() - 2); \
                                    }, \
                                    readOnly: false, \
                                } \
                            ] \
                        ); \
                        \
                        editor.on('gutterclick', function(e) { \
                            showEditorError(editor, 'Breakpoints are not available for now.'); \
                        }); \
                        var langTools = ace.require('ace/ext/language_tools');  \
                        \
                        langTools.setCompleters([myCompleter]); \
                        \
                        editor.setOptions({ \
                            enableBasicAutocompletion: true, \
                            enableSnippets: true, \
                            enableLiveAutocompletion: true \
                        });"
    );

    return app;
}


int main(int argc, char **argv)
{
    scheduledTask();

    try 
    {
        WServer server(argc, argv, WTHTTP_CONFIGURATION);

        HelpSection helpSection;

        server.addResource(&helpSection, "/stray68K/help");

        server.addEntryPoint(EntryPointType::Application,    &createApplication, "/stray68K", "/template/imgs/favicon.png");
        
        server.run();

    } 
    catch (Wt::WServer::Exception& e) 
    {
        std::cerr << e.what() << std::endl;
    } 
    catch (std::exception &e) 
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}