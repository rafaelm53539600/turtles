#include "ttmdl.h"
#include "ttscr.h"
#include "ttio.h"
#include <assert.h>


WINDOW * mainwin;

extern TURTLE * turtle[MAX_PLAYERS];

void TSbegin()
{
  if ( (mainwin = initscr()) == NULL ) {
    perror("error initialising ncurses");
    exit(EXIT_FAILURE);
  }

  if ((SCREEN_HEIGHT > LINES ) ||
      (SCREEN_WIDTH > COLS))
    {
      char msg[50];
      sprintf(msg,"Not enough resolution (%d x %d)",LINES, COLS);
      Error_Quit(msg);
    }

  if (has_colors() == FALSE) {
    endwin();
    Error_Quit("Your terminal does not support color\n");
  }

  start_color();

  init_pair(COLOR_PLAYER(PLAYER1), COLOR_BLACK,COLOR_RED);
  init_pair(COLOR_PLAYER(PLAYER2), COLOR_BLACK,COLOR_YELLOW);
  

  noecho(); 
  keypad(mainwin, TRUE);
  curs_set(0);
}


void TSend()
{
  delwin(mainwin);
  endwin();
  refresh();
}

int TSrotateMoveTurtle(const int oriy,const int orix, const TURTLE *turtle)
{
  // Get the last stone
  int y,x ;
  int c;
  y = turtle->y;
  x = turtle->x;
  while ((c=mvinch(y,x))==TURTLESTONE)  // THE ONLY LOOP IN GAME!
    {
      x = x + SHIFT_HORZ(turtle->dir)*((turtle->dir==LEFT)?-1:1);
      y = y + SHIFT_VERT(turtle->dir)*((turtle->dir==UP)?-1:1);
    }
  mvaddch(y,x,TURTLESTONE);
  mvaddch(oriy, orix,EMPTY); //delete (fiction of mouvement)
  attron(COLOR_PAIR(COLOR_PLAYER(turtle->id)));
  mvaddch(turtle->y, turtle->x, turtle->dir);
  attroff(COLOR_PAIR(COLOR_PLAYER(turtle->id)));
  return 1;
}

int TSShootBullet(const BULLET *bullet)
{
  mvaddch(bullet->y, bullet->x, SHIFT_HORZ(bullet->dir)?BULLET_HORZ:BULLET_VERT);
  (bullet->active )|| mvaddch(bullet->y, bullet->x,EMPTY);
  return 1;
}

int TSMoveBullet(const int oriy, const int orix, const BULLET *bullet)
{
  mvaddch(oriy, orix,EMPTY); //delete (fiction of mouvement)
  mvaddch(bullet->y, bullet->x, SHIFT_HORZ(bullet->dir)?BULLET_HORZ:BULLET_VERT);
  //log  mvprintw(LINES-1,0,"%d %d  %d", bullet->active,bullet->y,bullet->x);
  (bullet->active )|| mvaddch(bullet->y, bullet->x,EMPTY);
  return 1;
}

void TSUpdateRanking(void) 
{
  int max, min;

  max = (turtle[PLAYER2]->score > turtle[PLAYER1]->score)? PLAYER2:PLAYER1;
  min = 1 - max;
  mvprintw(SCORE_START_Y+2+0*SCORE_HEIGHT/2,
	   SCORE_START_X+1,
	   "P%d %3d",turtle[max]->id,turtle[max]->score);
  mvprintw(SCORE_START_Y+2+1*SCORE_HEIGHT/2,
	   SCORE_START_X+1,
	   "P%d %3d",turtle[min]->id,turtle[min]->score);

}

