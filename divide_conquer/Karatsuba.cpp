//! This file implements karatsuba algorithm, which is frequently used in integer mul.
#include <deque>
#include <iostream>
#include <algorithm>

constexpr int numMax = 10;

struct Number
{
    Number(std::size_t size, bool sign):NumVec(size), Sign(sign){
        //NumVec.reserve(size + 1);
    }

    std::size_t size() const
    {
        return NumVec.size();
    }

    int operator[](std::size_t idx) const
    {
        return NumVec.at(NumVec.size() - idx - 1);
    }

    int& operator[](std::size_t idx)
    {
        return NumVec.at(NumVec.size() - idx - 1);
    }

    void print() const
    {
        if(Sign)
            std::cout<<"-";
        for(int i = 0; i < NumVec.size(); ++i)
            std::cout<<NumVec.at(i);
        //for(auto i = NumVec.size() - 1; i >= 0; i--)
            //std::cout<<NumVec.at(i);
    }

    std::deque<int> NumVec;
    bool Sign;
};

Number mul(const Number& a, const Number& b)
{
    if(a.size() == 0 || b.size() == 0)
        return Number(0, false);

    Number c(a.size() + b.size() - 1, false);

    for(int i=0; i < a.size(); ++i)
        for(int j=0; j < b.size(); ++j)
        {
            auto multiplied = a[i]*b[j];
            c[i + j] += multiplied;
        }

    for(int cIdx = 0; cIdx < c.size(); ++cIdx)
        if(c[cIdx] >= numMax)
        {
            const auto carry = c[cIdx]/numMax;
            c[cIdx] -= carry*numMax;
            if(cIdx + 1 < c.size())
                c[cIdx+1] += carry;
            else
                c.NumVec.emplace_front(carry);
        }

    if(a.Sign != b.Sign)
        c.Sign = 1;
    else
        c.Sign = 0;
    return c;
}

Number add(const Number& a, const Number& b)
{
    Number c(a.size(), false);

    if(a.size() < b.size())
        return add(b, a);

    for(int i=0; i < a.size(); ++i)
    {
        if(i < b.size())
        {
            if(a.Sign != b.Sign)
            {
                c[i] = a[i] - b[i];
            }
            else
                c[i] = a[i] + b[i];
        }
        else
        {
                c[i] = a[i];
        }
    }

    bool isNegative = false;
    for(int i=0; i < c.size(); ++i)
    {
        if(c[i] >= numMax)
        {
            if(i + 1 < c.size())
                c[i+1] += 1;
            else
                c.NumVec.emplace_front(1);
            c[i] -= numMax;
        }

        if(c[i] < 0)
        {
            if(i + 1 < c.size())
            {
                c[i+1]-= 1;
            }
            else
                isNegative = true;
            c[i] = numMax - std::abs(c[i]);
        }
    }

    const auto cLastIdx = c.size() - 1;
    if(isNegative)
    {
        if(a.Sign == true && b.Sign == false)
            c.Sign = false;

        if(a.Sign == false && b.Sign == true)
            c.Sign = true;
    }
    if(c[cLastIdx] > numMax)
        c[cLastIdx] -= numMax;

    if(!isNegative)
        c.Sign = a.Sign;
    return c;
}

Number sub(Number a, Number b)
{
    b.Sign = ~b.Sign;
    return add(a, b);
}

//! let c = a*b = (a_high*10^5 + a_low) * (b_high*10^5 + b_low)
Number karatsuba(Number a,  Number b)
{
    if(a.size() <= 2 || b.size() <= 2)
    {
        return mul(a, b);
    }

    auto aLowSize = std::min(a.size()/2, b.size()/2);
    auto bLowSize= aLowSize;

    auto aHighSize = a.size()-aLowSize;
    auto bHighSize = b.size()-bLowSize;

    //! Prepare a
    Number aHigh(aHighSize, a.Sign);
    for(int i =0; i < aHighSize; ++i)
        aHigh.NumVec.at(i) = a.NumVec.at(i);

    Number aLow(a.size() - aHighSize, a.Sign);
    for(int i =0; i < aLowSize; ++i)
        aLow.NumVec.at(i) = a.NumVec.at(aHighSize + i);

    //! Prepare b
    Number bHigh(bHighSize, b.Sign);
    for(int i =0; i < bHighSize; ++i)
        bHigh.NumVec.at(i) = b.NumVec.at(i);

    Number bLow(b.size() - bHighSize, b.Sign);
    for(int i =0; i < bLowSize; ++i)
        bLow.NumVec.at(i) = b.NumVec.at(bHighSize + i);

    auto z0 = karatsuba(aLow, bLow);
    auto z2 = karatsuba(aHigh, bHigh);
    auto z1 = sub(sub(karatsuba(add(aHigh, aLow), add(bHigh, bLow)), z2), z0);

    for(int i =0; i<aLowSize*2; ++i)
        z2.NumVec.emplace_back(0);
    for(int i =0; i < aLowSize; ++i)
        z1.NumVec.emplace_back(0);
    
    return add(add(z2, z1), z0);
}

int main()
{
    Number a(2, false);
    a.NumVec = {1,2,3,4,5,6,7,8,9};
    Number b(2, false);
    b.NumVec = {1,2,3,4,5,4,3,2,1,2,3,4,5};

    const auto out = karatsuba(a, b);
    out.print();
    std::cout<<std::endl;

    return 0;
}