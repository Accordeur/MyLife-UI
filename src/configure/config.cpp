#include "config.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <glog/logging.h>
#include "tab_bar_node.h"
#include "view_tree_node.h"

#define MYLIFE_UI_CONFIG "MyLifeUIConfig"

Config* Config::config = nullptr;

Config *Config::getConfig()
{
    if(config != nullptr) {
        return config;
    }

    return nullptr;
}

Config *Config::getConfig(const QString &file)
{
    if(config != nullptr) {
        delete config;
        config = new Config(file);
        return config;
    }
    config = new Config(file);
    return config;
}

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
        LOG(ERROR) << "The root node is not 'MyLifeUIConfig', maybe it is not a MyLife UI config file!!!";
        valid = false;
        return false;
    }

    if(parseTabBarNode(root) && parseViewTreeNode(root)) {
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
        LOG(ERROR) << "Current config is invalid, can not save!!!";
        return false;
    }

    if(!hasChanged()) {
        return true;
    }

    //保存前备份一次配置
    QFile::rename(configPath, configPath+"_back");
    QFile configFile(configPath);
    if(!configFile.open(QFile::WriteOnly | QFile::Truncate)) {
        LOG(ERROR) << "Open config file failed: " << configFile.error();
        valid = false;
        return false;
    }

    //保存到文件
    if(tabBar->updateDom() && viewTree->updateDom()) {
        QTextStream outStream(&configFile);
        doc.save(outStream, 4);
        configFile.close();
        return true;
    }
    LOG(ERROR) << "update DomDocument fail!!!";
    return false;
}

TabBarNode *Config::getTabBarNode()
{
    return reinterpret_cast<TabBarNode*>(tabBar);
}

ViewTreeNode *Config::getViewTreeNode()
{
    return reinterpret_cast<ViewTreeNode*>(viewTree);
}

Config::~Config()
{
    delete tabBar;
    tabBar = nullptr;

    delete viewTree;
    viewTree = nullptr;

    config = nullptr;
}

bool Config::parseTabBarNode(const QDomElement &root)
{
    QDomNodeList elementList = root.elementsByTagName(TAB_BAR_NODE);
    if(elementList.isEmpty()) {
        LOG(ERROR) << "can not find '" << TAB_BAR_NODE << "' element!";
        valid = false;
        return false;
    } else if (elementList.size() > 1) {
        LOG(ERROR) << "element '" << TAB_BAR_NODE << "' more than one!";
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
        LOG(ERROR) << "can not find '" << VIEW_TREE_NODE << "' element!";
        valid = false;
        return false;
    } else if (elementList.size() > 1) {
        LOG(ERROR) << "element '" << VIEW_TREE_NODE << "' more than one!";
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
        LOG(ERROR) << "Open config file failed: " << configFile.error();
        valid = false;
        return false;
    }

    QString errorMsg;
    int errorLine = 0;
    int errorColum = 0;
    if(!doc.setContent(&configFile, false, &errorMsg, &errorLine, &errorColum)) {
        LOG(ERROR) << "It is a invalid config file, error: " << errorMsg.toStdString()
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
