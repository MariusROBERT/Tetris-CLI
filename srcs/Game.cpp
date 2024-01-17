#include "Game.hpp"

Game::Game() : map(), piece_pos(), piece_color(1)
{
	piece_pos[0] = {0, 3};
	piece_pos[1] = {0, 4};
	piece_pos[2] = {0, 5};
	piece_pos[3] = {0, 6};
}

char Game::getCase(unsigned int x, unsigned int y) const
{
	for	(int i = 0; i < 4; ++i)
		if (std::get<0>(piece_pos[i]) == x && std::get<1>(piece_pos[i]) == y)
			return piece_color;
	return map[x][y];
}

void Game::moveDown()
{
	bool can_move = true;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<0>(piece_pos[i]) == 19 || map[std::get<0>(piece_pos[i]) + 1][std::get<1>(piece_pos[i])])
			can_move = false;

	if (can_move)
		for	(int i = 0; i < 4; ++i)
			piece_pos[i] = {std::get<0>(piece_pos[i]) + 1, std::get<1>(piece_pos[i])};
}

void Game::moveLeft()
{
	bool can_move = true;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<1>(piece_pos[i]) == 0 || map[std::get<0>(piece_pos[i])][std::get<1>(piece_pos[i]) - 1])
			can_move = false;

	if (can_move)
		for	(int i = 0; i < 4; ++i)
			piece_pos[i] = {std::get<0>(piece_pos[i]), std::get<1>(piece_pos[i]) - 1};
}

void Game::moveRight()
{
	bool can_move = true;

	for (int i = 0; i < 4 && can_move; ++i)
		if (std::get<1>(piece_pos[i]) == 9 || map[std::get<0>(piece_pos[i])][std::get<1>(piece_pos[i]) + 1])
			can_move = false;

	if (can_move)
		for	(int i = 0; i < 4; ++i)
			piece_pos[i] = {std::get<0>(piece_pos[i]), std::get<1>(piece_pos[i]) + 1};
}

void Game::printMap() const
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 10; ++j)
			std::cout << (int)map[i][j];
		std::cout << std::endl;
	}
}
