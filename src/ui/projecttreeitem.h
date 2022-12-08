#ifndef PROJECTTREEITEM_H
#define PROJECTTREEITEM_H

#include <QPushButton>
#include <QMouseEvent>

class ProjectTreeItem : public QPushButton
{
    Q_OBJECT

public:
    explicit ProjectTreeItem( QWidget *parent = 0, QString path = QString() );

    inline const QString &getPath() const { return path; }

private slots:
    void mousePressEvent( QMouseEvent *e );

signals:
    void rightClicked();

    void leftClicked();

private:
    QString path;
};

#endif // PROJECTTREEITEM_H
