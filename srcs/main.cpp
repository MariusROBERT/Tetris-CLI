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

Element getDisplayCase(char value);

ButtonOption ButtonStyle();

int main()
{
	auto screen = ScreenInteractive::TerminalOutput();

	Event lastEvent;

	Game game;
	Component buttonStart, buttonQuit, buttons;
	unsigned int bestScore = 0;

	buttonStart = Button("Play", [&]
	{
		if (game.isPaused())
			return game.unPause();
		if (!game.isLost())
			return;
		if (game.getScore() > bestScore)
			bestScore = game.getScore();
		game = Game();
		game.start();
	}, ButtonStyle()) | hcenter;

	buttonQuit = Button("Quit", [&]
	{
		if (game.isLost())
			screen.Exit();
	}, ButtonStyle()) | hcenter;

	buttons = Container::Vertical(
			{
					buttonStart,
					buttonQuit
			});

	Component component;
	Element leftPanel, rightPanel, gamePanel, box;


	component = Renderer(buttons, [&]
	{
		if (game.isLost() || game.isPaused())
		{
			leftPanel = vbox({window(text("BestScore"),
									 vbox(text(std::to_string(bestScore))
										  | center)) | size(WIDTH, GREATER_THAN, 11) | hcenter
							 }) | flex | size(WIDTH, EQUAL, 20);

			if (game.getScore() <= bestScore || game.isPaused())
				gamePanel = vbox({filler(),
								  buttonStart->Render(),
								  filler(),
								  buttonQuit->Render(),
								  filler()
								 }) | size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 20);
			else
				gamePanel = vbox({filler(),
								  paragraphAlignCenter(
										  "New best score: " + std::to_string(game.getScore())) |
								  borderDashed | size(WIDTH, EQUAL, 16) | hcenter | flex,
								  filler(),
								  buttonStart->Render(),
								  filler(),
								  buttonQuit->Render(),
								  filler()
								 }) | size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 20);

			rightPanel = vbox({window(text("-Score"),
									  vbox(text(std::to_string(game.getScore()))
										   | center)) | size(WIDTH, GREATER_THAN, 11) | hcenter
							  }) | flex | size(WIDTH, EQUAL, 20);
		}
		else
		{
			game.loop();

			leftPanel = vbox({
									 filler(),
									 window(text("BestScore"),
											vbox(text(std::to_string(bestScore))
												 | center)) | size(WIDTH, GREATER_THAN, 11) | hcenter,
									 filler(),
									 window(text("-Hold"),
											vbox(getDisplay(game.getHold()))) | hcenter,
									 filler() | size(WIDTH, EQUAL, 20)
							 });

			Elements showMap;
			for (int i = 0; i < 20; ++i)
			{
				Elements line;
				for (int j = 0; j < 10; ++j)
					line.push_back(getDisplayCase(game.getCase(i, j)));
				showMap.push_back(hbox(std::move(line)));
			}

			gamePanel = vbox(std::move(showMap)) | size(WIDTH, EQUAL, 20) | size(HEIGHT, EQUAL, 20);

			rightPanel = vbox({
									  filler(),
									  window(text("-Score"),
											 vbox(text(std::to_string(game.getScore()))
												  | center)) | size(WIDTH, GREATER_THAN, 11) | hcenter,
									  filler(),
									  window(text("-Lines"),
											 vbox(text(std::to_string(game.getLines()))
												  | center)) | size(WIDTH, GREATER_THAN, 9) | hcenter,
									  filler(),
									  window(text("-Level"),
											 vbox(text(std::to_string(game.getLevel()))
												  | center)) | size(WIDTH, GREATER_THAN, 9) | hcenter,
									  filler(),
									  window(text("-Next"),
											 vbox(getDisplay(game.getNext())) | center) | hcenter,
									  filler() | size(WIDTH, EQUAL, 20)
							  });
		}

		box = hbox({window(text("Tetris") | hcenter,
						   hbox({
										leftPanel,
										separator(),
										gamePanel,
										separator(),
										rightPanel,
								})),
					filler()}) | size(HEIGHT, EQUAL, 22);

		return box;
	});

	component |= CatchEvent(
			[&](const Event &event)
			{
				if (game.isPaused())
				{
					if (event == Event::Character(PAUSE))
						game.unPause();
					else
						return false;
					return true;
				}
				else if (!game.isLost())
				{
					if (event == Event::ArrowLeft || event == Event::Character(MOVE_LEFT))
						game.moveLeft();
					else if (event == Event::ArrowRight || event == Event::Character(MOVE_RIGHT))
						game.moveRight();
					else if (event == Event::ArrowDown || event == Event::Character(MOVE_DOWN))
						game.moveDown();
					else if (event == Event::Character(ROTATE_RIGHT))
						game.turnRight();
					else if (event == Event::Character(ROTATE_LEFT))
						game.turnLeft();
					else if (event == Event::Character(HOLD))
						game.swapHold();
					else if (event == Event::Character(DROP))
						game.drop();
					if (event == Event::Character(PAUSE))
						game.pause();
					else
						return false;
					return true;
				}

				return false;
			});

	std::atomic<bool> refresh = true;
	std::thread refresh_ui(
			[&]
			{
				while (refresh)
				{
					using namespace std::chrono_literals;
					std::this_thread::sleep_for(0.01666s); //60fps
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

Element getDisplayCase(char value)
{
	switch (value)
	{
		case tetrominoes::EMPTY:
			return (text("  "));
		case tetrominoes::I:
			return (text("  ") | bgcolor(Color::CyanLight));
		case tetrominoes::O:
			return (text("  ") | bgcolor(Color::YellowLight));
		case tetrominoes::T:
			return (text("  ") | bgcolor(Color::Magenta));
		case tetrominoes::S:
			return (text("  ") | bgcolor(Color::GreenLight));
		case tetrominoes::Z:
			return (text("  ") | bgcolor(Color::RedLight));
		case tetrominoes::J:
			return (text("  ") | bgcolor(Color::BlueLight));
		case tetrominoes::L:
			return (text("  ") | bgcolor(Color::Orange1));
		case -tetrominoes::I:
			return (text("::") | color(Color::CyanLight));
		case -tetrominoes::O:
			return (text("::") | color(Color::YellowLight));
		case -tetrominoes::T:
			return (text("::") | color(Color::Magenta));
		case -tetrominoes::S:
			return (text("::") | color(Color::GreenLight));
		case -tetrominoes::Z:
			return (text("::") | color(Color::RedLight));
		case -tetrominoes::J:
			return (text("::") | color(Color::BlueLight));
		case -tetrominoes::L:
			return (text("::") | color(Color::Orange1));
		default:
			return (text("  "));
	}
}

ButtonOption ButtonStyle()
{
	auto option = ButtonOption::Simple();
	option.transform = [](const EntryState &s)
	{
		auto element = text(s.label);
		if (s.focused)
			element |= inverted;
		return element | center | border | size(HEIGHT, EQUAL, 5) | size(WIDTH, EQUAL, 14);
	};
	return option;
}
