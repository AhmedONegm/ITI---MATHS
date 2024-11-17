#include <SFML/Graphics.hpp>
#include <cmath>

class DraggablePoint {
    sf::CircleShape shape;
    bool isDragging = false;
public:
    DraggablePoint(const sf::Vector2f& position)
    {
        shape = sf::CircleShape(10);
        shape.setOrigin(10, 10);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Blue);
    }

    void beginDrag(const sf::Vector2i& mousePos)
    {
        isDragging = shape.getGlobalBounds().contains((sf::Vector2f)mousePos);
    }

    void drag(const sf::Vector2i& mousePos)
    {
        if (!isDragging) return;
        shape.setPosition((sf::Vector2f)mousePos);
    }

    void endDrag()
    {
        isDragging = false;
    }

    void draw(sf::RenderWindow& window) const
    {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const
    {
        return shape.getPosition();
    }
};

sf::Vector2f reflectPoint(const sf::Vector2f& point, const sf::Vector2f& origin)
{
    sf::Vector2f offset = point - origin;
    return origin + sf::Vector2f(-offset.x, offset.y);
}

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Adjustable Shapes and Reflection");

    DraggablePoint p0(sf::Vector2f(100, 500));
    DraggablePoint p1(sf::Vector2f(400, 100));
    DraggablePoint p2(sf::Vector2f(700, 500));
    DraggablePoint p3 = p0;

    sf::VertexArray line(sf::LineStrip, 4);
    sf::VertexArray triangle(sf::Triangles, 3);
    sf::VertexArray reflectedTriangle(sf::Triangles, 3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                p0.beginDrag(sf::Mouse::getPosition(window));
                p1.beginDrag(sf::Mouse::getPosition(window));
                p2.beginDrag(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                p0.endDrag();
                p1.endDrag();
                p2.endDrag();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            p0.drag(sf::Mouse::getPosition(window));
            p1.drag(sf::Mouse::getPosition(window));
            p2.drag(sf::Mouse::getPosition(window));
        }

        // Update line
        line[0].position = p0.getPosition();
        line[1].position = p1.getPosition();
        line[2].position = p2.getPosition();
        line[3].position = p3.getPosition();

        // Update triangle
        triangle[0].position = p0.getPosition();
        triangle[1].position = p1.getPosition();
        triangle[2].position = p2.getPosition();

        // Reflect triangle points
        reflectedTriangle[0].position = reflectPoint(p0.getPosition());
        reflectedTriangle[1].position = reflectPoint(p1.getPosition());
        reflectedTriangle[2].position = reflectPoint(p2.getPosition());

        window.clear(sf::Color::White);

        // Draw elements
        window.draw(line);
        window.draw(triangle);
        window.draw(reflectedTriangle);
        p0.draw(window);
        p1.draw(window);
        p2.draw(window);

        window.display();
    }

    return 0;
}
