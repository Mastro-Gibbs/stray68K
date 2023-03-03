#include "register.hpp"


#define INVALID_MNEMONIC  "invalid"
#define REG_DEF_VAL_2byte "0000"
#define REG_DEF_VAL_4byte "00000000"
#define REG_DEF_VAL_16BIT "0000000000000000"


string format32BitReg(string* s)
{
    int len = s->length();
    int padding = 8 - len;
    for (int i = 0; i < padding; ++i) {
        s->insert(0, "0");
    }

    return string(*s);
}


string format16BitReg(string* s)
{
    int len = s->length();
    int padding = 16 - len;
    for (int i = 0; i < padding; ++i) {
        s->insert(0, "0");
    }

    return string(*s);
}

string format2ByteReg(string* s)
{
    int len = s->length();
    int padding = 4 - len;
    for (int i = 0; i < padding; ++i) {
        s->insert(0, "0");
    }

    return string(*s);
}




RegisterRender::RegisterRender()
    : template_(nullptr),
    WContainerWidget()
{
    WApplication* instance = WApplication::instance();
    
    instance->messageResourceBundle().use("template/xmls/register");
    instance->useStyleSheet("template/css/register.css");

    template_ = this->addWidget(make_unique<WTemplate>(tr("register-msg")));

    template_->bindWidget("break", make_unique<WBreak>());

    init_data_reg();
    init_addr_reg();
    init_other_regs();
    init_others();
    
}


void RegisterRender::clear()
{
    for (unsigned int i = 0; i < 8; i++)
    {
        data_reg[i]->setText(REG_DEF_VAL_4byte);
        addr_reg[i]->setText(REG_DEF_VAL_4byte);
    }

    setUSP(REG_DEF_VAL_4byte);
    setSSP(REG_DEF_VAL_4byte);
    setPC (REG_DEF_VAL_4byte);
    setCCR(0);

    setMnemonic("", false);
    setHCode("", false);
    setBCode(0, false);

    setTime(0, false);

    setFWB(REG_DEF_VAL_4byte);
    setLWB(REG_DEF_VAL_4byte);
    setHALT(REG_DEF_VAL_4byte);
}


void RegisterRender::init_data_reg()
{
    for (unsigned int i = 0; i < 8; i++)
    {
        auto reg = make_unique<WTextArea>();
        reg->setText(REG_DEF_VAL_4byte);
        reg->setStyleClass("register-data-8bit");
        reg->setReadOnly(true);

        string _id = "d" + to_string(i);

        data_reg[i] = template_->bindWidget(_id, move(reg));

        data_reg[i]->setId(_id);

        data_reg[i]->doJavaScript("\
            const textarea" + _id + " = document.getElementById('" + _id + "'); \
            const popup" + _id + " = document.getElementById('div-" + _id + "'); \
            \
            textarea" + _id + ".addEventListener('mouseover', function() { \
                popup" + _id + ".style.display = 'block'; \
                popup" + _id + ".innerHTML = parseInt(this.value, 16); \
            }); \
            \
            textarea" + _id + ".addEventListener('mouseout', function() { \
                popup" + _id + ".style.display = 'none'; \
            });\
        ");
    }
}


void RegisterRender::init_addr_reg()
{
    for (unsigned int i = 0; i < 8; i++)
    {
        auto reg = make_unique<WTextArea>();
        reg->setText(REG_DEF_VAL_4byte);
        reg->setStyleClass("register-data-8bit");
        reg->setReadOnly(true);

        string _id = "a" + to_string(i);

        addr_reg[i] = template_->bindWidget(_id, move(reg));

        addr_reg[i]->setId(_id);

        addr_reg[i]->doJavaScript("\
            const textarea" + _id + " = document.getElementById('" + _id + "'); \
            const popup" + _id + " = document.getElementById('div-" + _id + "'); \
            \
            textarea" + _id + ".addEventListener('mouseover', function() { \
                popup" + _id + ".style.display = 'block'; \
                popup" + _id + ".innerHTML = parseInt(this.value, 16); \
            }); \
            \
            textarea" + _id + ".addEventListener('mouseout', function() { \
                popup" + _id + ".style.display = 'none'; \
            });\
        ");
    }
}


