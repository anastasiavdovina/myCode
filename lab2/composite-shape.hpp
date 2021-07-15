#ifndef A_COMPOSITE_SHAPE_HPP
#define A_COMPOSITE_SHAPE_HPP

#include <memory>

#include "shape.hpp"

namespace vdovina
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &src);
    CompositeShape(CompositeShape &&src) noexcept;
    ~CompositeShape() override = default;
    CompositeShape& operator=(const CompositeShape& shape);
    CompositeShape& operator=(CompositeShape&& shape) noexcept;
    void add(const Ptr& shape);
    void remove(size_t index);
    rectangle_t getFrameRect() const override;
    point_t getCentre() const;
    double getArea() const override;
    Ptr operator [](size_t index);
    size_t size() const;
    void move(const point_t& centre_p);
    void move(double dx, double dy);
    void scale(double factor) override;
    void print(std::ostream& stream) const override;

  private:
    size_t size_;
    std::unique_ptr<Shape::Ptr[]> shapesArray_;
  };
}

#endif
