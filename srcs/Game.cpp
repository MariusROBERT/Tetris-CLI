#include "Game.hpp"

Game::Game() : map(), tetromino_pos(), tetromino(1), rotation(0), lost(false), hold(EMPTY), holdLock(false)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 7);
	next = (char) distrib(gen);

	spawnNewPiece();
}

char Game::getCase(unsigned int x, unsigned int y) const
{
	for (int i = 0; i < 4; ++i)
		if (std::get<0>(tetromino_pos[i]) == x && std::get<1>(tetromino_pos[i]) == y)
			return tetromino;
	return map[x][y];
}

char Game::getNext() const
{
	return next;
}

char Game::getHold() const
{
	return hold;
}

void Game::moveDown()
{
	bool can_move = true;

	if (lost)
		return;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<0>(tetromino_pos[i]) == 19 ||
			map[std::get<0>(tetromino_pos[i]) + 1][std::get<1>(tetromino_pos[i])])
			can_move = false;


	if (can_move)
		for (int i = 0; i < 4; ++i)
			tetromino_pos[i] = {std::get<0>(tetromino_pos[i]) + 1, std::get<1>(tetromino_pos[i])};
	else
		lockTetromino();
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, 7);

	tetromino = next;
	next = (char) distrib(gen);
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