void RegisterRender::init_other_regs()
{
    auto usp = make_unique<WTextArea>();
    usp->setText(REG_DEF_VAL_4byte);
    usp->setStyleClass("register-data-8bit");
    usp->setReadOnly(true);

    USP = template_->bindWidget("usp", move(usp));

    auto ssp = make_unique<WTextArea>();
    ssp->setText(REG_DEF_VAL_4byte);
    ssp->setStyleClass("register-data-8bit");
    ssp->setReadOnly(true);

    SSP = template_->bindWidget("ssp", move(ssp));

    auto pc = make_unique<WTextArea>();
    pc->setText(REG_DEF_VAL_4byte);
    pc->setStyleClass("register-data-8bit");
    pc->setReadOnly(true);

    PC = template_->bindWidget("pc", move(pc));

    auto ccr = make_unique<WTextArea>();
    ccr->setText(REG_DEF_VAL_16BIT);
    ccr->setStyleClass("register-data-16bit");
    ccr->setReadOnly(true);

    string _id = "ccr";

    CCR = template_->bindWidget(_id, move(ccr));

    CCR->setId(_id);

    CCR->doJavaScript("\
        const textarea" + _id + " = document.getElementById('" + _id + "'); \
        const popup" + _id + " = document.getElementById('div-" + _id + "'); \
        \
        textarea" + _id + ".addEventListener('mouseover', function() { \
            popup" + _id + ".style.display = 'block'; \
            popup" + _id + ".innerHTML = 'X:' + this.value.charAt(11) + ' N:' + this.value.charAt(12) + ' Z:' + this.value.charAt(13) + ' V:' + this.value.charAt(14) + ' C:' + this.value.charAt(15);\
        }); \
        \
        textarea" + _id + ".addEventListener('mouseout', function() { \
            popup" + _id + ".style.display = 'none'; \
        });\
    ");
}

void RegisterRender::init_others()
{
    auto mnem = make_unique<WTextArea>();
    mnem->setText(INVALID_MNEMONIC);
    mnem->setStyleClass("register-data-8bit");
    mnem->setReadOnly(true);

    mnemonic = template_->bindWidget("mnem", move(mnem));

    auto hcode = make_unique<WTextArea>();
    hcode->setText(REG_DEF_VAL_2byte);
    hcode->setStyleClass("register-data-2byte");
    hcode->setReadOnly(true);

    code = template_->bindWidget("hcode", move(hcode));

    auto bcode = make_unique<WTextArea>();
    bcode->setText(REG_DEF_VAL_16BIT);
    bcode->setStyleClass("register-data-16bit");
    bcode->setReadOnly(true);

    _16bit_code = template_->bindWidget("bcode", move(bcode));


    auto time_ = make_unique<WTextArea>();
    time_->setText(REG_DEF_VAL_16BIT);
    time_->setStyleClass("register-data-16bit");
    time_->setReadOnly(true);

    time = template_->bindWidget("time", move(time_));

    auto fwb = make_unique<WTextArea>();
    fwb->setText(REG_DEF_VAL_4byte);
    fwb->setStyleClass("register-data-8bit");
    fwb->setReadOnly(true);

    FWB = template_->bindWidget("fwb", move(fwb));

    auto lwb = make_unique<WTextArea>();
    lwb->setText(REG_DEF_VAL_4byte);
    lwb->setStyleClass("register-data-8bit");
    lwb->setReadOnly(true);

    LWB = template_->bindWidget("lwb", move(lwb));

    auto halt = make_unique<WTextArea>();
    halt->setText(REG_DEF_VAL_4byte);
    halt->setStyleClass("register-data-8bit");
    halt->setReadOnly(true);

    HALT = template_->bindWidget("halt", move(halt));
}

#include <algorithm>
#include <bitset>


void RegisterRender::setTime(unsigned int val, bool valid)
{
    if (!valid)
        time->setText(REG_DEF_VAL_16BIT);
    else
    {
        unsigned int _val = val;
        _val /= 1000;

        string result = to_string(_val);

        time->setText(format16BitReg(&result));
    }
}

void RegisterRender::setUSP(string result)
{
    USP->setText(format32BitReg(&result));
}


