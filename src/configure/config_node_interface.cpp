#include "config_node_interface.h"

ConfigNodeInterface::ConfigNodeInterface(const QDomNode& node) : domNode(node)
{

}

void ConfigNodeInterface::change(bool flag)
{
    changed = flag;
}

void ConfigNodeInterface::setValid(bool valid)
{
    this->valid = valid;
}

bool ConfigNodeInterface::isValid() const
{
    return valid;
}
