#include "tabbar.h"
#include <QPushButton>
#include <QDebug>
#include <QMenu>
#include <QContextMenuEvent>
#include <glog/logging.h>
#include "configure/config.h"
#include "setup_workspace.h"

TabBar::TabBar(QWidget *parent) : QTabBar(parent),
    pushButton_Add_Tag(new QPushButton("+", this)),
    setupWorkspace(new SetUpWorkspace(this)),
    menu(new QMenu(this)),
    tabBarConfig(Config::getConfig()->getTabBarNode()->getTabBarConfig()) {
    setMovable(true);
    setTabsClosable(true);
    setExpanding(false);
    setElideMode(Qt::ElideRight);
    setDrawBase(false);

    setupMenu();

    QObject::connect(pushButton_Add_Tag, SIGNAL(clicked()), this, SLOT(addNewTab()));
    QObject::connect(this, SIGNAL(tabMoved(int,int)), this, SLOT(onTabMoved(int,int)));

    for(const auto& b : qAsConst(tabBarConfig)) {
        addTab(b.name);
    }
}

void TabBar::saveConfig() {
    for(int i = 0; i < tabBarConfig.length(); i++) {
        tabBarConfig[i].position = i;
    }
    Config::getConfig()->getTabBarNode()->updateTableBarTable(tabBarConfig);
}

void TabBar::addNewTab() {
    int index = addTab("(1)New Workspace");

    setCurrentIndex(index);
    TabBarNode::TabBarTable b;
    b.name = tabText(index);
    tabBarConfig.push_back(b);
}

void TabBar::closeTab(int index) {
    tabBarConfig.removeAt(index);
    removeTab(index);
}

void TabBar::setupMenu()
{
    QAction* newWorkspace = new QAction(tr("New workspace"), this);
    QAction* pinTab = new QAction(tr("Pin this Tab"), this);
    QAction* setAsDefault = new QAction(tr("Set as default for this Tab"), this);
    QAction* lockDefault = new QAction(tr("Lock default in this Tab"), this);
    QAction* restoreDefault = new QAction(tr("Restore default for this Tab"), this);
    QAction* openInNewWindow = new QAction(tr("Open in new window"), this);
    QAction* closeTab = new QAction(tr("Close Tab"), this);
    QAction* undoCloseTab = new QAction(tr("Undo close Tab"), this);
    QAction* assignHotkey = new QAction(tr("Assign hotkey..."), this);

    QMenu* assignIcon = new QMenu(tr("Assign icon"), this);
    QAction* currentViewIcon = new QAction(tr("Current view icon"), this);
    QAction* customIcon = new QAction(tr("Custom icon..."), this);
    QAction* noIcon = new QAction(tr("No Icon"), this);

    QAction* setupWorkspace = new QAction(tr("Set up workspace..."), this);


    lockDefault->setCheckable(true);
    currentViewIcon->setCheckable(true);
    customIcon->setCheckable(true);
    noIcon->setCheckable(true);

    menu->addAction(newWorkspace);
    menu->addAction(pinTab);
    menu->addSeparator();
    menu->addAction(setAsDefault);
    menu->addAction(lockDefault);
    menu->addAction(restoreDefault);
    menu->addSeparator();
    menu->addAction(openInNewWindow);
    menu->addSeparator();
    menu->addAction(closeTab);
    menu->addAction(undoCloseTab);
    menu->addSeparator();
    menu->addAction(assignHotkey);

    assignIcon->addAction(currentViewIcon);
    assignIcon->addAction(customIcon);
    assignIcon->addSeparator();
    assignIcon->addAction(noIcon);

    menu->addMenu(assignIcon);
    menu->addSeparator();
    menu->addAction(setupWorkspace);

    connect(setupWorkspace, SIGNAL(triggered()), this, SLOT(showSetupWorkspace()));
}

void TabBar::paintEvent(QPaintEvent *event) {
    paintAddTagButton();
    return QTabBar::paintEvent(event);
}

void TabBar::mouseDoubleClickEvent(QMouseEvent *event)
{

    showSetupWorkspace();
    return QTabBar::mouseDoubleClickEvent(event);
}

void TabBar::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
    return QTabBar::contextMenuEvent(event);
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

void TabBar::showSetupWorkspace() {
    setupWorkspace->setdata(tabBarConfig[currentIndex()].name,
            tabBarConfig[currentIndex()].showCounter,
            tabBarConfig[currentIndex()].syncSelection,
            tabBarConfig[currentIndex()].syncZoom);

    QRect rect = tabRect(currentIndex());
    QPoint globalPoint = mapToGlobal(QPoint(rect.x(), rect.y()));

    QPoint centerPoint = QPoint(globalPoint.x()+rect.width()/2, globalPoint.y() + rect.height());

    QPoint showPoint = QPoint(centerPoint.x() - setupWorkspace->width()/2, centerPoint.y());
    setupWorkspace->move(showPoint);
    setupWorkspace->show();
}

void TabBar::onTabMoved(int form, int to)
{
    tabBarConfig.swapItemsAt(form, to);
}
