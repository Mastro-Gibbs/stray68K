#ifndef COMPLETERITEM_H
#define COMPLETERITEM_H

#include <QListWidgetItem>
#include <QObject>

#include "completerenums.h"

class CompleterItem : public QListWidgetItem
{
public:
    CompleterItem();

    virtual ~CompleterItem();

    SuggestionType getSType() const;
    void setSType(const SuggestionType t);

private:
    SuggestionType stype;
};

#endif // COMPLETERITEM_H
