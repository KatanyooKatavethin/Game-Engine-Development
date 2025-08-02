#pragma once
#ifndef PROFILE_HPP
#define PROFILE_HPP

namespace TK
{
	class App
	{
		public:
			App();
			void printMenu();
			float cirCal(float r);
			float triCal(float l, float h);
			float squaCal(float h, float w);
	};
}

#endif