#ifdef ENABLE_TEST

#include <gtest/gtest.h>
#include <QFile>
#include "configure/config.h"
#include "configure/tab_bar_node.h"
#include "configure/view_tree_node.h"
#include <glog/logging.h>

TEST(Config, TabBarRead) {
    Config* config = Config::getConfig("../src/test/tab_bar_read_test.xml");
    EXPECT_EQ(config->isValid(), true);

    TabBarNode* node = config->getTabBarNode();
    auto tableVec = node->getTabBarConfig();
    ASSERT_EQ(tableVec.length(), 2);

    EXPECT_EQ(tableVec[0].position, 1);
    EXPECT_EQ(tableVec[1].position, 2);

    EXPECT_EQ(tableVec[0].pinTab, true);
    EXPECT_EQ(tableVec[1].pinTab, false);

    EXPECT_EQ(tableVec[0].showView, true);
    EXPECT_EQ(tableVec[1].showView, false);

    EXPECT_EQ(tableVec[0].isDefault, true);
    EXPECT_EQ(tableVec[1].isDefault, false);

    EXPECT_EQ(tableVec[0].lockDefault, false);
    EXPECT_EQ(tableVec[1].lockDefault, true);

    EXPECT_EQ(tableVec[0].iconPath, ":/icon/outline");
    EXPECT_EQ(tableVec[1].iconPath, ":/icon/todo");

    EXPECT_EQ(tableVec[0].name, "OutLine");
    EXPECT_EQ(tableVec[1].name, "ToDO");

    EXPECT_EQ(tableVec[0].currentView, 3);
    EXPECT_EQ(tableVec[1].currentView, 4);

    EXPECT_EQ(tableVec[0].defaultView, 6);
    EXPECT_EQ(tableVec[1].defaultView, 7);

    EXPECT_EQ(tableVec[0].hotkey, "Ctrl+N");
    EXPECT_EQ(tableVec[1].hotkey, "Ctrl+T");
}

TEST(Config, TabBarModify) {
    QFile::remove("../src/test/tab_bar_modify_test.xml");
    QFile::remove("../src/test/tab_bar_modify_test.xml_back");
    QFile::copy("../src/test/tab_bar_read_test.xml", "../src/test/tab_bar_modify_test.xml");
    Config* config = Config::getConfig("../src/test/tab_bar_modify_test.xml");
    EXPECT_EQ(config->isValid(), true);

    TabBarNode* node = config->getTabBarNode();
    auto tableVec = node->getTabBarConfig();
    ASSERT_EQ(tableVec.length(), 2);

    tableVec[0].position = 4;
    tableVec[0].pinTab = !tableVec[0].pinTab;
    tableVec[0].showView = !tableVec[0].showView;
    tableVec[0].isDefault = !tableVec[0].isDefault;
    tableVec[0].lockDefault = !tableVec[0].lockDefault;
    tableVec[0].iconPath = ":/IcOn/OuTLiNe";
    tableVec[0].name = "WoRkSpAcE";
    tableVec[0].currentView = 4;
    tableVec[0].defaultView = 7;
    tableVec[0].hotkey = "Alt+N";

    ASSERT_EQ(node->updateTableBarTable(tableVec[0]), true);

    tableVec = node->getTabBarConfig();
    ASSERT_EQ(tableVec.length(), 2);

    EXPECT_EQ(tableVec[0].position, 4);
    EXPECT_EQ(tableVec[0].pinTab, false);
    EXPECT_EQ(tableVec[0].showView, false);
    EXPECT_EQ(tableVec[0].isDefault, false);
    EXPECT_EQ(tableVec[0].lockDefault, true);
    EXPECT_EQ(tableVec[0].iconPath, ":/IcOn/OuTLiNe");
    EXPECT_EQ(tableVec[0].name, "WoRkSpAcE");
    EXPECT_EQ(tableVec[0].currentView, 4);
    EXPECT_EQ(tableVec[0].defaultView, 7);
    EXPECT_EQ(tableVec[0].hotkey, "Alt+N");


    TabBarNode::TabBarTable table;
    ASSERT_EQ(node->updateTableBarTable(table), false);
    ASSERT_EQ(node->addTabBarTable(table), true);
    ASSERT_EQ(node->removeTabBarTable(table), true);
    ASSERT_EQ(node->removeTabBarTable(table), false);


    table.iconPath = ":/icon/ABC";
    table.name = "Life";
    table.hotkey = "Alt+3";
    ASSERT_EQ(node->addTabBarTable(table), true);
    tableVec = node->getTabBarConfig();
    ASSERT_EQ(tableVec.length(), 3);
    ASSERT_EQ(config->save(), true);

    config = Config::getConfig("../src/test/tab_bar_modify_test.xml");
    EXPECT_EQ(config->isValid(), true);

    node = config->getTabBarNode();
    tableVec = node->getTabBarConfig();
    ASSERT_EQ(tableVec.length(), 3);

    QFile::remove("../src/test/tab_bar_modify_test.xml");
    QFile::remove("../src/test/tab_bar_modify_test.xml_back");
}

