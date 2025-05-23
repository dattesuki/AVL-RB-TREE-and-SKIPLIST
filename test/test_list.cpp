//UNN
//Litvyakov D. D.
//

#include "skiplist.h"
#include <gtest.h>

TEST(skiplist, test_check)
{
	EXPECT_EQ(1,1);
}

TEST(skiplist, add_find) {
    SkipList<int> sl(0.5);
    EXPECT_FALSE(sl.find(42));
    EXPECT_TRUE(sl.add(42, 100));
    EXPECT_TRUE(sl.find(42));
    EXPECT_FALSE(sl.add(42, 200));
}

TEST(skiplist, remove) {
    SkipList<int> sl(0.5);
    EXPECT_TRUE(sl.add(100, 999));
    EXPECT_TRUE(sl.find(100));
    EXPECT_TRUE(sl.remove(100));
    EXPECT_FALSE(sl.find(100));
    EXPECT_FALSE(sl.remove(100));
}

TEST(skiplist, add2) {
    SkipList<int> sl(0.5);
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(sl.add(i, i * 2));
    }
    EXPECT_EQ(sl.size(), 100);

    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(sl.add(i, i * 2));
    }
    EXPECT_EQ(sl.size(), 100);

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(sl.find(i));
    }
    EXPECT_EQ(sl.size(), 100);
    EXPECT_FALSE(sl.find(100));
    EXPECT_FALSE(sl.find(-1));
}

TEST(skiplist, remove_size) {
    SkipList<int> sl(0.5);
    for (int i = 9; i >= 0; --i) {
        EXPECT_TRUE(sl.add(i, i * 10));
    }

    EXPECT_EQ(sl.size(), 10);

    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(sl.remove(i));
    }

    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(sl.find(i));
    }

    EXPECT_EQ(sl.size(), 0);
}

