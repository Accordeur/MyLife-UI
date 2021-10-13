#include "tab_bar_node.h"
#include <algorithm>
#include <glog/logging.h>

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
        LOG(ERROR) << "Can not parse Node, because the root node must is " << TAB_BAR_NODE;
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

        QDomNode node = tab.firstChild();
        while(!node.isNull()) {
            QDomElement e = node.toElement();
            if(e.tagName() == TAB_BAR_ICON) {
                table.iconPath = e.text();
            } else if(e.tagName() == TAB_BAR_NAME) {
                table.name = e.text();
            } else if(e.tagName() == TAB_BAR_CURRENT_VIEW) {
                table.currentView = e.text().toInt();
            } else if(e.tagName() == TAB_BAR_DEFAULT_VIEW) {
                table.defaultView = e.text().toInt();
            } else if (e.tagName() == TAB_BAR_HOTKEY) {
                table.hotkey = e.text();
            } else {
                LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
            }
            node = node.nextSibling();
        }

        tabBarVec.push_back(table);
    }

    setValid(true);
    return true;
}

bool TabBarNode::updateDom()
{
    if(!hasChanged()) {
        return true;
    }
    //删除所有节点
    QDomElement tabBarElement = domNode.toElement();
    QDomNodeList list = tabBarElement.elementsByTagName(TAB_BAR);
    while(list.length()) {
        tabBarElement.removeChild(list.at(0));
    }

    //重新添加
    QDomDocument doc = domNode.ownerDocument();
    foreach(const auto& c, tabBarVec) {
        QDomElement element = doc.createElement(TAB_BAR);
        element.setAttribute(TAB_BAR_ID, c.id);
        element.setAttribute(TAB_BAR_POSITION, c.position);
        element.setAttribute(TAB_BAR_PIN_TAB, c.pinTab ? "true" : "false");
        element.setAttribute(TAB_BAR_SHOW_VIEW, c.showView ? "true" : "false");
        element.setAttribute(TAB_BAR_IS_DEFAULT, c.isDefault ? "true" : "false");
        element.setAttribute(TAB_BAR_LOCK_DEFAULT, c.lockDefault ? "true" : "false");

        QDomElement icon = doc.createElement(TAB_BAR_ICON);
        icon.appendChild(doc.createTextNode(c.iconPath));

        QDomElement name = doc.createElement(TAB_BAR_NAME);
        name.appendChild(doc.createTextNode(c.name));

        QDomElement currentView = doc.createElement(TAB_BAR_CURRENT_VIEW);
        currentView.appendChild(doc.createTextNode(QString::number(c.currentView)));

        QDomElement defaultView = doc.createElement(TAB_BAR_DEFAULT_VIEW);
        defaultView.appendChild(doc.createTextNode(QString::number(c.defaultView)));

        QDomElement hotKey = doc.createElement(TAB_BAR_HOTKEY);
        hotKey.appendChild(doc.createTextNode(c.hotkey));

        element.appendChild(icon);
        element.appendChild(name);
        element.appendChild(currentView);
        element.appendChild(defaultView);
        element.appendChild(hotKey);
        tabBarElement.appendChild(element);
    }
    change(false);
    return true;
}

bool TabBarNode::addTabBarTable(TabBarTable &tab)
{
    if(tab.id != -1) {
        LOG(ERROR) << "It is forbidden to add existing nodes repeatedly.";
        return false;
    }
    tab.id = findUnusedID();
    tabBarVec.push_back(tab);
    change(true);
    return true;
}

bool TabBarNode::removeTabBarTable(TabBarTable &tab)
{
    if(tab.id == -1) {
        LOG(ERROR) << "It is forbidden to delete an ID that does not exist.";
        return false;
    }
    if(tabBarVec.removeOne(tab)) {
        tab.id = -1;
        change(true);
        return true;
    }
    return false;
}

bool TabBarNode::updateTableBarTable(TabBarTable &tab)
{
    if(tab.id == -1) {
        LOG(ERROR) << "It is forbidden to update an ID that does not exist.";
        return false;
    }

    auto findIter = std::find(tabBarVec.begin(), tabBarVec.end(), tab);
    if(findIter != tabBarVec.end()) {
        *findIter = tab;
        change(true);
        return true;
    }

    LOG(ERROR) << "The node to be deleted was not found.";
    return false;
}

QVector<TabBarNode::TabBarTable> TabBarNode::getTabBarConfig() const
{
    return tabBarVec;
}

int TabBarNode::findUnusedID() const
{
    int result = 0;
    while(true) {
        TabBarTable t;
        t.id = result;
        auto findIter = std::find(tabBarVec.cbegin(), tabBarVec.cend(), t);
        if(findIter == tabBarVec.cend()) {
            return result;
        }
        result++;
    }
}
