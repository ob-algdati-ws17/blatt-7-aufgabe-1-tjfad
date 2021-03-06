#include "testAvlTree.h"

using namespace std;

// empty tree

TEST(AvlTreeTest, Empty_Tree) {
    AvlTree b;
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

// empty tree

TEST(AvlTreeTest, Predecessor) {
    AvlTree b;

    b.insert(100);
    b.insert(50);
    b.insert(70);
    b.insert(150);
    b.insert(120);
    b.insert(170);
/*
    *       120
    *     /     \
    *    70     150
    *   /  \   /   \
    *  50 100      170

    */
    int pre = b.getSymPredecessor(130);
    EXPECT_EQ(120,pre);
    pre = b.getSymPredecessor(180);
    EXPECT_EQ(170,pre);
    pre = b.getSymPredecessor(70);
    EXPECT_EQ(50,pre);
    pre = b.getSymPredecessor(100);
    EXPECT_EQ(70,pre);
    pre = b.getSymPredecessor(40);
    EXPECT_EQ(0,pre);
}

TEST(AvlTreeTest, Successor) {
    AvlTree b;

    b.insert(100);
    b.insert(50);
    b.insert(70);
    b.insert(150);
    b.insert(120);
    b.insert(170);

    int pre = b.getSymSuccessor(130);
    EXPECT_EQ(150,pre);
   // pre = b.getSymSuccessor(180);
  //  EXPECT_EQ(0,pre);
    pre = b.getSymSuccessor(70);
    EXPECT_EQ(100,pre);
    pre = b.getSymSuccessor(100);
    EXPECT_EQ(120,pre);
    pre = b.getSymSuccessor(40);
    EXPECT_EQ(50,pre);
    pre = b.getSymSuccessor(700);
    EXPECT_EQ(0,pre);
}
// insert and search

TEST(AvlTreeTest, Inserts_Rotations) {
    AvlTree b;

    b.insert(100);
    b.insert(50);
    b.insert(70);

    /*
     *      70
     *     /  \
     *    50  100
     */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(70,50,100));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(50,70,100));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(50,100,70));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0));


    b.insert(150);
    b.insert(120);
    /*
     *      70
     *     /  \
     *    50  120
     *       /   \
     *     100   150
     */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(70,50,120,100,150));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(50,70,100,120,150));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(50,100,150,120,70));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(1,0,0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,1,0,0,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,1));

    b.insert(170); //rl(70)
    /*
    *       120
    *     /     \
    *    70     150
    *   /  \   /   \
    *  50 100      170

    */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,50,100,150,170));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(50,70,100,120,150,170));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(50,100,70,170,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0,0,0,0,1,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,0,1,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,1,0));
}

TEST(AvlTreeTest, Remove_Leaf_No_Height_Change) {
    AvlTree b;

    b.insert(100);
    b.insert(50);
    b.insert(70);
    b.insert(150);
    b.insert(120);
    b.insert(170);
    /*
    *       120
    *     /     \
    *    70     150
    *   /  \   /   \
    *  50 100      170

    */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,50,100,150,170));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(50,70,100,120,150,170));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(50,100,70,170,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0,0,0,0,1,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,0,1,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,1,0));

    b.remove(170);
    /*
   *       120
   *     /     \
   *    70     150
   *   /  \
   *  50 100
   */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,50,100,150));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(50,70,100,120,150));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(50,100,70,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(-1,0,0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,-1,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,-1));

    b.remove(50);
    /*
   *       120
   *     /     \
   *    70     150
   *     \
   *     100
   */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,100,150));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(70,100,120,150));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(100,70,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(-1,1,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(1,0,-1,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,1,0,-1));

    b.remove(100);
    /*
   *       120
   *     /     \
   *    70     150
   *
   *
   */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,150));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(70,120,150));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(70,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0));

    b.remove(70);
    b.remove(150);
    /*
   *       120
   *
   *
   */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(120));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0));

    b.remove(120);
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}


