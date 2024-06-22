#ifndef VECTOR_H
#define VECTOR_H

#include <stdarg.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>

#include "base_vector.h"
#include "iterator.hpp"
#include "const_iterator.h"
#include "errors.h"
#include "concepts.h"

using namespace std;

template<ComparableCopyableConstructible Type>
class Vector: public BaseVector
{
public:
	/* --------------- ALIASES --------------- */
	using value_type = Type;
	using size_type = size_t;
	using iterator = InputIterator<Type>;
	using const_iterator = ConstInputIterator<Type>;

	static_assert(std::input_iterator<iterator>);
    static_assert(std::input_iterator<const_iterator>);

	/* ----------- FRIEND CLASSES ------------ */
    friend class InputIterator<Type>;
    friend class ConstInputIterator<Type>;

	/* ---------------- CONSTRUCTORS ----------------- */
    Vector();
    explicit Vector(size_type len);
    Vector(size_type len, const Type* array); //changed 
    Vector(size_type len, Type vector, ...);
    Vector(initializer_list<Type> args);
    explicit Vector(const Vector<Type> &vector);
    Vector(Vector<Type>&& vector) noexcept;

	// на основе вектора
	template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    explicit Vector(const Vector<U> &vector);

	// на основе любого контейнера
	template<Container U>
	requires ConvertibleTo<typename U::value_type, Type>
	Vector(U&& container);

	// на основе двух итераторов
	template<IsInputIterator Iter>
	requires ConvertibleTo<typename Iter::value_type, Type>
	Vector(Iter first, Iter last);

	virtual ~Vector();
	
	/* -------------- OPERATORS --------------- */
    Vector<Type> &operator =(const Vector<Type> &vector);
    Vector<Type> &operator =(initializer_list<Type> args);
    Vector<Type> &operator =(Vector<Type> &&vector);

    bool setItem (size_type index, const Type &item);
          Type &getItem(size_type index);
    const Type &getItem(size_type index) const;

          Type &operator [](size_type index);
    const Type &operator [](size_type index) const;

    double getLength() const;
    size_type getSize() const noexcept override;
    bool isEmpty() const noexcept override;

    bool isZero() const; // проверка на нулевой вектор
    bool isSingle() const; // проверка единичный вектор

    bool isCollinear(const Vector<Type>&) const;
    bool isOrthgonal(const Vector<Type> &) const;

    Vector<Type> getSingle() const; // нормирование вектора


    // Сумма вектора и числа
    template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) operator+(const U &) const;
    Vector<Type>  &operator +=(const Type &);

    template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) sumNum(const U &) const;
    Vector<Type>  &sumNumEqual(const Type &);

    // Сумма двух векторов
    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) operator +(const Vector<U> &) const;
    Vector<Type>  &operator +=(const Vector<Type> &);

    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) sum(const Vector<U> &) const;
    Vector<Type>  &sumEqual(const Vector<Type> &);

    // Разность вектора и числа
    template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) operator -(const U &) const;
    Vector<Type>  &operator -=(const Type &);

    template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) subNum(const U &) const;
    Vector<Type>  &subNumEqual(const Type &);

    // Разность двух векторов
    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) operator -(const Vector<U> &) const;
    Vector<Type>  &operator -=(const Vector<Type> &);
    
	template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) sub(const Vector<U> &) const;
    Vector<Type>  &subEqual(const Vector<Type> &);
    Vector<Type> operator -();
    Vector<Type> reverse();

    // Умножение на число
    template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) operator *(const U &number) const;
    Vector<Type> &operator *=(const Type &number);

	template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) mulNum(const U &number) const;
    Vector<Type> &mulNumEqual(const Type &number);

    //Умножение элементов двух веткоров
    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) operator ^(const Vector<U> &) const;
    Vector<Type> &operator ^=(const Vector<Type>&);

    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) mulElems(const Vector<U> &) const;
    Vector<Type>  &mulElemsEqual(const Vector<Type> &);

    // Скалярное произведение
    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    auto operator *(const Vector<U> &) const;
    Type  operator *=(const Vector<Type> &);

    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    auto scalarMul(const Vector<U> &) const;
    Type  scalarMulEqual(const Vector<Type> &);

    // Векторное произведение
    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) operator &(const Vector<U> &) const;
     Vector<Type> &operator &=(const Vector<Type> &);

    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) vectorMul(const Vector<U> &) const;
     Vector<Type> &vectorMulEqual(const Vector<Type> &);

    // Деление вектора на число
    template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) operator /(const U& number) const;
    Vector<Type>  &operator /=(const Type& number);

	template<typename U>
	requires std::convertible_to<U, Type>
    decltype(auto) divNum(const U&) const;
    Vector<Type>  &divNumEqual(const Type& number);

    // Деление двух векторов
    template<ComparableCopyableConstructible U>
	requires std::convertible_to<U, Type> 
    decltype(auto) operator /(const Vector<U>&) const;
    Vector<Type>  &operator /=(const Vector<Type>&);

    // Логические операции
    bool operator ==(const Vector<Type> &) const;
    bool operator !=(const Vector<Type> &) const;

    // угол между векторами
    double angleBetweenVectors(const Vector<Type>&) const;

    iterator begin() noexcept;
    iterator end() noexcept;

	const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

protected:
    Type sumValue();
    void allocNewVectorMem(size_type amount);
private:
    shared_ptr<Type[]> values; // Type[] - передача болле сложных типов (классов, объектов)
};

// создан для быстрого вывода вектора
template<ComparableCopyableConstructible Type>
ostream& operator <<(ostream& os, const Vector<Type>& vec)
{
    InputIterator<Type> iter(vec);
    os << '(';
    for (; iter; iter++)
        if (iter + 1)
            os << *iter <<  ", ";
        else
            os << *iter;
    os << ')';

    return os;
}

#endif // VECTOR_H
