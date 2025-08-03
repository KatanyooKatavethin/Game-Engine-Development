#pragma once

namespace TK
{
  template<typename T>
  class Vector2
  {
  public:
    T x;
    T y;

    Vector2():x(0.0f), y(0.0f) {}
    Vector2(T x, T y):x(x), y(y) {}

    Vector2(const Vector2& other):x(other.x), y(other.y) {}
    Vector2& operator=(const Vector2& other)
    {
      x = other.x;
      y = other.y;
      return *this;
    }
    Vector2 operator+(const Vector2& other)
    {
      return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator+=(const Vector2& other)
    {
      x += other.x;
      y += other.y;
      return *this;
    }

    static Vector2 ones() {
      return Vector2(1.0f, 1.0f);
    }
    static Vector2 zeros() {
      return Vector2(0.0f, 0.0f);
    }
    static Vector2 up() {
      return Vector2(0.0f, 1.0f);
    }

  };

  typedef Vector2<float> vec2f;
  typedef Vector2<int> vec2i;

}
