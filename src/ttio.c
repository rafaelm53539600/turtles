#include "ttio.h"

#include <stdio.h>
#include <stdlib.h>
#include "ttmdl.h"
#include "ttscr.h"


// The whole state of the game.
extern WINDOW * mainwin;
extern TURTLE * turtle[MAX_PLAYERS];
extern BULLET * bullet[MAX_PLAYERS];

#define RANK_PATH "ranking.txt"


static void TIOrank()
{
  // The rank is not part of the state of the game.
  FILE *f;
#define MAX_ID 10
#define MAX_RANK 10  
  typedef struct {
    char id[MAX_ID];
    int score;
  } LIST[MAX_RANK];

  int N;
  LIST list;
#if 0
  if ((f = fopen(RANK_PATH,"r"))==NULL)
    Error_Quit("fopen");
  for (N=0; fscanf(f,"%s %d\n",list[N].id, &(list[N].score))!=2 ; N++) ;
  if (feof(f)!=EOF)
    Error_Quit("fscanf");
  if (fclose(f)==EOF)
    Error_Quit("fclose");
  if ((f = fopen(RANK_PATH,"w"))==NULL)
    Error_Quit("fopen");
  int n;
  for (n=0; n<N; n++)
    if (fprintf(f,"%s %d",list[n].id, list[n].score) < 0 )
      Error_Quit("fprintf");       
  if (fclose(f)==EOF)
    Error_Quit("fclose");
#endif  
}


#ifndef _WIN32_

  /*  Signal handler  */
#include <sys/ioctl.h>
#include <signal.h>
#include <sys/time.h>



  void handler(int signum)
  {

    /*  Switch on signal number  */

    switch ( signum ) {

    case SIGALRM:

      /*  Received from the timer
	  We use it for simulate token-pass
	  and timing the bullets.
      */
      ungetch(TIMER);  // enqueue "event" to GUI,
      // (the back-door to the game : '*'
      break;

    case SIGTERM:
    case SIGINT:

      /*  Used to 
	  Clean up nicely  */
      TIOUnSetTimer();
      TMend();    
      TSend();
      exit(EXIT_SUCCESS);
      break;
    }
  }

  /*  Sets up signal handlers we need  */

  void TIOSetSignals(void) {

    struct sigaction sa;


    /*  Fill in sigaction struct  */

    sa.sa_handler = handler;
    sa.sa_flags   = 0;
    sigemptyset(&sa.sa_mask);


    /*  Set signal handlers  */

    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);


    /*  Ignore SIGTSTP  */

    sa.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &sa, NULL);
  }

  /*  Sets up the game timer  */

  void TIOSetTimer(void) {

    struct itimerval it;


    /*  Clear itimerval struct members  */

    timerclear(&it.it_interval);
    timerclear(&it.it_value);


    /*  Set timer  */
    it.it_interval.tv_usec = TIMESTEP;
    it.it_value.tv_usec = TIMESTEP;
    setitimer(ITIMER_REAL, &it, NULL);
  }


  void  TIOUnSetTimer(void)
  {

    struct itimerval it;


    /*  Clear itimerval struct members  */

    timerclear(&it.it_interval);
    timerclear(&it.it_value);


    /*  Set timer  */

    it.it_interval.tv_usec = 0;
    it.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &it, NULL);

  }
#else // _WIN32_

#include <windows.h>

  DWORD WINAPI handler(LPVOID lpParam)
  {
    // Simulates a TIMER
    static int clock = 0;	
    for ( ; 1 ; )
      {
	ungetch(TIMER); // Simulate "timer" envent
	Sleep(TIMESTEP/1000);
	// sending '*' to the queue
      }
  }

  void TIOSetSignals(void)
  {
    // No counter-part in windows
    // i.e TACET (like a Tuba in a Mozart's symphonie)
  }


  /*  Sets up the game timer  */

  void TIOSetTimer(void) 
  {
    DWORD dwThreadId;
    HANDLE hThread;

    hThread = CreateThread(NULL,
			   0,
			   handler,
			   NULL,
			   0,
			   &dwThreadId);
    if (hThread == NULL)
      Error_Quit("CreateThread");
  }

  void  TIOUnSetTimer(void)
  {
    // kill Thread. TODO
  }
#endif // _WIN32_



  void Quit(const int reason) {



    /*  Clean up nicely  */
    TIOUnSetTimer();  
    TMend();
    TSend();

    /*  Output  message  */

    switch ( reason ) {
    case GAME_OVER:
      TIOrank();
      printf("\nGame over!\n");
      break;
    default:
      printf("\nGoodbye! (%d x %d)\n", LINES, COLS );
      break;
    }

    exit(EXIT_SUCCESS);
  }



  /*  Quit on error  */

  void Error_Quit(const char * msg) {


    /*  Clean up nicely  */
    TIOUnSetTimer();  
    TMend();
    TSend();
    /*  Output error message and exit  */

    perror(msg);
    exit(EXIT_FAILURE);
  }


  void TIOwritef(const char *path)
  {
    FILE *f;
    int y,x,ch;
    if ((f = fopen(path,"w"))==NULL)
      Error_Quit("fopen");
    for (y=0; y < LINES ; y++)
      for (x=0; x < COLS ; x++)
	{
	  move(y,x);
	  if (fputc((ch = inch()),f)==EOF)
	    Error_Quit("fputc");
	}
    if (fclose(f)==EOF)
      Error_Quit("fclose");
  }


  void TIOreadf(const char *path)
  {
    FILE *f;
    int y,x,ch;
    if ((f = fopen(path,"r"))==NULL)
      Error_Quit("fopen");
    for (y=0; y < LINES ; y++)
      for (x=0; x < COLS ; x++)
	{
	  if ((ch=fgetc(f))==EOF)
	    Error_Quit("fgetc");
	  mvaddch(y,x,ch);
	}
    if (fclose(f)==EOF)
      Error_Quit("fclose");
  }


