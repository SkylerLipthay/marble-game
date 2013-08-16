#ifndef SKYLIB_COMMON_COLOR_H_
#define SKYLIB_COMMON_COLOR_H_

#include <skylib/math/vector.h>

namespace skylib {

class Color {
 public:
  Color();
  Color(float red, float green, float blue, float alpha);

  float GetRed() const;
  float GetGreen() const;
  float GetBlue() const;
  float GetAlpha() const;

  static Color Red();
  static Color Orange();
  static Color Yellow();
  static Color Green();
  static Color Teal();
  static Color Blue();
  static Color Purple();
  static Color Black();
  static Color White();
  static Color Gray();
  static Color Clear();

 private:
  Vector<4> components_;
};

} // namespace skylib

#endif // SKYLIB_COMMON_COLOR_H_
