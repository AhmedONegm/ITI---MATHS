#include <SFML/Graphics.hpp>

void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle) {
    int pointCount = shape.getPointCount();
    shape.setPoint(0, center);
    for (int i = 1; i < pointCount; i++)
    {
        shape.setPoint(i, sf::Vector2f(center.x + radius * cos(i * (endAngle - startAngle) / (pointCount - 1) + startAngle), center.y + radius * sin(i * (endAngle - startAngle) / (pointCount - 1) + startAngle)));
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "PACMAN");
    sf::Vector2f center(100, 100);

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Yellow);

    sf::ConvexShape shape(20);
    shape.setFillColor(sf::Color::Black);
    
    sf::Clock clock;
    float time;
        

    bool rkey=true, lkey=false, ukey=false, dkey=false;
    updateArc(shape, center, 100, -3.14 / 4, 3.14 / 4);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    ukey = true;
                    rkey = false; lkey = false; dkey = false;
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    dkey = true;
                    rkey = false; lkey = false; ukey = false;
                }
                else if (event.key.code == sf::Keyboard::Right) {
                    rkey = true;
                    lkey = false; ukey = false; dkey = false;
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    lkey = true;
                    rkey = false; ukey = false; dkey = false;
                }
            }
        }
        time = clock.getElapsedTime().asSeconds();
        if (rkey)
            updateArc(shape, center, 100, (3.14*(sin(time)+1)/8 - 3.14 / 4), (-3.14 * (sin(time) + 1) / 8 + 3.14 / 4));
        if (lkey)
            updateArc(shape, center, 100, (-3.14 * (sin(time) + 1) /8 -9.42 / 4), (3.14 * (sin(time) + 1) / 8 -15.7 / 4));
        if (ukey)
            updateArc(shape, center, 100, (-3.14 * (sin(time) + 1) / 8 -3.14 / 4), (+3.14 * (sin(time) + 1) / 8 -9.42 / 4));
        if (dkey)
            updateArc(shape, center, 100, (3.14 * (sin(time) + 1) / 8 +3.14 / 4), (-3.14 * (sin(time) + 1) / 8 + 9.42 / 4));

        window.clear();
        window.draw(circle);
        
        window.draw(shape);
        window.display();
    }

    return 0;
}