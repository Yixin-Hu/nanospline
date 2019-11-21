#include <catch2/catch.hpp>

#include <cmath>
#include <iostream>
#include <nanospline/NURBS.h>

TEST_CASE("NURBS", "[nurbs]") {
    using namespace nanospline;

    SECTION("Generic degree 0") {
        Eigen::Matrix<float, 3, 2> control_pts;
        control_pts << 0.0, 0.0,
                       1.0, 0.0,
                       2.0, 0.0;
        Eigen::Matrix<float, 4, 1> knots;
        knots << 0.0, 0.5, 0.75, 1.0;

        Eigen::Matrix<float, 3, 1> weights;
        weights << 1.0, 2.0, 3.0;

        NURBS<float, 2, 0, true> curve;
        curve.set_control_points(control_pts);
        curve.set_knots(knots);
        curve.set_weights(weights);
        curve.initialize();

        REQUIRE(curve.get_degree() == 0);

        auto p0 = curve.evaluate(0.1);
        REQUIRE(p0[0] == Approx(0.0));
        REQUIRE(p0[1] == Approx(0.0));

        auto p1 = curve.evaluate(0.6);
        REQUIRE(p1[0] == Approx(1.0));
        REQUIRE(p1[1] == Approx(0.0));

        auto p2 = curve.evaluate(1.0);
        REQUIRE(p2[0] == Approx(2.0));
        REQUIRE(p2[1] == Approx(0.0));
    }

    SECTION("Circles") {
        SECTION("3-way split") {
            constexpr float R = 1.1;
            Eigen::Matrix<float, 1, 2> c(0.0, R);
            Eigen::Matrix<float, 7, 2> control_pts;
            control_pts << 0.0, 0.0,
                           sqrt(3)*R, 0.0,
                           0.5*sqrt(3)*R, 1.5*R,
                           0.0, 3*R,
                          -0.5*sqrt(3)*R, 1.5*R,
                          -sqrt(3)*R, 0.0,
                           0.0, 0.0;
            Eigen::Matrix<float, 10, 1> knots;
            knots << 0.0, 0.0, 0.0,
                     1.0/3.0, 1.0/3.0,
                     2.0/3.0, 2.0/3.0,
                     1.0, 1.0, 1.0;

            Eigen::Matrix<float, 7, 1> weights;
            weights << 1.0, 0.5, 1.0, 0.5, 1.0, 0.5, 1.0;

            NURBS<float, 2, 2, true> curve;
            curve.set_control_points(control_pts);
            curve.set_knots(knots);
            curve.set_weights(weights);
            curve.initialize();

            REQUIRE(curve.get_degree() == 2);

            for (float t=0.0; t<1.01; t+=0.2) {
                const auto p = curve.evaluate(t);
                REQUIRE((p-c).norm() == Approx(R));
            }
        }

        SECTION("4-way split") {
            constexpr float R = 12.1;
            Eigen::Matrix<float, 1, 2> c(0.0, R);
            Eigen::Matrix<float, 9, 2> control_pts;
            control_pts << 0.0, 0.0,
                           R, 0.0,
                           R, R,
                           R, 2*R,
                           0.0, 2*R,
                           -R, 2*R,
                           -R, R,
                           -R, 0.0,
                           0.0, 0.0;
            Eigen::Matrix<float, 12, 1> knots;
            knots << 0.0, 0.0, 0.0,
                     0.25, 0.25,
                     0.5, 0.5,
                     0.75, 0.75,
                     1.0, 1.0, 1.0;
            Eigen::Matrix<float, 9, 1> weights;
            weights << 1.0, sqrt(2)/2,
                       1.0, sqrt(2)/2,
                       1.0, sqrt(2)/2,
                       1.0, sqrt(2)/2,
                       1.0;

            NURBS<float, 2, 2, true> curve;
            curve.set_control_points(control_pts);
            curve.set_knots(knots);
            curve.set_weights(weights);
            curve.initialize();

            REQUIRE(curve.get_degree() == 2);

            for (float t=0.0; t<1.01; t+=0.2) {
                const auto p = curve.evaluate(t);
                REQUIRE((p-c).norm() == Approx(R));
            }
        }
    }
}