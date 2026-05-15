# turtles
Turtles is a VGA-compatible game mode, ideally running in  25x80 mode. The only purpose is to learn to program curses library as well as understand the design of graphic application, in terms of the model, the view, the controler...

(The binary library **pdcurses** is bundled in folder)

# Quick start
- Linux
$ export PATH=$HOME/bin:$PATH

$ ./configure --prefix=$HOME

$ make install

$ ttrts


- In Mac OS. Tested on:

$ uname -mrsp

** Darwin 25.5.0 x86_64 i386 **

$ export PATH=$HOME/bin:$PATH

$ ./configure --prefix=$HOME --disable-dependency-tracking

$ chmod +x install-sh

$ make install

$ ttrts


- In Windows, VSC++. 

CHOOSE ALWAYS **\<DEBUG\> \<X86\>** AS RUNNING  CONFIGURATION!!.

\<X64\> WON'T WORK.
  

Provided solution files (.sln) for Visual Studio under VSC++ directory.

- VC2013 
- VC2017
- VC2019
- VC2022

You may need to tweak the platformset or WINDOWS SDK for update upon request. 

No installer provided, so try to run the project from the IDE ( or search *.EXE to run from cmd).



# The Game
- Two players.
- The screen marks each player's keys to control your turtle (red or yellow), up, down, right, left and shooting.
- Your goal is to catch every jewel '@'. 
- You cannot pass through stones 'O', but can push them.
- You cannot either pass through or push the ice blocks ' * ' , but
 can melt them by shooting them.
- Once you shoot, you have to wait some time to reload  bullets. (Game Dynamics was not fully finished)
- You can also shoot your adversary, game ending when reached.
- Score, ranking and control panels displays resective information.
