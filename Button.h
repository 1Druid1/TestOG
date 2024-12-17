#pragma once

#include<SFML/Graphics.hpp>


class Button
{
private:
	sf::RectangleShape shape;
	sf::Text button_text;
	sf::RenderWindow* window;
	sf::Font font;

public:
	Button(float x, float y, float width, float height, std::string text, unsigned int char_size, sf::Color fill_color, sf::RenderWindow* _window);
	bool isMouseOver();
	void drawButton();
	void setButtonText(std::string t);
};
