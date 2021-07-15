#ifndef B1_TASKS_HPP
#define B1_TASKS_HPP

#include <functional>

void task1(std::function<bool(const int &, const int &)> comparator);
void task2(const char *filename);
void task3();
void task4(std::function<bool(const double &, const double &)> compar, int size);

#endif
