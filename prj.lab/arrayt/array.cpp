#include "arrayt.hpp"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <algorithm> 

template<class T>
ArrayT<T>::ArrayT(const ArrayT<T>& src)
    : capacity_(src.size_)
    , size_(capacity_) {
    data_.reset(new T[capacity_]);
    std::copy(src.data_.get(), src.data_.get() + size_, data_.get());
}

template<class T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size)
    : capacity_(size)
    , size_(size) {
    if (size_ <= 0) {
        throw std::invalid_argument("ArrayT::ArrayT - non positive size");
    }
    data_.reset(new T[size]);
}

template<class T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs) {
    if (this != &rhs) {
        Resize(rhs.size_);
        std::copy(rhs.data_.get(), rhs.data_.get() + size_, data_.get());
    }
    return *this;
}

template<class T>
T& ArrayT<T>::operator[](const std::ptrdiff_t idx) {
    CheckIndex(idx);
    return data_[idx];
}

template<class T>
const T& ArrayT<T>::operator[](const std::ptrdiff_t idx) const {
    CheckIndex(idx);
    return data_[idx];
}

template<class T>
void ArrayT<T>::Resize(const std::ptrdiff_t size) {
    if (size < 0) {
        throw std::invalid_argument("New size must be bigger than -1");
    }
    if (capacity_ < size) {
        add_capacity(size * 2);
    }
    size_ = size;
}

template<class T>
void ArrayT<T>::Insert(const std::ptrdiff_t idx, const T& val) {
    if (idx > size_ || idx < 0) {
        throw std::out_of_range("Index out of bounds");
    }
    if (capacity_ <= size_ + 1) {
        add_capacity(std::max(capacity_ * 2, 1));
    }
    for (std::ptrdiff_t i = size_; i > idx; i--) {
        data_[i] = data_[i - 1];
    }
    data_[idx] = val;
    ++size_;
}

template<class T>
void ArrayT<T>::Remove(const std::ptrdiff_t idx) {
    CheckIndex(idx);
    for (std::ptrdiff_t i = idx; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    --size_;
}

template<class T>
void ArrayT<T>::CheckIndex(const std::ptrdiff_t idx) const {
    if (idx >= size_ || idx < 0) {
        throw std::out_of_range("Index out of bounds");
    }
}

template<class T>
void ArrayT<T>::add_capacity(const std::ptrdiff_t new_capacity) {
    if (new_capacity <= capacity_) return;

    T* new_data = new T[new_capacity];
    if (data_) {
        std::copy(data_.get(), data_.get() + capacity_, new_data);
    }
    data_.reset(new_data);
    capacity_ = new_capacity;
}

