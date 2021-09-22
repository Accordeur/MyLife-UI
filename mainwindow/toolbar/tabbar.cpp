#include "tabbar.h"

TabBar::TabBar(QWidget *parent)
{
    setMovable(true);
    setTabsClosable(true);
    setExpanding(false);

    addTab("(1) Outline");
    addTab("(1) To-DO");
    addTab("(1) New Workspace");

    addTab("+");
}
