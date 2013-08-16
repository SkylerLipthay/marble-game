#include <skylib/math/vector.h>
#include <cmath>

namespace skylib {

template <unsigned int size>
Vector<size>::Vector() {
}

template <>
Vector<2>::Vector(float a, float b) {
  scalars_[0] = a;
  scalars_[1] = b;
}

template <>
Vector<3>::Vector(float a, float b, float c) {
  scalars_[0] = a;
  scalars_[1] = b;
  scalars_[2] = c;
}

template <>
Vector<4>::Vector(float a, float b, float c, float d) {
  scalars_[0] = a;
  scalars_[1] = b;
  scalars_[2] = c;
  scalars_[3] = d;
}

template <unsigned int size>
float& Vector<size>::At(unsigned int index) {
  if (index >= size) {
    return scalars_[0];
  }

  return scalars_[index];
}

template <unsigned int size>
float const& Vector<size>::At(unsigned int index) const {
  if (index >= size) {
    return scalars_[0];
  }

  return scalars_[index];
}

template <unsigned int size>
const float *Vector<size>::Data() const {
  return reinterpret_cast<const float *>(scalars_);
}

template <unsigned int size>
float Vector<size>::Length() {
  float squared_length = 0.0f;

  for (unsigned int index = 0; index < size; index++) {
    squared_length += (scalars_[index] * scalars_[index]);
  }

  return std::sqrt(squared_length);
}

template <unsigned int size>
void Vector<size>::Normalize() {
  float length = Length();

  for (unsigned int index = 0; index < size; index++) {
    scalars_[index] /= length;
  }
}

template <unsigned int size>
Vector<size> const& Vector<size>::Add(Vector<size> const& other) {
  for (unsigned int index = 0; index < size; index++) {
    scalars_[index] += other.At(index);
  }

  return *this;
}

template <unsigned int size>
Vector<size> const& Vector<size>::Subtract(Vector<size> const& other) {
  for (unsigned int index = 0; index < size; index++) {
    scalars_[index] -= other.At(index);
  }

  return *this;
}

template <unsigned int size>
Vector<size> const& Vector<size>::Multiply(float const& multiplier) {
  for (unsigned int index = 0; index < size; index++) {
    scalars_[index] *= multiplier;
  }

  return *this;
}

template <unsigned int size>
Vector<size> const& Vector<size>::Divide(float const& divisor) {
  for (unsigned int index = 0; index < size; index++) {
    scalars_[index] /= divisor;
  }

  return *this;
}

template <unsigned int size>
Vector<size> Vector<size>::Plus(Vector<size> const& other) const {
  Vector<size> result = *this;

  for (unsigned int index = 0; index < size; index++) {
    result.At(index) += other.At(index);
  }

  return result;
}

template <unsigned int size>
Vector<size> Vector<size>::Minus(Vector<size> const& other) const {
  Vector<size> result = *this;

  for (unsigned int index = 0; index < size; index++) {
    result.At(index) -= other.At(index);
  }

  return result;
}

template <unsigned int size>
Vector<size> Vector<size>::MultipliedBy(float const& multiplier) const {
  Vector<size> result = *this;

  for (unsigned int index = 0; index < size; index++) {
    result.At(index) *= multiplier;
  }

  return result;
}

template <unsigned int size>
Vector<size> Vector<size>::DividedBy(float const& divisor) const {
  Vector<size> result = *this;

  for (unsigned int index = 0; index < size; index++) {
    result.At(index) /= divisor;
  }

  return result;
}

template <unsigned int size>
float Vector<size>::DotProduct(Vector<size> const& other) const {
  float dot_product = 0.0f;

  for (unsigned int index = 0; index < size; index++) {
    dot_product += scalars_[index] * other.At(index);
  }

  return dot_product;
}

template <unsigned int size>
Vector<size> const& Vector<size>::operator += (Vector<size> const& other) {
  return Add(other);
}

template <unsigned int size>
Vector<size> const& Vector<size>::operator -= (Vector<size> const& other) {
  return Subtract(other);
}

template <unsigned int size>
Vector<size> const& Vector<size>::operator *= (float const& multiplier) {
  return Multiply(multiplier);
}

template <unsigned int size>
Vector<size> const& Vector<size>::operator /= (float const& divisor) {
  return Divide(divisor);
}

template <unsigned int size>
Vector<size> Vector<size>::operator + (Vector<size> const& other) const {
  return Plus(other);
}

template <unsigned int size>
Vector<size> Vector<size>::operator - (Vector<size> const& other) const {
  return Minus(other);
}

template <unsigned int size>
Vector<size> Vector<size>::operator * (float const& multiplier) const {
  return MultipliedBy(multiplier);
}

template <unsigned int size>
Vector<size> Vector<size>::operator / (float const& divisor) const {
  return DividedBy(divisor);
}

template <unsigned int size>
Vector<size> Vector<size>::Zero() {
  Vector<size> result;

  for (unsigned int index = 0; index < size; index++) {
    result.At(index) = 0.0f;
  }

  return result;
}

template <unsigned int size>
Vector<size> Vector<size>::One() {
  Vector<size> result;

  for (unsigned int index = 0; index < size; index++) {
    result.At(index) = 1.0f;
  }

  return result;
}

template <unsigned int size>
Vector<size> Vector<size>::Unit(unsigned int axis) {
  Vector<size> result;

  for (unsigned int index = 0; index < size; index++) {
    if (index == axis) {
      result.At(index) = 1.0f;
    } else {
      result.At(index) = 0.0f;
    }
  }

  return result;
}

// begin specialized functions for size = 3

template <>
Vector<3> Vector<3>::CrossProduct(Vector<3> const& other) const {
  float x = scalars_[1] * other.At(2) - scalars_[2] * other.At(1);
  float y = scalars_[2] * other.At(0) - scalars_[0] * other.At(2);
  float z = scalars_[0] * other.At(1) - scalars_[1] * other.At(0);

  return Vector<3>(x, y, z);
}

// end specialized functions for size = 3

// instantiate valid types
template class Vector<2>;
template class Vector<3>;
template class Vector<4>;

} // namespace skylib
