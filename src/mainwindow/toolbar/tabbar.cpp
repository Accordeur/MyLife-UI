#include "tabbar.h"
#include <QPushButton>
#include <QDebug>
#include "configure/config.h"

TabBar::TabBar(QWidget *parent) : QTabBar(parent),
    pushButton_Add_Tag(new QPushButton("+", this)), tabBarConfig(Config::getConfig()->getTabBarNode()->getTabBarConfig()) {
    setMovable(true);
    setTabsClosable(true);
    setExpanding(false);
    setElideMode(Qt::ElideRight);
    setDrawBase(false);

    //addTab("(1) Outline");
    //addTab("(1) To-DO");
    //addTab("(1) New Workspace");

    QObject::connect(pushButton_Add_Tag, SIGNAL(clicked()), this, SLOT(addNewTab()));

    for(const auto& b : tabBarConfig) {
        addTab(b.name);
    }
}

void TabBar::addNewTab() {
    int index = addTab("(1)New Workspace");
    setCurrentIndex(index);
}

void TabBar::closeTab(int index) {

    removeTab(index);
}

void TabBar::paintEvent(QPaintEvent *event) {
    paintAddTagButton();
    return QTabBar::paintEvent(event);
}


void TabBar::paintAddTagButton() {
    int lastTagIndex = count()-1;

    if(lastTagIndex >= 0) {
        QRect lastTagRect = tabRect(lastTagIndex);
        if(geometry().x()+geometry().width() < lastTagRect.x()+lastTagRect.width() + pushButton_Add_Tag->geometry().width()) {
            pushButton_Add_Tag->setVisible(false);
            emit tabIsTooLong(true);
        } else {
            pushButton_Add_Tag->move(lastTagRect.x()+lastTagRect.width(), lastTagRect.y());
            pushButton_Add_Tag->setVisible(true);
            emit tabIsTooLong(false);
        }
    } else {
        pushButton_Add_Tag->move(geometry().x(), geometry().y());
        pushButton_Add_Tag->setVisible(true);
        emit tabIsTooLong(false);
    }
}
