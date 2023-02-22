#include "memory.hpp"

#include <algorithm>

MemoryView::MemoryView()
    : bitfield(nullptr),
      addresses(nullptr),
      go(nullptr),
      currOffSet(nullptr),
      from(nullptr),
      offset_(0),
      emulator(nullptr),
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

void MemoryView::setEmulator(struct EmulationMachine* _emulator)
{
    emulator = _emulator;
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
        string s = ss.str();
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        addresses->setText(addresses->text() + format32BitReg(s));
    }

    const unsigned char* block = read_chunk(emulator, offset_, offset_ + (16*20));

    for (size_t i = 0, j = 0; i < (16*20); i++, j++)
    {
        stringstream ss;
        ss << hex << ((unsigned int) block[i]);

        string s = ss.str();
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        
        if (j == 16) 
        {
            renderChunck(block, i-16);

            j = 0;
        }

        bitfield->setText(bitfield->text() + format1ByteReg(s) + " ");
    }

    renderChunck(block, 15*20);
}


void MemoryView::update(unsigned int _from)
{
    unsigned int address = (_from != 0) ? _from : offset_;

    if (address != 0 && emulator != nullptr)
    {   
        offset_ = address;

        stringstream ss;
        ss << hex << address;
        from->setText(ss.str());
        addresses->setText("");
        bitfield->setText("");

        for (size_t i = 0, j = 0; i < 20; i++, j += 16)
        {
            stringstream ss;
            ss << hex << (address + j) << "\n";
            string s = ss.str();
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            addresses->setText(addresses->text() + format32BitReg(s));
        }

        const unsigned char* block = read_chunk(emulator, address, address + (16*20));

        for (size_t i = 0, j = 0; i < (16*20); i++, j++)
        {
            stringstream ss;
            ss << hex << ((unsigned int) block[i]);

            string s = ss.str();
            transform(s.begin(), s.end(), s.begin(), ::toupper);
            
            if (j == 16) 
            {
                renderChunck(block, i-16);

                j = 0;
            }

            bitfield->setText(bitfield->text() + format1ByteReg(s) + " ");
        }

        renderChunck(block, 15*20);
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


void MemoryView::renderChunck(const unsigned char* block, unsigned int chunk_begin)
{
    bitfield->setText(bitfield->text() + "  ");

    char c[33];

    for (size_t _i = chunk_begin, _j = 0; _j < 32; ++_i, ++_j )
        if (block[_i] < 0x20 || block[_i] > 0x7E)
        {
            c[_j++] = '-';
            c[_j]   = ' ';
        }    
        else 
        {
            c[_j++] = (char) block[_i];
            c[_j]   = ' ';   
        }
    
    c[32] = '\0';

    bitfield->setText(bitfield->text() + string(c) + "\n");
}