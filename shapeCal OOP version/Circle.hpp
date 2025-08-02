#pragma once
#include <iostream>
#include "Shape.hpp"

namespace TK 
{
	const float PI = 3.141f;

	class Circle : public Shape
	{
	public:
		Circle();
		Circle(float radius);
		void setRadius(float radius);
		float getArea() const override;
	private:
		float m_radius;
	};
}