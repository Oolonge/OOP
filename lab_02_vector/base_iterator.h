#ifndef BASE_ITERATOR_H
#define BASE_ITERATOR_H

#include <memory>
#include <iostream>
#include <ctime>

#include "errors.h"
#include "concepts.h"

template<ComparableCopyableConstructible Type>
class BaseIterator
{
protected:
	BaseIterator() = default;

public:
	virtual ~BaseIterator() = 0;
	
		/* --------------- ALIASES --------------- */
	using value_type = Type;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
	
	const Type& operator *() const;
	const Type* operator ->() const;

	const Type &operator [](int index) const;
	operator bool() const;
	BaseIterator<Type>& operator =(const BaseIterator<Type>& iterator);

	bool operator <=(const BaseIterator<Type>& iterator) const;
	bool operator <(const BaseIterator<Type>& iterator) const;
	bool operator >=(const BaseIterator<Type>& iterator) const;
	bool operator >(const BaseIterator<Type>& iterator) const;
	bool operator ==(const BaseIterator<Type>& iterator) const;
	bool operator !=(const BaseIterator<Type>& iterator) const;

protected:
	Type* get_cur_ptr() const;
	void check_object(int) const;   // проверка объекта на null
    void check_validity(int) const; // проверака на валидность индекса

	size_t index;
    size_t size;

	std::weak_ptr<Type[]> weakPtr;
};

template<ComparableCopyableConstructible Type>
BaseIterator<Type>::~BaseIterator() {}

#include "base_iterator.hpp"

#endif // BASE_ITERATOR_H
