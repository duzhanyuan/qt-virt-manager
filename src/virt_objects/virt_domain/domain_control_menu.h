#ifndef DOMAIN_CONTROL_MENU_H
#define DOMAIN_CONTROL_MENU_H

#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QStringList>

class DomainControlMenu : public QMenu
{
    Q_OBJECT
public:
    explicit DomainControlMenu(QWidget *parent = 0, QStringList params = QStringList(), bool state = false);
    ~DomainControlMenu();

signals:
    void execMethod(const QStringList&);

private:
    bool            autoReloadState;
    QAction        *start;
    QAction        *pause;
    QAction        *destroy;
    QAction        *reset;
    QAction        *reboot;
    QAction        *shutdown;
    QAction        *save;
    QAction        *undefine;
    QAction        *autoStart;
    QAction        *getXMLDesc;
    QAction        *reload;
    QStringList     parameters;

private slots:
    void emitExecMethod(QAction*);

};

#endif // DOMAIN_CONTROL_MENU_H