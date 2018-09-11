/*

  Turtles game using ncurses.

*/


#include <curses.h>



#include <stdlib.h> // srand

#include "ttscr.h"
#include "ttmdl.h"
#include "ttio.h"
#include <time.h>


extern TURTLE * turtle[MAX_PLAYERS];
extern BULLET * bullet[MAX_PLAYERS];


#define FILE_PATH "turtles.txt"

static void TRTSLoop()
{
  /*  Loop and get user input, invoking services rutines  */
  halfdelay(TIMESAMPLER);  // sampler
  static unsigned int clock = 0;
  while ( 1 ) {
    int key = getch();

    switch ( key ) {
    case KEY_F(1):
      TIOreadf(FILE_PATH);
      break;
    case KEY_F(2):
      TIOwritef(FILE_PATH);
      break;
    case '\n': // See  why KEY_ENTER not
      turtle[PLAYER1]->bullets && TMShootBullet(bullet[PLAYER1],turtle[PLAYER1]);
      break;
    case KEY_UP:
       turtle[PLAYER1]->power && TMMoveTurtle(turtle[PLAYER1],TURTLEUP);
      break;
    case KEY_DOWN:
       turtle[PLAYER1]->power && TMMoveTurtle(turtle[PLAYER1],TURTLEDOWN);
      break;
    case KEY_LEFT:
       turtle[PLAYER1]->power && TMMoveTurtle(turtle[PLAYER1],TURTLELEFT);
      break;
    case KEY_RIGHT:
       turtle[PLAYER1]->power && TMMoveTurtle(turtle[PLAYER1],TURTLERIGHT);
      break;
    case 'W':
    case 'w':
       turtle[PLAYER2]->power && TMMoveTurtle(turtle[PLAYER2],TURTLEUP);
      break;
    case 'X':
    case 'x':
       turtle[PLAYER2]->power && TMMoveTurtle(turtle[PLAYER2],TURTLEDOWN);
      break;
    case 'D':
    case 'd':
       turtle[PLAYER2]->power && TMMoveTurtle(turtle[PLAYER2],TURTLERIGHT);
      break;
    case 'A':
    case 'a':
       turtle[PLAYER2]->power && TMMoveTurtle(turtle[PLAYER2],TURTLELEFT);
      break;
    case ' ': // See  why KEY_ENTER not
      turtle[PLAYER2]->bullets && TMShootBullet(bullet[PLAYER2],turtle[PLAYER2] );
      break;
    case 'Q':
    case 'q':
      Quit(USER_QUIT);
      break;
    case TIMER: // Either TIMER OR ERR option happens, not both
	  mvprintw(LINES - 1, 0, "%d", clock++);
      TMClock();
      break;
    case ERR: 
      /*
       getch(3NCURSES)

       The  behavior  of  getch and friends in the presence of handled signals is unspecified in
       the SVr4 and XSI Curses documentation.  Under historical curses implementations, it  var‐
       ied  depending on whether the operating system's implementation of handled signal receipt
       interrupts a read(2) call in progress or not, and also (in some implementations)  depend‐
       ing on whether an input timeout or non-blocking mode has been set.

       Programmers concerned about portability should be prepared for either of two  cases:  (a)
       signal  receipt  does not interrupt getch; (b) signal receipt interrupts getch and causes
       it to return ERR with errno set to EINTR.

      */
      //signal interferres
      //flash();
      // beep();
      6;
    }
    refresh();
  }
}



int main(int argc, char **args) {

  /*  Seed for random generator,
      and register signal handlers
      SIGTERM, SIGINT, SIGALRM */

  TSbegin();
  TMbegin();
  TIOSetSignals();
  TIOSetTimer();

  if (argc > 1 )
    TIOreadf(args[1]); // args[1]
  TSScreen();
  TRTSLoop();
  TMend();
  TSend();

  return 0;

}
