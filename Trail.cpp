#include <SFML/Graphics.hpp>

template<class T>
T lerp(const T& start, const T& end, float alpha)
{
    if (alpha < 0) return T(start);
    if (alpha > 1) return T(end);

    return (1 - alpha) * start + alpha * end;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");
    sf::CircleShape shape(20);
    shape.setOrigin(20, 20);
    shape.setFillColor(sf::Color::Green);
    sf::CircleShape follower(20);
    follower.setOrigin(20, 20);
    follower.setFillColor(sf::Color::Green);
    sf::CircleShape fellow(20);
    fellow.setOrigin(20, 20);
    fellow.setFillColor(sf::Color::Green);
    
    //float alpha = 0.002;
    float speed = 3;

    sf::Vector2f position;
    sf::Vector2f positionf(0,0);
    sf::Vector2f position_f(0,0);

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f tragetPosition = (sf::Vector2f)sf::Mouse::getPosition(window);

        position = lerp(position, tragetPosition, 0.01);
        positionf = lerp(positionf, position, 0.01);
        position_f = lerp(position_f, positionf, 0.01);


        shape.setPosition(position);
        follower.setPosition(positionf);
        fellow.setPosition(position_f);


        window.clear();
        window.draw(shape);
        window.draw(follower);
        window.draw(fellow);

        window.display();
    }

    return 0;
}