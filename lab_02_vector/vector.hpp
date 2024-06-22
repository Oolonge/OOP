#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector.h"

// Конструктор инициализации.
template<ComparableCopyableConstructible Type>
Vector<Type>::Vector()
{
    size = 0;
    allocNewVectorMem(size);
}

// Конструктор вектора нужной длины
template<ComparableCopyableConstructible Type>
Vector<Type>::Vector(size_t len)
{
    time_t curTime = time(NULL);
    if (len < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime)); // возможно создать другое иск   лючение

    size = len;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> iterator(*this);
    for (; iterator; iterator++)
        *iterator = 0;
}

// Конструктор на основе массива.
template<ComparableCopyableConstructible Type>
Vector<Type>::Vector(size_t len, const Type* array)
{
    time_t curTime = time(NULL);
    if (len <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (!array)
        throw InvalidCopyArrayPointer(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    size = len;
    allocNewVectorMem(size);
    if(!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> iterator(*this);
    for (size_t i = 0; iterator; i++, iterator++)
        *iterator = array[i];
}

// Конструктор на основе элементов.
template<ComparableCopyableConstructible Type>
Vector<Type>::Vector(size_t len, Type vector, ...)
{
    time_t currentTime = time(NULL);
    if (len < 1)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    size = len;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iterator(*this);
    va_list var;
    va_start(var, vector);
    for (; iterator; iterator++)
    {
        *iterator = vector;
        vector = va_arg(var, Type);
    }
    va_end(var);
}

// Конструктор с инициализацией.
template<ComparableCopyableConstructible Type>
Vector<Type>::Vector(std::initializer_list<Type> args)
{
    // std::cout << "Vector<Type>::Vector(std::initializer_list<Type> args)" << endl;
    if (args.size() == 0)
    {
        Vector();
        return;
    }

    time_t currentTime = time(NULL);
    size = size_t(args.size());
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iterator(*this);
    for (auto &currentItem : args)
    {
        *iterator = currentItem;
        iterator++;
    }
}

// Конструктор от вектора.
template<ComparableCopyableConstructible Type>
Vector<Type>::Vector(const Vector<Type> &vector)
{
    time_t currentTime = time(NULL);
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iteratorTo(*this);
    InputIterator<Type> iteratorFrom(vector);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;
}

template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
Vector<Type>::Vector(const Vector<U> &vector)
{
    time_t currentTime = time(NULL);
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iteratorTo(*this);
    InputIterator<U> iteratorFrom(vector);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;	
}

// Конструктор переноса
template<ComparableCopyableConstructible Type>
Vector<Type>:: Vector(Vector<Type> &&vector) noexcept
{
    size = vector.size;
    allocNewVectorMem(size);
    values = vector.values;
    vector.values = nullptr;
}

template<ComparableCopyableConstructible Type>
template<Container U>
	requires ConvertibleTo<typename U::value_type, Type>
Vector<Type>::Vector(U&& container)
{
	if (container.size() == 0)
	{
		Vector();
		return;
	}

	time_t currentTime = time(NULL);
    size = size_t(container.size());
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

	InputIterator<Type> iteratorTo(*this);
    InputIterator<U> iteratorFrom(container);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;
}

template<ComparableCopyableConstructible Type>
template<IsInputIterator Iter>
	requires ConvertibleTo<typename Iter::value_type, Type>
Vector<Type>::Vector(Iter first, Iter last)
{
	if (first >= last)
	{
		Vector();
		return;
	}
	time_t currentTime = time(NULL);
	size = size_t(last - first);
	allocNewVectorMem(size);
	if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

	InputIterator<Type> iteratorTo(first), iteratorFrom(last);
	for (; iteratorTo; iteratorFrom++, iteratorTo++)
		*iteratorTo = *iteratorFrom;
}

// Деструктор.
template<ComparableCopyableConstructible Type>
Vector<Type>::~Vector()
{
    if (values)
        values.reset();
}

// Операторы присваивания
template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator =(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> iteratorTo(*this);
    InputIterator<Type> iteratorFrom(vector);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;

    return *this;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator =(initializer_list<Type> args)
{
    time_t currentTime = time(NULL);
    size = size_t(args.size());
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iterator(*this);
    for (auto &currentItem : args)
    {
        *iterator = currentItem;
        iterator++;
    }

    return *this;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator =(Vector<Type> &&vector)
{
    time_t curTime = time(NULL);
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    values = vector.values;
    vector.values = nullptr;

    return *this;
}

// Получение элемента по индексу.
template<ComparableCopyableConstructible Type>
Type &Vector<Type>::getItem(size_t index) {
    time_t currentTime = time(NULL);
    if (index < 0 || index >= size)
        throw IndexVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iterator(*this);
    for (size_t i = 0; i < index; i++, iterator++);

    return *iterator;
}

// Получение элемента по индексу Const.
template<ComparableCopyableConstructible Type>
const Type &Vector<Type>::getItem(size_t index) const {
    time_t currentTime = time(NULL);
    if (index < 0 || index >= size)
        throw IndexVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iterator(*this);
    for (size_t i = 0; i < index; i++, iterator++) { }

    return *iterator;
}

template<ComparableCopyableConstructible Type>
size_t Vector<Type>::getSize() const noexcept
{
    return size;
}

template<ComparableCopyableConstructible Type>
bool Vector<Type>::isEmpty() const noexcept
{
    return bool(size);
}

// Установить значени по индексу
template<ComparableCopyableConstructible Type>
bool Vector<Type>::setItem (size_t index, const Type &item)
{
    bool res = true;
    if (index < 0 || index >= size)
            res = false;
    else
    {
        InputIterator<Type> iterator(*this);
        for (size_t i = 0; i < index; i++, iterator++);
        (*iterator) = item;
    }
    return res;
}

// Оператор индексации.
template<ComparableCopyableConstructible Type>
Type &Vector<Type>::operator[] (size_t index)
{
    return getItem(index);
}

// Оператор индексации Const.
template<ComparableCopyableConstructible Type>
const Type &Vector<Type>::operator [](size_t index) const
{
    return getItem(index);
}

// Проверка на нулевой вектор - длина равная 0
template<ComparableCopyableConstructible Type>
bool Vector<Type>::isSingle() const
{
    if (fabs(getLength() - 1) < __DBL_EPSILON__)
        return true;
    return false;
}

// Проверка на единичный вектор - длина равная 1
template<ComparableCopyableConstructible Type>
bool Vector<Type>::isZero() const
{
    if (getLength() == 0)
        return true;
    return false;
}

// вычисление длины вектора
template<ComparableCopyableConstructible Type>
double Vector<Type>::getLength() const
{
    time_t curTime = time(NULL);
    if (size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> iterator(*this);
    double sum = 0.;
    for (; iterator; iterator++)
        sum += *iterator * *iterator;
    sum = sqrt(sum);
    return sum;
}

// получение единичного вектора
template<ComparableCopyableConstructible Type>
Vector<Type> Vector<Type>::getSingle() const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> singleVector(*this);

    double len = getLength();
    InputIterator<Type> iterator(singleVector);

    for (; iterator; iterator++)
        *iterator /= len;
    return singleVector;
}

// Опредление угла между векторами
template<ComparableCopyableConstructible Type>
double Vector<Type>::angleBetweenVectors(const Vector<Type> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (!this->getLength() || !vector.getLength())
        throw ZeroDivError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    double angle = (*this * vector) / (this->getLength() * vector.getLength());
    if (angle > 1) 
        angle = 1.0;

    return acos(angle) * 180 / M_PI;
}

// Проверка на коллинерность вектора
template<ComparableCopyableConstructible Type>
bool Vector<Type>::isCollinear(const Vector<Type>& vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (angleBetweenVectors(vector) < 1e-05)
        return true;
    return false;
}

// Проверка на ортогональность вектора
template<ComparableCopyableConstructible Type>
bool Vector<Type>::isOrthgonal(const Vector<Type>& vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (fabs(angleBetweenVectors(vector) - 90) < __DBL_EPSILON__)
        return true;
    return false;
}

// Умножить на число
template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::operator *(const U &num) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] * num)> newVector(*this);
    InputIterator<Type> iterator(newVector);
    for (; iterator; iterator++)
        *iterator *= num;

    return newVector;
}

template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::mulNum(const U &num) const
{
    return operator*(num);
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator *=(const Type &num)
{
    time_t currentTime = time(NULL);
    if (size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iterator(*this);
    for (; iterator; iterator++)
        *iterator *= num;
    return *this;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::mulNumEqual(const Type &num)
{
    return operator*=(num);
}

// Умножение элементов двух векторов
template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::operator ^(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] * vector[0])> newVector(size);

    InputIterator<decltype((*this)[0] * vector[0])> resIter(newVector);
    InputIterator<Type> fIter(*this);
    InputIterator<U> sIter(vector);

    for (size_t i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        *resIter = *fIter * *sIter;
    }

    return newVector;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator ^=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> fIter(*this);
    InputIterator<Type> sIter(vector);

    for (size_t i = 0; fIter; i++, fIter++, sIter++)
    {
        *fIter = *fIter * *sIter;
    }

    return (*this);
}

template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::mulElems(const Vector<U> & vector) const
{
    return operator^(vector);
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::mulElemsEqual(const Vector<Type> &vector)
{
    return operator^=(vector);
}

// Скалярное произведение
template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
auto Vector<Type>::operator *(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype ((*this)[0] * vector[0])> newVector(size);
    newVector = (*this) ^ vector;
    return newVector.sumValue();
}

template<ComparableCopyableConstructible Type>
Type Vector<Type>::operator *=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    (*this) ^= vector;
    return this->sumValue();
}

template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
auto Vector<Type>::scalarMul(const Vector<U> &vector) const
{
    return operator*(vector);
}

template<ComparableCopyableConstructible Type>
Type Vector<Type>::scalarMulEqual(const Vector<Type> &vector)
{
    return operator*=(vector);
}

// Векторное произведение
template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::operator &(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (size != 3)
        return Vector<Type>();

    decltype((*this)[0] * vector[0]) x = (*this)[1] * vector[2] - (*this)[2] * vector[1];
    decltype((*this)[0] * vector[0]) y = (*this)[2] * vector[0] - (*this)[0] * vector[2];
    decltype((*this)[0] * vector[0]) z = (*this)[0] * vector[1] - (*this)[1] * vector[0];

    Vector<decltype((*this)[0] * vector[0])> new_vector(3, x, y, z);
    return new_vector;
}

template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::vectorMul(const Vector<U> &vector) const
{
    return operator&(vector);
}

template<ComparableCopyableConstructible Type>
Vector<Type>& Vector<Type>::operator &=(const Vector<Type>& vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (size != 3)
        return *(new Vector<Type>);

    Type x = (*this)[1] * vector[2] - (*this)[2] * vector[1];
    Type y = (*this)[2] * vector[0] - (*this)[0] * vector[2];
    Type z = (*this)[0] * vector[1] - (*this)[1] * vector[0];

    *this = Vector<Type>(3, x, y, z);
    return *this;
}

template<ComparableCopyableConstructible Type>
Vector<Type>& Vector<Type>::vectorMulEqual(const Vector<Type>& vector)
{
    return operator&=(vector);
}

// Деление двух векторов
template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::operator /(const Vector<U>& vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + vector[0])> newVector(size);

    InputIterator<decltype((*this)[0] + vector[0])> resIter(newVector);
    InputIterator<Type> fIter((*this));
    InputIterator<U> sIter(vector);

    for (size_t i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        if (fabs(*sIter) < __DBL_EPSILON__)
        {
            curTime = time(NULL);
            throw ZeroDivError (__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
        }
        *resIter = *fIter / *sIter;
    }

    return newVector;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator /=(const Vector<Type>& vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> fIter((*this));
    InputIterator<Type> sIter(vector);

    for (size_t i = 0; fIter; i++, fIter++, sIter++)
    {
        if (fabs(*sIter) < __DBL_EPSILON__)
        {
            curTime = time(NULL);
            throw ZeroDivError (__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
        }
        *fIter /= *sIter;
    }

    return *this;
}

// Деление вектора на число
template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator /=(const Type& number)
{
    time_t curTime = time(NULL);
    if (size <= 0)
       throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (number == 0)
        throw ZeroDivError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> iterator(*this);
    for (; iterator; iterator++)
       *iterator /= number;
    return *this;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::divNumEqual(const Type& number)
{
    return operator/=(number);
}

template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::operator /(const U& number) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
       throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (number == 0)
        throw ZeroDivError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] / number)> new_vector(*this);
    InputIterator<decltype((*this)[0] / number)> iterator(new_vector);
    for (; iterator; iterator++)
       *iterator /= number;
    return new_vector;
}

template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::divNum(const U& number) const
{
    return operator/(number);
}


// Равны ли вектора.
template<ComparableCopyableConstructible Type>
bool Vector<Type>::operator ==(const Vector<Type> &vector) const {
    bool res = true;
    time_t currentTime = time(NULL);
    if (size < 0 || vector.vector_size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    if (size != vector.size)
        res = true;
    else
    {
        InputIterator<Type> fIter(*this);
        InputIterator<Type> sIter(vector);
        for (; res && fIter; sIter++, fIter++)
            if (fabs(*fIter - *sIter) > __DBL_EPSILON__)
                res = false;
    }

    return res;
}

// Различны ли вектора.
template<ComparableCopyableConstructible Type>
bool Vector<Type>::operator !=(const Vector<Type> &vector) const {
    bool res = false;
    time_t currentTime = time(NULL);
    if (size < 0 || vector.vector_size < 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    if (size != vector.size)
        res = true;
    else
    {
        InputIterator<Type> fIter(*this);
        InputIterator<Type> sIter(vector);

        for (; !res && fIter; sIter++)
            if (*fIter != *sIter)
                res = true;
    }

    return res;
}

// Суммирование всех элементов.
template<ComparableCopyableConstructible Type>
Type Vector<Type>::sumValue()
{
    time_t currentTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    InputIterator<Type> iterator(*this);
    Type sum = 0;
    for (; iterator; iterator++)
        sum += *iterator;

    return sum;
}

// Сумма векторов
template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::operator +(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + vector[0])> newVector(size);

    InputIterator<decltype((*this)[0] + vector[0])> resIter(newVector);
    InputIterator<Type> fIter((*this));
    InputIterator<U> sIter(vector);
    for (size_t i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter + *sIter;

    return newVector;
}

template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::sum(const Vector<U> &vector) const
{
    return operator+(vector);
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator +=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> fIter((*this));
    InputIterator<Type> sIter(vector);
    for (size_t i = 0; fIter; i++, fIter++, sIter++)
        *fIter = *fIter + *sIter;

    return *this;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::sumEqual(const Vector<Type> &vector)
{
     return operator+=(vector);
}

// Cумма вектора и числа
template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::operator +(const U &number) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + number)> newVector(size);

    InputIterator<decltype((*this)[0] + number)> resIter(newVector);
    InputIterator<Type> fIter((*this));
    for (size_t i = 0; resIter; i++, resIter++, fIter++)
        *resIter = *fIter + number;

    return newVector;
}

template<ComparableCopyableConstructible Type>
 Vector<Type> &Vector<Type>::operator +=(const Type &number)
 {
     time_t curTime = time(NULL);
     if (size <= 0)
         throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

     InputIterator<Type> fIter((*this));
     for (size_t i = 0; fIter; i++, fIter++)
         *fIter += number;

     return (*this);
 }

template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::sumNum(const U &number) const
{
   return operator +(number);
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::sumNumEqual(const Type &number)
{
    return operator+=(number);
}

// Разность векторов.
template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::operator -(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] - vector[0])> newVector(size);
    InputIterator<decltype((*this)[0] - vector[0])> resIter(newVector);
    InputIterator<Type> fIter((*this));
    InputIterator<U> sIter(vector);

    for (size_t i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter - *sIter;

    return newVector;
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::operator -=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    InputIterator<Type> fIter((*this));
    InputIterator<Type> sIter(vector);

    for (size_t i = 0; fIter; i++, fIter++, sIter++)
        *fIter = *fIter - *sIter;

    return *this;
}

template<ComparableCopyableConstructible Type>
template<ComparableCopyableConstructible U>
requires std::convertible_to<U, Type> 
decltype(auto) Vector<Type>::sub(const Vector<U> &vector) const
{
    return operator-(vector);
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::subEqual(const Vector<Type> &vector)
{
    return operator-=(vector);
}

// Cумма вектора и числа
template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::operator -(const U &number) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + number)> newVector(size);

    InputIterator<decltype((*this)[0] + number)> resIter(newVector);
    InputIterator<Type> fIter((*this));
    for (size_t i = 0; resIter; i++, resIter++, fIter++)
        *resIter = *fIter - number;

    return newVector;
}

template<ComparableCopyableConstructible Type>
 Vector<Type> &Vector<Type>::operator -=(const Type &number)
 {
     time_t curTime = time(NULL);
     if (size <= 0)
         throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

     InputIterator<Type> fIter((*this));
     for (size_t i = 0; fIter; i++, fIter++)
         *fIter -= number;

     return (*this);
 }

template<ComparableCopyableConstructible Type>
template<typename U>
requires std::convertible_to<U, Type>
decltype(auto) Vector<Type>::subNum(const U &number) const
{
   return operator -(number);
}

template<ComparableCopyableConstructible Type>
Vector<Type> &Vector<Type>::subNumEqual(const Type &number)
{
   return operator -=(number);
}


// Оператор вычитания - обратный вектор
template<ComparableCopyableConstructible Type>
Vector<Type> Vector<Type>::operator -()
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorError(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> newVector(*this);
    InputIterator<Type> iterator(newVector);
    for (; iterator; iterator++)
        *iterator = -*iterator;

    return newVector;
}

template<ComparableCopyableConstructible Type>
Vector<Type> Vector<Type>::reverse()
{
    return operator-();
}


// Выделение памяти под новый вектор.
template<ComparableCopyableConstructible Type>
void Vector<Type>::allocNewVectorMem(size_t amount)
{
    time_t currentTime = time(NULL);
    try
    {
        values.reset();
    }
    catch (std::bad_alloc &exception)
    {
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    }
    std::shared_ptr<Type[]> temp(new Type[amount], std::default_delete<Type[]>());
    values = temp;
}

template<ComparableCopyableConstructible Type>
typename Vector<Type>::iterator Vector<Type>::begin() noexcept
{
    return iterator(*this);
}

template<ComparableCopyableConstructible Type>
typename Vector<Type>::iterator Vector<Type>::end() noexcept
{
    return iterator(*this) + size;
}

template<ComparableCopyableConstructible Type>
typename Vector<Type>::const_iterator Vector<Type>::begin() const noexcept
{
    return iterator(*this);
}

template<ComparableCopyableConstructible Type>
typename Vector<Type>::const_iterator Vector<Type>::end() const noexcept
{
    return iterator(*this) + size;
}

template<ComparableCopyableConstructible Type>
typename Vector<Type>::const_iterator Vector<Type>::cbegin() const noexcept
{
    return iterator(*this);
}

template<ComparableCopyableConstructible Type>
typename Vector<Type>::const_iterator Vector<Type>::cend() const noexcept
{
    return iterator(*this) + size;
}

#endif // VECTOR_HPP
