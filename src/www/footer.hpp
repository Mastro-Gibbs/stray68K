#ifndef __footer__68000__
#define __footer__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WAnchor.h>
#include <Wt/WTextArea.h>


using namespace Wt;
using namespace std;



class Footer : public WContainerWidget
{
    public:
        Footer();

    private:
        WTemplate*   template_;
}; 


#endif // __footer__68000__