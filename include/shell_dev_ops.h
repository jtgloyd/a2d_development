//
// Created by James on 10/28/2022.
//

#include "a2dveccore3d.h"
#include <iostream>

#ifndef A2D_SHELL_DEV_OPS
#define A2D_SHELL_DEV_OPS

// NOTE: I changed the constant scalar inputs to store by copy to get rid of memory management issues.
// If they are done by reference for a reason, it will need to be changed back.
// TODO: if not, change this for all other operations.

template <typename T, int P>
void print_vector_no_endl(const A2D::Vec<T, P>& x) {
  for (int i = 0; i < P - 1; ++i) {
    std::cout << x(i) << ", ";
  }
  std::cout << x(P - 1);
};

template <typename T, int P, int Q>
void print_mat_no_endl(const A2D::Mat<T, P, Q>& A) {
  for (int i = 0; i < P - 1; ++i) {
    for (int j = 0; j < Q; ++j) {
      std::cout << A(i, j) << ", ";
    }
    std::cout << std::endl;
  }
  for (int j = 0; j < Q - 1; ++j) {
    std::cout << A(P - 1, j) << ", ";
  }
  std::cout << A(P - 1, Q - 1);
};

namespace A2D {

/**
 * ScalarMult operation (z = a * b)
 * */
template <int N, typename T>  // TODO: complete the ScalarMult operation (z = a * b)
class A2DScalarScalarMultExpr {
 public:
  A2DScalarScalarMultExpr(A2DScalar<N, T>& aObj,
                          const T& b,
                          A2DScalar<N, T>& zObj)
      : aObj(aObj), b(b), zObj(zObj) {
    zObj.value = aObj.value * b;
  };

  void reverse() {
//            input:
    const T& zb = zObj.bvalue;
    const T& a = aObj.value;
//            operations:
    aObj.bvalue += zb * b;

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_A2DScalarScalarMultExpr_reverse" << std::endl
              << "zb=" << zb << ", a=" << a << ", b=" << b << std::endl
              << "aObj.bvalue=" << aObj.bvalue << std::endl;*/
  };

  void hforward() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& ap = aObj.pvalue[i];
//                operations:
      zObj.pvalue[i] = ap * b;
    }
  };

  void hreverse() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& zh = zObj.hvalue[i];
//                operations:
      aObj.hvalue[i] += zh * b;
    }
  };

  A2DScalar<N, T>& aObj;
  const T b;
  A2DScalar<N, T>& zObj;
};

template <int N, typename T>
inline A2DScalarScalarMultExpr<N, T> ScalarMult(A2DScalar<N, T>& a,
                                                const T& b,
                                                A2DScalar<N, T>& z) {
  return A2DScalarScalarMultExpr<N, T>(a, b, z);
};

template <int N, typename T>
class A2DScalarA2DScalarMultExpr {
 public:
  A2DScalarA2DScalarMultExpr(A2DScalar<N, T>& aObj,
                             A2DScalar<N, T>& bObj,
                             A2DScalar<N, T>& zObj)
      : aObj(aObj), bObj(bObj), zObj(zObj) {
    zObj.value = aObj.value * bObj.value;
  };

  void reverse() {
//            input:
    const T& zb = zObj.bvalue;
    const T& a = aObj.value;
    const T& b = bObj.value;
//            operations:
    aObj.bvalue += zb * b;
    bObj.bvalue += zb * a;

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_A2DScalarA2DScalarMultExpr_reverse" << std::endl
              << "zb=" << zb << ", a=" << a << ", b=" << b << std::endl
              << "aObj.bvalue=" << aObj.bvalue << ", bObj.bvalue=" << bObj.bvalue << std::endl;*/
  };

  void hforward() {
//            input:
    const T& a = aObj.value;
    const T& b = bObj.value;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& ap = aObj.pvalue[i];
      const T& bp = bObj.pvalue[i];
//                operations:
      zObj.pvalue[i] = ap * b + a * bp;
    }
  };

  void hreverse() {
//            input:
    const T& zb = zObj.bvalue;
    const T& a = aObj.value;
    const T& b = bObj.value;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& ap = aObj.pvalue[i];
      const T& bp = bObj.pvalue[i];
      const T& zh = zObj.hvalue[i];
//                operations:
      aObj.hvalue[i] += zh * b + zb * bp;
      bObj.hvalue[i] += zh * a + zb * ap;
    }
  };

  A2DScalar<N, T>& aObj;
  A2DScalar<N, T>& bObj;
  A2DScalar<N, T>& zObj;
};

template <int N, typename T>
inline A2DScalarA2DScalarMultExpr<N, T> ScalarMult(A2DScalar<N, T>& a,
                                                   A2DScalar<N, T>& b,
                                                   A2DScalar<N, T>& z) {
  return A2DScalarA2DScalarMultExpr<N, T>(a, b, z);
};