void TSUpdateStatus(const TURTLE *turtle) // p: player
{
  int p =turtle->id;
  mvprintw(CONTROL_START_Y(p)+1*(CONTROL_HEIGHT(p)/4),
	   CONTROL_START_X(p)+1,
	   POS_CONTROL,
	   turtle->y-ARENA_START_Y,
	   turtle->x-ARENA_START_X);
  mvprintw(CONTROL_START_Y(p)+2*(CONTROL_HEIGHT(p)/4),
	   CONTROL_START_X(p)+1,
	   POW_CONTROL,
	   turtle->power);
  mvprintw(CONTROL_START_Y(p)+1*(CONTROL_HEIGHT(p)/4),
	   CONTROL_START_X(p)+2*(CONTROL_WIDTH(p)/4),
	   BULLETS_CONTROL,
	   turtle->bullets);  
  mvprintw(CONTROL_START_Y(p)+2*(CONTROL_HEIGHT(p)/4),
	   CONTROL_START_X(p)+2*(CONTROL_WIDTH(p)/4),
	   SCORE_CONTROL,
	   turtle->score);  

}

static void TSframe(const int starty, const int startx,  const int width, const int height)
{
  // 4 corners
  mvaddch( starty, startx, WALL_CORNER);
  mvaddch( starty + height - 1, startx, WALL_CORNER);
  mvaddch( starty, startx + width - 1, WALL_CORNER);
  mvaddch( starty + height - 1, startx + width - 1, WALL_CORNER);

  int i;
  // sides
  for (i = 1+starty; i < (starty + height - 1); i++) {
    mvaddch(i, startx, WALL_VERT);
    mvaddch(i, startx + width - 1, WALL_VERT);
  }

  // top and bottom
  for (i = 1+startx; i < (startx + width - 1); i++) {
    mvaddch( starty, i, WALL_HORZ);
    mvaddch( starty + height - 1, i, WALL_HORZ);
  }

  refresh();
}

/*  Draws game arena  */

