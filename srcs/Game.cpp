#include "Game.hpp"

Game::Game() : map(), tetromino_pos(), tetromino(1), rotation(0), lost(false)
{
	spawnNewPiece();
}

char Game::getCase(unsigned int x, unsigned int y) const
{
	for (int i = 0; i < 4; ++i)
		if (std::get<0>(tetromino_pos[i]) == x && std::get<1>(tetromino_pos[i]) == y)
			return tetromino;
	return map[x][y];
}

void Game::moveDown()
{
	bool can_move = true;
	static bool final = false;

	if (lost)
		return;

	if (final)
	{
		final = false;
		lockTetromino();
	}

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<0>(tetromino_pos[i]) == 19 ||
			map[std::get<0>(tetromino_pos[i]) + 1][std::get<1>(tetromino_pos[i])])
			can_move = false;


	if (can_move)
		for (int i = 0; i < 4; ++i)
			tetromino_pos[i] = {std::get<0>(tetromino_pos[i]) + 1, std::get<1>(tetromino_pos[i])};
	else
		final = true;
}

void Game::moveLeft()
{
	bool can_move = true;

	if (lost)
		return;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<1>(tetromino_pos[i]) == 0 || map[std::get<0>(tetromino_pos[i])][std::get<1>(tetromino_pos[i]) - 1])
			can_move = false;

	if (can_move)
		for (int i = 0; i < 4; ++i)
			tetromino_pos[i] = {std::get<0>(tetromino_pos[i]), std::get<1>(tetromino_pos[i]) - 1};
}

void Game::moveRight()
{
	bool can_move = true;

	if (lost)
		return;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<1>(tetromino_pos[i]) == 9 || map[std::get<0>(tetromino_pos[i])][std::get<1>(tetromino_pos[i]) + 1])
			can_move = false;

	if (can_move)
		for (int i = 0; i < 4; ++i)
			tetromino_pos[i] = {std::get<0>(tetromino_pos[i]), std::get<1>(tetromino_pos[i]) + 1};
}

void Game::printMap() const
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 10; ++j)
			std::cout << (int) map[i][j];
		std::cout << std::endl;
	}
}

void Game::spawnNewPiece()
{
	if (lost)
		return;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 7);

	tetromino = (char) distrib(gen);

	switch (tetromino)
	{
		case I:
			tetromino_pos[0] = {0, 3};
			tetromino_pos[1] = {0, 4};
			tetromino_pos[2] = {0, 5};
			tetromino_pos[3] = {0, 6};
			break;
		case O:
			tetromino_pos[0] = {-1, 4};
			tetromino_pos[1] = {-1, 5};
			tetromino_pos[2] = {0, 4};
			tetromino_pos[3] = {0, 5};
			break;
		case T:
			tetromino_pos[0] = {-1, 4};
			tetromino_pos[1] = {0, 3};
			tetromino_pos[2] = {0, 4};
			tetromino_pos[3] = {0, 5};
			break;
		case S:
			tetromino_pos[0] = {-1, 4};
			tetromino_pos[1] = {-1, 5};
			tetromino_pos[2] = {0, 3};
			tetromino_pos[3] = {0, 4};
			break;
		case Z:
			tetromino_pos[0] = {-1, 3};
			tetromino_pos[1] = {-1, 4};
			tetromino_pos[2] = {0, 4};
			tetromino_pos[3] = {0, 5};
			break;
		case J:
			tetromino_pos[0] = {-1, 3};
			tetromino_pos[1] = {0, 3};
			tetromino_pos[2] = {0, 4};
			tetromino_pos[3] = {0, 5};
			break;
		case L:
			tetromino_pos[0] = {-1, 5};
			tetromino_pos[1] = {0, 3};
			tetromino_pos[2] = {0, 4};
			tetromino_pos[3] = {0, 5};
			break;
	}
	rotation = 0;
}

void Game::lockTetromino()
{
	for (auto &tetromino_piece: tetromino_pos)
		map[std::get<0>(tetromino_piece)][std::get<1>(tetromino_piece)] = tetromino;
	checkLines();
	spawnNewPiece();
	if (checkLose())
		lost = true;
}

void Game::clearLine(unsigned int line)
{
	for (unsigned int i = line; i > 0; --i)
		for (int j = 0; j < 10; ++j)
			map[i][j] = map[i - 1][j];

	for (int j = 0; j < 10; ++j)
		map[0][j] = 0;
}

void Game::checkLines()
{
	for (unsigned int i = 0; i < 20; ++i)
	{
		bool full = true;
		for (unsigned int j = 0; j < 10; ++j)
		{
			if (map[i][j] == 0)
			{
				full = false;
				break;
			}
		}
		if (full)
			clearLine(i);
	}
}

