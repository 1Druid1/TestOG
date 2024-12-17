#include "ShapesField.h"
#include "Button.h"


int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 800), L"TestOG", sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    sf::CircleShape* rect = new sf::CircleShape(50.f);
    rect->setPointCount(4);
    rect->setFillColor(sf::Color::Blue);

    /*sf::ConvexShape* rect2 = new sf::ConvexShape();
    rect2->setPointCount(4);
    rect2->setPoint(0, sf::Vector2f(0, 0));
    rect2->setPoint(1, sf::Vector2f(100, 0));
    rect2->setPoint(2, sf::Vector2f(100, 100));
    rect2->setPoint(3, sf::Vector2f(0, 100));
    rect2->setFillColor(sf::Color::Yellow);*/
    
    sf::CircleShape* circle = new sf::CircleShape(50.f);
    circle->setFillColor(sf::Color::Green);
 
    sf::CircleShape* tri = new sf::CircleShape(50.f);
    tri->setPointCount(3);
    tri->setFillColor(sf::Color::Red);

    std::vector<sf::Shape*> sh;
    sh.push_back(rect);
    sh.push_back(circle);
    sh.push_back(tri);
    //sh.push_back(rect2);

    StopState stop_state;
    SpinState spin_state;
    ScoringState scoring_state;


    ShapesField shapes_field(static_cast<float>(window.getPosition().x) - 400, static_cast<float>(window.getPosition().y), 3, 3, 105, 105, sh, &window, 700, &stop_state);


    Button start_button(700, 100, 200, 100, "START", 50, sf::Color::Green, &window);
    Button stop_button(700, 400, 200, 100, "STOP", 50, sf::Color::Red, &window);
    Button score_field(400, 600, 200, 100, "SUMMARY SCORE: 0", 25, sf::Color::Transparent, &window);

    sf::Clock* clock = new sf::Clock;
    float dT;
    std::string won = "";
    while (window.isOpen())
    {
        sf::Event event;

        dT = clock->restart().asSeconds();
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (start_button.isMouseOver())
                {
                    if (shapes_field.getState() == &stop_state) 
                    {
                        shapes_field.setState(&spin_state);
                        won = "";
                    }
                }
                if (stop_button.isMouseOver())
                {
                    if (shapes_field.getState() == &spin_state)
                    {
                        shapes_field.setState(&scoring_state);
                    }
                }
            }
        }

        if (spin_state.isTimeOut() == 1)
        {
            shapes_field.setState(&scoring_state);
        }
        if (scoring_state.isSpinComplete() == 1)
        {
            int diffscore = shapes_field.getScore();
            shapes_field.setState(&stop_state);
            if (shapes_field.getScore() - diffscore > 0) { won = "YOU WON! \n"; }
        }
        score_field.setButtonText(won + "SUMMARY SCORE: " + std::to_string(shapes_field.getScore()));

        window.clear(sf::Color::White);
        shapes_field.update(dT);
        start_button.drawButton();
        stop_button.drawButton();
        score_field.drawButton();
        window.display();
    }
    return 0;
}