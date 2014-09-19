// Implementation of the subtraction game with k=3 and n=21

#define K 3
#define N 21

#include <stdio.h>
#include <stdlib.h>

#include "minimax.h"

typedef struct {
    int stones;
    int player;
} GameState;

typedef int Move;

void *get_moves(void *s, int *num_moves) {
    GameState *state = (GameState *) s;
    *num_moves = 0;
    if(state->stones > K) {
        *num_moves = K;
    } else {
        *num_moves = state->stones;
    }
    
    Move *moves = (Move *) malloc(sizeof(Move) * *num_moves);
    int i;
    for(i = 0; i < *num_moves; i++) {
        moves[i] = i+1; // can take 1,2,...,k
    }
    
    return (void *) moves;
}

void free_moves(void *moves) {
    free(moves);
}

void apply_move(void *s, void *m) {
    GameState *state = (GameState *) s;
    int move = *((int *) m);
    if(move > state->stones) {
        state->stones = 0;
    } else {
        state->stones -= move;
    }
    state->player ^= 1;
}

int check_win(void *s) {
    GameState *state = (GameState *) s;
    if(state->stones == 0) { // there's a winner
        return state->player ^ 1; // it's the other player
    } else {
        return -1; // no winner
    }
}

int value(void *s) {
    int win = check_win(s);
    
    if(win == -1) {
        return 0;
    } else if(win == 0) { // maximising player won
        return 1;
    } else { // minimising player won
        return -1;
    }
}

void print_state(GameState *state) {
    printf("There are %2d stones left.  How many will Player %d take? ", state->stones, state->player+1);
}

void print_move(void *move) {
    printf("%d\n", *((int *) move));
}

void *get_player_move() {
    int *move = (int *) malloc(sizeof(int));
    scanf("%d", move);
    while(*move < 1 || *move > 3) {
        printf("Improper move, please try again: ");
        scanf("%d", move);
    }
    return (void *) move;
}

int main() {
    printf("Enter 1, 2, or 3 to take that many stones.  The player to take the last stone wins.\n");
    
    GameState *state = (GameState *) malloc(sizeof(GameState));
    state->stones = N;
    state->player = 0;
    
    MMGame *g = mm_setup_game((void *) state, get_moves, free_moves, apply_move, sizeof(Move), value);
    
    while(check_win(state) == -1) { // keep going until someone wins
        print_state(state);
        if(state->player == 0) { // computer's move
            void *m = mm_suggest_move(g, -1);
            print_move(m);
            apply_move(state, m);
            free_moves(m);
        } else { // human's move
            void *m = (Move *) get_player_move();
            apply_move(state, m);
            mm_register_move(g, m);
            free_moves(m);
        }
    }
    
    printf("Player %d took the last stone and won the game!\n", check_win(state)+1);
    
    mm_free_game(g);
    
    return 0;
}
    
