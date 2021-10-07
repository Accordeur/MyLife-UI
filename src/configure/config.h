#ifndef CONFIG_H
#define CONFIG_H
#include <QCoreApplication>

#include <QDomDocument>


class TabBarNode;
class ViewTreeNode;

class Config
{
    Q_DECLARE_TR_FUNCTIONS(Config);
public:

    Config(){};
    explicit Config(const QString& file);
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
    Config(const Config&&) = delete;
    bool setConfigPath(const QString& file);
    bool parse();
    bool isValid() const;
    bool save();

    TabBarNode* getTabBarNode();
    ViewTreeNode* getViewTreeNode();

    ~Config();
private:
    bool parseTabBarNode(const QDomElement& root);
    bool parseViewTreeNode(const QDomElement& root);
    bool init();
    bool hasChanged();

    bool valid = false;
    QDomDocument doc;
    QString configPath;
    TabBarNode* tabBar = nullptr;
    ViewTreeNode* viewTree = nullptr;
};

#endif // CONFIG_H
