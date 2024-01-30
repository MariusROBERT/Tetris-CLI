#include "Game.hpp"

Game::Game()
		: map(), tetromino_pos(), tetromino_shadow(), bag({1, 2, 3, 4, 5, 6, 7}), bag_iter(7), tetromino(1),
		  rotation(0), lost(true), paused(false), hold(EMPTY), next(0), holdLock(false), clock(0), score(0), lines(0),
		  level(0)
{
	std::random_device rd;
	rand_gen = std::mt19937(rd());
}

void Game::start()
{
	lost = false;
	next = getNewPiece();
	spawnNewPiece();
}

bool Game::isLost() const
{
	return lost;
}

bool Game::isPaused() const
{
	return paused;
}

void Game::pause()
{
	paused = true;
}

void Game::unPause()
{
	paused = false;
}

char Game::getCase(int x, int y) const
{
	for (int i = 0; i < 4; ++i)
		if (std::get<0>(tetromino_pos[i]) == x && std::get<1>(tetromino_pos[i]) == y)
			return tetromino;
	if (map[x][y])
		return map[x][y];
	for (int i = 0; i < 4; ++i)
		if (std::get<0>(tetromino_shadow[i]) == x && std::get<1>(tetromino_shadow[i]) == y)
			return (char) -tetromino;
	return (0);
}

char Game::getNext() const
{
	return next;
}

char Game::getHold() const
{
	return hold;
}

unsigned int Game::getScore() const
{
	return score;
}

unsigned int Game::getLines() const
{
	return lines;
}

void Game::moveDown()
{
	bool can_move = true;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<0>(tetromino_pos[i]) == 19 ||
			map[std::get<0>(tetromino_pos[i]) + 1][std::get<1>(tetromino_pos[i])])
			can_move = false;

	if (can_move)
		for (int i = 0; i < 4; ++i)
			tetromino_pos[i] = {std::get<0>(tetromino_pos[i]) + 1, std::get<1>(tetromino_pos[i])};
	else
		lockTetromino();

	score++;
	clock = 0;
}

void Game::moveLeft()
{
	bool can_move = true;

	if (lost)
		return;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<0>(tetromino_pos[i]) >= 0 && (std::get<1>(tetromino_pos[i]) == 0 ||
												   map[std::get<0>(tetromino_pos[i])][std::get<1>(tetromino_pos[i]) -
																					  1]))
			can_move = false;

	if (can_move)
		for (int i = 0; i < 4; ++i)
			tetromino_pos[i] = {std::get<0>(tetromino_pos[i]), std::get<1>(tetromino_pos[i]) - 1};
	updateShadow();
}

void Game::moveRight()
{
	bool can_move = true;

	if (lost)
		return;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<0>(tetromino_pos[i]) >= 0 && (std::get<1>(tetromino_pos[i]) == 9 ||
												   map[std::get<0>(tetromino_pos[i])][std::get<1>(tetromino_pos[i]) +
																					  1]))
			can_move = false;

	if (can_move)
		for (int i = 0; i < 4; ++i)
			tetromino_pos[i] = {std::get<0>(tetromino_pos[i]), std::get<1>(tetromino_pos[i]) + 1};
	updateShadow();
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

char Game::getNewPiece()
{
	if (bag_iter == 7)
	{
		std::shuffle(bag.begin(), bag.end(), rand_gen);
		bag_iter = 0;
	}
	return bag[bag_iter++];
}

void Game::spawnNewPiece()
{
	tetromino = next;
	next = getNewPiece();
	spawnNewPiece(tetromino);
}

void Game::spawnNewPiece(char newTetromino)
{
	if (lost)
		return;

	tetromino = newTetromino;

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
	updateShadow();
}

