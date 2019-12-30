#!/usr/bin/env python
# coding=utf-8
import utils
import os
from sympy import symbols, diff, together, fraction, Poly
from scipy.special import comb
import numpy as np
from sympy.printing.ccode import C99CodePrinter


code_template_heder = """/**
 * This code is automatically generated by scripts/inflection.py
 */

#pragma once
#include <cassert>
#include <vector>

#include <nanospline/Exceptions.h>
#include <nanospline/PolynomialRootFinder.h>
#include <nanospline/BezierBase.h>

namespace nanospline {
namespace internal {

"""

code_template = """
template<typename Derived>
std::vector<typename Derived::Scalar> compute_{type}_inflections(
        const Eigen::PlainObjectBase<Derived>& ctrl_pts,
        typename Derived::Scalar t0 = 0,
        typename Derived::Scalar t1 = 1) {{
    switch(ctrl_pts.rows()-1) {{
{body}
    }}
}}
"""

code_rational_template = """
template<typename Derived, typename Derived2>
std::vector<typename Derived::Scalar> compute_{type}_inflections(
        const Eigen::PlainObjectBase<Derived>& ctrl_pts,
        const Eigen::PlainObjectBase<Derived2>& weights,
        typename Derived::Scalar t0 = 0,
        typename Derived::Scalar t1 = 1) {{
    switch(ctrl_pts.rows()-1) {{
{body}
    }}
}}
"""

specialization_template = """
template<typename Derived>
std::vector<typename Derived::Scalar> compute_{type}_degree_{degree}_inflections(
        const Eigen::PlainObjectBase<Derived>& ctrl_pts,
        typename Derived::Scalar t0 = 0,
        typename Derived::Scalar t1 = 1) {{
    using Scalar = typename Derived::Scalar;
    std::vector<Scalar> result;
    constexpr Scalar tol = 1e-8;

{body}

    return result;
}}

"""

specialization_rational_template = """
template<typename Derived, typename Derived2>
std::vector<typename Derived::Scalar> compute_{type}_degree_{degree}_inflections(
        const Eigen::PlainObjectBase<Derived>& ctrl_pts,
        const Eigen::PlainObjectBase<Derived2>& weights,
        typename Derived::Scalar t0 = 0,
        typename Derived::Scalar t1 = 1) {{
    using Scalar = typename Derived::Scalar;
    std::vector<Scalar> result;
    constexpr Scalar tol = 1e-8;

{body}

    return result;
}}

"""

code_template_footer = """
} // End internal namespace
} // End nanospline namespace

"""



if __name__ == "__main__":
    functions = utils.setup_functions()
    t = symbols('t')

    printer = C99CodePrinter()

    for poly_name in functions:
        code = code_template_heder
        specialized_code = "";
        lines = []
        first=True
        for n_coeffs, degree, is_rational, curve in functions[poly_name]:
            syms = utils.create_coeff_symbols(n_coeffs)
            func = curve(t, syms)

            tx = (diff(func[0], t))
            ty = (diff(func[1], t))

            nx = -(diff(func[1], t, 2))
            ny = (diff(func[0], t, 2))

            eq = together(tx*nx+ty*ny)
            n, _ = fraction(eq)

            poly = Poly(n, t)
            coeffs = poly.all_coeffs()
            coeffs.reverse()

            solver_lines = utils.generate_solver_code(n_coeffs, coeffs, is_rational, poly, printer)

            if degree >= 5:
                lines.append("#ifdef HIGH_DEGREE_SUPPORT");
            lines.append("case {}:".format(degree));
            if is_rational:
                lines.append("    return compute_{}_degree_{}_inflections(ctrl_pts, weights, t0, t1);".format(
                        poly_name, degree));
            else:
                lines.append("    return compute_{}_degree_{}_inflections(ctrl_pts, t0, t1);".format(
                        poly_name, degree));
            if degree >= 5:
                lines.append("#endif // HIGH_DEGREE_SUPPORT");

            if is_rational:
                specialized_code += specialization_rational_template.format(
                        type=poly_name, body="\n".join(utils.indent(solver_lines)), degree=degree);
            else:
                specialized_code += specialization_template.format(
                        type=poly_name, body="\n".join(utils.indent(solver_lines)), degree=degree);

        lines.append("default:")
        lines.append("    throw not_implemented_error(")
        lines.append("        \"Inflection computation only works on {} curve with degree lower than {}\");".format(poly_name, degree))

        body = "\n".join(utils.indent(utils.indent(lines)))
        code += specialized_code;
        if poly_name == "Bezier":
            code += code_template.format(type=poly_name, body=body) + "\n\n"
        else:
            code += code_rational_template.format(type=poly_name, body=body) + "\n\n"

        code += code_template_footer
        dir_path = os.path.dirname(os.path.realpath(__file__))
        with open(os.path.join(dir_path, "..", "include", "nanospline",
            "internal", "auto_inflection_{}.h".format(poly_name)), "w") as f:
            f.write(code)

