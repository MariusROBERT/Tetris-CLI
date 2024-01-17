#include <string>  // for to_string, operator+
#include <utility>  // for move
#include <vector>   // for vector

#include "ftxui/component/component.hpp"       // for Button, Renderer, Vertical
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, text, Element, hbox, separator, size, vbox, border, frame, vscroll_indicator, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color, Color::Default, Color::GrayDark, Color::White
#include "ftxui/component/event.hpp"           // for Event

using namespace ftxui;

std::string EventsHandler(const Event &event)
{
	std::string out;

	if (event.is_character())
	{
		if (event.character() == " ")
			out += "Space";
		else
			out += event.character();
	}
	else if (event == Event::ArrowLeft)
		out += "Left";
	else if (event == Event::ArrowRight)
		out += "Right";
	else if (event == Event::ArrowDown)
		out += "Down";
	return out;
}

int main()
{
	auto screen = ScreenInteractive::TerminalOutput();

	std::vector<Event> keys;
	std::vector<std::vector<char>> map;

	for (int i = 0; i < 20; i++)
	{
		std::vector<char> row;
		row.reserve(10);
		for (int j = 0; j < 10; ++j)
			row.push_back(0);
		map.push_back(row);
	}

	map[2][3] = 1;
	map[2][4] = 2;
	map[2][5] = 3;
	map[2][6] = 4;
	map[5][8] = -4;

	auto component =
			Renderer([&]
					 {
//						 Elements children;
						 for (size_t i = std::max(0, (int) keys.size() - 20); i < keys.size(); ++i)
						 {
							 std::string e = EventsHandler(keys[i]);
							 if (e == "Left") {
								 //move left
							 } else if (e == "Right") {
								 // move Right
							 } else if (e == "Down") {
								 // move Down
							 }
						 }
//						 keys.resize(20);

						 Elements showMap;
						 for (size_t i = 0; i < 20; ++i)
						 {
							 Elements line;
							 for (int j = 0; j < 10; ++j)
								 switch (abs(map[i][j]))
								 {
									 case 0:
										 line.push_back(text("  "));
										 break;
									 case 1:
										 line.push_back(text("  ") | bgcolor(Color::Blue));
										 break;
									 case 2:
										 line.push_back(text("  ") | bgcolor(Color::RedLight));
										 break;
									 case 3:
										 line.push_back(text("  ") | bgcolor(Color::Green));
										 break;
									 case 4:
										 line.push_back(text("  ") | bgcolor(Color::Orange1));
										 break;
								 }
						 	showMap.push_back(hbox(std::move(line)));
						 }

						 auto leftPanel = text("") | size(WIDTH, GREATER_THAN, 15);
						 auto gamePanel =
								 vbox(std::move(showMap)) | size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 20);
						 auto rightPanel = text("") | size(WIDTH, GREATER_THAN, 15);
						 auto box = window(text("Game") | hcenter, hbox({
																				leftPanel,
																				separator(),
																				gamePanel,
																				separator(),
																				rightPanel,
																		}));

						 return box;
					 });


	component |= CatchEvent([&](Event event)
							{
								keys.push_back(event);
								return true;
							});

	screen.Loop(component);
}
