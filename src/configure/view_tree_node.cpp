#include "view_tree_node.h"

ViewTreeNode::ViewTreeNode(const QDomNode &node) : ConfigNodeInterface(node)
{

}

bool ViewTreeNode::parse()
{
    return false;
}
