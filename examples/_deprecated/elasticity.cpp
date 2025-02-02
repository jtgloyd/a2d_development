#include "fem/elasticity.h"

#include <cstdint>
#include <iomanip>
#include <iostream>

#include "a2d.h"

using namespace A2D;

template <typename I, typename T, class PDE, class Basis>
void test_data_adjoint_product(typename PDE::SolutionArray& u,
                               ElementBasis<I, T, PDE, Basis>& element,
                               double dh = 1e-30) {
  auto data = element.get_quad_data();
  auto dfddata = data.duplicate();
  auto pdata = data.duplicate();
  pdata->random();

  // Create the adjoint
  auto adj = u.duplicate();
  adj->random();

  // Compute the exact dot product
  dfddata->zero();
  element.add_adjoint_dfddata(*adj, *dfddata);
  T result = dfddata->dot(*pdata);

  // Now, compute the complex-step value
  data.axpy(T(0.0, dh), *pdata);

  auto res = u.duplicate();
  res->zero();
  element.add_residual(*res);
  T fd = (adj->dot(*res)).imag() / dh;

  std::printf("Complex-step result: %20.20e\t", fd.real());
  std::printf("Adjoint-data result: %20.20e\n", result.real());
}

template <typename I, typename T, class PDE, class DesignArray>
void test_adjoint_product(DesignArray& x,
                          std::shared_ptr<FEModel<I, T, PDE>> model,
                          double dh = 1e-30) {
  auto res = model->new_solution();
  auto adj = model->new_solution();
  adj->random();
  model->zero_bcs(adj);

  auto dfdx = x.duplicate();
  auto px = x.duplicate();
  px->random();

  // Compute the adjoint-residual product
  dfdx->zero();
  model->add_adjoint_dfdx(adj, dfdx);
  T result = dfdx->dot(*px);

  // Set the new values of the design variables
  x.axpy(T(0.0, dh), *px);
  model->set_design_vars(x);

  // Compute the complex-step
  res->zero();
  model->residual(res);
  T fd = (adj->dot(*res)).imag() / dh;

  std::printf("Complex-step result: %20.20e\t", fd.real());
  std::printf("Adjoint-data result: %20.20e\n", result.real());
}

