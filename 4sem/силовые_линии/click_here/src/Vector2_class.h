#pragma once

class Vector2 //������ ������ ����� ����������� ��������� ������ ������� ��������� ������ ���������� ��� ������ (�.�. �� �� ������� ����� ������ ����������)
{
public: //�����, ����� �� ����� ����� ������������ (� ������� ������) � ��� ������, �.�. �� ������� ������������ ������ (������) ��� private
	float x;
	float y;

	//����� ����������� - ��� �������� ������� � 1 �������
	Vector2(float a, float b) {
		x = a;
		y = b;
	}

	//����� "������" �����������, ����� ����� ���� ������ (����� �������� ������������ ����) ������ ������ 'Vector2 v;'
	Vector2() : x(0), y(0) {}

	//��������� ���������� ��������� +
	Vector2 operator+(const Vector2& other) const;

	//��������� ���������� ��������� -
	Vector2 operator-(const Vector2& other) const;

	//��������� ���������� ��������� +=
	Vector2& operator+=(const Vector2& other);

	//��������� ���������� ��������� -=
	Vector2& operator-=(const Vector2& other);

	//��������� ���������� ��������� *
	Vector2 operator*(float k);

	//��������� ���������� ��������� /
	Vector2 operator/(float k);

	//��������� ������� ����� �������
	float len() const;

	//��������� ������� �������� ����� �������
	float squarelen() const;

	//��������� ��������� ������, �������������� �������
	Vector2 norm() const;

	//��������� ������, ���������������� �������
	Vector2 perpendicular() const;

	//���������� ��������� ������������
	float operator*(const Vector2& other) const;

	//���������� ��������� ������������ (������)
	float operator^(const Vector2& other) const;

	//��������� ������� �����
	Vector2 operator-() const;

	//��������� ������� �� ���� ��
	Vector2 rotate(float phi) const;

	//��������� ������� ������ ������� �� ���� ��
	Vector2& selfrotate(float phi);
};

//����������� �������� �����
std::istream& operator>>(std::istream& stream, Vector2& v) {
	stream >> v.x >> v.y;
	return stream;
}

//����������� �������� ������
std::ostream& operator<<(std::ostream& stream, const Vector2& v) {
	stream << v.x << " " << v.y;
	return stream;
}

//���������� ���������� ��������� +
Vector2 Vector2::operator+(const Vector2& other) const { // ����� "Vector2::", ����� ����� ������, ��� �� ���������� ����� ������
	Vector2 sum;
	sum.x = x + other.x;
	sum.y = y + other.y;
	return sum;
}

//���������� ���������� ��������� -
Vector2 Vector2::operator-(const Vector2& other) const { // ����� "Vector2::", ����� ����� ������, ��� �� ���������� ����� ������
	Vector2 sum;
	sum.x = x - other.x;
	sum.y = y - other.y;
	return sum;
}

//���������� ���������� ��������� +=
Vector2& Vector2::operator+=(const Vector2& other) { // ����� "Vector2::", ����� ����� ������, ��� �� ���������� ����� ������
														   // ����� &(������) ����� Vector2, ����� �������� ��� �������� - ������ ��������� � ��
	x += other.x;
	y += other.y;
	return *this; //����� * ����� this(�������� �������), ����� ������������ �� � �������� ��� ������
}

//���������� ���������� ��������� -=
Vector2& Vector2::operator-=(const Vector2& other) { // ����� "Vector2::", ����� ����� ������, ��� �� ���������� ����� ������
														   // ����� &(������) ����� Vector2, ����� �������� ��� �������� - ������ ��������� � ��
	x -= other.x;
	y -= other.y;
	return *this; //����� * ����� this(�������� �������), ����� ������������ �� � �������� ��� ������
}

//���������� ���������� ��������� * �� ������ (������ �������� ��� �� ������)
Vector2 Vector2::operator*(float k) {
	return Vector2(k * x, k * y);
}

//����������� �������� * �� ����� (������ �������� - �����)
Vector2 operator*(float k, const Vector2& v) { //�������� ��, ����� ������ & ����� Vector2? ��� ���� ����� � ������� �������� �� ������������ � ������������ ����� ��� ��� ���� -  ��� ����� �������� �������
	return Vector2(k * v.x, k * v.y);
}

//���������� ���������� ��������� / �� ������ 
Vector2 Vector2::operator/(float k) {
	return Vector2(x / k, y / k);
}

//���������� ����� �������
float Vector2::len() const {
	return sqrt(x * x + y * y);
}

//���������� ������� ����� �������
float Vector2::squarelen() const {
	return x * x + y * y;
}

//���������� ��������� ������, �������������� �������
Vector2 Vector2::norm() const {
	float length = this->len(); //����� � ���� ���������(������) � ���� �� ����� � ��������� - �������� � �����������
	return { x / length, y / length }; //�� ��� ������������� ����������� ����� � �������� �������
}

//���������� ������, ���������������� �������
Vector2 Vector2::perpendicular() const {
	return { -y, x }; //�� ��� ������������� ����������� ����� � �������� �������
}

//���������� ��������� ������������
float Vector2::operator*(const Vector2& other) const { // ������ const ��������� � ������ ������� (�������)
	return x * other.x + y * other.y;
}

//���������� ��������� ������������ (������)
float Vector2::operator^(const Vector2& other) const { // ������ const ��������� � ������ ������� (�������)
	return x * other.y - y * other.x;
}

//���������� ������� �����
Vector2 Vector2::operator-() const {
	return { -x, -y };
}

//���������� ������� �� ���� ��
Vector2 Vector2::rotate(float phi) const {
	return { x * cos(phi) - y * sin(phi) , y * cos(phi) + x * sin(phi) };
}

//���������� ������� ������ ������� �� ���� ��
Vector2& Vector2::selfrotate(float phi) {
	float a = x;
	float b = y;
	x = a * cos(phi) - b * sin(phi);
	y = b * cos(phi) + a * sin(phi);
	return *this;
}