//
// Created by James on 10/7/2022.
//

#ifndef A2D_N_VECTOR_CORE_H
#define A2D_N_VECTOR_CORE_H

typedef unsigned int SizeType;

namespace A2D {

// TODO: before going further, ask to see if we should include N in the template or if N should be an input
    template <typename T, class VecType>
    inline T VectorNDotCore(const VecType& x, const VecType& y, const SizeType N) {
        T result = x(0) * y(0);
        for(SizeType i = N-1; i != 0; i--){
            result += x(i) * y(i);
        }
        return result;
    }

    template <typename T, class VecType>
    inline T VectorNNormCore(const VecType& x, const SizeType N) {
        return sqrt(VectorNDotCore<T, VecType>(x, x, N));
    }

}   // namespace A2D

namespace A2D {

}   // namespace A2D

#endif //A2D_N_VECTOR_CORE_H
