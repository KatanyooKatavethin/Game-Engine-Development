#include "Circle.hpp"
#include <iostream>
#include <cassert>

using namespace std;

namespace TK 
{
	Circle::Circle():m_radius(0.0f) { }
	Circle::Circle(float radius) :m_radius(radius) {}

	void Circle::setRadius(float radius)
	{
		//rejection mechanism
		assert(radius >= 0);

		this-> m_radius = radius;

		assert(this->m_radius >= 0.0f);
	}

	float Circle::getArea() const
	{
		return PI * m_radius * m_radius;
	}
}