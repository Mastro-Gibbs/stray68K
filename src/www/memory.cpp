#include "memory.hpp"


MemoryView::MemoryView()
    : bitfield(nullptr),
      addresses(nullptr),
      go(nullptr),
      currOffSet(nullptr),
      from(nullptr),
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

    go->clicked().connect(this, [=]{
        string s = from->text().toUTF8();
        addresses->setText(s);
    });
}