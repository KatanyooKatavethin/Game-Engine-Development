#include "Triangle.hpp"
#include <iostream>
#include <cassert>

using namespace std;

namespace TK
{
	Triangle::Triangle() :m_height(0.0f), m_bLength(0.0f) {}
	Triangle::Triangle(float height, float bLength) :m_height(height), m_bLength(bLength) {}

	void Triangle::setHBL(float height, float bLength)
	{
		//rejection mechanisms
		assert(height >= 0);
		assert(bLength >= 0);

		this->m_height = height;
		this->m_bLength = bLength;

		assert(this->m_height >= 0.0f);
		assert(this->m_bLength >= 0.0f);
	}

	float Triangle::getArea() const
	{
		return 0.5f * (m_height * m_bLength);
	}
}