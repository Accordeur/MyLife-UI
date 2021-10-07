#ifndef VIEWTREENODE_H
#define VIEWTREENODE_H
#include <QCoreApplication>

#include "config_node_interface.h"

#define VIEW_TREE_NODE "ViewTree"

class ViewTreeNode : public ConfigNodeInterface
{
    Q_DECLARE_TR_FUNCTIONS(ViewTreeNode);
public:
    ViewTreeNode(const QDomNode& node);
    virtual bool parse() override;
};

#endif // VIEWTREENODE_H
