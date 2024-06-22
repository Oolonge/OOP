#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>
#include <iostream>
#include <ctime>

#include "base_iterator.h"
#include "errors.h"
#include "concepts.h"

template<ComparableCopyableConstructible Type>
class Vector;

template<ComparableCopyableConstructible Type>
class InputIterator: public BaseIterator<Type>
{
public:

	/* --------------- ALIASES --------------- */
	using value_type = Type;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    InputIterator(const InputIterator<Type>&);
    InputIterator(const Vector<Type>&);

	Type& operator *();
	Type* operator ->();
	Type &operator [](int index);

	InputIterator<Type>& operator +=(int number);
   	InputIterator<Type>& operator ++();     // префиксный инкремент
   	InputIterator<Type>  operator ++(int);  // постфиксный инкремент
   	InputIterator<Type>  operator + (int number) const;

   	InputIterator<Type>& operator -=(int number);
   	InputIterator<Type>& operator --();    
   	InputIterator<Type>  operator --(int); 
   	InputIterator<Type>  operator - (int number) const;

};

#include "iterator.hpp"

#endif // ITERATOR_H
