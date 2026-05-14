# turtles
Turtles is a VGA-compatible game mode, ideally running in  25x80 mode. The only purpose is to learn to program curses library as well as understand the design of graphic application, in terms of the model, the view, the controler...

(The binary library pdcurses is bundled in folder)

# Quick start
- In Linux.


$ ./configure --prefix=$HOME  

$ make install

$ ttrts   # (You may need to adjust your PATH environment variable to $HOME/bin:$PATH)

- In Mac (tested as of Tahoe 26.5, intel). See video under res/ folder.

$ ./configure --prefix=$HOME --disable-dependency-tracking  # don't
know why

$ make install  # (I could not make it work... GNU software clashing in Mac?)

 

$ src/ttrts    # run from compilation folder


- In Windows. 

*CHOOSE ALWAYS \<DEBUG\> \<X86\> AS RUNNING  CONFIGURATION!!.* 
  
\<RELEASE\>\<X64\> DOES  NOT WORK.  See video  under res/ folder

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
- Your goal is to catch every jewel '@'. You cannot pass through stones 'O', but can push them. You cannot either pass through or push the ice blocks ' * ' , but you can melt them by shooting them. Once you shoot, you have to wait some time to reload  bullets. (Game Dynamics was not fully finished)
- You can also shoot your adversary, game ending when reached.
- Score, ranking and control panels displays resective information.
