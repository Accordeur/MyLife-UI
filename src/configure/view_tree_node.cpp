#include "view_tree_node.h"
#include <glog/logging.h>

#define VIEW "View"
#define VIEW_ID "id"
#define VIEW_POSITION "position"
#define VIEW_IS_FOLDER "isFolder"
#define VIEW_HIDE "hide"
#define VIEW_NAME "name"
#define VIEW_ICON "icon"

#define VIEW_COUNTERS "counters"
#define VIEW_COUNTERS_ENABLE "enable"
#define VIEW_COUNTERS_HIDE_IF_ZERO "hideIfZero"
#define VIEW_COUNTERS_TYPE "type"
#define VIEW_COUNTERS_HIERARHY "hierarchy"

#define VIEW_FILTER "Filter"
#define VIEW_FILTER_SHOW "show"
#define VIEW_FILTER_SHOW_ACTIONS "actions"
#define VIEW_FILTER_SHOW_HIERARCHY "hierarchy"
#define VIEW_FILTER_SHOW_COMPLET "complet"
#define VIEW_FILTER_SHOW_COMPLET_TYPE "type"
#define VIEW_FILTER_SHOW_COMPLET_HIDE_OLD "hideOld"

#define VIEW_FILTER_TEXT "text"
#define VIEW_FILTER_TEXT_IN_TITLE "inTitle"
#define VIEW_FILTER_TEXT_IN_NOTES "inNotes"
#define VIEW_FILTER_TEXT_IN_CONTEXTS "inContexts"
#define VIEW_FILTER_TEXT_IN_TAGS "inTags"
#define VIEW_FILTER_TEXT_STRING "string"

#define VIEW_FILTER_CONTEXTS "contexts"
#define VIEW_FILTER_CONTEXTS_INCLUDE_CLOSED "includeClosed"
#define VIEW_FILTER_CONTEXTS_OPERATION "operation"
#define VIEW_FILTER_CONTEXTS_ROW "row"

#define VIEW_FILTER_FLAGS "flags"
#define VIEW_FILTER_FLAGS_INCLUDE_CLOSED "includeClosed"
#define VIEW_FILTER_FLAGS_OPERATION "operation"
#define VIEW_FILTER_FLAGS_ROW "row"

#define VIEW_FILTER_START_DATE "startDate"
#define VIEW_FILTER_START_DATE_HIDE_UNDATED "hideUndated"
#define VIEW_FILTER_START_DATE_FROM "from"
#define VIEW_FILTER_START_DATE_FROM_TYPE "type"
#define VIEW_FILTER_START_DATE_TO "to"
#define VIEW_FILTER_START_DATE_TO_TYPE "type"

#define VIEW_FILTER_ADVANCED "advanced"
#define VIEW_FILTER_ADVANCED_USE_ADVANCED "useAdvanced"
#define VIEW_FILTER_ADVANCED_RULE "rule"
#define VIEW_FILTER_ADVANCED_RULE_ENABLE "enable"
#define VIEW_FILTER_ADVANCED_RULE_FIELD "field"
#define VIEW_FILTER_ADVANCED_RULE_CONDITION_ID "conditionID"
#define VIEW_FILTER_ADVANCED_RULE_CONDITION_NAME "conditionName"
#define VIEW_FILTER_ADVANCED_RULE_EXPANDED "expanded"
#define VIEW_FILTER_ADVANCED_RULE_DATA_VALUE "dataValue"
#define VIEW_FILTER_ADVANCED_RULE_DATA_TYPE "dataType"
#define VIEW_FILTER_ADVANCED_RULE_LINK_EXPR "linkExpr"

