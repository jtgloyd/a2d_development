#ifndef A2D_POISSON_H
#define A2D_POISSON_H

#include "a2dmatops2d.h"
#include "a2dmatops3d.h"
#include "multiphysics/femapping.h"
#include "multiphysics/fespace.h"

namespace A2D {

/**
 * @brief Regular Poisson problem
 *
 * @tparam T Scalar type for the calculation
 * @tparam D Dimension of the problem
 */
template <typename T, A2D::index_t D>
class Poisson {
 public:
  // Spatial dimension
  static const A2D::index_t dim = D;

  // No data associated with this element
  static const A2D::index_t data_dim = 0;

  // Space for the finite-element data
  using DataSpace = A2D::FESpace<T, data_dim>;

  // Finite element space
  using FiniteElementSpace = A2D::FESpace<T, dim, A2D::H1Space<T, 1, dim>>;

  // Space for the element geometry - parametrized by H1 in 2D
  using FiniteElementGeometry = A2D::FESpace<T, dim, A2D::H1Space<T, dim, dim>>;

  // The type of matrix used to store data at each quadrature point
  using QMatType = A2D::SymmMat<T, FiniteElementSpace::ncomp>;

  // Mapping of the solution from the reference element to the physical element
  using SolutionMapping = A2D::InteriorMapping<T, dim>;

  /**
   * @brief Evaluate the weak form of the coefficients for nonlinear elasticity
   *
   * @param wdetJ The quadrature weight times determinant of the Jacobian
   * @param dobj The data at the quadrature point
   * @param geo The geometry evaluated at the current point
   * @param s The trial solution
   * @param coef Derivative of the weak form w.r.t. coefficients
   */
  A2D_INLINE_FUNCTION void weak(T wdetJ, const DataSpace& dobj,
                                const FiniteElementGeometry& geo,
                                const FiniteElementSpace& s,
                                FiniteElementSpace& coef) {
    const A2D::H1Space<T, 1, dim>& u = s.template get<0>();
    const A2D::Vec<T, dim>& u_grad = u.get_grad();

    A2D::H1Space<T, 1, dim>& v = coef.template get<0>();
    A2D::Vec<T, dim>& v_grad = v.get_grad();

    // Set the terms from the variational statement
    for (A2D::index_t k = 0; k < dim; k++) {
      v_grad(k) = wdetJ * u_grad(k);
    }
  }

  /**
   * @brief Construct the JacVecProduct functor
   *
   * This functor computes a Jacobian-vector product of the weak form
   *
   * @param pde The PDE object for this class
   * @param wdetJ The quadrature weight times determinant of the Jacobian
   * @param data The data at the quadrature point
   * @param geo The geometry at the quadrature point
   * @param s The solution at the quadrature point
   */
  class JacVecProduct {
   public:
    A2D_INLINE_FUNCTION JacVecProduct(const Poisson<T, D>& pde, T wdetJ,
                                      const DataSpace& data,
                                      const FiniteElementGeometry& geo,
                                      const FiniteElementSpace& s)
        : wdetJ(wdetJ) {}

    A2D_INLINE_FUNCTION void operator()(const FiniteElementSpace& p,
                                        FiniteElementSpace& Jp) {
      const A2D::H1Space<T, 1, dim>& u = p.template get<0>();
      const A2D::Vec<T, dim>& u_grad = u.get_grad();

      A2D::H1Space<T, 1, dim>& v = Jp.template get<0>();
      A2D::Vec<T, dim>& v_grad = v.get_grad();

      // Set the terms from the variational statement
      for (A2D::index_t k = 0; k < dim; k++) {
        v_grad(k) = wdetJ * u_grad(k);
      }
    }

   private:
    T wdetJ;
  };
};

/**
 * @brief Mixed Poisson problem discretization
 *
 * @tparam T Scalar type for the calculation
 * @tparam D Dimension of the problem
 */
template <typename T, A2D::index_t D>
class MixedPoisson {
 public:
  // Spatial dimension
  static const A2D::index_t dim = D;

  // No data associated with this element
  static const A2D::index_t data_dim = 0;

