#ifndef __header__68000__
#define __header__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WAnchor.h>


using namespace Wt;
using namespace std;



class Header : public WContainerWidget
{
    public:
        Header();

    private:
        WTemplate*   template_;
        WPushButton* title;

        void openGitHubProjectPage();
}; 


#endif // __header__68000__