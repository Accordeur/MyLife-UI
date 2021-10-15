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
    void saveConfig();

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
    void showSetupWorkspace();
    void onTabMoved(int form, int to);

private:
    void setupMenu();
    void paintAddTagButton();


    QPushButton* pushButton_Add_Tag;
    SetUpWorkspace* setupWorkspace;
    QMenu* menu;
    QVector<TabBarNode::TabBarTable> tabBarConfig;
};

#endif // TABBAR_H
