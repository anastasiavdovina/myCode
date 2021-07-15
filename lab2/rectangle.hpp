#ifndef A_RECTANGLE_HPP
#define A_RECTANGLE_HPP

#include <iostream>

#include "base-types.hpp"
#include "shape.hpp"

namespace vdovina
{
class Rectangle :public Shape
  {
  public:
    Rectangle(const point_t& center, double width, double height);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& center) override;
    void move(double dx, double dy) override;
    double getWidth() const;
    double getHeight() const;
    point_t getCentre() const;
    void print(std::ostream& stream) const override;
    void scale(double factor) override;

  private:
    point_t center_;
    double width_;
    double height_;
  };
}

#endif
