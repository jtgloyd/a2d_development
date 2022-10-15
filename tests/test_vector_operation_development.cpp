
#include <gtest/gtest.h>

#include "a2dobjs.h"
#include "a2dtypes.h"
#include "vector_operation_development.h"
#include "test_commons.h"

using T = double;  /*UNQ_TC_TD_01*/
using ADScalar_t = A2D::ADScalar<T>;  /*UNQ_TC_TD_01*/
using Vec_t = A2D::Vec<T, 3>;  /*UNQ_TC_TD_01*/
using Mat_t = A2D::Mat<T, 3, 3>;  /*UNQ_TC_TD_01*/
using ADMat_t = A2D::ADMat<Mat_t>;  /*UNQ_TC_TD_01*/
using ADVec_t = A2D::ADVec<Vec_t>;  /*UNQ_TC_TD_01*/
using I = int;  /*UNQ_TC_TD_01*/

class vector_operation_developmentTest : public ::testing::Test {
protected:
    // Input Options:
    const T x_data[3] = {0.6997085942135798, 0.9471398850319938, 0.09615581263753803};
    const T a_data = 0.675186012167962;
    const T v_data[3] = {0.00824907101533956, 0.1752440719052778, 0.028262995802690538};
    const T y_data[3] = {0.17364532414090939, 0.41083978571414315, 0.33905981280121733};
    const T S_data[9] = {1.7969010114780788, 0.46650142443174414, 0.7232310348453856, 0.46650142443174414, 1.8842020942744466, 1.708838738066331, 0.7232310348453856, 1.708838738066331, 1.7711748125830122};
    const T xb_data[3] = {0.5178332377412588, 0.6680503778214888, 0.19823130070172934};
    const T ab_data = 0.06069463626674265;
    const T vb_data[3] = {0.09927613648164724, 0.8604733016976351, 0.684492047583691};
    const T yb_data[3] = {0.5650226129261964, 0.3910203176346104, 0.5083149423164457};
    const T Sb_data[9] = {0.996921580330169, 1.51191166066541, 1.2345785556877065, 1.51191166066541, 0.1183271982162859, 0.7459064506630303, 1.2345785556877065, 0.7459064506630303, 0.7734236713020877};
};  /*UNQ_TC_TIC_01*/

class Vec3Norm : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Norm_ADVec : public Vec3Norm {
protected:
    // Results
    const T a_out = 1.1814872064219517;
    const T ab_out = 0.8583509082106944;
    const T xb_out[3] = {0.03594500083256932, 0.04865588937677491, 0.004939657442963567};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Norm_ADVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t xb;  /*UNQ_TF_TFP_02*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFP_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3Norm(x_ad, a_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Norm_ADVec, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFF_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Norm(x_ad, a_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFF_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Norm_ADVec, reverse) {
    // Declarations and Initializations:
    T ab(ab_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFR_01*/
    Vec_t xb;  /*UNQ_TF_TFR_02*/
    ADScalar_t a_ad(0, ab);  /*UNQ_TF_TFR_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Norm(x_ad, a_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Norm_Vec : public Vec3Norm {
protected:
    // Results
    const T a_out = 1.1814872064219517;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Norm_Vec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    T a;  /*UNQ_TF_TFP_02*/
    // Evaluations:
    A2D::Vec3Norm(x, a);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a, a_out);  /*UNQ_TF_TFP_06*/
}

class Vec3Scale : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Scale_ADVecADScalar : public Vec3Scale {
protected:
    // Results
    const T v_out[3] = {0.47243345540671766, 0.6394956019399739, 0.06492305968150903};
    const T vb_out[3] = {0.3921023173770517, 0.5085445813443327, 0.1396791434806372};
    const T xb_out[3] = {0.06702985869448573, 0.580979537150226, 0.4621594559687152};
    const T ab_out = 0.9502708390188692;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_ADVecADScalar, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb, xb;  /*UNQ_TF_TFP_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a_ad, v_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Scale_ADVecADScalar, forward) {
    // Declarations and Initializations:
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    Vec_t v, vb;  /*UNQ_TF_TFF_02*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a_ad, v_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFF_06*/
    expect_vec_eq<3>(v_ad.bvalue(), vb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Scale_ADVecADScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data), vb(vb_data);  /*UNQ_TF_TFR_01*/
    Vec_t v, xb;  /*UNQ_TF_TFR_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a_ad, v_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Scale_ADVecScalar : public Vec3Scale {
protected:
    // Results
    const T v_out[3] = {0.47243345540671766, 0.6394956019399739, 0.06492305968150903};
    const T vb_out[3] = {0.3496337587585447, 0.4510582705285914, 0.13384300140766878};
    const T xb_out[3] = {0.06702985869448573, 0.580979537150226, 0.4621594559687152};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_ADVecScalar, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb, xb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a, v_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Scale_ADVecScalar, forward) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    Vec_t v, vb;  /*UNQ_TF_TFF_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a, v_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFF_06*/
    expect_vec_eq<3>(v_ad.bvalue(), vb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Scale_ADVecScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data), vb(vb_data);  /*UNQ_TF_TFR_01*/
    Vec_t v, xb;  /*UNQ_TF_TFR_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a, v_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Scale_VecADScalar : public Vec3Scale {
protected:
    // Results
    const T v_out[3] = {0.47243345540671766, 0.6394956019399739, 0.06492305968150903};
    const T vb_out[3] = {0.04246855861850706, 0.05748631081574132, 0.005836142072968427};
    const T ab_out = 0.9502708390188692;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_VecADScalar, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb;  /*UNQ_TF_TFP_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    ADVec_t v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x, a_ad, v_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Scale_VecADScalar, forward) {
    // Declarations and Initializations:
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFF_01*/
    Vec_t v, vb;  /*UNQ_TF_TFF_02*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
    ADVec_t v_ad(v, vb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x, a_ad, v_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFF_06*/
    expect_vec_eq<3>(v_ad.bvalue(), vb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Scale_VecADScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data), vb(vb_data);  /*UNQ_TF_TFR_01*/
    Vec_t v;  /*UNQ_TF_TFR_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
    ADVec_t v_ad(v, vb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x, a_ad, v_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFR_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Scale_VecScalar : public Vec3Scale {
protected:
    // Results
    const T v_out[3] = {0.47243345540671766, 0.6394956019399739, 0.06492305968150903};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_VecScalar, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t v;  /*UNQ_TF_TFP_02*/
    // Evaluations:
    A2D::Vec3Scale(x, a, v);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v, v_out);  /*UNQ_TF_TFP_06*/
}

