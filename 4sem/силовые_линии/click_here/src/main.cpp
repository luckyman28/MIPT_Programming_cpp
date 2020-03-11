#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2_class.h"

#define STEP 1000
#define RADIUS 20

struct direction {
	float x;
	float y;
};


direction E(float x, float y, std::vector<sf::CircleShape> charge_array) 
{
	direction E;
	E.x = 0, E.y = 0;
	for (auto& it : charge_array)
	{
		Vector2 charge_position(it.getPosition().x, it.getPosition().y);
		Vector2 point_position(x, y);
		Vector2 vect((point_position.x - charge_position.x), (point_position.y - charge_position.y)); //������, ����������� �� ��������� ����� � �������
		float distance = vect.len();
		Vector2 normed_vect; 
		normed_vect = vect.norm();
		float E_module = 1 / (distance * distance);
		Vector2 E_from_charge(E_module * normed_vect.x, E_module * normed_vect.y);
		E.x += E_from_charge.x;
		E.y += E_from_charge.y;
	}
	return E;
}


int main()
{
	const float Pi = 3.14159f;

	//������� ����, ����� �������� ������ "������"
	int flag = 0;
	int lines_flag = 1;

	//������� ������, � ������� ����� ������� ������
	std::vector<sf::CircleShape> charge_array;

	//������ ���-�� �������
	int charge_number = 0;

	//������� ����
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");// , sf::Style::Fullscreen);

	while (window.isOpen())
	{
		//���� ����������� ���� �����������
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		//����������� ���� � �����
		window.clear(sf::Color::White);

		////������ ������
		//for (auto& it : charge_array)
		//{
		//	window.draw(it); 
		//}

		Vector2 v(0, -10);

		for (auto& it : charge_array)
		{
			window.draw(it);
			Vector2 charge_position(it.getPosition().x, it.getPosition().y);

			for (int i = 0; i < 8; ++i)
			{
				v.selfrotate((Pi / 4) * i);
				//std::vector<Vector2> line; 
				sf::VertexArray line_vertex(sf::LinesStrip);
				float x_cur = charge_position.x + v.x, y_cur = charge_position.y + v.y;
				line_vertex.append(sf::Vertex(sf::Vector2f(x_cur, y_cur), sf::Color::Red));
				//line.push_back(Vector2(x_cur, y_cur));
				while ((x_cur > 0) && (x_cur < 1920) && (y_cur > 0) && (y_cur < 1080))
				{
					direction delta_E = E(x_cur, y_cur, charge_array);
					x_cur += delta_E.x * STEP;
					y_cur += delta_E.y * STEP;
					line_vertex.append(sf::Vertex(sf::Vector2f(x_cur, y_cur), sf::Color::Red));
					//line.push_back(Vector2(x_cur + delta_E.x * 100000, y_cur + delta_E.y * 100000));
				}
				//������� �����
				//sf::VertexArray line_Vertex(sf::LinesStrip);
				//Vector2toVertex(line, line_Vertex);
				window.draw(line_vertex);
			}

			//if (lines_flag == 0)
			//{
			//	for (int i = 0; i < 16; ++i)
			//	{
			//		v.selfrotate((Pi / 8) * i);
			//		//������� �����
			//		sf::Vertex line[] =
			//		{
			//			sf::Vertex(sf::Vector2f(charge_position.x, charge_position.y), sf::Color::Red),
			//			sf::Vertex(sf::Vector2f(charge_position.x + 3000 * v.x, charge_position.y + 3000 * v.y), sf::Color::Red)
			//		};
			//		window.draw(line, 2, sf::Lines);
			//	}
			//}
		}

		window.display(); // ������� ��� �� �����

		//���� ����� ������, �������� ����� �����, �������� ����������� ������ "������" � ������� �����
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Vector2 mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

			//if (flag == 0) // ���� ��� ������ ������� ����� �� ��� ������� ���-����, �� ������ �� ��� �� ������� �� ���������� �������
			//{
				sf::CircleShape charge(RADIUS);
				charge.setOrigin(RADIUS, RADIUS);
				charge.setPosition(mousePosition.x, mousePosition.y);
				charge.setFillColor(sf::Color::Red);
				charge_array.push_back(charge);
				//charge_array[charge_number] = charge;
				//charge_number++;
				flag = 1; //������ ����
			//}
		}
		else
		{
			flag = 0; //���� ����� ��������, ���� ����������
		}

	}
}


