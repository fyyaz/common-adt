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

#include "../inc/big-integer.h"

/* Default Constructor
 * Initializes big integer to 0
 */
BigInteger::BigInteger()
{
    this->digit.resize(1);
    this->digit[0] = '0';
    this->signbit = POSITIVE;
}

/* Default Deconstructor
 * Initializes big integer to 0
 */
BigInteger::~BigInteger()
{
    this->length = 0;
    this->digit.resize(this->length);
}

/* Constructor for string values
 * Initializes big integer to num
 */
BigInteger::BigInteger(const std::string &num)
{
    if((int)num.size() == 0)
    {
        // default to 0
        this->length = 1;
        this->digit.resize(this->length);
        this->digit[0] = '0';
        this->signbit = POSITIVE;
    }
    else
    {
        if(num[0] == '-')
        {
            this->signbit = NEGATIVE;
            this->length = (int)num.size()-1;
            this->digit.resize(this->length);
            // assign positions from least significant digit
            // -1000
            //     ^- least significant
            for(int i = this->length, j = 0;i >= 1;i--)
                this->digit[j++] = num[i];
        }
        else{
            this->signbit = POSITIVE;
            this->length = (int)num.size()-1;
            this->digit.resize(this->length);
            // assign positions from least significant digit
            // 1000
            //    ^- least significant
            for(int i = this->length, j = 0;i >= 0;i--)
                this->digit[j++] = num[i];
        }
    }
}

/* Constructor for int values
 * Initializes big integer to num
 */
BigInteger::BigInteger(int num)
{
    if(num >= 0)
    {
        this->signbit = POSITIVE;
    }
    else
    {
        this->signbit = NEGATIVE;
        num *=-1;
    }
    this->length = (int)std::floor(std::log10(num)+1);
    this->digit.resize(this->length);
    this->digit[0] = '0';
    // we can get the least significant digit by modding num by 10
    // then we just divide by 10 to get the next least significant digit
    for(int i = 0;i < length && num != 0;i++){
        digit[i] = (num%10)+'0';
        num/=10;
    }
}

/* Constructor for long long values
 * Initializes big integer to num
 */
BigInteger::BigInteger(long long num)
{
    if(num >= 0)
    {
        this->signbit = POSITIVE;
    }
    else
    {
        this->signbit = NEGATIVE;
        num *=-1;
    }
    this->length = (int)std::floor(std::log10(num)+1);
    this->digit.resize(this->length);
    this->digit[0] = '0';
    // we can get the least significant digit by modding num by 10
    // then we just divide by 10 to get the next least significant digit
    for(int i = 0;i < length && num != 0;i++){
        digit[i] = (num%10)+'0';
        num/=10;
    }
}

/* This method simply be increases the magnitude of the number. It does not
 * deal with addition of postive and negative numbers.
 */
void BigInteger::add(BigInteger &num)
{
    int final_length = std::max(this->length, num.length)+2;
    int carry = 0;
    // we will add leading zeroes to make looping less cumbersome
    this->length = final_length;
    this->digit.resize(final_length);
    num.digit.resize(final_length);
    num.digit.resize(final_length);
    for(int i = 0,sum = 0;i < final_length;i++)
    {
        sum = carry;
        carry = 0;
        // since we added the leading zeroes this will break when it
        // detects two characters that aren't roman numerals and when
        // the carry value is zero
        if(!isdigit(this->digit[i]) && !isdigit(num.digit[i]) && sum == 0)
        {
            break;
        }
        else
        {
            // we're only going to add valid characters
            // so we skip over numbers of a smaller length in a sence
            // for example
            // 00001
            // 0001
            if(isdigit(this->digit[i]))
                sum += this->digit[i]-'0';
            if(isdigit(num.digit[i]))
                sum += num.digit[i]-'0';
            if(sum >= 10){
                sum %= 10;
                carry = 1;
            }
            this->digit[i] = sum+'0';
        }
    }
    // remove the characters that were appended to each number
    this->zero_justify();
    num.zero_justify();
}

/* This method simply be decreases the magnitude of the number. It does not
 * deal with subtraction of postive and negative numbers.
 */
