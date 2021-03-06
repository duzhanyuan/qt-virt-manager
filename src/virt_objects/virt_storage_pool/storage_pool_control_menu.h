#ifndef STORAGE_POOL_CONTROL_MENU_H
#define STORAGE_POOL_CONTROL_MENU_H

#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QVariantMap>
#include "delete_pool_menu.h"

class StoragePoolControlMenu : public QMenu
{
    Q_OBJECT
public:
    explicit StoragePoolControlMenu(
            QWidget     *parent = Q_NULLPTR,
            QVariantMap  params = QVariantMap(),
            bool         state  = false);

signals:
    void            execMethod(const Act_Param&);

private:
    bool            autoReloadState;
    bool            active, autostart, persistent;
    QAction        *start = Q_NULLPTR;
    QAction        *destroy = Q_NULLPTR;
    QAction        *undefine = Q_NULLPTR;
    QAction        *autoStart = Q_NULLPTR;
    Delete_Pool_Menu
                    *delete_Menu = Q_NULLPTR;
    QAction        *delete_Action = Q_NULLPTR;
    QAction        *getXMLDesc = Q_NULLPTR;
    QAction        *overview = Q_NULLPTR;
    QAction        *reload = Q_NULLPTR;

private slots:
    void            emitExecMethod(QAction*);
};

#endif // STORAGE_POOL_CONTROL_MENU_H
