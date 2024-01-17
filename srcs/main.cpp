#include <string>  // for to_string, operator+
#include <utility>  // for move
#include <vector>   // for vector

#include "ftxui/component/component.hpp"       // for Button, Renderer, Vertical
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, text, Element, hbox, separator, size, vbox, border, frame, vscroll_indicator, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color, Color::Default, Color::GrayDark, Color::White
#include "ftxui/component/event.hpp"           // for Event
#include "Game.hpp"

using namespace ftxui;

int main()
{
	auto screen = ScreenInteractive::TerminalOutput();

	Event lastEvent;

	Game game = Game();

	auto component =
			Renderer([&]
					 {
						 if (lastEvent == Event::ArrowLeft)
						 {
							 game.moveLeft();
						 }
						 else if (lastEvent == Event::ArrowRight)
						 {
							 game.moveRight();
						 }
						 else if (lastEvent == Event::ArrowDown)
						 {
							 game.moveDown();
						 }

						 Elements showMap;
						 for (size_t i = 0; i < 20; ++i)
						 {
							 Elements line;
							 for (int j = 0; j < 10; ++j)
								 switch (abs(game.getCase(i, j)))
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
								if (event == Event::Event::ArrowRight ||
									event == Event::Event::ArrowLeft ||
									event == Event::Event::ArrowDown)
								{
									lastEvent = event;
									return true;
								}
								return false;
							});

	screen.Loop(component);
}
