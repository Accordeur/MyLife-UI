#ifndef VIEWTREENODE_H
#define VIEWTREENODE_H
#include <QCoreApplication>

#include "config_node_interface.h"

#define VIEW_TREE_NODE "ViewTree"

class ViewTreeNode : public ConfigNodeInterface
{
public:
    ViewTreeNode(const QDomNode& node);
    virtual bool parse() override;
    virtual bool updateDom() override;

    struct AdvancedFilter {
        bool useAdvFlt = false;
        struct Rule {
            bool enable = false;
            bool expanded = false;
            QString field;
            QString conditionID;
            QString conditionName;
            QString dataType;
            QString dataValue;
            QString linkExpr;
            QList<Rule> subRule;
            friend inline bool operator== (const Rule&, const Rule&) noexcept;
            friend inline bool operator!= (const Rule&, const Rule&) noexcept;
        };
        QVector<Rule> rule;
        friend inline bool operator== (const AdvancedFilter&, const AdvancedFilter&) noexcept;
        friend inline bool operator!= (const AdvancedFilter&, const AdvancedFilter&) noexcept;
    };


    struct ViewTable {
    private:
        int32_t id = -1;
    public:
        int32_t position = -1;
        bool isFolder = false;
        bool hide = false;
        QString name;
        QString icon;
        struct Counters {
            bool enable = true;
            bool hideIfZero = false;
            QString type;
            QString hierarchy;
            friend constexpr inline bool operator== (const Counters&, const Counters&) noexcept;
            friend constexpr inline bool operator!= (const Counters&, const Counters&) noexcept;
        };
        Counters counters;
        struct Filter {
            struct Show {
                QString actions;
                QString hierarchy;
                struct Complet {
                    QString type;
                    QString hideOld;
                    friend inline bool operator== (const Complet&, const Complet&) noexcept;
                    friend inline bool operator!= (const Complet&, const Complet&) noexcept;
                };
                Complet comple;
                friend inline bool operator== (const Show&, const Show&) noexcept;
                friend inline bool operator!= (const Show&, const Show&) noexcept;
            };
            Show show;
            struct Text {
                bool inTitle = false;
                bool inNotes = false;
                bool inContexts = false;
                bool inTags = false;
                QString str;
                friend constexpr inline bool operator== (const Text&, const Text&) noexcept;
                friend constexpr inline bool operator!= (const Text&, const Text&) noexcept;
            };
            Text text;
            struct Contexts {
                bool includeClose = false;
                QString operation;
                QVector<QString> row;
                friend constexpr inline bool operator== (const Contexts&, const Contexts&) noexcept;
                friend constexpr inline bool operator!= (const Contexts&, const Contexts&) noexcept;
            };
            Contexts context;
            struct Flags {
                bool includeClose = false;
                QString operation;
                QVector<QString> row;
                friend constexpr inline bool operator== (const Flags&, const Flags&) noexcept;
                friend constexpr inline bool operator!= (const Flags&, const Flags&) noexcept;
            };
            Flags flags;
            struct StartDate {
                bool hideUndated;
                struct From {
                    QString type;
                    QString fromDate;
                    friend inline bool operator== (const From&, const From&) noexcept;
                    friend inline bool operator!= (const From&, const From&) noexcept;
                };
                From from;
                struct To {
                    QString type;
                    QString fromDate;
                    friend inline bool operator== (const To&, const To&) noexcept;
                    friend inline bool operator!= (const To&, const To&) noexcept;
                };
                To to;
                friend inline bool operator== (const StartDate&, const StartDate&) noexcept;
                friend inline bool operator!= (const StartDate&, const StartDate&) noexcept;
            };
            StartDate startDate;
            AdvancedFilter advFlt;
            struct GroupSort {
                struct Group {
                    bool showCount = false;
                    bool showName = false;
                    bool onlyByDays = false;
                    struct GroupBy {
                        QString type;
                        QString by;
                        friend inline bool operator== (const GroupBy&, const GroupBy&) noexcept;
                        friend inline bool operator!= (const GroupBy&, const GroupBy&) noexcept;
                    };
                    QVector<GroupBy> groupBy;
                    friend inline bool operator== (const Group&, const Group&) noexcept;
                    friend inline bool operator!= (const Group&, const Group&) noexcept;
                };
                Group group;
                struct Sort {
                    bool manual = false;
                    struct SortBy {
                        QString type;
                        QString by;
                        friend inline bool operator== (const SortBy&, const SortBy&) noexcept;
                        friend inline bool operator!= (const SortBy&, const SortBy&) noexcept;
                    };
                    QVector<SortBy> sortBy;
                    friend constexpr inline bool operator== (const Sort&, const Sort&) noexcept;
                    friend constexpr inline bool operator!= (const Sort&, const Sort&) noexcept;
                };
                Sort sortBy;
                friend inline bool operator== (const GroupSort&, const GroupSort&) noexcept;
                friend inline bool operator!= (const GroupSort&, const GroupSort&) noexcept;
            };
            GroupSort groupSort;
            friend inline bool operator== (const Filter&, const Filter&) noexcept;
            friend inline bool operator!= (const Filter&, const Filter&) noexcept;
        };
        Filter filter;