/*
  Finite-element computations using templating/auto-diff and multi-dimensional
  arrays
*/
void main_body() {
  Timer timer("main()");
  using I = index_t;
  using T = A2D_complex_t<double>;
  using Basis = BasisOps<3, HexTriLinearBasisFunc, Hex8ptQuadrature>;
  using PDE = ElasticityPDEInfo<3, I, T>;

  const index_t nx = 32;
  const index_t ny = 32;
  const index_t nz = 32;
  const index_t nnodes = (nx + 1) * (ny + 1) * (nz + 1);
  const index_t nelems = nx * ny * nz;
  const index_t nbcs = (ny + 1) * (nz + 1);

  auto model = std::make_shared<FEModel<I, T, PDE>>(nnodes, nbcs);
  auto element = std::make_shared<LinElasticityElement<I, T, Basis>>(nelems);
  model->add_element(element);

  // Set the boundary conditions
  auto bcs = model->get_bcs();
  index_t index = 0;
  for (int k = 0; k < nz + 1; k++) {
    for (int j = 0; j < ny + 1; j++) {
      int i = 0;
      int node = i + (nx + 1) * (j + (ny + 1) * k);

      // Set the boundary conditions
      bcs(index, 0) = node;
      for (int ii = 0; ii < 3; ii++) {
        bcs(index, 1) |= 1U << ii;
      }
      index++;
    }
  }

  // Set the connectivity
  auto conn = element->get_conn();
  for (int k = 0; k < nz; k++) {
    for (int j = 0; j < ny; j++) {
      for (int i = 0; i < nx; i++) {
        int elem = i + nx * (j + ny * k);

        int conn_coord[8];
        for (int kk = 0, index = 0; kk < 2; kk++) {
          for (int jj = 0; jj < 2; jj++) {
            for (int ii = 0; ii < 2; ii++, index++) {
              conn_coord[index] =
                  (i + ii) + (nx + 1) * ((j + jj) + (ny + 1) * (k + kk));
            }
          }
        }

        // Convert to the correct connectivity
        conn(elem, 0) = conn_coord[0];
        conn(elem, 1) = conn_coord[1];
        conn(elem, 2) = conn_coord[3];
        conn(elem, 3) = conn_coord[2];

        conn(elem, 4) = conn_coord[4];
        conn(elem, 5) = conn_coord[5];
        conn(elem, 6) = conn_coord[7];
        conn(elem, 7) = conn_coord[6];
      }
    }
  }

  // Set the node locations
  auto X = model->get_nodes();
  for (int k = 0; k < nz + 1; k++) {
    for (int j = 0; j < ny + 1; j++) {
      for (int i = 0; i < nx + 1; i++) {
        int node = i + (nx + 1) * (j + (ny + 1) * k);

        X(node, 0) = 1.0 * i / nx;
        X(node, 1) = 1.0 * j / ny;
        X(node, 2) = 1.0 * k / nz;
      }
    }
  }

  // Set the node locations - Note: This must be done after setting the
  // connectivity!
  model->init();

  // Set the element
  T q = 5.0, E = 70e3, nu = 0.3;
  T density = 1.0, design_stress = 1e3;
  auto constitutive = std::make_shared<TopoIsoConstitutive<I, T, Basis>>(
      element, q, E, nu, density, design_stress);
  model->add_constitutive(constitutive);

  // Create the design vector
  auto x = std::make_shared<A2D::MultiArrayNew<T* [1]>>("x", model->nnodes);

  // Set the design variable values
  BLAS::fill(*x, 1.0);
  model->set_design_vars(x);

  // Set up the stress functional
  auto functional = std::make_shared<Functional<I, T, PDE>>();
  auto agg_functional =
      std::make_shared<TopoVonMisesAggregation<I, T, Basis>>(constitutive);
  functional->add_functional(agg_functional);

  // Compute the Jacobian matrix
  auto J = model->new_matrix();

  model->jacobian(J);

  int num_levels = 3;
  double omega = 0.6667;
  double epsilon = 0.0;
  bool print_info = true;
  auto amg = model->new_amg(num_levels, omega, epsilon, J, print_info);

  // Set the residuals and apply the boundary conditions
  auto solution = model->new_solution();
  auto residual = model->new_solution();
  BLAS::fill(*solution, 1.0);
  model->zero_bcs(solution);

  BLAS::zero(*residual);
  BSRMatVecMult(*J, *solution, *residual);
  model->zero_bcs(residual);

  // Compute the solution
  index_t monitor = 10;
  index_t max_iters = 80;
  BLAS::zero(*solution);
  amg->cg(*residual, *solution, monitor, max_iters);

  // Set the solution
  model->set_solution(solution);

  agg_functional->compute_offset();
  functional->eval_functional();

  // Compute the adjoint right-hand-side
  auto dfdu = model->new_solution();
  functional->eval_dfdu(dfdu);
  BLAS::scale(*dfdu, -1.0);
  model->zero_bcs(dfdu);

  // Compute the adjoint variables
  auto adjoint = model->new_solution();
  amg->mg(*dfdu, *adjoint, monitor, max_iters);

  // Complete the adjoint derivative
  auto dfdx =
      std::make_shared<A2D::MultiArrayNew<T* [1]>>("dfdx", model->nnodes);
  BLAS::zero(*dfdx);
  functional->eval_dfdx(dfdx);
  model->add_adjoint_dfdx(adjoint, dfdx);

  // Compute a projected derivative and test against complex step
  auto px = std::make_shared<A2D::MultiArrayNew<T* [1]>>("px", model->nnodes);
  BLAS::random(*px);
  T ans = BLAS::dot(*dfdx, *px);

  // Set the new desigh variable values
  double dh = 1e-30;
  BLAS::fill(*x, 1.0);
  BLAS::axpy(*x, T(0.0, dh), *px);
  model->set_design_vars(x);
  model->jacobian(J);
  amg->update();

  BLAS::zero(*solution);
  amg->cg(*residual, *solution, monitor, max_iters);

  // Set the solution
  model->set_solution(solution);

  // Compute the complex-step result
  T fd = functional->eval_functional().imag() / dh;

  std::printf("Complex-step result: %20.10e\n", fd.real());
  std::printf("Adjoint-data result: %20.10e\n", ans.real());
  std::printf("Relative error:      %20.10e\n",
              (ans.real() - fd.real()) / ans.real());

  // // Set the design variable values
  // x->fill(1.0);
  // model->set_design_vars(x);
  // test_data_adjoint_product(*solution, element);

  // // Set the design variable values
  // x->fill(1.0);
  // model->set_design_vars(x);
  // test_adjoint_product(x, model);

  // amg->testGalerkin();
  return;
}

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  { main_body(); }
  Kokkos::finalize();
  return 0;
}
