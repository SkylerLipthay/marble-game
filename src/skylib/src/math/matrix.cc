#include <skylib/math/matrix.h>
#include <skylib/math/definitions.h>
#include <algorithm>
#include <cmath>

namespace skylib {

template <unsigned int r, unsigned int c>
Matrix<r, c>::Matrix() {
}

template <unsigned int r, unsigned int c>
Matrix<r, c>::Matrix(float value) {
  std::fill(&data_[0][0], &data_[r][0], value);
}

template <unsigned int r, unsigned int c>
float& Matrix<r, c>::At(unsigned int row, unsigned int column) {
  if (column >= c || row >= r) {
    return data_[0][0];
  }

  return data_[row][column];
}

template <unsigned int r, unsigned int c>
float const& Matrix<r, c>::At(unsigned int row, unsigned int column) const {
  if (column >= c || row >= r) {
    return data_[0][0];
  }

  return data_[row][column];
}

template <unsigned int r, unsigned int c>
const float *Matrix<r, c>::Data() const {
  return reinterpret_cast<const float *>(data_);
}

template <unsigned int r, unsigned int c>
void Matrix<r, c>::Transpose() {
  for (unsigned int row = 0; row < r; row++) {
    for (unsigned int column = 0; column < c; column++) {
      if (row == column) {
        continue;
      }

      std::swap(data_[row][column], data_[column][row]);
    }
  }
}

template <unsigned int r, unsigned int c>
Matrix<r, c> Matrix<r, c>::Transposed() const {
  Matrix<r, c> result = *this;
  result.Transpose();

  return result;
}

template <unsigned int r, unsigned int c>
bool Matrix<r, c>::Equals(Matrix<r, c> const& other) const {
  return std::equal(&data_[0][0], &data_[r][0],
                    reinterpret_cast<const float *>(&other));
}

template <unsigned int r, unsigned int c>
Matrix<r, c> const& Matrix<r, c>::Multiply(float const& multiplier) {
  for (unsigned int row = 0; row < r; row++) {
    for (unsigned int column = 0; column < c; column++) {
      data_[row][column] *= multiplier;
    }
  }

  return *this;
}

template <unsigned int r, unsigned int c>
Matrix<r, c> const& Matrix<r, c>::Multiply(Matrix<r, c> const& other) {
  Matrix<r, c> result = Matrix<r, c>::Identity();

  for (unsigned int i = 0; i < r; i++) {
    for (unsigned int j = 0; j < r; j++) {
      for (unsigned int k = 0; k < c; k++) {
        result.At(i, j) += At(i, k) * other.At(k, j);
      }
    }
  }

  *this = result;

  return *this;
}

template <unsigned int r, unsigned int c>
Matrix<r, c> const& Matrix<r, c>::Divide(float const& divisor) {
  for (unsigned int row = 0; row < r; row++) {
    for (unsigned int column = 0; column < c; column++) {
      data_[row][column] /= divisor;
    }
  }

  return *this;
}

template <unsigned int c, unsigned int r>
Matrix<c, r> Matrix<c, r>::MultipliedBy(float const& multiplier) const {
  Matrix<c, r> result = *this;

  for (unsigned int row = 0; row < r; row++) {
    for (unsigned int column = 0; column < c; column++) {
      result.At(row, column) *= multiplier;
    }
  }

  return result;
}

template <unsigned int c, unsigned int r>
Matrix<c, r> Matrix<c, r>::DividedBy(float const& divisor) const {
  Matrix<c, r> result = *this;

  for (unsigned int row = 0; row < r; row++) {
    for (unsigned int column = 0; column < c; column++) {
      result.At(row, column) /= divisor;
    }
  }

  return result;
}

template <unsigned int r, unsigned int c>
Matrix<r - 1, c - 1> Matrix<r, c>::SubMatrix(unsigned int row_ignore,
                                             unsigned int column_ignore) const {
  if (row_ignore >= r || column_ignore >= c) {
    return SubMatrix(r - 1, c - 1);
  }

  Matrix<r - 1, c - 1> result;
  unsigned int row_current = 0;
  unsigned int column_current;

  for (unsigned int row = 0; row < r; row++) {
    if (row == row_ignore) {
      continue;
    }

    column_current = 0;
    
    for (unsigned int column = 0; column < c; column++) {
      if (column == column_ignore) {
        continue;
      }

      result.At(row_current, column_current) = At(row, column);

      column_current++;
    }

    row_current++;
  }
  
  return result;
}

template <unsigned int r, unsigned int c>
Matrix<r, c> const& Matrix<r, c>::operator *= (float const& multiplier) {
  return Multiply(multiplier);
}

template <unsigned int r, unsigned int c>
Matrix<r, c> const& Matrix<r, c>::operator *= (Matrix<r, c> const& other) {
  return Multiply(other);
}

template <unsigned int r, unsigned int c>
Matrix<r, c> const& Matrix<r, c>::operator /= (float const& divisor) {
  return Divide(divisor);
}

template <unsigned int r, unsigned int c>
Matrix<r, c> Matrix<r, c>::operator * (float const& multiplier) const {
  return MultipliedBy(multiplier);
}

template <unsigned int r, unsigned int c>
Matrix<r, c> Matrix<r, c>::operator / (float const& divisor) const {
  return DividedBy(divisor);
}

template <unsigned int r, unsigned int c>
Matrix<r, c> Matrix<r, c>::Identity() {
  Matrix<r, c> result(0.0f);

  if (r != c) {
    return result;
  }

  for (unsigned int i = 0; i < c; i++) {
    result.At(i, i) = 1.0f;
  }

  return result;
}

// begin specialized functions for c = 3, r = 3

template <>
Matrix<3, 3>::Matrix(float r0c0, float r0c1, float r0c2,
                     float r1c0, float r1c1, float r1c2,
                     float r2c0, float r2c1, float r2c2) {
  data_[0][0] = r0c0;
  data_[0][1] = r0c1;
  data_[0][2] = r0c2;

  data_[1][0] = r1c0;
  data_[1][1] = r1c1;
  data_[1][2] = r1c2;

  data_[2][0] = r2c0;
  data_[2][1] = r2c1;
  data_[2][2] = r2c2;
}

// end specialized functions for c = 3, r = 3

// begin specialized functions for c = 4, r = 4

template <>
Matrix<4, 4>::Matrix(float r0c0, float r0c1, float r0c2, float r0c3,
                     float r1c0, float r1c1, float r1c2, float r1c3,
                     float r2c0, float r2c1, float r2c2, float r2c3,
                     float r3c0, float r3c1, float r3c2, float r3c3) {
  data_[0][0] = r0c0;
  data_[0][1] = r0c1;
  data_[0][2] = r0c2;
  data_[0][3] = r0c3;

  data_[1][0] = r1c0;
  data_[1][1] = r1c1;
  data_[1][2] = r1c2;
  data_[1][3] = r1c3;

  data_[2][0] = r2c0;
  data_[2][1] = r2c1;
  data_[2][2] = r2c2;
  data_[2][3] = r2c3;

  data_[3][0] = r3c0;
  data_[3][1] = r3c1;
  data_[3][2] = r3c2;
  data_[3][3] = r3c3;
}

template <>
void Matrix<4, 4>::GetScale(float& x, float& y, float& z) const {
  x = data_[0][0];
  y = data_[1][1];
  z = data_[2][2];
}

template <>
void Matrix<4, 4>::GetScale(Vector<3>& vector) const {
  GetScale(vector.At(0), vector.At(1), vector.At(2));
}

template <>
void Matrix<4, 4>::GetTranslation(float& x, float& y, float& z) const {
  x = data_[0][3];
  y = data_[1][3];
  z = data_[2][3];
}

template <>
void Matrix<4, 4>::GetTranslation(Vector<3>& vector) const {
  GetScale(vector.At(0), vector.At(1), vector.At(2));
}

template <>
float Matrix<4, 4>::Determinant() const {
  float result = 0.0f;
  int alternate = 1;

  for (unsigned int column = 0; column < 4; column++) {
    Matrix<3, 3> sub = SubMatrix(0, column);

    float determinant = sub.At(0, 0) *
        (sub.At(1, 1) * sub.At(2, 2) - sub.At(2, 1) * sub.At(1, 2));
    determinant -= sub.At(0, 1) *
        (sub.At(1, 0) * sub.At(2, 2) - sub.At(2, 0) * sub.At(1, 2));
    determinant += sub.At(0, 2) *
        (sub.At(1, 0) * sub.At(2, 1) - sub.At(2, 0) * sub.At(1, 1));

    result += At(0, column) * determinant * alternate;
    alternate *= -1;
  }

  return result;
}

template <>
void Matrix<4, 4>::AffineInverse(Matrix<4, 4>& result) const {
  const float *pointer = reinterpret_cast<const float *>(data_);

  result.At(0, 0) = *pointer;
  result.At(1, 0) = *(++pointer);
  result.At(2, 0) = *(++pointer);

  float tx = *(++pointer);

  result.At(0, 1) = *(++pointer);
  result.At(1, 1) = *(++pointer);
  result.At(2, 1) = *(++pointer);

  float ty = *(++pointer);

  result.At(0, 2) = *(++pointer);
  result.At(1, 2) = *(++pointer);
  result.At(2, 2) = *(++pointer);

  float tz = *(++pointer);

  pointer = reinterpret_cast<const float *>(data_);

  result.At(0, 3) = - *pointer * tx;
  result.At(1, 3) = - *(++pointer) * tx;
  result.At(2, 3) = - *(++pointer) * tx;
  
  ++pointer;

  result.At(0, 3) -= *(++pointer) * ty;
  result.At(1, 3) -= *(++pointer) * ty;
  result.At(2, 3) -= *(++pointer) * ty;

  ++pointer;

  result.At(0, 3) -= *(++pointer) * tz;
  result.At(1, 3) -= *(++pointer) * tz;
  result.At(2, 3) -= *(++pointer) * tz;
}

template<>
bool Matrix<4, 4>::Inverse(Matrix<4, 4>& result) const {
  float determinant = Determinant();

  static const float kEpsilon = 0.0005f;
  if (std::abs(determinant) < kEpsilon) {
    return false;
  }

  for (unsigned int row = 0; row < 4; row++) {
    for (unsigned int column = 0; column < 4; column++) {
      int sign = 1 - ((row + column) % 2) * 2;

      Matrix<3, 3> sub = SubMatrix(row, column);

      float sub_determinant = sub.At(0, 0) *
          (sub.At(1, 1) * sub.At(2, 2) - sub.At(2, 1) * sub.At(1, 2));
      sub_determinant -= sub.At(0, 1) *
          (sub.At(1, 0) * sub.At(2, 2) - sub.At(2, 0) * sub.At(1, 2));
      sub_determinant += sub.At(0, 2) *
          (sub.At(1, 0) * sub.At(2, 1) - sub.At(2, 0) * sub.At(1, 1));

      result.At(row, column) = (sub_determinant * sign) / determinant;
    }
  }

  return true;
}

template <>
Matrix<4, 4> Matrix<4, 4>::RotateX(float degrees) {
  Matrix<4, 4> result = Matrix<4, 4>::Identity();

  float sr = std::sin(degrees * kPiOver180);
  float cr = std::cos(degrees * kPiOver180);

  result.At(1, 1) = cr;
  result.At(2, 1) = -sr;
  result.At(1, 2) = sr;
  result.At(2, 2) = cr;

  return result;
}

template <>
Matrix<4, 4> Matrix<4, 4>::RotateY(float degrees) {
  Matrix<4, 4> result = Matrix<4, 4>::Identity();

  float sr = std::sin(degrees * kPiOver180);
  float cr = std::cos(degrees * kPiOver180);

  result.At(0, 0) = cr;
  result.At(2, 0) = sr;
  result.At(0, 2) = -sr;
  result.At(2, 2) = cr;

  return result;
}

template <>
Matrix<4, 4> Matrix<4, 4>::RotateZ(float degrees) {
  Matrix<4, 4> result = Matrix<4, 4>::Identity();

  float sr = std::sin(degrees * kPiOver180);
  float cr = std::cos(degrees * kPiOver180);

  result.At(0, 0) = cr;
  result.At(1, 0) = -sr;
  result.At(0, 1) = sr;
  result.At(1, 1) = cr;

  return result;
}

template <>
Matrix<4, 4> Matrix<4, 4>::Scale(float x, float y, float z) {
  Matrix<4, 4> result = Matrix<4, 4>::Identity();

  result.At(0, 0) = x;
  result.At(1, 1) = y;
  result.At(2, 2) = z;

  return result;
}

template <>
Matrix<4, 4> Matrix<4, 4>::Scale(Vector<3> const& vector) {
  return Scale(vector.At(0), vector.At(1), vector.At(2));
}

template <>
Matrix<4, 4> Matrix<4, 4>::Translate(float x, float y, float z) {
  Matrix<4, 4> result = Matrix<4, 4>::Identity();

  result.At(3, 0) = x;
  result.At(3, 1) = y;
  result.At(3, 2) = z;

  return result;
}

template <>
Matrix<4, 4> Matrix<4, 4>::Translate(Vector<3> const& vector) {
  return Translate(vector.At(0), vector.At(1), vector.At(2));
}

// end specialized functions for c = 4, r = 4

// instantiate valid types
template class Matrix<3, 3>;
template class Matrix<4, 4>;

} // namespace skylib