        friend constexpr inline bool operator==(const ViewTable& v1, const ViewTable& v2) noexcept;
        friend constexpr inline bool operator!=(const ViewTable& v1, const ViewTable& v2) noexcept;
        friend class ViewTreeNode;
    };

    QVector<ViewTable> getViewTableConfig() const;
private:
    int findUnusedID() const;
    bool parseCounters(const QDomElement& element, ViewTable::Counters& counters);
    bool parseFilter(const QDomElement& element, ViewTable::Filter& filter);
    bool parseFilterShow(const QDomElement& element, ViewTable::Filter::Show& show);
    bool parseFilterShowComplet(const QDomElement& element, ViewTable::Filter::Show::Complet& complet);
    bool parseFilterText(const QDomElement& element, ViewTable::Filter::Text& text);
    bool parseFilterContexts(const QDomElement& element, ViewTable::Filter::Contexts& contexts);
    bool parseFilterFlags(const QDomElement& element, ViewTable::Filter::Flags& flags);
    bool parseFilterStartDate(const QDomElement& element, ViewTable::Filter::StartDate& startDate);
    bool parseFilterGroupSort(const QDomElement& element, ViewTable::Filter::GroupSort & groupSort);
    bool parseFilterGroupSortGroup(const QDomElement& element, ViewTable::Filter::GroupSort::Group & group);
    bool parseFilterGroupSortSort(const QDomElement& element, ViewTable::Filter::GroupSort::Sort & sort);

    bool parseFilterAdvanced(const QDomElement& element, AdvancedFilter& filter);
    bool parseFilterAdvancedRule(const QDomElement& element, AdvancedFilter::Rule& rule);

    QVector<ViewTable> viewTableVec;
};

inline bool operator== (const ViewTreeNode::AdvancedFilter::Rule& r1, const ViewTreeNode::AdvancedFilter::Rule& r2) noexcept {
    return r1.conditionID == r2.conditionID && r1.conditionName == r2.conditionName && r1.dataType == r2.dataType &&
            r1.dataValue == r2.dataValue && r1.enable == r2.enable && r1.expanded == r2.expanded && r1.field == r2.field &&
            r1.linkExpr == r2.field && r1.subRule == r2.subRule;
}
inline bool operator!= (const ViewTreeNode::AdvancedFilter::Rule& r1, const ViewTreeNode::AdvancedFilter::Rule& r2) noexcept {
    return !(r1 == r2);
}


inline bool operator== (const ViewTreeNode::AdvancedFilter& f1, const ViewTreeNode::AdvancedFilter& f2) noexcept {
    return f1.rule == f2.rule && f1.useAdvFlt == f2.useAdvFlt;
}

inline bool operator!= (const ViewTreeNode::AdvancedFilter& f1, const ViewTreeNode::AdvancedFilter& f2) noexcept {
    return !(f1 == f2);
}

