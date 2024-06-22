#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include "const_iterator.h"

// конструктор копирования итератора
template<ComparableCopyableConstructible Type>
ConstInputIterator<Type>::ConstInputIterator(const ConstInputIterator<Type>& iterator)
{
    this->weakPtr = iterator.weakPtr;
    this->index = iterator.index;
    this->size = iterator.size;
}

// преобразование обычного в константный
template<ComparableCopyableConstructible Type>
ConstInputIterator<Type>::ConstInputIterator(const InputIterator<Type>& iterator)
{
    this->weakPtr = iterator.weakPtr;
    this->index = iterator.index;
    this->size = iterator.size;
}

template<ComparableCopyableConstructible Type>
ConstInputIterator<Type>::ConstInputIterator(const Vector<Type>& vector)
{
    this->index = 0;
    this->size = vector.getSize();
    this->weakPtr = vector.values;
}

// операции сложения
template<ComparableCopyableConstructible Type>
ConstInputIterator<Type>& ConstInputIterator<Type>::operator +=(int number)
{
    this->check_object(__LINE__);
    this->index += number;

    return *this;
}

template<ComparableCopyableConstructible Type>
ConstInputIterator<Type> ConstInputIterator<Type>::operator +(int number) const
{
    this->check_object(__LINE__);
    ConstInputIterator<Type> iterator(*this);
    if (this->index + number <= this->size)
        iterator += number;

    return iterator;
}

template<ComparableCopyableConstructible Type>
ConstInputIterator<Type> ConstInputIterator<Type>::operator ++(int)
{
    this->check_object(__LINE__);
    if (this->index < this->size)
		this->index++;
        // ++(*this);

    return *this;
}

template<ComparableCopyableConstructible Type>
ConstInputIterator<Type>& ConstInputIterator<Type>::operator ++()
{
    this->check_object(__LINE__);
    if (this->index < this->size)
        ++this->index;

    return *this;
}

// операции вычитания
template<ComparableCopyableConstructible Type>
ConstInputIterator<Type>& ConstInputIterator<Type>::operator -=(int number)
{
    this->check_object(__LINE__);
    if (this->index >= number - 1)
        this->index -= number;

    return *this;
}

template<ComparableCopyableConstructible Type>
ConstInputIterator<Type> ConstInputIterator<Type>::operator -(int number) const
{
    this->check_object(__LINE__);

    ConstInputIterator<Type> iterator(*this);
    if (this->index >= number - 1)
        iterator -= number;

    return iterator;
}

template<ComparableCopyableConstructible Type>
ConstInputIterator<Type> ConstInputIterator<Type>::operator --(int)
{
    this->check_object(__LINE__);
    if (this->index >= 0)
        --(*this);

    return *this;
}

template<ComparableCopyableConstructible Type>
ConstInputIterator<Type>& ConstInputIterator<Type>::operator --()
{
    this->check_object(__LINE__);
    if (this->index >= 0)
        --(this->index);

    return *this;
}

#endif // CONST_ITERATOR_HPP
