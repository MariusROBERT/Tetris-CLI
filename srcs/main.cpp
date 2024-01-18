#include <utility>  // for move
#include <vector>   // for vector

#include "ftxui/component/component.hpp"       // for Button, Renderer, Vertical
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, text, Element, hbox, separator, size, vbox, border, frame, vscroll_indicator, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color, Color::Default, Color::GrayDark, Color::White
#include "ftxui/component/event.hpp"           // for Event
#include "Game.hpp"

using namespace ftxui;

Elements getDisplay(char tetromino);

int main()
{
	auto screen = ScreenInteractive::TerminalOutput();

	size_t time = 0;
	Event lastEvent;

	Game game = Game();

	auto component =
			Renderer([&]
					 {
						 if (lastEvent == Event::ArrowLeft || lastEvent == Event::Character(MOVE_LEFT))
							 game.moveLeft();
						 else if (lastEvent == Event::ArrowRight || lastEvent == Event::Character(MOVE_RIGHT))
							 game.moveRight();
						 else if (lastEvent == Event::ArrowDown || lastEvent == Event::Character(MOVE_DOWN))
							 game.moveDown();
						 else if (lastEvent == Event::Character(ROTATE_RIGHT))
							 game.turnRight();
						 else if (lastEvent == Event::Character(ROTATE_LEFT))
							 game.turnLeft();
						 else if (lastEvent == Event::Character(HOLD))
							 game.swapHold();

						 if (time > 20)
						 {
							 game.moveDown();
							 time = 0;
						 }

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

						 Elements holdDisplay = getDisplay(game.getHold());
						 auto leftPanel = vbox({
														 filler()| flex,
														 window(text("-Hold"),
																vbox(std::move(holdDisplay))) | hcenter,
														 filler() | size(WIDTH, EQUAL, 20)
												 }) | flex;
						 ;
						 auto gamePanel =
								 vbox(std::move(showMap)) | size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 20);

						 Elements nextDisplay = getDisplay(game.getNext());

						 auto rightPanel = vbox({
														filler()| flex,
														window(text("-Next"),
															   vbox(std::move(nextDisplay))) | hcenter,
														filler() | size(WIDTH, EQUAL, 20)
						 }) | flex;
						 auto box = hbox({window(text("Tetris") | hcenter, hbox({
																						leftPanel,
																						separator(),
																						gamePanel,
																						separator(),
																						rightPanel,
																				})),
										  filler()}) | size(HEIGHT, EQUAL, 22);

						 return box;
					 });


	component |= CatchEvent([&](const Event& event)
							{
								if (event == Event::Event::ArrowRight ||
									event == Event::Event::ArrowLeft ||
									event == Event::Event::ArrowDown ||
									event == Event::Event::Character(ROTATE_LEFT) ||
									event == Event::Event::Character(ROTATE_RIGHT) ||
									event == Event::Event::Character(MOVE_LEFT) ||
									event == Event::Event::Character(MOVE_RIGHT) ||
									event == Event::Event::Character(MOVE_DOWN) ||
									event == Event::Event::Character(HOLD))
								{
									lastEvent = event;
									return true;
								}
								return false;
							});

	std::atomic<bool> refresh = true;
	std::thread refresh_ui([&] {
		while (refresh) {
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(0.05s);
			screen.Post([&] {
				time++;
			});
			screen.Post(Event::Custom);
		}
	});

	screen.Loop(component);
	refresh = false;
	refresh_ui.join();
	return EXIT_SUCCESS;
}

Elements getDisplay(char tetromino)
{
	Elements nextDisplay;

	Elements line;
	switch (tetromino)
	{
		case I:
			line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
			line.clear();
			for (int i = 0; i < 4; ++i)
				line.push_back(bgcolor(Color::CyanLight, text("  ")));
			nextDisplay.push_back(hbox(std::move(line)));
			break;
		case O:
			for (int i = 0; i < 2; ++i)
			{
				line.push_back(text("  "));
				line.push_back(bgcolor(Color::YellowLight, text("  ")));
				line.push_back(bgcolor(Color::YellowLight, text("  ")));
				line.push_back(text("  "));
				nextDisplay.push_back(hbox(std::move(line)));
				line.clear();
			}
			break;
		case T:
			line.push_back(text("  "));
			line.push_back(bgcolor(Color::Magenta, text("  ")));
			nextDisplay.push_back(hbox(std::move(line)));
			line.clear();
			for (int i = 0; i < 3; ++i)
				line.push_back(bgcolor(Color::Magenta, text("  ")));
			line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
			break;
		case S:
			line.push_back(text("  "));
			line.push_back(bgcolor(Color::GreenLight, text("  ")));
			line.push_back(bgcolor(Color::GreenLight, text("  ")));
			line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
			line.clear();
			line.push_back(bgcolor(Color::GreenLight, text("  ")));
			line.push_back(bgcolor(Color::GreenLight, text("  ")));
			nextDisplay.push_back(hbox(std::move(line)));
			break;
		case Z:
			line.push_back(bgcolor(Color::RedLight, text("  ")));
			line.push_back(bgcolor(Color::RedLight, text("  ")));
			nextDisplay.push_back(hbox(std::move(line)));
			line.clear();
			line.push_back(text("  "));
			line.push_back(bgcolor(Color::RedLight, text("  ")));
			line.push_back(bgcolor(Color::RedLight, text("  ")));
			line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
			break;
		case J:
			line.push_back(bgcolor(Color::BlueLight, text("  ")));
			nextDisplay.push_back(hbox(std::move(line)));
			line.clear();
			for (int i = 0; i < 3; ++i)
				line.push_back(bgcolor(Color::BlueLight, text("  ")));
			line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
			break;
		case L:
			line.push_back(text("  "));
			line.push_back(text("  "));
			line.push_back(bgcolor(Color::Orange1, text("  ")));
			line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
			line.clear();
			for (int i = 0; i < 3; ++i)
				line.push_back(bgcolor(Color::Orange1, text("  ")));
			nextDisplay.push_back(hbox(std::move(line)));
			break;
		default:
			line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
			line.clear();
			for (int i = 0; i < 4; ++i)
				line.push_back(text("  "));
			nextDisplay.push_back(hbox(std::move(line)));
	}
	return nextDisplay;
}
