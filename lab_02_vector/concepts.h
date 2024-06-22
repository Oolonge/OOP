#ifndef CONCEPTS_H_
#define CONCEPTS_H_

#include <concepts>
#include <memory>
#include <compare>
#include <iterator>
#include <iostream>

template<typename T>
concept Comparable = requires(const T a, const T b) {
    {  a == b  } noexcept -> std::same_as<bool>;
    {  a != b  } noexcept -> std::same_as<bool>;
    requires (std::convertible_to<decltype(a <=> b), std::weak_ordering> ||
             std::convertible_to<decltype(a <=> b), std::partial_ordering>);
};

template<typename Type>
concept CopyableConstructible = std::is_copy_constructible<Type>::value && std::is_copy_assignable<Type>::value; 

template<typename Type>
concept ComparableCopyableConstructible = CopyableConstructible<Type> && Comparable<Type>;

template <typename Type>
concept Container = requires(Type t)
{
    typename Type::value_type;
    typename Type::size_type;
    typename Type::iterator;
    typename Type::const_iterator;
    { t.size() } noexcept -> std::same_as<typename Type::size_type>;
    { t.end() } noexcept -> std::same_as<typename Type::iterator>;
    { t.begin() } noexcept -> std::same_as<typename Type::iterator>;
};

template<typename Type>
concept IsInputIterator = std::input_iterator<Type>;

template<typename From, typename To>
concept ConvertibleTo = std::convertible_to<From, To>;

#endif //CONCEPTS_H_
