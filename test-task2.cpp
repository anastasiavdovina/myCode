#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(task2_test)

const char *filename = "text.txt";

  struct Fixture
  {
    std::streambuf *cout;
    std::ostringstream output;

    Fixture() :
      cout(std::cout.rdbuf(output.rdbuf()))
    {
      std::cout.rdbuf(output.rdbuf());
    }
    ~Fixture()
    {
      std::cout.rdbuf(cout);
    }
  };

  BOOST_AUTO_TEST_CASE(correct_exceptions)
  {
    BOOST_CHECK_THROW(task2(nullptr), std::invalid_argument);
    BOOST_CHECK_THROW(task2("wrong_filename.txt"), std::runtime_error);
  }

  BOOST_FIXTURE_TEST_CASE(correct_copy_into_vector, Fixture)
  {
    const std::string testText = "it works";
    std::ofstream stream;
    stream.open(filename);
    stream << testText << std::endl;
    task2(filename);
    const std::string text = "it works\n";
    const std::string out = output.str();
    BOOST_CHECK_EQUAL(out, text);
    std::remove(filename);
  }

BOOST_AUTO_TEST_SUITE_END()
