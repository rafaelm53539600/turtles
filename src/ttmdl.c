/*

  Implementation of turtles service functions.
  Modeling the state.

*/


#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ttmdl.h"
#include "ttscr.h"
#include "ttio.h"


/* State of the game. */

TURTLE * turtle[MAX_PLAYERS];
BULLET * bullet[MAX_PLAYERS];

void TMbegin()
{
  int i;
  for (i = 0 ; i < MAX_PLAYERS ; i++)
    {
      if ( (turtle[i] = malloc(sizeof(TURTLE))) == NULL )
	Error_Quit("couldn't allocate memory for turtle");
      if ( (bullet[i] = malloc(sizeof(BULLET))) == NULL )
	Error_Quit("couldn't allocate memory for bullet");

      /*  Set coordinates and dir for the turtles  */
      turtle[i]->y = PLAYER_START_Y(i);
      turtle[i]->x = PLAYER_START_X(i);
      turtle[i]->bullets = 1 ;
      turtle[i]->dir = (i == PLAYER1)? LEFT : RIGHT ;
      turtle[i]->power = MAXPOWER ;
      turtle[i]->score = 0 ;
      turtle[i]->id = i  ;

      bullet[i]->active=0;
      bullet[i]->owner = turtle[i];
    }
  
}

void TMend(void) {
  int i;
  for (i = 0 ; i < MAX_PLAYERS ; i++)
    {
      free(turtle[i]);
      free(bullet[i]);
    }
}


int TMRandomPowerCards(TURTLE *turtle)
{
  (turtle->power <  MAXPOWER) && (turtle->power+=5);
  TSUpdateStatus(turtle);
  return 1;
}


int TMRandomBulletCards(TURTLE *turtle)
{
  ((MAXPOWER - turtle->power) <= 5 ) && (turtle->bullets < MAXBULLET)  && (turtle->bullets++);   
  TSUpdateStatus(turtle);
  return 1;
}




/*  Moves/Rotates the turtle  */
int TMMoveTurtle(TURTLE *turtle, int d) {
  /*  Determine position of new turtle bit  */

  int dy,dx,ch;
  int y , x ;
  
  int oldy,oldx, olddir ; //former values
  
  olddir = turtle->dir;
  oldy = turtle->y;
  oldx = turtle->x;
  
#if DECREASE  
  turtle->power--;
#endif  
  turtle->dir = d;
  
  dx = turtle->x + SHIFT_HORZ(turtle->dir)*((turtle->dir==LEFT)?-1:1);
  dy = turtle->y + SHIFT_VERT(turtle->dir)*((turtle->dir==UP)?-1:1);
  ch = mvinch(dy,dx);
  // Compute new pos.
  switch (ch)
    {
    case TURTLESTONE: // Not trivial. loop.
      y = dy ;
      x = dx ;
      while ((ch=mvinch(y,x))==TURTLESTONE)  // THE ONLY LOOP IN GAME!
	{
	  x = x + SHIFT_HORZ(turtle->dir)*((turtle->dir==LEFT)?-1:1);
	  y = y + SHIFT_VERT(turtle->dir)*((turtle->dir==UP)?-1:1);
	}
      if (ch==EMPTY)
	{
	  turtle->y = dy ;
	  turtle->x = dx ;
	}
      break;
    case TURTLEJEWELL:
    case EMPTY :
      turtle->y = dy ;
      turtle->x = dx ;
      turtle->score += (ch==EMPTY)?MOVESCORE:JEWELLSCORE ;
      break;
    case TURTLEGLACE:
    case WALL_HORZ:
    case WALL_VERT:
      break;
    }

  TSrotateMoveTurtle(oldy,oldx,turtle);
  TSUpdateRanking();
  return 1;
}

// Event on time

int TMMoveBullet(BULLET *bullet) {
  int oldy, oldx;
  int dx, dy,ch;
  assert(bullet->active);
  dy = oldy = bullet->y;
  dx = oldx = bullet->x;
  // log mvprintw(LINES-2,0,"%c %d  %d", bullet->owner->dir,dy,dx);
  // Look ahead new pos.
  switch (bullet->dir)
    {
    case LEFT:
      dx--;
      break;
    case RIGHT:
      dx++;
      break;
    case DOWN:
      dy++;
      break; 
    case UP:
      dy--;
      break;
    }
  
  ch = (mvinch(dy,dx) & A_CHARTEXT) ;
  // React to next pos.
  switch (ch) {
  case TURTLEJEWELL:
    bullet->active = 0 ;
    break;
  case EMPTY :
    bullet->y = dy ;
    bullet->x = dx ;
    break;
  case TURTLEGLACE:
    bullet->y = dy ;
    bullet->x = dx ;
    bullet->owner->score += GLACESCORE;
    bullet->active = 0 ;
    break;
  case TURTLEUP:
  case TURTLEDOWN:
  case TURTLERIGHT:
  case TURTLELEFT:
    Quit(GAME_OVER); // turtle shooted!
  case WALL_HORZ:
  case WALL_VERT:
  case TURTLESTONE:
  default:  //
    bullet->active = 0 ;      
    break;

  }
  TSUpdateStatus(bullet->owner);
  TSUpdateRanking();


  //  mvprintw(LINES-2,0,"%c %d  %d", bullet->owner->dir,oldy,oldx);
  //mvprintw(LINES-1,0,"%c %d  %d", bullet->owner->dir,bullet->y,bullet->x);
  TSMoveBullet(oldy,oldx,bullet);
  return 1;
}



/* Shoot inturtle dir */
int TMShootBullet(BULLET *bullet, TURTLE *turtle) {
  assert(turtle->bullets);  
  bullet->dir = turtle->dir ;
  int dy, dx, ch;
  dy = turtle->y ;
  dx = turtle->x ;
  // Look ahead new pos
  switch (bullet->dir)
    {
    case LEFT:
      dx--;
      break;
    case RIGHT:
      dx++;
      break;
    case DOWN:
      dy++;
      break; 
    case UP:
      dy--;
      break;
    }
  ch = (mvinch(dy,dx)  & A_CHARTEXT) ;
  // React to newpos.
  switch (ch) {
  case EMPTY :
    bullet->active = 1 ;
    bullet->y = dy ;
    bullet->x = dx ;
    turtle->bullets--;
    break;
  case TURTLEGLACE:
    bullet->active = 0 ;    
    bullet->y = dy ;
    bullet->x = dx ;
    turtle->bullets--;
    break;
  default:  //TURTLEJEWELL,WALL_HORZ,WALL_VERT,TURTLESTONE: // no bullets
    break;
  }
  TSShootBullet(bullet);
  TSUpdateStatus(turtle);
  TSUpdateRanking();
  return 1;
}


void TMClock()
{
  static unsigned int clock = 0 ;
  ((clock++ % CLOCK_SUFFLE)!=0) && 	TMRandomPowerCards(turtle[PLAYER1]);
  ((clock   % CLOCK_SUFFLE)!=0) && 	TMRandomPowerCards(turtle[PLAYER2]);    
  (!bullet[PLAYER1]->active) && TMRandomBulletCards(turtle[PLAYER1]);
  (!bullet[PLAYER2]->active) && TMRandomBulletCards(turtle[PLAYER2]);
    

  (bullet[PLAYER1]->active) && TMMoveBullet(bullet[PLAYER1]);
  (bullet[PLAYER2]->active) && TMMoveBullet(bullet[PLAYER2]);
}


/*  Releases memory used by turtle  */

