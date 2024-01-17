#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <tuple>



class Game
{
private:
	char map[20][10];
	std::tuple<unsigned int, unsigned int> piece_pos[4];
	char piece_color;

public:
	Game();
	[[nodiscard]] char getCase(unsigned int x, unsigned int y) const;

	void moveDown();
	void moveLeft();
	void moveRight();

	void printMap() const;
};


#endif //GAME_HPP