/**
 *  Vec3ScaleDiv operation (v = (1/a) * x)
 * */
template <int N, typename T>  // TODO: complete the Vec3ScaleDiv operation (v = (1/a) * x)
class A2DVec3A2DScaleDivExpr {
 public:
  A2DVec3A2DScaleDivExpr(A2DVec<N, Vec<T, 3>>& xObj,
                         A2DScalar<N, T>& aObj,
                         A2DVec<N, Vec<T, 3>>& vObj)
      : xObj(xObj), aObj(aObj), vObj(vObj) {
    const T a = aObj.value;
    const Vec<T, 3>& x = xObj.value();
    Vec<T, 3>& v = vObj.value();

    v(0) = x(0) / a;
    v(1) = x(1) / a;
    v(2) = x(2) / a;
  };

  void reverse() {
//            input:
    const Vec<T, 3>& vb = vObj.bvalue();
    const Vec<T, 3>& x = xObj.value();
    const T& a = aObj.value;
//            output:
    Vec<T, 3>& xb = xObj.bvalue();
//            operations:
    aObj.bvalue += -Vec3DotCore<T, Vec<T, 3>>(vb, x) / (a * a);
    Vec3AXPYCore(1 / a, vb, xb, xb);  // TODO: check if a scale-add in place is faster

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_A2DVec3A2DScaleDivExpr_reverse" << std::endl
              << "a=" << a << std::endl;
    std::cout << "vb={";
    print_vector_no_endl(vb);
    std::cout << "}" << std::endl;
    std::cout << "x={";
    print_vector_no_endl(x);
    std::cout << "}" << std::endl
              << "aObj.bvalue=" << aObj.bvalue << std::endl
              << "xObj.bvalue={";
    print_vector_no_endl(xb);
    std::cout << "}" << std::endl;*/
  };

  void hforward() {
//            input:
    const Vec<T, 3>& x = xObj.value();
    const T& aInv = 1 / aObj.value;
    const T& aNegativeInvSquared = -aInv * aInv;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const Vec<T, 3>& xp = xObj.pvalue(i);
      const T& ap = aObj.pvalue[i];
//                output:
      Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
      Vec3AXPBYCore(ap * aNegativeInvSquared, x, aInv, xp, vp);
    }
  };

  void hreverse() {
//            input:
    const Vec<T, 3>& x = xObj.value();
    const Vec<T, 3>& vb = vObj.bvalue();
    const T& aInv = 1 / aObj.value;
    const T& aNegativeInvSquared = -aInv * aInv;
    const T& aInvCubed2 = 2 * aInv * aInv * aInv;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const Vec<T, 3>& xp = xObj.pvalue(i);
      const Vec<T, 3>& vh = vObj.hvalue(i);
      const T& ap = aObj.pvalue[i];
//                output:
      Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
      aObj.hvalue[i] +=
          (Vec3DotCore<T>(vh, x) * aNegativeInvSquared) +
              (Vec3DotCore<T>(vb, x) * aInvCubed2 * ap) +
              (Vec3DotCore<T>(vb, xp) * aNegativeInvSquared);
      Vec3AXPBYIncrementCore(aInv, vh, ap * aNegativeInvSquared, vb, xh);
    }
  };

  A2DVec<N, Vec<T, 3>>& xObj;
  A2DScalar<N, T>& aObj;
  A2DVec<N, Vec<T, 3>>& vObj;
};

template <int N, typename T>
inline A2DVec3A2DScaleDivExpr<N, T> Vec3ScaleDiv(A2DVec<N, Vec<T, 3>>& x,
                                                 A2DScalar<N, T>& a,
                                                 A2DVec<N, Vec<T, 3>>& v) {
  return A2DVec3A2DScaleDivExpr<N, T>(x, a, v);
};

/**
 *  ScalarAxpay operation (z = a * (x + y))
 * */
template <int N, typename T>  // TODO: complete the ScalarAxpay operation (z = a * (x + y))
class ScalarA2DScalarA2DScalarAxpayExpr {
 public:
  ScalarA2DScalarA2DScalarAxpayExpr(const T& a,
                                    A2DScalar<N, T>& xObj,
                                    A2DScalar<N, T>& yObj,
                                    A2DScalar<N, T>& zObj)
      : a{a}, xObj(xObj), yObj(yObj), zObj(zObj) {
    zObj.value = a * (xObj.value + yObj.value);
  };

