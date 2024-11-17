#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14f;

void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle) {
    int pointCount = shape.getPointCount();
    shape.setPoint(0, center);
    for (int i = 1; i < pointCount; i++)
    {
        shape.setPoint(i, sf::Vector2f(center.x + radius * cos(i * (endAngle - startAngle) / (pointCount - 1) + startAngle), center.y + radius * sin(i * (endAngle - startAngle) / (pointCount - 1) + startAngle)));
    }
}

sf::Vector2f toCartesian(float angle, float length) {
    return sf::Vector2f(std::cos(angle) * length, std::sin(angle) * length);
}

bool isPointInRange(const sf::Vector2f& point, const sf::Vector2f& center, float radius) {
    return std::sqrt(std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2)) <= radius;
}

bool isPointInFOV(const sf::Vector2f& point, const sf::Vector2f& center, float radius, float angle, float fov) {
    if (!isPointInRange(point, center, radius)) return false;

    sf::Vector2f direction = point - center;
    float pointAngle = std::atan2(direction.y, direction.x);
    float deltaAngle = std::fmod(pointAngle - angle + 3 * PI, 2 * PI) - PI;

    return std::abs(deltaAngle) <= fov / 2;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "FOV with SFML");
    window.setFramerateLimit(60);

    float radius = 100.f;
    float fovAngle = PI / 3;
    sf::Vector2f playerPosition(400, 300);
    sf::Vector2f staticPosition(200, 300);

    sf::CircleShape circleA(10);
    circleA.setFillColor(sf::Color::Red);
    circleA.setOrigin(10, 10);
    circleA.setPosition(staticPosition);

    sf::CircleShape circleB(10);
    circleB.setFillColor(sf::Color::Blue);
    circleB.setOrigin(10, 10);
    circleB.setPosition(playerPosition);

    float angle = 0.f;
    sf::ConvexShape fovCone, arc(30);
    fovCone.setPointCount(3);
    fovCone.setFillColor(sf::Color(0, 255, 0, 100));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerPosition.y -= 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerPosition.y += 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerPosition.x -= 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerPosition.x += 2;
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        angle = std::atan2(mousePos.y - playerPosition.y, mousePos.x - playerPosition.x);

        fovCone.setPoint(0, playerPosition);
        fovCone.setPoint(1, playerPosition + toCartesian(angle - fovAngle / 2, radius));
        fovCone.setPoint(2, playerPosition + toCartesian(angle + fovAngle / 2, radius));
        updateArc(arc, playerPosition, radius, angle + 3.14 / 6, angle - 3.14 / 6);

        if (isPointInFOV(staticPosition, playerPosition, radius, angle, fovAngle)) {
            arc.setFillColor(sf::Color(255, 0, 0, 100));
            fovCone.setFillColor(sf::Color(255, 0, 0, 100));
        }
        else {
            arc.setFillColor(sf::Color(0, 255, 0, 100));
            fovCone.setFillColor(sf::Color(0, 255, 0, 100));
        }

        circleB.setPosition(playerPosition);

        window.clear();
        window.draw(circleA);
        window.draw(circleB);
        window.draw(fovCone);
        window.draw(arc);
        window.display();
    }

    return 0;
}
