#include <iostream>
#include <functional>
#include <sstream>
#include <stdexcept>
#include "tasks.hpp"
#include "extra-functions.hpp"

int main(int argc, char* argv[])
{
  std::srand(std::time(nullptr));
  if ((argc < 2) || (argc > 4))
  {
    std::cerr << "Incorrect arguments provided";
    return 1;
  }
  int taskNum = 0;
  std::istringstream read(argv[1]);
  read >> taskNum;
  if (!read.eof())
  {
    std::cerr << "Incorrect input of task number";
    return 1;
  }
  switch(taskNum)
  {
  case 1:
    if (argc != 3)
    {
      std::cerr << "Incorrect number of arguments";
      return 1;
    }
    try
    {
      std::function<bool(const int &, const int &)> comparator = getSortingOrder<int>(argv[2]);
      task1(comparator);
    }
    catch (const std::invalid_argument &error)
    {
      std::cerr << error.what() << "\n";
      return 1;
    }
    catch (const std::runtime_error &error)
    {
      std::cerr << error.what() << "\n";
      return 2;
    }
    break;
  case  2:
    if (argc != 3)
    {
      std::cerr << "Incorrect number of arguments";
      return 1;
    }
    try
    {
      task2(argv[2]);
    }
    catch (const std::runtime_error &error)
    {
      std::cerr << error.what() << "\n";
      return 2;
    }
    catch (const std::invalid_argument &error)
    {
      std::cerr << error.what() << "\n";
      return 1;
    }
    break;
  case 3:
    if (argc != 2)
    {
      std::cerr << "Incorrect number of arguments";
      return 1;
    }
    try
    {
      task3();
    }
    catch (const std::runtime_error &error)
    {
      std::cerr << error.what() << "\n";
      return 2;
    }
    catch (const std::logic_error &error)
    {
      std::cerr << error.what() << "\n";
      return 2;
    }
    break;
  case 4:
    if (argc != 4)
    {
      std::cerr << "Incorrect number of arguments";
      return 1;
    }
    try
    {
      std::function<bool(double, double)> comparator = getSortingOrder<double>(argv[2]);
      int size = 0;
      std::istringstream stream(argv[3]);
      stream >> size;
      if (!stream.eof())
      {
        std::cerr << "Incorrect input of size";
        return 1;
      }
      task4(comparator, size);
    }
    catch (const std::invalid_argument &error)
    {
      std::cerr << error.what() << "\n";
      return 1;
    }
    break;
  default:
    std::cerr << "Incorrect task number";
    return 1;
  }
  return 0;
}
