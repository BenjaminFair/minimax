#include <stdlib.h>
#include <check.h>
#include "../src/tree.h"

START_TEST (make_free_node) {
    Node *node = make_node(NULL);
    free_node(node);
} END_TEST

/*START_TEST (make_free_children_1) {
    Node **children*/

Suite *tree_suite() {
    Suite *s = suite_create("Tree");
    
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, make_free_node);
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