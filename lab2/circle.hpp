#ifndef A_CIRCLE_HPP
#define A_CIRCLE_HPP

#include <iostream>

#include "base-types.hpp"
#include "shape.hpp"

namespace vdovina
{
  class Circle :public Shape
  {
  public:
    Circle(const point_t& centre, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& centre_p) override;
    void move(double dx, double dy) override;
    double getRadius() const;
    point_t getCentre() const;
    void print(std::ostream& stream) const override;
    void scale(double factor) override;

  private:
    point_t center_;
    double radius_;
  };
}

#endif
