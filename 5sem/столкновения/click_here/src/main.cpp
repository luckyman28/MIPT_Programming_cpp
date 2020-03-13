#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2_class.h"

//создаем структуру, в которую передаем текстуру и координаты - направление движения текстуры
struct moving_texture {
	sf::Sprite ball;
	float x;
	float y;
};

//функция отцентровки камеры по герою
Vector2 FindViewCenter(const sf::Sprite& hero, const sf::Sprite& background, sf::View& gameView)
{
	Vector2 center = Vector2(hero.getPosition().x, hero.getPosition().y) + Vector2(hero.getLocalBounds().width / 2, hero.getLocalBounds().height / 2);
	center.x = std::max(center.x, gameView.getSize().x / 2);
	center.y = std::max(center.y, gameView.getSize().y / 2);

	center.x = std::min(center.x, background.getTexture()->getSize().x - gameView.getSize().x / 2);
	center.y = std::min(center.y, background.getTexture()->getSize().y - gameView.getSize().y / 2);

	return center;
}

//функция движения текстуры - ссылка для того чтобы изменить объект т.к. он двигается
void move(sf::Sprite& circle, float x, float y) {
	circle.move(x, 0);
	circle.move(0, y);
}

int main()
{
	//создаем флаг, чтобы избежать эффект "лазера"
	int flag = 0;

	int k = 0;

	//создаем окно
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");// , sf::Style::Fullscreen);

	//создаем задний фон
	sf::Texture mapTexture;
	if (!mapTexture.loadFromFile("molumen-world-map.png"))
	{
		std::cout << "Can't load texture\n";
	}
	mapTexture.setSmooth(true);
	sf::Sprite background;
	background.setTexture(mapTexture);


	//делаем возможным приближение/удаление
	sf::View gameView(sf::FloatRect(0.0f, 0.0f, mapTexture.getSize().x, mapTexture.getSize().y));
	window.setView(gameView);
	sf::View initialView = gameView;
	float scale = 1.0f;

	//создаем массив структур (которые мы ввели) под "летающие" текстуры (мячи-пули)
	std::vector<moving_texture> balls_array(1000);

	//создаем маячок для пробегания по этому массиву и его заполнения
	int ball_number = 0;

	//sf::CircleShape circle(50);

	//создаем "героя" - двигающуюся иконку
	sf::Texture texture;
	texture.loadFromFile("Chelsea.png"); //файл с рисунком должен лежать в папке bin !!!
	sf::Sprite hero(texture); //называем нашу текстуру circle
	hero.setScale(0.5f, 0.5f); //уменьшаем размер текстуры вдвое
	hero.setPosition(200, 200);

	float velocity = 2; //задаем скорость движения героя

	//объявляем текстуру для мячей-пуль
	sf::Texture texture_;
	texture_.loadFromFile("ball.png");

	while (window.isOpen())
	{

		//даем возможность окну закрываться
		sf::Event event;
		while (window.pollEvent(event)) 
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		//закрашиваем окно в белый
		window.clear(sf::Color::White);

		//отрисовываем задний фон
		window.draw(background);

		//проходим по массиву мячей-пуль, рисуем их и двигаем в том направлении, в котором они должны двигаться
		for (auto& it : balls_array)
		{
			window.draw(it.ball); //рисуем
			move(it.ball , 2 * it.x, 2 * it.y); //двигаем
		}

		window.draw(hero); //рисуем нашего "героя"
		window.display(); // выводим все на экран

		//код для реализации приближения/удаления
		gameView = initialView;
		gameView.zoom(scale);
		window.setView(gameView);

		//
		Vector2 center1 = FindViewCenter(hero, background, gameView);
		gameView.setCenter(sf::Vector2f(center1.x, center1.y));

		if (k == 0)
		{
			window.setView(gameView);
			k = 1;
		}
		//window.setView(gameView);

		sf::Vector2u circleSize = hero.getTexture()->getSize(); //создаем вектор, характеризующий размер нашего "героя"
		hero.setOrigin(circleSize.x / 2, circleSize.y / 2);

		//реализуем движение героя с учетом того что он не должен вылетать за границы окна 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (hero.getPosition().x - (circleSize.x / 2)*0.5 - velocity < 0) // circle.getPosition().x возвращает координату центра -> дальше надо отнять радиус, чтобы граница не заходила за край
			{                                                                 //домножаем на 0.5, т.к. мы писали hero.setScale(0.5f, 0.5f)
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

		//удаление
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && scale < 1.0f)
		{
			scale *= 1.03f;
		}
		//приближение
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			scale /= 1.03f;
		}

		//код, необходимый для того, чтобы герой ориентировался на мышку
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2f center = hero.getPosition();
		sf::Vector2f d = sf::Vector2f(mousePosition.x, mousePosition.y) - center; //вектор, напрвленный от положения героя к курсору
		const float Pi = 3.14159f;
		hero.setRotation(-(90 + atan2f(d.x, d.y) * 180 / Pi));


		Vector2 direction(d.x, d.y), normed_direction; // перегоняем вектор d в "наш" Vector2
		normed_direction = direction.norm(); //нормируем полученный вектор

		//если мышка нажата, стреляем новым шаром, отдельно обрабатывая случай "лазера" с помощью флага
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (flag == 0) // если при данном нажатии мышки мы уже создали мяч-пулю, то больше мы его не создаем до следующего нажатия
			{
				balls_array[ball_number].ball.setTexture(texture_); //добавляем в массив мяч-пулю
				balls_array[ball_number].ball.setScale(2.0f, 2.0f); //увеличиваем его изображение
				balls_array[ball_number].x = normed_direction.x; //задаем ему x-компоненту движения
				balls_array[ball_number].y = normed_direction.y; //задаем ему y-компоненту движения
				balls_array[ball_number++].ball.setPosition(hero.getPosition().x, hero.getPosition().y);//задаем начальное положение мяча-пули
				flag = 1; //ставим флаг
			}
		}
		else
		{
			flag = 0; //если мыщка отпущена, флаг обнуляется
		}
	}
}


