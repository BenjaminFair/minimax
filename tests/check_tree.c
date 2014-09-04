#include <stdlib.h>
#include <check.h>
#include "../src/tree.h"

START_TEST (make_free_node) {
    Node *node = make_node(NULL);
    free_node(node);
} END_TEST

START_TEST (node_init_children) {
    Node *node = make_node(NULL);
    ck_assert_ptr_eq(get_children(node), NULL);
    ck_assert_int_eq(get_num_children(node), 0);
    free_node(node);
} END_TEST

void test_set_children(int num_children) {
    Node *node = make_node(NULL);
    Node **children = make_children(num_children);
    set_children(node, children, num_children);
    ck_assert_ptr_eq(get_children(node), children);
    ck_assert_int_eq(get_num_children(node), num_children);
    free_node(node);
    free_children(children, num_children);
}

START_TEST (node_set_children_1) {
    test_set_children(1);
} END_TEST

START_TEST (node_set_children_0) {
    const int num_children = 0;
    Node *node = make_node(NULL);
    Node **children = make_children(num_children);
    set_children(node, children, num_children);
    ck_assert_ptr_eq(get_children(node), NULL);
    ck_assert_int_eq(get_num_children(node), num_children);
    free_node(node);
    free_children(children, num_children);
} END_TEST

START_TEST (node_set_children_20) {
    test_set_children(20);
} END_TEST

START_TEST (make_free_children_1) {
    Node **children = make_children(1);
    free_children(children, 1);
} END_TEST

START_TEST (make_free_children_0) {
    Node **children = make_children(0);
    ck_assert_ptr_eq(children, NULL);
    free_children(children, 0);
} END_TEST

START_TEST (make_free_children_20) {
    Node **children = make_children(20);
    free_children(children, 20);
} END_TEST

START_TEST (free_tree_null) {
    free_tree(NULL);
} END_TEST

START_TEST (free_tree_node) {
    Node *node = make_node(NULL);
    free_tree(node);
} END_TEST

START_TEST (free_tree_1_child) {
    Node *node = make_node(NULL);
    Node **children = make_children(1);
    set_children(node, children, 1);
    free_tree(node);
} END_TEST

START_TEST (free_tree_0_children) {
    Node *node = make_node(NULL);
    Node **children = make_children(0);
    set_children(node, children, 0);
    free_tree(node);
} END_TEST

START_TEST (free_tree_20_children) {
    Node *node = make_node(NULL);
    Node **children = make_children(20);
    set_children(node, children, 20);
    free_tree(node);
} END_TEST

START_TEST (free_tree_depth_3_width_1) {
    Node *root = make_node(NULL);
    Node **children1 = make_children(1);
    Node **children2 = make_children(1);
    
    set_children(root, children1, 1);
    set_children(children1[0], children2, 1);
    
    free_tree(root);
} END_TEST

START_TEST (free_tree_depth_3_width_20) {
    Node *root = make_node(NULL);
    Node **children1 = make_children(20);
    set_children(root, children1, 20);
    
    int i;
    for(i = 0; i < 20; i++) {
        Node **children2 = make_children(20);
        set_children(children1[i], children2, 20);
    }
        
    free_tree(root);
} END_TEST

START_TEST (set_get_data) {
    int *data_in = malloc(sizeof(int));
    *data_in = 42;
    
    Node *node = make_node(data_in);
    
    int *data_out = (int *) get_data(node);
    ck_assert_ptr_eq(data_out, data_in);
} END_TEST

Suite *tree_suite() {
    Suite *s = suite_create("Tree");
    
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, make_free_node);
    tcase_add_test(tc_core, node_init_children);
    tcase_add_test(tc_core, node_set_children_1);
    tcase_add_test(tc_core, node_set_children_0);
    tcase_add_test(tc_core, node_set_children_20);
    tcase_add_test(tc_core, make_free_children_1);
    tcase_add_test(tc_core, make_free_children_0);
    tcase_add_test(tc_core, make_free_children_20);
    tcase_add_test(tc_core, free_tree_null);
    tcase_add_test(tc_core, free_tree_node);
    tcase_add_test(tc_core, free_tree_1_child);
    tcase_add_test(tc_core, free_tree_0_children);
    tcase_add_test(tc_core, free_tree_20_children);
    tcase_add_test(tc_core, free_tree_depth_3_width_1);
    tcase_add_test(tc_core, free_tree_depth_3_width_20);
    tcase_add_test(tc_core, set_get_data);
    suite_add_tcase(s, tc_core);
    
    return s;
}

int main() {
    Suite *tree = tree_suite();
    SRunner *sr = srunner_create(tree);
    srunner_run_all(sr, CK_VERBOSE);
    int num_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}