bool Game::checkLose()
{
	if (map[0][4])
		return true;
	if ((tetromino == I || tetromino == T || tetromino == J || tetromino == L) && (map[0][3] || map[0][5]))
		return true;
	if (map[0][3] && tetromino == S)
		return true;
	if (map[0][5] && (tetromino == O || tetromino == Z))
		return true;
	if (map[0][6] && tetromino == I)
		return true;
	return false;
}

void Game::turnRight()
{
	switch (tetromino)
	{
		case I:
			turnIRight();
			break;
		case T:
			turnTRight();
			break;
		case S:
			turnSRight();
			break;
		case Z:
			turnZRight();
			break;
		case J:
			turnJRight();
			break;
		case L:
			turnLRight();
			break;
	}
}

void Game::turnLeft()
{
	switch (tetromino)
	{
		case I:
			turnILeft();
			break;
		case T:
			turnTLeft();
			break;
		case S:
			turnSLeft();
			break;
		case Z:
			turnZLeft();
			break;
		case J:
			turnJLeft();
			break;
		case L:
			turnLLeft();
			break;
	}
}


void Game::turnIRight()
{
	switch (rotation)
	{
		case 0:
			turnI0Right();
			break;
		case 1:
			turnI1Right();
			break;
		case 2:
			turnI2Right();
			break;
		case 3:
			turnI3Right();
			break;
	}
}

void Game::turnTRight()
{
	switch (rotation)
	{
		case 0:
			turnT1();
			break;
		case 1:
			turnT2();
			break;
		case 2:
			turnT3();
			break;
		case 3:
			turnT0();
			break;
	}
}

void Game::turnSRight()
{
	switch (rotation)
	{
		case 0:
			turnS1();
			break;
		case 1:
			turnS2();
			break;
		case 2:
			turnS3();
			break;
		case 3:
			turnS0();
			break;
	}
}

void Game::turnZRight()
{
	switch (rotation)
	{
		case 0:
			turnZ1();
			break;
		case 1:
			turnZ2();
			break;
		case 2:
			turnZ3();
			break;
		case 3:
			turnZ0();
			break;
	}
}

void Game::turnJRight()
{
	switch (rotation)
	{
		case 0:
			turnJ1();
			break;
		case 1:
			turnJ2();
			break;
		case 2:
			turnJ3();
			break;
		case 3:
			turnJ0();
			break;
	}
}

void Game::turnLRight()
{
	switch (rotation)
	{
		case 0:
			turnL1();
			break;
		case 1:
			turnL2();
			break;
		case 2:
			turnL3();
			break;
		case 3:
			turnL0();
			break;
	}
}


void Game::turnILeft()
{
	switch (rotation)
	{
		case 0:
			turnI0Left();
			break;
		case 1:
			turnI1Left();
			break;
		case 2:
			turnI2Left();
			break;
		case 3:
			turnI3Left();
			break;
	}
}

void Game::turnTLeft()
{
	switch (rotation)
	{
		case 0:
			turnT3();
			break;
		case 1:
			turnT0();
			break;
		case 2:
			turnT1();
			break;
		case 3:
			turnT2();
			break;
	}
}

void Game::turnSLeft()
{
	switch (rotation)
	{
		case 0:
			turnS3();
			break;
		case 1:
			turnS0();
			break;
		case 2:
			turnS1();
			break;
		case 3:
			turnS2();
			break;
	}
}

void Game::turnZLeft()
{
	switch (rotation)
	{
		case 0:
			turnZ3();
			break;
		case 1:
			turnZ0();
			break;
		case 2:
			turnZ1();
			break;
		case 3:
			turnZ2();
			break;
	}
}

void Game::turnJLeft()
{
	switch (rotation)
	{
		case 0:
			turnJ3();
			break;
		case 1:
			turnJ0();
			break;
		case 2:
			turnJ1();
			break;
		case 3:
			turnJ2();
			break;
	}
}

void Game::turnLLeft()
{
	switch (rotation)
	{
		case 0:
			turnL3();
			break;
		case 1:
			turnL0();
			break;
		case 2:
			turnL1();
			break;
		case 3:
			turnL2();
			break;
	}
}


//From pos0 to pos1
void Game::turnI0Right()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 2][std::get<1>(tetromino_pos[2])] &&
		std::get<0>(tetromino_pos[2]) < 18)
	{
		rotation = 1;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2])};
		tetromino_pos[2] = {std::get<0>(tetromino_pos[1]) + 1, std::get<1>(tetromino_pos[1])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}

