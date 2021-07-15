#include <cmath>
#include <forward_list>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "extra-functions.hpp"
#include "policy.hpp"

BOOST_AUTO_TEST_SUITE(extra_functions_test)

  auto ascending = getSortingOrder<int>("ascending");
  auto descending = getSortingOrder<int>("descending");
  const int size = 10;

  struct fixture
  {
    std::vector<int> vector;
    std::vector<int> vectorAscending;
    std::vector<int> vectorDescending;
    std::forward_list<int> list;
    std::forward_list<int> listAscending;
    std::forward_list<int> listDescending;
    std::streambuf *cout;
    std::ostringstream output;
    fixture() :
      vector({5, 10, 2, 53, 7, 23, 11, 8}),
      vectorAscending({2, 5, 7, 8, 10, 11, 23, 53}),
      vectorDescending({53, 23, 11, 10, 8, 7, 5, 2}),
      list({5, 10, 2, 53, 7, 23, 11, 8}),
      listAscending({2, 5, 7, 8, 10, 11, 23, 53}),
      listDescending({53, 23, 11, 10, 8, 7, 5, 2}),
      cout(std::cout.rdbuf(output.rdbuf()))
    {
      std::cout.rdbuf(output.rdbuf());
    }
    ~fixture()
    {
      std::cout.rdbuf(cout);
    }
  };

  BOOST_FIXTURE_TEST_CASE(sort_with_at_policy, fixture)
  {
    sort<AtPolicy>(vector, ascending);
    BOOST_CHECK(vector == vectorAscending);
    sort<AtPolicy>(vector, descending);
    BOOST_CHECK(vector == vectorDescending);
  }

  BOOST_FIXTURE_TEST_CASE(sort_with_brackets_policy, fixture)
  {
    sort<BracketsPolicy>(vector, ascending);
    BOOST_CHECK(vector == vectorAscending);
    sort<BracketsPolicy>(vector, descending);
    BOOST_CHECK(vector == vectorDescending);
  }

  BOOST_FIXTURE_TEST_CASE(sort_with_iterator_policy, fixture)
  {
    sort<IteratorPolicy>(list, ascending);
    BOOST_CHECK(list == listAscending);
    sort<IteratorPolicy>(list, descending);
    BOOST_CHECK(list == listDescending);
  }

  BOOST_AUTO_TEST_CASE(getSortingOrder_exceptions)
  {
    BOOST_CHECK_THROW(getSortingOrder<double>(""), std::invalid_argument);
    BOOST_CHECK_THROW(getSortingOrder<double>("wrongSortOrder"), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(checkDefineOrder)
  {
    auto comparator1 = getSortingOrder<double>("ascending");
    auto comparator2 = getSortingOrder<double>("descending");
    BOOST_CHECK(comparator1(0, 1) == true);
    BOOST_CHECK(comparator2(1, 0) == true);
  }

  BOOST_FIXTURE_TEST_CASE(correct_fillrendom, fixture)
  {
    std::vector<double> vec(size);
    std::vector<double> vec1(size);
    fillRandom(vec.data(), size);
    fillRandom(vec1.data(), size);
    print(vec, " ");
    const std::string out = output.str();
    print(vec1, " ");
    const std::string out1 = output.str();
    BOOST_CHECK(out != out1);
  }

BOOST_AUTO_TEST_SUITE_END()
