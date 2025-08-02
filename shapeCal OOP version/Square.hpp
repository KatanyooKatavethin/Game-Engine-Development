#pragma once
#include <iostream>
#include "Shape.hpp"

namespace TK
{
	class Square : public Shape
	{
	public:
		Square();
		Square(float height, float width);
		void setHW(float height, float width);
		float getArea() const override;
	private:
		float m_height;
		float m_width;
	};
}