#ifndef SKYLIB_MATH_TRIANGULATE_H_
#define SKYLIB_MATH_TRIANGULATE_H_

#include <skylib/math/vector.h>
#include <vector>

namespace skylib {

class Triangulate {
 public:
  static bool Process(std::vector< Vector<2> > const& face,
                      std::vector< std::vector< Vector<2> > >& result);
  static float Area(std::vector< Vector<2> > const& face);
  static bool InsideTriangle(std::vector< Vector<2> > const& face,
                             Vector<2> const& point);

 private:
  static bool Snip(std::vector< Vector<2> > const& face, int u, int v, int w,
                   int n, int *V);
};

} // namespace skylib

#endif // SKYLIB_MATH_TRIANGULATE_H_
