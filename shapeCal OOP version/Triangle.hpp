#pragma once
#include <iostream>
#include "Shape.hpp"

namespace TK
{
	class Triangle : public Shape
	{
	public:
		Triangle();
		Triangle(float height, float bLength);

		void setHBL(float height, float bLength);
		float getArea() const override;
	private:
		float m_height;
		float m_bLength;
	};
}