void TSScreen(void) {

  /* Draw Controls - panels */
  TSframe(CONTROL1_START_Y,
	CONTROL1_START_X,
	CONTROL1_WIDTH,
	CONTROL1_HEIGHT );
  mvprintw(CONTROL1_START_Y,
	   CONTROL1_START_X+3,
	   "Control 0");  
  TSframe(CONTROL2_START_Y,
	CONTROL2_START_X,
	CONTROL2_WIDTH,
	CONTROL2_HEIGHT );

  mvprintw(CONTROL2_START_Y,
	   CONTROL2_START_X+3,
	   "Control 1");  
  /* Draw action-panels */
  TSframe(HELP2_START_Y,
	HELP2_START_X,
	HELP2_WIDTH,
	HELP2_HEIGHT );

  mvprintw(HELP2_START_Y,
	   HELP2_START_X+3,
	   "Action 1");    
  mvprintw(HELP2_START_Y+1*(HELP2_HEIGHT/4),
	   HELP2_START_X+(HELP2_WIDTH/2),
	   UP_HELP2);  
  mvprintw(HELP2_START_Y+3*(HELP2_HEIGHT/4),
	   HELP2_START_X+(HELP2_WIDTH/2),
	   DOWN_HELP2);
  mvprintw(HELP2_START_Y+2*(HELP2_HEIGHT/4),
	   HELP2_START_X+(HELP2_WIDTH/4),
	   LEFT_HELP2);  
  mvprintw(HELP2_START_Y+2*(HELP2_HEIGHT/4),
	   HELP2_START_X+3*(HELP2_WIDTH/4),
	   RIGHT_HELP2);  
  mvprintw(HELP2_START_Y+2*(HELP2_HEIGHT/4),
	   HELP2_START_X+1,
	   SHOOT_HELP2);
  
  TSframe(HELP1_START_Y,
	HELP1_START_X,
	HELP1_WIDTH,
	HELP1_HEIGHT );
  mvprintw(HELP1_START_Y,
	   HELP1_START_X+3,
	   "Action 0");  
  mvprintw(HELP1_START_Y+1*(HELP1_HEIGHT/4),
	   HELP1_START_X+(HELP1_WIDTH/2),
	   UP_HELP1);  

  mvprintw(HELP1_START_Y+3*(HELP1_HEIGHT/4),
	   HELP1_START_X+(HELP1_WIDTH/2),
	   DOWN_HELP1);
  mvprintw(HELP1_START_Y+2*(HELP1_HEIGHT/4),
	   HELP1_START_X+(HELP1_WIDTH/4),
	   LEFT_HELP1);  
  mvprintw(HELP1_START_Y+2*(HELP1_HEIGHT/4),
	   HELP1_START_X+3*(HELP1_WIDTH/4),
	   RIGHT_HELP1);  
  mvprintw(HELP1_START_Y+2*(HELP1_HEIGHT/4),
	   HELP1_START_X+1,
	   SHOOT_HELP1);


  /* Draw ranking panel */
  TSframe(SCORE_START_Y,
	SCORE_START_X,
	SCORE_WIDTH,
	SCORE_HEIGHT );
  mvprintw(SCORE_START_Y,SCORE_START_X+1,"Ranking");
  mvprintw(SCORE_START_Y+2+0*SCORE_HEIGHT/2,
	   SCORE_START_X+1,
	   "P%d %3d",turtle[PLAYER1]->id,turtle[PLAYER1]->score);
  mvprintw(SCORE_START_Y+2+1*SCORE_HEIGHT/2,
	   SCORE_START_X+1,
	   "P%d %3d",turtle[PLAYER2]->id,turtle[PLAYER2]->score);

  
  /* Draw OS services panel */

  TSframe(OS_START_Y,
	OS_START_X,
	OS_WIDTH,
	OS_HEIGHT );
  mvprintw(OS_START_Y,
	   OS_START_X+2,
	   "O.S");    
  mvprintw(OS_START_Y+2+0*OS_HEIGHT/4,
	   OS_START_X+1,
	   F1_OS);  
  mvprintw(OS_START_Y+2+1*OS_HEIGHT/4,
	   OS_START_X+1,
	   F2_OS);
  mvprintw(OS_START_Y+2+2*OS_HEIGHT/4,
	   OS_START_X+1,
	   F3_OS);  
#if 0
  mvprintw(OS_START_Y+1+3*OS_HEIGHT/4,
	   OS_START_X+1,
	   F4_OS);  
#endif
  

  TSframe(ARENA_START_Y,ARENA_START_X,ARENA_WIDTH, ARENA_HEIGHT );
  mvprintw(ARENA_START_Y,ARENA_START_X+(ARENA_WIDTH - ARENA_WIDTH/2),"Arena");    

  
  /*  Draw initial turtle Jewell  */
  int n;
  for ( n=0; n<NUM_JEWELLS ; n++) TSPlaceItem(TURTLEJEWELL);
   /*  Draw initial stones obstacles  */
  for ( n=0; n<NUM_STONES ; n++) TSPlaceItem(TURTLESTONE);
   /*  Draw initial glaces  */
  for ( n=0; n<NUM_GLACES ; n++) TSPlaceItem(TURTLEGLACE);

  /*  Draw the turtle  */
  attron(COLOR_PAIR(PLAYER1+1));
  mvaddch(turtle[PLAYER1]->y, turtle[PLAYER1]->x, turtle[PLAYER1]->dir);
  attroff(COLOR_PAIR(PLAYER1+1));
  
  attron(COLOR_PAIR(PLAYER2+1));  
  mvaddch(turtle[PLAYER2]->y, turtle[PLAYER2]->x, turtle[PLAYER2]->dir);
  attroff(COLOR_PAIR(PLAYER2+1));  

  TSUpdateStatus(turtle[PLAYER1]);
  TSUpdateStatus(turtle[PLAYER2]);

}


/*  Place item in the arena  */
void TSPlaceItem(char item)
{

  int x,y;
  do {
    x = (rand() % (ARENA_WIDTH) + ARENA_START_X);
    y = (rand() % (ARENA_HEIGHT) + ARENA_START_Y);
    move(y,x);
  } while ((inch() & A_CHARTEXT)!= EMPTY );

  // log mvprintw(LINES-1,0,"%d ", color);
  //  attron(COLOR_PAIR(color)); // lot of problems with colors
  mvaddch(y,x,item);
  refresh();
  //attroff(COLOR_PAIR(color));  
}


