#ifndef EOPI_PRIMITIVES_GEOMETRY_HPP_
#define EOPI_PRIMITIVES_GEOMETRY_HPP_

#include <algorithm>
#include <cstdint>

#include <iostream>

namespace eopi {
namespace primitives {

struct Point {
  std::int64_t x, y;

  // pairwise subtraction
  Point operator-=(Point const &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  };

  friend Point operator-(Point lhs, Point const &rhs) {
    lhs -= rhs;
    return lhs;
  }

  friend bool operator<(Point const &lhs, Point const &rhs) {
    return lhs.x < rhs.x && lhs.y < rhs.y;
  }

  friend bool operator<=(Point const &lhs, Point const &rhs) {
    return lhs.x <= rhs.x && lhs.y <= rhs.y;
  }

  Point max(Point const &other) const {
    return {std::max(x, other.x), std::max(y, other.y)};
  }

  Point min(Point const &other) const {
    return {std::min(x, other.x), std::min(y, other.y)};
  }

  friend std::ostream &operator<<(std::ostream &os, Point const &p) {
    os << "[" << p.x << "," << p.y << "]";
    return os;
  }
};

struct Rectangle {
  Point lower_left;
  Point upper_right;

  // return the size of the rectangle
  std::uint64_t area() const {
    auto const delta = upper_right - lower_left;
    return delta.x * delta.y;
  }

  bool contains(Point const &point) const {
    return lower_left <= point && point <= upper_right;
  }

  bool does_intersect(Rectangle const &other) const {
    return lower_left.max(other.lower_left) <=
           upper_right.min(other.upper_right);
  }

  Rectangle intersect(Rectangle const &other) const {
    if (!does_intersect(other))
      throw("Invalid argument, Rectangles do not intersect");
    return {lower_left.max(other.lower_left),
            upper_right.min(other.upper_right)};
  }

  friend std::ostream &operator<<(std::ostream &os, Rectangle const &rec) {
    os << "[" << rec.lower_left << "," << rec.upper_right << "]";
    return os;
  }
};

} // namespace primitives
} // namespace eopi

#endif // EOPI_PRIMITIVES_GEOMETRY_HPP_
