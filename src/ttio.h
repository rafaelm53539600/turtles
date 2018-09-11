#ifndef IO_H
#define IO_H


/* Module implementing O.S services */

#define USER_QUIT    1
#define GAME_OVER    2

#define TIMESTEP 200000  // microseconds (1 ms = 1000 us)
#define TIMESAMPLER 1  // tenths of tenths of second (1 ms = 1000 us)
#define CLOCK_SUFFLE 2

#define TIMER '*'   // This can be the back-door of the game



void Error_Quit(const char * msg);
void Quit(const int reason);
void TIOSetTimer(void) ;
void TIOUnSetTimer(void);
void TIOSetSignals(void);
void TIOreadf(const char *path);
void TIOwritef(const char *path);
#endif
