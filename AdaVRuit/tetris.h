#ifndef TETRIS_H_
#define TETRIS_H_

#include "main.h"

/* Konstanten */

#define GAME_SPEED 3
#define FADE_OUT_SPEED 60

/* Funktionen */



struct figure rotate(struct figure obj, uint8_t board[16]);
struct figure moveLeft(struct figure obj, uint8_t board[16]);
struct figure moveRight(struct figure obj, uint8_t board[16]);

void output(struct figure obj, uint8_t board[16]);
void printScore(uint8_t score);

struct figure newObj(uint16_t rand);

struct figure init_Quad(uint8_t newRotState);
struct figure init_L(uint8_t newRotState);
struct figure init_L_inv(uint8_t newRotState);
struct figure init_I(uint8_t newRotState);
struct figure init_Z(uint8_t newRotState);
struct figure init_Z_inv(uint8_t newRotState);
struct figure init_T(uint8_t newRotState);

uint16_t checkRows(uint8_t board[16], uint16_t score);
void lockObj(uint8_t board[16], struct figure obj);

void playTetris();


#endif /* TETRIS_H_*/
