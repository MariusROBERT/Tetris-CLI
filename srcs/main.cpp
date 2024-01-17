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
							 game.moveLeft();
						 else if (lastEvent == Event::ArrowRight)
							 game.moveRight();
						 else if (lastEvent == Event::ArrowDown)
							 game.moveDown();
						 else if (lastEvent == Event::Return)
							 game.lockTetromino();
						 else if (lastEvent == Event::Character('w'))
							 game.turnRight();
						 else if (lastEvent == Event::Character('q'))
							 game.turnLeft();

						 lastEvent = Event::Custom;

						 Elements showMap;
						 for (size_t i = 0; i < 20; ++i)
						 {
							 Elements line;
							 for (int j = 0; j < 10; ++j)
								 switch (abs(game.getCase(i, j)))
								 {
									 case tetrominoes::EMPTY:
										 line.push_back(text("  "));
										 break;
									 case tetrominoes::I:
										 line.push_back(text("  ") | bgcolor(Color::CyanLight));
										 break;
									 case tetrominoes::O:
										 line.push_back(text("  ") | bgcolor(Color::YellowLight));
										 break;
									 case tetrominoes::T:
										 line.push_back(text("  ") | bgcolor(Color::Magenta));
										 break;
									 case tetrominoes::S:
										 line.push_back(text("  ") | bgcolor(Color::GreenLight));
										 break;
									 case tetrominoes::Z:
										 line.push_back(text("  ") | bgcolor(Color::RedLight));
										 break;
									 case tetrominoes::J:
										 line.push_back(text("  ") | bgcolor(Color::BlueLight));
										 break;
									 case tetrominoes::L:
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


	component |= CatchEvent([&](const Event& event)
							{
								if (event == Event::Event::ArrowRight ||
									event == Event::Event::ArrowLeft ||
									event == Event::Event::ArrowDown ||
									event == Event::Event::Return ||
									event == Event::Event::Character('q') ||
									event == Event::Event::Character('w'))
								{
									lastEvent = event;
									return true;
								}
								return false;
							});

	screen.Loop(component);
}

/**/
