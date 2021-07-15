#include <iostream>
#include <memory>
#include <stdexcept>

#include "base-types.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

int main()
{
  const double factor = 2.0;
  const vdovina::point_t rectCenter = {5.34, 10.35};
  try
  {
    std::cout << "Rectangle: ""\n";
    const std::shared_ptr<vdovina::Shape> rectangle(new vdovina::Rectangle({rectCenter}, 13.62, 15.7));
    rectangle->print(std::cout);
    std::cout << "\n";
    rectangle->scale(factor);
    std::cout << "Rectangle after scaling";
    rectangle->print(std::cout);
    std::cout << "\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  const vdovina::point_t circleCenter = {8.14, 3.65};
  try
  {
    std::cout << "Circle: \n";
    const std::shared_ptr<vdovina::Shape> circle(new vdovina::Circle({circleCenter}, 4.44));
    circle->print(std::cout);
    std::cout << "\n";
    circle->scale(factor);
    std::cout << "Circle after scaling";
    circle->print(std::cout);
    std::cout << "\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  const vdovina::point_t circleCenter1 = {3.78, 10.32};
  try
  {
    std::cout << "Circle1: \n";
    const std::shared_ptr<vdovina::Circle> circle1(new vdovina::Circle({circleCenter1}, 7.67));
    circle1->print(std::cout);
    std::cout << "\n";
    circle1->scale(factor);
    std::cout << "Circle1 after scaling";
    circle1->print(std::cout);
    std::cout << "\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  const std::shared_ptr<vdovina::Shape> rectangle(new vdovina::Rectangle({rectCenter}, 13.62, 15.7));
  const std::shared_ptr<vdovina::Shape> circle(new vdovina::Circle({circleCenter}, 4.44));
  const std::shared_ptr<vdovina::Circle> circle1(new vdovina::Circle({circleCenter1}, 7.67));
  vdovina::CompositeShape compShape;
  try
  {
    std::cout << "Composite shape: ""\n";
    compShape.add(rectangle);
    compShape.add(circle);
    compShape.add(circle1);
    compShape.print(std::cout);
    std::cout << "\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  catch (const std::logic_error& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  try
  {
    const double dX = 4.82;
    const double dY = 8.13;
    compShape.move(dX, dY);
    std::cout << "Composite shape after moving(dx, dy): ""\n";
    compShape.print(std::cout);
    std::cout << "\n";
    const vdovina::point_t newCenter = {3.18, 5.87};
    compShape.move(newCenter);
    std::cout << "Composite shape after moving(new center): ""\n";
    compShape.print(std::cout);
    std::cout << "\n";
  }
  catch (const std::logic_error& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  try
  {
    compShape.remove(2);
    std::cout << "Composite shape after removing second shape: ""\n";
    compShape.print(std::cout);
    std::cout << "\n";
  }
  catch (const std::out_of_range& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  try
  {
    std::cout << "Composite shape after scaling: ""\n";
    compShape.scale(factor);
    compShape.print(std::cout);
    std::cout << "\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  catch (const std::logic_error& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}
