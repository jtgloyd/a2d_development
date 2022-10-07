//
// Created by James on 10/6/2022.
//

#include "a2d.h"
#include <stdlib.h>
#include <complex>

using namespace A2D;

///*
//  Use the cplx type for TacsComplex
//*/
//typedef std::complex<double> TacsComplex;
//typedef double TacsReal;
//
///*
//  Define the basic scalar type TacsScalar
//*/
//typedef TacsComplex TacsScalar;

TacsScalar test_shell_scalar( const TacsScalar n0_data[],
                              const TacsScalar n0xi_data[],
                              const TacsScalar X0xi_data[],
                              const TacsScalar u0xi_data[],
                              const TacsScalar d0_data[],
                              const TacsScalar d0xi_data[] ){
    Vec3<TacsScalar> n0(n0_data); // Interpolated normal at this point
    Mat3x2<TacsScalar> n0xi(n0xi_data); // Derivative of the normal along the xi and eta directions
    Mat3x2<TacsScalar> X0xi(X0xi_data); // Derivative of the mid-surface coordinate

    // Displacements and directors
    Mat3x2<TacsScalar> u0xi(u0xi_data);
    Vec3<TacsScalar> d0(d0_data);
    Mat3x2<TacsScalar> d0xi(d0xi_data);

    // Get the in-plane tangent directions
    Vec3<TacsScalar> t1_dir, t2_dir;
    Mat3x2ToVec3<TacsScalar> X0tovecs(X0xi, t1_dir, t2_dir);

    // Compute the normal direction
    Vec3<TacsScalar> n1_dir, n1;
//    Vec3CrossProduct<TacsScalar> cross_normal(t1_dir, t2_dir, n1_dir);
//    Vec3Normalize<TacsScalar> normalize_normal(n1_dir, n1);

    // Normalize the t1 direction
    Vec3<TacsScalar> t1;
//    Vec3Normalize<TacsScalar> normalize_t1(t1_dir, t1);

    // Find the t2 direction
    Vec3<TacsScalar> t2;
//    Vec3CrossProduct<TacsScalar> cross_t2(t1, n1, t2);

    // Form the transformation matrix
    Mat3x3<TacsScalar> T;
//    Mat3x3FromThreeVec3<TacsScalar> assembleT(t1, t2, n1, T);

    // Assemble the matrix Xd = [X0,xi | n0]
    Mat3x3<TacsScalar> Xd, Xdz;
//    Mat3x3FromMat3x2AndVec3<TacsScalar> assembleXd(X0xi, n0, Xd);
//    Mat3x3FromMat3x2<TacsScalar> assembleXdz(n0xi, Xdz);

    // Assemble the zero-th and first order terms
    Mat3x3<TacsScalar> u0d, u1d;
//    Mat3x3FromMat3x2AndVec3<TacsScalar> assembleU0xi(u0xi, d0, u0d);
//    Mat3x3FromMat3x2<TacsScalar> assembleU1xi(d0xi, u1d);

    // Compute the inverse matrix
    Mat3x3<TacsScalar> Xdinv;
    Scalar<TacsScalar> detXd;
//    Mat3x3Det<TacsScalar> computedetXd(Xd, detXd);
//    Mat3x3Inverse<TacsScalar> invXd(Xd, Xdinv);

    // Compute XdinvT = Xdinv * T
    Mat3x3<TacsScalar> XdinvT;
//    Mat3x3MatMult<TacsScalar> multXinvT(Xdinv, T, XdinvT);

    // Compute XdinvzT = - Xdinv * Xdz * Xdinv * T
    Mat3x3<TacsScalar> XdinvzT, XdzXdinvT;
//    Mat3x3MatMult<TacsScalar> multXdzXdinvT(Xdz, XdinvT, XdzXdinvT);
//    Mat3x3MatMult<TacsScalar> multXdinvzT(-1.0, Xdinv, XdzXdinvT, XdinvzT);

    // Compute u1x = T^{T} * (u1d * XdinvT + u0d * XdinvzT)
    Mat3x3<TacsScalar> u1dXdinvT, u1x;
//    Mat3x3MatMult<TacsScalar> multu1d(u1d, XdinvT, u1dXdinvT);
//    Mat3x3MatMultAdd<TacsScalar> multu1dadd(u0d, XdinvzT, u1dXdinvT);
//    MatTrans3x3MatMult<TacsScalar> multu1x(T, u1dXdinvT, u1x);

    // Compute u0x = T^{T} * u0d * XdinvT
    Mat3x3<TacsScalar> u0dXdinvT, u0x;
//    Mat3x3MatMult<TacsScalar> multu0d(u0d, XdinvT, u0dXdinvT);
//    MatTrans3x3MatMult<TacsScalar> multu0x(T, u0dXdinvT, u0x);

    // Compute the Green strain
    Symm3x3<TacsScalar> e0x, e1x;
    Mat3x3GreenStrain<TacsScalar> strain0(u0x, e0x);
    Mat3x3GreenStrain<TacsScalar> strain1(u1x, e1x);

    // This isn't really the energy, but is okay for testing..
    Scalar<TacsScalar> energy;
    Symm3x3SymmMultTraceScale<TacsScalar> trace(detXd, e0x, e1x, energy);

    return energy.value;
}

