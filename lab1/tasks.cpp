#include "tasks.hpp"

#include <cstdlib>
#include <forward_list>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "extra-functions.hpp"

void task1(std::function<bool(const int &, const int &)> comparator)
{
  std::vector<int> vector;
  int element = 0;
  while (std::cin >> element)
  {
    vector.push_back(element);
  }
  if(!std::cin.eof())
  {
    throw std::runtime_error("Incorrect input");
  }
  if (vector.empty())
  {
    return;
  }
  std::vector<int> vector1 = vector;
  std::forward_list<int> list(vector.begin(), vector.end());
  sort<BracketsPolicy>(vector, comparator);
  sort<IteratorPolicy>(list, comparator);
  sort<AtPolicy>(vector1, comparator);
  print(vector, " ");
  std::cout << "\n";
  print(vector1, " ");
  std::cout << "\n";
  print(list, " ");
}

void task2(const char *filename)
{
  if (filename == nullptr)
  {
    throw std::invalid_argument("Filename is undefined");
  }
  std::ifstream stream(filename);
  if (!stream)
  {
    throw std::runtime_error("File is not open");
  }
  size_t capacity = 1;
  size_t size = 0;
  std::unique_ptr<char[], decltype(&std::free)> data(static_cast<char*>(std::malloc(capacity)), &std::free);
  if (!data)
  {
    throw std::bad_alloc();
  }
  while (stream)
  {
    stream.read(data.get() + size, capacity - size);
    size += stream.gcount();
    if (size == capacity)
    {
      capacity *= 2;
      std::unique_ptr<char[], decltype(&std::free)> tempData(static_cast<char*>(std::realloc(data.get(), capacity)), &std::free);
      if (!tempData)
      {
        throw std::bad_alloc();
      }
      data.release();
      data = std::move(tempData);
    }
  }
  if (!stream.eof())
  {
    throw std::runtime_error("Error while reading from file");
  }
  std::vector<char> vector(data.get(),data.get() + size);
  print(vector, "");
}

void task3()
{
  std::vector<int> vector;
  int element = 0;
  while (std::cin >> element)
  {
    if (element == 0)
    {
      break;
    }
    vector.push_back(element);
  }
  if (element != 0)
  {
    throw std::runtime_error("Last element must be 0");
  }
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Incorrect input");
  }
  if (vector.empty())
  {
    return;
  }
  auto iterator = vector.begin();
  switch (vector.back())
  {
  case 1:
    while (iterator != vector.end()) {
      if (*iterator % 2 == 0) {
        iterator = vector.erase(iterator);
      }
      else
      {
        iterator++;
      }
    }
    break;
  case 2:
    while (iterator != vector.end()) {
      if (*iterator % 3 == 0)
      {
        iterator = vector.insert(iterator + 1, 3, 1) + 3;
      }
      else
      {
        iterator++;
      }
    }
    break;
  default:
    break;
  }
  print(vector, " ");
}

void fillRandom(double * array, int size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Array is nullptr");
  }
  if (size < 0)
  {
    throw std::invalid_argument("Size must be > 0");
  }
  for (int i = 0; i < size; i++)
  {
    array[i] = static_cast<double> (rand()) / RAND_MAX * 2 - 1;
  }
}

void task4(std::function<bool(const double &, const double &)> compar, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Incorrect size provided");
  }
  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector, " ");
  std::cout << "\n";
  sort<AtPolicy>(vector, compar);
  print(vector, " ");
}
