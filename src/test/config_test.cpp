#include <gtest/gtest.h>
#include "configure/config.h"
#include "configure/tab_bar_node.h"

#ifdef ENABLE_TEST

TEST(Config, TabBar)
{
    Config config("D:/msys64/home/Zelonge/Workspace/MyLife-UI/doc/config.xml");

    EXPECT_EQ(config.isValid(), true);

}

#endif
