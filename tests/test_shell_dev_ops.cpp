/*
    This is a set of automatically generated unit tests for shell_dev_ops.h using
    Google Test framework.  These tests were written on 2022-10-30 using the
    A2DTestConstructor package.
*/

#include <gtest/gtest.h>

#include "a2dobjs.h"
#include "a2dtypes.h"
#include "shell_dev_ops.h"
#include "test_commons.h"

using T = double;  /*UNQ_TC_TD_01*/
using A2DScalar_t = A2D::A2DScalar<3, T>;  /*UNQ_TC_TD_01*/
using Vec_t = A2D::Vec<T, 3>;  /*UNQ_TC_TD_01*/
using A2DVec_t = A2D::A2DVec<3, Vec_t>;  /*UNQ_TC_TD_01*/
using Mat4x7_t = A2D::Mat<T, 4, 7>;  /*UNQ_TC_TD_01*/
using A2DMat4x7_t = A2D::A2DMat<3, Mat4x7_t>;  /*UNQ_TC_TD_01*/
using Vec7_t = A2D::Vec<T, 7>;  /*UNQ_TC_TD_01*/
using Vec4_t = A2D::Vec<T, 4>;  /*UNQ_TC_TD_01*/
using A2DVec4_t = A2D::A2DVec<3, Vec4_t>;  /*UNQ_TC_TD_01*/
using A2DVec7_t = A2D::A2DVec<3, Vec7_t>;  /*UNQ_TC_TD_01*/

class shell_dev_opsTest : public ::testing::Test {
protected:
    // Input Options:
    const T a_data = 0.616021518478398;
    const T b_data = 0.29324322133183145;
    const T X_data[3] = {0.8394748188795624, 0.3355084384295447, 0.13744077289077916};
    const T x_data = 0.16676013818331414;
    const T y_data = 0.9455413868052376;
    const T A_data[28] = {0.9324986673036278, 0.35832446161899334, 0.5452743494684774, 0.28375344696973537, 0.11144578194136678, 0.5322802893161724, 0.3888976130489119,
0.6048801200217164, 0.2587443573074818, 0.8197547723122492, 0.3297874034658086, 0.9569091435624203, 0.16352602777816594, 0.2819745586898418, 
0.8247109605070235, 0.8604270498771729, 0.7946456803810342, 0.4596583601713933, 0.7642158392823254, 0.3337282253369097, 0.10402692188572704, 
0.016568448240481426, 0.7846114081548096, 0.4847401575674857, 0.5999484164243418, 0.86063137324544, 0.13445516408722336, 0.1132067625064106};
    const T Xinner_data[4] = {0.3039282684655805, 0.21980449174157635, 0.4508081421171213, 0.15876677652976046};
    const T Yinner_data[7] = {0.3890399552319155, 0.47303898053543725, 0.5436146475060387, 0.9311562058617121, 0.20768771226355753, 0.3794185512126991, 0.04191187299733212};
    const T ab_data = 0.2668445125496999;
    const T bb_data = 0.537543067693097;
    const T zb_data = 0.37181942394898704;
    const T Xb_data[3] = {0.9748963363264409, 0.5004951661667953, 0.961697256293684};
    const T Vb_data[3] = {0.6055269131809089, 0.6065898458395677, 0.6480995872797352};
    const T xb_data = 0.26731325034875975;
    const T yb_data = 0.11797747074155873;
    const T Ab_data[28] = {0.489083878808365, 0.5093985294816511, 0.5762733704315812, 0.5760212574956043, 0.5125729645329513, 0.060400273788209, 0.4542288228865813,
0.22128003372077965, 0.47992837397212107, 0.07273074104599142, 0.24676120274215996, 0.5928400703371856, 0.36172071084916724, 0.8863289452102815, 
0.6413299311724694, 0.8158544705534897, 0.6507255797004735, 0.9425413991566923, 0.7654562248412765, 0.20172463516488548, 0.6843886082060592, 
0.998316102034082, 0.29387193465546435, 0.4338977156089675, 0.33384605768332765, 0.723549071814747, 0.18793351553030546, 0.551552486358033};
    const T Xinnerb_data[4] = {0.9377936107279649, 0.027685156906511743, 0.24434341192741782, 0.8716438172361937};
    const T Yinnerb_data[7] = {0.2758378043930759, 0.057687661985666217, 0.47371573740022166, 0.9960511663602971, 0.6096918935538898, 0.8437500470115705, 0.9918823269606065};
    const T ap0_data = 0.5452497060752673;
    const T ap1_data = 0.17203974703945468;
    const T ap2_data = 0.5902338319436345;
    const T bp0_data = 0.49171697434676664;
    const T bp1_data = 0.8549391975494786;
    const T bp2_data = 0.8635851762934134;
    const T Xp0_data[3] = {0.239198762915939, 0.859265971533978, 0.2468917240708589};
    const T Xp1_data[3] = {0.37818917827298415, 0.5066056802085267, 0.32726775934834507};
    const T Xp2_data[3] = {0.7520180907281179, 0.6580328660398679, 0.6185796039001836};
    const T xp0_data = 0.44186813103443545;
    const T xp1_data = 0.2774817629194688;
    const T xp2_data = 0.42302113053503965;
    const T yp0_data = 0.17094952997389112;
    const T yp1_data = 0.6264657715763813;
    const T yp2_data = 0.20602404215243242;
    const T Ap0_data[28] = {0.508699874448644, 0.348729110002716, 0.17674746797971508, 0.286246757218653, 0.8462000096827299, 0.42419412898531184, 0.24724150131394784,
0.9707419279290426, 0.09245466980786154, 0.4571078712341301, 0.7911102564746777, 0.7223135344469294, 0.2176664566723926, 0.901153950537916, 
0.7061025108171493, 0.22683166601907434, 0.8697715132753481, 0.9044797124792586, 0.9448765271568219, 0.8255019517984378, 0.7960149304033663, 
0.4252219659644706, 0.975782314517836, 0.4788200834596408, 0.8849446951752938, 0.9548760791148586, 0.2505406515317049, 0.10006895440651253};
    const T Ap1_data[28] = {0.4948410501872652, 0.8245271921836241, 0.8336430521554968, 0.8568690619452004, 0.4794068045346298, 0.9259697457709788, 0.5308276056969992,
0.32666957336715663, 0.8953205780422567, 0.9339999832806769, 0.8261689356980273, 0.10704001834155552, 0.6882789156251212, 0.8658568288542107, 
0.42689912728483315, 0.41428545141979867, 0.6462690004200801, 0.1264439708386098, 0.5511578054497526, 0.5273285496971344, 0.23472183499027832, 
0.06576875831914197, 0.17506587724637346, 0.49682269542288227, 0.018041663184725998, 0.01013665004565234, 0.7800797601066614, 0.9581268112334752};
    const T Ap2_data[28] = {0.09438786529162291, 0.028428702031243258, 0.6863021402371566, 0.8764474112081182, 0.35431155565512396, 0.6589517539350492, 0.0539132145064789,
0.6838156552550718, 0.744612989676942, 0.22342266898888963, 0.9195527824824643, 0.7981871198305107, 0.9582538364687051, 0.1771870549128326, 
0.13919944129256412, 0.7441212571115705, 0.5539326918555276, 0.8636711831844699, 0.4670055038100632, 0.0066338560242079625, 0.6017997171680342, 
0.6531904212329244, 0.6113720220829365, 0.5190472449501241, 0.18590216194364206, 0.08865764998817816, 0.7950030465073267, 0.6342770956415515};
    const T Xinnerp0_data[4] = {0.034009827833190065, 0.7955512916184163, 0.6435129437560846, 0.01529128142746461};
    const T Xinnerp1_data[4] = {0.7616812033472488, 0.9072985140735947, 0.1420108556963312, 0.8176745368879904};
    const T Xinnerp2_data[4] = {0.2902260871832585, 0.5869621427705588, 0.983532151499903, 0.6640961386754096};
    const T Yinnerp0_data[7] = {0.09200602567593141, 0.2381176466135404, 0.5512167180426673, 0.7324695717757135, 0.972845503619396, 0.8090263005428812, 0.9984440009646832};
    const T Yinnerp1_data[7] = {0.8450425351093434, 0.7270884328819884, 0.8798503092401676, 0.7011598736157428, 0.04103466989448201, 0.16641951194265436, 0.396210314622793};
    const T Yinnerp2_data[7] = {0.3532134875940034, 0.8644757788217853, 0.6142046319411545, 0.12307422004743251, 0.31652074462505597, 0.18850384321846314, 0.7252257783886528};
    const T zh0_data = 0.7136802451374066;
    const T zh1_data = 0.2764181866242037;
    const T zh2_data = 0.8087454027996934;
    const T Vh0_data[3] = {0.469949566295098, 0.5126249654879124, 0.9782979024319591};
    const T Vh1_data[3] = {0.8253821022235273, 0.7431586254450954, 0.8223767677975246};
    const T Vh2_data[3] = {0.7671950078166472, 0.9927146021208949, 0.64244798108166};
    const T ah0_data = 0.7412169271716516;
    const T ah1_data = 0.5573710995133562;
    const T ah2_data = 0.1746418032048671;
};  /*UNQ_TC_TIC_01*/

