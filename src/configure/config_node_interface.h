#ifndef CONFIG_NODE_INTERFACE_H
#define CONFIG_NODE_INTERFACE_H
#include <QDomNode>

class ConfigNodeInterface
{
public:
    ConfigNodeInterface(const QDomNode& node);
    ConfigNodeInterface(const ConfigNodeInterface&) = delete;
    ConfigNodeInterface& operator=(const ConfigNodeInterface&) = delete;
    virtual bool parse() = 0;
    virtual bool updateDom() = 0;

    void setValid(bool valid);
    bool isValid() const;
    bool hasChanged() {return changed;}
    virtual ~ConfigNodeInterface(){};

protected:
    void change(bool flag);
    QDomNode domNode;

private:
    bool valid = false;
    bool changed = false;
};

#endif // CONFIG_NODE_INTERFACE_H
