#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <cstring>

#define STR_SIZE 200

class BaseError: public std::exception
{
public:
    BaseError(const char* filename,
              const char* classname,
              int line,
              const char *time,
              const char* info = "Error!")
    {
        snprintf(error_info, STR_SIZE, "\nFile name: %s"
                                  "\nClass: %s"
                                  "\nLine: %d"
                                  "\nTime: %s"
                                  "Info: %s",
                filename, classname, line, time, info);
    }

    virtual const char* what() const noexcept override
    {
        return error_info;
    }

protected:
    char error_info[STR_SIZE];
};

class MemoryError: public BaseError
{
public:
    MemoryError(const char* filename,
                const char* classname,
                int line,
                const char *time,
                const char* info = "Memory allocation error!\n"):
        BaseError(filename, classname, line, time, info) {};
};

class DeletedObject: public BaseError
{
public:
    DeletedObject(const char* filename,
                const char* classname,
                int line,
                const char *time,
                const char* info = "Attempt to work with a remote object!\n"):
        BaseError(filename, classname, line, time, info) {};
};

class InvalidIterator : public BaseError
{
public:
    InvalidIterator(
        const char* filename,
        const char* classname,
        int line,
        const char *time,
        const char* info = "Attempt to use an invalid iterator!\n") :
    BaseError(filename, classname, line, time, info) {};
};

class EmptyVectorError : public BaseError
{
public:
    EmptyVectorError(const char* filename,
                     const char* classname,
                     int line, const char *time,
                     const char* info = "The size of the vector must be greater than 0!\n") :
    BaseError(filename, classname, line, time, info) {};
};

class IndexVectorError : public BaseError
{
public:
    IndexVectorError(const char* filename,
               const char* classname,
               int line, const char *time,
               const char* info = "Going beyond the vector limit!\n") :
    BaseError(filename, classname, line, time, info) {};
    virtual const char* what() const noexcept
    {
        return error_info;
    }
};

class ZeroDivError : public BaseError
{
public:
    ZeroDivError(const char* filename,
                 const char* classname,
                 int line,
                 const char *time,
                 const char* info = "Division by zero is not allowed!\n") :
    BaseError(filename, classname, line, time, info) {};
};

class InvalidCopyArrayPointer : public BaseError
{
public:
    InvalidCopyArrayPointer(const char* filename,
                 const char* classname,
                 int line,
                 const char *time,
                 const char* info = "The original array does not exist!\n") :
    BaseError(filename, classname, line, time, info) {};
};

class DifferentSizeVectors: public BaseError
{
public:
    DifferentSizeVectors(const char* filename,
                 const char* classname,
                 int line,
                 const char *time,
                 const char* info = "The Vectors are different size!\n") :
    BaseError(filename, classname, line, time, info) {};
};

#endif // ERRORS_H