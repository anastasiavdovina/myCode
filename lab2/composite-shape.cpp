#include "composite-shape.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>

#include "base-types.hpp"

vdovina::CompositeShape::CompositeShape() :
  size_(0)
{
}

vdovina::CompositeShape::CompositeShape(const CompositeShape &src) :
  size_(src.size_)
{
  if (src.size_ != 0)
  {
    shapesArray_ = std::make_unique<Ptr[]>(src.size_);
    for (size_t i = 0; i < src.size_; ++i)
    {
      shapesArray_[i] = src.shapesArray_[i];
    }
  }
}

vdovina::CompositeShape::CompositeShape(vdovina::CompositeShape &&src) noexcept:
  size_(src.size_),
  shapesArray_(std::move(src.shapesArray_))
{
  src.size_ = 0;
}

vdovina::CompositeShape &vdovina::CompositeShape::operator=(const CompositeShape &shape)
{
  if (this == &shape)
  {
    return *this;
  }
  if (shape.size_ != 0)
  {
    shapesArray_ = std::make_unique<Ptr[]>(shape.size_);
    size_ = shape.size_;
    for (size_t i = 0; i < size_; i++)
    {
      shapesArray_[i] = shape.shapesArray_[i];
    }
  }
  else
  {
    shapesArray_ = nullptr;
    size_ = 0;
  }
  return *this;
}

vdovina::CompositeShape &vdovina::CompositeShape::operator=(CompositeShape &&shape) noexcept
{
  if (this == &shape)
  {
    return *this;
  }
  size_ = shape.size_;
  shapesArray_ = std::move(shape.shapesArray_);
  shape.size_ = 0;
  return *this;
}

vdovina::Shape::Ptr vdovina::CompositeShape::operator[](size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Incorrect index");
  }
  return shapesArray_[index];
}

void vdovina::CompositeShape::add(const vdovina::Shape::Ptr &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape is nullptr");
  }
  for (size_t i = 0; i < size_; ++i)
  {
    if (shapesArray_[i] == shape)
    {
      throw std::logic_error("Such shape is already here");
    }
  }
  if (this == shape.get())
  {
    throw std::logic_error("Cannot add shape to itself");
  }
  std::unique_ptr<Ptr[]> tempArray = std::make_unique<Ptr[]>(size_ + 1);
  for (size_t i = 0; i < size_; i++)
  {
    tempArray[i] = std::move(shapesArray_[i]);
  }
  tempArray[size_] = shape;
  shapesArray_ = std::move(tempArray);
  size_++;
}

void vdovina::CompositeShape::remove(size_t index)
{
  if (index > size_ - 1)
  {
    throw std::out_of_range("Index should be < size_");
  }
  size_t count = 0;
  std::unique_ptr<Ptr[]> tempArray = std::make_unique<Ptr[]>(size_ - 1);
  for (size_t i = 0; i < size_; i++)
  {
    if (i != index)
    {
      tempArray[i - count] = std::move(shapesArray_[i]);
    }
    else
    {
      count++;
    }
  }
  size_--;
  shapesArray_ = std::move(tempArray);
}

vdovina::rectangle_t vdovina::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }
  vdovina::rectangle_t tempRect = shapesArray_[0]->getFrameRect();
  double x1 = tempRect.pos.x - tempRect.width / 2;
  double y1 = tempRect.pos.y - tempRect.height / 2;
  double x2 = tempRect.pos.x + tempRect.width / 2;
  double y2 = tempRect.pos.y + tempRect.height / 2;
  for (size_t i = 1; i < size_; ++i)
  {
    tempRect = shapesArray_[i]->getFrameRect();
    x1 = std::min(x1, tempRect.pos.x - tempRect.width / 2);
    x2 = std::max(x2, tempRect.pos.x + tempRect.width / 2);
    y1 = std::min(y1, tempRect.pos.y - tempRect.height / 2);
    y2 = std::max(y2, tempRect.pos.y + tempRect.height / 2);
  }
  return {{(x1 + x2) / 2, (y1 + y2) / 2}, x2 - x1, y2 - y1};
}

double vdovina::CompositeShape::getArea() const
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }
  double area = 0.0;
  for (size_t i = 0; i < size_; ++i)
  {
    area += shapesArray_[i]->getArea();
  }
  return area;
}

size_t vdovina::CompositeShape::size() const
{
  return size_;
}

void vdovina::CompositeShape::move(const vdovina::point_t &centre_p)
{
  move(centre_p.x - getFrameRect().pos.x, centre_p.y - getFrameRect().pos.y);
}

void vdovina::CompositeShape::move(double dx, double dy)
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }
  for (size_t i = 0; i < size_; ++i)
  {
    shapesArray_[i]->move(dx, dy);
  }
}
void vdovina::CompositeShape::scale(double factor)
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }
  if(factor <= 0)
  {
    throw std::invalid_argument("Factor should be > 0");
  }
  const rectangle_t rect = getFrameRect();
  for (size_t i = 0; i < size_; ++i)
  {
    shapesArray_[i]->scale(factor);
    const double DX = (shapesArray_[i]->getFrameRect().pos.x - rect.pos.x) * factor;
    const double DY = (shapesArray_[i]->getFrameRect().pos.y - rect.pos.y) * factor;
    shapesArray_[i]->move({rect.pos.x + DX, rect.pos.y + DY});
  }
}

vdovina::point_t vdovina::CompositeShape::getCentre() const
{
  if (size_ == 0)
  {
    throw std::logic_error("CompositeShape is empty");
  }
  return getFrameRect().pos;
}

void vdovina::CompositeShape::print(std::ostream &stream) const
{
  if (size_ == 0)
  {
    stream << "CompositeShape is empty";
  }
  else
  {
    stream << "Composite shape info""\n"
           << "Composite shape includes " << size_ << "shapes""\n"
           << "Center info: x = " << getCentre().x << " y = " << getCentre().y << "\n"
           << "Frame rect info: width = " << getFrameRect().width
           << " height = " << getFrameRect().height
           << " center x = " << getFrameRect().pos.x << " y = " << getFrameRect().pos.y << "\n";
    for (size_t i = 0; i < size_; ++i)
    {
      shapesArray_[i]->print(std::cout);
    }
    stream << "\n";
  }
}
