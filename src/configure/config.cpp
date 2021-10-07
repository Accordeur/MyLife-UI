#include "config.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include "tab_bar_node.h"
#include "view_tree_node.h"

#define MYLIFE_UI_CONFIG "MyLifeUIConfig"

Config::Config(const QString& file) : configPath(file)
{
    init();
}

bool Config::setConfigPath(const QString &file)
{
    configPath = file;
    return init();
}

bool Config::parse()
{
    QDomElement root = doc.documentElement();
    if(root.nodeName() != MYLIFE_UI_CONFIG) {
        qDebug() << tr("The root node is not 'MyLifeUIConfig', maybe it is not a MyLife UI config file!!!");
        valid = false;
        return false;
    }

    if(parseTabBarNode(root) /*&& parseViewTreeNode(root)*/) {
        valid = true;
        return true;
    }

    return false;
}

bool Config::isValid() const
{
    return valid;
}

bool Config::save()
{
    if(!isValid()) {
        qDebug() << tr("Current config is invalid, can not save!!!");
        return false;
    }

    if(!hasChanged()) {
        return true;
    }

    //保存前备份一次配置
    QFile::rename(configPath, configPath+"_back");
    QFile configFile(configPath);
    if(!configFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << tr("Open config file failed: ") << configFile.error();
        valid = false;
        return false;
    }

    //保存到文件
    QTextStream outStream(&configFile);
    doc.save(outStream, 4);
    configFile.close();
    return false;
}

TabBarNode *Config::getTabBarNode()
{
    return tabBar;
}

ViewTreeNode *Config::getViewTreeNode()
{
    return viewTree;
}

Config::~Config()
{
    delete tabBar;
    tabBar = nullptr;

    delete viewTree;
    viewTree = nullptr;
}

bool Config::parseTabBarNode(const QDomElement &root)
{
    QDomNodeList elementList = root.elementsByTagName(TAB_BAR_NODE);
    if(elementList.isEmpty()) {
        qDebug() << tr("can not find '") << TAB_BAR_NODE << tr("' element!");
        valid = false;
        return false;
    } else if (elementList.size() > 1) {
        qDebug() << tr("element '") << TAB_BAR_NODE << tr("' more than one!");
        valid = false;
        return false;
    }
    QDomNode element = elementList.at(0);
    if(tabBar != nullptr) {
        delete tabBar;
        tabBar = nullptr;
    }
    tabBar = new TabBarNode(element);
    if(!tabBar->parse()) {
        valid = false;
        delete tabBar;
        tabBar = nullptr;
        return false;
    }
    return true;
}

bool Config::parseViewTreeNode(const QDomElement &root)
{
    QDomNodeList elementList = root.elementsByTagName(VIEW_TREE_NODE);
    if(elementList.isEmpty()) {
        qDebug() << tr("can not find '") << VIEW_TREE_NODE << tr("' element!");
        valid = false;
        return false;
    } else if (elementList.size() > 1) {
        qDebug() << tr("element '") << VIEW_TREE_NODE << tr("' more than one!");
        valid = false;
        return false;
    }
    QDomNode element = elementList.at(0);
    if(viewTree != nullptr) {
        delete viewTree;
        viewTree = nullptr;
    }
    viewTree = new ViewTreeNode(element);
    if(!viewTree->parse()) {
        valid = false;
        delete viewTree;
        viewTree = nullptr;
        return false;
    }
    return true;
}

bool Config::init()
{
    QFile configFile(configPath);
    if(!configFile.open(QFile::ReadOnly)) {
        qDebug() << tr("Open config file failed: ") << configFile.error();
        valid = false;
        return false;
    }

    QString errorMsg;
    int errorLine = 0;
    int errorColum = 0;
    if(!doc.setContent(&configFile, false, &errorMsg, &errorLine, &errorColum)) {
        qDebug() << tr("It is a invalid config file, error: ") << errorMsg
                 << " line: " << errorLine
                 << " colum: " << errorColum;
        configFile.close();
        valid = false;
        return false;
    }
    configFile.close();
    return parse();
}

bool Config::hasChanged()
{
    return tabBar->hasChanged() || viewTree->hasChanged();
}