TacsScalar test_shell_forward( const TacsScalar n0_data[],
                               const TacsScalar n0_ddata[],
                               const TacsScalar n0xi_data[],
                               const TacsScalar n0xi_ddata[],
                               const TacsScalar X0xi_data[],
                               const TacsScalar X0xi_ddata[],
                               const TacsScalar u0xi_data[],
                               const TacsScalar d0_data[],
                               const TacsScalar d0xi_data[] ){
    ADVec3<TacsScalar> n0(n0_data, n0_ddata);
    ADMat3x2<TacsScalar> n0xi(n0xi_data, n0xi_ddata);
    ADMat3x2<TacsScalar> X0xi(X0xi_data, X0xi_ddata);

    // Displacements and directors
    Mat3x2<TacsScalar> u0xi(u0xi_data);
    Vec3<TacsScalar> d0(d0_data);
    Mat3x2<TacsScalar> d0xi(d0xi_data);

    // Get the in-plane tangent directions
    ADVec3<TacsScalar> t1_dir, t2_dir;
    ADMat3x2ToADVec3<TacsScalar> X0tovecs(X0xi, t1_dir, t2_dir);
    X0tovecs.forward();

    // Compute the normal direction
    ADVec3<TacsScalar> n1_dir, n1;
//    ADVec3CrossProduct<TacsScalar> cross_normal(t1_dir, t2_dir, n1_dir);
    cross_normal.forward();
//    ADVec3Normalize<TacsScalar> normalize_normal(n1_dir, n1);
    normalize_normal.forward();

    // Normalize the t1 direction
    ADVec3<TacsScalar> t1;
//    ADVec3Normalize<TacsScalar> normalize_t1(t1_dir, t1);
    normalize_t1.forward();

    // Find the t2 direction
    ADVec3<TacsScalar> t2;
//    ADVec3CrossProduct<TacsScalar> cross_t2(t1, n1, t2);
    cross_t2.forward();

    // Form the transformation matrix
    ADMat3x3<TacsScalar> T;
//    ADMat3x3FromThreeADVec3<TacsScalar> assembleT(t1, t2, n1, T);
    assembleT.forward();

    // Assemble the matrix Xd = [X0,xi | n0]
    ADMat3x3<TacsScalar> Xd, Xdz;
//    ADMat3x3FromADMat3x2AndADVec3<TacsScalar> assembleXd(X0xi, n0, Xd);
    assembleXd.forward();
//    ADMat3x3FromADMat3x2<TacsScalar> assembleXdz(n0xi, Xdz);
    assembleXdz.forward();

    // Assemble the zero-th and first order terms
    Mat3x3<TacsScalar> u0d, u1d;
//    Mat3x3FromMat3x2AndVec3<TacsScalar> assembleU0xi(u0xi, d0, u0d);
//    Mat3x3FromMat3x2<TacsScalar> assembleU1xi(d0xi, u1d);

    // Compute the inverse matrix
    ADMat3x3<TacsScalar> Xdinv;
    ADScalar<TacsScalar> detXd;
//    ADMat3x3Det<TacsScalar> computedetXd(Xd, detXd);
    computedetXd.forward();
//    ADMat3x3Inverse <TacsScalar>invXd(Xd, Xdinv);
    invXd.forward();

    // Compute XdinvT = Xdinv * T
    ADMat3x3<TacsScalar> XdinvT;
//    ADMat3x3ADMatMult<TacsScalar> multXinvT(Xdinv, T, XdinvT);
    multXinvT.forward();

    // Compute XdinvzT = - Xdinv * Xdz * Xdinv * T
    ADMat3x3<TacsScalar> XdinvzT, XdzXdinvT;
//    ADMat3x3ADMatMult<TacsScalar> multXdzXdinvT(Xdz, XdinvT, XdzXdinvT);
    multXdzXdinvT.forward();
//    ADMat3x3ADMatMult<TacsScalar> multXdinvzT(-1.0, Xdinv, XdzXdinvT, XdinvzT);
    multXdinvzT.forward();

    // Compute u1x = T^{T} * (u1d * XdinvT + u0d * XdinvzT)
    ADMat3x3<TacsScalar> u1dXdinvT, u1x;
//    Mat3x3ADMatMult<TacsScalar> multu1d(u1d, XdinvT, u1dXdinvT);
    multu1d.forward();
//    Mat3x3ADMatMultAdd<TacsScalar> multu1dadd(u0d, XdinvzT, u1dXdinvT);
    multu1dadd.forward();
//    ADMatTrans3x3ADMatMult<TacsScalar> multu1x(T, u1dXdinvT, u1x);
    multu1x.forward();

    // Compute u0x = T^{T} * u0d * XdinvT
    ADMat3x3<TacsScalar> u0dXdinvT, u0x;
//    Mat3x3ADMatMult<TacsScalar> multu0d(u0d, XdinvT, u0dXdinvT);
    multu0d.forward();
//    ADMatTrans3x3ADMatMult<TacsScalar> multu0x(T, u0dXdinvT, u0x);
    multu0x.forward();

    // Compute the Green strain
    ADSymm3x3<TacsScalar> e0x, e1x;
    ADMat3x3GreenStrain<TacsScalar> strain0(u0x, e0x);
    strain0.forward();
    ADMat3x3GreenStrain<TacsScalar> strain1(u1x, e1x);
    strain1.forward();

    // This isn't really the energy, but is okay for testing..
    ADScalar<TacsScalar> energy;
    ADSymm3x3ADSymmMultTraceADScale<TacsScalar> trace(detXd, e0x, e1x, energy);
    trace.forward();

    return energy.valued;
}

