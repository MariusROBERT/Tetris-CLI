#include "Game.hpp"

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
	updateShadow();
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
	updateShadow();
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) + 2 < 0 || !map[std::get<0>(tetromino_pos[2]) + 2][std::get<1>(tetromino_pos[2])]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 0 || (!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 2] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1])) &&
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
	if ((std::get<0>(tetromino_pos[1]) - 2 < 0 || !map[std::get<0>(tetromino_pos[1]) - 2][std::get<1>(tetromino_pos[1])]) &&
		(std::get<0>(tetromino_pos[1]) < 1 || !map[std::get<0>(tetromino_pos[1]) - 1][std::get<1>(tetromino_pos[1])]) &&
		(std::get<0>(tetromino_pos[1]) < -1 || !map[std::get<0>(tetromino_pos[1]) + 1][std::get<1>(tetromino_pos[1])]) &&
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
	if ((std::get<0>(tetromino_pos[1]) < 0 || (!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 2])) &&
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
	if ((std::get<0>(tetromino_pos[1]) < 1 || !map[std::get<0>(tetromino_pos[1]) - 1][std::get<1>(tetromino_pos[1])]) &&
		(std::get<0>(tetromino_pos[1]) < -1 || !map[std::get<0>(tetromino_pos[1]) + 1][std::get<1>(tetromino_pos[1])]) &&
		(std::get<0>(tetromino_pos[1]) + 2 < 0 || !map[std::get<0>(tetromino_pos[1]) + 2][std::get<1>(tetromino_pos[1])]) &&
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
	if ((std::get<0>(tetromino_pos[1]) < 0 || (!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 2] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 1])) &&
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
	if ((std::get<0>(tetromino_pos[2]) - 2 < 0 || !map[std::get<0>(tetromino_pos[2]) - 2][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
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
	if ((std::get<0>(tetromino_pos[1]) < 0 || (!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) - 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 1] &&
		!map[std::get<0>(tetromino_pos[1])][std::get<1>(tetromino_pos[1]) + 2])) &&
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
	if ((std::get<0>(tetromino_pos[2]) - 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || (!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1])) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || (!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1] &&
		!map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1])) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < 0 || !map[std::get<0>(tetromino_pos[2])][std::get<1>(tetromino_pos[2]) + 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2]) - 1]) &&
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
	if ((std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2])]) &&
		(std::get<0>(tetromino_pos[2]) < 1 || !map[std::get<0>(tetromino_pos[2]) - 1][std::get<1>(tetromino_pos[2]) - 1]) &&
		(std::get<0>(tetromino_pos[2]) < -1 || !map[std::get<0>(tetromino_pos[2]) + 1][std::get<1>(tetromino_pos[2])]) &&
		std::get<1>(tetromino_pos[2]) &&
		std::get<0>(tetromino_pos[2]) != 19)
	{
		rotation = 3;
		tetromino_pos[0] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2])};
		tetromino_pos[1] = {std::get<0>(tetromino_pos[2]) - 1, std::get<1>(tetromino_pos[2]) - 1};
		tetromino_pos[3] = {std::get<0>(tetromino_pos[2]) + 1, std::get<1>(tetromino_pos[2])};
	}
}