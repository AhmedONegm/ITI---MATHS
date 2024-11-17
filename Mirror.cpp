#include <SFML/Graphics.hpp>

sf::Color operator*(float value, sf::Color color)
{
	return sf::Color(color.r * value, color.g * value, color.b * value, color.a * value);
}





class DraggabelPoint {

	sf::CircleShape shape;
	bool isDragging;
public:
	DraggabelPoint(const sf::Vector2f& position)
	{
		shape = sf::CircleShape(10);
		shape.setOrigin(10, 10);
		shape.setPosition(position);
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

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	sf::Vector2f getPosition()
	{
		return shape.getPosition();
	}
};

float dotproduct(sf::Vector2f v, sf::Vector2f u) {
	return (v.x * u.x + v.y * u.y);
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Template!");

	DraggabelPoint p0(sf::Vector2f(100, 500));
	DraggabelPoint p1(sf::Vector2f(400, 100));
	DraggabelPoint p2(sf::Vector2f(700, 500));
	DraggabelPoint p3=p0;
	DraggabelPoint mirror1(sf::Vector2f(500, 200));
	DraggabelPoint mirror2(sf::Vector2f(800, 600));

	sf::VertexArray line(sf::LineStrip, 4);
	sf::VertexArray line2(sf::LineStrip, 2);
	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0].color = sf::Color::Red;
	triangle[1].color = sf::Color::Blue;
	triangle[2].color = sf::Color::Green;

	while (window.isOpen())
	{
		p3 = p0;
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
				mirror1.beginDrag(sf::Mouse::getPosition(window));
				mirror2.beginDrag(sf::Mouse::getPosition(window));
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				p0.endDrag();
				p1.endDrag();
				p2.endDrag();
				mirror1.endDrag();
				mirror2.endDrag();
			}
		}


		if (sf::Mouse::isButtonPressed)
		{
			p0.drag(sf::Mouse::getPosition(window));
			p1.drag(sf::Mouse::getPosition(window));
			p2.drag(sf::Mouse::getPosition(window));
			mirror1.drag(sf::Mouse::getPosition(window));
			mirror2.drag(sf::Mouse::getPosition(window));
		}

		line[0].position = p0.getPosition();
		line[1].position = p1.getPosition();
		line[2].position = p2.getPosition();
		line[3].position = p3.getPosition();
		
		line2[0].position = mirror1.getPosition();
		line2[1].position = mirror2.getPosition();
		sf::Vector2f direction = line2[1].position - line2[0].position;
		
		direction /= sqrt(dotproduct(direction, direction));

		sf::Vector2f d1 = line[0].position - line2[0].position;
		sf::Vector2f d2 = line[1].position - line2[0].position;
		sf::Vector2f d3 = line[2].position - line2[0].position;

		triangle[0] = line2[0].position + 2 * dotproduct(d1, direction) * direction - d1;
		triangle[1] = line2[0].position + 2 * dotproduct(d2, direction) * direction - d2;
		triangle[2] = line2[0].position + 2 * dotproduct(d3, direction) * direction - d3;
		
		window.clear();


		p0.draw(window);
		p1.draw(window);
		p2.draw(window);
		mirror1.draw(window);
		mirror2.draw(window);

		window.draw(line);
		window.draw(line2);
		window.draw(triangle);

		window.display();
	}

	return 0;
}