TEST(Config, ViewTree) {
    Config* config = Config::getConfig("../src/test/tab_bar_read_test.xml");
    EXPECT_EQ(config->isValid(), true);
    ViewTreeNode* node = config->getViewTreeNode();
    auto tableVec = node->getViewTableConfig();
    ASSERT_EQ(tableVec.length(), 1);

    EXPECT_EQ(tableVec[0].position, 1);
    EXPECT_EQ(tableVec[0].isFolder, true);
    EXPECT_EQ(tableVec[0].hide, false);
    EXPECT_EQ(tableVec[0].name, "To-Do");
    EXPECT_EQ(tableVec[0].icon, ":/icon/todo");

    ViewTreeNode::ViewTable::Counters countes{true, true, "Overdue", "with subtasks"};
    EXPECT_EQ(tableVec[0].counters, countes);

    ViewTreeNode::ViewTable::Filter::Show show{"Available", "Yes", {"Recent", "3d"}};
    EXPECT_EQ(tableVec[0].filter.show, show);

    ViewTreeNode::ViewTable::Filter::Text text{true, true, false, false, "ABC"};
    EXPECT_EQ(tableVec[0].filter.text, text);

    ViewTreeNode::ViewTable::Filter::Contexts context{false, "and", {"@Home", "@Office"}};
    EXPECT_EQ(tableVec[0].filter.contexts, context);

    ViewTreeNode::ViewTable::Filter::Flags flag{false, "and", {"red", "green"}};
    EXPECT_EQ(tableVec[0].filter.flags, flag);

    ViewTreeNode::ViewTable::Filter::StartDate startDate{false, {"functions", "Today-3"}, {"functions", "Today+5"}};
    EXPECT_EQ(tableVec[0].filter.startDate, startDate);

    ViewTreeNode::ViewTable::Filter::GroupSort groupSort{{true, true, false, {{"ascending", "Computed-Score"},{"ascending", "Effort"},{"ascending", "Flag"},{"ascending", "Project"}}},
                                                         {false,{{"ascending", "Computed-Score"},{"ascending", "Effort"},{"ascending", "Flag"},{"ascending", "Project"}}}};
    EXPECT_EQ(tableVec[0].filter.groupSort, groupSort);


    ViewTreeNode::AdvancedFilter advFlt{true,
                                        {
            {false, false, "CompletedDateTime", "410", "on", "TDateTime", "2021-10-10T23:22:00", "AND", {}},
            {true, true, "FolderName", "510", "contains", "string", "watch", "AND",
                {
                    {false, true, "OccurrencesLeft", "0", "=", "Integer", "fd", "AND",
                        {
                            {true, false, "Contexts", "1110", "contains (consider open/closed)", "string", "@HomeCalls;@HomeComputer;@Office", "OR"}
                        }
                    }
                }
            },
            {false, false, "Goal", "701", "=", "Integer", "Month", "OR", {}}
                                        }
                                       };

    EXPECT_EQ(tableVec[0].filter.advFlt, advFlt);

}

#endif