//From pos1 to pos2
void Game::turnI1Right()
{
	if (!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 2] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<1>(tetromino_pos[2]) > 1 &&
		std::get<1>(tetromino_pos[2]) < 9)
	{
		rotation = 2;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 2};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//From pos2 to pos3
void Game::turnI2Right()
{
	if (!map[std::get<0>(tetromino_pos[1]) - 2][std::get<1>(tetromino_pos[1])] &&
		!map[std::get<0>(tetromino_pos[1]) - 1][std::get<1>(tetromino_pos[1])] &&
		!map[std::get<0>(tetromino_pos[1]) + 1][std::get<1>(tetromino_pos[1])] &&
		std::get<0>(tetromino_pos[1]) < 19)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[1]) - 2, std::get<1>(tetromino_pos[1])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[1]) - 1, std::get<1>(tetromino_pos[1])};
		tetromino_pos[2] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}

//From pos3 to pos0
void Game::turnI3Right()
{
	if (!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 2] &&
		std::get<1>(tetromino_pos[1]) > 0 &&
		std::get<1>(tetromino_pos[2]) < 8)
	{
		rotation = 0;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) - 1};
		tetromino_pos[2] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) + 2};
	}
}

//From pos0 to pos3
void Game::turnI0Left()
{
	if (!map[std::get<0>(tetromino_pos[1]) - 1][std::get<1>(tetromino_pos[1])] &&
		!map[std::get<0>(tetromino_pos[1]) + 1][std::get<1>(tetromino_pos[1])] &&
		!map[std::get<0>(tetromino_pos[1]) + 2][std::get<1>(tetromino_pos[1])] &&
		std::get<0>(tetromino_pos[2]) < 18)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[1]) - 1, std::get<1>(tetromino_pos[1])};
		tetromino_pos[2] = {std::get<0>(tetromino_pos[1]) + 1, std::get<1>(tetromino_pos[1])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[1]) + 2, std::get<1>(tetromino_pos[1])};
	}
}

//From pos1 to pos0
void Game::turnI1Left()
{
	if (!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 2] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 1] &&
		std::get<1>(tetromino_pos[2]) > 1 &&
		std::get<1>(tetromino_pos[2]) < 9)
	{
		rotation = 0;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) - 2};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) - 1};
		tetromino_pos[2] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//From pos2 to pos1
void Game::turnI2Left()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 2][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		std::get<0>(tetromino_pos[1]) < 19)
	{
		rotation = 1;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 2, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}

//From pos3 to pos2
void Game::turnI3Left()
{
	if (!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 2] &&
		std::get<1>(tetromino_pos[1]) > 0 &&
		std::get<1>(tetromino_pos[2]) < 8)
	{
		rotation = 2;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2])};
		tetromino_pos[2] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[1]), std::get<1>(tetromino_pos[1]) + 2};
	}
}

//Go to pos0
void Game::turnT0()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 0;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos1
void Game::turnT1()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 1;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos2
void Game::turnT2()
{
	if (!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 2;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos3
void Game::turnT3()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<0>(tetromino_pos[2]) != 19)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
	}
}

//Go to pos0
void Game::turnS0()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 0;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos1
void Game::turnS1()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 1;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos2
void Game::turnS2()
{
	if (!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 2;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) - 1};
	}
}

//Go to pos3
void Game::turnS3()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<0>(tetromino_pos[2]) != 19)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
	}
}

//Go to pos0
void Game::turnZ0()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 0;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos1
void Game::turnZ1()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 1;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}

//Go to pos2
void Game::turnZ2()
{
	if (!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 2;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos3
void Game::turnZ3()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<0>(tetromino_pos[2]) != 19)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) - 1};
	}
}

//Go to pos0
void Game::turnJ0()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 0;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos1
void Game::turnJ1()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 1;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}

//Go to pos2
void Game::turnJ2()
{
	if (!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 2;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos3
void Game::turnJ3()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<0>(tetromino_pos[2]) != 19)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}

//Go to pos0
void Game::turnL0()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 0;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
	}
}

//Go to pos1
void Game::turnL1()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 1;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}

//Go to pos2
void Game::turnL2()
{
	if (!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1] &&
		std::get<0>(tetromino_pos[2]) != 19 &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<1>(tetromino_pos[2]) != 9)
	{
		rotation = 2;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]), std::get<1>(tetromino_pos[2]) + 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2]) - 1};
	}
}

//Go to pos3
void Game::turnL3()
{
	if (!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])] &&
		!map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])] &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<0>(tetromino_pos[2]) != 19)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}
