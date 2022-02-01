#include "Color.h"

Color::Color() : Color(0, 0, 0, 255)
{

}

Color::Color(int r, int g, int b) : Color(r, g, b, 255)
{

}

Color::Color(int r, int g, int b, int a)
{
	set(r, g, b, a);
}

Color::Color(const Color& other)
{
	data = other.data;
}

Color& Color::operator=(const Color& obj)
{
	data = obj.data;
	return *this;
}

int Color::r()
{
	return extract(data, 3);
}

float Color::rf()
{
	return r() / (float)BYTE_MAX;
}

int Color::g()
{
	return extract(data, 2);
}

float Color::gf()
{
	return g() / (float)BYTE_MAX;
}

int Color::b()
{
	return extract(data, 1);
}

float Color::bf()
{
	return b() / (float)BYTE_MAX;
}

int Color::a()
{
	return extract(data, 0);
}

float Color::af()
{
	return a() / (float)BYTE_MAX;
}

int Color::rawData() const
{
	return data;
}

std::string Color::toString()
{
	return "(" + std::to_string(r()) + ", " + std::to_string(g()) + ", " + std::to_string(b()) + ", " + std::to_string(a()) + ")";
}

void Color::set(int r, int g, int b, int a)
{
	//compact into one integer
	data = compact(a, b, g, r);
}