class Vec3Dot : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Dot_ADVecADVec : public Vec3Dot {
protected:
    // Results
    const T a_out = 0.5432264448868922;
    const T ab_out = 1.2461728154295526;
    const T xb_out[3] = {0.010539339788153123, 0.024935771357826417, 0.02057911201063974};
    const T yb_out[3] = {0.042468558618507055, 0.057486310815741314, 0.005836142072968427};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Dot_ADVecADVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFP_01*/
    Vec_t xb, yb;  /*UNQ_TF_TFP_02*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFP_03*/
    ADVec_t x_ad(x, xb), y_ad(y, yb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y_ad, a_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Dot_ADVecADVec, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data), xb(xb_data), yb(yb_data);  /*UNQ_TF_TFF_01*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFF_03*/
    ADVec_t x_ad(x, xb), y_ad(y, yb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y_ad, a_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFF_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Dot_ADVecADVec, reverse) {
    // Declarations and Initializations:
    T ab(ab_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFR_01*/
    Vec_t xb, yb;  /*UNQ_TF_TFR_02*/
    ADScalar_t a_ad(0, ab);  /*UNQ_TF_TFR_03*/
    ADVec_t x_ad(x, xb), y_ad(y, yb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y_ad, a_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
    expect_vec_eq<3>(y_ad.bvalue(), yb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Dot_ADVecVec : public Vec3Dot {
protected:
    // Results
    const T a_out = 0.5432264448868922;
    const T ab_out = 0.4315932621962205;
    const T xb_out[3] = {0.010539339788153123, 0.024935771357826417, 0.02057911201063974};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Dot_ADVecVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFP_01*/
    Vec_t xb;  /*UNQ_TF_TFP_02*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFP_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y, a_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Dot_ADVecVec, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFF_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y, a_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFF_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Dot_ADVecVec, reverse) {
    // Declarations and Initializations:
    T ab(ab_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFR_01*/
    Vec_t xb;  /*UNQ_TF_TFR_02*/
    ADScalar_t a_ad(0, ab);  /*UNQ_TF_TFR_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y, a_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Dot_VecVec : public Vec3Dot {
protected:
    // Results
    const T a_out = 0.5432264448868922;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Dot_VecVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFP_01*/
    T a;  /*UNQ_TF_TFP_02*/
    // Evaluations:
    A2D::Vec3Dot(x, y, a);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a, a_out);  /*UNQ_TF_TFP_06*/
}

class Vec3Normalize : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Normalize_ADVec : public Vec3Normalize {
protected:
    // Results
    const T v_out[3] = {0.59222697496031, 0.801650563699575, 0.08138540317227719};
    const T vb_out[3] = {0.008036207134191942, -0.01696769248849317, 0.1086546390650164};
    const T xb_out[3] = {-0.31913367976282364, 0.1825709931564465, 0.5239444978182258};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Normalize_ADVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb, xb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3Normalize(x_ad, v_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Normalize_ADVec, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    Vec_t v, vb;  /*UNQ_TF_TFF_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Normalize(x_ad, v_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFF_06*/
    expect_vec_eq<3>(v_ad.bvalue(), vb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Normalize_ADVec, reverse) {
    // Declarations and Initializations:
    Vec_t x(x_data), vb(vb_data);  /*UNQ_TF_TFR_01*/
    Vec_t v, xb;  /*UNQ_TF_TFR_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Normalize(x_ad, v_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Normalize_Vec : public Vec3Normalize {
protected:
    // Results
    const T v_out[3] = {0.59222697496031, 0.801650563699575, 0.08138540317227719};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Normalize_Vec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t v;  /*UNQ_TF_TFP_02*/
    // Evaluations:
    A2D::Vec3Normalize(x, v);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v, v_out);  /*UNQ_TF_TFP_06*/
}

class Vec3ScaleSymmetricOuterProduct : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3ScaleSymmetricOuterProduct_ADScalarADVec : public Vec3ScaleSymmetricOuterProduct {
protected:
    // Results
    const T S_out[9] = {0.3305657489420984, 0.44746056863918615, 0.045427222821793026, 0.44746056863918615, 0.6056917908998926, 0.06149121928266973, 0.045427222821793026, 0.06149121928266973, 0.0062427295625908825};
    const T Sb_out[9] = {0.518999107110335, 0.6869850921812485, 0.13135401532473837, 0.6869850921812485, 0.9088781347992946, 0.17566756244717727, 0.13135401532473837, 0.17566756244717727, 0.026300744116097476};
    const T ab_out = 2.9073295776732397;
    const T xb_out[3] = {3.035985163469247, 1.6767478039605628, 2.220946277726559};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarADVec, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFP_02*/
    Vec_t xb;  /*UNQ_TF_TFP_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFP_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x_ad, S_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarADVec, forward) {
    // Declarations and Initializations:
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFF_02*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFF_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x_ad, S_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFF_06*/
    expect_mat_eq<3, 3>(S_ad.bvalue(), Sb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarADVec, reverse) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Mat_t Sb(Sb_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFR_01*/
    Mat_t S;  /*UNQ_TF_TFR_02*/
    Vec_t xb;  /*UNQ_TF_TFR_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFR_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x_ad, S_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFR_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFR_07*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3ScaleSymmetricOuterProduct_ADScalarVec : public Vec3ScaleSymmetricOuterProduct {
protected:
    // Results
    const T S_out[9] = {0.3305657489420984, 0.44746056863918615, 0.045427222821793026, 0.44746056863918615, 0.6056917908998926, 0.06149121928266973, 0.045427222821793026, 0.06149121928266973, 0.0062427295625908825};
    const T Sb_out[9] = {0.029715615449232582, 0.040223665727407265, 0.004083598765507466, 0.040223665727407265, 0.05444757781693469, 0.005527642932021698, 0.004083598765507466, 0.005527642932021698, 0.000561178983694405};
    const T ab_out = 2.9073295776732397;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarVec, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFP_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x, S_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarVec, forward) {
    // Declarations and Initializations:
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFF_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFF_02*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x, S_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFF_06*/
    expect_mat_eq<3, 3>(S_ad.bvalue(), Sb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarVec, reverse) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Mat_t Sb(Sb_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFR_01*/
    Mat_t S;  /*UNQ_TF_TFR_02*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x, S_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFR_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFR_07*/
}

class Vec3ScaleSymmetricOuterProduct_ScalarADVec : public Vec3ScaleSymmetricOuterProduct {
protected:
    // Results
    const T S_out[9] = {0.3305657489420984, 0.44746056863918615, 0.045427222821793026, 0.44746056863918615, 0.6056917908998926, 0.06149121928266973, 0.045427222821793026, 0.06149121928266973, 0.0062427295625908825};
    const T Sb_out[9] = {0.4892834916611024, 0.6467614264538412, 0.12727041655923088, 0.6467614264538412, 0.8544305569823599, 0.17013991951515559, 0.12727041655923088, 0.17013991951515559, 0.025739565132403074};
    const T xb_out[3] = {3.035985163469247, 1.6767478039605628, 2.220946277726559};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3ScaleSymmetricOuterProduct_ScalarADVec, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFP_02*/
    Vec_t xb;  /*UNQ_TF_TFP_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFP_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a, x_ad, S_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ScalarADVec, forward) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFF_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFF_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a, x_ad, S_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFF_06*/
    expect_mat_eq<3, 3>(S_ad.bvalue(), Sb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ScalarADVec, reverse) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Mat_t Sb(Sb_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFR_01*/
    Mat_t S;  /*UNQ_TF_TFR_02*/
    Vec_t xb;  /*UNQ_TF_TFR_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFR_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a, x_ad, S_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3ScaleSymmetricOuterProduct_ScalarVec : public Vec3ScaleSymmetricOuterProduct {
protected:
    // Results
    const T S_out[9] = {0.3305657489420984, 0.44746056863918615, 0.045427222821793026, 0.44746056863918615, 0.6056917908998926, 0.06149121928266973, 0.045427222821793026, 0.06149121928266973, 0.0062427295625908825};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3ScaleSymmetricOuterProduct_ScalarVec, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Mat_t S;  /*UNQ_TF_TFP_02*/
    // Evaluations:
    A2D::Vec3ScaleSymmetricOuterProduct(a, x, S);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_mat_eq<3, 3>(S, S_out);  /*UNQ_TF_TFP_06*/
}