#define VIEW_FILTER_GROUP_SORT "groupSort"
#define VIEW_FILTER_GROUP_SORT_GROUP "group"
#define VIEW_FILTER_GROUP_SORT_GROUP_SHOW_COUNT "showCount"
#define VIEW_FILTER_GROUP_SORT_GROUP_SHOW_NAME "showName"
#define VIEW_FILTER_GROUP_SORT_GROUP_ONLY_BY_DAYS "onlyByDays"
#define VIEW_FILTER_GROUP_SORT_GROUP_GROUP_BY "groupBy"
#define VIEW_FILTER_GROUP_SORT_GROUP_GROUP_BY_TYPE "type"
#define VIEW_FILTER_GROUP_SORT_SORT "sort"
#define VIEW_FILTER_GROUP_SORT_SORT_MANUAL "manual"
#define VIEW_FILTER_GROUP_SORT_SORT_SORT_BY "sortBy"
#define VIEW_FILTER_GROUP_SORT_SORT_SORT_BY_TYPE "type"

ViewTreeNode::ViewTreeNode(const QDomNode &node) : ConfigNodeInterface(node)
{

}

bool ViewTreeNode::parse()
{
    if(domNode.nodeName() != VIEW_TREE_NODE && !domNode.isElement()) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_TREE_NODE;
        setValid(false);
        return false;
    }
    QDomElement viewTreeEle = domNode.toElement();
    QDomNodeList viewList = viewTreeEle.elementsByTagName(VIEW);
    for(int i = 0; i < viewList.size(); i++) {
        QDomElement view = viewList.at(i).toElement();
        QDomNamedNodeMap attrMap =  view.attributes();
        ViewTable table;
        table.id = attrMap.namedItem(VIEW_ID).nodeValue().toInt();
        table.position = attrMap.namedItem(VIEW_POSITION).nodeValue().toInt();
        table.isFolder = attrMap.namedItem(VIEW_IS_FOLDER).nodeValue() == "true" ? true : false;
        table.hide = attrMap.namedItem(VIEW_HIDE).nodeValue() == "true" ? true : false;

        QDomNode node = view.firstChild();
        while(!node.isNull()) {
            QDomElement e = node.toElement();
            if(e.tagName() == VIEW_NAME) {
                table.name = e.text();
            } else if(e.tagName() == VIEW_ICON) {
                table.icon = e.text();
            } else if(e.tagName() == VIEW_COUNTERS) {
                if(!parseCounters(e, table.counters)) {
                    LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_COUNTERS;
                    setValid(false);
                    return false;
                }
            } else if(e.tagName() == VIEW_FILTER) {
                if(!parseFilter(e, table.filter)) {
                    LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER;
                    setValid(false);
                    return false;
                }
            } else {
                LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
            }

            node = node.nextSibling();
        }
        viewTableVec.push_back(table);
    }

    setValid(true);
    return true;
}

bool ViewTreeNode::updateDom()
{
    if(!hasChanged()) {
        return true;
    }

    change(false);
    return true;
}

QVector<ViewTreeNode::ViewTable> ViewTreeNode::getViewTableConfig() const
{
    return viewTableVec;
}

int ViewTreeNode::findUnusedID() const
{
    int result = 0;
    while(true) {
        ViewTable t;
        t.id = result;
        auto findIter = std::find(viewTableVec.cbegin(), viewTableVec.cend(), t);
        if(findIter == viewTableVec.cend()) {
            return result;
        }
        result++;
    }
}

bool ViewTreeNode::parseCounters(const QDomElement &element, ViewTable::Counters &counters)
{
    if(element.tagName() != VIEW_COUNTERS) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_TREE_NODE;
        setValid(false);
        return false;
    }
    QDomNamedNodeMap attrMap =  element.attributes();

    counters.enable = attrMap.namedItem(VIEW_COUNTERS_ENABLE).nodeValue() == "true" ? true : false;
    counters.hideIfZero = attrMap.namedItem(VIEW_COUNTERS_HIDE_IF_ZERO).nodeValue() == "true" ? true : false;
    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_COUNTERS_TYPE) {
            counters.type = e.text();
        } else if(e.tagName() == VIEW_COUNTERS_HIERARHY) {
            counters.hierarchy = e.text();
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }

    return true;
}

