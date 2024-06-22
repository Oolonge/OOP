#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP

#include "base_iterator.h"

// операторы разыменования
template<ComparableCopyableConstructible Type>
const Type& BaseIterator<Type>::operator *() const
{
    this->check_object(__LINE__);
    this->check_validity(__LINE__);

    return *this->get_cur_ptr();
}

template<ComparableCopyableConstructible Type>
const Type* BaseIterator<Type>::operator ->() const
{
    this->check_object(__LINE__);
    this->check_validity(__LINE__);

    return this->get_cur_ptr();
}

template<ComparableCopyableConstructible Type>
const Type &BaseIterator<Type>::operator [](int index) const
{
    return *(this->operator+(index));
}

// // операция присваивания
template<ComparableCopyableConstructible Type>
BaseIterator<Type>& BaseIterator<Type>::operator =(const BaseIterator<Type>& iterator)
{
    iterator.check_object(__LINE__);

    this->weakPtr = iterator.weakPtr;
    this->index = iterator.index;
    this->size = iterator.size;

    return *this;
}

// логические операции
template<ComparableCopyableConstructible Type>
bool BaseIterator<Type>::operator <=(const BaseIterator<Type>& iterator) const
{
    check_object(__LINE__);

    return weakPtr <= iterator.weakPtr;
}

template<ComparableCopyableConstructible Type>
bool BaseIterator<Type>::operator <(const BaseIterator<Type>& iterator) const
{
    check_object(__LINE__);

    return weakPtr < iterator.weakPtr;
}

template<ComparableCopyableConstructible Type>
bool BaseIterator<Type>::operator >=(const BaseIterator<Type>& iterator) const
{
    check_object(__LINE__);

    return weakPtr >= iterator.weakPtr;
}

template<ComparableCopyableConstructible Type>
bool BaseIterator<Type>::operator >(const BaseIterator<Type>& iterator) const
{
    check_object(__LINE__);

    return weakPtr > iterator.weakPtr;
}

template<ComparableCopyableConstructible Type>
bool BaseIterator<Type>::operator ==(const BaseIterator<Type>& iterator) const
{
    check_object(__LINE__);

    return weakPtr == iterator.weakPtr;
}

template<ComparableCopyableConstructible Type>
bool BaseIterator<Type>::operator !=(const BaseIterator<Type>& iterator) const
{
    check_object(__LINE__);

    return this->weakPtr != iterator.weakPtr;
}

// проверки работы с объектом и итератором
template<ComparableCopyableConstructible Type>
void BaseIterator<Type>::check_object(int line) const
{
    if (this->weakPtr.expired())
    {
        time_t t_time = time(NULL);
        throw DeletedObject(__FILE__, typeid(*this).name(), line, ctime(&t_time));
    }
}

template<ComparableCopyableConstructible Type>
void BaseIterator<Type>::check_validity(int line) const {
    if (index < 0 || index >= size) //
    {
        time_t currentTime = time(NULL);
        throw InvalidIterator(__FILE__, typeid(*this).name(), line, ctime(&currentTime));
    }
}

// достать текущий указатель на объект
template<ComparableCopyableConstructible Type>
Type* BaseIterator<Type>::get_cur_ptr() const
{
    std::shared_ptr<Type[]> copy_ptr = this->weakPtr.lock();
    return copy_ptr.get() + this->index;
}

template<ComparableCopyableConstructible Type>
BaseIterator<Type>::operator bool() const
{
    check_object(__LINE__);

    if (this->index >= this->size || this->index < 0 || this->size == 0)
        return false;
	return true;
	
}


#endif // BASE_ITERATOR_HPP