#ifndef BASE_VECTOR_H
#define BASE_VECTOR_H

class BaseVector
{
public:
    virtual ~BaseVector() = default;

    virtual bool isEmpty() const = 0;
    virtual size_t getSize() const = 0;

protected:
    size_t size = 0;
};

#endif // BASE_VECTOR_H
