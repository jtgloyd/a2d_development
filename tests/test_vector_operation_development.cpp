
#include <gtest/gtest.h>

#include "a2dobjs.h"
#include "a2dtypes.h"
#include "vector_operation_development.h"
#include "test_commons.h"

using I = int;  /*UNQ_TC_TD_01*/
using T = double;  /*UNQ_TC_TD_01*/
using Vec_t = A2D::Vec<T, 3>;  /*UNQ_TC_TD_01*/
using ADVec_t = A2D::ADVec<Vec_t>;  /*UNQ_TC_TD_01*/
using Mat_t = A2D::Mat<T, 3, 3>;  /*UNQ_TC_TD_01*/
using ADMat_t = A2D::ADMat<Mat_t>;  /*UNQ_TC_TD_01*/
using ADScalar_t = A2D::ADScalar<T>;  /*UNQ_TC_TD_01*/

class vector_operation_developmentTest : public ::testing::Test {
protected:
    // Input Options:
    const T x_data[3] = {0.05487961748591952, 0.24589631152059166, 0.14089245122866312};
    const T a_data = 0.9426026707212607;
    const T v_data[3] = {0.6038030685108623, 0.9683377459053351, 0.33073954332993993};
    const T y_data[3] = {0.23420975942632027, 0.1995319286226539, 0.06989871791701063};
    const T S_data[9] = {0.602841238050233, 1.0739289161074699, 1.2614571800985452, 1.0739289161074699, 0.1098837545217537, 1.5173777268660207, 1.2614571800985452, 1.5173777268660207, 1.8825352218960931};
    const T xb_data[3] = {0.39041153534809747, 0.17688663798798576, 0.5446278080900379};
    const T ab_data = 0.43329628121652664;
    const T vb_data[3] = {0.2177166966055175, 0.7594273345561086, 0.14301953163680148};
    const T yb_data[3] = {0.60811060877918, 0.7230811256889814, 0.2763096011924536};
    const T Sb_data[9] = {0.2518778240713093, 0.5791395811055904, 0.6566999231869227, 0.5791395811055904, 0.12823124204359715, 1.2002220391070737, 0.6566999231869227, 1.2002220391070737, 1.2755595533645294};
};  /*UNQ_TC_TIC_01*/

