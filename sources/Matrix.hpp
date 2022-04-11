#include <iostream>
#include <vector>
using namespace std;

namespace zich
{
    class Matrix
    {
    private:
        int row;
        int col;
        std::vector<double> v;

    public:
        Matrix(vector<double> v, int row, int col); /* constructor for the matrix */
        // void operator=(const Matrix &temp);                         /* make one matrix get the parametes of the other */
        Matrix operator+(const Matrix &second);                     /* add one matrix to another and return the new matrix */
        Matrix operator+();                                         /* unary plus - nothing happend to the matrix */
        void operator+=(const Matrix &second);                      /* add to the first matrix the second, and return the first after adding the numbers of matrix 2 */
        Matrix &operator++();                                       /* increasing the matrix by 1 and return the matrix after we add to it */
        Matrix operator++(int num);                                 /* create a copy of the matrix, add to the matrix and return the copy */
        Matrix operator-(const Matrix &second);                     /* decrease one matrix fro another and return the new matrix */
        Matrix operator-();                                         /* unary minus - all the values of the matrix is multiple in -1 */
        void operator-=(const Matrix &second);                      /* decrease from the first matrix the second, and return the first after decreasing  the numbers of matrix 2 */
        Matrix &operator--();                                       /*  decreasing the matrix by 1 and return the matrix after we remove from it */
        Matrix operator--(int num);                                 /* create a copy of the matrix, remove from the matrix and return the copy */
        Matrix operator*(const Matrix &second);                     /* multiply one matrix with another */
        Matrix &operator*=(const Matrix &second);                   /* multiply one matrix with another and save it to the first */
        friend Matrix operator*(double num, const Matrix &current); /* multiply one matrix in a double number */
        Matrix operator*(double num) const;                         /* multiply one matrix in a double number */
        void operator*=(double num);                                /* multiply one matrix on the current matrix */
        bool operator==(const Matrix &second) const;                /* matrix first is equal to matrix second */
        bool operator!=(const Matrix &second) const;                /* matrix first is not equal to matrix second */
        bool operator>(const Matrix &second) const;                 /* matrix first is bigger from matrix second */
        bool operator>=(const Matrix &second) const;                /* matrix first is bigger-equal from matrix second */
        bool operator<(const Matrix &other) const;                  /* matrix first is smaller from matrix second */
        bool operator<=(const Matrix &other) const;                 /* matrix first is smaller-equal from matrix second */
        friend std::ostream &operator<<(std::ostream &output, const Matrix &m);
        friend std::istream &operator>>(std::istream &input, Matrix &m);
    };
}