  void reverse() {
//            input:
    const T& zb = zObj.bvalue;
//            operations:
    xObj.bvalue += zb * a;
    yObj.bvalue += zb * a;

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_ScalarA2DScalarA2DScalarAxpayExpr_reverse" << std::endl
              << "zb=" << zb << ", a=" << a << std::endl
              << "xObj.bvalue=" << xObj.bvalue << ", yObj.bvalue=" << yObj.bvalue << std::endl;*/
  };

  void hforward() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& xppyp = xObj.pvalue[i] + yObj.pvalue[i];
//                operations:
      zObj.pvalue[i] = a * xppyp;
    }
  };

  void hreverse() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& zh = zObj.hvalue[i];
//                operations:
      xObj.hvalue[i] += zh * a;
      yObj.hvalue[i] += zh * a;
    }
  };

  const T a;
  A2DScalar<N, T>& xObj;
  A2DScalar<N, T>& yObj;
  A2DScalar<N, T>& zObj;
};

template <int N, typename T>
inline ScalarA2DScalarA2DScalarAxpayExpr<N, T> ScalarAxpay(const T& a,
                                                           A2DScalar<N, T>& x,
                                                           A2DScalar<N, T>& y,
                                                           A2DScalar<N, T>& z) {
  return ScalarA2DScalarA2DScalarAxpayExpr<N, T>(a, x, y, z);
};

template <int N, typename T>
class A2DScalarA2DScalarA2DScalarAxpayExpr {
 public:
  A2DScalarA2DScalarA2DScalarAxpayExpr(A2DScalar<N, T>& aObj,
                                       A2DScalar<N, T>& xObj,
                                       A2DScalar<N, T>& yObj,
                                       A2DScalar<N, T>& zObj)
      : aObj(aObj), xObj(xObj), yObj(yObj), zObj(zObj) {
    zObj.value = aObj.value * (xObj.value + yObj.value);
  };

  void reverse() {
//            input:
    const T& zb = zObj.bvalue;
    const T& a = aObj.value;
//            operations:
    aObj.bvalue += zb * (xObj.value + yObj.value);
    xObj.bvalue += zb * a;
    yObj.bvalue += zb * a;

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_A2DScalarA2DScalarA2DScalarAxpayExpr_reverse" << std::endl
              << "zb=" << zb << ", a=" << a << ", x=" << xObj.value << ", y=" << xObj.value << std::endl
              << "aObj.bvalue=" << aObj.bvalue << ", xObj.bvalue=" << xObj.bvalue << ", yObj.bvalue=" << yObj.bvalue
              << std::endl;*/
  };

  void hforward() {
//            input:
    const T& xpy = xObj.value + yObj.value;
    const T& a = aObj.value;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& xppyp = xObj.pvalue[i] + yObj.pvalue[i];
      const T& ap = aObj.pvalue[i];
//                operations:
      zObj.pvalue[i] = ap * xpy + a * xppyp;
    }
  };

  void hreverse() {
//            input:
    const T& xpy = xObj.value + yObj.value;
    const T& zb = zObj.bvalue;
    const T& a = aObj.value;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& xppyp = xObj.pvalue[i] + yObj.pvalue[i];
      const T& zh = zObj.hvalue[i];
      const T& ap = aObj.pvalue[i];
//                operations:
      aObj.hvalue[i] += zh * xpy + zb * xppyp;
      xObj.hvalue[i] += zh * a + zb * ap;
      yObj.hvalue[i] += zh * a + zb * ap;
    }
  };

  A2DScalar<N, T>& aObj;
  A2DScalar<N, T>& xObj;
  A2DScalar<N, T>& yObj;
  A2DScalar<N, T>& zObj;
};

template <int N, typename T>
inline A2DScalarA2DScalarA2DScalarAxpayExpr<N, T> ScalarAxpay(A2DScalar<N, T>& a,
                                                              A2DScalar<N, T>& x,
                                                              A2DScalar<N, T>& y,
                                                              A2DScalar<N, T>& z) {
  return A2DScalarA2DScalarA2DScalarAxpayExpr<N, T>(a, x, y, z);
};

/**
 *  ScalarAxpby operation (z = a * x + b * y)
 * */
template <int N, typename T>  // TODO: complete the ScalarAxpby operation (z = a * x + b * y)
class ScalarA2DScalarScalarA2DScalarAxpbyExpr {
 public:
  ScalarA2DScalarScalarA2DScalarAxpbyExpr(const T& a,
                                          A2DScalar<N, T>& xObj,
                                          const T& b,
                                          A2DScalar<N, T>& yObj,
                                          A2DScalar<N, T>& zObj)
      : a(a), xObj(xObj), b(b), yObj(yObj), zObj(zObj) {
    zObj.value = a * xObj.value + b * yObj.value;
  };

