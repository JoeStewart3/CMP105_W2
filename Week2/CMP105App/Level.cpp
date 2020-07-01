#include "Level.h"

int x;
int y;
//Circle default position is off screen so that it only appears when user wants
int circleX = -1000;
int circleY = -1000;
int firstMousePosX;
int firstMousePosY;
int finalMousePosX;
int finalMousePosY;
int xDifference;
int yDifference;
std::string xyDifferenceOutput;
std::string coords;

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	circle.setRadius(15);
	circle.setPosition(circleX, circleY);
	circle.setFillColor(sf::Color::Green);

	// text
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "Error loading font\n";
	}

	text.setFont(font);
	text.setString(coords);
	text.setCharacterSize(24);
	text.setPosition(300, 0);
	text.setFillColor(sf::Color::Red);

	text2.setFont(font);
	text2.setString(xyDifferenceOutput);
	text2.setCharacterSize(24);
	text2.setPosition(300, 50);
	text2.setFillColor(sf::Color::Red);
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	if (input->isKeyDown(sf::Keyboard::W)) {
		input->setKeyDown(sf::Keyboard::W);
		std::cout << "W was pressed\n";
		input->setKeyUp(sf::Keyboard::W);
	}
	if (input->isKeyDown(sf::Keyboard::J) and input->isKeyDown(sf::Keyboard::K) and input->isKeyDown(sf::Keyboard::L)) {
		input->setKeyDown(sf::Keyboard::J);
		input->setKeyDown(sf::Keyboard::K);
		input->setKeyDown(sf::Keyboard::L);
		std::cout << "JKL is pressed\n";
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
	}
	if (input->isKeyDown(sf::Keyboard::Escape)) {
		input->setKeyDown(sf::Keyboard::Escape);
		window->close();
	}
	if (input->isMouseLDown() == true) {
		firstMousePosX = input->getMouseX();
		firstMousePosY = input->getMouseY();
		xDifference = finalMousePosX - firstMousePosX;
		yDifference = finalMousePosY - firstMousePosY;
	}
	if (input->isMouseLDown() == false) {
		finalMousePosX = input->getMouseX();
		finalMousePosY = input->getMouseY();
	}
	if (input->isMouseRDown() == true) {
		circleX = input->getMouseX();
		circleY = input->getMouseY();
	}
}

// Update game objects
void Level::update()
{
	x = input->getMouseX();
	y = input->getMouseY();
	coords = "MOUSE POSITION: " + std::to_string(x) + ", " + std::to_string(y);
	text.setString(coords);

	std::string xyDifference = std::to_string(xDifference) + ", " + std::to_string(yDifference);
	xyDifferenceOutput = "MOUSE DISPLACEMENT: " + xyDifference;
	text2.setString(xyDifferenceOutput);

	circle.setPosition(circleX, circleY);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(text);
	window->draw(text2);
	window->draw(circle);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}