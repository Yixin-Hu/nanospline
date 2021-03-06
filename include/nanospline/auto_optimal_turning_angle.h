
// This code is automatically generated by scripts/optimal_turning_angle.py

#pragma once
#include <cassert>
#include <vector>

#include <nanospline/Exceptions.h>
#include <nanospline/PolynomialRootFinder.h>
#include <nanospline/Bezier.h>
#include <nanospline/RationalBezier.h>

namespace nanospline {


template<typename Scalar, int _degree=3, bool generic=_degree<0 >
std::vector<Scalar> optimal_points_to_reduce_turning_angle(
        const Bezier<Scalar, 2, _degree, generic>& curve, bool flip,
        Scalar t0 = 0, Scalar t1 = 1) {
    std::vector<Scalar> result;
    constexpr Scalar tol = 1e-8;

    auto tan0 = curve.evaluate_derivative(t0);
    auto tan1 = curve.evaluate_derivative(t1);

    if (tan0.norm() < tol || tan1.norm() < tol){
        std::vector<Scalar> res;
        res.push_back((t0 + t1) / 2);
        return res;
    }

    tan0 = tan0 / tan0.norm();
    tan1 = tan1 / tan1.norm();

    if (flip) {
        tan0 = tan0 * (-1);
        tan1 = tan1 * (-1);
    }

    const Scalar tan0x = tan0[0];
    const Scalar tan0y = tan0[1];

    const Scalar tan1x = tan1[0];
    const Scalar tan1y = tan1[1];


    const Scalar tcutxp = -(tan0y + tan1y)/2;
    const Scalar tcutyp = (tan0x + tan1x)/2;

    if (tcutxp < tol && tcutyp < tol){
        std::vector<Scalar> res;
        res.push_back((t0 + t1) / 2);
        return res;
    }

    if (curve.get_degree() == 2) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        PolynomialRootFinder<Scalar, 1>::find_real_roots_in_interval({
            -2*cx0*tcutxp + 2*cx1*tcutxp - 2*cy0*tcutyp + 2*cy1*tcutyp,
    2*cx0*tcutxp - 4*cx1*tcutxp + 2*cx2*tcutxp + 2*cy0*tcutyp - 4*cy1*tcutyp + 2*cy2*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 3) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        PolynomialRootFinder<Scalar, 2>::find_real_roots_in_interval({
            -3*cx0*tcutxp + 3*cx1*tcutxp - 3*cy0*tcutyp + 3*cy1*tcutyp,
    6*cx0*tcutxp - 12*cx1*tcutxp + 6*cx2*tcutxp + 6*cy0*tcutyp - 12*cy1*tcutyp + 6*cy2*tcutyp,
    -3*cx0*tcutxp + 9*cx1*tcutxp - 9*cx2*tcutxp + 3*cx3*tcutxp - 3*cy0*tcutyp + 9*cy1*tcutyp - 9*cy2*tcutyp + 3*cy3*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 4) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        PolynomialRootFinder<Scalar, 3>::find_real_roots_in_interval({
            -4*cx0*tcutxp + 4*cx1*tcutxp - 4*cy0*tcutyp + 4*cy1*tcutyp,
    12*cx0*tcutxp - 24*cx1*tcutxp + 12*cx2*tcutxp + 12*cy0*tcutyp - 24*cy1*tcutyp + 12*cy2*tcutyp,
    -12*cx0*tcutxp + 36*cx1*tcutxp - 36*cx2*tcutxp + 12*cx3*tcutxp - 12*cy0*tcutyp + 36*cy1*tcutyp - 36*cy2*tcutyp + 12*cy3*tcutyp,
    4*cx0*tcutxp - 16*cx1*tcutxp + 24*cx2*tcutxp - 16*cx3*tcutxp + 4*cx4*tcutxp + 4*cy0*tcutyp - 16*cy1*tcutyp + 24*cy2*tcutyp - 16*cy3*tcutyp + 4*cy4*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 5) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        Scalar cx5 = ctrl_pts(5, 0);
        Scalar cy5 = ctrl_pts(5, 1);
        PolynomialRootFinder<Scalar, 4>::find_real_roots_in_interval({
            -5*cx0*tcutxp + 5*cx1*tcutxp - 5*cy0*tcutyp + 5*cy1*tcutyp,
    20*cx0*tcutxp - 40*cx1*tcutxp + 20*cx2*tcutxp + 20*cy0*tcutyp - 40*cy1*tcutyp + 20*cy2*tcutyp,
    -30*cx0*tcutxp + 90*cx1*tcutxp - 90*cx2*tcutxp + 30*cx3*tcutxp - 30*cy0*tcutyp + 90*cy1*tcutyp - 90*cy2*tcutyp + 30*cy3*tcutyp,
    20*cx0*tcutxp - 80*cx1*tcutxp + 120*cx2*tcutxp - 80*cx3*tcutxp + 20*cx4*tcutxp + 20*cy0*tcutyp - 80*cy1*tcutyp + 120*cy2*tcutyp - 80*cy3*tcutyp + 20*cy4*tcutyp,
    -5*cx0*tcutxp + 25*cx1*tcutxp - 50*cx2*tcutxp + 50*cx3*tcutxp - 25*cx4*tcutxp + 5*cx5*tcutxp - 5*cy0*tcutyp + 25*cy1*tcutyp - 50*cy2*tcutyp + 50*cy3*tcutyp - 25*cy4*tcutyp + 5*cy5*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 6) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        Scalar cx5 = ctrl_pts(5, 0);
        Scalar cy5 = ctrl_pts(5, 1);
        Scalar cx6 = ctrl_pts(6, 0);
        Scalar cy6 = ctrl_pts(6, 1);
        PolynomialRootFinder<Scalar, 5>::find_real_roots_in_interval({
            -6*cx0*tcutxp + 6*cx1*tcutxp - 6*cy0*tcutyp + 6*cy1*tcutyp,
    30*cx0*tcutxp - 60*cx1*tcutxp + 30*cx2*tcutxp + 30*cy0*tcutyp - 60*cy1*tcutyp + 30*cy2*tcutyp,
    -60*cx0*tcutxp + 180*cx1*tcutxp - 180*cx2*tcutxp + 60*cx3*tcutxp - 60*cy0*tcutyp + 180*cy1*tcutyp - 180*cy2*tcutyp + 60*cy3*tcutyp,
    60*cx0*tcutxp - 240*cx1*tcutxp + 360*cx2*tcutxp - 240*cx3*tcutxp + 60*cx4*tcutxp + 60*cy0*tcutyp - 240*cy1*tcutyp + 360*cy2*tcutyp - 240*cy3*tcutyp + 60*cy4*tcutyp,
    -30*cx0*tcutxp + 150*cx1*tcutxp - 300*cx2*tcutxp + 300*cx3*tcutxp - 150*cx4*tcutxp + 30*cx5*tcutxp - 30*cy0*tcutyp + 150*cy1*tcutyp - 300*cy2*tcutyp + 300*cy3*tcutyp - 150*cy4*tcutyp + 30*cy5*tcutyp,
    6*cx0*tcutxp - 36*cx1*tcutxp + 90*cx2*tcutxp - 120*cx3*tcutxp + 90*cx4*tcutxp - 36*cx5*tcutxp + 6*cx6*tcutxp + 6*cy0*tcutyp - 36*cy1*tcutyp + 90*cy2*tcutyp - 120*cy3*tcutyp + 90*cy4*tcutyp - 36*cy5*tcutyp + 6*cy6*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 7) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        Scalar cx5 = ctrl_pts(5, 0);
        Scalar cy5 = ctrl_pts(5, 1);
        Scalar cx6 = ctrl_pts(6, 0);
        Scalar cy6 = ctrl_pts(6, 1);
        Scalar cx7 = ctrl_pts(7, 0);
        Scalar cy7 = ctrl_pts(7, 1);
        PolynomialRootFinder<Scalar, 6>::find_real_roots_in_interval({
            -7*cx0*tcutxp + 7*cx1*tcutxp - 7*cy0*tcutyp + 7*cy1*tcutyp,
    42*cx0*tcutxp - 84*cx1*tcutxp + 42*cx2*tcutxp + 42*cy0*tcutyp - 84*cy1*tcutyp + 42*cy2*tcutyp,
    -105*cx0*tcutxp + 315*cx1*tcutxp - 315*cx2*tcutxp + 105*cx3*tcutxp - 105*cy0*tcutyp + 315*cy1*tcutyp - 315*cy2*tcutyp + 105*cy3*tcutyp,
    140*cx0*tcutxp - 560*cx1*tcutxp + 840*cx2*tcutxp - 560*cx3*tcutxp + 140*cx4*tcutxp + 140*cy0*tcutyp - 560*cy1*tcutyp + 840*cy2*tcutyp - 560*cy3*tcutyp + 140*cy4*tcutyp,
    -105*cx0*tcutxp + 525*cx1*tcutxp - 1050*cx2*tcutxp + 1050*cx3*tcutxp - 525*cx4*tcutxp + 105*cx5*tcutxp - 105*cy0*tcutyp + 525*cy1*tcutyp - 1050*cy2*tcutyp + 1050*cy3*tcutyp - 525*cy4*tcutyp + 105*cy5*tcutyp,
    42*cx0*tcutxp - 252*cx1*tcutxp + 630*cx2*tcutxp - 840*cx3*tcutxp + 630*cx4*tcutxp - 252*cx5*tcutxp + 42*cx6*tcutxp + 42*cy0*tcutyp - 252*cy1*tcutyp + 630*cy2*tcutyp - 840*cy3*tcutyp + 630*cy4*tcutyp - 252*cy5*tcutyp + 42*cy6*tcutyp,
    -7*cx0*tcutxp + 49*cx1*tcutxp - 147*cx2*tcutxp + 245*cx3*tcutxp - 245*cx4*tcutxp + 147*cx5*tcutxp - 49*cx6*tcutxp + 7*cx7*tcutxp - 7*cy0*tcutyp + 49*cy1*tcutyp - 147*cy2*tcutyp + 245*cy3*tcutyp - 245*cy4*tcutyp + 147*cy5*tcutyp - 49*cy6*tcutyp + 7*cy7*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 8) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        Scalar cx5 = ctrl_pts(5, 0);
        Scalar cy5 = ctrl_pts(5, 1);
        Scalar cx6 = ctrl_pts(6, 0);
        Scalar cy6 = ctrl_pts(6, 1);
        Scalar cx7 = ctrl_pts(7, 0);
        Scalar cy7 = ctrl_pts(7, 1);
        Scalar cx8 = ctrl_pts(8, 0);
        Scalar cy8 = ctrl_pts(8, 1);
        PolynomialRootFinder<Scalar, 7>::find_real_roots_in_interval({
            -8*cx0*tcutxp + 8*cx1*tcutxp - 8*cy0*tcutyp + 8*cy1*tcutyp,
    56*cx0*tcutxp - 112*cx1*tcutxp + 56*cx2*tcutxp + 56*cy0*tcutyp - 112*cy1*tcutyp + 56*cy2*tcutyp,
    -168*cx0*tcutxp + 504*cx1*tcutxp - 504*cx2*tcutxp + 168*cx3*tcutxp - 168*cy0*tcutyp + 504*cy1*tcutyp - 504*cy2*tcutyp + 168*cy3*tcutyp,
    280*cx0*tcutxp - 1120*cx1*tcutxp + 1680*cx2*tcutxp - 1120*cx3*tcutxp + 280*cx4*tcutxp + 280*cy0*tcutyp - 1120*cy1*tcutyp + 1680*cy2*tcutyp - 1120*cy3*tcutyp + 280*cy4*tcutyp,
    -280*cx0*tcutxp + 1400*cx1*tcutxp - 2800*cx2*tcutxp + 2800*cx3*tcutxp - 1400*cx4*tcutxp + 280*cx5*tcutxp - 280*cy0*tcutyp + 1400*cy1*tcutyp - 2800*cy2*tcutyp + 2800*cy3*tcutyp - 1400*cy4*tcutyp + 280*cy5*tcutyp,
    168*cx0*tcutxp - 1008*cx1*tcutxp + 2520*cx2*tcutxp - 3360*cx3*tcutxp + 2520*cx4*tcutxp - 1008*cx5*tcutxp + 168*cx6*tcutxp + 168*cy0*tcutyp - 1008*cy1*tcutyp + 2520*cy2*tcutyp - 3360*cy3*tcutyp + 2520*cy4*tcutyp - 1008*cy5*tcutyp + 168*cy6*tcutyp,
    -56*cx0*tcutxp + 392*cx1*tcutxp - 1176*cx2*tcutxp + 1960*cx3*tcutxp - 1960*cx4*tcutxp + 1176*cx5*tcutxp - 392*cx6*tcutxp + 56*cx7*tcutxp - 56*cy0*tcutyp + 392*cy1*tcutyp - 1176*cy2*tcutyp + 1960*cy3*tcutyp - 1960*cy4*tcutyp + 1176*cy5*tcutyp - 392*cy6*tcutyp + 56*cy7*tcutyp,
    8*cx0*tcutxp - 64*cx1*tcutxp + 224*cx2*tcutxp - 448*cx3*tcutxp + 560*cx4*tcutxp - 448*cx5*tcutxp + 224*cx6*tcutxp - 64*cx7*tcutxp + 8*cx8*tcutxp + 8*cy0*tcutyp - 64*cy1*tcutyp + 224*cy2*tcutyp - 448*cy3*tcutyp + 560*cy4*tcutyp - 448*cy5*tcutyp + 224*cy6*tcutyp - 64*cy7*tcutyp + 8*cy8*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 9) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        Scalar cx5 = ctrl_pts(5, 0);
        Scalar cy5 = ctrl_pts(5, 1);
        Scalar cx6 = ctrl_pts(6, 0);
        Scalar cy6 = ctrl_pts(6, 1);
        Scalar cx7 = ctrl_pts(7, 0);
        Scalar cy7 = ctrl_pts(7, 1);
        Scalar cx8 = ctrl_pts(8, 0);
        Scalar cy8 = ctrl_pts(8, 1);
        Scalar cx9 = ctrl_pts(9, 0);
        Scalar cy9 = ctrl_pts(9, 1);
        PolynomialRootFinder<Scalar, 8>::find_real_roots_in_interval({
            -9*cx0*tcutxp + 9*cx1*tcutxp - 9*cy0*tcutyp + 9*cy1*tcutyp,
    72*cx0*tcutxp - 144*cx1*tcutxp + 72*cx2*tcutxp + 72*cy0*tcutyp - 144*cy1*tcutyp + 72*cy2*tcutyp,
    -252*cx0*tcutxp + 756*cx1*tcutxp - 756*cx2*tcutxp + 252*cx3*tcutxp - 252*cy0*tcutyp + 756*cy1*tcutyp - 756*cy2*tcutyp + 252*cy3*tcutyp,
    504*cx0*tcutxp - 2016*cx1*tcutxp + 3024*cx2*tcutxp - 2016*cx3*tcutxp + 504*cx4*tcutxp + 504*cy0*tcutyp - 2016*cy1*tcutyp + 3024*cy2*tcutyp - 2016*cy3*tcutyp + 504*cy4*tcutyp,
    -630*cx0*tcutxp + 3150*cx1*tcutxp - 6300*cx2*tcutxp + 6300*cx3*tcutxp - 3150*cx4*tcutxp + 630*cx5*tcutxp - 630*cy0*tcutyp + 3150*cy1*tcutyp - 6300*cy2*tcutyp + 6300*cy3*tcutyp - 3150*cy4*tcutyp + 630*cy5*tcutyp,
    504*cx0*tcutxp - 3024*cx1*tcutxp + 7560*cx2*tcutxp - 10080*cx3*tcutxp + 7560*cx4*tcutxp - 3024*cx5*tcutxp + 504*cx6*tcutxp + 504*cy0*tcutyp - 3024*cy1*tcutyp + 7560*cy2*tcutyp - 10080*cy3*tcutyp + 7560*cy4*tcutyp - 3024*cy5*tcutyp + 504*cy6*tcutyp,
    -252*cx0*tcutxp + 1764*cx1*tcutxp - 5292*cx2*tcutxp + 8820*cx3*tcutxp - 8820*cx4*tcutxp + 5292*cx5*tcutxp - 1764*cx6*tcutxp + 252*cx7*tcutxp - 252*cy0*tcutyp + 1764*cy1*tcutyp - 5292*cy2*tcutyp + 8820*cy3*tcutyp - 8820*cy4*tcutyp + 5292*cy5*tcutyp - 1764*cy6*tcutyp + 252*cy7*tcutyp,
    72*cx0*tcutxp - 576*cx1*tcutxp + 2016*cx2*tcutxp - 4032*cx3*tcutxp + 5040*cx4*tcutxp - 4032*cx5*tcutxp + 2016*cx6*tcutxp - 576*cx7*tcutxp + 72*cx8*tcutxp + 72*cy0*tcutyp - 576*cy1*tcutyp + 2016*cy2*tcutyp - 4032*cy3*tcutyp + 5040*cy4*tcutyp - 4032*cy5*tcutyp + 2016*cy6*tcutyp - 576*cy7*tcutyp + 72*cy8*tcutyp,
    -9*cx0*tcutxp + 81*cx1*tcutxp - 324*cx2*tcutxp + 756*cx3*tcutxp - 1134*cx4*tcutxp + 1134*cx5*tcutxp - 756*cx6*tcutxp + 324*cx7*tcutxp - 81*cx8*tcutxp + 9*cx9*tcutxp - 9*cy0*tcutyp + 81*cy1*tcutyp - 324*cy2*tcutyp + 756*cy3*tcutyp - 1134*cy4*tcutyp + 1134*cy5*tcutyp - 756*cy6*tcutyp + 324*cy7*tcutyp - 81*cy8*tcutyp + 9*cy9*tcutyp
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 10) {
        const auto& ctrl_pts = curve.get_control_points();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        Scalar cx5 = ctrl_pts(5, 0);
        Scalar cy5 = ctrl_pts(5, 1);
        Scalar cx6 = ctrl_pts(6, 0);
        Scalar cy6 = ctrl_pts(6, 1);
        Scalar cx7 = ctrl_pts(7, 0);
        Scalar cy7 = ctrl_pts(7, 1);
        Scalar cx8 = ctrl_pts(8, 0);
        Scalar cy8 = ctrl_pts(8, 1);
        Scalar cx9 = ctrl_pts(9, 0);
        Scalar cy9 = ctrl_pts(9, 1);
        Scalar cx10 = ctrl_pts(10, 0);
        Scalar cy10 = ctrl_pts(10, 1);
        PolynomialRootFinder<Scalar, 9>::find_real_roots_in_interval({
            -10*cx0*tcutxp + 10*cx1*tcutxp - 10*cy0*tcutyp + 10*cy1*tcutyp,
    90*cx0*tcutxp - 180*cx1*tcutxp + 90*cx2*tcutxp + 90*cy0*tcutyp - 180*cy1*tcutyp + 90*cy2*tcutyp,
    -360*cx0*tcutxp + 1080*cx1*tcutxp - 1080*cx2*tcutxp + 360*cx3*tcutxp - 360*cy0*tcutyp + 1080*cy1*tcutyp - 1080*cy2*tcutyp + 360*cy3*tcutyp,
    840*cx0*tcutxp - 3360*cx1*tcutxp + 5040*cx2*tcutxp - 3360*cx3*tcutxp + 840*cx4*tcutxp + 840*cy0*tcutyp - 3360*cy1*tcutyp + 5040*cy2*tcutyp - 3360*cy3*tcutyp + 840*cy4*tcutyp,
    -1260*cx0*tcutxp + 6300*cx1*tcutxp - 12600*cx2*tcutxp + 12600*cx3*tcutxp - 6300*cx4*tcutxp + 1260*cx5*tcutxp - 1260*cy0*tcutyp + 6300*cy1*tcutyp - 12600*cy2*tcutyp + 12600*cy3*tcutyp - 6300*cy4*tcutyp + 1260*cy5*tcutyp,
    1260*cx0*tcutxp - 7560*cx1*tcutxp + 18900*cx2*tcutxp - 25200*cx3*tcutxp + 18900*cx4*tcutxp - 7560*cx5*tcutxp + 1260*cx6*tcutxp + 1260*cy0*tcutyp - 7560*cy1*tcutyp + 18900*cy2*tcutyp - 25200*cy3*tcutyp + 18900*cy4*tcutyp - 7560*cy5*tcutyp + 1260*cy6*tcutyp,
    -840*cx0*tcutxp + 5880*cx1*tcutxp - 17640*cx2*tcutxp + 29400*cx3*tcutxp - 29400*cx4*tcutxp + 17640*cx5*tcutxp - 5880*cx6*tcutxp + 840*cx7*tcutxp - 840*cy0*tcutyp + 5880*cy1*tcutyp - 17640*cy2*tcutyp + 29400*cy3*tcutyp - 29400*cy4*tcutyp + 17640*cy5*tcutyp - 5880*cy6*tcutyp + 840*cy7*tcutyp,
    360*cx0*tcutxp - 2880*cx1*tcutxp + 10080*cx2*tcutxp - 20160*cx3*tcutxp + 25200*cx4*tcutxp - 20160*cx5*tcutxp + 10080*cx6*tcutxp - 2880*cx7*tcutxp + 360*cx8*tcutxp + 360*cy0*tcutyp - 2880*cy1*tcutyp + 10080*cy2*tcutyp - 20160*cy3*tcutyp + 25200*cy4*tcutyp - 20160*cy5*tcutyp + 10080*cy6*tcutyp - 2880*cy7*tcutyp + 360*cy8*tcutyp,
    -90*cx0*tcutxp + 810*cx1*tcutxp - 3240*cx2*tcutxp + 7560*cx3*tcutxp - 11340*cx4*tcutxp + 11340*cx5*tcutxp - 7560*cx6*tcutxp + 3240*cx7*tcutxp - 810*cx8*tcutxp + 90*cx9*tcutxp - 90*cy0*tcutyp + 810*cy1*tcutyp - 3240*cy2*tcutyp + 7560*cy3*tcutyp - 11340*cy4*tcutyp + 11340*cy5*tcutyp - 7560*cy6*tcutyp + 3240*cy7*tcutyp - 810*cy8*tcutyp + 90*cy9*tcutyp,
    10*cx0*tcutxp - 100*cx1*tcutxp + 10*cx10*tcutxp + 450*cx2*tcutxp - 1200*cx3*tcutxp + 2100*cx4*tcutxp - 2520*cx5*tcutxp + 2100*cx6*tcutxp - 1200*cx7*tcutxp + 450*cx8*tcutxp - 100*cx9*tcutxp + 10*cy0*tcutyp - 100*cy1*tcutyp + 10*cy10*tcutyp + 450*cy2*tcutyp - 1200*cy3*tcutyp + 2100*cy4*tcutyp - 2520*cy5*tcutyp + 2100*cy6*tcutyp - 1200*cy7*tcutyp + 450*cy8*tcutyp - 100*cy9*tcutyp
        },
        result, t0, t1, tol);
    } else{
        throw not_implemented_error(
            "Inflection computation only works on Bezier curve with degree lower than 10");
    }

    return result;
}



template<typename Scalar, int _degree=3, bool generic=_degree<0 >
std::vector<Scalar> optimal_points_to_reduce_turning_angle(
        const RationalBezier<Scalar, 2, _degree, generic>& curve, bool flip,
        Scalar t0 = 0, Scalar t1 = 1) {
    std::vector<Scalar> result;
    constexpr Scalar tol = 1e-8;

    auto tan0 = curve.evaluate_derivative(t0);
    auto tan1 = curve.evaluate_derivative(t1);

    if (tan0.norm() < tol || tan1.norm() < tol){
        std::vector<Scalar> res;
        res.push_back((t0 + t1) / 2);
        return res;
    }

    tan0 = tan0 / tan0.norm();
    tan1 = tan1 / tan1.norm();

    if (flip) {
        tan0 = tan0 * (-1);
        tan1 = tan1 * (-1);
    }

    const Scalar tan0x = tan0[0];
    const Scalar tan0y = tan0[1];

    const Scalar tan1x = tan1[0];
    const Scalar tan1y = tan1[1];


    const Scalar tcutxp = -(tan0y + tan1y)/2;
    const Scalar tcutyp = (tan0x + tan1x)/2;

    if (tcutxp < tol && tcutyp < tol){
        std::vector<Scalar> res;
        res.push_back((t0 + t1) / 2);
        return res;
    }

    if (curve.get_degree() == 2) {
        const auto& ctrl_pts = curve.get_control_points();
        const auto& weights = curve.get_weights();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar w0 = weights(0);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar w1 = weights(1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar w2 = weights(2);
        PolynomialRootFinder<Scalar, 2>::find_real_roots_in_interval({
            -2*cx0*tcutxp*w0*w1 + 2*cx1*tcutxp*w0*w1 - 2*cy0*tcutyp*w0*w1 + 2*cy1*tcutyp*w0*w1,
    4*cx0*tcutxp*w0*w1 - 2*cx0*tcutxp*w0*w2 - 4*cx1*tcutxp*w0*w1 + 2*cx2*tcutxp*w0*w2 + 4*cy0*tcutyp*w0*w1 - 2*cy0*tcutyp*w0*w2 - 4*cy1*tcutyp*w0*w1 + 2*cy2*tcutyp*w0*w2,
    -2*cx0*tcutxp*w0*w1 + 2*cx0*tcutxp*w0*w2 + 2*cx1*tcutxp*w0*w1 - 2*cx1*tcutxp*w1*w2 - 2*cx2*tcutxp*w0*w2 + 2*cx2*tcutxp*w1*w2 - 2*cy0*tcutyp*w0*w1 + 2*cy0*tcutyp*w0*w2 + 2*cy1*tcutyp*w0*w1 - 2*cy1*tcutyp*w1*w2 - 2*cy2*tcutyp*w0*w2 + 2*cy2*tcutyp*w1*w2
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 3) {
        const auto& ctrl_pts = curve.get_control_points();
        const auto& weights = curve.get_weights();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar w0 = weights(0);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar w1 = weights(1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar w2 = weights(2);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar w3 = weights(3);
        PolynomialRootFinder<Scalar, 4>::find_real_roots_in_interval({
            -3*cx0*tcutxp*w0*w1 + 3*cx1*tcutxp*w0*w1 - 3*cy0*tcutyp*w0*w1 + 3*cy1*tcutyp*w0*w1,
    12*cx0*tcutxp*w0*w1 - 6*cx0*tcutxp*w0*w2 - 12*cx1*tcutxp*w0*w1 + 6*cx2*tcutxp*w0*w2 + 12*cy0*tcutyp*w0*w1 - 6*cy0*tcutyp*w0*w2 - 12*cy1*tcutyp*w0*w1 + 6*cy2*tcutyp*w0*w2,
    -18*cx0*tcutxp*w0*w1 + 18*cx0*tcutxp*w0*w2 - 3*cx0*tcutxp*w0*w3 + 18*cx1*tcutxp*w0*w1 - 9*cx1*tcutxp*w1*w2 - 18*cx2*tcutxp*w0*w2 + 9*cx2*tcutxp*w1*w2 + 3*cx3*tcutxp*w0*w3 - 18*cy0*tcutyp*w0*w1 + 18*cy0*tcutyp*w0*w2 - 3*cy0*tcutyp*w0*w3 + 18*cy1*tcutyp*w0*w1 - 9*cy1*tcutyp*w1*w2 - 18*cy2*tcutyp*w0*w2 + 9*cy2*tcutyp*w1*w2 + 3*cy3*tcutyp*w0*w3,
    12*cx0*tcutxp*w0*w1 - 18*cx0*tcutxp*w0*w2 + 6*cx0*tcutxp*w0*w3 - 12*cx1*tcutxp*w0*w1 + 18*cx1*tcutxp*w1*w2 - 6*cx1*tcutxp*w1*w3 + 18*cx2*tcutxp*w0*w2 - 18*cx2*tcutxp*w1*w2 - 6*cx3*tcutxp*w0*w3 + 6*cx3*tcutxp*w1*w3 + 12*cy0*tcutyp*w0*w1 - 18*cy0*tcutyp*w0*w2 + 6*cy0*tcutyp*w0*w3 - 12*cy1*tcutyp*w0*w1 + 18*cy1*tcutyp*w1*w2 - 6*cy1*tcutyp*w1*w3 + 18*cy2*tcutyp*w0*w2 - 18*cy2*tcutyp*w1*w2 - 6*cy3*tcutyp*w0*w3 + 6*cy3*tcutyp*w1*w3,
    -3*cx0*tcutxp*w0*w1 + 6*cx0*tcutxp*w0*w2 - 3*cx0*tcutxp*w0*w3 + 3*cx1*tcutxp*w0*w1 - 9*cx1*tcutxp*w1*w2 + 6*cx1*tcutxp*w1*w3 - 6*cx2*tcutxp*w0*w2 + 9*cx2*tcutxp*w1*w2 - 3*cx2*tcutxp*w2*w3 + 3*cx3*tcutxp*w0*w3 - 6*cx3*tcutxp*w1*w3 + 3*cx3*tcutxp*w2*w3 - 3*cy0*tcutyp*w0*w1 + 6*cy0*tcutyp*w0*w2 - 3*cy0*tcutyp*w0*w3 + 3*cy1*tcutyp*w0*w1 - 9*cy1*tcutyp*w1*w2 + 6*cy1*tcutyp*w1*w3 - 6*cy2*tcutyp*w0*w2 + 9*cy2*tcutyp*w1*w2 - 3*cy2*tcutyp*w2*w3 + 3*cy3*tcutyp*w0*w3 - 6*cy3*tcutyp*w1*w3 + 3*cy3*tcutyp*w2*w3
        },
        result, t0, t1, tol);
    } else if (curve.get_degree() == 4) {
        const auto& ctrl_pts = curve.get_control_points();
        const auto& weights = curve.get_weights();
        Scalar cx0 = ctrl_pts(0, 0);
        Scalar cy0 = ctrl_pts(0, 1);
        Scalar w0 = weights(0);
        Scalar cx1 = ctrl_pts(1, 0);
        Scalar cy1 = ctrl_pts(1, 1);
        Scalar w1 = weights(1);
        Scalar cx2 = ctrl_pts(2, 0);
        Scalar cy2 = ctrl_pts(2, 1);
        Scalar w2 = weights(2);
        Scalar cx3 = ctrl_pts(3, 0);
        Scalar cy3 = ctrl_pts(3, 1);
        Scalar w3 = weights(3);
        Scalar cx4 = ctrl_pts(4, 0);
        Scalar cy4 = ctrl_pts(4, 1);
        Scalar w4 = weights(4);
        PolynomialRootFinder<Scalar, 6>::find_real_roots_in_interval({
            -4*cx0*tcutxp*w0*w1 + 4*cx1*tcutxp*w0*w1 - 4*cy0*tcutyp*w0*w1 + 4*cy1*tcutyp*w0*w1,
    24*cx0*tcutxp*w0*w1 - 12*cx0*tcutxp*w0*w2 - 24*cx1*tcutxp*w0*w1 + 12*cx2*tcutxp*w0*w2 + 24*cy0*tcutyp*w0*w1 - 12*cy0*tcutyp*w0*w2 - 24*cy1*tcutyp*w0*w1 + 12*cy2*tcutyp*w0*w2,
    -60*cx0*tcutxp*w0*w1 + 60*cx0*tcutxp*w0*w2 - 12*cx0*tcutxp*w0*w3 + 60*cx1*tcutxp*w0*w1 - 24*cx1*tcutxp*w1*w2 - 60*cx2*tcutxp*w0*w2 + 24*cx2*tcutxp*w1*w2 + 12*cx3*tcutxp*w0*w3 - 60*cy0*tcutyp*w0*w1 + 60*cy0*tcutyp*w0*w2 - 12*cy0*tcutyp*w0*w3 + 60*cy1*tcutyp*w0*w1 - 24*cy1*tcutyp*w1*w2 - 60*cy2*tcutyp*w0*w2 + 24*cy2*tcutyp*w1*w2 + 12*cy3*tcutyp*w0*w3,
    80*cx0*tcutxp*w0*w1 - 120*cx0*tcutxp*w0*w2 + 48*cx0*tcutxp*w0*w3 - 4*cx0*tcutxp*w0*w4 - 80*cx1*tcutxp*w0*w1 + 96*cx1*tcutxp*w1*w2 - 32*cx1*tcutxp*w1*w3 + 120*cx2*tcutxp*w0*w2 - 96*cx2*tcutxp*w1*w2 - 48*cx3*tcutxp*w0*w3 + 32*cx3*tcutxp*w1*w3 + 4*cx4*tcutxp*w0*w4 + 80*cy0*tcutyp*w0*w1 - 120*cy0*tcutyp*w0*w2 + 48*cy0*tcutyp*w0*w3 - 4*cy0*tcutyp*w0*w4 - 80*cy1*tcutyp*w0*w1 + 96*cy1*tcutyp*w1*w2 - 32*cy1*tcutyp*w1*w3 + 120*cy2*tcutyp*w0*w2 - 96*cy2*tcutyp*w1*w2 - 48*cy3*tcutyp*w0*w3 + 32*cy3*tcutyp*w1*w3 + 4*cy4*tcutyp*w0*w4,
    -60*cx0*tcutxp*w0*w1 + 120*cx0*tcutxp*w0*w2 - 72*cx0*tcutxp*w0*w3 + 12*cx0*tcutxp*w0*w4 + 60*cx1*tcutxp*w0*w1 - 144*cx1*tcutxp*w1*w2 + 96*cx1*tcutxp*w1*w3 - 12*cx1*tcutxp*w1*w4 - 120*cx2*tcutxp*w0*w2 + 144*cx2*tcutxp*w1*w2 - 24*cx2*tcutxp*w2*w3 + 72*cx3*tcutxp*w0*w3 - 96*cx3*tcutxp*w1*w3 + 24*cx3*tcutxp*w2*w3 - 12*cx4*tcutxp*w0*w4 + 12*cx4*tcutxp*w1*w4 - 60*cy0*tcutyp*w0*w1 + 120*cy0*tcutyp*w0*w2 - 72*cy0*tcutyp*w0*w3 + 12*cy0*tcutyp*w0*w4 + 60*cy1*tcutyp*w0*w1 - 144*cy1*tcutyp*w1*w2 + 96*cy1*tcutyp*w1*w3 - 12*cy1*tcutyp*w1*w4 - 120*cy2*tcutyp*w0*w2 + 144*cy2*tcutyp*w1*w2 - 24*cy2*tcutyp*w2*w3 + 72*cy3*tcutyp*w0*w3 - 96*cy3*tcutyp*w1*w3 + 24*cy3*tcutyp*w2*w3 - 12*cy4*tcutyp*w0*w4 + 12*cy4*tcutyp*w1*w4,
    24*cx0*tcutxp*w0*w1 - 60*cx0*tcutxp*w0*w2 + 48*cx0*tcutxp*w0*w3 - 12*cx0*tcutxp*w0*w4 - 24*cx1*tcutxp*w0*w1 + 96*cx1*tcutxp*w1*w2 - 96*cx1*tcutxp*w1*w3 + 24*cx1*tcutxp*w1*w4 + 60*cx2*tcutxp*w0*w2 - 96*cx2*tcutxp*w1*w2 + 48*cx2*tcutxp*w2*w3 - 12*cx2*tcutxp*w2*w4 - 48*cx3*tcutxp*w0*w3 + 96*cx3*tcutxp*w1*w3 - 48*cx3*tcutxp*w2*w3 + 12*cx4*tcutxp*w0*w4 - 24*cx4*tcutxp*w1*w4 + 12*cx4*tcutxp*w2*w4 + 24*cy0*tcutyp*w0*w1 - 60*cy0*tcutyp*w0*w2 + 48*cy0*tcutyp*w0*w3 - 12*cy0*tcutyp*w0*w4 - 24*cy1*tcutyp*w0*w1 + 96*cy1*tcutyp*w1*w2 - 96*cy1*tcutyp*w1*w3 + 24*cy1*tcutyp*w1*w4 + 60*cy2*tcutyp*w0*w2 - 96*cy2*tcutyp*w1*w2 + 48*cy2*tcutyp*w2*w3 - 12*cy2*tcutyp*w2*w4 - 48*cy3*tcutyp*w0*w3 + 96*cy3*tcutyp*w1*w3 - 48*cy3*tcutyp*w2*w3 + 12*cy4*tcutyp*w0*w4 - 24*cy4*tcutyp*w1*w4 + 12*cy4*tcutyp*w2*w4,
    -4*cx0*tcutxp*w0*w1 + 12*cx0*tcutxp*w0*w2 - 12*cx0*tcutxp*w0*w3 + 4*cx0*tcutxp*w0*w4 + 4*cx1*tcutxp*w0*w1 - 24*cx1*tcutxp*w1*w2 + 32*cx1*tcutxp*w1*w3 - 12*cx1*tcutxp*w1*w4 - 12*cx2*tcutxp*w0*w2 + 24*cx2*tcutxp*w1*w2 - 24*cx2*tcutxp*w2*w3 + 12*cx2*tcutxp*w2*w4 + 12*cx3*tcutxp*w0*w3 - 32*cx3*tcutxp*w1*w3 + 24*cx3*tcutxp*w2*w3 - 4*cx3*tcutxp*w3*w4 - 4*cx4*tcutxp*w0*w4 + 12*cx4*tcutxp*w1*w4 - 12*cx4*tcutxp*w2*w4 + 4*cx4*tcutxp*w3*w4 - 4*cy0*tcutyp*w0*w1 + 12*cy0*tcutyp*w0*w2 - 12*cy0*tcutyp*w0*w3 + 4*cy0*tcutyp*w0*w4 + 4*cy1*tcutyp*w0*w1 - 24*cy1*tcutyp*w1*w2 + 32*cy1*tcutyp*w1*w3 - 12*cy1*tcutyp*w1*w4 - 12*cy2*tcutyp*w0*w2 + 24*cy2*tcutyp*w1*w2 - 24*cy2*tcutyp*w2*w3 + 12*cy2*tcutyp*w2*w4 + 12*cy3*tcutyp*w0*w3 - 32*cy3*tcutyp*w1*w3 + 24*cy3*tcutyp*w2*w3 - 4*cy3*tcutyp*w3*w4 - 4*cy4*tcutyp*w0*w4 + 12*cy4*tcutyp*w1*w4 - 12*cy4*tcutyp*w2*w4 + 4*cy4*tcutyp*w3*w4
        },
        result, t0, t1, tol);
    } else{
        throw not_implemented_error(
            "Inflection computation only works on RationalBezier curve with degree lower than 4");
    }

    return result;
}



}