class Vec3Norm : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Norm_Vec : public Vec3Norm {
protected:
    // Results
    const T a_out = 0.2886649463444668;
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

class Vec3Norm_ADVec : public Vec3Norm {
protected:
    // Results
    const T a_out = 0.2886649463444668;
    const T ab_out = 0.49072586139564944;
    const T xb_out[3] = {0.08237624440502214, 0.3690990495936094, 0.2114845461561903};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Norm_ADVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t xb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFP_03*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3Norm(x_ad, a_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Norm_ADVec, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFF_03*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Norm(x_ad, a_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFF_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Norm_ADVec, reverse) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFR_01*/
    T ab(ab_data);  /*UNQ_TF_TFR_01*/
    Vec_t xb;  /*UNQ_TF_TFR_02*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFR_03*/
    ADScalar_t a_ad(0, ab);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Norm(x_ad, a_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Scale : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Scale_VecScalar : public Vec3Scale {
protected:
    // Results
    const T v_out[3] = {0.051729674010388936, 0.2317825199598168, 0.13280560081260281};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_VecScalar, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t v;  /*UNQ_TF_TFP_02*/
    // Evaluations:
    A2D::Vec3Scale(x, a, v);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v, v_out);  /*UNQ_TF_TFP_06*/
}

class Vec3Scale_ADVecScalar : public Vec3Scale {
protected:
    // Results
    const T v_out[3] = {0.051729674010388936, 0.2317825199598168, 0.13280560081260281};
    const T vb_out[3] = {0.36800295589950455, 0.1667338173823802, 0.5133676264547359};
    const T xb_out[3] = {0.20522033968097123, 0.7158382337713162, 0.1348105924861529};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_ADVecScalar, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb, xb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3Scale(x_ad, a, v_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Scale_ADVecScalar, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    T a(a_data);  /*UNQ_TF_TFF_01*/
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
    Vec_t x(x_data), vb(vb_data);  /*UNQ_TF_TFR_01*/
    T a(a_data);  /*UNQ_TF_TFR_01*/
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
    const T v_out[3] = {0.051729674010388936, 0.2317825199598168, 0.13280560081260281};
    const T vb_out[3] = {0.02377913417123439, 0.10654595734673292, 0.061048175168860574};
    const T ab_out = 0.21883896185115456;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_VecADScalar, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb;  /*UNQ_TF_TFP_02*/
    ADVec_t v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3Scale(x, a_ad, v_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Scale_VecADScalar, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFF_01*/
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t v, vb;  /*UNQ_TF_TFF_02*/
    ADVec_t v_ad(v, vb);  /*UNQ_TF_TFF_03*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x, a_ad, v_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFF_06*/
    expect_vec_eq<3>(v_ad.bvalue(), vb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Scale_VecADScalar, reverse) {
    // Declarations and Initializations:
    Vec_t x(x_data), vb(vb_data);  /*UNQ_TF_TFR_01*/
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Vec_t v;  /*UNQ_TF_TFR_02*/
    ADVec_t v_ad(v, vb);  /*UNQ_TF_TFR_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x, a_ad, v_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFR_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Scale_ADVecADScalar : public Vec3Scale {
protected:
    // Results
    const T v_out[3] = {0.051729674010388936, 0.2317825199598168, 0.13280560081260281};
    const T vb_out[3] = {0.39178209007073894, 0.2732797747291131, 0.5744158016235965};
    const T xb_out[3] = {0.20522033968097123, 0.7158382337713162, 0.1348105924861529};
    const T ab_out = 0.21883896185115456;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Scale_ADVecADScalar, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb, xb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3Scale(x_ad, a_ad, v_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Scale_ADVecADScalar, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t v, vb;  /*UNQ_TF_TFF_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFF_03*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a_ad, v_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFF_06*/
    expect_vec_eq<3>(v_ad.bvalue(), vb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Scale_ADVecADScalar, reverse) {
    // Declarations and Initializations:
    Vec_t x(x_data), vb(vb_data);  /*UNQ_TF_TFR_01*/
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Vec_t v, xb;  /*UNQ_TF_TFR_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFR_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Scale(x_ad, a_ad, v_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_vec_eq<3>(v_ad.value(), v_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Dot : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Dot_VecVec : public Vec3Dot {
protected:
    // Results
    const T a_out = 0.07176570899275475;
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

class Vec3Dot_ADVecVec : public Vec3Dot {
protected:
    // Results
    const T a_out = 0.07176570899275475;
    const T ab_out = 0.1648015093239036;
    const T xb_out[3] = {0.10148221778404191, 0.08645644265615736, 0.03028685453524371};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Dot_ADVecVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFP_01*/
    Vec_t xb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFP_03*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3Dot(x_ad, y, a_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Dot_ADVecVec, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFF_03*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y, a_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFF_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Dot_ADVecVec, reverse) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFR_01*/
    T ab(ab_data);  /*UNQ_TF_TFR_01*/
    Vec_t xb;  /*UNQ_TF_TFR_02*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFR_03*/
    ADScalar_t a_ad(0, ab);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y, a_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Dot_ADVecADVec : public Vec3Dot {
protected:
    // Results
    const T a_out = 0.07176570899275475;
    const T ab_out = 0.4149073056699317;
    const T xb_out[3] = {0.10148221778404191, 0.08645644265615736, 0.03028685453524371};
    const T yb_out[3] = {0.0237791341712344, 0.10654595734673293, 0.06104817516886058};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Dot_ADVecADVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFP_01*/
    Vec_t xb, yb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb), y_ad(y, yb);  /*UNQ_TF_TFP_03*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3Dot(x_ad, y_ad, a_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3Dot_ADVecADVec, forward) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data), xb(xb_data), yb(yb_data);  /*UNQ_TF_TFF_01*/
    ADVec_t x_ad(x, xb), y_ad(y, yb);  /*UNQ_TF_TFF_03*/
    ADScalar_t a_ad(0, 0);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y_ad, a_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFF_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3Dot_ADVecADVec, reverse) {
    // Declarations and Initializations:
    Vec_t x(x_data), y(y_data);  /*UNQ_TF_TFR_01*/
    T ab(ab_data);  /*UNQ_TF_TFR_01*/
    Vec_t xb, yb;  /*UNQ_TF_TFR_02*/
    ADVec_t x_ad(x, xb), y_ad(y, yb);  /*UNQ_TF_TFR_03*/
    ADScalar_t a_ad(0, ab);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3Dot(x_ad, y_ad, a_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_val_eq(a_ad.value, a_out);  /*UNQ_TF_TFR_06*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
    expect_vec_eq<3>(y_ad.bvalue(), yb_out);  /*UNQ_TF_TFR_07*/
}

class Vec3Normalize : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3Normalize_Vec : public Vec3Normalize {
protected:
    // Results
    const T v_out[3] = {0.1901152813353067, 0.8518398739941256, 0.4880829938406679};
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

class Vec3Normalize_ADVec : public Vec3Normalize {
protected:
    // Results
    const T v_out[3] = {0.1901152813353067, 0.8518398739941256, 0.4880829938406679};
    const T vb_out[3] = {1.0292799798275472, -0.835339451507895, 1.0569792569857595};
    const T xb_out[3] = {0.2549285670724711, 0.39367935299273793, -0.7863777094067483};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3Normalize_ADVec, passive) {
    // Declarations and Initializations:
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Vec_t v, vb, xb;  /*UNQ_TF_TFP_02*/
    ADVec_t x_ad(x, xb), v_ad(v, vb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3Normalize(x_ad, v_ad);  /*UNQ_TF_TFP_04*/
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

class Vec3ScaleSymmetricOuterProduct : public vector_operation_developmentTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3ScaleSymmetricOuterProduct_ScalarVec : public Vec3ScaleSymmetricOuterProduct {
protected:
    // Results
    const T S_out[9] = {0.0028389047223614573, 0.01272013603531725, 0.007288320572583365, 0.01272013603531725, 0.056994466733066865, 0.03265640738909512, 0.007288320572583365, 0.03265640738909512, 0.018711306635382945};
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

class Vec3ScaleSymmetricOuterProduct_ADScalarVec : public Vec3ScaleSymmetricOuterProduct {
protected:
    // Results
    const T S_out[9] = {0.0028389047223614573, 0.01272013603531725, 0.007288320572583365, 0.01272013603531725, 0.056994466733066865, 0.03265640738909512, 0.007288320572583365, 0.03265640738909512, 0.018711306635382945};
    const T Sb_out[9] = {0.0013049897874637013, 0.005847201383859798, 0.0033503005014804787, 0.005847201383859798, 0.02619925791899191, 0.015011521099085788, 0.0033503005014804787, 0.015011521099085788, 0.008601227042577571};
    const T ab_out = 0.142782050042545;
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarVec, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFP_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFP_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x, S_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarVec, forward) {
    // Declarations and Initializations:
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFF_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFF_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFF_03*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x, S_ad);  /*UNQ_TF_TFF_04*/
    expr.forward();  /*UNQ_TF_TFF_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFF_06*/
    expect_mat_eq<3, 3>(S_ad.bvalue(), Sb_out);  /*UNQ_TF_TFF_07*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarVec, reverse) {
    // Declarations and Initializations:
    Mat_t Sb(Sb_data);  /*UNQ_TF_TFR_01*/
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFR_01*/
    Mat_t S;  /*UNQ_TF_TFR_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFR_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
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
    const T S_out[9] = {0.0028389047223614573, 0.01272013603531725, 0.007288320572583365, 0.01272013603531725, 0.056994466733066865, 0.03265640738909512, 0.007288320572583365, 0.03265640738909512, 0.018711306635382945};
    const T Sb_out[9] = {0.040391722906905035, 0.09964085760427532, 0.08002225748556513, 0.09964085760427532, 0.0819984614001504, 0.14972674203301628, 0.08002225748556513, 0.14972674203301628, 0.14465924654529685};
    const T xb_out[3] = {0.4689548341984216, 0.4381533423353795, 0.963125629082972};
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
    A2D::Vec3ScaleSymmetricOuterProduct(a, x_ad, S_ad);  /*UNQ_TF_TFP_04*/
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
    Mat_t Sb(Sb_data);  /*UNQ_TF_TFR_01*/
    T a(a_data);  /*UNQ_TF_TFR_01*/
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

class Vec3ScaleSymmetricOuterProduct_ADScalarADVec : public Vec3ScaleSymmetricOuterProduct {
protected:
    // Results
    const T S_out[9] = {0.0028389047223614573, 0.01272013603531725, 0.007288320572583365, 0.01272013603531725, 0.056994466733066865, 0.03265640738909512, 0.007288320572583365, 0.03265640738909512, 0.018711306635382945};
    const T Sb_out[9] = {0.04169671269436873, 0.10548805898813512, 0.08337255798704561, 0.10548805898813512, 0.10819771931914231, 0.16473826313210208, 0.08337255798704561, 0.16473826313210208, 0.15326047358787442};
    const T ab_out = 0.142782050042545;
    const T xb_out[3] = {0.4689548341984216, 0.4381533423353795, 0.963125629082972};
};  /*UNQ_TF_FTV_01*/

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarADVec, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_TF_TFP_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFP_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFP_02*/
    Vec_t xb;  /*UNQ_TF_TFP_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFP_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFP_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFP_03*/
    // Evaluations:
    A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x_ad, S_ad);  /*UNQ_TF_TFP_04*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFP_05*/
}

TEST_F(Vec3ScaleSymmetricOuterProduct_ADScalarADVec, forward) {
    // Declarations and Initializations:
    T a(a_data), ab(ab_data);  /*UNQ_TF_TFF_01*/
    Vec_t x(x_data), xb(xb_data);  /*UNQ_TF_TFF_01*/
    Mat_t S, Sb;  /*UNQ_TF_TFF_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFF_03*/
    ADScalar_t a_ad(a, ab);  /*UNQ_TF_TFF_03*/
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
    Mat_t Sb(Sb_data);  /*UNQ_TF_TFR_01*/
    T a(a_data);  /*UNQ_TF_TFR_01*/
    Vec_t x(x_data);  /*UNQ_TF_TFR_01*/
    Mat_t S;  /*UNQ_TF_TFR_02*/
    Vec_t xb;  /*UNQ_TF_TFR_02*/
    ADMat_t S_ad(S, Sb);  /*UNQ_TF_TFR_03*/
    ADScalar_t a_ad(a, 0);  /*UNQ_TF_TFR_03*/
    ADVec_t x_ad(x, xb);  /*UNQ_TF_TFR_03*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleSymmetricOuterProduct(a_ad, x_ad, S_ad);  /*UNQ_TF_TFR_04*/
    expr.reverse();  /*UNQ_TF_TFR_05*/
    // Comparisons:
    expect_mat_eq<3, 3>(S_ad.value(), S_out);  /*UNQ_TF_TFR_06*/
    expect_val_eq(a_ad.bvalue, ab_out);  /*UNQ_TF_TFR_07*/
    expect_vec_eq<3>(x_ad.bvalue(), xb_out);  /*UNQ_TF_TFR_07*/
}
