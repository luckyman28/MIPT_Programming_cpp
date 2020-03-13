#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2_class.h"
#include <cmath>

//������� ���������, � ������� �������� �������� � ���������� - ����������� �������� ��������
struct moving_texture {
	sf::Sprite ball;
	float x;
	float y;
};

//������� �������� �������� - ������ ��� ���� ����� �������� ������ �.�. �� ���������
void move(sf::Sprite& circle, float x, float y) {
	circle.move(x, 0);
	circle.move(0, y);
}

int main()
{
	//������� ����, ����� �������� ������ "������"
	int flag = 0;

	//������� ����
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");// , sf::Style::Fullscreen);

	//std::vector<sf::CircleShape> circles(1000);

	//������� ������ �������� (������� �� �����) ��� "��������" �������� (����-����)
	std::vector<moving_texture> balls_array(1000);

	//������� ������ ��� ���������� �� ����� ������� � ��� ����������
	int ball_number = 0;

	//sf::CircleShape circle(50);

	//������� "�����" - ����������� ������
	sf::Texture texture;
	texture.loadFromFile("Chelsea.png"); //���� � �������� ������ ������ � ����� bin !!!
	sf::Sprite hero(texture); //�������� ���� �������� circle
	hero.setScale(0.5f, 0.5f); //��������� ������ �������� �����
	hero.setPosition(200, 200);

	float velocity = 2; //������ �������� �������� �����

	//��������� �������� ��� �����-����
	sf::Texture texture_;
	texture_.loadFromFile("ball.png");

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

		sf::Vector2u circleSize = hero.getTexture()->getSize(); //������� ������, ��������������� ������ ������ "�����"
		hero.setOrigin(circleSize.x / 2, circleSize.y / 2);

		//���, ����������� ��� ����, ����� ����� �������������� �� �����
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = hero.getPosition();
		sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center; //������, ����������� �� ��������� ����� � �������
		const float Pi = 3.14159f;
		hero.setRotation(-(90 + atan2f(d.x, d.y) * 180 / Pi));


		Vector2 direction(d.x, d.y), normed_direction; // ���������� ������ d � "���" Vector2
		normed_direction = direction.norm(); //��������� ���������� ������

		//��� ������� �� ������ ������ ���� �������� �������
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			//������� �������������
			sf::RectangleShape rectangle;// ������� ������������� - ��� ������
			rectangle.setSize(sf::Vector2f(10, 3000)); //������ ��� �������
			float angle = atan(normed_direction.x / normed_direction.y); //������ ���� �������� ����� ����������� ����� ����������� ������� �����
			if (normed_direction.y < 0)
				rectangle.setRotation(180 - (angle * 180 / Pi)); //����� ������ ������� � ���� ������� �������� �����������
			if (normed_direction.y >= 0)
				rectangle.setRotation(-(angle * 180 / Pi));
			rectangle.move(sf::Vector2f(hero.getPosition().x , hero.getPosition().y)); //������ ��������� ���������� �������������� - ��� ��������� � ����������� �����-������
			rectangle.setFillColor(sf::Color::Red);
			window.draw(rectangle);

		}

		//�������� �� ������� �����-����, ������ �� � ������� � ��� �����������, � ������� ��� ������ ���������
		for (auto& it : balls_array)
		{
			window.draw(it.ball); //������
			move(it.ball , 2 * it.x, 2 * it.y); //�������
		}

		window.draw(hero); //������ ������ "�����"
		window.display(); // ������� ��� �� �����

		//��������� �������� ����� � ������ ���� ��� �� �� ������ �������� �� ������� ���� 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (hero.getPosition().x - (circleSize.x / 2)*0.5 - velocity < 0) // circle.getPosition().x ���������� ���������� ������ -> ������ ���� ������ ������, ����� ������� �� �������� �� ����
			{                                                                 //��������� �� 0.5, �.�. �� ������ hero.setScale(0.5f, 0.5f)
				hero.move(-(hero.getPosition().x - (circleSize.x / 2)*0.5), 0);
			}
			else
			{
				hero.move(-velocity, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (hero.getPosition().x + (circleSize.x / 2) * 0.5 + velocity > 1920)
			{
				hero.move((hero.getPosition().x + (circleSize.x / 2) * 0.5 - 1920), 0);
			}
			else
			{
				hero.move(velocity, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (hero.getPosition().y - (circleSize.y / 2) * 0.5 - velocity < 0)
			{
				hero.move(-(hero.getPosition().y - (circleSize.y / 2) * 0.5), 0);
			}
			else
			{
				hero.move(0, -velocity);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (hero.getPosition().y + (circleSize.y / 2) * 0.5 + velocity > 1080)
			{
				hero.move((hero.getPosition().y + (circleSize.y / 2) * 0.5 - 1080), 0);
			}
			else
			{
				hero.move(0, velocity);
			}
		}


		//���� ����� ������, �������� ����� �����, �������� ����������� ������ "������" � ������� �����
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (flag == 0) // ���� ��� ������ ������� ����� �� ��� ������� ���-����, �� ������ �� ��� �� ������� �� ���������� �������
			{
				balls_array[ball_number].ball.setTexture(texture_); //��������� � ������ ���-����
				balls_array[ball_number].ball.setScale(2.0f, 2.0f); //����������� ��� �����������
				balls_array[ball_number].x = normed_direction.x; //������ ��� x-���������� ��������
				balls_array[ball_number].y = normed_direction.y; //������ ��� y-���������� ��������
				balls_array[ball_number++].ball.setPosition(hero.getPosition().x, hero.getPosition().y);//������ ��������� ��������� ����-����
				flag = 1; //������ ����
			}
		}
		else
		{
			flag = 0; //���� ����� ��������, ���� ����������
		}
	}
}