bool ViewTreeNode::parseFilter(const QDomElement &element, ViewTable::Filter &filter)
{
    if(element.tagName() != VIEW_FILTER) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_TREE_NODE;
        setValid(false);
        return false;
    }
    // QDomNamedNodeMap attrMap =  element.attributes();

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_SHOW) {
            if(!parseFilterShow(e, filter.show)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_SHOW;
                setValid(false);
                return false;
            }
        } else if(e.tagName() == VIEW_FILTER_TEXT) {
            if(!parseFilterText(e, filter.text)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_TEXT;
                setValid(false);
                return false;
            }
        } else if(e.tagName() == VIEW_FILTER_CONTEXTS) {
            if(!parseFilterContexts(e, filter.contexts)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_CONTEXTS;
                setValid(false);
                return false;
            }
        } else if(e.tagName() == VIEW_FILTER_FLAGS) {
            if(!parseFilterFlags(e, filter.flags)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_FLAGS;
                setValid(false);
                return false;
            }
        } else if(e.tagName() == VIEW_FILTER_START_DATE) {
            if(!parseFilterStartDate(e, filter.startDate)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_START_DATE;
                setValid(false);
                return false;
            }
        } else if(e.tagName() == VIEW_FILTER_ADVANCED) {
            if(!parseFilterAdvanced(e, filter.advFlt)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_ADVANCED;
                setValid(false);
                return false;
            }
        } else if(e.tagName() == VIEW_FILTER_GROUP_SORT) {
            if(!parseFilterGroupSort(e, filter.groupSort)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_GROUP_SORT;
                setValid(false);
                return false;
            }
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }

        node = node.nextSibling();
    }

    return true;
}

