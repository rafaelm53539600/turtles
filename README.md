# turtles
Turtles is a VGA-compatible game mode, ideally running in  25x80 mode. The only purpose is to learn to program curses library as well as understand the design of graphic application, in terms of the model, the view, the controler...

# Quick start
- In Linux, Mac
$ ./configure --prefix=$HOME  (To install under /home/user/bin directory)
$ make install
$ ttrts
- In Windows.
Just open solution file (.sln) with your Visual Studio, under either turtles/VSC++/VC2013 or turtles/VSC++/VC2017. No installer provided, so try to run the project from the IDE, or open a command prompt for the *.EXE

# The Game
- Two players.
- The screen marks each player's keys to control your turtle (red or yellow), up, down, right, left and shooting.
- Your goal is to catch every jewel '@'. You cannot pass through stones 'O', but can push them. You cannot either pass through or push the ice blocks ' * ' , but you can melt them by shooting them.
- You can also shoot your adversary, game ending when reached.
