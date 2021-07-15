#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(rectangletest)

  const double EPSILON = 0.0000001;
  const double HEIGHT = 5.1;
  const double WIDTH = 7.9;
  const vdovina::point_t CENTER = { 3.63, 8.76 };
  const double AREA = 40.29;
  const double FACTOR = 2.3;
  const double FACTOR1 = -2.3;
  const double WIDTH1 = -4.7;
  const double HEIGHT1 = -4.7;
  const double DX = 2.2;
  const double DY = 5.6;
  const vdovina::point_t NEWCENTER = { 7.2, 6.8 };

  BOOST_AUTO_TEST_CASE(correct_scale)
  {
    vdovina::Rectangle rectangle(CENTER, WIDTH, HEIGHT);
    rectangle.scale(FACTOR);
    BOOST_CHECK_CLOSE(rectangle.getArea(), FACTOR * FACTOR * AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT * FACTOR, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH * FACTOR, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(correct_move_new_centre)
  {
    vdovina::Rectangle rectangle(CENTER, WIDTH, HEIGHT);
    rectangle.move(NEWCENTER);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, NEWCENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, NEWCENTER.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(correct_move_dx_dy)
  {
    vdovina::Rectangle rectangle(CENTER, WIDTH, HEIGHT);
    rectangle.move(DX, DY);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x + DX, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y + DY, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(arguments)
  {
    vdovina::Rectangle rectangle(CENTER, WIDTH, HEIGHT);
    BOOST_CHECK_THROW(rectangle.scale(FACTOR1), std::invalid_argument);
    BOOST_CHECK_THROW(vdovina::Rectangle rectangle1(CENTER, WIDTH1, HEIGHT);, std::invalid_argument);
    BOOST_CHECK_THROW(vdovina::Rectangle rectangle2(CENTER, WIDTH, HEIGHT1);, std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getters)
  {
    vdovina::Rectangle rectangle(CENTER, WIDTH, HEIGHT);
    BOOST_CHECK_CLOSE(rectangle.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
