#include "completeritem.h"

CompleterItem::CompleterItem() : QListWidgetItem()
{}


CompleterItem::~CompleterItem() {}


SuggestionType CompleterItem::getSType() const
{
    return this->stype;
}

void CompleterItem::setSType(const SuggestionType t)
{
    this->stype = t;
}

