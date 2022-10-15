//
// Created by James on 10/7/2022.
//

#ifndef A2D_VECTOR_OPERATION_DEVELOPMENT_H
#define A2D_VECTOR_OPERATION_DEVELOPMENT_H

#include "a2dobjs.h"
#include "a2dtypes.h"
#include "a2dveccore3d.h"
#include "a2dvecops3d.h"

// FOR: a2dveccore3d.h
namespace A2D {
//    /**
//     * @brief scalar-vector multiply and add v = a * x + b * y
//     * @param alpha:  Scalar to multiply x
//     * @param x    :  3-Vector
//     * @param beta :  Scalar to multiply y
//     * @param y    :  3-Vector
//     * @param v    :  3-Vector to store result
//     */
//        template <typename T, class VecType>
//        inline T Vec3AXPBYCore(const T alpha, const VecType& x, const T beta, const VecType& y,
//                               VecType& v) {
//            v(0) = alpha * x(0) + beta * y(0);
//            v(1) = alpha * x(1) + beta * y(1);
//            v(2) = alpha * x(2) + beta * y(2);
//        }
}  // namespace A2D

// FOR: a2dvecops3d.h
namespace A2D {

//    TODO: Make function call input naming conventions more consistent
//    TODO: make class notations consistent

//    QUESTION: Why is ADScalar.value not a function call but ADVec.value() is?
// ANSWER: ADScalar.value is faster than ADScalar.value() but ADVec.value() can't be returned or accessed properly
// without the function call

//    QUESTION: Should scalar values (like those referenced above) be set by reference or by assignment?
//    i.e. should I use:
//      normObj.bvalue = ...;
//    or
//      T& nb = normObj.bvalue; // with:
//      nb = ...;
// ANSWER: Use single line

//    QUESTION: Should I be explicitly typing the core functions? e.g.:
//      nb = Vec3DotCore<T, Vec<T, 3>>(x, xb) / n;
//    or
//      nb = Vec3DotCore(x, xb) / n;
// ANSWER: this is fine to use


    /*
        Vec3Norm
        This represents the L2 norm (or 2 norm) of a 3 vector
        normObj = ||xObj||
    */
    template <typename T>
    inline void Vec3Norm(const Vec<T, 3>& x,
                         T& norm) {
        norm = Vec3NormCore<T>(x);
    }

    template <typename T>
    class ADVec3NormExpr {
    public:
        ADVec3NormExpr(ADVec<Vec<T, 3>>& xObj,
                       ADScalar<T>& normObj)
                : xObj(xObj), normObj(normObj) {
            const Vec<T, 3>& x = xObj.value();
            normObj.value = Vec3NormCore<T>(x);
        }

        void forward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& xb = xObj.bvalue();
            const T& n = normObj.value;
//            output:
            T& nb = normObj.bvalue;
//            operations:
            nb = Vec3DotCore<T, Vec<T, 3>>(x, xb) / n;
            normObj.bvalue = Vec3DotCore<T, Vec<T, 3>>(x, xb) / n;
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
        }

        ADVec<Vec<T, 3>>& xObj;
        ADScalar<T>& normObj;
    };

    template <typename T>
    inline ADVec3NormExpr<T> Vec3Norm(ADVec<Vec<T, 3>>& x,
                                      ADScalar<T>& norm) {
        return ADVec3NormExpr<T>(x, norm);
    }


