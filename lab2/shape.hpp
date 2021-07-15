#ifndef A_SHAPE_HPP
#define A_SHAPE_HPP

#include <iostream>
#include <memory>

namespace vdovina
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    using Ptr = std::shared_ptr<Shape>;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& centre_p) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void print(std::ostream& stream) const = 0;
    virtual void scale(double factor) = 0;
  };
}

#endif
