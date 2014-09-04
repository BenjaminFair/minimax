#ifndef __MINIMAX_H__
#define __MINIMAX_H__

typedef struct MMGame MMGame;

MMGame *mm_setup_game(void *state, void *(*get_moves)(void *, int *), void (*free_moves)(void *), void (*apply_move)(void *, void *), int (*value)(void *));
void mm_free_game(MMGame *g);

void *mm_suggest_move(MMGame *g);
void mm_register_move(MMGame *g, void *m);

#endif
