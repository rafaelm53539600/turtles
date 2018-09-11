#ifndef SCREEN_H
#define SCREEN_H
#include <stdlib.h>
#include "ttmdl.h"

#define UP_HELP1  "(UP)"
#define DOWN_HELP1  "(DOWN)"
#define LEFT_HELP1  "(LEFT)"
#define RIGHT_HELP1  "(RIGHT)"
#define SHOOT_HELP1  "(ENTER)"

#define UP_HELP2  "('W')"
#define DOWN_HELP2  "('X')"
#define LEFT_HELP2  "('A')"
#define RIGHT_HELP2  "('D')"
#define SHOOT_HELP2  "(SPACE)"


#define F1_OS  "F1-LD"
#define F2_OS  "F2-SV"
#define F3_OS  "F3-||"

#define POW_CONTROL  "(Pow) %2d"
#define POS_CONTROL  "(Pos) (%2d,%2d)"
#define BULLETS_CONTROL  "(Bullets) %d"
#define SCORE_CONTROL  "(Score) %3d"

#define ARENA_HEIGHT (2*(LINES/3))
#define ARENA_WIDTH (4*(COLS/5))
#define ARENA_START_Y ((LINES - ARENA_HEIGHT) / 2)
#define ARENA_START_X ((COLS - ARENA_WIDTH) / 2)  

#define CONTROL1_HEIGHT ((LINES/6))
#define CONTROL1_WIDTH (ARENA_WIDTH/2)
#define CONTROL1_START_Y (ARENA_START_Y - HELP1_HEIGHT) // 0!
#define CONTROL1_START_X (ARENA_START_X + ARENA_WIDTH/2)

#define CONTROL2_HEIGHT ((LINES/6))
#define CONTROL2_WIDTH (ARENA_WIDTH/2)
#define CONTROL2_START_Y (ARENA_START_Y - HELP1_HEIGHT) // 0!
#define CONTROL2_START_X (ARENA_START_X)


#define CONTROL_HEIGHT(p) ((p==PLAYER1)?CONTROL1_HEIGHT : CONTROL2_HEIGHT)
#define CONTROL_WIDTH(p) ((p==PLAYER1)?CONTROL1_WIDTH : CONTROL2_WIDTH)
#define CONTROL_START_Y(p) ((p==PLAYER1)?CONTROL1_START_Y : CONTROL2_START_Y)
#define CONTROL_START_X(p) ((p==PLAYER1)?CONTROL1_START_X : CONTROL2_START_X)

#define PLAYER1_START_Y (ARENA_START_Y + ARENA_HEIGHT - 2)
#define PLAYER1_START_X (ARENA_START_X+ARENA_WIDTH -2)
#define PLAYER2_START_Y (ARENA_START_Y +1)
#define PLAYER2_START_X (ARENA_START_X+1)

#define PLAYER_START_X(p) ((p==PLAYER1)?PLAYER1_START_X : PLAYER2_START_X)
#define PLAYER_START_Y(p) ((p==PLAYER1)?PLAYER1_START_Y : PLAYER2_START_Y)


#define SCORE_HEIGHT ((ARENA_HEIGHT)/2)
#define SCORE_WIDTH (COLS/10)
#define SCORE_START_Y (ARENA_START_Y + ((ARENA_HEIGHT - SCORE_HEIGHT)/2))
#define SCORE_START_X (ARENA_START_X - SCORE_WIDTH) // 0!


#define OS_HEIGHT ((ARENA_HEIGHT)/2) 
#define OS_WIDTH (COLS-ARENA_WIDTH-ARENA_START_X) 
#define OS_START_Y (ARENA_START_Y + ((ARENA_HEIGHT - OS_HEIGHT)/2))
#define OS_START_X (ARENA_START_X + ARENA_WIDTH) // 0!

#define HELP1_HEIGHT ((LINES/6))
#define HELP1_WIDTH (ARENA_WIDTH/2)
#define HELP1_START_Y ARENA_START_Y + ARENA_HEIGHT
#define HELP1_START_X (ARENA_START_X + ARENA_WIDTH/2)

#define HELP2_HEIGHT ((LINES/6))
#define HELP2_WIDTH (ARENA_WIDTH/2)
#define HELP2_START_Y ARENA_START_Y + ARENA_HEIGHT
#define HELP2_START_X (ARENA_START_X )


#define SCREEN_HEIGHT (CONTROL1_HEIGHT + ARENA_HEIGHT + CONTROL1_HEIGHT)
#define SCREEN_WIDTH (SCORE_WIDTH + ARENA_WIDTH)


#define TURTLEDOWN  'v'
#define TURTLEUP  '^'  // Any other idea?
#define TURTLELEFT  '<'
#define TURTLERIGHT  '>'

#define EMPTY    ' '
#define TURTLEJEWELL '@'
#define TURTLESTONE 'O'
#define TURTLEGLACE '*'
#define TURTLEBULLET '-'

#define BULLET_VERT '"'
#define BULLET_HORZ '='

#define WALL_VERT '|'
#define WALL_HORZ '-'
#define WALL_CORNER '+'


#define COLOR_PLAYER(p)  (p+1)   // i.e 0+1, since 0 is not valid in curses.

#include <curses.h>


void TSbegin();
void TSend();
int TSrotateMoveTurtle(const int oriy,const int oryx, const TURTLE *turtle);
void TSPlaceItem(char item);
void TSScreen(void) ;
int TSMoveBullet(const int oriy, const int orix, const BULLET *bullet);
int TSShootBullet(const BULLET *bullet);
void TSUpdateStatus(const TURTLE *turtle);
void TSUpdateRanking(void) ;


#endif  