//    QUESTION: What happens if we were to take the derivative with respect to a vector?
//    The ab would be a vector and xb would be a matrix, so do we need to account for those changes?
//    OR is it that we are ALWAYS going to be taking a derivative with respect to a scalar?
// ANSWER: the derivative will always be with respect to some scalar (though the scalar may be

    /*
        Vec3Scale
        This represents scalar multiplication of a 3 vector
        yObj = alpha * xObj
    */
    template <typename T>
    inline void Vec3Scale(const Vec<T, 3>& x,
                          const T& alpha,
                          Vec<T, 3>& v) {
        Vec3ScaleCore(alpha, x, v);
    }

    template <typename T>
    class ADVec3ScaleExpr {
    public:
        ADVec3ScaleExpr(ADVec<Vec<T, 3>>& xObj,
                        const T& alpha,
                        ADVec<Vec<T, 3>>& vObj)
                : xObj(xObj), alpha(alpha), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            Vec<T, 3>& v = vObj.value();
            Vec3ScaleCore(alpha, x, v);
        };

        void forward() {
//            input:
            const Vec<T, 3>& xb = xObj.bvalue();
//            output:
            Vec<T, 3>& vb = vObj.bvalue();
//            operations:
            Vec3ScaleCore(alpha, xb, vb);
        }

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
            const Vec<T, 3>& x = xObj.value();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3ScaleCore(alpha, vb, xb);
        };

        ADVec<Vec<T, 3>>& xObj;
        ADVec<Vec<T, 3>>& vObj;
        const T& alpha;
    };

    template <typename T>
    inline ADVec3ScaleExpr<T> Vec3Scale(ADVec<Vec<T, 3>>& x,
                                        const T& alpha,
                                        ADVec<Vec<T, 3>>& v) {
        return ADVec3ScaleExpr<T>(x, alpha, v);
    }

    template <typename T>
    class Vec3ADScaleExpr {
    public:
        Vec3ADScaleExpr(const Vec<T, 3>& x,
                        ADScalar<T>& alpha,
                        ADVec<Vec<T, 3>>& vObj)
                : x(x), alpha(alpha), vObj(vObj) {
            const T& a = alpha.value;
            Vec<T, 3>& v = vObj.value();
            Vec3ScaleCore(a, x, v);
        }

        void forward() {
//            input:
            const T& ab = alpha.bvalue;
//            output:
            Vec<T, 3>& vb = vObj.bvalue();
//            operations:
            Vec3ScaleCore(ab, x, vb);
        }

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
//            output:
            T& ab = alpha.bvalue;
//            operations:
            ab = Vec3DotCore<T, Vec<T, 3>>(vb, x);
        };

        const Vec<T, 3>& x;
        ADVec<Vec<T, 3>>& vObj;
        ADScalar<T>& alpha;
    };

    template <typename T>
    inline Vec3ADScaleExpr<T> Vec3Scale(const Vec<T, 3>& x,
                                        ADScalar<T>& alpha,
                                        ADVec<Vec<T, 3>>& v) {
        return Vec3ADScaleExpr<T>(x, alpha, v);
    }

    template <typename T>
    class ADVec3ADScaleExpr {
    public:
        ADVec3ADScaleExpr(ADVec<Vec<T, 3>>& xObj,
                          ADScalar<T>& alpha,
                          ADVec<Vec<T, 3>>& vObj)
                : xObj(xObj), alpha(alpha), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            Vec<T, 3>& v = vObj.value();
            Vec3ScaleCore(a, x, v);
        }

        void forward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& xb = xObj.bvalue();
            const T& a = alpha.value;
            const T& ab = alpha.bvalue;
//            output:
            Vec<T, 3>& vb = vObj.bvalue();
