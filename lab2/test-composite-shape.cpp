#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "base-types.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

const double EPSILON = 0.00001;
const double RADIUS = 5.1;
const vdovina::point_t CIRCLECENTER = {4.2, 3.7};
const double CIRCLEAREA = RADIUS * RADIUS * M_PI;

const double HEIGHT = 5.1;
const double WIDTH = 7.9;
const vdovina::point_t RECTCENTER = {3.63, 8.76};
const double RECTAREA = HEIGHT * WIDTH;

const double DX = 2.2;
const double DY = 5.6;
const double FACTOR = 2.3;
const double FACTOR1 = -2.3;
const vdovina::point_t NEWCENTER = {7.2, 6.8};
const int size = 2;

struct fixture
{
  vdovina::CompositeShape compositeShape;
  std::shared_ptr<vdovina::Shape> circle;
  std::shared_ptr<vdovina::Shape> rectangle;
  fixture() :
    circle(std::make_shared<vdovina::Circle>(CIRCLECENTER, RADIUS)),
    rectangle(std::make_shared<vdovina::Rectangle>(RECTCENTER, WIDTH, HEIGHT))
  {
    compositeShape.add(circle);
    compositeShape.add(rectangle);
  }
};

BOOST_AUTO_TEST_SUITE(compositeShapeTest)

  BOOST_FIXTURE_TEST_CASE(correct_move_new_center, fixture)
  {
    const double frameRectWidth = compositeShape.getFrameRect().width;
    const double frameRectHeight = compositeShape.getFrameRect().height;
    compositeShape.move(NEWCENTER);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), circle->getArea() + rectangle->getArea(), EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), CIRCLEAREA + RECTAREA, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectWidth, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectHeight, EPSILON);
    BOOST_CHECK_CLOSE(circle->getFrameRect().height / 2, RADIUS, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(correct_move_dx_dy, fixture)
  {
    const double frameRectWidth = compositeShape.getFrameRect().width;
    const double frameRectHeight = compositeShape.getFrameRect().height;
    compositeShape.move(DX, DY);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), circle->getArea() + rectangle->getArea(), EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), CIRCLEAREA + RECTAREA, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectWidth, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectHeight, EPSILON);
    BOOST_CHECK_CLOSE(circle->getFrameRect().height / 2, RADIUS, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(correct_get_size_and_invariableness_of_parameters, fixture)
  {
    const double frameRectWidth = compositeShape.getFrameRect().width;
    const double frameRectHeight = compositeShape.getFrameRect().height;
    compositeShape.size();
    BOOST_CHECK_EQUAL(compositeShape.size(), 2);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), circle->getArea() + rectangle->getArea(), EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), CIRCLEAREA + RECTAREA, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectWidth, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectHeight, EPSILON);
    BOOST_CHECK_CLOSE(circle->getFrameRect().height / 2, RADIUS, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(correct_scale, fixture)
  {
    const double frameRectWidth = compositeShape.getFrameRect().width;
    const double frameRectHeight = compositeShape.getFrameRect().height;
    const double radiusBeforeScaling = circle->getFrameRect().height / 2;
    const double areaBeforeScaling = compositeShape.getArea();
    const vdovina::rectangle_t frameRect = compositeShape.getFrameRect();
    const double DX = (rectangle->getFrameRect().pos.x - frameRect.pos.x) * FACTOR;
    const double DY = (rectangle->getFrameRect().pos.y - frameRect.pos.y) * FACTOR;
    const double circleDx = (circle->getFrameRect().pos.x - frameRect.pos.x) * FACTOR;
    const double circleDy = (circle->getFrameRect().pos.y - frameRect.pos.y) * FACTOR;
    compositeShape.scale(FACTOR);
    BOOST_CHECK_CLOSE(compositeShape.getCentre().x, compositeShape.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getCentre().y, compositeShape.getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getArea(), areaBeforeScaling * FACTOR * FACTOR, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectWidth * FACTOR, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectHeight * FACTOR, EPSILON);
    BOOST_CHECK_CLOSE(radiusBeforeScaling * FACTOR, RADIUS * FACTOR, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape[1]->getFrameRect().pos.x, frameRect.pos.x + DX, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape[1]->getFrameRect().pos.y, frameRect.pos.y + DY, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape[0]->getFrameRect().pos.x, frameRect.pos.x + circleDx, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape[0]->getFrameRect().pos.y, frameRect.pos.y + circleDy, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(correct_exceptions_with_invalid_arguments, fixture)
  {
    const int INDEX = -1;
    const int INDEX1 = 5;
    BOOST_CHECK_THROW(compositeShape.scale(FACTOR1), std::invalid_argument);
    BOOST_CHECK_THROW(compositeShape.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(compositeShape[INDEX], std::out_of_range);
    BOOST_CHECK_THROW(compositeShape.add(circle), std::logic_error);
    BOOST_CHECK_THROW(compositeShape.remove(INDEX), std::out_of_range);
    BOOST_CHECK_THROW(compositeShape.remove(INDEX1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(empty_shapes)
  {
    vdovina::CompositeShape compShape;
    BOOST_CHECK_THROW(compShape.getFrameRect(), std::logic_error);
    BOOST_CHECK_THROW(compShape.getCentre(), std::logic_error);
    BOOST_CHECK_THROW(compShape.getArea(), std::logic_error);
    BOOST_CHECK_THROW(compShape.scale(FACTOR), std::logic_error);
    BOOST_CHECK_THROW(compShape.move(DX, DY), std::logic_error);
    BOOST_CHECK_THROW(compShape.move(NEWCENTER), std::logic_error);
  }

  BOOST_FIXTURE_TEST_CASE(correct_get, fixture)
  {
    BOOST_CHECK_CLOSE(compositeShape.getArea(), CIRCLEAREA + RECTAREA, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, compositeShape.getCentre().x, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, compositeShape.getCentre().y, EPSILON);
    const double X1 = std::max(RECTCENTER.x + WIDTH * 0.5, CIRCLECENTER.x + RADIUS);
    const double X = std::min(RECTCENTER.x - WIDTH * 0.5, CIRCLECENTER.x - RADIUS);
    const double Y1 = std::max(RECTCENTER.y + HEIGHT * 0.5, CIRCLECENTER.y + RADIUS);
    const double Y = std::min(RECTCENTER.y - HEIGHT * 0.5, CIRCLECENTER.y - RADIUS);
    const double frameRectWidth = X1 - X;
    const double  frameRectHeight = Y1 - Y;
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectHeight, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectWidth, EPSILON);
  }

  BOOST_FIXTURE_TEST_CASE(correct_copy, fixture)
  {
    vdovina::CompositeShape temp(compositeShape);
    BOOST_CHECK_EQUAL(compositeShape.size(), temp.size());
    for (int i = 0; i < size; i++)
    {
      BOOST_CHECK_EQUAL(compositeShape[i], temp[i]);
    }
  }

  BOOST_FIXTURE_TEST_CASE(correct_copy_operator, fixture)
  {
    vdovina::CompositeShape temp = compositeShape;
    BOOST_CHECK_EQUAL(compositeShape.size(), temp.size());
    for (int i = 0; i < size; i++)
    {
      BOOST_CHECK_EQUAL(compositeShape[i], temp[i]);
    }
  }

  BOOST_FIXTURE_TEST_CASE(correct_move, fixture)
  {
    vdovina::CompositeShape compShapeForMoving(compositeShape);
    vdovina::CompositeShape temp(std::move(compShapeForMoving));
    BOOST_CHECK_EQUAL(compShapeForMoving.size(), 0);
    BOOST_CHECK_EQUAL(compositeShape.size(), temp.size());
    for (int i = 0; i < size; i++)
    {
      BOOST_CHECK_EQUAL(compositeShape[i], temp[i]);
    }
  }

  BOOST_FIXTURE_TEST_CASE(correct_move_operator, fixture)
  {
    vdovina::CompositeShape compShapeForMoving(compositeShape);
    vdovina::CompositeShape temp = std::move(compShapeForMoving);
    BOOST_CHECK_EQUAL(compShapeForMoving.size(), 0);
    BOOST_CHECK_EQUAL(compositeShape.size(), temp.size());
    for (int i = 0; i < size; i++)
    {
      BOOST_CHECK_EQUAL(compositeShape[i], temp[i]);
    }
  }

  BOOST_FIXTURE_TEST_CASE(method_add_test, fixture)
  {
    const std::shared_ptr<vdovina::CompositeShape> compShape = std::make_shared<vdovina::CompositeShape>();
    compShape->add(circle);
    compShape->add(rectangle);
    BOOST_CHECK_EQUAL(compositeShape[0], circle);
    BOOST_CHECK_EQUAL(compositeShape[1], rectangle);
    BOOST_CHECK_THROW(compShape->add(circle), std::logic_error);
    BOOST_CHECK_THROW(compShape->add(rectangle), std::logic_error);
    BOOST_CHECK_THROW(compShape->add(compShape), std::logic_error);
    std::shared_ptr<vdovina::Shape> newRect = std::make_shared<vdovina::Rectangle>(NEWCENTER, HEIGHT, WIDTH);
    compositeShape.add(newRect);
    BOOST_CHECK_EQUAL(compositeShape[2], newRect);
  }

  BOOST_FIXTURE_TEST_CASE(correct_remove, fixture)
  {
    compositeShape.remove(1);
    BOOST_CHECK_THROW(compositeShape[1], std::out_of_range);
    const vdovina::point_t cntr = {1.2, 5.6};
    const double rad = 3.4;
    std::shared_ptr<vdovina::Shape> crcl = std::make_shared<vdovina::Circle >(cntr, rad);
    compositeShape.add(crcl);
    compositeShape.remove(1);
    bool is_CS_contain_figure = false;
    for(size_t i = 0; i < compositeShape.size(); i++)
    {
      if(compositeShape[i] == crcl)
      {
        is_CS_contain_figure = true;
      }
    }
    BOOST_CHECK(is_CS_contain_figure == false);
  }

BOOST_AUTO_TEST_SUITE_END()