  void reverse() {
//            input:
    const T& zb = zObj.bvalue;
//            operations:
    xObj.bvalue += zb * a;
    yObj.bvalue += zb * b;

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_ScalarA2DScalarScalarA2DScalarAxpbyExpr_reverse" << std::endl;
    std::cout << "zb=" << zb << ", a=" << a << ", b=" << b << std::endl
              << "xObj.bvalue=" << xObj.bvalue << ", yObj.bvalue=" << yObj.bvalue << std::endl;*/
  };

  void hforward() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& xp = xObj.pvalue[i];
      const T& yp = yObj.pvalue[i];
//                operations:
      zObj.pvalue[i] = a * xp + b * yp;
    }
  };

  void hreverse() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& zh = zObj.hvalue[i];
//                operations:
      xObj.hvalue[i] += zh * a;
      yObj.hvalue[i] += zh * b;
    }
  };

  const T a;
  A2DScalar<N, T>& xObj;
  const T b;
  A2DScalar<N, T>& yObj;
  A2DScalar<N, T>& zObj;
};

template <int N, typename T>
inline ScalarA2DScalarScalarA2DScalarAxpbyExpr<N, T> ScalarAxpby(const T& a,
                                                                 A2DScalar<N, T>& x,
                                                                 const T& b,
                                                                 A2DScalar<N, T>& y,
                                                                 A2DScalar<N, T>& z) {
  return ScalarA2DScalarScalarA2DScalarAxpbyExpr<N, T>(a, x, b, y, z);
};

template <int N, typename T>
class A2DScalarA2DScalarA2DScalarA2DScalarAxpbyExpr {
 public:
  A2DScalarA2DScalarA2DScalarA2DScalarAxpbyExpr(A2DScalar<N, T>& aObj,
                                                A2DScalar<N, T>& xObj,
                                                A2DScalar<N, T>& bObj,
                                                A2DScalar<N, T>& yObj,
                                                A2DScalar<N, T>& zObj)
      : aObj(aObj), xObj(xObj), bObj(bObj), yObj(yObj), zObj(zObj) {
    zObj.value = aObj.value * xObj.value + bObj.value * yObj.value;
  };

  void reverse() {
//            input:
    const T& zb = zObj.bvalue;
//            operations:
    aObj.bvalue += zb * xObj.value;
    xObj.bvalue += zb * aObj.value;
    bObj.bvalue += zb * yObj.value;
    yObj.bvalue += zb * bObj.value;

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_A2DScalarA2DScalarA2DScalarA2DScalarAxpbyExpr_reverse" << std::endl;
    std::cout << "zb=" << zb << ", a=" << aObj.value << ", b=" << bObj.value
              << ", x=" << xObj.value << ", y=" << yObj.value << std::endl
              << "aObj.bvalue=" << aObj.bvalue << ", bObj.bvalue=" << bObj.bvalue
              << ", xObj.bvalue=" << xObj.bvalue << ", yObj.bvalue=" << yObj.bvalue << std::endl;*/
  };

  void hforward() {
//            input:
    const T& a = aObj.value;
    const T& x = xObj.value;
    const T& b = bObj.value;
    const T& y = yObj.value;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& ap = aObj.pvalue[i];
      const T& xp = xObj.pvalue[i];
      const T& bp = bObj.pvalue[i];
      const T& yp = yObj.pvalue[i];
//                operations:
      zObj.pvalue[i] = ap * x + a * xp + bp * y + b * yp;
    }
  };

  void hreverse() {
//            input:
    const T& a = aObj.value;
    const T& x = xObj.value;
    const T& b = bObj.value;
    const T& y = yObj.value;
    const T& zb = zObj.bvalue;
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& ap = aObj.pvalue[i];
      const T& xp = xObj.pvalue[i];
      const T& bp = bObj.pvalue[i];
      const T& yp = yObj.pvalue[i];
      const T& zh = zObj.hvalue[i];
//                operations:
      aObj.hvalue[i] += zh * x + zb * xp;
      xObj.hvalue[i] += zh * a + zb * ap;
      bObj.hvalue[i] += zh * y + zb * yp;
      yObj.hvalue[i] += zh * b + zb * bp;
    }
  };

  A2DScalar<N, T>& aObj;
  A2DScalar<N, T>& xObj;
  A2DScalar<N, T>& bObj;
  A2DScalar<N, T>& yObj;
  A2DScalar<N, T>& zObj;
};

template <int N, typename T>
inline A2DScalarA2DScalarA2DScalarA2DScalarAxpbyExpr<N, T> ScalarAxpby(A2DScalar<N, T>& a,
                                                                       A2DScalar<N, T>& x,
                                                                       A2DScalar<N, T>& b,
                                                                       A2DScalar<N, T>& y,
                                                                       A2DScalar<N, T>& z) {
  return A2DScalarA2DScalarA2DScalarA2DScalarAxpbyExpr<N, T>(a, x, b, y, z);
};

