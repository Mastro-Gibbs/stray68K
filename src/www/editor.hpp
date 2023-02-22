#ifndef __editor__68000__
#define __editor__68000__


#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTextArea.h>
#include <Wt/WSignal.h>


using namespace Wt;
using namespace std;


class Editor : public WTemplate
{
    public:
        Editor();

        std::string getText();

        void disable(bool status);

        JSignal<std::string>  jsEditorContentRequestSignal;
        void                  onContentRequest(std::string result);

        JSignal<std::string>  jsEditorInputSignal;

        Signal<> onTextChange;
        Signal<> onTextCome;

    private:
        std::string self;
};


#endif // __editor__68000__