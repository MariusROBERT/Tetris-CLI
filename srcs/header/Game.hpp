#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <tuple>
#include <random>
#include <string>
#include "ftxui/component/component_base.hpp"

#ifndef AZERTY
# define AZERTY 0
#endif


#if AZERTY == 0
# define ROTATE_LEFT 'q'
# define ROTATE_RIGHT 'e'
# define MOVE_LEFT 'a'
# define MOVE_RIGHT 'd'
# define MOVE_DOWN 's'
# define HOLD 'w'
# define DROP ' '
# define PAUSE 'p'
#endif

#if AZERTY == 1
# define ROTATE_LEFT 'a'
# define ROTATE_RIGHT 'e'
# define MOVE_LEFT 'q'
# define MOVE_RIGHT 'd'
# define MOVE_DOWN 's'
# define HOLD 'z'
# define DROP ' '
# define PAUSE 'p'
#endif

enum tetrominoes {
	EMPTY = 0,
	I = 1,
	O = 2,
	T = 3,
	S = 4,
	Z = 5,
	J = 6,
	L = 7,
};


class Game
{
private:
	char map[20][10];
	std::tuple<int, int> tetromino_pos[4];
	std::tuple<int, int> tetromino_shadow[4];
	char tetromino;
	char rotation;

	bool lost;
	bool paused;

	char hold;
	char next;
	bool holdLock;

	size_t clock;

	unsigned int score;
	unsigned int lines;

	void spawnNewPiece();
	void spawnNewPiece(char newTetromino);

	void updateShadow();

	void checkLines();
	void clearLine(unsigned int line);
	bool checkLose();

public:
	Game();
	[[nodiscard]] char getCase(int x, int y) const;

	void start();
	[[nodiscard]] bool isLost() const;
	[[nodiscard]] bool isPaused() const;

	void pause();
	void unPause();

	void moveDown();
	void moveLeft();
	void moveRight();

	[[nodiscard]] char getNext() const;
	[[nodiscard]] char getHold() const;
	[[nodiscard]] unsigned int getScore() const;
	[[nodiscard]] unsigned int getLines() const;

	void turnRight();
	void turnLeft();

	void drop();

	void swapHold();
	void lockTetromino();

	void loop();

	void printMap() const;

private:
	void turnIRight();
	void turnTRight();
	void turnSRight();
	void turnZRight();
	void turnJRight();
	void turnLRight();

	void turnILeft();
	void turnTLeft();
	void turnSLeft();
	void turnZLeft();
	void turnJLeft();
	void turnLLeft();


	void turnI0Right();
	void turnI1Right();
	void turnI2Right();
	void turnI3Right();

	void turnI0Left();
	void turnI1Left();
	void turnI2Left();
	void turnI3Left();

	void turnT0();
	void turnT1();
	void turnT2();
	void turnT3();

	void turnS0();
	void turnS1();
	void turnS2();
	void turnS3();

	void turnZ0();
	void turnZ1();
	void turnZ2();
	void turnZ3();

	void turnJ0();
	void turnJ1();
	void turnJ2();
	void turnJ3();

	void turnL0();
	void turnL1();
	void turnL2();
	void turnL3();
};


#endif //GAME_HPP
