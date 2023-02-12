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

        Signal<> text_changed;

        void setUpEditor();

        WString text_();

    private:
        WTextArea* editor_;
        WTextArea* line_counter;

        void enableTabEvent();

        void updateLines();

        void scroll();
};


#endif // __editor__68000__