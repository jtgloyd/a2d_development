//
// Created by James on 10/15/2022.
//

#ifndef A2D_A2D_VEC_OPERATION_DEVELOPMENT_H
#define A2D_A2D_VEC_OPERATION_DEVELOPMENT_H

#include "a2dobjs.h"
#include "a2dtypes.h"
#include "a2dveccore3d.h"

// FOR: a2dvecops3d.h
namespace A2D {

    // TODO: change N to D in templates since we will likely want to use N for arbitrary size matrix and vector?
    //  so as to avoid confusion

    // TODO: change alpha naming (use aObj and a instead)

    /*
        Vec3Norm
        This represents the L2 norm (or 2 norm) of a 3 vector
        normObj = ||xObj||
    */
    template <int N, typename T>
    class A2DVec3NormExpr {
    public:
        A2DVec3NormExpr(A2DVec<N, Vec<T, 3>>& xObj,
                        A2DScalar<N, T>& normObj)
                : xObj(xObj), normObj(normObj) {
            const Vec<T, 3>& x = xObj.value();
            normObj.value = Vec3NormCore<T>(x);
            Vec3ScaleCore(1 / normObj.value, x, normX);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& n = normObj.value;
            const T& nb = normObj.bvalue;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3ScaleCore(nb / n, x, xb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& norm = normObj.value;
/*
//            main loop: (uses decrements because comparison to 0 is faster)
            for (int i = N - 1; i != 0; i--) {
//    //                input:
//                    const Vec<T, 3>& xp = xObj.pvalue(i);
//    //                output:
//                    T& normp = normObj.pvalue[i];
//    //                operations:
//                    normp = Vec3DotCore<T>(x, xp) / norm;
                normObj.pvalue[i] = Vec3DotCore<T>(normX, xObj.pvalue(i));
            }
//            const Vec<T, 3>& xp = xObj.pvalue(0);
//            normObj.pvalue[0] = Vec3DotCore<T>(x, xp) / norm;
            normObj.pvalue[0] = Vec3DotCore<T>(normX, xObj.pvalue(0));
*/

//            main loop:
            for (int i = 0; i < N; i++) {
                normObj.pvalue[i] = Vec3DotCore<T>(normX, xObj.pvalue(i));
            }
//            TODO: there are faster ways to do this instead of repeatedly calling Vec3DotCore
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& norm = normObj.value;
            const T& nb = normObj.bvalue;
            T invNorm = 1 / norm;
/*
//            main loop:
            for (int i = N - 1; i != 0; i--) {
//                input:
                const T& nh = normObj.hvalue(i);
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Vec3ScaleCore(-Vec3DotCore<T>(normX, xp), normX, xh);
                Vec3AddThenScaleCore(nb * invNorm, xp, xh);
                Vec3ScaleThenAddCore(nh, normX, xh);
            }
//                input:
            const T& nh = normObj.hvalue(0);
            const Vec<T, 3>& xp = xObj.pvalue(0);
//                output:
            Vec<T, 3>& xh = xObj.hvalue(0);
//                operations:
            Vec3ScaleCore(-Vec3DotCore<T>(normX, xp), normX, xh);
            Vec3AddThenScaleCore(nb * invNorm, xp, xh);
            Vec3ScaleThenAddCore(nh, normX, xh);
*/

//            main loop:
            for (int i = 0; i < N; i++) {
//                input:
                const T& nh = normObj.hvalue(i);
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Vec3ScaleCore(-Vec3DotCore<T>(normX, xp), normX, xh);
                Vec3AddThenScaleCore(nb * invNorm, xp, xh);
                Vec3ScaleAndAddCore(nh, normX, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DScalar<N, T>& normObj;

    private:
        Vec<T, 3> normX;
    };

    template <int N, typename T>
    inline A2DVec3NormExpr<N, T> Vec3Norm(A2DVec<N, Vec<T, 3>>& x,
                                          A2DScalar<N, T>& norm) {
        return A2DVec3NormExpr<N, T>(x, norm);
    }


    /*
        Vec3Scale
        This represents scalar multiplication of a 3 vector
        yObj = alpha * xObj
    */
    template <int N, typename T>
    class A2DVec3ScaleExpr {
    public:
        A2DVec3ScaleExpr(A2DVec<N, Vec<T, 3>>& xObj,
                         const T& alpha,
                         A2DVec<N, Vec<T, 3>>& vObj)
                : xObj(xObj), alpha(alpha), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            Vec<T, 3>& v = vObj.value();
            Vec3ScaleCore(a, x, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
            const Vec<T, 3>& x = xObj.value();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            alpha.bvalue = Vec3DotCore<T, Vec<T, 3>>(vb, x);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; i++) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3ScaleCore(alpha, xp, vp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; i++) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Vec3ScaleCore(alpha, vh, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DVec<N, Vec<T, 3>>& vObj;
        const T& alpha;
    };

    template <int N, typename T>
    inline A2DVec3ScaleExpr<N, T> Vec3Scale(A2DVec<N, Vec<T, 3>>& x,
                                            const T& alpha,
                                            A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3ScaleExpr<N, T>(x, alpha, v);
    }

    template <int N, typename T>
    class Vec3A2DScaleExpr {
    public:
        Vec3A2DScaleExpr(const Vec<T, 3>& x,
                         A2DScalar<N, T>& alpha,
                         A2DVec<N, Vec<T, 3>>& vObj)
                : x(x), alpha(alpha), vObj(vObj) {
            const T& a = alpha.value;
            Vec<T, 3>& v = vObj.value();
            Vec3ScaleCore(a, x, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
//            operations:
            alpha.bvalue = Vec3DotCore<T, Vec<T, 3>>(vb, x);
        };

        void hforward() {
//            input:
            const T& a = alpha.value;
//            main loop:
            for (int i = 0; i < N; i++) {
//                input:
                const T& ap = alpha.pvalue[i];
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3ScaleCore(ap, x, vp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; i++) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                operations:
                alpha.hvalue[i] = Vec3DotCore<T>(vh, x);
            }
        };

        const Vec<T, 3>& x;
        A2DVec<N, Vec<T, 3>>& vObj;
        A2DScalar<N, T>& alpha;
    };

    template <int N, typename T>
    inline Vec3A2DScaleExpr<N, T> Vec3Scale(const Vec<T, 3>& x,
                                            A2DScalar<N, T>& alpha,
                                            A2DVec<N, Vec<T, 3>>& v) {
        return Vec3A2DScaleExpr<N, T>(x, alpha, v);
    }

    template <int N, typename T>
    class A2DVec3A2DScaleExpr {
    public:
        A2DVec3A2DScaleExpr(A2DVec<N, Vec<T, 3>>& xObj,
                            A2DScalar<N, T>& alpha,
                            A2DVec<N, Vec<T, 3>>& vObj)
                : xObj(xObj), alpha(alpha), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            Vec<T, 3>& v = vObj.value();
            Vec3ScaleCore(a, x, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            alpha.bvalue = Vec3DotCore<T, Vec<T, 3>>(vb, x);
            Vec3ScaleCore(a, vb, xb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
//            main loop:
            for (int i = 0; i < N; i++) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const T& ap = alpha.pvalue[i];
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3AXPBYCore(ap, x, a, xp, vp);
            }
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
            const T& a = alpha.value;
//            main loop:
            for (int i = 0; i < N; i++) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& vh = vObj.hvalue(i);
                const T& ap = alpha.pvalue[i];
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                alpha.hvalue[i] = Vec3DotCore<T>(vh, x) + Vec3DotCore<T>(vb, xp);
                Vec3AXPBYCore(a, vh, ap, vb, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DVec<N, Vec<T, 3>>& vObj;
        A2DScalar<N, T>& alpha;
    };

    template <int N, typename T>
    inline A2DVec3A2DScaleExpr<N, T> Vec3Scale(A2DVec<N, Vec<T, 3>>& x,
                                               A2DScalar<N, T>& alpha,
                                               A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3A2DScaleExpr<N, T>(x, alpha, v);
    }


    /*
        Vec3Axpy
        This operation is a compound scalar multiplication of a vector (Ax)
        and addition of another unscaled vector (py).  So Axpy means:
        "a (scalar) times (vector) x plus (vector) y"
    */
    template <int N, typename T>
    class Vec3VecA2DScalarAxpyExpr {
    public:
        Vec3VecA2DScalarAxpyExpr(A2DScalar<N, T>& alpha,
                                 const Vec<T, 3>& x,
                                 const Vec<T, 3>& y,
                                 A2DVec<N, Vec<T, 3>>& vObj)
                : alpha(alpha), x(x), y(y), vObj(vObj) {
            const T& a = alpha.value;
            const Vec<T, 3>& v = vObj.value();
            Vec3AXPYCore(a, x, y, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
//            operations:
            alpha.bvalue = Vec3DotCore<T>(vb, x);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const T& ap = alpha.pvalue[i];
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3ScaleCore(ap, x, vp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                operations:
                alpha.hvalue[i] = Vec3DotCore<T>(vh, x);
            }
        };

        A2DScalar<N, T>& alpha;
        const Vec<T, 3>& x;
        const Vec<T, 3>& y;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline Vec3VecA2DScalarAxpyExpr<N, T> Vec3Axpy(A2DScalar<N, T>& alpha,
                                                   const Vec<T, 3>& x,
                                                   const Vec<T, 3>& y,
                                                   A2DVec<N, Vec<T, 3>>& v) {
        return Vec3VecA2DScalarAxpyExpr<N, T>(alpha, x, y, v);
    }

    template <int N, typename T>
    class A2DVec3VecScalarAxpyExpr {
    public:
        A2DVec3VecScalarAxpyExpr(const T& a,
                                 A2DVec<N, Vec<T, 3>>& xObj,
                                 const Vec<T, 3>& y,
                                 A2DVec<N, Vec<T, 3>>& vObj)
                : a(a), xObj(xObj), y(y), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& v = vObj.value();
            Vec3AXPYCore(a, x, y, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3ScaleCore(a, vb, xb);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3ScaleCore(a, xp, vp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Vec3ScaleCore(a, vh, xh);
            }
        };

        const T& a;
        A2DVec<N, Vec<T, 3>>& xObj;
        const Vec<T, 3>& y;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline A2DVec3VecScalarAxpyExpr<N, T> Vec3Axpy(const T& a,
                                                   A2DVec<N, Vec<T, 3>>& x,
                                                   const Vec<T, 3>& y,
                                                   A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3VecScalarAxpyExpr<N, T>(a, x, y, v);
    }

    template <int N, typename T>
    class Vec3A2DVecScalarAxpyExpr {
    public:
        Vec3A2DVecScalarAxpyExpr(const T& a,
                                 const Vec<T, 3>& x,
                                 A2DVec<N, Vec<T, 3>>& yObj,
                                 A2DVec<N, Vec<T, 3>>& vObj)
                : a(a), x(x), yObj(yObj), vObj(vObj) {
            const Vec<T, 3>& y = yObj.value();
            const Vec<T, 3>& v = vObj.value();
            Vec3AXPYCore(a, x, y, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& yb = yObj.bvalue();
//            operations:
            yb(0) = vb(0);
            yb(1) = vb(1);
            yb(2) = vb(2);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& yp = yObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                vp(0) = yp(0);
                vp(1) = yp(1);
                vp(2) = yp(2);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& yh = yObj.hvalue(i);
//                operations:
                yh(0) = vh(0);
                yh(1) = vh(1);
                yh(2) = vh(2);
            }
        };

        const T& a;
        const Vec<T, 3>& x;
        A2DVec<N, Vec<T, 3>>& yObj;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline Vec3A2DVecScalarAxpyExpr<N, T> Vec3Axpy(const T& a,
                                                   const Vec<T, 3>& x,
                                                   A2DVec<N, Vec<T, 3>>& y,
                                                   A2DVec<N, Vec<T, 3>>& v) {
        return Vec3A2DVecScalarAxpyExpr<N, T>(a, x, y, v);
    }

    template <int N, typename T>
    class A2DVec3VecA2DScalarAxpyExpr {
    public:
        A2DVec3VecA2DScalarAxpyExpr(A2DScalar<N, T>& alpha,
                                    A2DVec<N, Vec<T, 3>>& xObj,
                                    const Vec<T, 3>& y,
                                    A2DVec<N, Vec<T, 3>>& vObj)
                : alpha(alpha), xObj(xObj), y(y), vObj(vObj) {
            const T& a = alpha.value;
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& v = vObj.value();
            Vec3AXPYCore(a, x, y, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            alpha.bvalue = Vec3DotCore<T>(vb, x);
            Vec3ScaleCore(a, vb, xb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const T& ap = alpha.pvalue[i];
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3AXPBYCore(ap, x, a, xp, vp);
            }
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
            const T& a = alpha.value;
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const T& ap = alpha.pvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                alpha.hvalue[i] = Vec3DotCore<T>(vh, x) + Vec3DotCore<T>(vb, xp);
                Vec3AXPBYCore(a, vh, ap, vb, xh);
            }
        };

        A2DScalar<N, T>& alpha;
        A2DVec<N, Vec<T, 3>>& xObj;
        const Vec<T, 3>& y;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline A2DVec3VecA2DScalarAxpyExpr<N, T> Vec3Axpy(A2DScalar<N, T>& alpha,
                                                      A2DVec<N, Vec<T, 3>>& x,
                                                      const Vec<T, 3>& y,
                                                      A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3VecA2DScalarAxpyExpr<N, T>(alpha, x, y, v);
    }

    template <int N, typename T>
    class Vec3A2DVecA2DScalarAxpyExpr {
    public:
        Vec3A2DVecA2DScalarAxpyExpr(A2DScalar<N, T>& alpha,
                                    const Vec<T, 3>& x,
                                    A2DVec<N, Vec<T, 3>>& yObj,
                                    A2DVec<N, Vec<T, 3>>& vObj)
                : alpha(alpha), x(x), yObj(yObj), vObj(vObj) {
            const T& a = alpha.value;
            const Vec<T, 3>& y = yObj.value();
            const Vec<T, 3>& v = vObj.value();
            Vec3AXPYCore(a, x, y, v);
        };

        void reverse() {
//            input:
            const T& a = alpha.value;
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& yb = yObj.bvalue();
//            operations:
            alpha.bvalue = Vec3DotCore<T>(vb, x);
            yb(0) = vb(0);
            yb(1) = vb(1);
            yb(2) = vb(2);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const T& ap = alpha.pvalue[i];
                const Vec<T, 3>& yp = yObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3AXPYCore(ap, x, yp, vp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& yh = yObj.hvalue(i);
//                operations:
                alpha.hvalue[i] = Vec3DotCore<T>(vh, x);
                yh(0) = vh(0);
                yh(1) = vh(1);
                yh(2) = vh(2);
            }
        };

        A2DScalar<N, T>& alpha;
        const Vec<T, 3>& x;
        A2DVec<N, Vec<T, 3>>& yObj;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline Vec3A2DVecA2DScalarAxpyExpr<N, T> Vec3Axpy(A2DScalar<N, T>& alpha,
                                                      const Vec<T, 3>& x,
                                                      A2DVec<N, Vec<T, 3>>& y,
                                                      A2DVec<N, Vec<T, 3>>& v) {
        return Vec3A2DVecA2DScalarAxpyExpr<N, T>(alpha, x, y, v);
    }

    template <int N, typename T>
    class A2DVec3A2DVecScalarAxpyExpr {
    public:
        A2DVec3A2DVecScalarAxpyExpr(const T& a,
                                    A2DVec<N, Vec<T, 3>>& xObj,
                                    A2DVec<N, Vec<T, 3>>& yObj,
                                    A2DVec<N, Vec<T, 3>>& vObj)
                : a(a), xObj(xObj), yObj(yObj), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
            const Vec<T, 3>& v = vObj.value();
            Vec3AXPYCore(a, x, y, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
            Vec<T, 3>& yb = yObj.bvalue();
//            operations:
            Vec3ScaleCore(a, vb, xb);
            yb(0) = vb(0);
            yb(1) = vb(1);
            yb(2) = vb(2);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& yp = yObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3AXPYCore(a, xp, yp, vp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
                Vec<T, 3>& yh = yObj.hvalue(i);
//                operations:
                Vec3ScaleCore(a, vh, xh);
                yh(0) = vh(0);
                yh(1) = vh(1);
                yh(2) = vh(2);
            }
        };

        const T& a;
        A2DVec<N, Vec<T, 3>>& xObj;
        A2DVec<N, Vec<T, 3>>& yObj;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline A2DVec3A2DVecScalarAxpyExpr<N, T> Vec3Axpy(const T& a,
                                                      A2DVec<N, Vec<T, 3>>& x,
                                                      A2DVec<N, Vec<T, 3>>& y,
                                                      A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3A2DVecScalarAxpyExpr<N, T>(a, x, y, v);
    }

    template <int N, typename T>
    class A2DVec3A2DVecA2DScalarAxpyExpr {
    public:
        A2DVec3A2DVecA2DScalarAxpyExpr(A2DScalar<N, T>& alpha,
                                       A2DVec<N, Vec<T, 3>>& xObj,
                                       A2DVec<N, Vec<T, 3>>& yObj,
                                       A2DVec<N, Vec<T, 3>>& vObj)
                : alpha(alpha), xObj(xObj), yObj(yObj), vObj(vObj) {
            const T& a = alpha.value;
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
            const Vec<T, 3>& v = vObj.value();
            Vec3AXPYCore(a, x, y, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
            Vec<T, 3>& yb = yObj.bvalue();
//            operations:
            alpha.bvalue = Vec3DotCore<T>(vb, x);
            Vec3ScaleCore(a, vb, xb);
            yb(0) = vb(0);
            yb(1) = vb(1);
            yb(2) = vb(2);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const T& ap = alpha.pvalue[i];
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& yp = yObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3AXPBYCore(ap, x, a, xp, vp);
                Vec3AddCore<T>(vp, yp, vp);
            }
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
            const T& a = alpha.value;
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const T& ap = alpha.pvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
                Vec<T, 3>& yh = yObj.hvalue(i);
//                operations:
                alpha.hvalue[i] = Vec3DotCore<T>(vh, x) + Vec3DotCore<T>(vb, xp);
                Vec3AXPBYCore(a, vh, ap, vb, xh);
                yh(0) = vh(0);
                yh(1) = vh(1);
                yh(2) = vh(2);
            }
        };

        A2DScalar<N, T>& alpha;
        A2DVec<N, Vec<T, 3>>& xObj;
        A2DVec<N, Vec<T, 3>>& yObj;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline A2DVec3A2DVecA2DScalarAxpyExpr<N, T> Vec3Axpy(A2DScalar<N, T>& alpha,
                                                         A2DVec<N, Vec<T, 3>>& x,
                                                         A2DVec<N, Vec<T, 3>>& y,
                                                         A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3A2DVecA2DScalarAxpyExpr<N, T>(alpha, x, y, v);
    }


    /*
        Vec3Dot
        This represents vector-vector dot product (inner product) of two 3 vectors
        alpha = xObj . yObj
        A.K.A.
        alpha = xObj @ yObj (in numpy notation)
    */
    template <int N, typename T>
    class A2DVec3DotVecExpr {
    public:
        A2DVec3DotVecExpr(A2DVec<N, Vec<T, 3>>& xObj,
                          const Vec<T, 3>& y,
                          A2DScalar<N, T>& alpha)
                : xObj(xObj), y(y), alpha(alpha) {
            const Vec<T, 3>& x = xObj.value();
            alpha.value = Vec3DotCore<T>(x, y);
        };

        void reverse() {
//            input:
            const T& ab = alpha.bvalue;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3ScaleCore(ab, y, xb);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                operations:
                alpha.pvalue[i] = Vec3DotCore<T>(xp, y);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const T& ah = alpha.hvalue[i];
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Vec3ScaleCore(ah, y, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        const Vec<T, 3>& y;
        A2DScalar<N, T>& alpha;
    };

    template <int N, typename T>
    inline A2DVec3DotVecExpr<N, T> Vec3Dot(A2DVec<N, Vec<T, 3>>& x,
                                           const Vec<T, 3>& y,
                                           A2DScalar<N, T>& alpha) {
        return A2DVec3DotVecExpr<N, T>(x, y, alpha);
    }

    // TODO: Vec3DotA2DVecExpr?
    // ^ This is probably not necessary

    template <int N, typename T>
    class A2DVec3DotA2DVecExpr {
    public:
        A2DVec3DotA2DVecExpr(A2DVec<N, Vec<T, 3>>& xObj,
                             A2DVec<N, Vec<T, 3>>& yObj,
                             A2DScalar<N, T>& alpha)
                : xObj(xObj), yObj(yObj), alpha(alpha) {
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();

            alpha.value = Vec3DotCore<T>(x, y);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
            const T& ab = alpha.bvalue;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
            Vec<T, 3>& yb = yObj.bvalue();
//            operations:
            Vec3ScaleCore(ab, y, xb);
            Vec3ScaleCore(ab, x, yb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& yp = yObj.pvalue(i);
//                operations:
                alpha.pvalue[i] = Vec3DotCore<T>(xp, y) + Vec3DotCore<T>(x, yp);
            }
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
            const T& ab = alpha.bvalue;
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const T& ah = alpha.hvalue[i];
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& yp = yObj.pvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
                Vec<T, 3>& yh = yObj.hvalue(i);
//                operations:
                Vec3AXPBYCore(ah, y, ab, yp, xh);
                Vec3AXPBYCore(ah, x, ab, xp, yh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DVec<N, Vec<T, 3>>& yObj;
        A2DScalar<N, T>& alpha;
    };

    template <int N, typename T>
    inline A2DVec3DotA2DVecExpr<N, T> Vec3Dot(A2DVec<N, Vec<T, 3>>& x,
                                              A2DVec<N, Vec<T, 3>>& y,
                                              A2DScalar<N, T>& alpha) {
        return A2DVec3DotA2DVecExpr<N, T>(x, y, alpha);
    }


    /*
        Vec3CrossProduct
        This represents vector-vector cross product of two 3 vectors
    */
    template <int N, typename T>
    class A2DVec3CrossVecExpr {
    public:
        A2DVec3CrossVecExpr(A2DVec<N, Vec<T, 3>>& xObj,
                            const Vec<T, 3>& y,
                            A2DVec<N, Vec<T, 3>>& vObj)
                : xObj(xObj), y(y), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            Vec<T, 3>& v = vObj.value();
            Vec3CrossProductCore(x, y, v);
        }

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3CrossProductAddCore(y, vb, xb);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3CrossProductCore(xp, y, vp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Vec3CrossProductCore(y, vh, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        const Vec<T, 3>& y;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline A2DVec3CrossVecExpr<N, T> Vec3Cross(A2DVec<N, Vec<T, 3>>& x,
                                               const Vec<T, 3>& y,
                                               A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3CrossVecExpr<N, T>(x, y, v);
    }

    // TODO: Vec3CrossA2DVecExpr
    // ^ This is probably not necessary

    template <int N, typename T>
    class A2DVec3CrossA2DVecExpr {
    public:
        A2DVec3CrossA2DVecExpr(A2DVec<N, Vec<T, 3>>& xObj,
                               A2DVec<N, Vec<T, 3>>& yObj,
                               A2DVec<N, Vec<T, 3>>& vObj)
                : xObj(xObj), yObj(yObj), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
            Vec<T, 3>& v = vObj.value();
            Vec3CrossProductCore(x, y, v);
        }

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
            Vec<T, 3>& yb = yObj.bvalue();
//            operations:
            Vec3CrossProductAddCore(y, vb, xb);
            Vec3CrossProductAddCore(vb, x, yb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& yp = yObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3CrossProductCore(xp, y, vp);
                Vec3CrossProductAddCore(x, yp, vp);
            }
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& yp = yObj.pvalue(i);
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
                Vec<T, 3>& yh = yObj.hvalue(i);
//                operations:
                Vec3CrossProductCore(y, vh, xh);
                Vec3CrossProductAddCore(vb, yp, xh);
                Vec3CrossProductCore(vh, x, yh);
                Vec3CrossProductAddCore(xp, vb, yh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DVec<N, Vec<T, 3>>& yObj;
        A2DVec<N, Vec<T, 3>>& vObj;
    };

    template <int N, typename T>
    inline A2DVec3CrossA2DVecExpr<N, T> Vec3Cross(A2DVec<N, Vec<T, 3>>& x,
                                                  A2DVec<N, Vec<T, 3>>& y,
                                                  A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3CrossA2DVecExpr<N, T>(x, y, v);
    }


    /*
        Vec3Normalize
        This represents the normalization of a vector
        vObj = xObj / ||xObj||

        NOTE: I have made the design decision to compute and store the inverse of the vector norm and the negative of
        the norm inverse squared (previously cubed) in order to eliminate the need to compute these inside the "forward"
        and "backward" methods, which may have to be called up to twice per instance of the normalized vector.
        *** This does come at the cost of the memory needed to store those two components.  If memory is a concern or
        if memory is more important than processing speed, then it should be possible to create a template variable can
        override this behavior (or you can overwrite it completely if desired).

        NOTE: I'm also replacing the derived formula as follows:
        Original:
            Forward:  vb = (xb / ||x||) - ((xb . x) x / (||x||^3))
            Reverse:  xb = (vb / ||x||) - ((vb . x) x / (||x||^3))
        New:
            Forward:  vb = (xb / ||x||) - ((xb . x) v / (||x||^2))
            Reverse:  xb = (vb / ||x||) - ((vb . x) v / (||x||^2))
        This saves us a multiplication and allows us to use the norm squared, which is computed en-route to getting the
        norm.  HOWEVER, this might cause floating point accuracy issues, so please be aware!

        TODO: this can be improved more by using v = (x / ||x||)
    */
    template <int N, typename T>
    class A2DVec3NormalizeExpr {
    public:
        A2DVec3NormalizeExpr(A2DVec<N, Vec<T, 3>>& xObj,
                             A2DVec<N, Vec<T, 3>>& vObj)
                : xObj(xObj), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            Vec<T, 3>& v = vObj.value();
            negativeSquaredNormInv = 1 / Vec3DotCore<T>(x, x);
            normInv = sqrt(negativeSquaredNormInv);
            negativeSquaredNormInv *= -1;
            Vec3ScaleCore(normInv, x, v);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
            const Vec<T, 3>& v = vObj.value();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3AXPBYCore(normInv, vb, negativeSquaredNormInv * Vec3DotCore<T>(vb, x), v, xb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& v = vObj.value();
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& vp = vObj.pvalue(i);
//                operations:
                Vec3AXPYCore(-Vec3DotCore<T>(xp, v), v, xp, vp);
                Vec3ScaleCore(normInv, vp, vp);
            }
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& v = vObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
            const Vec<T, 3>& x = xObj.value();
//            operations:
            T temp1{Vec3DotCore<T>(vb, v)}, temp2;
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const Vec<T, 3>& vh = vObj.hvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                temp2 = Vec3DotCore(xp, v);
                Vec3AXPBYCore(3 * temp2 * temp1 - Vec3DotCore<T>(vh, x) - temp2 - (Vec3DotCore<T>(vb, xp) * normInv),
                              v, -temp1, xp, xh);
                Vec3AXPYCore(normInv, xh, vh, xh);
                Vec3ScaleCore(normInv, xh, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DVec<N, Vec<T, 3>>& vObj;

    private:
        T normInv;
        T negativeSquaredNormInv;
    };

    template <int N, typename T>
    inline A2DVec3NormalizeExpr<N, T> Vec3Normalize(A2DVec<N, Vec<T, 3>>& x,
                                                    A2DVec<N, Vec<T, 3>>& v) {
        return A2DVec3NormalizeExpr<N, T>(x, v);
    }


    /*
        Vec3ScaleSymmetricOuterProduct
        This represents a scaled, 3 vector outer product with itself
        sObj = alpha * xObj . (xObj^T)

        NOTE: there are significant improvements that can be made to this if the symmetries are taken advantage of,
        especially if a symmetric matrix type (class) is implemented
    */
    template <int N, typename T>
    class A2DVec3ScaleSymmetricOuterProductExpr {
    public:
        A2DVec3ScaleSymmetricOuterProductExpr(const T& alpha,
                                              A2DVec<N, Vec<T, 3>>& xObj,
                                              A2DMat<N, Mat<T, 3, 3>>& sObj)
                : alpha(alpha), xObj(xObj), sObj(sObj) {
            const Vec<T, 3>& x = xObj.value();
            Mat<T, 3, 3>& S = sObj.value();
            Vec3OuterProductScaleCore(alpha, x, x, S);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Mat<T, 3, 3>& Sb = sObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Mat3x3VecMultScaleCore(2 * alpha, Sb, x, xb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            Vec<T, 3> ax;
//            operations:
            Vec3ScaleCore<T, Vec<T, 3>>(alpha, x, ax);
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Mat<T, 3, 3>& Sp = sObj.pvalue(i);
//                operations:
                Vec3OuterProductCore<Vec<T, 3>, Mat<T, 3, 3>>(xp, ax, Sp);
                Vec3OuterProductAddCore<Vec<T, 3>, Mat<T, 3, 3>>(ax, xp, Sp);
            }
        };

        void hreverse() {
//            input:
            const Mat<T, 3, 3>& sb = sObj.bvalue();
            const Vec<T, 3>& x = xObj.value();
            Vec<T, 3> sbxp, shx, x_sx;
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Mat<T, 3, 3>& sh = sObj.hvalue(i);
                const Vec<T, 3>& xp = xObj.pvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Mat3x3VecMultCore(sb, xp, sbxp);
                Mat3x3VecMultCore(sh, x, shx);
                Vec3AddCore(shx, sbxp, x_sx);
                Vec3ScaleCore(2 * alpha, x_sx, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DMat<N, Mat<T, 3, 3>>& sObj;
        const T& alpha;
    };

    template <int N, typename T>
    inline A2DVec3ScaleSymmetricOuterProductExpr<N, T> Vec3ScaleSymmetricOuterProduct(const T& alpha,
                                                                                      A2DVec<N, Vec<T, 3>>& x,
                                                                                      A2DMat<N, Mat<T, 3, 3>>& S) {
        return A2DVec3ScaleSymmetricOuterProductExpr<N, T>(alpha, x, S);
    }

    template <int N, typename T>
    class Vec3A2DScaleSymmetricOuterProductExpr {
    public:
        Vec3A2DScaleSymmetricOuterProductExpr(A2DScalar<N, T>& alpha,
                                              const Vec<T, 3>& x,
                                              A2DMat<N, Mat<T, 3, 3>>& sObj)
                : alpha(alpha), x(x), sObj(sObj) {
            const T& a = alpha.value;
            Mat<T, 3, 3>& S = sObj.value();
            Vec3OuterProductScaleCore(a, x, x, S);
        };

        void reverse() {
//            input:
            const Mat<T, 3, 3>& Sb = sObj.bvalue();
//            operations:
            alpha.bvalue = Mat3x3InnerProductCore<T, Vec<T, 3>, Mat<T, 3, 3>>(Sb, x, x);
        };

        void hforward() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const T& ap = alpha.pvalue[i];
//                output:
                Mat<T, 3, 3>& Sp = sObj.pvalue(i);
//                operations:
                Vec3OuterProductScaleCore(ap, x, x, Sp);
            }
        };

        void hreverse() {
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Mat<T, 3, 3>& sh = sObj.hvalue(i);
//                operations:
                alpha.hvalue[i] = Mat3x3InnerProductCore<T>(sh, x, x);
            }
        };

        const Vec<T, 3>& x;
        A2DMat<N, Mat<T, 3, 3>>& sObj;
        A2DScalar<N, T>& alpha;
    };

    template <int N, typename T>
    inline Vec3A2DScaleSymmetricOuterProductExpr<N, T> Vec3ScaleSymmetricOuterProduct(A2DScalar<N, T>& alpha,
                                                                                      const Vec<T, 3>& x,
                                                                                      A2DMat<N, Mat<T, 3, 3>>& S) {
        return Vec3A2DScaleSymmetricOuterProductExpr<N, T>(alpha, x, S);
    }

    template <int N, typename T>
    class A2DVec3A2DScaleSymmetricOuterProductExpr {
    public:
        A2DVec3A2DScaleSymmetricOuterProductExpr(A2DScalar<N, T>& alpha,
                                                 A2DVec<N, Vec<T, 3>>& xObj,
                                                 A2DMat<N, Mat<T, 3, 3>>& sObj)
                : alpha(alpha), xObj(xObj), sObj(sObj) {
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            Mat<T, 3, 3>& S = sObj.value();
            Vec3OuterProductScaleCore(a, x, x, S);
        };

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Mat<T, 3, 3>& Sb = sObj.bvalue();
            const T& a = alpha.value;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            alpha.bvalue = Mat3x3InnerProductCore<T, Vec<T, 3>, Mat<T, 3, 3>>(Sb, x, x);
            Mat3x3VecMultScaleCore(2 * a, Sb, x, xb);
        };

        void hforward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
//            operations:
            Vec<T, 3> ax;
            Vec3ScaleCore<T, Vec<T, 3>>(a, x, ax);
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const T& ap = alpha.pvalue[i];
//                output:
                Mat<T, 3, 3>& Sp = sObj.pvalue(i);
//                operations:
                Vec3OuterProductCore<Vec<T, 3>, Mat<T, 3, 3>>(xp, ax, Sp);
                Vec3OuterProductAddCore<Vec<T, 3>, Mat<T, 3, 3>>(ax, xp, Sp);
                Vec3OuterProductAddScaleCore<T, Vec<T, 3>, Mat<T, 3, 3>>(ap, x, x, Sp);
            }
        };

        void hreverse() {
//            input:
            const Mat<T, 3, 3>& sb = sObj.bvalue();
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            Vec<T, 3> sbxp, shx, sbx, a_sx, x_sx;
//            operations:
            Mat3x3VecMultCore(sb, x, sbx);
//            main loop:
            for (int i = 0; i < N; ++i) {
//                input:
                const Mat<T, 3, 3>& sh = sObj.hvalue(i);
                const Vec<T, 3>& xp = xObj.pvalue(i);
                const T& ap = alpha.pvalue(i);
//                output:
                Vec<T, 3>& xh = xObj.hvalue(i);
//                operations:
                Mat3x3VecMultCore(sb, xp, sbxp);
                Mat3x3VecMultCore(sh, x, shx);
                Vec3AXPYCore(2, sbxp, shx, a_sx);
                Vec3AddCore(shx, sbxp, x_sx);
                alpha.hvalue[i] = Vec3DotCore<T>(x, a_sx);
                Vec3AXPBYCore(2 * a, x_sx, 2 * ap, sbx, xh);
            }
        };

        A2DVec<N, Vec<T, 3>>& xObj;
        A2DMat<N, Mat<T, 3, 3>>& sObj;
        A2DScalar<N, T>& alpha;
    };

    template <int N, typename T>
    inline A2DVec3A2DScaleSymmetricOuterProductExpr<N, T> Vec3ScaleSymmetricOuterProduct(A2DScalar<N, T>& alpha,
                                                                                         A2DVec<N, Vec<T, 3>>& x,
                                                                                         A2DMat<N, Mat<T, 3, 3>>& S) {
        return A2DVec3A2DScaleSymmetricOuterProductExpr<N, T>(alpha, x, S);
    }



    /*
        Loop Testing:
    *//*
    template <int N, typename T>
    inline T DecrementDotProduct(const Vec<T, N>& x,
                                 const Vec<T, N>& y) {
        T result = x(0) * y(0);
        for (int i = N; i != 0; i--) {
            result += x(i) * y(i);
        }
        return result;
    }

    template <int N, typename T>
    inline T IncrementDotProduct(const Vec<T, N>& x,
                                 const Vec<T, N>& y) {
//        T result = x(0) * y(0);
        T result = 0;
        for (int i = 0; i < N; i++) {
            result += x(i) * y(i);
        }
        return result;
    }

    template <int N>
    inline int DecrementLoop() {
        int result = 0;
        for (int i = N; i != 0; i--) {
            result += i;
        }
        return result;
    }

    template <int N>
    inline int IncrementLoop() {
        int result = 0;
        for (int i = 1; i < N; i++) {
            result += i;
        }
        return result;
    }*/

}  // namespace A2D

#endif //A2D_A2D_VEC_OPERATION_DEVELOPMENT_H
