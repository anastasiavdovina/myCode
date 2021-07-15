#ifndef B1_EXTRA_FUNCTIONS_HPP
#define B1_EXTRA_FUNCTIONS_HPP

#include <ctime>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <cstdlib>

#include "policy.hpp"

void fillRandom(double * array, int size);

template<class T>
std::function<bool(const T, const T)> getSortingOrder(const char *order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument("Sorting order is undefined");
  }
  if (!strcmp(order, "ascending"))
  {
    return std::less<const T>();
  }
  if (!strcmp(order, "descending"))
  {
    return std::greater<const T>();
  }
  else
  {
  throw std::invalid_argument("Sorting order is incorrect");
  }
}

template<class T>
void print(T& container, const char* separator)
{
  if (separator == nullptr) {
    throw std::invalid_argument("Incorrect separator");
  }
  for(auto i = container.begin(); i != container.end(); i++)
  {
    std::cout << *i << separator;
  }
}

template<typename T> using compare = std::function<bool(typename T::value_type, typename T::value_type)>;

template<template<class> class Policy, class T>
void sort(T& container, compare<T> comparator)
{
  typename Policy<T>::iterator i = Policy<T>::begin(container);
  typename Policy<T>::iterator j = Policy<T>::begin(container);
  typename Policy<T>::iterator end = Policy<T>::end(container);
  while (i != end)
  {
    j = i;
    while (++j != end)
    {
      typename T::value_type &temp = Policy<T>::get(container, j);
      typename T::value_type &temp1 = Policy<T>::get(container, i);
      if(comparator(temp, temp1))
      {
        std::swap(temp, temp1);
      }
    }
    i++;
  }
}

#endif