constexpr inline bool operator== (const ViewTreeNode::ViewTable::Counters& c1, const ViewTreeNode::ViewTable::Counters& c2) noexcept {
    return c1.enable == c2.enable && c1.hideIfZero == c2.hideIfZero && c1.hierarchy == c2.hierarchy && c1.type == c2.type;
}
constexpr inline bool operator!= (const ViewTreeNode::ViewTable::Counters& c1, const ViewTreeNode::ViewTable::Counters& c2) noexcept {
    return !(c1 == c2);
}


inline bool operator== (const ViewTreeNode::ViewTable::Filter::Show::Complet& c1, const ViewTreeNode::ViewTable::Filter::Show::Complet& c2) noexcept {
    return c1.type == c2.type && c1.hideOld == c2.hideOld;
}
inline bool operator!= (const ViewTreeNode::ViewTable::Filter::Show::Complet& c1, const ViewTreeNode::ViewTable::Filter::Show::Complet& c2) noexcept {
    return !(c1 == c2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter::Show& s1, const ViewTreeNode::ViewTable::Filter::Show& s2) noexcept {
    return s1.actions == s2.actions && s1.comple == s2.comple && s1.hierarchy == s2.hierarchy;
}
inline bool operator!= (const ViewTreeNode::ViewTable::Filter::Show& s1, const ViewTreeNode::ViewTable::Filter::Show& s2) noexcept{
    return !(s1 == s2);
}

constexpr inline bool operator== (const ViewTreeNode::ViewTable::Filter::Text& t1, const ViewTreeNode::ViewTable::Filter::Text& t2) noexcept {
    return t1.inContexts == t2.inContexts && t1.inNotes == t2.inNotes &&
            t1.inTags == t2.inTags && t1.inTitle == t2.inTags && t1.str == t2.str;
}

constexpr inline bool operator!= (const ViewTreeNode::ViewTable::Filter::Text& t1, const ViewTreeNode::ViewTable::Filter::Text& t2) noexcept {
    return !(t1 == t2);
}

constexpr inline bool operator== (const ViewTreeNode::ViewTable::Filter::Contexts& c1, const ViewTreeNode::ViewTable::Filter::Contexts& c2) noexcept {
    return c1.includeClose == c2.includeClose && c1.operation == c2.operation && c1.row == c2.row;
}
constexpr inline bool operator!= (const ViewTreeNode::ViewTable::Filter::Contexts& c1, const ViewTreeNode::ViewTable::Filter::Contexts& c2) noexcept {
    return !(c1 == c2);
}

constexpr inline bool operator== (const ViewTreeNode::ViewTable::Filter::Flags& f1, const ViewTreeNode::ViewTable::Filter::Flags& f2) noexcept {
    return f1.includeClose == f2.includeClose && f1.operation == f2.operation && f1.row == f2.row;
}
constexpr inline bool operator!= (const ViewTreeNode::ViewTable::Filter::Flags& f1, const ViewTreeNode::ViewTable::Filter::Flags& f2) noexcept {
    return !(f1 == f2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter::StartDate::From& f1, const ViewTreeNode::ViewTable::Filter::StartDate::From& f2) noexcept {
    return f1.fromDate == f2.fromDate && f1.type == f2.type;
}
inline bool operator!= (const ViewTreeNode::ViewTable::Filter::StartDate::From& f1, const ViewTreeNode::ViewTable::Filter::StartDate::From& f2) noexcept {
    return !(f1 == f2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter::StartDate::To& t1, const ViewTreeNode::ViewTable::Filter::StartDate::To& t2) noexcept {
    return t1.fromDate == t2.fromDate && t1.type == t2.type;
}
inline bool operator!= (const ViewTreeNode::ViewTable::Filter::StartDate::To& t1, const ViewTreeNode::ViewTable::Filter::StartDate::To& t2) noexcept {
    return !(t1 == t2);
}


inline bool operator== (const ViewTreeNode::ViewTable::Filter::StartDate& s1, const ViewTreeNode::ViewTable::Filter::StartDate& s2) noexcept {
    return s1.from == s2.from && s1.hideUndated == s2.hideUndated && s1.to == s2.to;
}
inline bool operator!= (const ViewTreeNode::ViewTable::Filter::StartDate& s1, const ViewTreeNode::ViewTable::Filter::StartDate& s2) noexcept {
    return !(s1 == s2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter::GroupSort::Group::GroupBy& g1, const ViewTreeNode::ViewTable::Filter::GroupSort::Group::GroupBy& g2) noexcept {
    return g1.by == g2.by && g1.type == g2.type;
}

inline bool operator!= (const ViewTreeNode::ViewTable::Filter::GroupSort::Group::GroupBy& g1, const ViewTreeNode::ViewTable::Filter::GroupSort::Group::GroupBy& g2) noexcept {
    return !(g1 == g2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter::GroupSort::Group& g1, const ViewTreeNode::ViewTable::Filter::GroupSort::Group& g2) noexcept {
    return g1.groupBy == g2.groupBy && g1.onlyByDays == g2.onlyByDays &&
            g1.showCount == g2.showCount && g1.showName == g2.showName;
}

inline bool operator!= (const ViewTreeNode::ViewTable::Filter::GroupSort::Group& g1, const ViewTreeNode::ViewTable::Filter::GroupSort::Group& g2) noexcept {
   return !(g1 == g2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter::GroupSort::Sort::SortBy& s1, const ViewTreeNode::ViewTable::Filter::GroupSort::Sort::SortBy& s2) noexcept {
    return s1.by == s2.by && s1.type == s2.type;
}
inline bool operator!= (const ViewTreeNode::ViewTable::Filter::GroupSort::Sort::SortBy& s1, const ViewTreeNode::ViewTable::Filter::GroupSort::Sort::SortBy& s2) noexcept {
    return !(s1 == s2);
}

constexpr inline bool operator== (const ViewTreeNode::ViewTable::Filter::GroupSort::Sort& s1, const ViewTreeNode::ViewTable::Filter::GroupSort::Sort& s2) noexcept {
    return s1.manual == s2.manual && s1.sortBy == s2.sortBy;
}
constexpr inline bool operator!= (const ViewTreeNode::ViewTable::Filter::GroupSort::Sort& s1, const ViewTreeNode::ViewTable::Filter::GroupSort::Sort& s2) noexcept {
    return !(s1 == s2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter::GroupSort& s1, const ViewTreeNode::ViewTable::Filter::GroupSort& s2) noexcept {
    return s1.group == s2.group && s1.sortBy == s2.sortBy;
}

inline bool operator!= (const ViewTreeNode::ViewTable::Filter::GroupSort& s1, const ViewTreeNode::ViewTable::Filter::GroupSort& s2) noexcept {
    return !(s1 == s2);
}

inline bool operator== (const ViewTreeNode::ViewTable::Filter& f1, const ViewTreeNode::ViewTable::Filter& f2) noexcept {
    return f1.advFlt == f2.advFlt && f1.context == f2.context && f1.flags == f2.flags && f1.groupSort == f1.groupSort &&
            f1.show == f2.show && f1.startDate == f2.startDate && f1.text == f2.text;
}
inline bool operator!= (const ViewTreeNode::ViewTable::Filter& f1, const ViewTreeNode::ViewTable::Filter& f2) noexcept {
    return !(f1 == f2);
}

constexpr inline bool operator==(const ViewTreeNode::ViewTable& v1, const ViewTreeNode::ViewTable& v2) noexcept {
    if(v1.id == -1 && v2.id == -1) {
        return v1.position == v2.position && v1.isFolder == v2.isFolder && v1.hide == v2.hide &&
                v1.icon == v2.icon && v1.counters == v2.counters && v1.filter == v2.filter;
    }
    return v1.id == v2.id;
}

constexpr inline bool operator!=(const ViewTreeNode::ViewTable& v1, const ViewTreeNode::ViewTable& v2) noexcept {
    return !(v1 == v2);
}
#endif // VIEWTREENODE_H
