#include "ShapesField.h"


ShapesField::ShapesField(float x, float y, unsigned int r, unsigned int c, float w, float h, std::vector<sf::Shape*> v, sf::RenderWindow* _window, float speed)
	: start_pos_x(x), start_pos_y(y), rows(r), columns(c), cell_width(w), cell_height(h), shape_types(v), window(_window), base_speed(speed)
{
	rows = rows + 2;
	shapes = { rows, std::vector<sf::Shape*>{columns} };

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			shapes[i][j] = generateRandShape(cell_width * (j + 1), cell_height * (i + 1));
		}
	}
	
	border.setSize(sf::Vector2f(cell_width * columns + 1, cell_height * (rows - 2)));
	border.setFillColor(sf::Color::Transparent);
	border.setPosition(cell_width - 1, cell_height - 1);
	border.setOutlineThickness(5);
	border.setOutlineColor(sf::Color::Black);
	white_rect_top.setSize(sf::Vector2f(cell_width * columns + 1, 800));
	white_rect_top.setOrigin(sf::Vector2f(0, white_rect_top.getSize().y));
	white_rect_top.setFillColor(sf::Color::White);
	white_rect_top.setPosition(border.getPosition().x, border.getPosition().y - border.getOutlineThickness());
	white_rect_bot.setSize(sf::Vector2f(cell_width * columns + 1, 800));
	white_rect_bot.setFillColor(sf::Color::White);
	white_rect_bot.setPosition(border.getPosition().x, border.getPosition().y + (cell_height * (rows - 2) + 5));
	slot_speed = base_speed;
	slow_speed = base_speed * 0.2;
	score = 0;
}


sf::Shape* ShapesField::generateRandShape(float posx, float posy)
{
	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, shape_types.size() - 1);
	int n = distribution(generator);

	sf::ConvexShape* t = new sf::ConvexShape();
	size_t pc = shape_types[n]->getPointCount();
	t->setPointCount(pc);
	for (size_t i = 0; i < pc; i++)
	{
		t->setPoint(i, shape_types[n]->getPoint(i));
	}
	t->setFillColor(shape_types[n]->getFillColor());
	t->setPosition(sf::Vector2f(posx, posy));
	return t;
}


void ShapesField::deleteOldShapes()
{
	for (int j = 0; j < columns; j++)
	{
		if (shapes[0][j]->getPosition().y + shapes[0][j]->getGlobalBounds().getSize().y <= border.getPosition().y)
		{
			delete shapes[0][j];
			shapes[0][j] = nullptr;
			for (int t = 0; t < rows - 1; t++)
			{
				shapes[t][j] = shapes[t + 1][j];
			}
			shapes[rows - 1][j] = generateRandShape(cell_width * (j + 1), shapes[rows - 2][j]->getPosition().y + cell_height);
		}
	}
}

void ShapesField::drawField()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (shapes[i][j] != nullptr) { window->draw(*shapes[i][j]); }
		}
	}

	window->draw(border);
	window->draw(white_rect_bot);
	window->draw(white_rect_top);
}


void ShapesField::moveSlots(float dT)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (j % 2 == 1) { shapes[i][j]->move(0.0f, -1.0f * dT * slot_speed * 1.5f); }
			else { shapes[i][j]->move(0.0f, -1.0f * dT * slot_speed); }
		}
	}
	deleteOldShapes();
}


bool ShapesField::stopSlots(float dT)
{
	slot_speed -= slow_speed;
	if (slot_speed <= slow_speed) { slow_speed = slow_speed / 2; }
	if (slot_speed <= 1)
	{
		slot_speed = 0;
		alignmentSlots(dT);
		slow_speed = base_speed * 0.2;
		return 1;
	}
	return 0;
}


void ShapesField::alignmentSlots(float dT)
{
	for (int j = 0; j < columns; j++)
	{
		if (shapes[0][j]->getPosition().y + shapes[0][j]->getGlobalBounds().getSize().y / 2.0f <= border.getPosition().y)
		{
			while (shapes[1][j]->getPosition().y >= border.getPosition().y + 3)
			{
				for (int i = 0; i < rows; i++)
				{
					shapes[i][j]->move(0.0f, -0.01f * dT);
				}
			}
		}
		else if (shapes[0][j]->getPosition().y + shapes[0][j]->getGlobalBounds().getSize().y / 2.0f > border.getPosition().y)
		{
			while (shapes[0][j]->getPosition().y < border.getPosition().y + 3)
			{
				for (int i = 0; i < rows; i++)
				{
					shapes[i][j]->move(0.0f, 0.01f * dT);
				}
			}
		}
		
	}
	deleteOldShapes();
}

void ShapesField::setSlotSpeed(float speed) { slot_speed = speed; }
float ShapesField::getBaseSpeed() { return base_speed; }
float ShapesField::getDeltaTime() { return delta_time; }
int ShapesField::getScore() { return score; }

void ShapesField::scoring()
{
	int count = 1;
	sf::Shape* temp;
	for (int i = 0; i < rows - 2; i++)
	{
		temp = shapes[i][0];
		for (int j = 1; j < columns; j++)
		{
			if (shapes[i][j]->getFillColor() == temp->getFillColor()) { count++; }
		}
		if (count == columns) { score++; }
		count = 1;
	}
}

void ShapesField::setState(States* state) 
{
	if (currentState != state)
	{
		if (currentState) { currentState->exitAction(*this); }
		currentState = state;
		currentState->entryAction(*this);
	}
	
}

States* ShapesField::getState() { return currentState; }

void ShapesField::update(float dT)
{
	delta_time = dT;
	drawField();
	currentState->handle(*this);
}






States::~States() {}
void States::entryAction(ShapesField& shapesfield) {}
void States::exitAction(ShapesField& shapesfield) {}


void StopState::handle(ShapesField& shapesfield) 
{
}
void StopState::entryAction(ShapesField& shapesfield)
{
}
void StopState::exitAction(ShapesField& shapesfield)
{
}


void SpinState::handle(ShapesField& shapesfield)
{
	shapesfield.moveSlots(shapesfield.getDeltaTime());
	if (spin_clock.getElapsedTime().asSeconds() > 5)
	{
		time_out = 1;
	}
}
void SpinState::entryAction(ShapesField& shapesfield)
{
	spin_clock.restart();
	time_out = 0;
	shapesfield.setSlotSpeed(shapesfield.getBaseSpeed());
}
void SpinState::exitAction(ShapesField& shapesfield)
{
	time_out = 0;
}
bool SpinState::isTimeOut() { return time_out; }



void ScoringState::handle(ShapesField& shapesfield)
{
	shapesfield.moveSlots(shapesfield.getDeltaTime());
	if (scoring_clock.getElapsedTime().asSeconds() >= 1)
	{
		complete_spin = shapesfield.stopSlots(shapesfield.getDeltaTime());
		scoring_clock.restart();
	}
}
void ScoringState::entryAction(ShapesField& shapesfield)
{
	complete_spin = 0;
}
void ScoringState::exitAction(ShapesField& shapesfield)
{
	complete_spin = 0;
	shapesfield.scoring();
}
bool ScoringState::isSpinComplete() { return complete_spin; }