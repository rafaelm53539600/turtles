/*

  Interface to turtle's model.

*/
#ifndef _TURTLES_H
#define _TURTLES_H

/* Structures for State of the Program */

#include <curses.h>


struct turtle {
  char dir;  // DOWN, LEFT, UP, RIGHT
  int power;
  int bullets;
  int x;
  int y;
  int score;
  int id;
};

typedef struct turtle TURTLE;

struct bullet {
  char dir;  // DOWN, LEFT, UP, RIGHT
  int active;
  int x;
  int y;
  TURTLE *owner ; // Hack to get it
};

typedef struct bullet BULLET;


#define MAX_PLAYERS  2
#define PLAYER1 0
#define PLAYER2 1

/*
    Usefull Macros in O(1), i.e , constants or expresion
    in constants
*/
#define DECREASE 1

#define SCORE_STR "%s %3d"


#define MOVESCORE  1
#define JEWELLSCORE 10
#define GLACESCORE 2

#define MAXPOWER  (ARENA_WIDTH/2)
#define MAXBULLET  1

#define DOWN  TURTLEDOWN
#define UP    TURTLEUP
#define LEFT  TURTLELEFT
#define RIGHT TURTLERIGHT


#define NUM_JEWELLS (COLS/5)
#define NUM_STONES (COLS)
#define NUM_GLACES (COLS/3)


#define SHIFT_HORZ(dir) ((dir)==LEFT ||(dir)==RIGHT )
#define SHIFT_VERT(dir) ((dir)==DOWN ||(dir)==UP )  

void TMbegin();
void TMend();
int TMMoveTurtle(TURTLE *turtle,int dir); 
int TMShootBullet(BULLET *bullet,TURTLE *turtle); 
void TMClock();
#endif  /* PG_TURTLES_H  */
