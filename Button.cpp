#include "Button.h"


Button::Button(float x, float y, float width, float height, std::string text, unsigned int char_size, sf::Color fill_color, sf::RenderWindow* _window) : window(_window)
{
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(fill_color);
	button_text.setString(text);
	font.loadFromFile("fonts/font.ttf");
	button_text.setFont(font);
	button_text.setCharacterSize(char_size);
	button_text.setFillColor(sf::Color::Black);
	sf::FloatRect tb = button_text.getLocalBounds();
	button_text.setOrigin(tb.width / 2, tb.height / 2);
	button_text.setPosition(x + width / 2, y + height / 2);
	
}

bool Button::isMouseOver()
{
	return shape.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}

void Button::drawButton()
{
	window->draw(shape);
	window->draw(button_text);
}

void Button::setButtonText(std::string t)
{
	button_text.setString(t);
}