#include <iostream>
#include <type_traits>
#include <cmath>
// Declaration of Matrix class
template <typename T, std::size_t Rows, std::size_t Cols>
class Matrix;
// Template for generic matrix
template <typename T, std::size_t Rows, std::size_t Cols>
class Matrix {
public:
    // Constructors
    Matrix() = default;
    // Access operators
    T& operator()(std::size_t row, std::size_t col) {
        return data[row][col];
    }
    const T& operator()(std::size_t row, std::size_t col) const {
        return data[row][col];
    }
    // Matrix addition
    Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i)
            for (std::size_t j = 0; j < Cols; ++j)
                result(i, j) = data[i][j] + other(i, j);
        return result;
    }
    // Matrix subtraction
    Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i)
            for (std::size_t j = 0; j < Cols; ++j)
                result(i, j) = data[i][j] - other(i, j);
        return result;
    }
    // Matrix multiplication
    template <std::size_t N>
    Matrix<T, Rows, N> operator*(const Matrix<T, Cols, N>& other) const {
        Matrix<T, Rows, N> result;
        for (std::size_t i = 0; i < Rows; ++i)
            for (std::size_t j = 0; j < N; ++j)
                for (std::size_t k = 0; k < Cols; ++k)
                    result(i, j) += data[i][k] * other(k, j);
        return result;
    }
    // Scalar multiplication
    Matrix<T, Rows, Cols> operator*(T scalar) const {
        Matrix<T, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i)
            for (std::size_t j = 0; j < Cols; ++j)
                result(i, j) = data[i][j] * scalar;
        return result;
    }
    // Transpose
    Matrix<T, Cols, Rows> transpose() const {
        Matrix<T, Cols, Rows> result;
        for (std::size_t i = 0; i < Cols; ++i)
            for (std::size_t j = 0; j < Rows; ++j)
                result(i, j) = data[j][i];
        return result;
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Cols>& matrix) {
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                os << matrix(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }
private:
    T data[Rows][Cols] = {};
};
template <typename T, std::size_t Rows>
class Matrix<T, Rows, 1> {
public:
    // Constructors
    Matrix() = default;
    // Access operators
    T& operator()(std::size_t row) {
        return data[row][0];
    }
    const T& operator()(std::size_t row) const {
        return data[row][0];
    }
    // Addition
    Matrix<T, Rows, 1> operator+(const Matrix<T, Rows, 1>& other) const {
        Matrix<T, Rows, 1> result;
        for (std::size_t i = 0; i < Rows; ++i)
            result(i) = data[i][0] + other(i);
        return result;
    }
    // Subtraction
    Matrix<T, Rows, 1> operator-(const Matrix<T, Rows, 1>& other) const {
        Matrix<T, Rows, 1> result;
        for (std::size_t i = 0; i < Rows; ++i)
            result(i) = data[i][0] - other(i);
        return result;
    }
    // Multiplication
    Matrix<T, Rows, 1> operator*(T scalar) const {
        Matrix<T, Rows, 1> result;
        for (std::size_t i = 0; i < Rows; ++i)
            result(i) = data[i][0] * scalar;
        return result;
    }
    // Transpose
    Matrix<T, 1, Rows> transpose() const {
        Matrix<T, 1, Rows> result;
        for (std::size_t i = 0; i < Rows; ++i)
            result(0, i) = data[i][0];
        return result;
    }
    // L2 norm calculation
    T norm() const {
        T result = 0;
        for (std::size_t i = 0; i < Rows; ++i)
            result += data[i][0] * data[i][0];
        return std::sqrt(result);
    }
    //  "<<" operator for printing
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, 1>& vector) {
        for (std::size_t i = 0; i < Rows; ++i) {
            os << vector(i) << std::endl;
        }
        return os;
    }
private:
    T data[Rows][1] = {};
};
int main() {
    Matrix<double, 2, 3> mat1;
    Matrix<double, 3, 2> mat2;
    
    Matrix<double, 2, 1> vec1;
    Matrix<double, 2, 1> vec2; 
    auto mat3 = mat1 * mat2;   
    auto vec_sum = vec1 + vec2;
    auto vec_diff = vec1 - vec2;
    auto vec_scalar = vec1 * 2.0;
    auto vec_norm = vec1.norm();
    std::cout << "Matrix 1:" << std::endl << mat1 << std::endl;
    std::cout << "Matrix 2:" << std::endl << mat2 << std::endl;
    std::cout << "Matrix 3:" << std::endl << mat3 << std::endl;  // Will result in a compile-time error
    std::cout << "Vector 1:" << std::endl << vec1 << std::endl;
    std::cout << "Vector 2:" << std::endl << vec2 << std::endl;
    std::cout << "Vector Sum:" << std::endl << vec_sum << std::endl;
    std::cout << "Vector Difference:" << std::endl << vec_diff << std::endl;
    std::cout << "Vector Scalar Multiplication:" << std::endl << vec_scalar << std::endl;
    std::cout << "Vector Norm: " << vec_norm << std::endl;
    return 0;
}
