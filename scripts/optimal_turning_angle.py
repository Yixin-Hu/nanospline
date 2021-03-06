#!/usr/bin/env python
# coding=utf-8
import utils
import os
from sympy import *
import numpy as np
from sympy.printing.ccode import C99CodePrinter


code_template_heder = """
// This code is automatically generated by scripts/optimal_turning_angle.py

#pragma once
#include <cassert>
#include <vector>

#include <nanospline/Exceptions.h>
#include <nanospline/PolynomialRootFinder.h>
#include <nanospline/Bezier.h>
#include <nanospline/RationalBezier.h>

namespace nanospline {

"""

code_template = """
template<typename Scalar, int _degree=3, bool generic=_degree<0 >
std::vector<Scalar> optimal_points_to_reduce_turning_angle(
        const {type}<Scalar, 2, _degree, generic>& curve, bool flip,
        Scalar t0 = 0, Scalar t1 = 1) {{
    std::vector<Scalar> result;
    constexpr Scalar tol = 1e-8;

    auto tan0 = curve.evaluate_derivative(t0);
    auto tan1 = curve.evaluate_derivative(t1);

    if (tan0.norm() < tol || tan1.norm() < tol){{
        std::vector<Scalar> res;
        res.push_back((t0 + t1) / 2);
        return res;
    }}

    tan0 = tan0 / tan0.norm();
    tan1 = tan1 / tan1.norm();

    if (flip) {{
        tan0 = tan0 * (-1);
        tan1 = tan1 * (-1);
    }}

    const Scalar tan0x = tan0[0];
    const Scalar tan0y = tan0[1];

    const Scalar tan1x = tan1[0];
    const Scalar tan1y = tan1[1];


    const Scalar tcutxp = -(tan0y + tan1y)/2;
    const Scalar tcutyp = (tan0x + tan1x)/2;

    if (tcutxp < tol && tcutyp < tol){{
        std::vector<Scalar> res;
        res.push_back((t0 + t1) / 2);
        return res;
    }}

{body}

    return result;
}}
"""

code_template_footer = """
}

"""

if __name__ == "__main__":
    functions = utils.setup_functions()
    t = symbols('t')
    tcutxp = symbols('tcutxp')
    tcutyp = symbols('tcutyp')

    printer = C99CodePrinter()
    code = code_template_heder

    for poly_name in functions:
        lines = []
        first=True
        for n_coeffs, degree, is_rational, curve in functions[poly_name]:
            syms = utils.create_coeff_symbols(n_coeffs)
            func = curve(t, syms)

            tx = diff(func[0], t)
            ty = diff(func[1], t)

            eq = together(tx*tcutxp+ty*tcutyp)
            n, _ = fraction(eq)

            poly = Poly(n, t)
            coeffs = poly.all_coeffs()
            coeffs.reverse()

            lines.append("{}if (curve.get_degree() == {}) {{".format(
                "" if first else "} else ", degree))
            first = False

            solver_lines = utils.generate_solver_code(n_coeffs, coeffs, is_rational, poly, printer)
            for l in solver_lines:
                lines.append("    " + l)

        lines.append("} else{")
        lines.append("    throw not_implemented_error(")
        lines.append("        \"Inflection computation only works on {} curve with degree lower than {}\");".format(poly_name, degree))
        lines.append("}")

        body = "\n".join(["    {}".format(l) for l in lines])
        code += code_template.format(type=poly_name, body=body) + "\n\n"

    code += code_template_footer
    dir_path = os.path.dirname(os.path.realpath(__file__))
    with open(os.path.join(dir_path, "..", "include", "nanospline", "auto_optimal_turning_angle.h"), "w") as f:
        f.write(code)
