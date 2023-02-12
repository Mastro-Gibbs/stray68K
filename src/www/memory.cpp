#include "memory.hpp"

#include <algorithm>

MemoryView::MemoryView()
    : bitfield(nullptr),
      addresses(nullptr),
      go(nullptr),
      currOffSet(nullptr),
      from(nullptr),
      offset_(0),
      WTemplate(tr("memory-msg"))
{

}


void MemoryView::setUpMemory()
{
    auto bfield = make_unique<WTextArea>();
    bfield->setStyleClass("bitfield");

    auto addrs = make_unique<WTextArea>();
    addrs->setStyleClass("addresses");

    auto f_le = make_unique<WLineEdit>();
    f_le->setStyleClass("from");
    f_le->setMaxLength(8);
    f_le->setInputMask("HHHHHHHH");

    auto go_btn = make_unique<WPushButton>();
    go_btn->setText("Fetch");
    go_btn->setStyleClass("fetch-btn");

    bitfield   = bindWidget("bitfield",  move(bfield));
    addresses  = bindWidget("addresses", move(addrs));
    from       = bindWidget("from",      move(f_le));
    go         = bindWidget("go",        move(go_btn));

    bitfield->setText("");
    bitfield->setReadOnly(true);

    addresses->setText("");
    addresses->setReadOnly(true);

    go->clicked().connect(this, &MemoryView::fetchBlock);
    enableFetch(false);
}

string format32BitReg(string s)
{
    int len = s.length();
    int padding = 8 - len;
    for (int i = 0; i <= padding; ++i) {
        s.insert(0, "0");
    }

    return string(s);
}

string format1ByteReg(string s)
{
    if (s.length() < 2) 
        s.insert(0, "0");

    return string(s);
}


void MemoryView::fetchBlock()
{
    addresses->setText("");
    bitfield->setText("");

    string _s = from->text().toUTF8();
    
    offset_ = stoi(_s, nullptr, 16);

    for (size_t i = 0, j = 0; i < 20; i++, j += 16)
    {
        stringstream ss;
        ss << hex << (offset_ + j) << "\n";
        addresses->setText(addresses->text() + format32BitReg(ss.str()));
    }

    const unsigned char* block = read_chunk(offset_, offset_ + (16*20));

    for (size_t i = 0, j = 0; i < (16*20); i++, j++)
    {
        stringstream ss;
        ss << hex << ((unsigned int) block[i]);

        string s = ss.str();
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        
        if (j == 16) 
        {
            bitfield->setText(bitfield->text() + "\n");
            j = 0;
        }

        bitfield->setText(bitfield->text() + format1ByteReg(s) + " ");
    }
}


void MemoryView::update()
{
    if (offset_ != 0)
    {
        addresses->setText("");
        bitfield->setText("");

        for (size_t i = 0, j = 0; i < 20; i++, j += 16)
        {
            stringstream ss;
            ss << hex << (offset_ + j) << "\n";
            addresses->setText(addresses->text() + format32BitReg(ss.str()));
        }

        const unsigned char* block = read_chunk(offset_, offset_ + (16*20));

        for (size_t i = 0, j = 0; i < (16*20); i++, j++)
        {
            stringstream ss;
            ss << hex << ((unsigned int) block[i]);

            string s = ss.str();
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            
            if (j == 16) 
            {
                bitfield->setText(bitfield->text() + "\n");
                j = 0;
            }

            bitfield->setText(bitfield->text() + format1ByteReg(s) + " ");
        }
    }
}


void MemoryView::enableFetch(bool status)
{
    go->setDisabled(!status);
    
    if (status)
        go->setStyleClass("fetch-btn");
    else
        go->setStyleClass("fetch-btn-disabled");
}