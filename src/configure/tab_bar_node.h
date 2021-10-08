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
        int id = -1;
    public:
        int position = -1;
        bool pinTab = false;
        bool showView = false;
        bool isDefault = false;
        bool lockDefault = false;
        QString iconPath;
        QString name;
        int currentView = 0;
        int defaultView = 0;
        QString hotkey;

        bool operator==(const TabBarTable& node) const noexcept {
            if(id == -1) {
                return position == node.position && pinTab == node.pinTab &&
                        showView == node.showView && isDefault == node.isDefault &&
                        lockDefault == node.isDefault && iconPath == node.iconPath &&
                        name == node.name && currentView == node.currentView &&
                        defaultView == node.defaultView && hotkey == node.hotkey;
            }
            return id == node.id;
        }

        friend class TabBarNode;
    };

    TabBarNode(const QDomNode& node);
    virtual bool parse() override;
    virtual bool updateDom() override;
    bool addTabBarTable(TabBarTable& tab);
    bool removeTabBarTable(TabBarTable& tab);
    bool updateTableBarTable(TabBarTable& tab);
    QVector<TabBarTable> getConfig() const;
private:
    int findUnusedID() const;

    QVector<TabBarTable> config;
};

#endif // TABBARNODE_H
