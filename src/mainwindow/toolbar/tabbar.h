#ifndef TABBAR_H
#define TABBAR_H

#include <QTabBar>
#include "configure/tab_bar_node.h"

class SetUpWorkspace;
class QPushButton;
class QMenu;

class TabBar : public QTabBar
{
    Q_OBJECT
public:
    TabBar(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    void tabIsTooLong(bool flag = false);

public slots:
    void addNewTab();

private slots:
    void closeTab(int index);

private:
    void setupMenu();
    void paintAddTagButton();
    void showSetupWorkspace();

    QPushButton* pushButton_Add_Tag;
    SetUpWorkspace* setupWorkspace;
    QMenu* menu;
    QVector<TabBarNode::TabBarTable> tabBarConfig;
};

#endif // TABBAR_H
