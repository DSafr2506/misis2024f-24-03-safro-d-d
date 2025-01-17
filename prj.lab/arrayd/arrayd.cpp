// 2024 by Polevoi Dmitry under Unlicense

#include <arrayd/arrayd.hpp>

#include <cstring>
#include <stdexcept>
#include <cstddef>
#include <memory>
#include <stdexcept>

ArrayD::ArrayD(const ArrayD& src)
    : capacity_(src.size_)
    , size_(capacity_)
    , data_(new double[size_]) {
    std::copy(src.data_, src.data_ + size_, data_);
}


ArrayD::ArrayD(const std::ptrdiff_t size)
    : capacity_(size)
    , size_(size) {
    if (size_ <= 0) {
        throw std::invalid_argument("ArrayD::ArrayD - non positive size");
    }
    data_ = new double[capacity_] {0.0};
}

ArrayD::~ArrayD() {
    delete[] data_;
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
    if (this != &rhs) {
        Resize(rhs.size_);
        std::copy(rhs.data_,rhs.data_ + size_, data_);
    }
    return *this;
}

void ArrayD::Resize(const std::ptrdiff_t size) {
    if (size < 0) {
        throw std::invalid_argument("ArrayD::Resize - non positive size");
    }
    if (capacity_ < size) {
        auto data = new double[size] {0.0};
        if (0 < size_) {
            std::copy(data_, data_+ size_, data);
        }
        std::swap(data_, data);
        delete[] data;
        capacity_ = size;
    }
    else {
        if (size_ < size) {
            std::memset(data_ + size_, 0, (size - size_) * sizeof(*data_));
        }
    }
    size_ = size;
}


double& ArrayD::operator[](const std::ptrdiff_t idx) {
    if (idx < 0 || size_ <= idx) {
        throw std::invalid_argument("ArrayD::operator[] - invalid index");
    }
    return *(data_ + idx);
}

double ArrayD::operator[](const std::ptrdiff_t idx) const {
    if (idx < 0 || size_ <= idx) {
        throw std::invalid_argument("ArrayD::operator[] - invalid index");
    }
    return data_[idx];
}

void ArrayD::Insert(const std::ptrdiff_t idx, const double val) {
    if (idx < 0 || size_ < idx) {
        throw std::invalid_argument("ArrayD::Insert - invalid index");
    }
    Resize(size_ + 1);
    if (idx != Size() - 1) {
        std::copy_backward(data_ + idx,
            data_ + size_ - 1, data_ + size_);
    }
    data_[idx] = val;
}


void ArrayD::Remove(const std::ptrdiff_t idx) {
    if (idx < 0 || size_ <= idx) {
        throw std::invalid_argument("ArrayD::operator[] - invalid index");
    }
    if (idx != size_ - 1) {
        // óäàëÿåì ÍÅ â êîíöå
        std::copy(data_ + idx + 1,
            data_ + size_, data_ + idx);
    }
    Resize(size_ - 1);
}
