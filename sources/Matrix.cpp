#include <iostream>
#include <vector>
#include <string>
#include "Matrix.hpp"
using namespace std;
using namespace zich;

namespace zich
{
    /* constructor for the matrix */
    Matrix::Matrix(vector<double> v, int row, int col)
    {
        if (row < 1 || col < 1)
        {
            throw std::invalid_argument("you can't create a matrix smaller then 1X1");
        }
        if (size(v) != row * col)
        {
            throw std::invalid_argument("you can't create a matrix with those values");
        }

        this->v.resize((unsigned int)(row * col));
        for (uint i = 0; i < row * col; ++i)
        {
            this->v[i] = v[i];
        }
        this->row = row;
        this->col = col;
    }

    /* add one matrix to another and return the new matrix */
    Matrix Matrix::operator+(const Matrix &second)
    {

        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't add differet nXm matrix's");
        }
        vector<double> copy(this->v.begin(), this->v.end());
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy[i] += second.v[i];
        }
        return Matrix(copy, row, col);
    }
    /* unary plus - nothing happend to the matrix */
    Matrix Matrix::operator+()
    {
        vector<double> copy(this->v.begin(), this->v.end());
        return Matrix(copy, this->row, this->col);
    }

    /* add to the first matrix the second, and return the first after adding the numbers of matrix 2 */
    void Matrix::operator+=(const Matrix &second)
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't add differet nXm matrix's");
        }
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] += second.v[i];
        }
    }

    /* increasing the matrix by 1 and return the matrix after we add to it */
    Matrix &Matrix::operator++()
    {
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] += 1;
        }
        return *this;
    }

    /* create a copy of the matrix, add to the matrix and return the copy */
    Matrix Matrix::operator++(int)
    {
        vector<double> copy(this->v.begin(), this->v.end());
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] += 1;
        }
        return Matrix(copy, this->row, this->col);
    }

    /* decrease one matrix from another and return the new matrix */
    Matrix Matrix::operator-(const Matrix &second)
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        vector<double> copy(this->v.begin(), this->v.end());
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy[i] -= second.v[i];
        }
        return Matrix(copy, this->row, this->col);
    }

    /* unary minus - all the values of the matrix is multiple in -1 */
    Matrix Matrix::operator-()
    {
        vector<double> copy(this->v.begin(), this->v.end());
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy[i] *= -1;
        }
        return Matrix(copy, this->row, this->col);
    }
    /* decrease from the first matrix the second, and return the first after decreasing  the numbers of matrix 2 */
    void Matrix::operator-=(const Matrix &second)
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] -= second.v[i];
        }
    }

    /*  decreasing the matrix by 1 and return the matrix after we remove from it */
    Matrix &Matrix::operator--()
    {
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] -= 1;
        }
        return *this;
    }

    /* create a copy of the matrix, remove from the matrix and return the copy */
    Matrix Matrix::operator--(int)
    {
        vector<double> copy(this->v.begin(), this->v.end());
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] -= 1;
        }
        return Matrix(copy, this->row, this->col);
    }

    /* multiply one matrix with another */
    Matrix Matrix::operator*(const Matrix &second)
    {
        if (this->col != second.row)
        {
            throw std::invalid_argument("you can't multiply matrix that has differet nXm mXt m size");
        }
        int size = (int)(this->row * second.col);
        vector<double> copy((unsigned int)size, 0);
        size_t copy_row = size_t(this->row);
        size_t copy_col = size_t(second.col);

        for (size_t i = 0; i < copy_row; i++)
        {
            for (size_t j = 0; j < copy_col; j++)
            {
                for (size_t k = 0; k < second.row; k++)
                {
                    copy[i * copy_col + j] += this->v[i * size_t(this->col) + k] * second.v[k * copy_col + j];
                }
            }
        }

        return Matrix(copy, this->row, second.col);
    }

    Matrix &Matrix::operator*=(const Matrix &second) /* fixed! */
    {
        if (this->col != second.row)
        {
            throw std::invalid_argument("you can't multiply matrix that has differet nXm mXt m size");
        }
        Matrix copy = *this;
        Matrix ans = copy * second;

        this->col = ans.col;
        this->row = ans.row;
        this->v = ans.v;

        return *this;
    }

    /* multiply one matrix in a double number */
    Matrix operator*(double num, const Matrix &current)
    {
        vector<double> copy(size_t(current.row * current.col));
        for (size_t i = 0; i < size(current.v); i++)
        {
            copy[i] = current.v[i] * num;
        }
        return Matrix(copy, current.row, current.col);
    }

    /* multiply one matrix in a double number */
    Matrix Matrix::operator*(double num) const
    {
        vector<double> copy(this->v.begin(), this->v.end());
        for (size_t i = 0; i < size(this->v); i++)
        {
            copy[i] *= num;
        }
        return Matrix(copy, this->row, this->col);
    }

    /* multiply one matrix in a double number and add to it */
    void Matrix::operator*=(double num)
    {
        for (size_t i = 0; i < size(this->v); i++)
        {
            this->v[i] *= num;
        }
    }

    /* matrix first is equal to matrix second */
    bool Matrix::operator==(const Matrix &second) const
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't compare differet nXm matrix's");
        }
        if (size(this->v) != size(second.v))
        {
            throw std::invalid_argument("you can't compare differet nXm matrix's");
        }
        for (size_t i = 0; i < size(this->v); i++)
        {
            if (this->v[i] != second.v[i])
            {
                return false;
            }
        }
        return true;
    }

    /* matrix first is not equal to matrix second */
    bool Matrix::operator!=(const Matrix &second) const
    {
        Matrix temp = *this;
        return !(temp == second);
    }

    /* matrix first is bigger then matrix second */
    bool Matrix::operator>(const Matrix &second) const
    {
        if (this->col != second.col || this->row != second.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        double sum_this = 0;
        double sum_second = 0;

        for (size_t i = 0; i < size(this->v); i++)
        {
            sum_this += this->v[i];
            sum_second += second.v[i];
        }
        return sum_this > sum_second;
    }

    /* matrix first is bigger-equal from matrix second */
    bool Matrix::operator>=(const Matrix &second) const
    {
        Matrix temp = *this;
        bool equal = temp == second;
        bool bigger = temp > second;
        return equal || bigger;
    }

    /* matrix first is smaller then matrix second */
    bool Matrix::operator<(const Matrix &other) const
    {
        if (this->col != other.col || this->row != other.row)
        {
            throw std::invalid_argument("you can't decrease differet nXm matrix's");
        }
        double sum_this = 0;
        double sum_second = 0;

        for (size_t i = 0; i < size(this->v); i++)
        {
            sum_this += this->v[i];
            sum_second += other.v[i];
        }
        return sum_this < sum_second;
    }

    /* matrix first is smaller-equal from matrix second */
    bool Matrix::operator<=(const Matrix &other) const
    {
        Matrix temp = *this;
        bool equal = temp == other;
        bool smaller = temp < other;
        return equal || smaller;
    }

    std::ostream &operator<<(std::ostream &output, const Matrix &m)
    {

        size_t final_row = size_t(m.row);
        size_t final_col = size_t(m.col);

        for (size_t i = 0; i < final_row; i++)
        {
            output << '[';
            for (size_t j = 0; j < final_col; j++)
            {
                output << m.v[(i * final_col) + j];
                if (j < final_col - 1)
                {
                    output << ' ';
                }
            }
            output << ']';
            if (i < final_row - 1)
            {
                output << '\n';
            }
        }
        return output;
    }
    std::istream &operator>>(std::istream &input, Matrix &m)
    {
        int open = 0;
        int close = 0;
        int row = 0;
        int col = 0;
        string value;
        getline(input, value);

        if (value[0] != '[' || value[size(value) - 1] != ']')
        {
            throw std::invalid_argument("invalid input1");
        }
        for (size_t i = 0; i < size_t(size(value) - 1); i++)
        {
            if ((value[i] < '0' || value[i] > '9') && value[i] != '[' && value[i] != ']' && value[i] != ',' && value[i] != ' ' && value[i] != '.')
            {
                throw std::invalid_argument("invalid char");
            }
            if (value[i] == '[' && (value[i + 1] < '0' || value[i + 1] > '9'))
            {
                throw std::invalid_argument("invalid input2");
            }
            if (value[i] == ']' && value[i + 1] != ',')
            {
                if (value[i + 1] != '\n')
                {
                    throw std::invalid_argument("invalid input3");
                }
            }
            if (value[i] == ',' && value[i + 1] != ' ')
            {
                throw std::invalid_argument("invalid input4");
            }
            if (value[i] == ' ' && value[i + 1] != '[')
            {
                if (value[i + 1] < '0' || value[i + 1] > '9')
                {
                    cout << "hey :" << value[i] << "," << value[i + 1] << ":finished";
                    throw std::invalid_argument("invalid input5");
                }
            }

            if (value[i] == '[')
            {
                open++;
            }
            if (value[i] == ']')
            {
                close++;
            }
        }
        if (value[size(value) - 1] == ']')
        {
            close++;
        }
        if (open != close)
        {
            throw std::invalid_argument("invalid input6");
        }

        return input;
    }
}
