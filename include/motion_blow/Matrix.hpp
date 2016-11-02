#pragma once
#include <array>
#include <vector>

class Matrix
{
    const unsigned _width;
    const unsigned _height;
    std::vector<std::vector<double>> _data;
public:
    Matrix(const unsigned &width, const unsigned &height)
            : _width(width), _height(height)
    {
    }
    Matrix(const unsigned &width, const unsigned &height,
            const std::vector<std::vector<double>> &data)
            : _width(width), _height(height), _data(data)
    {
    }

    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;
    Matrix operator*(const double &s) const;
    bool operator==(const Matrix &m) const;
    bool operator!=(const Matrix &m) const;
    unsigned getWidth() const
    {
        return _width;
    }
    unsigned getHeigth() const
    {
        return _height;
    }
    Matrix t() const;
    double &at(unsigned i, unsigned j);
    static Matrix IdentityMatrix(const unsigned &size);
};

class MatrixException: public std::exception
{

};
