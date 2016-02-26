// Copyright (c) 2016 William Granados
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef BIG_INTEGER_INC_BIG_INTEGER_H_
#define BIG_INTEGER_INC_BIG_INTEGER_H_

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

class BigInteger
{
    #define POSITIVE 1
    #define NEGATIVE -1
    // class members
    private:
        std::vector<char>digit;
        int signbit;
        int length;

    // constructors and destructor
    public:
        BigInteger();
        ~BigInteger();
        BigInteger(const std::string&num);
        BigInteger(int num);
        BigInteger(long long num);

    // utility methods
    private:
        void add(BigInteger &num);
        void sub(BigInteger &num);

    // more utility methods
    public:
        void zero_justify();
        int compare_magnitude(const BigInteger &num)const;

     // boolean operators
    public:
        bool operator < (const BigInteger&num)const;
        bool operator > (const BigInteger&num)const;
        bool operator >= (const BigInteger&num)const;
        bool operator <= (const BigInteger&num)const;
        bool operator != (const BigInteger&num)const;
        bool operator == (const BigInteger&num)const;

    // assignment operators
    public:
        void operator =  (const BigInteger &num);
        void operator =  (int num);
        void operator =  (long long num);
        void operator += (BigInteger &num);
        void operator -= (BigInteger &num);
        void operator *= (BigInteger &num);
        void operator /= (BigInteger &num);

    // arithmetic operators
    public:
        BigInteger operator +  (BigInteger &num);
        BigInteger operator -  (BigInteger &num);
        BigInteger operator *  (BigInteger &num);
        BigInteger operator /  (BigInteger &num);
        BigInteger operator %  (BigInteger &num);


    // output/input operators
};

#endif