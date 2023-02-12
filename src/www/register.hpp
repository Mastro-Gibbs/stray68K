#ifndef __register__68000__
#define __register__68000__

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WString.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WTextArea.h>
#include <Wt/WLabel.h>
#include <jeayeson/jeayeson.hpp>

using namespace Wt;
using namespace std;


class RegisterRender : public WContainerWidget
{
    public:
        RegisterRender();

        void update(const char* map);

        void clear();

    protected:
        void init_data_reg();
        void init_addr_reg();
        void init_other_regs();

    public:
        void setDataReg(unsigned int index, string result);
        void setAddrReg(unsigned int index, string result);

        void setMnemonic(string mnem, bool valid = true);
        void setHCode(string val, bool valid = true);
        void setBCode(int val, bool valid = true);

        void setUSP(string result);
        void setSSP(string result);
        void setPC (string result);
        void setCCR(unsigned int val);

        void setTime(unsigned int val, bool valid = true);

    private:
        WTemplate* template_;

        WTextArea* data_reg[8];
        WTextArea* addr_reg[8];

        WTextArea* USP;
        WTextArea* SSP;
        WTextArea* PC;
        WTextArea* CCR;

        WTextArea* mnemonic;
        WTextArea* code;
        WTextArea* _16bit_code;

        WTextArea* time;
};


#endif // __register__68000__