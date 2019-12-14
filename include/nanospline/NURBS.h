#pragma once

#include <Eigen/Core>
#include <iostream>

#include <nanospline/Exceptions.h>
#include <nanospline/BSplineBase.h>
#include <nanospline/BSpline.h>

namespace nanospline {

template<typename _Scalar, int _dim=2, int _degree=3, bool _generic=_degree<0 >
class NURBS : public BSplineBase<NURBS<_Scalar, _dim, _degree, _generic> > {
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        using Base = BSplineBase<NURBS<_Scalar, _dim, _degree, _generic> >;
        using Scalar = typename Base::Scalar;
        using Point = typename Base::Point;
        using ControlPoints = typename Base::ControlPoints;
        using WeightVector = Eigen::Matrix<_Scalar, _generic?Eigen::Dynamic:_degree+1, 1>;
        using BSplineHomogeneous = BSpline<_Scalar, _dim+1, _degree, _generic>;

    public:
        Point evaluate(Scalar t) const override {
            validate_initialization();
            auto p = m_bspline_homogeneous.evaluate(t);
            return p.template segment<_dim>(0) / p[_dim];
        }

        Scalar inverse_evaluate(const Point& p) const override {
            throw not_implemented_error("Too complex, sigh");
        }

        Point evaluate_derivative(Scalar t) const override {
            validate_initialization();
            const auto p = m_bspline_homogeneous.evaluate(t);
            const auto d =
                m_bspline_homogeneous.evaluate_derivative(t);

            return (d.template head<_dim>() -
                    p.template head<_dim>() * d[_dim] / p[_dim])
                / p[_dim];
        }

        Point evaluate_2nd_derivative(Scalar t) const override {
            const auto p0 = m_bspline_homogeneous.evaluate(t);
            const auto d1 =
                m_bspline_homogeneous.evaluate_derivative(t);
            const auto d2 =
                m_bspline_homogeneous.evaluate_2nd_derivative(t);

            const auto c0 = p0.template head<_dim>() / p0[_dim];
            const auto c1 = (d1.template head<_dim>() -
                    p0.template head<_dim>() * d1[_dim] / p0[_dim]) / p0[_dim];

            return (d2.template head<_dim>()
                    - d2[_dim] * c0 - 2 * d1[_dim] * c1) / p0[_dim];
        }

        void insert_knot(Scalar t, int multiplicity=1) override {
            validate_initialization();
            m_bspline_homogeneous.insert_knot(t, multiplicity);

            // Extract control points, weights and knots;
            const auto ctrl_pts = m_bspline_homogeneous.get_control_points();
            m_weights = ctrl_pts.col(_dim);
            Base::m_control_points = ctrl_pts.leftCols(_dim).array().colwise() / m_weights.array();
            Base::m_knots = m_bspline_homogeneous.get_knots();
        }

    public:
        void initialize() {
            typename BSplineHomogeneous::ControlPoints ctrl_pts(
                    Base::m_control_points.rows(), _dim+1);
            ctrl_pts.template leftCols<_dim>() =
                Base::m_control_points.array().colwise() * m_weights.array();
            ctrl_pts.template rightCols<1>() = m_weights;

            m_bspline_homogeneous.set_control_points(std::move(ctrl_pts));
            m_bspline_homogeneous.set_knots(Base::m_knots);
        }

        const WeightVector& get_weights() const {
            return m_weights;
        }

        template<typename Derived>
        void set_weights(const Eigen::PlainObjectBase<Derived>& weights) {
            m_weights = weights;
        }

        template<typename Derived>
        void set_weights(const Eigen::PlainObjectBase<Derived>&& weights) {
            m_weights.swap(weights);
        }

        const BSplineHomogeneous& get_homogeneous() const {
            return m_bspline_homogeneous;
        }

        void set_homogeneous(const BSplineHomogeneous& homogeneous) {
            const auto ctrl_pts = homogeneous.get_control_points();
            m_bspline_homogeneous = homogeneous;
            m_weights = ctrl_pts.template rightCols<1>();
            Base::m_control_points =
                ctrl_pts.template leftCols<_dim>().array().colwise()
                / m_weights.array();
            Base::m_knots = homogeneous.get_knots();
            validate_initialization();
        }

        virtual void write(std::ostream &out) const override {
            out << "c:\n" << this->m_control_points << "\n";
            out << "k:\n" << this->m_knots << "\n";
            out << "w:\n" << m_weights << "\n";
        }

    private:
        void validate_initialization() const {
            Base::validate_curve();
            const auto& ctrl_pts = m_bspline_homogeneous.get_control_points();
            if (ctrl_pts.rows() != Base::m_control_points.rows() ||
                ctrl_pts.rows() != m_weights.rows() ) {
                throw invalid_setting_error("NURBS curve is not initialized.");
            }
        }

    private:
        BSplineHomogeneous m_bspline_homogeneous;
        WeightVector m_weights;
};

}
