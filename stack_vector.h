#pragma once

#include <array>
#include <stdexcept>
#include <iostream>

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector() = default;
    explicit StackVector(size_t n) 
    {
        if (n > N) 
        {
            throw std::invalid_argument("out of range");
        }
        else
        {
            size_ = n;
        }
    }


    T& operator[](size_t index)
    {
        return body_[index];
    }

    const T& operator[](size_t index) const
    {
        return body_[index];   
    }

    typename std::array<T,N>::iterator begin()          {   return body_;           }
    typename std::array<T,N>::iterator end()            {   return (body_ + size_); }
    typename std::array<T,N>::const_iterator begin() const    {   return body_;           }
    typename std::array<T,N>::const_iterator end() const      {   return (body_ + size_); }

    size_t Size() const
    {
        return size_;
    }
    
    size_t Capacity() const
    {
        return N;
    }

    void PushBack(const T& value)
    {
        if (size_ == N) throw std::overflow_error("out of range");
        body_[size_] = value;
        ++size_;
    }
    
    T PopBack()
    {
        if (size_ == 0) throw std::underflow_error("out of range");
        --size_;
        return body_[size_];
    }


private:
    T body_[N] = {0};
    size_t size_ = 0;
};






