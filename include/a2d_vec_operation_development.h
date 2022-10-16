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

    // TODO: test to see if decrementing loops actually improve speed

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
        }

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
//            TODO: there are faster ways to do this instead of repeatedly calling Vec3DotCore
        };

        void hreverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const T& norm = normObj.value;
            const T& nb = normObj.bvalue;
            T invNorm = 1 / norm;

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

}  // namespace A2D

#endif //A2D_A2D_VEC_OPERATION_DEVELOPMENT_H
