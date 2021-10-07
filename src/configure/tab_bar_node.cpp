#include "tab_bar_node.h"
#include <QDebug>
#include <algorithm>

#define TAB_BAR "TabBar"
#define TAB_BAR_ID "id"
#define TAB_BAR_POSITION "position"
#define TAB_BAR_PIN_TAB "pinTab"
#define TAB_BAR_SHOW_VIEW "showView"
#define TAB_BAR_IS_DEFAULT "isDefault"
#define TAB_BAR_LOCK_DEFAULT "lockDefault"
#define TAB_BAR_ICON "icon"
#define TAB_BAR_NAME "name"
#define TAB_BAR_CURRENT_VIEW "currentView"
#define TAB_BAR_DEFAULT_VIEW "defaultView"
#define TAB_BAR_HOTKEY "hotkey"

TabBarNode::TabBarNode(const QDomNode& node) : ConfigNodeInterface(node)
{

}

bool TabBarNode::parse()
{
    if(domNode.nodeName() != TAB_BAR_NODE && !domNode.isElement()) {
        qDebug() << tr("Can not parse Node, because the root node must is ") << TAB_BAR_NODE;
        setValid(false);
        return false;
    }

    QDomElement tabBarElement = domNode.toElement();
    QDomNodeList nodeList = tabBarElement.elementsByTagName(TAB_BAR);
    for(int i = 0; i < nodeList.size(); i++) {
        QDomElement tab = nodeList.at(i).toElement();
        QDomNamedNodeMap attrMap =  tab.attributes();
        TabBarTable table;
        table.id = attrMap.namedItem(TAB_BAR_ID).nodeValue().toInt();
        table.position = attrMap.namedItem(TAB_BAR_POSITION).nodeValue().toInt();
        table.pinTab = attrMap.namedItem(TAB_BAR_PIN_TAB).nodeValue() == "true" ? true : false;
        table.showView = attrMap.namedItem(TAB_BAR_SHOW_VIEW).nodeValue() == "true" ? true : false;
        table.isDefault = attrMap.namedItem(TAB_BAR_IS_DEFAULT).nodeValue() == "true" ? true : false;
        table.lockDefault = attrMap.namedItem(TAB_BAR_LOCK_DEFAULT).nodeValue() == "true" ? true : false;
        table.iconPath = attrMap.namedItem(TAB_BAR_ICON).nodeValue();
        table.name = attrMap.namedItem(TAB_BAR_NAME).nodeValue();
        table.currentView = attrMap.namedItem(TAB_BAR_CURRENT_VIEW).nodeValue().toInt();
        table.defaultView = attrMap.namedItem(TAB_BAR_DEFAULT_VIEW).nodeValue().toInt();
        table.hotkey = attrMap.namedItem(TAB_BAR_HOTKEY).nodeValue();

        config.push_back(table);
    }

    setValid(true);
    return true;
}

bool TabBarNode::addTabBarTable(TabBarTable &tab)
{
    if(tab.id != -1) {
        qDebug() << tr("It is forbidden to add existing nodes repeatedly.");
        return false;
    }
    tab.id = findUnusedID();
    config.push_back(tab);
    return true;
}

int TabBarNode::findUnusedID() const
{
    int result = 0;
    while(true) {
        TabBarTable t;
        t.id = result;
        auto findIter = std::find(config.cbegin(), config.cend(), t);
        if(findIter == config.cend()) {
            return result;
        }
        result++;
    }
}