TacsScalar test_shell_reverse( const TacsScalar n0_data[],
                               const TacsScalar n0_ddata[],
                               const TacsScalar n0xi_data[],
                               const TacsScalar n0xi_ddata[],
                               const TacsScalar X0xi_data[],
                               const TacsScalar X0xi_ddata[],
                               const TacsScalar u0xi_data[],
                               const TacsScalar d0_data[],
                               const TacsScalar d0xi_data[] ){
    ADVec3<TacsScalar> n0(n0_data);
    ADMat3x2<TacsScalar> n0xi(n0xi_data);
    ADMat3x2<TacsScalar> X0xi(X0xi_data);

    // Displacements and directors
    Mat3x2<TacsScalar> u0xi(u0xi_data);
    Vec3<TacsScalar> d0(d0_data);
    Mat3x2<TacsScalar> d0xi(d0xi_data);

    // Get the in-plane tangent directions
    ADVec3<TacsScalar> t1_dir, t2_dir;
    ADMat3x2ToADVec3<TacsScalar> X0tovecs(X0xi, t1_dir, t2_dir);

    // Compute the normal direction
    ADVec3<TacsScalar> n1_dir, n1;
//    ADVec3CrossProduct<TacsScalar> cross_normal(t1_dir, t2_dir, n1_dir);
//    ADVec3Normalize<TacsScalar> normalize_normal(n1_dir, n1);

    // Normalize the t1 direction
    ADVec3<TacsScalar> t1;
//    ADVec3Normalize<TacsScalar> normalize_t1(t1_dir, t1);

    // Find the t2 direction
    ADVec3<TacsScalar> t2;
//    ADVec3CrossProduct<TacsScalar> cross_t2(t1, n1, t2);

    // Form the transformation matrix
    ADMat3x3<TacsScalar> T;
//    ADMat3x3FromThreeADVec3<TacsScalar> assembleT(t1, t2, n1, T);

    // Assemble the matrix Xd = [X0,xi | n0]
    ADMat3x3<TacsScalar> Xd, Xdz;
//    ADMat3x3FromADMat3x2AndADVec3<TacsScalar> assembleXd(X0xi, n0, Xd);
//    ADMat3x3FromADMat3x2<TacsScalar> assembleXdz(n0xi, Xdz);

    // Assemble the zero-th and first order terms
    Mat3x3<TacsScalar> u0d, u1d;
//    Mat3x3FromMat3x2AndVec3<TacsScalar> assembleU0xi(u0xi, d0, u0d);
//    Mat3x3FromMat3x2<TacsScalar> assembleU1xi(d0xi, u1d);

    // Compute the inverse matrix
    ADMat3x3<TacsScalar> Xdinv;
    ADScalar<TacsScalar> detXd;
//    ADMat3x3Det<TacsScalar> computedetXd(Xd, detXd);
//    ADMat3x3Inverse<TacsScalar> invXd(Xd, Xdinv);

    // Compute XdinvT = Xdinv * T
    ADMat3x3<TacsScalar> XdinvT;
//    ADMat3x3ADMatMult<TacsScalar> multXinvT(Xdinv, T, XdinvT);

    // Compute XdinvzT = - Xdinv * Xdz * Xdinv * T
    ADMat3x3<TacsScalar> XdinvzT, XdzXdinvT;
//    ADMat3x3ADMatMult<TacsScalar> multXdzXdinvT(Xdz, XdinvT, XdzXdinvT);
//    ADMat3x3ADMatMult<TacsScalar> multXdinvzT(-1.0, Xdinv, XdzXdinvT, XdinvzT);

    // Compute u1x = T^{T} * (u1d * XdinvT + u0d * XdinvzT)
    ADMat3x3<TacsScalar> u1dXdinvT, u1x;
//    Mat3x3ADMatMult<TacsScalar> multu1d(u1d, XdinvT, u1dXdinvT);
//    Mat3x3ADMatMultAdd<TacsScalar> multu1dadd(u0d, XdinvzT, u1dXdinvT);
//    ADMatTrans3x3ADMatMult<TacsScalar> multu1x(T, u1dXdinvT, u1x);

    // Compute u0x = T^{T} * u0d * XdinvT
    ADMat3x3<TacsScalar> u0dXdinvT, u0x;
//    Mat3x3ADMatMult<TacsScalar> multu0d(u0d, XdinvT, u0dXdinvT);
//    ADMatTrans3x3ADMatMult<TacsScalar> multu0x(T, u0dXdinvT, u0x);

    // Compute the Green strain
    ADSymm3x3<TacsScalar> e0x, e1x;
    ADMat3x3GreenStrain<TacsScalar> strain0(u0x, e0x);
    ADMat3x3GreenStrain<TacsScalar> strain1(u1x, e1x);

    // This isn't really the energy, but is okay for testing..
    ADScalar<TacsScalar> energy;
    ADSymm3x3ADSymmMultTraceADScale<TacsScalar> trace(detXd, e0x, e1x, energy);

    // Reverse mode
    energy.valued = 1.0;

    trace.reverse();
    strain1.reverse();
    strain0.reverse();
    multu0x.reverse();
    multu0d.reverse();
    multu1x.reverse();
    multu1dadd.reverse();
    multu1d.reverse();
    multXdinvzT.reverse();
    multXdzXdinvT.reverse();
    multXinvT.reverse();
    invXd.reverse();
    computedetXd.reverse();
    assembleXdz.reverse();
    assembleXd.reverse();
    assembleT.reverse();
    cross_t2.reverse();
    normalize_t1.reverse();
    normalize_normal.reverse();
    cross_normal.reverse();
    X0tovecs.reverse();

    TacsScalar deriv = 0.0;
    for ( int i = 0; i < 3; i++ ){
        deriv += n0.xd[i] * n0_ddata[i];
    }

    for ( int i = 0; i < 6; i++ ){
        deriv += n0xi.Ad[i] * n0xi_ddata[i];
        deriv += X0xi.Ad[i] * X0xi_ddata[i];
    }

    return deriv;
}

