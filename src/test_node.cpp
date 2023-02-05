#include <gtest/gtest.h>

#include "test_cases.hpp"
#include "rule2022.hpp"

using namespace rule2022;

void add_child_node(std::shared_ptr<Node> &root, const moveVec_t history)
{
    std::shared_ptr<Node> child;
    auto p = root;
    for (auto m : history)
    {
        try
        {
            child = p->select_child(m);
        }
        catch (const std::out_of_range &e)
        {
            child = p->gen_child(m);
            child->priority = p->child_move_set.size();
            p->children.push_back(child);
        }
        p = child;
    }
}

void gen_test_case_1(std::shared_ptr<Node> &root)
{
    std::vector<moveVec_t> hist_list = {
        {make_move("5352"), make_move("3637"), make_move("5242"), make_move("2042"), make_move("3537")},
        {make_move("5352"), make_move("3637"), make_move("5242"), make_move("3747")},
        {make_move("5352"), make_move("3637"), make_move("5242"), make_move("2042")},
        {make_move("5352"), make_move("3637"), make_move("3537"), make_move("5652")},
        {make_move("5352"), make_move("3637"), make_move("0001")},
        {make_move("5352"), make_move("5652"), make_move("3536")},
        {make_move("3536"), make_move("5636"), make_move("5352")}};

    for (auto h : hist_list)
    {
        add_child_node(root, h);
    }
}

// 案例二
void gen_test_case_2(std::shared_ptr<Node> &root)
{
    std::vector<moveVec_t> hist_list = {
        {make_move("7657"), make_move("2757"), make_move("7079"), make_move("1914"), make_move("1014"), make_move("6779")},
        {make_move("7657"), make_move("2757"), make_move("7079"), make_move("6779")},
        {make_move("7657"), make_move("4857"), make_move("7079"), make_move("6779")},
        {make_move("7657"), make_move("4939"), make_move("7079"), make_move("6779")},
        {make_move("7668"), make_move("2868"), make_move("7079")},
        {make_move("7668"), make_move("4939"), make_move("7079")}};

    for (auto h : hist_list)
    {
        add_child_node(root, h);
    }
}

TEST(NodeBase, Nodex01)
{
    auto root = Node::create({});
    gen_test_case_1(root);
    EXPECT_TRUE(root->is_root());
    EXPECT_EQ(root->children.size(), 2);

    // 指向的父节点相同
    auto c11 = root->children[0];
    auto c12 = root->children[1];

    EXPECT_EQ(c11->parent, c12->parent);
    EXPECT_EQ(c11->parent, root);
    EXPECT_EQ(c11->parent, root);

    EXPECT_EQ(c11->path(), "root -> 5352");
    EXPECT_EQ(c12->path(), "root -> 3536");

    auto c21 = c11->children[0];
    EXPECT_EQ(c21->path(), "root -> 5352 -> 3637");
}

// 偶数深度节点更新
TEST(NodeBase, Nodex02x1)
{
    auto root = Node::create({});
    gen_test_case_1(root);

    auto hist = {make_move("5352"), make_move("5652"), make_move("3536")};
    auto c = root->select_posterity(hist);

    EXPECT_EQ(c->path(), "root -> 5352 -> 5652 -> 3536");

    c->visit_count = 1;
    c->pass = true;
    c->value = 0.8f;

    auto c2 = c->parent;
    EXPECT_EQ(c2->path(), "root -> 5352 -> 5652");

    c2->update();

    // c2->view_detail();

    // 深度为偶数的节点，其任一子节点通过，节点通过
    EXPECT_TRUE(c2->pass);
    EXPECT_EQ(c2->value, c->value);
}