void RegisterRender::setSSP(string result)
{
    SSP->setText(format32BitReg(&result));
}


void RegisterRender::setPC(string result)
{
    PC->setText(format32BitReg(&result));
}


void RegisterRender::setCCR(unsigned int val)
{
    string bits = bitset<16>(val).to_string();

    CCR->setText(format16BitReg(&bits));

    CCR->doJavaScript(" \
        var textarea" + CCR->id() + " = document.getElementById('" + CCR->id() + "'); \
        var popup" + CCR->id() + " = document.getElementById('div-" + CCR->id() + "'); \
        \
        popup" + CCR->id() + ".innerHTML = 'X:' + textarea" + CCR->id() + ".value.charAt(11) + ' N:' + textarea" + CCR->id() + ".value.charAt(12) + ' Z:' + textarea" + CCR->id() + ".value.charAt(13) + ' V:' + textarea" + CCR->id() + ".value.charAt(14) + ' C:' + textarea" + CCR->id() + ".value.charAt(15);\
    ");
}




void RegisterRender::setMnemonic(string mnem, bool valid)
{
    if (!valid)
        mnemonic->setText(INVALID_MNEMONIC);
    else
        mnemonic->setText(mnem);
}


void RegisterRender::setHCode(string val, bool valid)
{
    if (!valid)
        code->setText(REG_DEF_VAL_2byte);
    else
        code->setText(format2ByteReg(&val));
    
}


void RegisterRender::setBCode(int val, bool valid)
{
    if (!valid)
        _16bit_code->setText(REG_DEF_VAL_16BIT);
    else
    {
        string bits = bitset<16>(val).to_string();

        _16bit_code->setText(format16BitReg(&bits));
    }
}


void RegisterRender::setDataReg(unsigned int index, string result)
{
    auto reg = data_reg[index];

    reg->setText(format32BitReg(&result));

    reg->doJavaScript(" \
        var textarea" + reg->id() + " = document.getElementById('" + reg->id() + "'); \
        var popup" + reg->id() + " = document.getElementById('div-" + reg->id() + "'); \
        \
        popup" + reg->id() + ".innerHTML = parseInt(textarea" + reg->id() + ".value, 16); \
    ");
}

void RegisterRender::setAddrReg(unsigned int index, string result)
{
    auto reg = addr_reg[index];

    reg->setText(format32BitReg(&result));

    reg->doJavaScript(" \
        var textarea" + reg->id() + " = document.getElementById('" + reg->id() + "'); \
        var popup" + reg->id() + " = document.getElementById('div-" + reg->id() + "'); \
        \
        popup" + reg->id() + ".innerHTML = parseInt(textarea" + reg->id() + ".value, 16); \
    ");
}

void RegisterRender::setFWB(string result)
{
    FWB->setText(format32BitReg(&result));
}

void RegisterRender::setLWB(string result)
{
    LWB->setText(format32BitReg(&result));
}

void RegisterRender::setHALT(string result)
{
    HALT->setText(format32BitReg(&result));
}


void RegisterRender::update(const char* map)
{
    if (map != NULL)
    {
        try
        {
            string _json = string(map);

            json_map json{ json_data{ _json } }; 

            for (size_t i = 0; i < 8; i++)
            {
                setDataReg(i, string(json["CPU"]["D" + to_string(i)]));
                setAddrReg(i, string(json["CPU"]["A" + to_string(i)]));
            }

            setUSP(string(json["CPU"]["US"]));
            setSSP(string(json["CPU"]["SS"]));
            setPC (string(json["CPU"]["PC"]));
            setCCR(stoi(string(json["CPU"]["SR"]), nullptr, 16));

            setMnemonic(string(json["OP"]["MNEMONIC"]));
            setHCode(string(json["OP"]["CODE"]));
            setBCode(stoi(string(json["OP"]["CODE"]), nullptr, 16));
            setTime((unsigned long) json["TIME"]);

            setFWB(string(json["RAM"]["BEGIN"]));
            setLWB(string(json["RAM"]["END"]));
            setHALT(string(json["RAM"]["HALT"]));
        }
        catch (boost::bad_get& e) { }
        catch (runtime_error& e)  { }
    }

}