/**
 *  MatInnerProduct operation (a = x.A.y)
 * */
template <typename T, int P, int Q>
// TODO: inspect this to see how it's compiled
inline T MatInnerProductCore(const Mat<T, P, Q>& A,
                             const Vec<T, P>& x,
                             const Vec<T, Q>& y) {
  T a{0}, b;
  for (int i = 0; i < P; ++i) {
    b = 0;
    for (int j = 0; j < Q; ++j) {
      b += A(i, j) * y(j);
    }
    a += b * x(i);
  }
  return a;
};

template <typename T, int P, int Q>
// TODO: inspect this to see how it's compiled
inline void VecOuterProductScaleCore(const T& a,
                                     const Vec<T, P>& x,
                                     const Vec<T, Q>& y,
                                     Mat<T, P, Q>& C) {
  for (int i = 0; i < P; ++i) {
    for (int j = 0; j < Q; ++j) {
      C(i, j) = a * x(i) * y(j);
    }
  }
};

template <typename T, int P, int Q>
// TODO: inspect this to see how it's compiled
inline void VecOuterProductScaleIncrementCore(const T& a,
                                              const Vec<T, P>& x,
                                              const Vec<T, Q>& y,
                                              Mat<T, P, Q>& C) {
  for (int i = 0; i < P; ++i) {
    for (int j = 0; j < Q; ++j) {
      C(i, j) += a * x(i) * y(j);
    }
  }
};

template <typename T, int P, int Q>
// Note: this is an in-place operation on v, so it uses increment assignment
// TODO: inspect this to see how it's compiled
inline void MatVecScaleMultCore(const T& a,
                                const Mat<T, P, Q>& A,
                                const Vec<T, Q>& x,
                                Vec<T, P>& v) {
  for (int i = 0; i < P; ++i) {
    for (int j = 0; j < Q; ++j) {
      v(i) += a * A(i, j) * x(j);
      // TODO: This can be done more efficiently by changing loop order and multiplying x and a first
    }
  }
};

template <typename T, int P, int Q>
// Note: this is an in-place operation on v, so it uses increment assignment
// TODO: inspect this to see how it's compiled
inline void MatTransVecScaleMultCore(const T& a,
                                     const Mat<T, P, Q>& A,
                                     const Vec<T, P>& x,
                                     Vec<T, Q>& v) {
  for (int i = 0; i < Q; ++i) {
    for (int j = 0; j < P; ++j) {
      v(i) += a * A(j, i) * x(j);
      // TODO: This can be done more efficiently by changing loop order and multiplying x and a first
    }
  }
};

template <typename T, int P>
// TODO: inspect this to see how it's compiled
inline T VecDotCore(const Vec<T, P>& x,
                    const Vec<T, P>& y) {
  T a{0};
  for (int i = 0; i < P; ++i) {
    a += x(i) * y(i);
  }
  return a;
};

template <typename T, int P>
// Note: this is an in-place operation on v, so it uses increment assignment
// TODO: inspect this to see how it's compiled
inline void VecAXPYIncrementCore(const T& a,
                                 const Vec<T, P>& x,
                                 const Vec<T, P>& y,
                                 Vec<T, P>& v) {
  for (int i = 0; i < P; ++i) {
    v(i) += a * x(i) + y(i);
  }
};

template <typename T, int P>
// TODO: inspect this to see how it's compiled
inline void VecAXPYCore(const T& a,
                        const Vec<T, P>& x,
                        const Vec<T, P>& y,
                        Vec<T, P>& v) {
  for (int i = 0; i < P; ++i) {
    v(i) = a * x(i) + y(i);
  }
};

template <typename T, int P>
// Note: this is an in-place operation on v, so it uses increment assignment
// TODO: inspect this to see how it's compiled
inline void VecAXPBYIncrementCore(const T& a,
                                  const Vec<T, P>& x,
                                  const T& b,
                                  const Vec<T, P>& y,
                                  Vec<T, P>& v) {
  for (int i = 0; i < P; ++i) {
    v(i) += a * x(i) + b * y(i);
  }
};

template <typename T, int P>
// TODO: inspect this to see how it's compiled
inline void VecAXPBYCore(const T& a,
                         const Vec<T, P>& x,
                         const T& b,
                         const Vec<T, P>& y,
                         Vec<T, P>& v) {
  for (int i = 0; i < P; ++i) {
    v(i) = a * x(i) + b * y(i);
  }
};

