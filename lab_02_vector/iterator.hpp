#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator.h"

// конструктор копирования итератора
template<ComparableCopyableConstructible Type>
InputIterator<Type>::InputIterator(const InputIterator<Type>& iterator)
{
    this->weakPtr = iterator.weakPtr;
    this->index = iterator.index;
    this->size = iterator.size;
}

template<ComparableCopyableConstructible Type>
InputIterator<Type>::InputIterator(const Vector<Type>& vector)
{
    this->index = 0;
    this->size = vector.getSize();
    this->weakPtr = vector.values;
}

// операторы разыменования
template<ComparableCopyableConstructible Type>
Type& InputIterator<Type>::operator *()
{
    this->check_object(__LINE__);
    this->check_validity(__LINE__);

    return *this->get_cur_ptr();
}

template<ComparableCopyableConstructible Type>
Type* InputIterator<Type>::operator ->()
{
    this->check_object(__LINE__);
    this->check_validity(__LINE__);

    return this->get_cur_ptr();
}

template<ComparableCopyableConstructible Type>
Type &InputIterator<Type>::operator [](int index)
{
    return *(this->operator+(index));
}

// операции сложения
template<ComparableCopyableConstructible Type>
InputIterator<Type>& InputIterator<Type>::operator +=(int number)
{
    this->check_object(__LINE__);
    this->index += number;

    return *this;
}

template<ComparableCopyableConstructible Type>
InputIterator<Type> InputIterator<Type>::operator +(int number) const
{
    this->check_object(__LINE__);
    InputIterator<Type> iterator(*this);
    if (this->index + number <= this->size)
        iterator += number;

    return iterator;
}

template<ComparableCopyableConstructible Type>
InputIterator<Type> InputIterator<Type>::operator ++(int)
{
    this->check_object(__LINE__);
    if (this->index < this->size)
		this->index++;
        // ++(*this);

    return *this;
}

template<ComparableCopyableConstructible Type>
InputIterator<Type>& InputIterator<Type>::operator ++()
{
    this->check_object(__LINE__);
    if (this->index < this->size)
        ++(this->index);

    return *this;
}

// операции вычитания
template<ComparableCopyableConstructible Type>
InputIterator<Type>& InputIterator<Type>::operator -=(int number)
{
    this->check_object(__LINE__);
    if (this->index >= number - 1)
        this->index -= number;

    return *this;
}

template<ComparableCopyableConstructible Type>
InputIterator<Type> InputIterator<Type>::operator -(int number) const
{
    this->check_object(__LINE__);

    InputIterator<Type> iterator(*this);
    if (this->index >= number - 1)
        iterator -= number;

    return iterator;
}

template<ComparableCopyableConstructible Type>
InputIterator<Type> InputIterator<Type>::operator --(int)
{
    this->check_object(__LINE__);
    if (this->index >= 0)
        --(*this);

    return *this;
}

template<ComparableCopyableConstructible Type>
InputIterator<Type>& InputIterator<Type>::operator --()
{
    this->check_object(__LINE__);
    if (this->index >= 0)
        --(this->index);

    return *this;
}

#endif // ITERATOR_HPP
