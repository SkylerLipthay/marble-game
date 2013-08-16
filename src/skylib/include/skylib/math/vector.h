#ifndef SKYLIB_MATH_VECTOR_H_
#define SKYLIB_MATH_VECTOR_H_

namespace skylib {

// class is only valid when size = 2, 3, or 4
template <unsigned int size>
class Vector {
 public:
  // empty default constructor
  Vector();
  // specialized for size = 2
  Vector(float a, float b);
  // speciailzed for size = 3
  Vector(float a, float b, float c);
  // speciailized for size = 4
  Vector(float a, float b, float c, float d);

  float& At(unsigned int index);
  float const& At(unsigned int index) const;
  const float *Data() const;
  float Length();
  void Normalize();
  Vector<size> const& Add(Vector<size> const& other);
  Vector<size> const& Subtract(Vector<size> const& other);
  Vector<size> const& Multiply(float const& multiplier);
  Vector<size> const& Divide(float const& divisor);
  Vector<size> Plus(Vector<size> const& other) const;
  Vector<size> Minus(Vector<size> const& other) const;
  Vector<size> MultipliedBy(float const& multiplier) const;
  Vector<size> DividedBy(float const& divisor) const;
  float DotProduct(Vector<size> const& other) const;
  // specialized function for size = 3
  Vector<size> CrossProduct(Vector<size> const& other) const;

  Vector<size> const& operator += (Vector<size> const& other);
  Vector<size> const& operator -= (Vector<size> const& other);
  Vector<size> const& operator *= (float const& multiplier);
  Vector<size> const& operator /= (float const& divisor);
  Vector<size> operator + (Vector<size> const& other) const;
  Vector<size> operator - (Vector<size> const& other) const;
  Vector<size> operator * (float const& multiplier) const;
  Vector<size> operator / (float const& divisor) const;

  static Vector<size> Zero();
  static Vector<size> One();
  static Vector<size> Unit(unsigned int axis);

 private:
  float scalars_[size];
};

} // namespace skylib

#endif // SKYLIB_MATH_VECTOR_H_
