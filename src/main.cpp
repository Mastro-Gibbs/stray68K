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
    return std::make_unique<App>(env);
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