template <typename T, int P>
// TODO: inspect this to see how it's compiled
inline void VecScaleCore(const T& a,
                         const Vec<T, P>& x,
                         Vec<T, P>& v) {
  for (int i = 0; i < P; ++i) {
    v(i) = a * x(i);
  }
};

template <int N, typename T, int P, int Q>  // TODO: complete the MatInnerProduct operation (a = x.A.y)
class MatA2DVecA2DVecInnerProductExpr {
 public:
  MatA2DVecA2DVecInnerProductExpr(const Mat<T, P, Q>& A,
                                  A2DVec<N, Vec<T, P>>& xObj,
                                  A2DVec<N, Vec<T, Q>>& yObj,
                                  A2DScalar<N, T>& aObj)
      : A(A), xObj(xObj), yObj(yObj), aObj(aObj) {
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    aObj.value = MatInnerProductCore(A, x, y);
  };

  void reverse() {
//            input:
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    const T& ab = aObj.bvalue;
//            output:
    Vec<T, P>& xb = xObj.bvalue();
    Vec<T, Q>& yb = yObj.bvalue();
//            operations:
    MatVecScaleMultCore<T, P, Q>(ab, A, y, xb);
    MatTransVecScaleMultCore<T, P, Q>(ab, A, x, yb);

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_MatA2DVecA2DVecInnerProductExpr_reverse" << std::endl;
    std::cout << "ab=" << ab << std::endl;
    std::cout << "A={";
    print_mat_no_endl(A);
    std::cout << "}";
    std::cout << std::endl;
    std::cout << "x={";
    print_vector_no_endl(x);
    std::cout << "}";
    std::cout << std::endl;
    std::cout << "y={";
    print_vector_no_endl(y);
    std::cout << "}";
    std::cout << std::endl;
    std::cout << "xb={";
    print_vector_no_endl(xb);
    std::cout << "}";
    std::cout << std::endl;
    std::cout << "yb={";
    print_vector_no_endl(yb);
    std::cout << "}";
    std::cout << std::endl;*/
  };

  void hforward() {
//            input:
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    Vec<T, P> Ay;
    Vec<T, Q> xA;
    MatVecScaleMultCore<T, P, Q>(1, A, y, Ay);
    MatTransVecScaleMultCore<T, P, Q>(1, A, x, xA);
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const Vec<T, P>& xp = xObj.pvalue(i);
      const Vec<T, Q>& yp = yObj.pvalue(i);
//                operations:
      aObj.pvalue[i] = VecDotCore(xp, Ay) + VecDotCore(xA, yp);
    }
  };

  void hreverse() {
//            input:
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    const T& ab = aObj.bvalue;
    Vec<T, P> Ay;
    Vec<T, Q> xA;
    MatVecScaleMultCore<T, P, Q>(1, A, y, Ay);
    MatTransVecScaleMultCore<T, P, Q>(1, A, x, xA);
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const Vec<T, P>& xp = xObj.pvalue(i);
      const Vec<T, Q>& yp = yObj.pvalue(i);
      const T& ah = aObj.hvalue[i];
//                Interstitial values:
      Vec<T, P> Ayp;
      Vec<T, Q> xpA;
//                output:
      Vec<T, P>& xh = xObj.hvalue(i);
      Vec<T, Q>& yh = yObj.hvalue(i);
//                operations:
      MatVecScaleMultCore<T, P, Q>(1, A, yp, Ayp);
      VecAXPBYIncrementCore(ah, Ay, ab, Ayp, xh);

      MatTransVecScaleMultCore<T, P, Q>(1, A, xp, xpA);
      VecAXPBYIncrementCore(ah, xA, ab, xpA, yh);
    }
  };

  const Mat<T, P, Q>& A;  // TODO: see if this needs to be stored by copy (doesn't appear so)
  A2DVec<N, Vec<T, P>>& xObj;
  A2DVec<N, Vec<T, Q>>& yObj;
  A2DScalar<N, T>& aObj;
};

template <int N, typename T, int P, int Q>
inline MatA2DVecA2DVecInnerProductExpr<N, T, P, Q> MatInnerProduct(const Mat<T, P, Q>& A,
                                                                   A2DVec<N, Vec<T, P>>& x,
                                                                   A2DVec<N, Vec<T, Q>>& y,
                                                                   A2DScalar<N, T>& a) {
  return MatA2DVecA2DVecInnerProductExpr<N, T, P, Q>(A, x, y, a);
};

template <int N, typename T, int P, int Q>
class A2DMatA2DVecA2DVecInnerProductExpr {
 public:
  A2DMatA2DVecA2DVecInnerProductExpr(A2DMat<N, Mat<T, P, Q>>& AObj,
                                     A2DVec<N, Vec<T, P>>& xObj,
                                     A2DVec<N, Vec<T, Q>>& yObj,
                                     A2DScalar<N, T>& aObj)
      : AObj(AObj), xObj(xObj), yObj(yObj), aObj(aObj) {
    const Mat<T, P, Q>& A = AObj.value();
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    aObj.value = MatInnerProductCore(A, x, y);
  };

