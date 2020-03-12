#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2_class.h"

#define X	1440
#define Y	900

#define STEP 5
#define RADIUS 20
#define CHARGE 100 //аналог заряда, чтобы было "легче делить" при подсчете поля
#define LNUM	8

struct Charge
{
	sf::CircleShape image;
	std::vector<sf::VertexArray> lines;
};

//функция подсчета поля в точке
Vector2 E(float x, float y, std::vector<Charge>& charge_array)
{
	Vector2 E;
	Vector2 point_position(x, y); //координаты точки, в которой считаем поле
	Vector2 charge_position; 
	//пробегаемся во всем зарядам и считаем поле от каждого
	for (auto& it : charge_array)
	{
		charge_position = Vector2(it.image.getPosition().x, it.image.getPosition().y); //координаты заряда
		Vector2 vect((point_position.x - charge_position.x), (point_position.y - charge_position.y)); //вектор, напрвленный от заряда к точке, в которой считаем поле
		float distance = vect.len(); //длина этого вектора
		E += (CHARGE / distance) * vect / (distance * distance); //прибавляем поле созданное конкретным зарядом
	}
	return E.norm(); //нормируем поле
}

bool CheckPointInside(std::vector<Charge>& charges, sf::CircleShape& charge, float x, float y)
{
	sf::Vector2f n = charge.getPosition();
	for (auto& c : charges)
	{
		sf::Vector2f f = c.image.getPosition();
		if ((f.x == n.x) && (f.y == n.y))
			continue;

		sf::Vector2f v = f - sf::Vector2f(x, y);
		if ((v.x * v.x + v.y * v.y) <= RADIUS * RADIUS)
			return true;
	}

	return false;
}


int main()
{
	const float Pi = 3.14159f;

	//создаем флаг, чтобы избежать эффект "лазера"
	int flag = 0;

	//создаем массив, в котором будем хранить заряды
	std::vector<Charge> charge_array;

	//создаем окно
	sf::RenderWindow window(sf::VideoMode(X, Y), "My window");// , sf::Style::Fullscreen);

	while (window.isOpen())
	{
		//даем возможность окну закрываться
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// //закрашиваем окно в белый
		window.clear(sf::Color::White);

		//рисуем заряды и линии от каждого из них
		for (auto& it : charge_array)
		{
			window.draw(it.image);
			for (auto& line : it.lines)
			{
				window.draw(line);
			}
		}

		window.display(); // выводим все на экран

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Vector2 mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

			if (flag == 0) // если при данном нажатии мышки мы уже создали заряд, то больше мы его не создаем до следующего нажатия
			{
				Charge Charge; //структура для нового заряда

				//задаем параметры рисунка заряда
				Charge.image = sf::CircleShape(RADIUS);
				Charge.image.setOrigin(RADIUS, RADIUS);
				Charge.image.setPosition(mousePosition.x, mousePosition.y);
				Charge.image.setFillColor(sf::Color::Red);

				//создаем массивы под линии, исходящие из данного заряда
				for (int i = 0; i < LNUM; i++)
				{
					sf::VertexArray vline(sf::LinesStrip, 2*(X+Y));//создаем линии
					Charge.lines.push_back(vline); //добавляем ее в массив линий данного заряда
				}

				charge_array.push_back(Charge); // добавляем заряд в массив зарядов

				//обновляем линии, исходящие из всех зарядов
				for (auto& it : charge_array)
				{
					Vector2 charge_position(it.image.getPosition().x, it.image.getPosition().y);
					Vector2 v(0, -1);//вектор для определения начальной силовой линии

					for (int i = 0; i < LNUM; ++i)
					{
						//it.lines[i].clear();
						v.selfrotate(2 * Pi / LNUM);

						float x_cur = charge_position.x + v.x, y_cur = charge_position.y + v.y;
						//it.lines[i].append(sf::Vertex(sf::Vector2f(x_cur, y_cur), sf::Color::Red));
						sf::Vertex vertex_(sf::Vector2f(x_cur, y_cur), sf::Color::Red);
						it.lines[i][0].color = vertex_.color;
						it.lines[i][0].position = vertex_.position;
						it.lines[i][0].texCoords = vertex_.texCoords;

						for (int k = 1; k < 2*(X+Y); k++)
						{
							Vector2 delta_E = E(x_cur, y_cur, charge_array);
							x_cur += delta_E.x * STEP;
							y_cur += delta_E.y * STEP;
							sf::Vertex vertex(sf::Vector2f(x_cur, y_cur), sf::Color::Red);
							it.lines[i][k].color = vertex.color;
							it.lines[i][k].position = vertex.position;
							it.lines[i][k].texCoords = vertex.texCoords;
							
							//if (CheckPointInside(charge_array, it.image, x_cur, y_cur))
							//	break;
						}
						//int j = 1;
						//while ((x_cur > 0) && (x_cur < X) && (y_cur > 0) && (y_cur < Y))
						//{
						//	Vector2 delta_E = E(x_cur, y_cur, charge_array);
						//	x_cur += delta_E.x * STEP;
						//	y_cur += delta_E.y * STEP;
						//	sf::Vertex vertex(sf::Vector2f(x_cur, y_cur), sf::Color::Red);

						//	try
						//	{
						//		//it.lines[i].append(vertex);
						//		it.lines[i][j] = vertex;
						//		j++;
						//	}
						//	catch (std::bad_alloc)
						//	{
						//		std::cout << "Bad alloc" << std::endl;
						//		break;
						//	}
						//}
					}
				}

				flag = 1; //ставим флаг
			}
		}
		else
		{
			flag = 0; //если мыщка отпущена, флаг обнуляется
		}

	}
}