TEST(AvlTreeTest, Remove_Leaf_Height_Changes) {
    AvlTree b;

    b.insert(100);
    b.insert(50);
    b.insert(70);
    b.insert(150);
    b.insert(120);
    b.insert(170);
    b.insert(40);
    b.insert(60);
    /*
    *            120
    *          /     \
    *         70     150
    *        /  \   /   \
    *       50 100      170
    *      /  \
    *     40  60
    */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,50,40,60,100,150,170));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(40,50,60,70,100,120,150,170));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(40,60,50,100,70,170,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(-1,-1,0,0,0,0,1,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,-1,0,-1,1,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,-1,0,1,-1));
    /*Remove 170  RR120 in upout
    *
    *
    *          70
    *        /    \
    *       50    120
    *      /  \   /  \
    *     40  60 100 150
    */
    b.remove(170);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(70,50,40,60,120,100,150));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(40,50,60,70,100,120,150));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(40,60,50,100,150,120,70));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0,0,0,0,0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,0,0,0,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,0,0,0));

    b.remove(40);
    b.remove(60);
    b.remove(50);
    /*Remove 40,60,50  LR70 in upout
    *
    *
    *         120
    *        /   \
    *       70   150
    *      /  \
    *        100
    */
    b.remove(170);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,100,150));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(70,100,120,150));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(100,70,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(-1,1,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(1,0,-1,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,1,0,-1));

}
TEST(AvlTreeTest, Remove_InnerNodeWithOneSon_No_Height_Change) {
    AvlTree b;
//i100i50i70i150i120i170i40i60i130i160
    b.insert(100);
    b.insert(50);
    b.insert(70);
    b.insert(150);
    b.insert(120);
    b.insert(170);
    b.insert(40);
    b.insert(60);
    b.insert(130);
    b.insert(160);
    /*
    *            120
    *          /     \
    *         70     150
    *        /  \   /   \
    *       50 100 130  170
    *      /  \        /
    *     40  60     160
    */
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,50,40,60,100,150,130,170,160));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(40,50,60,70,100,120,130,150,160,170));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(40,60,50,100,70,130,160,170,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0,-1,0,0,0,0,1,0,-1,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,-1,0,0,0,1,0,-1));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,-1,0,0,-1,1,0));
    /*Remove 170 170->160remove 160
    *
    *
    *            120
    *          /     \
    *         70     150
    *        /  \   /   \
    *       50 100 130  160
    *      /  \
    *     40  60
    */
    b.remove(170);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(120,70,50,40,60,100,150,130,160));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(40,50,60,70,100,120,130,150,160));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(40,60,50,100,70,130,160,150,120));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(-1,-1,0,0,0,0,0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,-1,0,-1,0,0,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,-1,0,0,0,-1));
    /*Remove 130
    * Remove 150 150->160  ->  RR120
    *
    *
    *
    *          70
    *        /    \
    *       50    120
    *      /  \   /  \
    *     40  60 100 160
    */
    b.remove(130);
    b.remove(150);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(70,50,40,60,120,100,160));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(40,50,60,70,100,120,160));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(40,60,50,100,160,120,70));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(0,0,0,0,0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,0,0,0,0,0,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,0,0,0));
    /*Remove 60
   * Remove 50 LR70
   *
   *          70
    *        /   \
    *       40   120
    *            /  \
    *          100  160
   */
    b.remove(60);
    b.remove(50);
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(70,40,120,100,160));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(40,70,100,120,160));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(40,100,160,120,70));
    //testing balances
    EXPECT_THAT(*b.bPreorder(), testing::ElementsAre(1,0,0,0,0));
    EXPECT_THAT(*b.bInorder(), testing::ElementsAre(0,1,0,0,0));
    EXPECT_THAT(*b.bPostorder(), testing::ElementsAre(0,0,0,0,1));


}

TEST(AvlTreeTest, One_Node) {
    AvlTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(12213));
}

TEST(AvlTreeTest, Two_Nodes) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
}

TEST(AvlTreeTest, Three_Nodes) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    b.insert(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215, 123712));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213, 123712));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 123712, 12213));
}

// insert, remove and search

TEST(AvlTreeTest, One_Node_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123));
    EXPECT_FALSE(b.search(-123));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

TEST(AvlTreeTest, Two_Nodes_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215));
    b.remove(215);
    EXPECT_FALSE(b.search(215));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}

TEST(AvlTreeTest, Three_Nodes_Insert_Remove) {
    AvlTree b;
    b.insert(12213);
    b.insert(215);
    b.insert(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_TRUE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215, 123712));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213, 123712));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 123712, 12213));
    b.remove(123712);
    EXPECT_TRUE(b.search(12213));
    EXPECT_FALSE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(12213, 215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215, 12213));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215, 12213));
    b.remove(12213);
    EXPECT_FALSE(b.search(12213));
    EXPECT_FALSE(b.search(123712));
    EXPECT_TRUE(b.search(215));
    EXPECT_THAT(*b.preorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.inorder(), testing::ElementsAre(215));
    EXPECT_THAT(*b.postorder(), testing::ElementsAre(215));
    b.remove(215);
    EXPECT_FALSE(b.search(215));
    EXPECT_EQ(nullptr, b.preorder());
    EXPECT_EQ(nullptr, b.inorder());
    EXPECT_EQ(nullptr, b.postorder());
}
