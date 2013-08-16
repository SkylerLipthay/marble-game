#ifndef SKYLIB_MATH_MATRIX_H_
#define SKYLIB_MATH_MATRIX_H_

#include <skylib/math/vector.h>

namespace skylib {

// class is only valid when r = 4, c = 4
// rows, columns
template <unsigned int r, unsigned int c>
class Matrix {
 public:
  Matrix();
  Matrix(float value);

  float& At(unsigned int row, unsigned int column);
  float const& At(unsigned int row, unsigned int column) const;
  const float *Data() const;
  void Transpose();
  Matrix<r, c> Transposed() const;
  bool Equals(Matrix<r, c> const& other) const;
  Matrix<r, c> const& Multiply(float const& multiplier);
  Matrix<r, c> const& Multiply(Matrix<r, c> const& other);
  Matrix<r, c> const& Divide(float const& divisor);
  Matrix<r, c> MultipliedBy(float const& multiplier) const;
  template <unsigned int p>
  Matrix<r, p> MultipliedBy(Matrix<c, p> const& other) const;
  Matrix<r, c> DividedBy(float const& divisor) const;
  Matrix<r - 1, c - 1> SubMatrix(unsigned int row_ignore,
                                 unsigned int column_ignore) const;

  Matrix<r, c> const& operator *= (float const& multiplier);
  Matrix<r, c> const& operator *= (Matrix<r, c> const& other);
  Matrix<r, c> const& operator /= (float const& divisor);
  Matrix<r, c> operator * (float const& multiplier) const;
  template <unsigned int p>
  Matrix<r, p> operator * (Matrix<c, p> const& other) const;
  Matrix<r, c> operator / (float const& divisor) const;

  static Matrix<r, c> Identity();

  // begin specialized functions for c = 3, r = 3
  
  Matrix(float r0c0, float r0c1, float r0c2,
         float r1c0, float r1c1, float r1c2,
         float r2c0, float r2c1, float r2c2);

  // end specialized functions for c = 3, r = 3

  // begin specialized functions for c = 4, r = 4

  Matrix(float r0c0, float r0c1, float r0c2, float r0c3,
         float r1c0, float r1c1, float r1c2, float r1c3,
         float r2c0, float r2c1, float r2c2, float r2c3,
         float r3c0, float r3c1, float r3c2, float r3c3);

  void GetScale(float& x, float& y, float& z) const;
  void GetScale(Vector<3>& vector) const;
  void GetTranslation(float& x, float& y, float& z) const;
  void GetTranslation(Vector<3>& vector) const;
  float Determinant() const;
  void AffineInverse(Matrix<4, 4>& result) const;
  bool Inverse(Matrix<4, 4>& result) const;

  static Matrix<r, c> RotateX(float degrees);
  static Matrix<r, c> RotateY(float degrees);
  static Matrix<r, c> RotateZ(float degrees);
  static Matrix<r, c> Scale(float x, float y, float z);
  static Matrix<r, c> Scale(Vector<3> const& vector);
  static Matrix<r, c> Translate(float x, float y, float z);
  static Matrix<r, c> Translate(Vector<3> const& vector);

  // end specialized functions for c = 4, r = 4

 private:
  // column-major ordering
  float data_[r][c];
};

template <unsigned int r, unsigned int c>
template <unsigned int p>
Matrix<r, p> Matrix<r, c>::MultipliedBy(Matrix<c, p> const& other) const {
  Matrix<r, p> result(0);

  for (unsigned int i = 0; i < r; i++) {
    for (unsigned int j = 0; j < p; j++) {
      for (unsigned int k = 0; k < c; k++) {
        result.At(i, j) += At(i, k) * other.At(k, j);
      }
    }
  }

  return result;
}

template <unsigned int r, unsigned int c>
template <unsigned int p>
Matrix<r, p> Matrix<r, c>::operator * (Matrix<c, p> const& other) const {
  return MultipliedBy(other);
}

typedef Matrix<4, 4> Transform;

} // namespace skylib

#endif // SKYLIB_MATH_MATRIX_H_
