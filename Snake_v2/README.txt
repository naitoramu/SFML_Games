#How to run a game

You need to have gcc compiler, and SFML, at least version 2.5

1. Open folder with the game in terminal and run commands below:
$ g++ -c Snake.cpp
$ g++ Snake.o -o Snake -lsfml-graphics -lsfml-window -lsfml-system SnakeHead.cpp SnakeBody.cpp Apple.cpp 
$ ./Snake