// 奇数深度节点更新
TEST(NodeBase, Nodex02x2)
{
    auto root = Node::create({});
    gen_test_case_1(root);

    auto hist1 = {make_move("5352"), make_move("3637"), make_move("5242"), make_move("3747")};
    auto hist2 = {make_move("5352"), make_move("3637"), make_move("5242"), make_move("2042")};

    auto c41 = root->select_posterity(hist1);
    auto c42 = root->select_posterity(hist2);

    EXPECT_EQ(c41->path(), "root -> 5352 -> 3637 -> 5242 -> 3747");
    EXPECT_EQ(c42->path(), "root -> 5352 -> 3637 -> 5242 -> 2042");

    c41->visit_count = 1;
    c41->pass = true;
    c41->value = 0.5f;

    c42->visit_count = 1;
    c42->pass = true;
    c42->value = 0.8f;

    auto c3 = c41->parent;
    EXPECT_EQ(c3->path(), "root -> 5352 -> 3637 -> 5242");

    c3->update();

    // c42->view_tree();

    // 深度为奇数的节点，只有全部子节点通过，节点通过
    EXPECT_TRUE(c3->pass);
    // 取子节点中的最小值
    EXPECT_EQ(c3->value, c41->value);
}

// 选择子节点
TEST(NodeBase, Nodex03)
{
    auto root = Node::create({});
    gen_test_case_1(root);

    auto hist1 = {make_move("5352"), make_move("3637")};
    auto hist2 = {make_move("5352"), make_move("3637"), make_move("0001")};

    auto c21 = root->select_posterity(hist1);
    // c21->view_detail();
    EXPECT_EQ(c21->children.size(), 3);

    // c21->delete_child(hist2);
    // EXPECT_EQ(c21->children.size(), 2);
}

// 上N级祖先节点
TEST(NodeBase, Nodex04)
{
    auto root = Node::create({});
    gen_test_case_1(root);

    auto hist = {make_move("5352"), make_move("3637"), make_move("0001")};

    auto c31 = root->select_posterity(hist);

    auto c21 = c31->nth_predecessor(1);
    EXPECT_EQ(c21->path(), "root -> 5352 -> 3637");

    auto c11 = c31->nth_predecessor(2);
    EXPECT_EQ(c11->path(), "root -> 5352");

    auto c00 = c31->nth_predecessor(3);
    EXPECT_EQ(c00->path(), "root");
}

// 查询节点的根节点
TEST(NodeBase, Nodex06)
{
    moveVec_t hist = {make_move("7170"), make_move("4150"), make_move("7050")};
    std::vector<std::shared_ptr<Node>> vs;
    auto root = Node::create({});
    auto p = root;
    vs.push_back(p);
    for (size_t i = 0; i < hist.size(); i++)
    {
        auto c = p->gen_child(hist[i]);
        p->children.push_back(c);
        vs.push_back(c);
        std::swap(p, c);
    }

    // 根节点的根节点指向本身
    EXPECT_EQ(root->root_node(), root);

    EXPECT_EQ(vs[3]->root_node(), root);

    EXPECT_EQ(vs[3]->root_node()->path(), "root");
    EXPECT_EQ(vs[2]->root_node()->path(), "root");
    EXPECT_EQ(vs[1]->root_node()->path(), "root");
}

// 兄弟节点
TEST(NodeBase, Nodex07)
{
    auto root = Node::create({});
    gen_test_case_1(root);

    // 指向的父节点相同
    auto c11 = root->children[0];
    auto c12 = root->children[1];
    EXPECT_TRUE(c11->is_brother(c12));

    auto c21 = c11->children[0];
    auto c22 = c12->children[0];
    EXPECT_FALSE(c21->is_brother(c22));
}

TEST(NodeBase, Nodex09x1)
{
    std::vector<moveVec_t> hist_list = {
        {make_move("7657"), make_move("2757")},
        {make_move("7657"), make_move("4939")},
        {make_move("7668"), make_move("2868")},
        {make_move("7668"), make_move("4939")}};

    auto root = Node::create({});
    for (auto h : hist_list)
    {
        add_child_node(root, h);
    }
    auto m = root->get_root_tree_map();
    EXPECT_EQ(m.size(), 7);
}

TEST(NodeBase, Nodex09x2)
{
    auto root = Node::create({});
    auto m = root->get_root_tree_map();
    EXPECT_EQ(m.size(), 1);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}