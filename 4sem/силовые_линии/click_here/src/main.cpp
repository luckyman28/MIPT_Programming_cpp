#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2_class.h"

//������� ����
#define X	1440
#define Y	900

#define STEP 5 // ��� ��� ���������� ������� �����
#define RADIUS 20 //������ ������� - �����
#define CHARGE 100 //������ ������, ����� ���� "����� ������" ��� �������� ����
#define LNUM 32 //���-�� ������� �����, ��������� �� ������

//��������� ������
struct Charge
{
	sf::CircleShape image; //������� ������
	std::vector<sf::VertexArray> lines; //������ �����, ��������� �� ������
	int sign; //���� ������
	sf::Color color;//+ �������, - �����
};

//������� �������� ���� � �����
Vector2 E(float x, float y, std::vector<Charge>& charge_array)
{
	Vector2 E;
	Vector2 point_position(x, y); //���������� �����, � ������� ������� ����
	Vector2 charge_position; 

	//����������� �� ���� ������� � ������� ���� �� �������
	for (auto& it : charge_array)
	{
		charge_position = Vector2(it.image.getPosition().x, it.image.getPosition().y); //���������� ������
		Vector2 vect((point_position.x - charge_position.x), (point_position.y - charge_position.y)); //������, ����������� �� ������ � �����, � ������� ������� ����
		float distance = vect.len(); //����� ����� �������
		E += ((CHARGE / distance) * vect / (distance * distance)) * it.sign; //���������� ���� ��������� ���������� �������, �������� ���� ������
	}
	return E.norm(); //��������� ����
}

int main()
{
	const float Pi = 3.14159f;

	//������� ����, ����� �������� ������ "������"
	int flag = 0;

	//������� ������, � ������� ����� ������� ������
	std::vector<Charge> charge_array;

	//������� ����
	sf::RenderWindow window(sf::VideoMode(X, Y), "My window");// , sf::Style::Fullscreen);

	while (window.isOpen())
	{
		//���� ����������� ���� �����������
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// //����������� ���� � �����
		window.clear(sf::Color::White);

		//������ ����� �� �������
		for (auto& it : charge_array)
		{
			for (auto& line : it.lines)
			{
				window.draw(line);
			}
		}

		//������ ������
		for (auto& it : charge_array)
		{
			window.draw(it.image);
		}

		window.display(); // ������� ��� �� �����

		//���� ������ ����� ��� ������ ������ ����, ������� ������������� ��� ������������� ����� �������������
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			Vector2 mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

			if (flag == 0) // ���� ��� ������ ������� ����� �� ��� ������� �����, �� ������ �� ��� �� ������� �� ���������� �������
			{
				Charge Charge; //��������� ��� ������ ������

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

				//������ ��������� ������� ������
				Charge.image = sf::CircleShape(RADIUS);
				Charge.image.setOrigin(RADIUS, RADIUS);
				Charge.image.setPosition(mousePosition.x, mousePosition.y);
				Charge.image.setFillColor(Charge.color);

				//������� ������� ��� �����, ��������� �� ������� ������
				for (int i = 0; i < LNUM; i++)
				{
					sf::VertexArray vline(sf::LinesStrip, 2*(X+Y));//������� �����
					Charge.lines.push_back(vline); //��������� �� � ������ ����� ������� ������
				}

				charge_array.push_back(Charge); // ��������� ����� � ������ �������

				//��������� �����, ��������� �� ���� �������
				for (auto& it : charge_array)
				{
					Vector2 charge_position(it.image.getPosition().x, it.image.getPosition().y);
					Vector2 v(0, -1);//������ ��� ����������� ��������� ������� �����

					for (int i = 0; i < LNUM; ++i)
					{
						v.selfrotate(2 * Pi / LNUM);

						//������ ��������� ������� i-�� �����
						float x_cur = charge_position.x + v.x, y_cur = charge_position.y + v.y;
						sf::Vertex vertex_(sf::Vector2f(x_cur, y_cur), it.color);
						it.lines[i][0].color = vertex_.color;
						it.lines[i][0].position = vertex_.position;
						it.lines[i][0].texCoords = vertex_.texCoords;

						//������ ��������� ������� �����
						for (int k = 1; k < 2*(X+Y); k++)
						{
							Vector2 delta_E = E(x_cur, y_cur, charge_array); //������� ������ � � ������ �����

							//����������� ���������� ��������� ����� � ������ ����, ��� ������� ����� ������ �������� �� ������������� ������� � ������� � ������������� (��������� �� it.sign)
							x_cur += delta_E.x * STEP * it.sign; 
							y_cur += delta_E.y * STEP * it.sign;

							sf::Vertex vertex(sf::Vector2f(x_cur, y_cur), it.color);
							it.lines[i][k].color = vertex.color;
							it.lines[i][k].position = vertex.position;
							it.lines[i][k].texCoords = vertex.texCoords;
							
						}
					}
				}

				flag = 1; //������ ����
			}
		}
		else
		{
			flag = 0; //���� ����� ��������, ���� ����������
		}

	}
}

