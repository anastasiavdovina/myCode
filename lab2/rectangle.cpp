#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>

vdovina::Rectangle::Rectangle(const point_t& center, double width, double height) :
  center_(center),
  width_(width),
  height_(height)
{
  if (width <= 0)
  {
    throw std::invalid_argument("invalid width: it must be > 0");
  }
  if (height <= 0)
  {
    throw std::invalid_argument("invalid height: it must be > 0");
  }
}

double vdovina::Rectangle::getArea() const
{
  return width_ * height_;
}

vdovina::rectangle_t vdovina::Rectangle::getFrameRect() const
{
  return rectangle_t{ center_, width_, height_ };
}

void vdovina::Rectangle::move(const point_t& newCenter)
{
  center_ = newCenter;
}

void vdovina::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

double vdovina::Rectangle::getWidth() const
{
  return width_;
}

double vdovina::Rectangle::getHeight() const
{
  return height_;
}

vdovina::point_t vdovina::Rectangle::getCentre() const
{
  return center_;
}

void vdovina::Rectangle::print(std::ostream& stream) const
{
  stream << "Rectangle shape info""\n"
         << "Center is in: x = " << center_.x << " y = " << center_.y << "\n"
         << "Width is " << width_ << "\n"
         << "Height is " << height_ << "\n";
}

void vdovina::Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("invalid factor: it must be > 0");
  }
  width_ *= factor;
  height_ *= factor;
}
