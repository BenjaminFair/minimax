#include <stdlib.h>

#include "minimax.h"
#include "tree.h"

struct MMGame {
    void *(*get_moves)(void *, int *);
    void (*free_moves)(void *);
    void (*apply_move)(void *, void *);
    size_t move_size;
    int  (*value)(void *);
    
    int player;
    
    Node *root;
};

typedef struct {
    void *state;
    void *moves;
} NodeData;

int negamax(Node *node, int depth, int player, int *best) {
    if(depth == 0

MMGame *mm_setup_game(void *state, void *(*get_moves)(void *, int *),
        void (*free_moves)(void *), void (*apply_move)(void *, void *),
        size_t move_size, int (*value)(void *)) {
    MMGame *g = (MMGame *) malloc(sizeof(MMGame));
    
    g->get_moves  = get_moves;
    g->free_moves = free_moves;
    g->apply_move = apply_move;
    g->move_size  = move_size;
    g->value = value;
    
    g->player = 1;
    
    g->root = make_node(state);
    
    return g;
}

void mm_free_game(MMGame *g) {
    free_tree(g->root);
    free(g);
}

void *mm_suggest_move(MMGame *g, int depth) {
    mm_fill_tree(MMGame *g);
    
    int best;
    negamax(g->root, depth, g->player, &best);
    char *moves =  get_data
}

void mm_register_move(MMGame *g, void *m) {
}