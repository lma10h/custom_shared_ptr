#pragma once

#include <utility>

template<class T>
class CustomSharedPtr
{
public:
    CustomSharedPtr() noexcept;
    CustomSharedPtr(T *ptr) noexcept;
    CustomSharedPtr(const CustomSharedPtr<T> &ptr) noexcept;
    CustomSharedPtr(CustomSharedPtr<T> &&ptr) noexcept;
    ~CustomSharedPtr() noexcept;

    CustomSharedPtr &operator=(const CustomSharedPtr &ptr) noexcept;
    CustomSharedPtr &operator=(CustomSharedPtr &&ptr) noexcept;

    T &operator*() const noexcept;
    T *operator->() const noexcept;

    void reset(T *ptr = nullptr) noexcept;

    T *get() const noexcept;

    long use_count() const noexcept;

private:
    int *count;
    T *value;
};

template<class T>
CustomSharedPtr<T>::CustomSharedPtr() noexcept
    : count(nullptr)
    , value(nullptr)
{
}

template<class T>
CustomSharedPtr<T>::CustomSharedPtr(T *ptr) noexcept
    : count(new int(1))
    , value(ptr)
{
}

template<class T>
CustomSharedPtr<T>::CustomSharedPtr(const CustomSharedPtr<T> &ptr) noexcept
    : count(ptr.count)
    , value(ptr.value)
{
    if (count) {
        ++(*count);
    }
}

template<class T>
CustomSharedPtr<T>::CustomSharedPtr(CustomSharedPtr<T> &&ptr) noexcept
    : count(ptr.count)
    , value(ptr.value)
{
}

template<class T>
CustomSharedPtr<T>::~CustomSharedPtr() noexcept
{
    if (count && *count > 0) {
        --(*count);
    }

    if (count == 0) {
        delete value;
        value = nullptr;
    }
}

template<class T>
CustomSharedPtr<T> &CustomSharedPtr<T>::operator=(const CustomSharedPtr &ptr) noexcept
{
    *count = ptr.use_count() + 1;
    value = ptr.get();

    return this;
}

template<class T>
CustomSharedPtr<T> &CustomSharedPtr<T>::operator=(CustomSharedPtr &&ptr) noexcept
{
    *count = ptr.use_count();
    value = ptr.get();

    return this;
}

template<class T>
T &CustomSharedPtr<T>::operator*() const noexcept
{
    return *value;
}

template<class T>
T *CustomSharedPtr<T>::operator->() const noexcept
{
    return value;
}

template<class T>
void CustomSharedPtr<T>::reset(T *ptr) noexcept
{
    if (ptr == nullptr) {
        if (count && (*count) > 0) {
            --(*count);
        }

        if (count && *count == 0 && value) {
            delete value;
            value = nullptr;
        }
    } else {
        count = new int(1);
        value = ptr;
    }
}

template<class T>
T *CustomSharedPtr<T>::get() const noexcept
{
    return value;
}

template<class T>
long CustomSharedPtr<T>::use_count() const noexcept
{
    return count ? *count : 0;
}
