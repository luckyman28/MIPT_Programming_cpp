#pragma once

class Vector2 //внутри класса можем перегружать операторы только которые принимают первым аргументом сам вектор (т.к. он по дефолту будет первым аргументом)
{
public: //пишем, чтобы мы потом могли пользоваться (в методах класса) и вне класса, т.к. по дефолту спецификатор класса (любого) это private
	float x;
	float y;

	//пишем конструктор - для создания вектора в 1 строчку
	Vector2(float a, float b) {
		x = a;
		y = b;
	}

	//пишем "пустой" конструктор, чтобы можно было теперь (после создания конструктора выше) писать просто 'Vector2 v;'
	Vector2() : x(0), y(0) {}

	//объявляем перегрузку оператора +
	Vector2 operator+(const Vector2& other) const;

	//объявляем перегрузку оператора -
	Vector2 operator-(const Vector2& other) const;

	//объявляем перегрузку оператора +=
	Vector2& operator+=(const Vector2& other);

	//объявляем перегрузку оператора -=
	Vector2& operator-=(const Vector2& other);

	//объявляем перегрузку оператора *
	Vector2 operator*(float k);

	//объявляем перегрузку оператора /
	Vector2 operator/(float k);

	//объявляем функцию длины вектора
	float len() const;

	//объявляем функцию квадрата длины вектора
	float squarelen() const;

	//объявляем единичный вектор, сонаправленный данному
	Vector2 norm() const;

	//объявляем вектор, перпендикулярный данному
	Vector2 perpendicular() const;

	//определяем скалярное произведение
	float operator*(const Vector2& other) const;

	//определяем векторное произведение (модуль)
	float operator^(const Vector2& other) const;

	//объявляем унарный минус
	Vector2 operator-() const;

	//объявляем поворот на угол фи
	Vector2 rotate(float phi) const;

	//объявляем поворот самого вектора на угол фи
	Vector2& selfrotate(float phi);
};

//перегружаем оператор ввода
std::istream& operator>>(std::istream& stream, Vector2& v) {
	stream >> v.x >> v.y;
	return stream;
}

//перегружаем оператор вывода
std::ostream& operator<<(std::ostream& stream, const Vector2& v) {
	stream << v.x << " " << v.y;
	return stream;
}

//определяем перегрузку оператора +
Vector2 Vector2::operator+(const Vector2& other) const { // пишем "Vector2::", чтобы прога поняла, что мы определяем метод класса
	Vector2 sum;
	sum.x = x + other.x;
	sum.y = y + other.y;
	return sum;
}

//определяем перегрузку оператора -
Vector2 Vector2::operator-(const Vector2& other) const { // пишем "Vector2::", чтобы прога поняла, что мы определяем метод класса
	Vector2 sum;
	sum.x = x - other.x;
	sum.y = y - other.y;
	return sum;
}

//определяем перегрузку оператора +=
Vector2& Vector2::operator+=(const Vector2& other) { // пишем "Vector2::", чтобы прога поняла, что мы определяем метод класса
														   // пишем &(ссылка) после Vector2, чтобы изменить его значение - аналог указателя в си
	x += other.x;
	y += other.y;
	return *this; //пишем * перед this(является ссылкой), чтобы разыменовать ее и получить сам объект
}

//определяем перегрузку оператора -=
Vector2& Vector2::operator-=(const Vector2& other) { // пишем "Vector2::", чтобы прога поняла, что мы определяем метод класса
														   // пишем &(ссылка) после Vector2, чтобы изменить его значение - аналог указателя в си
	x -= other.x;
	y -= other.y;
	return *this; //пишем * перед this(является ссылкой), чтобы разыменовать ее и получить сам объект
}

//определяем перегрузку оператора * на скаляр (первый аргумент как бы вектор)
Vector2 Vector2::operator*(float k) {
	return Vector2(k * x, k * y);
}

//перегружаем оператор * на число (первый аргумент - число)
Vector2 operator*(float k, const Vector2& v) { //казалось бы, зачем писать & после Vector2? Это надо чтобы в функции значение не копировалось а передавалось сразу как оно есть -  так прога работает быстрее
	return Vector2(k * v.x, k * v.y);
}

//определяем перегрузку оператора / на скаляр 
Vector2 Vector2::operator/(float k) {
	return Vector2(x / k, y / k);
}

//определяем длину вектора
float Vector2::len() const {
	return sqrt(x * x + y * y);
}

//определяем квадрат длины вектора
float Vector2::squarelen() const {
	return x * x + y * y;
}

//определяем единичный вектор, сонаправленный данному
Vector2 Vector2::norm() const {
	float length = this->len(); //когда у меня указатель(ссылку) я пишу не точку а стрелочку - аналогия с указателями
	return { x / length, y / length }; //не при инициализации конструктор пишем в фигурных скобках
}

//определяем вектор, перпендикулярный данному
Vector2 Vector2::perpendicular() const {
	return { -y, x }; //не при инициализации конструктор пишем в фигурных скобках
}

//определяем скалярное произведение
float Vector2::operator*(const Vector2& other) const { // второй const относится к самому вектору (первому)
	return x * other.x + y * other.y;
}

//определяем векторное произведение (модуль)
float Vector2::operator^(const Vector2& other) const { // второй const относится к самому вектору (первому)
	return x * other.y - y * other.x;
}

//определяем унарный минус
Vector2 Vector2::operator-() const {
	return { -x, -y };
}

//определяем поворот на угол фи
Vector2 Vector2::rotate(float phi) const {
	return { x * cos(phi) - y * sin(phi) , y * cos(phi) + x * sin(phi) };
}

//определяем поворот самого вектора на угол фи
Vector2& Vector2::selfrotate(float phi) {
	float a = x;
	float b = y;
	x = a * cos(phi) - b * sin(phi);
	y = b * cos(phi) + a * sin(phi);
	return *this;
}