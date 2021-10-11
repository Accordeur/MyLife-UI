#ifndef TABBARNODE_H
#define TABBARNODE_H
#include <QVector>

#include "config_node_interface.h"

#define TAB_BAR_NODE "TabBarTable"


class TabBarNode : public ConfigNodeInterface
{
public:
    struct TabBarTable {
    private:
        int32_t id = -1;
    public:
        int32_t position = -1;
        bool pinTab = false;
        bool showView = false;
        bool isDefault = false;
        bool lockDefault = false;
        QString iconPath;
        QString name;
        int32_t currentView = 0;
        int32_t defaultView = 0;
        QString hotkey;

        friend constexpr inline bool operator==(const TabBarTable& t1,const TabBarTable& t2) noexcept;
        friend constexpr inline bool operator!=(const TabBarTable& t1,const TabBarTable& t2) noexcept;

        friend class TabBarNode;
    };

    TabBarNode(const QDomNode& node);
    virtual bool parse() override;
    virtual bool updateDom() override;
    bool addTabBarTable(TabBarTable& tab);
    bool removeTabBarTable(TabBarTable& tab);
    bool updateTableBarTable(TabBarTable& tab);
    QVector<TabBarTable> getTabBarConfig() const;
private:
    int findUnusedID() const;

    QVector<TabBarTable> tabBarVec;
};

constexpr inline bool operator==(const TabBarNode::TabBarTable& t1,const TabBarNode::TabBarTable& t2) noexcept {
    if(t1.id == -1 && t2.id == -1) {
        return t1.position == t2.position && t1.pinTab == t2.pinTab &&
                t1.showView == t2.showView && t1.isDefault == t2.isDefault &&
                t1.lockDefault == t2.isDefault && t1.iconPath == t2.iconPath &&
                t1.name == t2.name && t1.currentView == t2.currentView &&
                t1.defaultView == t2.defaultView && t1.hotkey == t2.hotkey;
    }
    return t1.id == t2.id;
}

constexpr inline bool operator!=(const TabBarNode::TabBarTable& t1,const TabBarNode::TabBarTable& t2) noexcept {
    return !(t1 == t2);
}
#endif // TABBARNODE_H
