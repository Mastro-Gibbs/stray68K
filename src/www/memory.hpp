#ifndef __memory__68000__
#define __memory__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTextArea.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLabel.h>


using namespace Wt;
using namespace std;


class MemoryView : public WTemplate
{
    public: 
        MemoryView();

        void setUpMemory();

    private:
        WLabel*      currOffSet;
        WLineEdit*   from;
        WPushButton* go;

        WTextArea* addresses;
        WTextArea* bitfield;

};



#endif // __memory__68000__