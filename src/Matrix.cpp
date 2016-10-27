/*
 * Matrix.cpp
 *
 *  Created on: Oct 24, 2016
 *      Author: link
 */

#include "motion_blow/Matrix.hpp"

Matrix Matrix::operator +(const Matrix& m) const
{
    if (getWidth() == m.getWidth() && getHeigth() == m.getHeigth())
    {
        std::vector<std::vector<double>> tmp(_width,
                std::vector<double>(_height));
        for (int i = 0; i < _width; ++i)
        {
            for (int j = 0; j < _height; ++j)
            {
                tmp[i][j] = _data[i][j] + m._data[i][j];
            }
        }
        return Matrix(_width, _height, tmp);
    }
    else
    {
        std::exception except;
        throw except;
    }

}

Matrix Matrix::operator -(const Matrix& m) const
{
    return *this + m * (-1);
}

Matrix Matrix::operator *(const Matrix& m) const
{
    if (getWidth() == m.getHeigth())
    {
        std::vector<std::vector<double>> tmp(m._width,
                std::vector<double>(_height, 0));
        for (int i = 0; i < m._width; ++i)
        {
            for (int j = 0; j < _height; ++j)
            {
                for (int k = 0; k < _width; ++k)
                {
                    tmp[i][j] += _data[k][j] * m._data[i][k];
                }
            }
        }
        return Matrix(m._width, _height, tmp);
    }
    else
    {
        std::exception except;
        throw except;
    }
}

Matrix Matrix::operator *(const double& s) const
{
    std::vector<std::vector<double>> tmp(_width, std::vector<double>(_height));
    for (int i = 0; i < _width; ++i)
    {
        for (int j = 0; j < _height; ++j)
        {
            tmp[i][j] = _data[i][j] * s;
        }
    }
    return Matrix(_width, _height, tmp);
}

Matrix Matrix::t() const
{
    std::vector<std::vector<double>> tmp(_width, std::vector<double>(_height));
    for (int i = 0; i < _width; ++i)
    {
        for (int j = 0; j < _height; ++j)
        {
            tmp[i][j] = _data[j][i];
        }
    }
    return Matrix(_width, _height, tmp);
}

bool Matrix::operator ==(const Matrix& m) const
{
    return _data == m._data && _width == m._width && _height == m._height;
}

double& Matrix::at(unsigned i, unsigned j)
{
    return _data[i][j];
}
