#define _USE_MATH_DEFINES

#include "circle.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

vdovina::Circle::Circle(const point_t& center, double radius) :
  center_(center),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("invalid radius: it must be > 0");
  }
}

double vdovina::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

vdovina::rectangle_t vdovina::Circle::getFrameRect() const
{
  return rectangle_t{ center_, radius_ * 2, radius_ * 2 };
}

void vdovina::Circle::move(const point_t& newCentre)
{
  center_ = newCentre;
}

void vdovina::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

double vdovina::Circle::getRadius() const
{
  return radius_;
}

vdovina::point_t vdovina::Circle::getCentre() const
{
  return center_;
}

void vdovina::Circle::print(std::ostream& stream) const
{
  stream << "Circle shape info\n"
         << "Center is in: x = " << center_.x << " y = " << center_.y << "\n"
         << "Radius is " << radius_ << "\n";
}

void vdovina::Circle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("invalid factor: it must be > 0");
  }
  radius_ *= factor;
}