//            operations:
            Vec3AXPBYCore(ab, x, a, xb, vb);
        }

        void reverse() {
//            input:
            const Vec<T, 3>& vb = vObj.bvalue();
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
            T& ab = alpha.bvalue;
//            operations:
            ab = Vec3DotCore<T, Vec<T, 3>>(vb, x);
            Vec3ScaleCore(a, vb, xb);
        }

        ADVec<Vec<T, 3>>& xObj;
        ADVec<Vec<T, 3>>& vObj;
        ADScalar<T>& alpha;
    };

    template <typename T>
    inline ADVec3ADScaleExpr<T> Vec3Scale(ADVec<Vec<T, 3>>& x,
                                          ADScalar<T>& alpha,
                                          ADVec<Vec<T, 3>>& v) {
        return ADVec3ADScaleExpr<T>(x, alpha, v);
    }


    /*
        Vec3Dot
        This represents vector-vector dot product (inner product) of two 3 vectors
        alpha = xObj . yObj
        A.K.A.
        alpha = xObj @ yObj (in numpy notation)
    */
    template <typename T>
    inline void Vec3Dot(const Vec<T, 3>& x,
                        const Vec<T, 3>& y,
                        T& alpha) {
        alpha = Vec3DotCore<T>(x, y);
    }

    template <typename T>
    class ADVec3DotVecExpr {
    public:
        ADVec3DotVecExpr(ADVec<Vec<T, 3>>& xObj,
                         const Vec<T, 3>& y,
                         ADScalar<T>& alpha)
                : xObj(xObj), y(y), alpha(alpha) {
            const Vec<T, 3>& x = xObj.value();

            alpha.value = Vec3DotCore<T, Vec<T, 3>>(x, y);
        }

        void forward() {
//            input:
            const Vec<T, 3>& xb = xObj.bvalue();
//            output:
            T& ab = alpha.bvalue;
//            operations:
            ab = Vec3DotCore<T, Vec<T, 3>>(xb, y);
        }

        void reverse() {
//            input:
            const T& ab = alpha.bvalue;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3ScaleCore(ab, y, xb);
        }

        ADVec<Vec<T, 3>>& xObj;
        const Vec<T, 3>& y;
        ADScalar<T>& alpha;
    };

    template <typename T>
    inline ADVec3DotVecExpr<T> Vec3Dot(ADVec<Vec<T, 3>>& x,
                                       const Vec<T, 3>& y,
                                       ADScalar<T>& alpha) {
        return ADVec3DotVecExpr<T>(x, y, alpha);
    }

//    TODO: Vec3DotADVecExpr (??? is this necessary because its equivalent to just swapping order?)
// ANSWER: not necessary

    template <typename T>
    class ADVec3DotADVecExpr {
    public:
        ADVec3DotADVecExpr(ADVec<Vec<T, 3>>& xObj,
                           ADVec<Vec<T, 3>>& yObj,
                           ADScalar<T>& alpha)
                : xObj(xObj), yObj(yObj), alpha(alpha) {
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& y = yObj.value();

            alpha.value = Vec3DotCore<T, Vec<T, 3>>(x, y);
        }

        void forward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& xb = xObj.bvalue();
            const Vec<T, 3>& y = yObj.value();
            const Vec<T, 3>& yb = yObj.bvalue();
//            output:
            T& ab = alpha.bvalue;
//            operations:
            ab = Vec3DotCore<T, Vec<T, 3>>(xb, y) + Vec3DotCore<T, Vec<T, 3>>(x, yb);
        }

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
        }

        ADVec<Vec<T, 3>>& xObj;
        ADVec<Vec<T, 3>>& yObj;
        ADScalar<T>& alpha;
    };

    template <typename T>
    inline ADVec3DotADVecExpr<T> Vec3Dot(ADVec<Vec<T, 3>>& x,
                                         ADVec<Vec<T, 3>>& y,
                                         ADScalar<T>& alpha) {
        return ADVec3DotADVecExpr<T>(x, y, alpha);
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
    */
    template <typename T>
    inline void Vec3Normalize(const Vec<T, 3>& x,
                              Vec<T, 3>& v) {
        Vec3ScaleCore(1 / Vec3NormCore<T>(x), x, v);
        // ^ this is a candidate for the fast inverse square root algorithm
    }

    template <typename T>
    class ADVec3NormalizeExpr {
    public:
        ADVec3NormalizeExpr(ADVec<Vec<T, 3>>& xObj,
                            ADVec<Vec<T, 3>>& vObj)
                : xObj(xObj), vObj(vObj) {
            const Vec<T, 3>& x = xObj.value();
            Vec<T, 3>& v = vObj.value();
//            T normSquared = Vec3DotCore<T>(x, x);
//            normInv = 1 / sqrt(normSquared);  // This is a candidate for the fast inverse square root algorithm
//            negativeCubedNormInv = -normInv * normInv * normInv;
            negativeSquaredNormInv = 1 / Vec3DotCore<T>(x, x);
            normInv = sqrt(negativeSquaredNormInv);
            negativeSquaredNormInv *= -1;
            Vec3ScaleCore(normInv, x, v);
        }

        void forward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& xb = xObj.bvalue();
            const Vec<T, 3>& v = vObj.value();
//            output:
            Vec<T, 3>& vb = vObj.bvalue();
//            operations:
            Vec3AXPBYCore(normInv, xb, negativeSquaredNormInv * Vec3DotCore<T>(xb, x), v, vb);
        }

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& vb = vObj.bvalue();
            const Vec<T, 3>& v = vObj.value();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Vec3AXPBYCore(normInv, vb, negativeSquaredNormInv * Vec3DotCore<T>(vb, x), v, xb);
        }

        ADVec<Vec<T, 3>>& xObj;
        ADVec<Vec<T, 3>>& vObj;

    private:
        T normInv;
        T negativeSquaredNormInv;
    };

    template <typename T>
    inline ADVec3NormalizeExpr<T> Vec3Normalize(ADVec<Vec<T, 3>>& xObj,
                                                ADVec<Vec<T, 3>>& vObj) {
        return ADVec3NormalizeExpr<T>(xObj, vObj);
    }


