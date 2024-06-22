#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H

#include <memory>
#include <iostream>
#include <ctime>

#include "base_iterator.h"
#include "errors.h"
#include "concepts.h"
#include "iterator.h"

template<ComparableCopyableConstructible Type>
class Vector;

template<ComparableCopyableConstructible Type>
class ConstInputIterator: public BaseIterator<Type>
{
public:
	
	/* --------------- ALIASES --------------- */
	using value_type = Type;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

	ConstInputIterator(const ConstInputIterator<Type>&);
	ConstInputIterator(const InputIterator<Type>&); //here
	ConstInputIterator(const Vector<Type>&);

	ConstInputIterator<Type>& operator +=(int number);
	ConstInputIterator<Type>& operator ++();     // префиксный инкремент
	ConstInputIterator<Type>  operator ++(int);  // постфиксный инкремент
	ConstInputIterator<Type>  operator + (int number) const;

	ConstInputIterator<Type>& operator -=(int number);
	ConstInputIterator<Type>& operator --();    // префиксный декремент
	ConstInputIterator<Type>  operator --(int); // постфиксный декремент
	ConstInputIterator<Type>  operator - (int number) const;
};

#include "const_iterator.hpp"

#endif // CONST_ITERATOR_H