void BigInteger::sub(BigInteger &num)
{
    int final_length = std::max(this->length, num.length)+2;
    int burrow = 0;
    // we will add leading zeroes to make looping less cumbersome
    this->length = final_length;
    this->digit.resize(final_length);
    num.digit.resize(final_length);
    num.digit.resize(final_length);
    for(int i = 0;i < final_length;i++)
    {
        int current_digit = this->digit[i]-'0';
        int sum = current_digit - burrow;
        burrow = 0;
        // only subtract when there's a valid digit
        if(isdigit(num.digit[i]))
        {
            if(sum - current_digit < 0)
            {
                sum += 10;
                burrow = 1;
                sum -= current_digit;
            }
            else
            {
                sum -= current_digit;
            }
        }
        // this only matters
        // when our current number is bigger than the provided number
        if(!isdigit(num.digit[i]))
        {
            if(sum < 0)
            {
                sum += 10;
                burrow = 1;
            }
        }
        this->digit[i] = sum+'0';
    }
    // remove the leading zeros inserted earlier
    this->zero_justify();
}

/* This method removes leading characters in the array until a valid
 * character is found. For reference of where this is used look at
 * BigInteger::add(BigInteger &num)
 */
void BigInteger::zero_justify()
{
    int last_index = this->length;
    // continally remove invalid elements
    while(!isdigit(this->digit[last_index]))
    {
        this->digit.pop_back();
        this->length--;
        last_index = this->length;
    }
    // Added this statement to avoid -0
    // -0 usually occurs when BigInteger::sub(BigInteger &num) is called
    if(this->digit[last_index] == 0 && this->digit[0] == 0)
        this->signbit = POSITIVE;
}

/* Compares the magnitude of two integers. So doesn't take into considerations
 * if it's positivety or negativity. Equivalient to < operator but only with
 * magnitude.
 * Return: -1 if current number > num
 *          0 if current number == num
 *          1 if current number < num
 */
int BigInteger::compare_magnitude(const BigInteger &num)
{
    int cur_len = this->length;
    int cmp_len = this->length;
    if(cur_len < cmp_len)
    {
        return 1;
    }
    else if(cmp_len < cur_len)
    {
        return -1;
    }
    else
    {
        // compare each digit individually now
        int len = cur_len;
        for(int i = len-1;i >= 0;i--)
        {
            if(this->digit[i] == num.digit[i])
            {
                continue;
            }
            else
            {
                if(this->digit[i] < num.digit[i])
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
        }
        // only reaches this statement when they are the same number
        return 0;
    }
}

/* Compares two numbers based on magnitude and sign
 * i.e. A < B
 */
bool BigInteger::operator <  (const BigInteger &num)const
{
    if(this->signbit == NEGATIVE && num.signbit == POSITIVE)
    {
        return true;
    }
    else if(this->signbit == POSITIVE && num.signbit == NEGATIVE)
    {
        return false;
    }
    else if(this->signbit == POSITIVE && num.signbit == POSITIVE)
    {
        return compare_magnitude(num);
    }
    else if(this->signbit == NEGATIVE && num.signbit == NEGATIVE)
    {
        return compare_magnitude(num) == -1;
    }
    else
    {
        return false;
    }
}


// /* This operator is used for simple addition
//  * i.e. A = B+C
//  */
// BigInteger BigInteger::operator + (const BigInteger &num)
// {
//     // get a copy of the current number this operator was invoked on
//     BigInteger ret(*this);
//     ret += num;
//     return ret;
// }

// // TODO

// void BigInteger::operator += (const BigInteger &num){
//     if(this->signbit == POSITIVE && num.signbit == POS)
//         this->add(num)
//     else if(this->signbit == NEG  && b.signbit == NEG)
//         this->add(num);
//     else if(this->signbit == POS && b.signbit == NEG){
//         if(*this >= b)
//             this->sub(b);
//         else{
//             bigint a(*this);
//             *this = b;
//             this->sub(a);
//         }
//     }
//     else if(this->signbit == NEG && b.signbit == POS){
//         if(*this >= b)
//             this->sub(b);
//         else{
//             bigint a(*this);
//             *this = b;
//             this->sub(a);
//         }
//     }
// }