//    QUESTION: Should I implement a SymMat and ADSymMat type? I think it will speed up these calculations significantly

    /*
        Vec3ScaleSymmetricOuterProduct
        This represents a scaled, 3 vector outer product with itself
        sObj = alpha * xObj . (xObj^T)

        NOTE: there are significant improvements that can be made to this if the symmetries are taken advantage of,
        especially if a symmetric matrix type (class) is implemented
    */
    template <typename T>
    inline void Vec3ScaleSymmetricOuterProduct(const T& alpha,
                                               const Vec<T, 3>& x,
                                               Mat<T, 3, 3>& S) {
        Vec3OuterProductScaleCore(alpha, x, x, S);
    }

    template <typename T>
    class ADVec3ScaleSymmetricOuterProductExpr {
    public:
        ADVec3ScaleSymmetricOuterProductExpr(const T& alpha,
                                             ADVec<Vec<T, 3>>& xObj,
                                             ADMat<Mat<T, 3, 3>>& sObj)
                : alpha(alpha), xObj(xObj), sObj(sObj) {
            const Vec<T, 3>& x = xObj.value();
            Mat<T, 3, 3>& S = sObj.value();
            Vec3OuterProductScaleCore(alpha, x, x, S);
        };

        void forward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& xb = xObj.bvalue();
//            output:
            Vec<T, 3> ax;
            Mat<T, 3, 3>& Sb = sObj.bvalue();
//            operations:
            Vec3ScaleCore<T, Vec<T, 3>>(alpha, x, ax);
            Vec3OuterProductCore(xb, ax, Sb);
            Vec3OuterProductAddCore(ax, xb, Sb);
            // ^ NOTE: This can be made faster by using the fact that the result will be symmetric
        }

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Mat<T, 3, 3>& Sb = sObj.bvalue();
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
//            operations:
            Mat3x3VecMultScaleCore(2 * alpha, Sb, x, xb);
        }

        ADVec<Vec<T, 3>>& xObj;
        ADMat<Mat<T, 3, 3>>& sObj;
        const T& alpha;
    };

    template <typename T>
    inline ADVec3ScaleSymmetricOuterProductExpr<T> Vec3ScaleSymmetricOuterProduct(const T& alpha,
                                                                                  ADVec<Vec<T, 3>>& x,
                                                                                  ADMat<Mat<T, 3, 3>>& S) {
        return ADVec3ScaleSymmetricOuterProductExpr<T>(alpha, x, S);
    }

    template <typename T>
    class Vec3ADScaleSymmetricOuterProductExpr {
    public:
        Vec3ADScaleSymmetricOuterProductExpr(ADScalar<T>& alpha,
                                             const Vec<T, 3>& x,
                                             ADMat<Mat<T, 3, 3>>& sObj)
                : alpha(alpha), x(x), sObj(sObj) {
            const T& a = alpha.value;
            Mat<T, 3, 3>& S = sObj.value();
            Vec3OuterProductScaleCore(a, x, x, S);
        };

        void forward() {
//            input:
            const T& ab = alpha.bvalue;
//            output:
            Mat<T, 3, 3>& Sb = sObj.bvalue();
//            operations:
            Vec3OuterProductAddScaleCore(ab, x, x, Sb);
            // ^ NOTE: This can be made faster by using the fact that the result will be symmetric
        }

        void reverse() {
//            input:
            const Mat<T, 3, 3>& Sb = sObj.bvalue();
            const T& a = alpha.value;
//            output:
            T& ab = alpha.bvalue;
//            operations:
            ab = Mat3x3InnerProductCore<T>(Sb, x, x);
        }

        const Vec<T, 3>& x;
        ADMat<Mat<T, 3, 3>>& sObj;
        ADScalar<T>& alpha;
    };

    template <typename T>
    inline Vec3ADScaleSymmetricOuterProductExpr<T> Vec3ScaleSymmetricOuterProduct(ADScalar<T>& alpha,
                                                                                  const Vec<T, 3>& x,
                                                                                  ADMat<Mat<T, 3, 3>>& S) {
        return Vec3ADScaleSymmetricOuterProductExpr<T>(alpha, x, S);
    }

    template <typename T>
    class ADVec3ADScaleSymmetricOuterProductExpr {
    public:
        ADVec3ADScaleSymmetricOuterProductExpr(ADScalar<T>& alpha,
                                               ADVec<Vec<T, 3>>& xObj,
                                               ADMat<Mat<T, 3, 3>>& sObj)
                : alpha(alpha), xObj(xObj), sObj(sObj) {
            const Vec<T, 3>& x = xObj.value();
            const T& a = alpha.value;
            Mat<T, 3, 3>& S = sObj.value();
            Vec3OuterProductScaleCore(a, x, x, S);
        };

        void forward() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Vec<T, 3>& xb = xObj.bvalue();
            const T& a = alpha.value;
            const T& ab = alpha.bvalue;
//            output:
            Vec<T, 3> ax;
            Mat<T, 3, 3>& Sb = sObj.bvalue();
//            operations:
            Vec3ScaleCore<T, Vec<T, 3>>(a, x, ax);
            Vec3OuterProductCore<Vec<T, 3>, Mat<T, 3, 3>>(xb, ax, Sb);
            Vec3OuterProductAddCore<Vec<T, 3>, Mat<T, 3, 3>>(ax, xb, Sb);
            // ^ NOTE: This can be made faster by using the fact that the result will be symmetric
            Vec3OuterProductAddScaleCore<T, Vec<T, 3>, Mat<T, 3, 3>>(ab, x, x, Sb);
        }

        void reverse() {
//            input:
            const Vec<T, 3>& x = xObj.value();
            const Mat<T, 3, 3>& Sb = sObj.bvalue();
            const T& a = alpha.value;
//            output:
            Vec<T, 3>& xb = xObj.bvalue();
            T& ab = alpha.bvalue;
//            operations:
            ab = Mat3x3InnerProductCore<T, Vec<T, 3>, Mat<T, 3, 3>>(Sb, x, x);
            Mat3x3VecMultScaleCore(2 * a, Sb, x, xb);
        }

        ADVec<Vec<T, 3>>& xObj;
        ADMat<Mat<T, 3, 3>>& sObj;
        ADScalar<T>& alpha;
    };

    template <typename T>
    inline ADVec3ADScaleSymmetricOuterProductExpr<T> Vec3ScaleSymmetricOuterProduct(ADScalar<T>& alpha,
                                                                                    ADVec<Vec<T, 3>>& x,
                                                                                    ADMat<Mat<T, 3, 3>>& S) {
        return ADVec3ADScaleSymmetricOuterProductExpr<T>(alpha, x, S);
    }



    /*
        TODO
        Vec3SymmetricOuterProduct
        ...
    */



    /*
        TODO
        Vec3VecOuterProduct
        ...
    */

}  // namespace A2D

#endif //A2D_VECTOR_OPERATION_DEVELOPMENT_H
