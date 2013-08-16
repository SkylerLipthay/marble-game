#include <skylib/common/color.h>

namespace skylib {

Color::Color() {
  Color(0.0f, 0.0f, 0.0f, 0.0f);
}

Color::Color(float red, float green, float blue, float alpha)
    : components_(red, green, blue, alpha) {
}

float Color::GetRed() const {
  return components_.At(0);
}

float Color::GetGreen() const {
  return components_.At(1);
}

float Color::GetBlue() const {
  return components_.At(2);
}

float Color::GetAlpha() const {
  return components_.At(3);
}

Color Color::Red() {
  return Color(1.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::Orange() {
  return Color(1.0f, 0.5f, 0.0f, 1.0f);
}

Color Color::Yellow() {
  return Color(1.0f, 1.0f, 0.0f, 1.0f);
}

Color Color::Green() {
  return Color(0.0f, 1.0f, 0.0f, 1.0f);
}

Color Color::Teal() {
  return Color(0.0f, 0.5f, 0.5f, 1.0f);
}

Color Color::Blue() {
  return Color(0.70f, 0.79f, 0.92f, 1.0f);
}

Color Color::Purple() {
  return Color(0.5f, 0.0f, 0.5f, 1.0f);
}

Color Color::Black() {
  return Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Color Color::White() {
  return Color(1.0f, 1.0f, 1.0f, 1.0f);
}

Color Color::Gray() {
  return Color(0.75f, 0.75f, 0.75f, 1.0f);
}

Color Color::Clear() {
  return Color(0.0f, 0.0f, 0.0f, 0.0f);
}

} // namespace skylib
