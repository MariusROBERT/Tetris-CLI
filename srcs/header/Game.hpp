#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <tuple>
#include <random>
#include "ftxui/component/component_base.hpp"

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
	char tetromino;
	char rotation;
	bool lost;
	char hold;
	char next;
	bool holdLock;

	void spawnNewPiece();
	void clearLine(unsigned int line);
	void checkLines();
	bool checkLose();

public:
	Game();
	[[nodiscard]] char getCase(unsigned int x, unsigned int y) const;

	void moveDown();
	void moveLeft();

	char getNext() const;

	void moveRight();

	void turnRight();
	void turnLeft();

	void swapHold();
	void lockTetromino();

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
