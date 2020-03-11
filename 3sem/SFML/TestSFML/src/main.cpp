#include <SFML\Graphics.hpp>
#include <iostream>

struct point {
	float x;
	float y;
};

int serpinskiy_triangle(point A, point B, point C, int depth, sf::RenderWindow &window) {

	if (depth == 0){
		return 0;
	}

	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(A.x, A.y), sf::Color::Red),
		sf::Vertex(sf::Vector2f(B.x, B.y), sf::Color::Red),
		sf::Vertex(sf::Vector2f(C.x, C.y), sf::Color::Red),
		sf::Vertex(sf::Vector2f(A.x, A.y), sf::Color::Red)
	};

	point a, b, c;
	a.x = (A.x + B.x) / 2;
	a.y = (A.y + B.y) / 2;
	b.x = (C.x + B.x) / 2;
	b.y = (C.y + B.y) / 2;
	c.x = (A.x + C.x) / 2;
	c.y = (A.y + C.y) / 2;

	window.draw(line, 4, sf::LinesStrip);

	serpinskiy_triangle(A, a, c, depth - 1, window);
	serpinskiy_triangle(a, B, b, depth - 1, window);
	serpinskiy_triangle(c, b, C, depth - 1, window);
	 
}

int main()
{
	//создаем окно
	sf::RenderWindow window(sf::VideoMode(800, 800), "My window");
	while (window.isOpen())
	{
		//даем возможность окну закрываться
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//закрашиваем окно в какой-то цвет
		window.clear(sf::Color::White);

		//создаем треугольник
		/*sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(40, 10), sf::Color::Red),
			sf::Vertex(sf::Vector2f(40, 650), sf::Color::Red),
			sf::Vertex(sf::Vector2f(584, 330), sf::Color::Red),
			sf::Vertex(sf::Vector2f(40, 10), sf::Color::Red)
		};

		window.draw(line, 4, sf::LinesStrip);*/

		point a, b, c;
		a.x = 40;
		a.y = 10;
		b.x = 40;
		b.y = 650;
		c.x = 584;
		c.y = 330;

		serpinskiy_triangle(a, b, c, 8, window);

		//создаем круг
		/*sf::CircleShape circle(50);
		circle.setPosition(100, 100);
		circle.setFillColor(sf::Color(150, 50, 250));
		circle.setOutlineThickness(10);
		circle.setOutlineColor(sf::Color(250, 150, 100));
		window.draw(circle);*/

		//создаем круг
		//sf::CircleShape circle1(50);
		//circle1.setPosition(600, 100);
		//circle1.setFillColor(sf::Color(150, 50, 250));
		//circle1.setOutlineThickness(10);
		//circle1.setOutlineColor(sf::Color(250, 150, 100));
		//window.draw(circle1);

		//создаем линию
		//sf::Vertex line[] =
		//{
		//	sf::Vertex(sf::Vector2f(10, 10)),
		//	sf::Vertex(sf::Vector2f(150, 150))
		//};
		//window.draw(line, 2, sf::Lines);

		//создаем прямоугольник
		//sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		//rectangle.setSize(sf::Vector2f(100, 300));
		//rectangle.move(sf::Vector2f(400, 100));
		//rectangle.setFillColor(sf::Color(150, 50, 250));
		//window.draw(rectangle);

		//создаем прямоугольник
		//sf::RectangleShape rectangle1(sf::Vector2f(120, 50));
		//rectangle1.setSize(sf::Vector2f(300, 100));
		//rectangle1.move(sf::Vector2f(300, 450));
		//rectangle1.setFillColor(sf::Color(150, 50, 250));
		//window.draw(rectangle1);

		//отображение экрана
		window.display();
	}
}
//открываем красное окошко с возможностью его закрывать

//sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
//while (window.isOpen())
//{
//    sf::Event event;
//    while (window.pollEvent(event)) {
//        if (event.type == sf::Event::Closed)
//            window.close();
//    }

//    window.clear(sf::Color::Red);
//    window.display();
//}

//return 0;

