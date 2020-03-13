#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2_class.h"

//размеры окна
#define X	1440
#define Y	900

#define STEP 5 // шаг при построении силовых линий
#define RADIUS 20 //радиус зарядов - шаров
#define CHARGE 100 //аналог заряда, чтобы было "легче делить" при подсчете поля
#define LNUM 32 //кол-во силовых линий, исходящих из заряда

//структура заряда
struct Charge
{
	sf::CircleShape image; //рисунок заряда
	std::vector<sf::VertexArray> lines; //массив линий, исходящих из заряда
	int sign; //знак заряда
	sf::Color color;//+ красный, - синий
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
		E += ((CHARGE / distance) * vect / (distance * distance)) * it.sign; //прибавляем поле созданное конкретным зарядом, учитывая знак заряда
	}
	return E.norm(); //нормируем поле
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

		//рисуем линии от зарядов
		for (auto& it : charge_array)
		{
			for (auto& line : it.lines)
			{
				window.draw(line);
			}
		}

		//рисуем заряды
		for (auto& it : charge_array)
		{
			window.draw(it.image);
		}

		window.display(); // выводим все на экран

		//если нажата левая или правая кнопка мыши, создаем положительныф или отрицательный заряд соотвественно
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			Vector2 mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

			if (flag == 0) // если при данном нажатии мышки мы уже создали заряд, то больше мы его не создаем до следующего нажатия
			{
				Charge Charge; //структура для нового заряда

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					Charge.sign = 1;
					Charge.color = sf::Color::Red;
				}

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					Charge.sign = -1;
					Charge.color = sf::Color::Blue;
				}

				//задаем параметры рисунка заряда
				Charge.image = sf::CircleShape(RADIUS);
				Charge.image.setOrigin(RADIUS, RADIUS);
				Charge.image.setPosition(mousePosition.x, mousePosition.y);
				Charge.image.setFillColor(Charge.color);

				//создаем массивы под линии, исходящие из данного заряда
				for (int i = 0; i < LNUM; i++)
				{
					sf::VertexArray vline(sf::LinesStrip, 2*(X+Y));//создаем линию
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
						v.selfrotate(2 * Pi / LNUM);

						//задаем начальную вершину i-ой линии
						float x_cur = charge_position.x + v.x, y_cur = charge_position.y + v.y;
						sf::Vertex vertex_(sf::Vector2f(x_cur, y_cur), it.color);
						it.lines[i][0].color = vertex_.color;
						it.lines[i][0].position = vertex_.position;
						it.lines[i][0].texCoords = vertex_.texCoords;

						//строим остальные вершины линии
						for (int k = 1; k < 2*(X+Y); k++)
						{
							Vector2 delta_E = E(x_cur, y_cur, charge_array); //считаем вектор Е в данной точке

							//расчитываем координаты следующей точки с учетом того, что силовые линии должны выходить из положительных зарядов и входить в отрицательные (домножаем на it.sign)
							x_cur += delta_E.x * STEP * it.sign; 
							y_cur += delta_E.y * STEP * it.sign;

							sf::Vertex vertex(sf::Vector2f(x_cur, y_cur), it.color);
							it.lines[i][k].color = vertex.color;
							it.lines[i][k].position = vertex.position;
							it.lines[i][k].texCoords = vertex.texCoords;
							
						}
					}
				}

				flag = 1; //ставим флаг
			}
		}
		else
		{
			flag = 0; //если мышка отпущена, флаг обнуляется
		}

	}
}