class ScalarMult : public shell_dev_opsTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class ScalarMult_A2DScalarScalar : public ScalarMult {
protected:
    // Results
    const T z_out = 0.18064413448833178;
    const T ab_out = 0.10903352563254688;
    const T zp0_out = 0.15989078023974565;
    const T zp1_out = 0.0504494896189631;
    const T zp2_out = 0.17308207021818225;
    const T ah0_out = 0.20928189408498424;
    const T ah1_out = 0.08105775948038485;
    const T ah2_out = 0.23715910715429167;
};  /*UNQ_T2F_FTV_01*/

TEST_F(ScalarMult_A2DScalarScalar, passive) {
    // Declarations and Initializations:
    T a(a_data), b(b_data);  /*UNQ_T2F_TFP_01*/
    A2DScalar_t a_a2d(a, 0), z_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::ScalarMult(a_a2d, b, z_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(ScalarMult_A2DScalarScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data), b(b_data), zb(zb_data);  /*UNQ_T2F_TFR_01*/
    A2DScalar_t a_a2d(a, 0), z_a2d(0, zb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::ScalarMult(a_a2d, b, z_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFR_06*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(ScalarMult_A2DScalarScalar, hforward) {
    // Declarations and Initializations:
    T a(a_data), b(b_data), ap0(ap0_data), ap1(ap1_data), ap2(ap2_data), zb(zb_data);  /*UNQ_T2F_TFHF_01*/
    A2DScalar_t a_a2d(a, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHF_05*/
    // Evaluations:
    auto expr = A2D::ScalarMult(a_a2d, b, z_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHF_09*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(ScalarMult_A2DScalarScalar, hreverse) {
    // Declarations and Initializations:
    T a(a_data), b(b_data), ap0(ap0_data), ap1(ap1_data), ap2(ap2_data), zb(zb_data), zh0(zh0_data), zh1(zh1_data), zh2(zh2_data);  /*UNQ_T2F_TFHR_01*/
    A2DScalar_t a_a2d(a, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHR_04*/
    z_a2d.hvalue[0] = zh0;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[1] = zh1;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[2] = zh2;  /*UNQ_T2F_TFHR_05*/
    // Evaluations:
    auto expr = A2D::ScalarMult(a_a2d, b, z_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHR_10*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.hvalue[0], ah0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[1], ah1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[2], ah2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class ScalarMult_A2DScalarA2DScalar : public ScalarMult {
protected:
    // Results
    const T z_out = 0.18064413448833178;
    const T ab_out = 0.10903352563254688;
    const T bb_out = 0.22904876614081823;
    const T zp0_out = 0.46279901743844437;
    const T zp1_out = 0.577110432300096;
    const T zp2_out = 0.7050691218538858;
    const T ah0_out = 0.39211181623186164;
    const T bh0_out = 0.6423768199392351;
    const T ah1_out = 0.3989407594234656;
    const T bh1_out = 0.23424727069995102;
    const T ah2_out = 0.5582568499334055;
    const T bh2_out = 0.7176649744840029;
};  /*UNQ_T2F_FTV_01*/

TEST_F(ScalarMult_A2DScalarA2DScalar, passive) {
    // Declarations and Initializations:
    T a(a_data), b(b_data);  /*UNQ_T2F_TFP_01*/
    A2DScalar_t a_a2d(a, 0), b_a2d(b, 0), z_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::ScalarMult(a_a2d, b_a2d, z_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(ScalarMult_A2DScalarA2DScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data), b(b_data), zb(zb_data);  /*UNQ_T2F_TFR_01*/
    A2DScalar_t a_a2d(a, 0), b_a2d(b, 0), z_a2d(0, zb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::ScalarMult(a_a2d, b_a2d, z_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFR_06*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(b_a2d.bvalue, bb_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(ScalarMult_A2DScalarA2DScalar, hforward) {
    // Declarations and Initializations:
    T a(a_data), b(b_data), ap0(ap0_data), bp0(bp0_data), ap1(ap1_data), bp1(bp1_data), ap2(ap2_data), bp2(bp2_data), zb(zb_data);  /*UNQ_T2F_TFHF_01*/
    A2DScalar_t a_a2d(a, 0), b_a2d(b, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHF_05*/
    b_a2d.pvalue[0] = bp0;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHF_05*/
    b_a2d.pvalue[1] = bp1;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHF_05*/
    b_a2d.pvalue[2] = bp2;  /*UNQ_T2F_TFHF_05*/
    // Evaluations:
    auto expr = A2D::ScalarMult(a_a2d, b_a2d, z_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHF_09*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(b_a2d.bvalue, bb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(ScalarMult_A2DScalarA2DScalar, hreverse) {
    // Declarations and Initializations:
    T a(a_data), b(b_data), ap0(ap0_data), bp0(bp0_data), ap1(ap1_data), bp1(bp1_data), ap2(ap2_data), bp2(bp2_data), zb(zb_data), zh0(zh0_data), zh1(zh1_data), zh2(zh2_data);  /*UNQ_T2F_TFHR_01*/
    A2DScalar_t a_a2d(a, 0), b_a2d(b, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHR_04*/
    b_a2d.pvalue[0] = bp0;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHR_04*/
    b_a2d.pvalue[1] = bp1;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHR_04*/
    b_a2d.pvalue[2] = bp2;  /*UNQ_T2F_TFHR_04*/
    z_a2d.hvalue[0] = zh0;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[1] = zh1;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[2] = zh2;  /*UNQ_T2F_TFHR_05*/
    // Evaluations:
    auto expr = A2D::ScalarMult(a_a2d, b_a2d, z_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHR_10*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(b_a2d.bvalue, bb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.hvalue[0], ah0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[1], ah1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[2], ah2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(b_a2d.hvalue[0], bh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(b_a2d.hvalue[1], bh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(b_a2d.hvalue[2], bh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class Vec3ScaleDiv : public shell_dev_opsTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class Vec3ScaleDiv_A2DVecA2DScalar : public Vec3ScaleDiv {
protected:
    // Results
    const T V_out[3] = {1.3627361929711554, 0.5446375302899584, 0.22311034398646382};
    const T Xb_out[3] = {0.9829638982037326, 0.9846893779585377, 1.0520729679712673};
    const T ab_out = -2.110547633163264;
    const T Vp0_out[3] = {-0.8178817308268755, 0.9127968769901611, 0.20330600609413538};
    const T Vp1_out[3] = {0.23334312851241362, 0.670279145912219, 0.46895100827092023};
    const T Vp2_out[3] = {-0.08492384244425068, 0.5463597608535664, 0.7903820175396429};
    const T Xh0_out[3] = {-0.1071573123639894, -0.0394087344211862, 0.6568852121844284};
    const T ah0_out = -0.2878331883936516;
    const T Xh1_out[3] = {1.065341424192623, 0.9313845324199985, 1.0411623316421201};
    const T ah1_out = -3.5740956795195946;
    const T Xh2_out[3] = {0.3035875434749068, 0.6680247441853419, 0.03486716140157253};
    const T ah2_out = -2.07137744002485;
};  /*UNQ_T2F_FTV_01*/

TEST_F(Vec3ScaleDiv_A2DVecA2DScalar, passive) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_T2F_TFP_01*/
    Vec_t X(X_data);  /*UNQ_T2F_TFP_01*/
    Vec_t V, Vb, Xb;  /*UNQ_T2F_TFP_02*/
    A2DScalar_t a_a2d(a, 0);  /*UNQ_T2F_TFP_03*/
    A2DVec_t X_a2d(X, Xb), V_a2d(V, Vb);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::Vec3ScaleDiv(X_a2d, a_a2d, V_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_vec_eq<3>(V_a2d.value(), V_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(Vec3ScaleDiv_A2DVecA2DScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data);  /*UNQ_T2F_TFR_01*/
    Vec_t X(X_data), Vb(Vb_data);  /*UNQ_T2F_TFR_01*/
    Vec_t V, Xb;  /*UNQ_T2F_TFR_02*/
    A2DScalar_t a_a2d(a, 0);  /*UNQ_T2F_TFR_03*/
    A2DVec_t X_a2d(X, Xb), V_a2d(V, Vb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::Vec3ScaleDiv(X_a2d, a_a2d, V_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_vec_eq<3>(V_a2d.value(), V_out);  /*UNQ_T2F_TFR_06*/
    expect_vec_eq<3>(X_a2d.bvalue(), Xb_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(Vec3ScaleDiv_A2DVecA2DScalar, hforward) {
    // Declarations and Initializations:
    T a(a_data), ap0(ap0_data), ap1(ap1_data), ap2(ap2_data);  /*UNQ_T2F_TFHF_01*/
    Vec_t X(X_data), Xp0(Xp0_data), Xp1(Xp1_data), Xp2(Xp2_data), Vb(Vb_data);  /*UNQ_T2F_TFHF_01*/
    Vec_t V, Xb;  /*UNQ_T2F_TFHF_02*/
    A2DScalar_t a_a2d(a, 0);  /*UNQ_T2F_TFHF_03*/
    A2DVec_t X_a2d(X, Xb), V_a2d(V, Vb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHF_05*/
    for (int ii_0 = 0; ii_0 < 3; ii_0++) {  /*UNQ_T2F_CDL_02*/
        if (ii_0 < 3) {X_a2d.pvalue(0)(ii_0) = Xp0(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 3) {X_a2d.pvalue(1)(ii_0) = Xp1(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 3) {X_a2d.pvalue(2)(ii_0) = Xp2(ii_0);  /*UNQ_T2F_TFHF_05*/ }
    }
    // Evaluations:
    auto expr = A2D::Vec3ScaleDiv(X_a2d, a_a2d, V_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_vec_eq<3>(V_a2d.value(), V_out);  /*UNQ_T2F_TFHF_09*/
    expect_vec_eq<3>(X_a2d.bvalue(), Xb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHF_10*/
    expect_vec_eq<3>(V_a2d.pvalue(0), Vp0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_vec_eq<3>(V_a2d.pvalue(1), Vp1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_vec_eq<3>(V_a2d.pvalue(2), Vp2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(Vec3ScaleDiv_A2DVecA2DScalar, hreverse) {
    // Declarations and Initializations:
    T a(a_data), ap0(ap0_data), ap1(ap1_data), ap2(ap2_data);  /*UNQ_T2F_TFHR_01*/
    Vec_t X(X_data), Xp0(Xp0_data), Xp1(Xp1_data), Xp2(Xp2_data), Vb(Vb_data), Vh0(Vh0_data), Vh1(Vh1_data), Vh2(Vh2_data);  /*UNQ_T2F_TFHR_01*/
    Vec_t V, Xb;  /*UNQ_T2F_TFHR_02*/
    A2DScalar_t a_a2d(a, 0);  /*UNQ_T2F_TFHR_03*/
    A2DVec_t X_a2d(X, Xb), V_a2d(V, Vb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHR_04*/
    for (int ii_0 = 0; ii_0 < 3; ii_0++) {  /*UNQ_T2F_CDL_02*/
        if (ii_0 < 3) {X_a2d.pvalue(0)(ii_0) = Xp0(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 3) {X_a2d.pvalue(1)(ii_0) = Xp1(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 3) {X_a2d.pvalue(2)(ii_0) = Xp2(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 3) {V_a2d.hvalue(0)(ii_0) = Vh0(ii_0);  /*UNQ_T2F_TFHR_05*/ }
        if (ii_0 < 3) {V_a2d.hvalue(1)(ii_0) = Vh1(ii_0);  /*UNQ_T2F_TFHR_05*/ }
        if (ii_0 < 3) {V_a2d.hvalue(2)(ii_0) = Vh2(ii_0);  /*UNQ_T2F_TFHR_05*/ }
    }
    // Evaluations:
    auto expr = A2D::Vec3ScaleDiv(X_a2d, a_a2d, V_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_vec_eq<3>(V_a2d.value(), V_out);  /*UNQ_T2F_TFHR_10*/
    expect_vec_eq<3>(X_a2d.bvalue(), Xb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHR_11*/
    expect_vec_eq<3>(V_a2d.pvalue(0), Vp0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_vec_eq<3>(V_a2d.pvalue(1), Vp1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_vec_eq<3>(V_a2d.pvalue(2), Vp2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_vec_eq<3>(X_a2d.hvalue(0), Xh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<3>(X_a2d.hvalue(1), Xh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<3>(X_a2d.hvalue(2), Xh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[0], ah0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[1], ah1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[2], ah2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class ScalarAxpay : public shell_dev_opsTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class ScalarAxpay_ScalarA2DScalarA2DScalar : public ScalarAxpay {
protected:
    // Results
    const T z_out = 0.6852016744292855;
    const T xb_out = 0.22904876614081823;
    const T yb_out = 0.22904876614081823;
    const T zp0_out = 0.3775088660847295;
    const T zp1_out = 0.5568511328249376;
    const T zp2_out = 0.38750536247044265;
    const T xh0_out = 0.43964238831758057;
    const T yh0_out = 0.43964238831758057;
    const T xh1_out = 0.1702795510592872;
    const T yh1_out = 0.1702795510592872;
    const T xh2_out = 0.4982045710950908;
    const T yh2_out = 0.4982045710950908;
};  /*UNQ_T2F_FTV_01*/

TEST_F(ScalarAxpay_ScalarA2DScalarA2DScalar, passive) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data);  /*UNQ_T2F_TFP_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::ScalarAxpay(a, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(ScalarAxpay_ScalarA2DScalarA2DScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data), zb(zb_data);  /*UNQ_T2F_TFR_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::ScalarAxpay(a, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFR_06*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(ScalarAxpay_ScalarA2DScalarA2DScalar, hforward) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data), xp0(xp0_data), yp0(yp0_data), xp1(xp1_data), yp1(yp1_data), xp2(xp2_data), yp2(yp2_data), zb(zb_data);  /*UNQ_T2F_TFHF_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHF_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpay(a, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHF_09*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(ScalarAxpay_ScalarA2DScalarA2DScalar, hreverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data), xp0(xp0_data), yp0(yp0_data), xp1(xp1_data), yp1(yp1_data), xp2(xp2_data), yp2(yp2_data), zb(zb_data), zh0(zh0_data), zh1(zh1_data), zh2(zh2_data);  /*UNQ_T2F_TFHR_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHR_04*/
    z_a2d.hvalue[0] = zh0;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[1] = zh1;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[2] = zh2;  /*UNQ_T2F_TFHR_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpay(a, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHR_10*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(x_a2d.hvalue[0], xh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[1], xh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[2], xh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[0], yh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[1], yh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[2], yh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class ScalarAxpay_A2DScalarA2DScalarA2DScalar : public ScalarAxpay {
protected:
    // Results
    const T z_out = 0.6852016744292855;
    const T ab_out = 0.4135753122788231;
    const T xb_out = 0.22904876614081823;
    const T yb_out = 0.22904876614081823;
    const T zp0_out = 0.9839909456518089;
    const T zp1_out = 0.7482112058155677;
    const T zp2_out = 1.0440233538411838;
    const T ah0_out = 1.0216851347215796;
    const T xh0_out = 0.6423768199396165;
    const T yh0_out = 0.6423768199396165;
    const T ah1_out = 0.6435656220717829;
    const T xh1_out = 0.23424727070007134;
    const T yh1_out = 0.23424727070007134;
    const T ah2_out = 1.1334599586072616;
    const T xh2_out = 0.7176649744844157;
    const T yh2_out = 0.7176649744844157;
};  /*UNQ_T2F_FTV_01*/

TEST_F(ScalarAxpay_A2DScalarA2DScalarA2DScalar, passive) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data);  /*UNQ_T2F_TFP_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::ScalarAxpay(a_a2d, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(ScalarAxpay_A2DScalarA2DScalarA2DScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data), zb(zb_data);  /*UNQ_T2F_TFR_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::ScalarAxpay(a_a2d, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFR_06*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(ScalarAxpay_A2DScalarA2DScalarA2DScalar, hforward) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data), ap0(ap0_data), xp0(xp0_data), yp0(yp0_data), ap1(ap1_data), xp1(xp1_data), yp1(yp1_data), ap2(ap2_data), xp2(xp2_data), yp2(yp2_data), zb(zb_data);  /*UNQ_T2F_TFHF_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHF_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpay(a_a2d, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHF_09*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(ScalarAxpay_A2DScalarA2DScalarA2DScalar, hreverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), y(y_data), ap0(ap0_data), xp0(xp0_data), yp0(yp0_data), ap1(ap1_data), xp1(xp1_data), yp1(yp1_data), ap2(ap2_data), xp2(xp2_data), yp2(yp2_data), zb(zb_data), zh0(zh0_data), zh1(zh1_data), zh2(zh2_data);  /*UNQ_T2F_TFHR_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHR_04*/
    z_a2d.hvalue[0] = zh0;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[1] = zh1;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[2] = zh2;  /*UNQ_T2F_TFHR_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpay(a_a2d, x_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHR_10*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.hvalue[0], ah0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[1], ah1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[2], ah2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[0], xh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[1], xh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[2], xh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[0], yh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[1], yh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[2], yh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class ScalarAxpby : public shell_dev_opsTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class ScalarAxpby_ScalarA2DScalarScalarA2DScalar : public ScalarAxpby {
protected:
    // Results
    const T z_out = 0.3800014357146878;
    const T xb_out = 0.22904876614081823;
    const T yb_out = 0.10903352563254688;
    const T zp0_out = 0.322330067901751;
    const T zp1_out = 0.35464157785490336;
    const T zp2_out = 0.32100527297322806;
    const T xh0_out = 0.43964238831758057;
    const T yh0_out = 0.20928189408498424;
    const T xh1_out = 0.1702795510592872;
    const T yh1_out = 0.08105775948038485;
    const T xh2_out = 0.4982045710950908;
    const T yh2_out = 0.23715910715429167;
};  /*UNQ_T2F_FTV_01*/

TEST_F(ScalarAxpby_ScalarA2DScalarScalarA2DScalar, passive) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data);  /*UNQ_T2F_TFP_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::ScalarAxpby(a, x_a2d, b, y_a2d, z_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(ScalarAxpby_ScalarA2DScalarScalarA2DScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data), zb(zb_data);  /*UNQ_T2F_TFR_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::ScalarAxpby(a, x_a2d, b, y_a2d, z_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFR_06*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(ScalarAxpby_ScalarA2DScalarScalarA2DScalar, hforward) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data), xp0(xp0_data), yp0(yp0_data), xp1(xp1_data), yp1(yp1_data), xp2(xp2_data), yp2(yp2_data), zb(zb_data);  /*UNQ_T2F_TFHF_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHF_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpby(a, x_a2d, b, y_a2d, z_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHF_09*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(ScalarAxpby_ScalarA2DScalarScalarA2DScalar, hreverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data), xp0(xp0_data), yp0(yp0_data), xp1(xp1_data), yp1(yp1_data), xp2(xp2_data), yp2(yp2_data), zb(zb_data), zh0(zh0_data), zh1(zh1_data), zh2(zh2_data);  /*UNQ_T2F_TFHR_01*/
    A2DScalar_t x_a2d(x, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHR_04*/
    z_a2d.hvalue[0] = zh0;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[1] = zh1;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[2] = zh2;  /*UNQ_T2F_TFHR_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpby(a, x_a2d, b, y_a2d, z_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHR_10*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(x_a2d.hvalue[0], xh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[1], xh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[2], xh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[0], yh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[1], yh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[2], yh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class ScalarAxpby_A2DScalarA2DScalarA2DScalarA2DScalar : public ScalarAxpby {
protected:
    // Results
    const T z_out = 0.3800014357146878;
    const T ab_out = 0.06200465851697334;
    const T xb_out = 0.22904876614081823;
    const T bb_out = 0.35157065376184976;
    const T yb_out = 0.10903352563254688;
    const T zp0_out = 0.8781947340707911;
    const T zp1_out = 1.1917113443293161;
    const T zp2_out = 1.2359882735655352;
    const T ah0_out = 0.2833085702398471;
    const T xh0_out = 0.6423768199390445;
    const T bh0_out = 0.7383765644820912;
    const T yh0_out = 0.39211181623186164;
    const T ah1_out = 0.14926864424251804;
    const T xh1_out = 0.23424727069989087;
    const T bh1_out = 0.49429697783057913;
    const T yh1_out = 0.3989407594234656;
    const T ah2_out = 0.2921539681992029;
    const T xh2_out = 0.7176649744837965;
    const T bh2_out = 0.8413059904084907;
    const T yh2_out = 0.5582568499334055;
};  /*UNQ_T2F_FTV_01*/

TEST_F(ScalarAxpby_A2DScalarA2DScalarA2DScalarA2DScalar, passive) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data);  /*UNQ_T2F_TFP_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), b_a2d(b, 0), y_a2d(y, 0), z_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::ScalarAxpby(a_a2d, x_a2d, b_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(ScalarAxpby_A2DScalarA2DScalarA2DScalarA2DScalar, reverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data), zb(zb_data);  /*UNQ_T2F_TFR_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), b_a2d(b, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::ScalarAxpby(a_a2d, x_a2d, b_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFR_06*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(b_a2d.bvalue, bb_out);  /*UNQ_T2F_TFR_07*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(ScalarAxpby_A2DScalarA2DScalarA2DScalarA2DScalar, hforward) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data), ap0(ap0_data), xp0(xp0_data), bp0(bp0_data), yp0(yp0_data), ap1(ap1_data), xp1(xp1_data), bp1(bp1_data), yp1(yp1_data), ap2(ap2_data), xp2(xp2_data), bp2(bp2_data), yp2(yp2_data), zb(zb_data);  /*UNQ_T2F_TFHF_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), b_a2d(b, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHF_05*/
    b_a2d.pvalue[0] = bp0;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHF_05*/
    b_a2d.pvalue[1] = bp1;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHF_05*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHF_05*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHF_05*/
    b_a2d.pvalue[2] = bp2;  /*UNQ_T2F_TFHF_05*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHF_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpby(a_a2d, x_a2d, b_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHF_09*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(b_a2d.bvalue, bb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(ScalarAxpby_A2DScalarA2DScalarA2DScalarA2DScalar, hreverse) {
    // Declarations and Initializations:
    T a(a_data), x(x_data), b(b_data), y(y_data), ap0(ap0_data), xp0(xp0_data), bp0(bp0_data), yp0(yp0_data), ap1(ap1_data), xp1(xp1_data), bp1(bp1_data), yp1(yp1_data), ap2(ap2_data), xp2(xp2_data), bp2(bp2_data), yp2(yp2_data), zb(zb_data), zh0(zh0_data), zh1(zh1_data), zh2(zh2_data);  /*UNQ_T2F_TFHR_01*/
    A2DScalar_t a_a2d(a, 0), x_a2d(x, 0), b_a2d(b, 0), y_a2d(y, 0), z_a2d(0, zb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.pvalue[0] = ap0;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[0] = xp0;  /*UNQ_T2F_TFHR_04*/
    b_a2d.pvalue[0] = bp0;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[0] = yp0;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[1] = ap1;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[1] = xp1;  /*UNQ_T2F_TFHR_04*/
    b_a2d.pvalue[1] = bp1;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[1] = yp1;  /*UNQ_T2F_TFHR_04*/
    a_a2d.pvalue[2] = ap2;  /*UNQ_T2F_TFHR_04*/
    x_a2d.pvalue[2] = xp2;  /*UNQ_T2F_TFHR_04*/
    b_a2d.pvalue[2] = bp2;  /*UNQ_T2F_TFHR_04*/
    y_a2d.pvalue[2] = yp2;  /*UNQ_T2F_TFHR_04*/
    z_a2d.hvalue[0] = zh0;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[1] = zh1;  /*UNQ_T2F_TFHR_05*/
    z_a2d.hvalue[2] = zh2;  /*UNQ_T2F_TFHR_05*/
    // Evaluations:
    auto expr = A2D::ScalarAxpby(a_a2d, x_a2d, b_a2d, y_a2d, z_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(z_a2d.value, z_out);  /*UNQ_T2F_TFHR_10*/
    expect_val_eq(a_a2d.bvalue, ab_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(x_a2d.bvalue, xb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(b_a2d.bvalue, bb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(y_a2d.bvalue, yb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(z_a2d.pvalue[0], zp0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[1], zp1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(z_a2d.pvalue[2], zp2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.hvalue[0], ah0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[1], ah1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(a_a2d.hvalue[2], ah2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[0], xh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[1], xh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(x_a2d.hvalue[2], xh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(b_a2d.hvalue[0], bh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(b_a2d.hvalue[1], bh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(b_a2d.hvalue[2], bh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[0], yh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[1], yh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_val_eq(y_a2d.hvalue[2], yh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class MatInnerProduct : public shell_dev_opsTest {
protected:
    
};  /*UNQ_TC_TF_01*/

class MatInnerProduct_Mat4x7A2DVec4A2DVec7 : public MatInnerProduct {
protected:
    // Results
    const T a_out = 1.7836652069921193;
    const T Xinnerb_out[4] = {0.35605622275084753, 0.3690550741476613, 0.5010157018533992, 0.38272365327961694};
    const T Yinnerb_out[7] = {0.21101663989932234, 0.18098351452049793, 0.20843316804231352, 0.12306843673367272, 0.19355802690282548, 0.09860256875231996, 0.0653891560996992};
    const T ap0_out = 4.627719361156574;
    const T ap1_out = 6.070902579196523;
    const T ap2_out = 5.8772783097291965;
    const T Xinnerh0_out[4] = {1.417804312494445, 1.600296569961992, 1.9714746682246134, 1.584527154449404};
    const T Yinnerh0_out[7] = {0.864700301635036, 0.7118525056981252, 0.8963729682570342, 0.49581336906050577, 0.8765417170945697, 0.3712904923612318, 0.2633467198017162};
    const T Xinnerh1_out[4] = {1.2705940639326188, 1.25918238495777, 1.7061622710846769, 1.2088028282499912};
    const T Yinnerh1_out[7] = {0.811604948176887, 0.7173042814020694, 0.8805399871774174, 0.5428986784832553, 0.8753631345271734, 0.3957166899571921, 0.3125362013179296};
    const T Xinnerh2_out[4] = {0.6137131465160317, 0.6470372093975636, 0.8509169346049632, 0.633550177687384};
    const T Yinnerh2_out[7] = {0.5244442623858245, 0.5515858942576108, 0.6014943471899113, 0.3811283203837467, 0.6382687360887974, 0.2427815987969455, 0.16444183273651175};
};  /*UNQ_T2F_FTV_01*/

TEST_F(MatInnerProduct_Mat4x7A2DVec4A2DVec7, passive) {
    // Declarations and Initializations:
    Vec4_t Xinner(Xinner_data);  /*UNQ_T2F_TFP_01*/
    Mat4x7_t A(A_data);  /*UNQ_T2F_TFP_01*/
    Vec7_t Yinner(Yinner_data);  /*UNQ_T2F_TFP_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFP_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFP_02*/
    A2DScalar_t a_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFP_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::MatInnerProduct(A, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(MatInnerProduct_Mat4x7A2DVec4A2DVec7, reverse) {
    // Declarations and Initializations:
    T ab(ab_data);  /*UNQ_T2F_TFR_01*/
    Vec4_t Xinner(Xinner_data);  /*UNQ_T2F_TFR_01*/
    Mat4x7_t A(A_data);  /*UNQ_T2F_TFR_01*/
    Vec7_t Yinner(Yinner_data);  /*UNQ_T2F_TFR_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFR_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFR_02*/
    A2DScalar_t a_a2d(0, ab);  /*UNQ_T2F_TFR_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFR_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::MatInnerProduct(A, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFR_06*/
    expect_vec_eq<4>(Xinner_a2d.bvalue(), Xinnerb_out);  /*UNQ_T2F_TFR_07*/
    expect_vec_eq<7>(Yinner_a2d.bvalue(), Yinnerb_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(MatInnerProduct_Mat4x7A2DVec4A2DVec7, hforward) {
    // Declarations and Initializations:
    T ab(ab_data);  /*UNQ_T2F_TFHF_01*/
    Vec4_t Xinner(Xinner_data), Xinnerp0(Xinnerp0_data), Xinnerp1(Xinnerp1_data), Xinnerp2(Xinnerp2_data);  /*UNQ_T2F_TFHF_01*/
    Mat4x7_t A(A_data);  /*UNQ_T2F_TFHF_01*/
    Vec7_t Yinner(Yinner_data), Yinnerp0(Yinnerp0_data), Yinnerp1(Yinnerp1_data), Yinnerp2(Yinnerp2_data);  /*UNQ_T2F_TFHF_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFHF_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFHF_02*/
    A2DScalar_t a_a2d(0, ab);  /*UNQ_T2F_TFHF_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFHF_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    for (int ii_0 = 0; ii_0 < 7; ii_0++) {  /*UNQ_T2F_CDL_02*/
        if (ii_0 < 4) {Xinner_a2d.pvalue(0)(ii_0) = Xinnerp0(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(0)(ii_0) = Yinnerp0(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(1)(ii_0) = Xinnerp1(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(1)(ii_0) = Yinnerp1(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(2)(ii_0) = Xinnerp2(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(2)(ii_0) = Yinnerp2(ii_0);  /*UNQ_T2F_TFHF_05*/ }
    }
    // Evaluations:
    auto expr = A2D::MatInnerProduct(A, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFHF_09*/
    expect_vec_eq<4>(Xinner_a2d.bvalue(), Xinnerb_out);  /*UNQ_T2F_TFHF_10*/
    expect_vec_eq<7>(Yinner_a2d.bvalue(), Yinnerb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(a_a2d.pvalue[0], ap0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(a_a2d.pvalue[1], ap1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(a_a2d.pvalue[2], ap2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(MatInnerProduct_Mat4x7A2DVec4A2DVec7, hreverse) {
    // Declarations and Initializations:
    T ab(ab_data), ah0(ah0_data), ah1(ah1_data), ah2(ah2_data);  /*UNQ_T2F_TFHR_01*/
    Vec4_t Xinner(Xinner_data), Xinnerp0(Xinnerp0_data), Xinnerp1(Xinnerp1_data), Xinnerp2(Xinnerp2_data);  /*UNQ_T2F_TFHR_01*/
    Mat4x7_t A(A_data);  /*UNQ_T2F_TFHR_01*/
    Vec7_t Yinner(Yinner_data), Yinnerp0(Yinnerp0_data), Yinnerp1(Yinnerp1_data), Yinnerp2(Yinnerp2_data);  /*UNQ_T2F_TFHR_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFHR_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFHR_02*/
    A2DScalar_t a_a2d(0, ab);  /*UNQ_T2F_TFHR_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFHR_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.hvalue[0] = ah0;  /*UNQ_T2F_TFHR_05*/
    a_a2d.hvalue[1] = ah1;  /*UNQ_T2F_TFHR_05*/
    a_a2d.hvalue[2] = ah2;  /*UNQ_T2F_TFHR_05*/
    for (int ii_0 = 0; ii_0 < 7; ii_0++) {  /*UNQ_T2F_CDL_02*/
        if (ii_0 < 4) {Xinner_a2d.pvalue(0)(ii_0) = Xinnerp0(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(0)(ii_0) = Yinnerp0(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(1)(ii_0) = Xinnerp1(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(1)(ii_0) = Yinnerp1(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(2)(ii_0) = Xinnerp2(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(2)(ii_0) = Yinnerp2(ii_0);  /*UNQ_T2F_TFHR_04*/ }
    }
    // Evaluations:
    auto expr = A2D::MatInnerProduct(A, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFHR_10*/
    expect_vec_eq<4>(Xinner_a2d.bvalue(), Xinnerb_out);  /*UNQ_T2F_TFHR_11*/
    expect_vec_eq<7>(Yinner_a2d.bvalue(), Yinnerb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(a_a2d.pvalue[0], ap0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.pvalue[1], ap1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.pvalue[2], ap2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_vec_eq<4>(Xinner_a2d.hvalue(0), Xinnerh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<4>(Xinner_a2d.hvalue(1), Xinnerh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<4>(Xinner_a2d.hvalue(2), Xinnerh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<7>(Yinner_a2d.hvalue(0), Yinnerh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<7>(Yinner_a2d.hvalue(1), Yinnerh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<7>(Yinner_a2d.hvalue(2), Yinnerh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}

class MatInnerProduct_A2DMat4x7A2DVec4A2DVec7 : public MatInnerProduct {
protected:
    // Results
    const T a_out = 1.7836652069921193;
    const T Ab_out[28] = {0.03155175919523545, 0.03836421376029753, 0.04408801261271132, 0.07551824943786038, 0.01684380382277902, 0.030771448025002514, 0.003399119567152957,
0.02281860265408889, 0.02774544977083095, 0.031884968295835515, 0.05461568454525753, 0.01218163666365259, 0.022254272455258604, 0.002458283175168076, 
0.0467998255481185, 0.056904545327024936, 0.0653944931016624, 0.11201406798023675, 0.024983934353550293, 0.045642412219302764, 0.005041817217721933, 
0.01648208350793163, 0.020040789833641, 0.023030801581776218, 0.0394494039430798, 0.008798906567472302, 0.01607446269064632, 0.0017756402174785733};
    const T Xinnerb_out[4] = {0.35605622275084753, 0.3690550741476613, 0.5010157018533992, 0.38272365327961694};
    const T Yinnerb_out[7] = {0.21101663989932234, 0.18098351452049793, 0.20843316804231352, 0.12306843673367272, 0.19355802690282548, 0.09860256875231996, 0.0653891560996992};
    const T ap0_out = 6.650973873169454;
    const T ap1_out = 7.881343079272969;
    const T ap2_out = 7.772980383060554;
    const T Ah0_out[28] = {0.09863417064491799, 0.130169404598579, 0.17210179401412917, 0.2776228719011099, 0.1275713720469222, 0.15453085910055214, 0.09079753265548887,
0.15136867660412967, 0.19145603648742435, 0.23630121942894416, 0.39234233034282756, 0.13498769075213513, 0.18981445352556617, 0.07428816610572049, 
0.20786943895616727, 0.26793816251464725, 0.34130435403951875, 0.5591518149498973, 0.22209095598639583, 0.2892567527693002, 0.1413102286439885, 
0.05126783176384088, 0.06768580972148977, 0.0895439434434572, 0.1444103638438309, 0.06650388154450873, 0.08047363168988994, 0.04740335384130556};
    const T Xinnerh0_out[4] = {1.7040070111986618, 2.0477684546403125, 2.5691656069617057, 2.1205901986413167};
    const T Yinnerh0_out[7] = {1.0658502542295238, 0.8141846973755271, 1.0624339685517323, 0.7117265248791167, 1.1416550736920383, 0.5283789709314664, 0.43625102455258963};
    const T Ah1_out[28] = {0.2135105320593122, 0.23524661126375906, 0.2739359552403908, 0.40386173545840026, 0.08072306935392827, 0.15488769688233886, 0.047751799975125735,
0.19141667137768265, 0.21512598588340695, 0.24981934423490368, 0.3806440225347522, 0.07813398818758603, 0.1481048135588868, 0.03852108995593263, 
0.21415063327733286, 0.22425061140232605, 0.26303502350794883, 0.35360172421320646, 0.06499173911161622, 0.12973306915347477, 0.05978172018788894, 
0.15511342876078082, 0.17587733524128246, 0.2039936776348996, 0.31527605692701505, 0.06543296996043027, 0.12341212607745944, 0.029639563115629944};
    const T Xinnerh1_out[4] = {1.8861378946487262, 1.8321786260767756, 2.0145008218792437, 1.4045381452547794};
    const T Yinnerh1_out[7] = {0.9250381806927304, 0.8939421415336297, 1.1017240270367696, 0.6768249404223026, 0.987253425926865, 0.6076685995338558, 0.4752008683138861};
    const T Ah2_out[28] = {0.07942515662115937, 0.13185321530530136, 0.12076763282372137, 0.13151957965947042, 0.05277852935408378, 0.0648111200647661, 0.06428746195737003,
0.09658575279367389, 0.14295418120875847, 0.14203816293356497, 0.1888078780389984, 0.05906724093115574, 0.08504862047525677, 0.050710549488856095, 
0.17522274883614405, 0.2653841894888932, 0.25935666538082225, 0.3324972683726779, 0.10893499322043095, 0.15212625870724866, 0.10154102459664824, 
0.09469322180105898, 0.1335679513382831, 0.13742856988413218, 0.1960432036025574, 0.05597277909025877, 0.08574333724336704, 0.03931427054607589};
    const T Xinnerh2_out[4] = {1.0313851574750872, 1.2161484766150383, 1.2875338175395383, 0.9925151149309567};
    const T Yinnerh2_out[7] = {0.6166257185024224, 0.712981741652454, 0.7588847785013754, 0.6179165516465525, 0.7737553507807488, 0.38690785048364323, 0.2784726591397299};
};  /*UNQ_T2F_FTV_01*/

TEST_F(MatInnerProduct_A2DMat4x7A2DVec4A2DVec7, passive) {
    // Declarations and Initializations:
    Vec4_t Xinner(Xinner_data);  /*UNQ_T2F_TFP_01*/
    Mat4x7_t A(A_data);  /*UNQ_T2F_TFP_01*/
    Vec7_t Yinner(Yinner_data);  /*UNQ_T2F_TFP_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFP_02*/
    Mat4x7_t Ab;  /*UNQ_T2F_TFP_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFP_02*/
    A2DScalar_t a_a2d(0, 0);  /*UNQ_T2F_TFP_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFP_03*/
    A2DMat4x7_t A_a2d(A, Ab);  /*UNQ_T2F_TFP_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFP_03*/
    // Set Derivative Values:
        /*None for "passive" tests*/
    // Evaluations:
    A2D::MatInnerProduct(A_a2d, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFP_04*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFP_05*/
}

TEST_F(MatInnerProduct_A2DMat4x7A2DVec4A2DVec7, reverse) {
    // Declarations and Initializations:
    T ab(ab_data);  /*UNQ_T2F_TFR_01*/
    Vec4_t Xinner(Xinner_data);  /*UNQ_T2F_TFR_01*/
    Mat4x7_t A(A_data);  /*UNQ_T2F_TFR_01*/
    Vec7_t Yinner(Yinner_data);  /*UNQ_T2F_TFR_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFR_02*/
    Mat4x7_t Ab;  /*UNQ_T2F_TFR_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFR_02*/
    A2DScalar_t a_a2d(0, ab);  /*UNQ_T2F_TFR_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFR_03*/
    A2DMat4x7_t A_a2d(A, Ab);  /*UNQ_T2F_TFR_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFR_03*/
    // Set Derivative Values:
        /*None for "reverse" tests*/
    // Evaluations:
    auto expr = A2D::MatInnerProduct(A_a2d, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFR_04*/
    expr.reverse();  /*UNQ_T2F_TFR_05*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFR_06*/
    expect_mat_eq<4, 7>(A_a2d.bvalue(), Ab_out);  /*UNQ_T2F_TFR_07*/
    expect_vec_eq<4>(Xinner_a2d.bvalue(), Xinnerb_out);  /*UNQ_T2F_TFR_07*/
    expect_vec_eq<7>(Yinner_a2d.bvalue(), Yinnerb_out);  /*UNQ_T2F_TFR_07*/
}

TEST_F(MatInnerProduct_A2DMat4x7A2DVec4A2DVec7, hforward) {
    // Declarations and Initializations:
    T ab(ab_data);  /*UNQ_T2F_TFHF_01*/
    Vec4_t Xinner(Xinner_data), Xinnerp0(Xinnerp0_data), Xinnerp1(Xinnerp1_data), Xinnerp2(Xinnerp2_data);  /*UNQ_T2F_TFHF_01*/
    Mat4x7_t A(A_data), Ap0(Ap0_data), Ap1(Ap1_data), Ap2(Ap2_data);  /*UNQ_T2F_TFHF_01*/
    Vec7_t Yinner(Yinner_data), Yinnerp0(Yinnerp0_data), Yinnerp1(Yinnerp1_data), Yinnerp2(Yinnerp2_data);  /*UNQ_T2F_TFHF_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFHF_02*/
    Mat4x7_t Ab;  /*UNQ_T2F_TFHF_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFHF_02*/
    A2DScalar_t a_a2d(0, ab);  /*UNQ_T2F_TFHF_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFHF_03*/
    A2DMat4x7_t A_a2d(A, Ab);  /*UNQ_T2F_TFHF_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFHF_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    for (int ii_0 = 0; ii_0 < 7; ii_0++) {  /*UNQ_T2F_CDL_02*/
        if (ii_0 < 4) {Xinner_a2d.pvalue(0)(ii_0) = Xinnerp0(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(0)(ii_0) = Yinnerp0(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(1)(ii_0) = Xinnerp1(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(1)(ii_0) = Yinnerp1(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(2)(ii_0) = Xinnerp2(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(2)(ii_0) = Yinnerp2(ii_0);  /*UNQ_T2F_TFHF_05*/ }
        for (int ii_1 = 0; ii_1 < 7; ii_1++) {  /*UNQ_T2F_CDL_02*/
            if (ii_1 < 7) {A_a2d.pvalue(0)(ii_0, ii_1) = Ap0(ii_0, ii_1);  /*UNQ_T2F_TFHF_05*/ }
            if (ii_1 < 7) {A_a2d.pvalue(1)(ii_0, ii_1) = Ap1(ii_0, ii_1);  /*UNQ_T2F_TFHF_05*/ }
            if (ii_1 < 7) {A_a2d.pvalue(2)(ii_0, ii_1) = Ap2(ii_0, ii_1);  /*UNQ_T2F_TFHF_05*/ }
        }
    }
    // Evaluations:
    auto expr = A2D::MatInnerProduct(A_a2d, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFHF_06*/
    expr.reverse();  /*UNQ_T2F_TFHF_07*/
    expr.hforward();  /*UNQ_T2F_TFHF_08*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFHF_09*/
    expect_mat_eq<4, 7>(A_a2d.bvalue(), Ab_out);  /*UNQ_T2F_TFHF_10*/
    expect_vec_eq<4>(Xinner_a2d.bvalue(), Xinnerb_out);  /*UNQ_T2F_TFHF_10*/
    expect_vec_eq<7>(Yinner_a2d.bvalue(), Yinnerb_out);  /*UNQ_T2F_TFHF_10*/
    expect_val_eq(a_a2d.pvalue[0], ap0_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(a_a2d.pvalue[1], ap1_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
    expect_val_eq(a_a2d.pvalue[2], ap2_out, 1e-13);  /*UNQ_T2F_TFHF_11*/
}

TEST_F(MatInnerProduct_A2DMat4x7A2DVec4A2DVec7, hreverse) {
    // Declarations and Initializations:
    T ab(ab_data), ah0(ah0_data), ah1(ah1_data), ah2(ah2_data);  /*UNQ_T2F_TFHR_01*/
    Vec4_t Xinner(Xinner_data), Xinnerp0(Xinnerp0_data), Xinnerp1(Xinnerp1_data), Xinnerp2(Xinnerp2_data);  /*UNQ_T2F_TFHR_01*/
    Mat4x7_t A(A_data), Ap0(Ap0_data), Ap1(Ap1_data), Ap2(Ap2_data);  /*UNQ_T2F_TFHR_01*/
    Vec7_t Yinner(Yinner_data), Yinnerp0(Yinnerp0_data), Yinnerp1(Yinnerp1_data), Yinnerp2(Yinnerp2_data);  /*UNQ_T2F_TFHR_01*/
    Vec4_t Xinnerb;  /*UNQ_T2F_TFHR_02*/
    Mat4x7_t Ab;  /*UNQ_T2F_TFHR_02*/
    Vec7_t Yinnerb;  /*UNQ_T2F_TFHR_02*/
    A2DScalar_t a_a2d(0, ab);  /*UNQ_T2F_TFHR_03*/
    A2DVec4_t Xinner_a2d(Xinner, Xinnerb);  /*UNQ_T2F_TFHR_03*/
    A2DMat4x7_t A_a2d(A, Ab);  /*UNQ_T2F_TFHR_03*/
    A2DVec7_t Yinner_a2d(Yinner, Yinnerb);  /*UNQ_T2F_TFHR_03*/
    // Set Derivative Values:
    /*UNQ_T2F_CDL_01*/
    a_a2d.hvalue[0] = ah0;  /*UNQ_T2F_TFHR_05*/
    a_a2d.hvalue[1] = ah1;  /*UNQ_T2F_TFHR_05*/
    a_a2d.hvalue[2] = ah2;  /*UNQ_T2F_TFHR_05*/
    for (int ii_0 = 0; ii_0 < 7; ii_0++) {  /*UNQ_T2F_CDL_02*/
        if (ii_0 < 4) {Xinner_a2d.pvalue(0)(ii_0) = Xinnerp0(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(0)(ii_0) = Yinnerp0(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(1)(ii_0) = Xinnerp1(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(1)(ii_0) = Yinnerp1(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 4) {Xinner_a2d.pvalue(2)(ii_0) = Xinnerp2(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        if (ii_0 < 7) {Yinner_a2d.pvalue(2)(ii_0) = Yinnerp2(ii_0);  /*UNQ_T2F_TFHR_04*/ }
        for (int ii_1 = 0; ii_1 < 7; ii_1++) {  /*UNQ_T2F_CDL_02*/
            if (ii_1 < 7) {A_a2d.pvalue(0)(ii_0, ii_1) = Ap0(ii_0, ii_1);  /*UNQ_T2F_TFHR_04*/ }
            if (ii_1 < 7) {A_a2d.pvalue(1)(ii_0, ii_1) = Ap1(ii_0, ii_1);  /*UNQ_T2F_TFHR_04*/ }
            if (ii_1 < 7) {A_a2d.pvalue(2)(ii_0, ii_1) = Ap2(ii_0, ii_1);  /*UNQ_T2F_TFHR_04*/ }
        }
    }
    // Evaluations:
    auto expr = A2D::MatInnerProduct(A_a2d, Xinner_a2d, Yinner_a2d, a_a2d);  /*UNQ_T2F_TFHR_06*/
    expr.reverse();  /*UNQ_T2F_TFHR_07*/
    expr.hforward();  /*UNQ_T2F_TFHR_08*/
    expr.hreverse();  /*UNQ_T2F_TFHR_09*/
    // Comparisons:
    expect_val_eq(a_a2d.value, a_out);  /*UNQ_T2F_TFHR_10*/
    expect_mat_eq<4, 7>(A_a2d.bvalue(), Ab_out);  /*UNQ_T2F_TFHR_11*/
    expect_vec_eq<4>(Xinner_a2d.bvalue(), Xinnerb_out);  /*UNQ_T2F_TFHR_11*/
    expect_vec_eq<7>(Yinner_a2d.bvalue(), Yinnerb_out);  /*UNQ_T2F_TFHR_11*/
    expect_val_eq(a_a2d.pvalue[0], ap0_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.pvalue[1], ap1_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_val_eq(a_a2d.pvalue[2], ap2_out, 1e-13);  /*UNQ_T2F_TFHR_12*/
    expect_mat_eq<4, 7>(A_a2d.hvalue(0), Ah0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_mat_eq<4, 7>(A_a2d.hvalue(1), Ah1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_mat_eq<4, 7>(A_a2d.hvalue(2), Ah2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<4>(Xinner_a2d.hvalue(0), Xinnerh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<4>(Xinner_a2d.hvalue(1), Xinnerh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<4>(Xinner_a2d.hvalue(2), Xinnerh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<7>(Yinner_a2d.hvalue(0), Yinnerh0_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<7>(Yinner_a2d.hvalue(1), Yinnerh1_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
    expect_vec_eq<7>(Yinner_a2d.hvalue(2), Yinnerh2_out, 1e-8);  /*UNQ_T2F_TFHR_13*/
}
