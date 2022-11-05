# turtles
Turtles is a VGA-compatible game mode, ideally running in  25x80 mode. The only purpose is to learn to program curses library as well as understand the design of graphic application, in terms of the model, the view, the controler...

# Quick start
- In Linux, Mac

$ ./configure --prefix=$HOME  (To install under /home/user/bin directory)

$ make install

$ ttrts

- In Windows.

Provided solution files (.sln) for Visual Studio under VSC++ directory.

- VC2013 
- VC2017
- VC2019
You may need to tweak the platformset or WINDOWS SDK for update upon request. 

No installer provided, so try to run the project from the IDE ( or search *.EXE to run from cmd).
CHOOSE ALWAYS <DEBUG> <X86> AS RUNNING CONFIGURATION!!. <RELEASE><X64> MAY NOT WORK.

Due to its own nature, the VGA dsiplay is very weak . Make sure that you are running Windows Console Host (as it was from XP) and not Windows Terminal (as it was from Windows 11). Never run the console in "Full Screen". It is recommended a Font size of 36 or lower, but not below.






# The Game
- Two players.
- The screen marks each player's keys to control your turtle (red or yellow), up, down, right, left and shooting.
- Your goal is to catch every jewel '@'. You cannot pass through stones 'O', but can push them. You cannot either pass through or push the ice blocks ' * ' , but you can melt them by shooting them.
- You can also shoot your adversary, game ending when reached.
