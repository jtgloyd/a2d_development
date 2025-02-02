#ifndef A2D_FE_SOLUTION_H
#define A2D_FE_SOLUTION_H

#include <vector>

#include "a2dobjs.h"

namespace A2D {

/*
  The solution vector
*/
template <typename T>
class SolutionVector {
 public:
  SolutionVector(A2D::index_t ndof) : ndof(ndof), x(ndof, T(0.0)) {}
  T& operator[](A2D::index_t index) { return x[index]; }
  const T& operator[](A2D::index_t index) const { return x[index]; }

  index_t get_num_dof() const { return ndof; }

  void zero() { std::fill(x.begin(), x.end(), T(0.0)); }
  void fill(T val) { std::fill(x.begin(), x.end(), val); }

 private:
  const A2D::index_t ndof;
  std::vector<T> x;
};

}  // namespace A2D

#endif  // A2D_FE_SOLUTION_H