void Game::updateShadow()
{
	int diff = 100;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = std::get<0>(tetromino_pos[i]); j < 21; ++j)
		{
			if (j < 0)
				continue;
			if (j == 20 || map[j][std::get<1>(tetromino_pos[i])])
			{
				if ((j - std::get<0>(tetromino_pos[i])) < diff)
					diff = j - std::get<0>(tetromino_pos[i]);
				break;
			}
		}
	}

	diff--;
	for (int i = 0; i < 4; ++i)
		tetromino_shadow[i] = {std::get<0>(tetromino_pos[i]) + diff, std::get<1>(tetromino_pos[i])};
}


void Game::lockTetromino()
{
	for (auto &tetromino_piece: tetromino_pos)
		map[std::get<0>(tetromino_piece)][std::get<1>(tetromino_piece)] = tetromino;
	checkLines();
	holdLock = false;
	spawnNewPiece();
	if (checkLose())
		lost = true;
}

void Game::loop()
{
	if (lost)
		return;

	clock++;

	unsigned int timing;
	switch (level)
	{
		case 0:
			timing = 48;
			break;
		case 1:
			timing = 43;
			break;
		case 2:
			timing = 38;
			break;
		case 3:
			timing = 33;
			break;
		case 4:
			timing = 28;
			break;
		case 5:
			timing = 23;
			break;
		case 6:
			timing = 18;
			break;
		case 7:
			timing = 13;
			break;
		case 8:
			timing = 8;
			break;
		case 9:
			timing = 6;
			break;
		case 10:
		case 11:
		case 12:
			timing = 5;
			break;
		case 13:
		case 14:
		case 15:
			timing = 4;
			break;
		case 16:
		case 17:
		case 18:
			timing = 3;
			break;
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
			timing = 2;
			break;
		default:
			timing = 1;
			break;
	}

	if (clock > timing)
	{
		moveDown();
	}
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
	unsigned int old_lines = lines;

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
		{
			clearLine(i);
			lines++;
			old_lines++;
		}
	}

	switch (lines - old_lines)
	{
		case 1:
			score += 100;
			break;
		case 2:
			score += 300;
			break;
		case 3:
			score += 500;
			break;
		case 4:
			score += 800;
			break;
	}

	if (lines >= 3050)
		level = 29;
	else if (lines >= 2850)
		level = 28;
	else if (lines >= 2650)
		level = 27;
	else if (lines >= 2450)
		level = 26;
	else if (lines >= 2250)
		level = 25;
	else if (lines >= 2060)
		level = 24;
	else if (lines >= 1880)
		level = 23;
	else if (lines >= 1710)
		level = 22;
	else if (lines >= 1650)
		level = 21;
	else if (lines >= 1650)
		level = 20;
	else if (lines >= 1510)
		level = 19;
	else if (lines >= 1380)
		level = 18;
	else if (lines >= 1260)
		level = 17;
	else if (lines >= 1150)
		level = 16;
	else if (lines >= 1050)
		level = 15;
	else if (lines >= 950)
		level = 14;
	else if (lines >= 850)
		level = 13;
	else if (lines >= 750)
		level = 12;
	else if (lines >= 650)
		level = 11;
	else if (lines >= 550)
		level = 10;
	else if (lines >= 450)
		level = 9;
	else if (lines >= 360)
		level = 8;
	else if (lines >= 280)
		level = 7;
	else if (lines >= 210)
		level = 6;
	else if (lines >= 150)
		level = 5;
	else if (lines >= 100)
		level = 4;
	else if (lines >= 60)
		level = 3;
	else if (lines >= 30)
		level = 2;
	else if (lines >= 10)
		level = 1;
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

void Game::drop()
{
	int bonus = std::get<0>(tetromino_shadow[0]) - std::get<0>(tetromino_pos[0]);

	clock = 0;
	for (int i = 0; i < 4; ++i)
		tetromino_pos[i] = tetromino_shadow[i];
	score += bonus * 2;
}


void Game::swapHold()
{
	if (holdLock)
		return;
	char tmp = tetromino;
	tetromino = hold;
	hold = tmp;
	if (tetromino == EMPTY)
		spawnNewPiece();
	else
		spawnNewPiece(tetromino);
	holdLock = true;
}