  void reverse() {
//            input:
    const Mat<T, P, Q>& A = AObj.value();
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    const T& ab = aObj.bvalue;
//            output:
    Vec<T, P>& xb = xObj.bvalue();
    Vec<T, Q>& yb = yObj.bvalue();
    Mat<T, P, Q>& Ab = AObj.bvalue();
//            operations:
    MatVecScaleMultCore<T, P, Q>(ab, A, y, xb);
    VecOuterProductScaleIncrementCore(ab, x, y, Ab);
    MatTransVecScaleMultCore<T, P, Q>(ab, A, x, yb);

    /*std::cout << "****************************************************************" << std::endl
              << "          TODO: UNQ_TODO_32473247542955" << std::endl;*/
  };

  void hforward() {
//            input:
    const Mat<T, P, Q>& A = AObj.value();
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    Vec<T, P> Ay;
    Vec<T, Q> xA;
    MatVecScaleMultCore<T, P, Q>(1, A, y, Ay);
    MatTransVecScaleMultCore<T, P, Q>(1, A, x, xA);
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const Mat<T, P, Q>& Ap = AObj.pvalue(i);
      const Vec<T, P>& xp = xObj.pvalue(i);
      const Vec<T, Q>& yp = yObj.pvalue(i);
//                operations:
      aObj.pvalue[i] = VecDotCore(xp, Ay) + MatInnerProductCore(Ap, x, y) + VecDotCore(xA, yp);
    }
  };

  void hreverse() {
//            input:
    const Mat<T, P, Q>& A = AObj.value();
    const Vec<T, P>& x = xObj.value();
    const Vec<T, Q>& y = yObj.value();
    const T& ab = aObj.bvalue;
    Vec<T, P> Ay;
    Vec<T, Q> xA;
    MatVecScaleMultCore<T, P, Q>(1, A, y, Ay);
    MatTransVecScaleMultCore<T, P, Q>(1, A, x, xA);
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const Mat<T, P, Q>& Ap = AObj.pvalue(i);
      const Vec<T, P>& xp = xObj.pvalue(i);
      const Vec<T, Q>& yp = yObj.pvalue(i);
      const T& ah = aObj.hvalue[i];
//                Interstitial values:
      Vec<T, P> Apy, Ayp, ApyAyp;
      Vec<T, Q> xAp, xpA, xApxpA;
//                output:
      Mat<T, P, Q>& Ah = AObj.hvalue(i);
      Vec<T, P>& xh = xObj.hvalue(i);
      Vec<T, Q>& yh = yObj.hvalue(i);
//                operations:
      MatVecScaleMultCore<T, P, Q>(1, Ap, y, Apy);
      MatVecScaleMultCore<T, P, Q>(1, A, yp, Ayp);
      VecAXPYCore<T, P>(1, Apy, Ayp, ApyAyp);
      VecAXPBYIncrementCore(ah, Ay, ab, ApyAyp, xh);

      MatTransVecScaleMultCore<T, P, Q>(1, Ap, x, xAp);
      MatTransVecScaleMultCore<T, P, Q>(1, A, xp, xpA);
      VecAXPYCore<T, Q>(1, xAp, xpA, xApxpA);
      VecAXPBYIncrementCore(ah, xA, ab, xApxpA, yh);

      VecOuterProductScaleIncrementCore(ah, x, y, Ah);
      VecOuterProductScaleIncrementCore(ab, xp, y, Ah);
      VecOuterProductScaleIncrementCore(ab, x, yp, Ah);
    }
  };

  A2DMat<N, Mat<T, P, Q>>& AObj;
  A2DVec<N, Vec<T, P>>& xObj;
  A2DVec<N, Vec<T, Q>>& yObj;
  A2DScalar<N, T>& aObj;
};

template <int N, typename T, int P, int Q>
inline A2DMatA2DVecA2DVecInnerProductExpr<N, T, P, Q> MatInnerProduct(A2DMat<N, Mat<T, P, Q>>& A,
                                                                      A2DVec<N, Vec<T, P>>& x,
                                                                      A2DVec<N, Vec<T, Q>>& y,
                                                                      A2DScalar<N, T>& a) {
  return A2DMatA2DVecA2DVecInnerProductExpr<N, T, P, Q>(A, x, y, a);
};

/**
 * Vec5ScalarAssembly operation (v = {x0, x1, x2, x3, x4})
 * */
