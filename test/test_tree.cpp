//UNN
//Litvyakov D. D.
//

#include "tree.h"
#include <gtest.h>

TEST(AVLTree, constructor) {
    AVLTree<int> tree(10, 100);
    EXPECT_TRUE(tree.find(10));
}

TEST(AVLTree, insert) {
    AVLTree<std::string> tree(1, "first");

    EXPECT_TRUE(tree.add(2, "second"));
    EXPECT_TRUE(tree.add(3, "third"));
    EXPECT_FALSE(tree.add(1, "and first")); 
}

TEST(AVLTree,find) {
    AVLTree<double> tree(5, 3.);
    tree.add(3, 2.);
    tree.add(7, 1.);

    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(3));
    EXPECT_TRUE(tree.find(7));
    EXPECT_FALSE(tree.find(2)); 
}

TEST(AVLTree, remove) {
    AVLTree<char> tree(10, 'A');
    tree.add(5, 'B');
    tree.add(15, 'C');

    EXPECT_TRUE(tree.remove(5));
    EXPECT_FALSE(tree.find(5));
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(15));

    EXPECT_FALSE(tree.remove(99)); 
}

TEST(AVLTree, test_w_balance) {
    AVLTree<int> tree(10, 1);

    tree.add(20, 2);
    tree.add(30, 3); 
    tree.add(25, 4);
    tree.add(5, 5);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_TRUE(tree.find(30));
    EXPECT_TRUE(tree.find(25));
    EXPECT_TRUE(tree.find(5));
}

TEST(AVLTree, destructor) {
    AVLTree<int>* tree = new AVLTree<int>(1, 1);
    tree->add(2, 2);
    tree->add(3, 3);

    delete tree; 
}

TEST(AVLTree, test_add_remove) {
    AVLTree<int> tree(50, 50);
    for (int i = 0; i < 100; i += 10) {
        if (i != 50) {
            tree.add(i, i);
        }
    }

    EXPECT_TRUE(tree.remove(20));
    EXPECT_TRUE(tree.remove(70));

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(90));
    EXPECT_FALSE(tree.find(20));
    EXPECT_FALSE(tree.find(70));
}