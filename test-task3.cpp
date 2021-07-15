#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(task3_test)

  const std::string input1 = "1 2 3 4 5 6 7 8 9 1 0";
  const std::string output1 = "1 3 5 7 9 1 ";
  const std::string input2 = "1 2 3 4 5 6 7 8 9 2 0";
  const std::string output2 = "1 2 3 1 1 1 4 5 6 1 1 1 7 8 9 1 1 1 2 ";
  const std::string incorrectInput = "1 2 3 4 5 6 7 8 9";
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

  BOOST_FIXTURE_TEST_CASE(correct_editing_with_1, Fixture)
  {
    input.str(input1);
    task3();
    const std::string out = output.str();
    BOOST_CHECK_EQUAL(out, output1);
  }

  BOOST_FIXTURE_TEST_CASE(correct_editing_with_2, Fixture)
  {
    input.str(input2);
    task3();
    const std::string out = output.str();
    BOOST_CHECK_EQUAL(out, output2);
  }

  BOOST_FIXTURE_TEST_CASE(incorrect_input_no_zero, Fixture)
  {
    input.str(incorrectInput);
    BOOST_CHECK_THROW(task3(), std::runtime_error);
  }

  BOOST_FIXTURE_TEST_CASE(incorrect_input_double, Fixture)
  {
    input.str(incorrectInput1);
    BOOST_CHECK_THROW(task3(), std::runtime_error);
  }

BOOST_AUTO_TEST_SUITE_END()
