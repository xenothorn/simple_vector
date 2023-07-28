#pragma once

#include <cassert>
#include <initializer_list>
#include <stddef.h>
#include <stdexcept>

#include <iostream>

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;

    void ZeroInit()
    {
        size_ = 0;
        capacity_ = 0;
        items_ = nullptr;
    }

    SimpleVector() noexcept = default;

    // Создаёт вектор из size элементов, инициализированных значением по умолчанию
    explicit SimpleVector(size_t size) {
        // Напишите тело конструктора самостоятельно
        if (size == 0)
        {
            ZeroInit();
        }
        else
        {
            SimpleVector tmp;
            tmp.items_ = new Type[size];
            tmp.capacity_ = size;
            tmp.size_ = size;
            std::fill(tmp.begin(), tmp.end(), Type{});
            swap(tmp);
        }

    }

    // Создаёт вектор из size элементов, инициализированных значением value
    SimpleVector(size_t size, const Type& value) {
        // Напишите тело конструктора самостоятельно
        if (size == 0)
        {
            ZeroInit();
        }
        else
        {
            SimpleVector tmp;
            tmp.items_ = new Type[size];
            tmp.capacity_ = size;
            tmp.size_ = size;
            std::fill(tmp.begin(), tmp.end(), value);
            swap(tmp);
        }
    }

    SimpleVector(const SimpleVector& other)
    {
        if (other.GetSize() == 0)
        {
            ZeroInit();
        }
        else
        {
            SimpleVector tmp(other.GetSize());
            std::copy(other.begin(), other.end(), tmp.begin());
            swap(tmp);
        }
    }

    // Создаёт вектор из std::initializer_list
    SimpleVector(std::initializer_list<Type> init) {
        if (init.size() == 0)
        {
            ZeroInit();
        }
        else
        {
            SimpleVector tmp(init.size());
            std::copy(init.begin(), init.end(), tmp.begin());
            swap(tmp);
        }
    }

    ~SimpleVector()
    {
        delete [] items_;
    }

    SimpleVector& operator=(const SimpleVector& rhs)
    {
        SimpleVector tmp(rhs);
        swap(tmp);
        return *this;
    }

    // Возвращает количество элементов в массиве
    size_t GetSize() const noexcept {
        return size_;
    }

    // Возвращает вместимость массива
    size_t GetCapacity() const noexcept {
        return capacity_;
    }

    // Сообщает, пустой ли массив
    bool IsEmpty() const noexcept {
        return (size_ == 0);
    }

    // Возвращает ссылку на элемент с индексом index
    Type& operator[](size_t index) noexcept {
        return *(this->items_+index);
    }

    // Возвращает константную ссылку на элемент с индексом index
    const Type& operator[](size_t index) const noexcept {
        return *(this->items_+index);
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    Type& At(size_t index) {
        if (index >= size_) throw std::out_of_range("out vector range");
        else
            return (items_[index]);
    }

    // Возвращает константную ссылку на элемент с индексом index
    // Выбрасывает исключение std::out_of_range, если index >= size
    const Type& At(size_t index) const {
        if (index >= size_) throw std::out_of_range("out vector range");
        else
            return (items_[index]);
    }

    // Обнуляет размер массива, не изменяя его вместимость
    void Clear() noexcept {
        size_ = 0;
    }

    // Изменяет размер массива.
    // При увеличении размера новые элементы получают значение по умолчанию для типа Type
    void Resize(size_t new_size) {
        if (new_size <= size_) size_ = new_size;
        else if (new_size <= capacity_)
        {
            auto it = end();
            size_ = new_size;
            std::fill(it, end(), Type{});
        }
        else
        {
            SimpleVector tmp(new_size);
            std::fill(tmp.begin(), tmp.end(), Type{});
            std::copy(begin(), end(), tmp.begin());
            swap(tmp);
        }
    }

    void PushBack(const Type& value)
    {
        if (items_ == nullptr)
        {
            SimpleVector tmp(1,value);
            swap(tmp);
        }
        else
        {
            if (size_ < capacity_)
            {
                items_[size_] = value;
                ++size_;
            }
            else
            {
                SimpleVector tmp(capacity_ * 2);
                std::copy(begin(), end(), tmp.begin());
                tmp[size_] = value;
                tmp.size_ = ++size_;
                swap(tmp);
            }
        }
    }

    void PopBack() noexcept
    {
        if (size_ > 0)
        {
            --size_;
        }
    }

    Iterator Insert(ConstIterator pos, const Type& value)
    {
        size_t d = pos - begin();
        size_t e = end() - begin();
        if (size_ < capacity_)
        {
            ++size_;
            std::copy_backward(begin()+d, begin()+e, this->end());
            *(begin() + d) = value;
        }
        else
        {
            SimpleVector tmp(capacity_ * 2);
            std::copy(begin(), end(), tmp.begin());
            tmp.size_ = size_;
            swap(tmp);
            ++size_;
            std::copy_backward(begin()+d, begin()+e, this->end());
            *(begin() + d) = value;
        }
        return (begin()+d);
    }

    Iterator Erase(ConstIterator pos)
    {
        if (size_ > 0)
        {
            auto beg = pos - begin();
            std::copy(begin()+beg+1, end(), begin()+beg);
            --size_;
            return begin() + beg + 1;
        }
        return end();
    }


    void swap(SimpleVector& v) noexcept {
        std::swap(v.items_, items_);
        std::swap(v.size_, size_);
        std::swap(v.capacity_, capacity_);
    }

    // Возвращает итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator begin() noexcept {
        // Напишите тело самостоятельно
        if (size_ == 0) return nullptr;
        else return items_;
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    Iterator end() noexcept {
        if (size_ == 0) return nullptr;
        else return (items_ + size_);
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator begin() const noexcept {
        if (size_ == 0) return nullptr;
        else return items_;
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator end() const noexcept {
        if (size_ == 0) return nullptr;
        else
            return (items_ + size_);
    }

    // Возвращает константный итератор на начало массива
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cbegin() const noexcept {
        return begin();
    }

    // Возвращает итератор на элемент, следующий за последним
    // Для пустого массива может быть равен (или не равен) nullptr
    ConstIterator cend() const noexcept {
        return end();
    }



private:
    Type* items_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename T>
void swap(SimpleVector<T> v, SimpleVector<T> t) noexcept {
    std::swap(v, t);
}

template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return (std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return (!(lhs == rhs));
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs < rhs) && (lhs != rhs);
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs < rhs);
}
