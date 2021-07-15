#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/test/unit_test.hpp>

#include "tasks.hpp"
#include "extra-functions.hpp"

BOOST_AUTO_TEST_SUITE(task1_test)

const std::string input1 = "7 2 9 3 1 0 5 3 7 5";
const std::string ascOutput = "0 1 2 3 3 5 5 7 7 9 \n0 1 2 3 3 5 5 7 7 9 \n0 1 2 3 3 5 5 7 7 9 ";
const std::string descOutput = "9 7 7 5 5 3 3 2 1 0 \n9 7 7 5 5 3 3 2 1 0 \n9 7 7 5 5 3 3 2 1 0 ";
const std::string incorrectInput1 = "1 2 3.14 4 5 6 7 8 9 0";

  struct Fixture
  {
    std::streambuf *cin;
    std::streambuf *cout;
    std::istringstream input;
    std::ostringstream output;

    Fixture() :
      cin(std::cin.rdbuf(input.rdbuf())),
      cout(std::cout.rdbuf(output.rdbuf()))
    {
      std::cin.rdbuf(input.rdbuf());
      std::cout.rdbuf(output.rdbuf());
    }
    ~Fixture()
    {
      std::cin.rdbuf(cin);
      std::cout.rdbuf(cout);
    }
  };

  BOOST_FIXTURE_TEST_CASE(correct_ascending_sorting, Fixture)
  {
    input.str(input1);
    std::function<bool(const int&, const int&)> comparator = getSortingOrder<int>("ascending");
    task1(comparator);
    const std::string out = output.str();
    BOOST_CHECK_EQUAL(out, ascOutput);
  }

  BOOST_FIXTURE_TEST_CASE(correct_descending_sorting, Fixture)
  {
    input.str(input1);
    std::function<bool(const int&, const int&)> comparator = getSortingOrder<int>("descending");
    task1(comparator);
    const std::string out = output.str();
    BOOST_CHECK_EQUAL(out, descOutput);
  }

BOOST_AUTO_TEST_SUITE_END()
