#pragma once

#include <algorithm>

#include <Eigen/Core>
#include <nanospline/Exceptions.h>
#include <nanospline/BezierBase.h>

namespace nanospline {

template<typename _Scalar, int _dim=2, int _degree=3, bool _generic=_degree<0 >
class Bezier : public BezierBase<Bezier<_Scalar, _dim, _degree, _generic> > {
    public:
        using Base = BezierBase<Bezier<_Scalar, _dim, _degree, _generic> >;
        using Scalar = typename Base::Scalar;
        using Point = typename Base::Point;
        using ControlPoints = typename Base::ControlPoints;

    public:
        Point evaluate(Scalar t) const override {
            const auto control_pts = deBoor(t, Base::get_degree());
            return control_pts.row(0);
        }

        Scalar inverse_evaluate(const Point& p) const override {
            throw not_implemented_error("Too complex, sigh");
        }

        Point evaluate_derivative(Scalar t) const override {
            const auto degree = Base::get_degree();
            assert(degree >= 0);
            if (degree == 0) {
                return Point::Zero();
            } else {
                const auto control_pts = deBoor(t, degree-1);
                return (control_pts.row(1) - control_pts.row(0))*degree;
            }
        }

        Point evaluate_2nd_derivative(Scalar t) const override {
            const auto degree = Base::get_degree();
            assert(degree >= 0);
            if (degree <= 1) {
                return Point::Zero();
            } else {
                const auto control_pts = deBoor(t, degree-2);
                return (control_pts.row(2) + control_pts.row(0) - 2 * control_pts.row(1))
                    * degree * (degree-1);
            }
        }

    private:
        ControlPoints deBoor(Scalar t, int num_recurrsions) const {
            const auto degree = Base::get_degree();
            if (num_recurrsions < 0 || num_recurrsions > degree) {
                throw invalid_setting_error(
                        "Number of de Boor recurrsion cannot exceeds degree");
            }

            if (num_recurrsions == 0) {
                return Base::m_control_points;
            } else {
                ControlPoints ctrl_pts = deBoor(t, num_recurrsions-1);
                assert(ctrl_pts.rows() >= degree+1-num_recurrsions);
                for (int i=0; i<degree+1-num_recurrsions; i++) {
                    ctrl_pts.row(i) = (1.0-t) * ctrl_pts.row(i) + t * ctrl_pts.row(i+1);
                }
                return ctrl_pts;
            }
        }
};

template<typename _Scalar, int _dim>
class Bezier<_Scalar, _dim, 0, false> : public BezierBase<Bezier<_Scalar, _dim, 0, false> > {
    public:
        using Base = BezierBase<Bezier<_Scalar, _dim, 0, false> >;
        using Scalar = typename Base::Scalar;
        using Point = typename Base::Point;
        using ControlPoints = typename Base::ControlPoints;

    public:
        Point evaluate(Scalar t) const override {
            return Base::m_control_points;
        }

        Scalar inverse_evaluate(const Point& p) const override {
            return 0.0;
        }

        Point evaluate_derivative(Scalar t) const override {
            return Point::Zero();
        }

        Point evaluate_2nd_derivative(Scalar t) const override {
            return Point::Zero();
        }
};

template<typename _Scalar, int _dim>
class Bezier<_Scalar, _dim, 1, false> : public BezierBase<Bezier<_Scalar, _dim, 1, false> > {
    public:
        using Base = BezierBase<Bezier<_Scalar, _dim, 1, false> >;
        using Scalar = typename Base::Scalar;
        using Point = typename Base::Point;
        using ControlPoints = typename Base::ControlPoints;

    public:
        Point evaluate(Scalar t) const override {
            return (1.0-t) * Base::m_control_points.row(0) +
                t * Base::m_control_points.row(1);
        }

        Scalar inverse_evaluate(const Point& p) const override {
            Point e = Base::m_control_points.row(1) - Base::m_control_points.row(0);
            Scalar t = (p - Base::m_control_points.row(0)).dot(e) / e.squaredNorm();
            return std::max<Scalar>(std::min<Scalar>(t, 1.0), 0.0);
        }

