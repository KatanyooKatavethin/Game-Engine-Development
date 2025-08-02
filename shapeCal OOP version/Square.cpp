#include "Square.hpp"
#include <iostream>
#include <cassert>

using namespace std;

namespace TK
{
	Square::Square() :m_height(0.0f), m_width(0.0f){}
	Square::Square(float height, float width) :m_height(height), m_width(height){}

	void Square::setHW(float height, float width)
	{
		//rejection mechanisms
		assert(height >= 0);
		assert(width >= 0);

		this->m_height = height;
		this->m_width = width;

		assert(this->m_height >= 0.0f);
		assert(this->m_width >= 0.0f);
	}

	float Square::getArea() const
	{
		return m_height * m_width;
	}
}