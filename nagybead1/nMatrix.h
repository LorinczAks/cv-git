#ifndef NMATRIX_H
#define NMATRIX_H

#include <string>
#include <vector>
#include <iostream>
#include <ostream>

class NMatrix {
    public:
        enum Exception { OVERINDEXED, NOT_MATCHING_SIZE, NULLPART };
        NMatrix();
        NMatrix(int n);
        int getItem(int i) const;
        int getItem(int i, int j) const;
        int getSize() const;


        void setItem(int a);
        void setItem(int i, int j, int a);
        int getVectorLength() const;
        NMatrix operator+(const NMatrix& rhs) const;
        NMatrix operator*(const NMatrix& rhs) const;
        friend std::ostream &operator<<(std::ostream &os, const NMatrix &matrix);
    private:
        NMatrix(std::vector<int> vec, int n);
        int size;
        std::vector<int> vec_;
};

#endif