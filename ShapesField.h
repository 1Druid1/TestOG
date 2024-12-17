#pragma once

#include<SFML/Graphics.hpp>
#include <vector>
#include <random>

class ShapesField;



class States
{
public:
	virtual ~States();
	virtual void handle(ShapesField& shapesfield) = 0;
	virtual void entryAction(ShapesField& shapesfield) = 0;
	virtual void exitAction(ShapesField& shapesfield) = 0;
};


class StopState : public States
{
	virtual void handle(ShapesField& shapesfield) override;
	virtual void entryAction(ShapesField& shapesfield) override;
	virtual void exitAction(ShapesField& shapesfield) override;
};

class SpinState : public States
{
private:
	sf::Clock spin_clock;
	float spin_delta_time;
	bool time_out;

public:
	bool isTimeOut();
	virtual void handle(ShapesField& shapesfield) override;
	virtual void entryAction(ShapesField& shapesfield) override;
	virtual void exitAction(ShapesField& shapesfield) override;
};


class ScoringState : public States
{
private:
	sf::Clock scoring_clock;
	float scoring_delta_time;
	bool complete_spin;

public:
	bool isSpinComplete();
	virtual void handle(ShapesField& shapesfield) override;
	virtual void entryAction(ShapesField& shapesfield) override;
	virtual void exitAction(ShapesField& shapesfield) override;
};


class ShapesField
{
private:
	float start_pos_x;
	float start_pos_y;
	unsigned int rows;
	unsigned int columns;
	float cell_width;
	float cell_height;
	std::vector<sf::Shape*> shape_types;
	std::vector<std::vector<sf::Shape*>> shapes;
	sf::RenderWindow* window;
	sf::RectangleShape border;
	sf::RectangleShape white_rect_bot;
	sf::RectangleShape white_rect_top;
	float base_speed;
	float slot_speed;
	float slow_speed;
	float delta_time;
	sf::Shape* generateRandShape(float posx, float posy);
	States* currentState;
	int score;

	void deleteOldShapes();
	void alignmentSlots(float dT);

public:
	ShapesField(float x, float y, unsigned int r, unsigned int c, float w, float h, std::vector<sf::Shape*> v, sf::RenderWindow* _window, float speed);
	void drawField();
	void moveSlots(float dT);
	bool stopSlots(float dT);
	float getBaseSpeed();
	void setSlotSpeed(float speed);
	void setState(States* state);
	States* getState();
	void update(float dT);
	float getDeltaTime();
	void scoring();
	int getScore();
};
