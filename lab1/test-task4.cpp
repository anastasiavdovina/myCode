#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "tasks.hpp"
#include "extra-functions.hpp"



BOOST_AUTO_TEST_SUITE(task4_test)

const int size = 10;
const char * order = "ascending";
const char * order1 = "descending";

  BOOST_AUTO_TEST_CASE(correct_sortingOrder_and_size_exceptions)
  {
    std::function<bool(double, double)> comparator = getSortingOrder<double>(order);
    BOOST_CHECK_THROW(task4(comparator, -10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(correct_random_correct_sorting)
  {
    std::vector<double> vec(size);
    std::vector<double> vec1(size);
    fillRandom(vec.data(), size);
    fillRandom(vec1.data(), size);
    std::function<bool(double, double)> comparator = getSortingOrder<double>(order);
    sort<AtPolicy>(vec, comparator);
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
      BOOST_CHECK(vec[i] <= vec[i+1]);
    }
    std::function<bool(double, double)> comparator1 = getSortingOrder<double>(order1);
    sort<AtPolicy>(vec1, comparator1);
    for (size_t i = 0; i < vec.size() - 1; i++)
    {
      BOOST_CHECK(vec1[i] >= vec1[i+1]);
    }
  }

BOOST_AUTO_TEST_SUITE_END()