  // Space for the finite-element data
  typedef A2D::FESpace<T, data_dim> DataSpace;

  // Finite element space
  typedef A2D::FESpace<T, dim, A2D::HdivSpace<T, dim>, A2D::L2Space<T, 1, dim>>
      FiniteElementSpace;

  // Space for the element geometry - parametrized by H1 in 2D
  typedef A2D::FESpace<T, dim, A2D::H1Space<T, dim, dim>> FiniteElementGeometry;

  // The type of matrix used to store data at each quadrature point
  typedef A2D::SymmMat<T, FiniteElementSpace::ncomp> QMatType;

  // Mapping of the solution from the reference element to the physical element
  using SolutionMapping = A2D::InteriorMapping<T, dim>;

  /**
   * @brief Evaluate the weak form of the coefficients for nonlinear elasticity
   *
   * @param wdetJ The quadrature weight times determinant of the Jacobian
   * @param dobj The data at the quadrature point
   * @param geo The geometry evaluated at the current point
   * @param s The trial solution
   * @param coef Derivative of the weak form w.r.t. coefficients
   */
  A2D_INLINE_FUNCTION void weak(T wdetJ, const DataSpace& dobj,
                                const FiniteElementGeometry& geo,
                                const FiniteElementSpace& s,
                                FiniteElementSpace& coef) {
    // Field objects for solution functions
    const A2D::HdivSpace<T, dim>& sigma = s.template get<0>();
    const A2D::L2Space<T, 1, dim>& u = s.template get<1>();

    // Solution function values
    const A2D::Vec<T, dim>& sigma_val = sigma.get_value();
    const T& sigma_div = sigma.get_div();
    const T& u_val = u.get_value();

    // Test function values
    A2D::HdivSpace<T, dim>& tau = coef.template get<0>();
    A2D::L2Space<T, 1, dim>& v = coef.template get<1>();

    // Test function values
    A2D::Vec<T, dim>& tau_val = tau.get_value();
    T& tau_div = tau.get_div();
    T& v_val = v.get_value();

    // Set the terms from the variational statement
    for (A2D::index_t k = 0; k < dim; k++) {
      tau_val(k) = wdetJ * sigma_val(k);
    }

    tau_div = -wdetJ * u_val;
    v_val = wdetJ * sigma_div;
  }

  /**
   * @brief Construct a JacVecProduct functor
   *
   * This functor computes a Jacobian-vector product of the
   *
   * @param wdetJ The quadrature weight times determinant of the Jacobian
   * @param data The data at the quadrature point
   * @param s The solution at the quadrature point
   */
  class JacVecProduct {
   public:
    A2D_INLINE_FUNCTION JacVecProduct(const MixedPoisson<T, D>& pde, T wdetJ,
                                      const DataSpace& data,
                                      const FiniteElementGeometry& geo,
                                      const FiniteElementSpace& s)
        : wdetJ(wdetJ) {}

    A2D_INLINE_FUNCTION void operator()(const FiniteElementSpace& p,
                                        FiniteElementSpace& Jp) {
      // Field objects for solution functions
      const A2D::HdivSpace<T, dim>& sigma = p.template get<0>();
      const A2D::L2Space<T, 1, dim>& u = p.template get<1>();

      // Solution function values
      const A2D::Vec<T, dim>& sigma_val = sigma.get_value();
      const T& sigma_div = sigma.get_div();
      const T& u_val = u.get_value();

      // Test function values
      A2D::HdivSpace<T, dim>& tau = Jp.template get<0>();
      A2D::L2Space<T, 1, dim>& v = Jp.template get<1>();

      // Test function values
      A2D::Vec<T, dim>& tau_val = tau.get_value();
      T& tau_div = tau.get_div();
      T& v_val = v.get_value();

      // Set the terms from the variational statement
      for (A2D::index_t k = 0; k < dim; k++) {
        tau_val(k) = wdetJ * sigma_val(k);
      }

      tau_div = -wdetJ * u_val;
      v_val = wdetJ * sigma_div;
    }

   private:
    T wdetJ;
  };
};

}  // namespace A2D

#endif  // A2D_POISSON_H