template <int N, typename T>  // TODO: complete the Vec5ScalarAssembly operation (v = {x0, x1, x2, x3, x4})
class A2DScalar5VecAssemblyExpr {
 public:
  A2DScalar5VecAssemblyExpr(A2DScalar<N, T>& x0Obj,
                            A2DScalar<N, T>& x1Obj,
                            A2DScalar<N, T>& x2Obj,
                            A2DScalar<N, T>& x3Obj,
                            A2DScalar<N, T>& x4Obj,
                            A2DVec<N, Vec<T, 5>>& vObj)
      : vObj(vObj), x0Obj(x0Obj), x1Obj(x1Obj), x2Obj(x2Obj), x3Obj(x3Obj), x4Obj(x4Obj) {
    Vec<T, 5>& v = vObj.value();
    v(0) = x0Obj.value;
    v(1) = x1Obj.value;
    v(2) = x2Obj.value;
    v(3) = x3Obj.value;
    v(4) = x4Obj.value;
  };

  void reverse() {
//            input:
    const Vec<T, 5>& vb = vObj.bvalue();
//            operations:
    x0Obj.bvalue += vb(0);
    x1Obj.bvalue += vb(1);
    x2Obj.bvalue += vb(2);
    x3Obj.bvalue += vb(3);
    x4Obj.bvalue += vb(4);

    /*std::cout << "****************************************************************" << std::endl
              << "          " << this << ":UNQ_A2DScalar5VecAssemblyExpr_reverse" << std::endl;
    std::cout << "vb={";
    print_vector_no_endl(vb);
    std::cout << "}" << std::endl;
    std::cout << "x0Obj.bvalue=" << x0Obj.bvalue
              << ",   x1Obj.bvalue=" << x1Obj.bvalue
              << ",   x2Obj.bvalue=" << x2Obj.bvalue
              << ",   x3Obj.bvalue=" << x3Obj.bvalue
              << ",   x4Obj.bvalue=" << x4Obj.bvalue << std::endl;*/
  };

  void hforward() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const T& x0p = x0Obj.pvalue[i];
      const T& x1p = x1Obj.pvalue[i];
      const T& x2p = x2Obj.pvalue[i];
      const T& x3p = x3Obj.pvalue[i];
      const T& x4p = x4Obj.pvalue[i];
//                output:
      Vec<T, 5>& vp = vObj.pvalue(i);
//                operations:
      vp(0) = x0p;
      vp(1) = x1p;
      vp(2) = x2p;
      vp(3) = x3p;
      vp(4) = x4p;
    }
  };

  void hreverse() {
//            main loop:
    for (int i = 0; i < N; i++) {
//                input:
      const Vec<T, 5>& vh = vObj.hvalue(i);
//                operations:
      x0Obj.hvalue[i] += vh(0);
      x1Obj.hvalue[i] += vh(1);
      x2Obj.hvalue[i] += vh(2);
      x3Obj.hvalue[i] += vh(3);
      x4Obj.hvalue[i] += vh(4);
    }
  };

  A2DVec<N, Vec<T, 5>>& vObj;
  A2DScalar<N, T>& x0Obj;
  A2DScalar<N, T>& x1Obj;
  A2DScalar<N, T>& x2Obj;
  A2DScalar<N, T>& x3Obj;
  A2DScalar<N, T>& x4Obj;
};

template <int N, typename T>
inline A2DScalar5VecAssemblyExpr<N, T> Vec5ScalarAssembly(A2DScalar<N, T>& x0,
                                                          A2DScalar<N, T>& x1,
                                                          A2DScalar<N, T>& x2,
                                                          A2DScalar<N, T>& x3,
                                                          A2DScalar<N, T>& x4,
                                                          A2DVec<N, Vec<T, 5>>& v) {
  return A2DScalar5VecAssemblyExpr<N, T>(v, x0, x1, x2, x3, x4);
};


// TODO: figure out how to do this at a later date.
/*template <int N, typename T, int D>  // TODO: make the VecScalarAssembly operation (v = {v1, v2, v3, ..., vD})
class A2DScalarVecAssemblyExpr {
  A2DScalarVecAssemblyExpr(A2DVec<N, Vec<T, D>>& vObj,
                           A2DScalar<N, T> x[D]){

    for (int i = 0; i < D; ++i) {
      v.value()(i) = x[i].value;
    }
  };
};
template <int N, typename T, int D>
A2DScalarVecAssemblyExpr<N, T, D> VecScalarAssembly(A2DVec<N, Vec<T, D>>& v, A2DScalar<N, T> x[D]) {
  return A2DScalarVecAssemblyExpr<N, T, D>(v, x);
};*/

}  // namespace A2D

#endif //A2D_SHELL_DEV_OPS
