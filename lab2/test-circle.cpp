#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(circletest)

  const double EPSILON = 0.00001;
  const double RADIUS = 5.1;
  const vdovina::point_t CENTER = { 3.6, 8.7 };
  const double AREA = 81.7128248;
  const double FACTOR = 4.86;
  const double RADIUS1 = -4.7;
  const double DX = 2.2;
  const double DY = 5.6;
  const vdovina::point_t NEWCENTER = { 7.24, 6.87 };
  const double FACTOR1 = -1.2;

  BOOST_AUTO_TEST_CASE(correct_scale)
  {
    vdovina::Circle circle(CENTER, RADIUS);
    circle.scale(FACTOR);
    BOOST_CHECK_CLOSE(circle.getArea(), FACTOR * FACTOR * AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * FACTOR * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * FACTOR * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(correct_move_new_centre)
  {
    vdovina::Circle circle(CENTER, RADIUS);
    circle.move(NEWCENTER);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, NEWCENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, NEWCENTER.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(correct_move_dx_dy)
  {
    vdovina::Circle circle(CENTER, RADIUS);
    circle.move(DX, DY);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x + DX, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y + DY, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(arguments)
  {
    vdovina::Circle circle(CENTER, RADIUS);
    BOOST_CHECK_THROW(circle.scale(FACTOR1), std::invalid_argument);
    BOOST_CHECK_THROW(vdovina::Circle circle1(CENTER, RADIUS1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getters)
  {
    vdovina::Circle circle(CENTER, RADIUS);
    BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getCentre().y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