        Point evaluate_derivative(Scalar t) const override {
            return Base::m_control_points.row(1) - Base::m_control_points.row(0);
        }

        Point evaluate_2nd_derivative(Scalar t) const override {
            return Point::Zero();
        }
};

template<typename _Scalar, int _dim>
class Bezier<_Scalar, _dim, 2, false> : public BezierBase<Bezier<_Scalar, _dim, 2, false> > {
    public:
        using Base = BezierBase<Bezier<_Scalar, _dim, 2, false> >;
        using Scalar = typename Base::Scalar;
        using Point = typename Base::Point;
        using ControlPoints = typename Base::ControlPoints;

    public:
        Point evaluate(Scalar t) const override {
            const Point p0 = (1.0-t) * Base::m_control_points.row(0) +
                t * Base::m_control_points.row(1);
            const Point p1 = (1.0-t) * Base::m_control_points.row(1) +
                t * Base::m_control_points.row(2);
            return (1.0-t) * p0 + t * p1;
        }

        Scalar inverse_evaluate(const Point& p) const override {
            throw not_implemented_error("Too complex, sigh");
        }

        Point evaluate_derivative(Scalar t) const override {
            const Point p0 = (1.0-t) * Base::m_control_points.row(0) +
                t * Base::m_control_points.row(1);
            const Point p1 = (1.0-t) * Base::m_control_points.row(1) +
                t * Base::m_control_points.row(2);
            return (p1-p0) * 2;
        }

        Point evaluate_2nd_derivative(Scalar t) const override {
            const auto& ctrl_pts = Base::m_control_points;
            return 2 * (ctrl_pts.row(0) + ctrl_pts.row(2) - 2 * ctrl_pts.row(1));
        }
};

template<typename _Scalar, int _dim>
class Bezier<_Scalar, _dim, 3, false> : public BezierBase<Bezier<_Scalar, _dim, 3, false> > {
    public:
        using Base = BezierBase<Bezier<_Scalar, _dim, 3, false> >;
        using Scalar = typename Base::Scalar;
        using Point = typename Base::Point;
        using ControlPoints = typename Base::ControlPoints;

    public:
        Point evaluate(Scalar t) const override {
            const Point q0 = (1.0-t) * Base::m_control_points.row(0) +
                t * Base::m_control_points.row(1);
            const Point q1 = (1.0-t) * Base::m_control_points.row(1) +
                t * Base::m_control_points.row(2);
            const Point q2 = (1.0-t) * Base::m_control_points.row(2) +
                t * Base::m_control_points.row(3);

            const Point p0 = (1.0-t) * q0 + t * q1;
            const Point p1 = (1.0-t) * q1 + t * q2;
            return (1.0-t) * p0 + t * p1;
        }

        Scalar inverse_evaluate(const Point& p) const override {
            throw not_implemented_error("Too complex, sigh");
        }

        Point evaluate_derivative(Scalar t) const override {
            const Point q0 = (1.0-t) * Base::m_control_points.row(0) +
                t * Base::m_control_points.row(1);
            const Point q1 = (1.0-t) * Base::m_control_points.row(1) +
                t * Base::m_control_points.row(2);
            const Point q2 = (1.0-t) * Base::m_control_points.row(2) +
                t * Base::m_control_points.row(3);

            const Point p0 = (1.0-t) * q0 + t * q1;
            const Point p1 = (1.0-t) * q1 + t * q2;

            return (p1-p0)*3;
        }

        Point evaluate_2nd_derivative(Scalar t) const override {
            const Point q0 = (1.0-t) * Base::m_control_points.row(0) +
                t * Base::m_control_points.row(1);
            const Point q1 = (1.0-t) * Base::m_control_points.row(1) +
                t * Base::m_control_points.row(2);
            const Point q2 = (1.0-t) * Base::m_control_points.row(2) +
                t * Base::m_control_points.row(3);
            return 6 * (q0+q2-2*q1);
        }
};


}
