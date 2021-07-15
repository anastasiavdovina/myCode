#include <vector>
#include <forward_list>
#include <boost/test/unit_test.hpp>

#include "policy.hpp"

BOOST_AUTO_TEST_SUITE(policy_test)

  const int size = 10;

  struct Fixture
  {
    std::vector<int> vector;
    std::list<int> list;

    Fixture() :
      vector({-6, 2, 9, 3, 1, 0, -4, 3, 7, 5}),
      list({-6, 2, 9, 3, 1, 0, -4, 3, 7, 5})
    { }

  };

  BOOST_FIXTURE_TEST_CASE(test_bigin, Fixture)
  {
    BOOST_CHECK(BracketsPolicy<std::vector<int>>::begin(vector) == 0);
    BOOST_CHECK(AtPolicy<std::vector<int>>::begin(vector) == 0);
    BOOST_CHECK(IteratorPolicy<std::list<int>>::begin(list) == list.begin());
  }

  BOOST_FIXTURE_TEST_CASE(test_end, Fixture)
  {
    BOOST_CHECK(BracketsPolicy<std::vector<int>>::end(vector) == size);
    BOOST_CHECK(AtPolicy<std::vector<int>>::end(vector) == size);
    BOOST_CHECK(IteratorPolicy<std::list<int>>::end(list) == list.end());
  }

  BOOST_FIXTURE_TEST_CASE(test_get, Fixture)
  {
    for (int i = 0; i < size; i++)
    {
      BOOST_CHECK(vector[i] == BracketsPolicy<std::vector<int>>::get(vector, i));
    }
    for (int i = 0; i < size; i++)
    {
      BOOST_CHECK(vector.at(i) == AtPolicy<std::vector<int>>::get(vector, i));
    }
    std::list<int>::iterator i;
    for (i = list.begin(); i != list.end(); i++)
    {
      BOOST_CHECK(*i == IteratorPolicy<std::list<int>>::get(list, i));
    }
  }

BOOST_AUTO_TEST_SUITE_END()