void test_shell(){
    TacsScalar n0[3], n0d[3];
    TacsScalar n0xi[6], n0xid[6];
    TacsScalar X0xi[6], X0xid[6];
    TacsScalar u0xi[6];
    TacsScalar d0[3];
    TacsScalar d0xi[6];

    // Fill in the data
    generate_random_array(3, n0);
    generate_random_array(3, n0d);
    generate_random_array(6, n0xi);
    generate_random_array(6, n0xid);
    generate_random_array(6, X0xi);
    generate_random_array(6, X0xid);
    generate_random_array(6, u0xi);
    generate_random_array(3, d0);
    generate_random_array(6, d0xi);

    TacsScalar f0 = test_shell_scalar(n0, n0xi, X0xi, u0xi, d0, d0xi);
    TacsScalar df = test_shell_forward(n0, n0d, n0xi, n0xid,
                                       X0xi, X0xid,
                                       u0xi, d0, d0xi);
    TacsScalar dfr = test_shell_reverse(n0, n0d, n0xi, n0xid,
                                        X0xi, X0xid,
                                        u0xi, d0, d0xi);

    TacsReal dh = 1e-30;
    for ( int i = 0; i < 3; i++ ){
        n0[i] += TacsScalar(0.0, dh) * n0d[i];
    }
    for ( int i = 0; i < 6; i++ ){
        n0xi[i] += TacsScalar(0.0, dh) * n0xid[i];
        X0xi[i] += TacsScalar(0.0, dh) * X0xid[i];
    }

    TacsScalar f1 = test_shell_scalar(n0, n0xi, X0xi, u0xi, d0, d0xi);
    TacsScalar fd = TacsImagPart(f1)/dh;
    printf("Shell test\n");
    printf("Function value:    %25.16e\n", TacsRealPart(f0));
    printf("Finite-difference: %25.16e\n", TacsRealPart(fd));
    printf("Forward mode:      %25.16e\n", TacsRealPart(df));
    printf("Reverse mode:      %25.16e\n", TacsRealPart(dfr));
}