bool ViewTreeNode::parseFilterShow(const QDomElement &element, ViewTable::Filter::Show &show)
{
    if(element.tagName() != VIEW_FILTER_SHOW) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_SHOW;
        setValid(false);
        return false;
    }
    //QDomNamedNodeMap attrMap =  element.attributes();

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_SHOW_ACTIONS) {
            show.actions = e.text();
        } else if(e.tagName() == VIEW_FILTER_SHOW_HIERARCHY) {
            show.hierarchy = e.text();
        } else if(e.tagName() == VIEW_FILTER_SHOW_COMPLET) {
            if(!parseFilterShowComplet(e, show.comple)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_SHOW_COMPLET;
                setValid(false);
                return false;
            }
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterShowComplet(const QDomElement &element, ViewTable::Filter::Show::Complet &complet)
{
    if(element.tagName() != VIEW_FILTER_SHOW_COMPLET) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_SHOW_COMPLET;
        setValid(false);
        return false;
    }
    //QDomNamedNodeMap attrMap =  element.attributes();

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_SHOW_COMPLET_TYPE) {
            complet.type = e.text();
        } else if(e.tagName() == VIEW_FILTER_SHOW_COMPLET_HIDE_OLD) {
            complet.hideOld = e.text();
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterText(const QDomElement &element, ViewTable::Filter::Text &text)
{
    if(element.tagName() != VIEW_FILTER_TEXT) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_TEXT << ", bust is " << element.tagName().toStdString();
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    text.inTitle = attrMap.namedItem(VIEW_FILTER_TEXT_IN_TITLE).nodeValue() == "true" ? true : false;
    text.inNotes = attrMap.namedItem(VIEW_FILTER_TEXT_IN_NOTES).nodeValue() == "true" ? true : false;
    text.inContexts = attrMap.namedItem(VIEW_FILTER_TEXT_IN_CONTEXTS).nodeValue() == "true" ? true : false;
    text.inTags = attrMap.namedItem(VIEW_FILTER_TEXT_IN_TAGS).nodeValue() == "true" ? true : false;

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_TEXT_STRING) {
            text.str = e.text();
        }  else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterContexts(const QDomElement &element, ViewTable::Filter::Contexts &contexts)
{
    if(element.tagName() != VIEW_FILTER_CONTEXTS) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_CONTEXTS;
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    contexts.includeClose = attrMap.namedItem(VIEW_FILTER_CONTEXTS_INCLUDE_CLOSED).nodeValue() == "true" ? true : false;
    contexts.operation = attrMap.namedItem(VIEW_FILTER_CONTEXTS_OPERATION).nodeValue();

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_CONTEXTS_ROW) {
            contexts.row.push_back(e.text());
        }  else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterFlags(const QDomElement &element, ViewTable::Filter::Flags &flags)
{
    if(element.tagName() != VIEW_FILTER_FLAGS) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_FLAGS;
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    flags.includeClose = attrMap.namedItem(VIEW_FILTER_FLAGS_INCLUDE_CLOSED).nodeValue() == "true" ? true : false;
    flags.operation = attrMap.namedItem(VIEW_FILTER_FLAGS_OPERATION).nodeValue();

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_FLAGS_ROW) {
            flags.row.push_back(e.text());
        }  else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterStartDate(const QDomElement &element, ViewTable::Filter::StartDate &startDate)
{
    if(element.tagName() != VIEW_FILTER_START_DATE) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_START_DATE;
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    startDate.hideUndated = attrMap.namedItem(VIEW_FILTER_START_DATE_HIDE_UNDATED).nodeValue() == "true" ? true : false;

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_START_DATE_FROM) {
            QDomNamedNodeMap fromAttrMap =  e.attributes();
            startDate.from.type = fromAttrMap.namedItem(VIEW_FILTER_START_DATE_FROM_TYPE).nodeValue();
            startDate.from.fromDate = e.text();
        } else if(e.tagName() == VIEW_FILTER_START_DATE_TO) {
            QDomNamedNodeMap toAttrMap =  e.attributes();
            startDate.to.type = toAttrMap.namedItem(VIEW_FILTER_START_DATE_TO_TYPE).nodeValue();
            startDate.to.fromDate = e.text();
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterGroupSort(const QDomElement &element, ViewTable::Filter::GroupSort &groupSort)
{
    if(element.tagName() != VIEW_FILTER_GROUP_SORT) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_GROUP_SORT;
        setValid(false);
        return false;
    }

    //QDomNamedNodeMap attrMap =  element.attributes();

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_GROUP_SORT_GROUP) {
            if(!parseFilterGroupSortGroup(e, groupSort.group)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_GROUP_SORT_GROUP;
                setValid(false);
                return false;
            }
        } else if(e.tagName() == VIEW_FILTER_GROUP_SORT_SORT) {
            if(!parseFilterGroupSortSort(e, groupSort.sortBy)) {
                LOG(ERROR) << "Parse Config Error, Tag: " << VIEW_FILTER_GROUP_SORT_SORT;
                setValid(false);
                return false;
            }
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterGroupSortGroup(const QDomElement &element, ViewTable::Filter::GroupSort::Group &group)
{
    if(element.tagName() != VIEW_FILTER_GROUP_SORT_GROUP) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_GROUP_SORT_GROUP;
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    group.showCount = attrMap.namedItem(VIEW_FILTER_GROUP_SORT_GROUP_SHOW_COUNT).nodeValue() == "true" ? true : false;
    group.showName = attrMap.namedItem(VIEW_FILTER_GROUP_SORT_GROUP_SHOW_COUNT).nodeValue() == "true" ? true : false;
    group.onlyByDays = attrMap.namedItem(VIEW_FILTER_GROUP_SORT_GROUP_ONLY_BY_DAYS).nodeValue() == "true" ? true : false;

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_GROUP_SORT_GROUP_GROUP_BY) {
            ViewTable::Filter::GroupSort::Group::GroupBy groupBy;
            QDomNamedNodeMap groupByAttrMap =  e.attributes();
            groupBy.type = groupByAttrMap.namedItem(VIEW_FILTER_GROUP_SORT_GROUP_GROUP_BY_TYPE).nodeValue();
            groupBy.by = e.text();
            group.groupBy.push_back(groupBy);
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterGroupSortSort(const QDomElement &element, ViewTable::Filter::GroupSort::Sort &sort)
{
    if(element.tagName() != VIEW_FILTER_GROUP_SORT_SORT) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_GROUP_SORT_GROUP;
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    sort.manual = attrMap.namedItem(VIEW_FILTER_GROUP_SORT_SORT_MANUAL).nodeValue() == "true" ? true : false;

    QDomNode node = element.firstChild();
    while(!node.isNull()) {
        QDomElement e = node.toElement();
        if(e.tagName() == VIEW_FILTER_GROUP_SORT_SORT_SORT_BY) {
            ViewTable::Filter::GroupSort::Sort::SortBy sortBy;
            QDomNamedNodeMap groupByAttrMap =  e.attributes();
            sortBy.type = groupByAttrMap.namedItem(VIEW_FILTER_GROUP_SORT_SORT_SORT_BY_TYPE).nodeValue();
            sortBy.by = e.text();
            sort.sortBy.push_back(sortBy);
        } else {
            LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
        }
        node = node.nextSibling();
    }
    return true;
}

bool ViewTreeNode::parseFilterAdvanced(const QDomElement &element, AdvancedFilter &filter)
{
    if(element.tagName() != VIEW_FILTER_ADVANCED) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_ADVANCED;
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    filter.useAdvFlt = attrMap.namedItem(VIEW_FILTER_ADVANCED_USE_ADVANCED).nodeValue() == "true" ? true : false;

    if(filter.useAdvFlt == true) {
        QDomNode node = element.firstChild();
        while(!node.isNull()) {
            QDomElement e = node.toElement();
            if(e.tagName() == VIEW_FILTER_ADVANCED_RULE) {
                AdvancedFilter::Rule rule;
                if(!parseFilterAdvancedRule(e, rule)) {
                    LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_ADVANCED_RULE;
                    setValid(false);
                    return false;
                }
                filter.rule.push_back(rule);
            } else {
                LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
            }
            node = node.nextSibling();
        }
    }

    return true;
}

bool ViewTreeNode::parseFilterAdvancedRule(const QDomElement &element, AdvancedFilter::Rule &rule)
{
    if(element.tagName() != VIEW_FILTER_ADVANCED_RULE) {
        LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_ADVANCED_RULE;
        setValid(false);
        return false;
    }

    QDomNamedNodeMap attrMap =  element.attributes();
    rule.enable = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_ENABLE).nodeValue() == "true" ? true : false;
    rule.field = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_FIELD).nodeValue();
    rule.conditionName = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_CONDITION_NAME).nodeValue();
    rule.dataValue = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_DATA_VALUE).nodeValue();
    rule.dataType = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_DATA_TYPE).nodeValue();
    rule.conditionID = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_CONDITION_ID).nodeValue();
    rule.expanded = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_EXPANDED).nodeValue() == "true" ? true : false;
    rule.linkExpr = attrMap.namedItem(VIEW_FILTER_ADVANCED_RULE_LINK_EXPR).nodeValue();

    if(rule.expanded == true) {
        QDomNode node = element.firstChild();
        while(!node.isNull()) {
            QDomElement e = node.toElement();
            if(e.tagName() == VIEW_FILTER_ADVANCED_RULE) {
                AdvancedFilter::Rule subRule;
                if(!parseFilterAdvancedRule(e, subRule)) {
                    LOG(ERROR) << "Can not parse Node, because the root node must is " << VIEW_FILTER_ADVANCED_RULE;
                    setValid(false);
                    return false;
                }
                rule.subRule.push_back(subRule);
            } else {
                LOG(ERROR) << "UnKnow tag: " << e.tagName().toStdString();
            }
            node = node.nextSibling();
        }
    }
    return true;
}
