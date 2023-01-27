/*
 * Copyright (c) 2001-2012 Python Software Foundation. All Rights Reserved.
 * Modified and extended by Stefan Krah.
 */


#ifndef DOCSTRINGS_H
#define DOCSTRINGS_H


#include "pymacro.h"


/******************************************************************************/
/*                                Module                                      */
/******************************************************************************/


PyDoc_STRVAR(doc__decimal,
"C decimal arithmetic module");

PyDoc_STRVAR(doc_getcontext,
"getcontext($module, /)\n--\n\n\
Get the current default context.\n\
\n");

PyDoc_STRVAR(doc_setcontext,
"setcontext($module, context, /)\n--\n\n\
Set a new default context.\n\
\n");

PyDoc_STRVAR(doc_localcontext,
"localcontext($module, /, ctx=None, **kwargs)\n--\n\n\
Return a context manager that will set the default context to a copy of ctx\n\
on entry to the with-statement and restore the previous default context when\n\
exiting the with-statement. If no context is specified, a copy of the current\n\
default context is used.\n\
\n");

#ifdef EXTRA_FUNCTIONALITY
PyDoc_STRVAR(doc_ieee_context,
"IEEEContext($module, bits, /)\n--\n\n\
Return a context object initialized to the proper values for one of the\n\
IEEE interchange formats.  The argument must be a multiple of 32 and less\n\
than IEEE_CONTEXT_MAX_BITS.  For the most common values, the constants\n\
DECIMAL32, DECIMAL64 and DECIMAL128 are provided.\n\
\n");
#endif


/******************************************************************************/
/*                       Decimal Object and Methods                           */
/******************************************************************************/

PyDoc_STRVAR(doc_decimal,
"Decimal(value=\"0\", context=None)\n--\n\n\
Construct a new Decimal object. 'value' can be an integer, string, tuple,\n\
or another Decimal object. If no value is given, return Decimal('0'). The\n\
context does not affect the conversion and is only passed to determine if\n\
the InvalidOperation trap is active.\n\
\n");

PyDoc_STRVAR(doc_adjusted,
"adjusted($self, /)\n--\n\n\
Return the adjusted exponent of the number.\n\
Defined as exp + digits - 1.\n\
\n");

PyDoc_STRVAR(doc_as_tuple,
"as_tuple($self, /)\n--\n\n\
Represents the number as a triple tuple.\n\
\n\
To show the internals exactly as they are.\n\
\n");

PyDoc_STRVAR(doc_as_integer_ratio,
"as_integer_ratio($self, /)\n--\n\n\
Express a finite Decimal instance in the form n / d.\n\
\n\
Return a pair (n, d) of integers, whose ratio is exactly equal to the original\n\
Decimal and with a positive denominator. The ratio is in lowest terms.\n\
Raise OverflowError on infinities and a ValueError on NaNs.\n\
\n\
    >>> Decimal('3.14').as_integer_ratio()\n\
    (157, 50)\n\
    >>> Decimal('-123e5').as_integer_ratio()\n\
    (-12300000, 1)\n\
    >>> Decimal('0.00').as_integer_ratio()\n\
    (0, 1)\n\
\n\
\n");

PyDoc_STRVAR(doc_canonical,
"canonical($self, /)\n--\n\n\
Return the canonical encoding of the argument.  Currently, the encoding\n\
of a Decimal instance is always canonical, so this operation returns its\n\
argument unchanged.\n\
\n");

PyDoc_STRVAR(doc_compare,
"compare($self, /, other, context=None)\n--\n\n\
Compare values numerically.\n\
\n\
If the signs of the operands differ, a value representing each operand\n\
('-1' if the operand is less than zero, '0' if the operand is zero or\n\
negative zero, or '1' if the operand is greater than zero) is used in\n\
place of that operand for the comparison instead of the actual\n\
operand.\n\
\n\
The comparison is then effected by subtracting the second operand from\n\
the first and then returning a value according to the result of the\n\
subtraction: '-1' if the result is less than zero, '0' if the result is\n\
zero or negative zero, or '1' if the result is greater than zero.\n\
\n\
        a or b is a NaN ==> Decimal('NaN')\n\
        a < b           ==> Decimal('-1')\n\
        a == b          ==> Decimal('0')\n\
        a > b           ==> Decimal('1')\n\
\n\
    >>> ExtendedContext.compare(Decimal('2.1'), Decimal('3'))\n\
    Decimal('-1')\n\
    >>> ExtendedContext.compare(Decimal('2.1'), Decimal('2.1'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.compare(Decimal('2.1'), Decimal('2.10'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.compare(Decimal('3'), Decimal('2.1'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.compare(Decimal('2.1'), Decimal('-3'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.compare(Decimal('-3'), Decimal('2.1'))\n\
    Decimal('-1')\n\
    >>> ExtendedContext.compare(1, 2)\n\
    Decimal('-1')\n\
    >>> ExtendedContext.compare(Decimal(1), 2)\n\
    Decimal('-1')\n\
    >>> ExtendedContext.compare(1, Decimal(2))\n\
    Decimal('-1')\n\
    >>> ExtendedContext.compare(Decimal('2'), Decimal('NaN'))\n\
    Decimal('NaN')\n\
\n");

PyDoc_STRVAR(doc_compare_signal,
"compare_signal($self, /, other, context=None)\n--\n\n\
Compares the values of the two operands numerically.\n\
\n\
It's pretty much like compare(), but all NaNs signal, with signaling\n\
NaNs taking precedence over quiet NaNs.\n\
\n\
    >>> c = ExtendedContext\n\
    >>> c.compare_signal(Decimal('2.1'), Decimal('3'))\n\
    Decimal('-1')\n\
    >>> c.compare_signal(Decimal('2.1'), Decimal('2.1'))\n\
    Decimal('0')\n\
    >>> c.flags[InvalidOperation] = 0\n\
    >>> print(c.flags[InvalidOperation])\n\
    0\n\
    >>> c.compare_signal(Decimal('NaN'), Decimal('2.1'))\n\
    Decimal('NaN')\n\
    >>> print(c.flags[InvalidOperation])\n\
    1\n\
    >>> c.flags[InvalidOperation] = 0\n\
    >>> print(c.flags[InvalidOperation])\n\
    0\n\
    >>> c.compare_signal(Decimal('sNaN'), Decimal('2.1'))\n\
    Decimal('NaN')\n\
    >>> print(c.flags[InvalidOperation])\n\
    1\n\
    >>> c.compare_signal(-1, 2)\n\
    Decimal('-1')\n\
    >>> c.compare_signal(Decimal(-1), 2)\n\
    Decimal('-1')\n\
    >>> c.compare_signal(-1, Decimal(2))\n\
    Decimal('-1')\n\
\n");

PyDoc_STRVAR(doc_compare_total,
"compare_total($self, /, other, context=None)\n--\n\n\
Compare two operands using their abstract representation rather than\n\
their numerical value.  Similar to the compare() method, but the result\n\
gives a total ordering on Decimal instances.  Two Decimal instances with\n\
the same numeric value but different representations compare unequal\n\
in this ordering:\n\
\n\
    >>> Decimal('12.0').compare_total(Decimal('12'))\n\
    Decimal('-1')\n\
\n\
Quiet and signaling NaNs are also included in the total ordering. The result\n\
of this function is Decimal('0') if both operands have the same representation,\n\
Decimal('-1') if the first operand is lower in the total order than the second,\n\
and Decimal('1') if the first operand is higher in the total order than the\n\
second operand. See the specification for details of the total order.\n\
\n\
This operation is unaffected by context and is quiet: no flags are changed\n\
and no rounding is performed. As an exception, the C version may raise\n\
InvalidOperation if the second operand cannot be converted exactly.\n\
\n");

PyDoc_STRVAR(doc_compare_total_mag,
"compare_total_mag($self, /, other, context=None)\n--\n\n\
Compare two operands using their abstract representation rather than their\n\
value as in compare_total(), but ignoring the sign of each operand.Like\n\
compare_total, but with operand's sign ignored and assumed to be 0.\n\
\n\
x.compare_total_mag(y) is equivalent to x.copy_abs().compare_total(y.copy_abs()).\n\
\n\
This operation is unaffected by context and is quiet: no flags are changed\n\
and no rounding is performed. As an exception, the C version may raise\n\
InvalidOperation if the second operand cannot be converted exactly.\n\
\n");

PyDoc_STRVAR(doc_conjugate,
"conjugate($self, /)\n--\n\n\
Return self.\n\
\n");

PyDoc_STRVAR(doc_copy_abs,
"copy_abs($self, /)\n--\n\n\
Return the absolute value of the argument. This operation is unaffected by\n\
context and is quiet: no flags are changed and no rounding is performed.\n\
\n\
    >>> ExtendedContext.copy_abs(Decimal('2.1'))\n\
    Decimal('2.1')\n\
    >>> ExtendedContext.copy_abs(Decimal('-100'))\n\
    Decimal('100')\n\
    >>> ExtendedContext.copy_abs(-1)\n\
    Decimal('1')\n\
\n");

PyDoc_STRVAR(doc_copy_negate,
"copy_negate($self, /)\n--\n\n\
Return the negation of the argument.  This operation is unaffected by context\n\
and is quiet: no flags are changed and no rounding is performed.\n\
\n");

PyDoc_STRVAR(doc_copy_sign,
"copy_sign($self, /, other, context=None)\n--\n\n\
Copies the second operand's sign to the first one.\n\
In detail, it returns a copy of the first operand with the sign\n\
equal to the sign of the second operand.\n\
\n\
    >>> ExtendedContext.copy_sign(Decimal( '1.50'), Decimal('7.33'))\n\
    Decimal('1.50')\n\
    >>> ExtendedContext.copy_sign(Decimal('-1.50'), Decimal('7.33'))\n\
    Decimal('1.50')\n\
    >>> ExtendedContext.copy_sign(Decimal( '1.50'), Decimal('-7.33'))\n\
    Decimal('-1.50')\n\
    >>> ExtendedContext.copy_sign(Decimal('-1.50'), Decimal('-7.33'))\n\
    Decimal('-1.50')\n\
    >>> ExtendedContext.copy_sign(1, -2)\n\
    Decimal('-1')\n\
    >>> ExtendedContext.copy_sign(Decimal(1), -2)\n\
    Decimal('-1')\n\
    >>> ExtendedContext.copy_sign(1, Decimal(-2))\n\
    Decimal('-1')\n\
\n\
This operation is unaffected by context and is quiet: no flags are changed\n\
and no rounding is performed. As an exception, the C version may raise\n\
InvalidOperation if the second operand cannot be converted exactly.\n\
\n");

PyDoc_STRVAR(doc_exp,
"exp($self, /, context=None)\n--\n\n\
Return the value of the (natural) exponential function e**a at the given\n\
number.  The function always uses the ROUND_HALF_EVEN mode and the result\n\
is correctly rounded.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> c.exp(Decimal('-Infinity'))\n\
    Decimal('0')\n\
    >>> c.exp(Decimal('-1'))\n\
    Decimal('0.367879441')\n\
    >>> c.exp(Decimal('0'))\n\
    Decimal('1')\n\
    >>> c.exp(Decimal('1'))\n\
    Decimal('2.71828183')\n\
    >>> c.exp(Decimal('0.693147181'))\n\
    Decimal('2.00000000')\n\
    >>> c.exp(Decimal('+Infinity'))\n\
    Decimal('Infinity')\n\
    >>> c.exp(10)\n\
    Decimal('22026.4658')\n\
\n");

PyDoc_STRVAR(doc_from_float,
"from_float($type, f, /)\n--\n\n\
Class method that converts a float to a decimal number, exactly.\n\
Since 0.1 is not exactly representable in binary floating point,\n\
Decimal.from_float(0.1) is not the same as Decimal('0.1').\n\
\n\
    >>> Decimal.from_float(0.1)\n\
    Decimal('0.1000000000000000055511151231257827021181583404541015625')\n\
    >>> Decimal.from_float(float('nan'))\n\
    Decimal('NaN')\n\
    >>> Decimal.from_float(float('inf'))\n\
    Decimal('Infinity')\n\
    >>> Decimal.from_float(float('-inf'))\n\
    Decimal('-Infinity')\n\
\n\
\n");

PyDoc_STRVAR(doc_fma,
"fma($self, /, other, third, context=None)\n--\n\n\
Returns a multiplied by b, plus c.\n\
\n\
Fused multiply-add. The first two operands are multiplied together,\n\
using multiply, the third operand is then added to the result of that\n\
multiplication, using add, all with only one final rounding.\n\
\n\
    >>> ExtendedContext.fma(Decimal('3'), Decimal('5'), Decimal('7'))\n\
    Decimal('22')\n\
    >>> ExtendedContext.fma(Decimal('3'), Decimal('-5'), Decimal('7'))\n\
    Decimal('-8')\n\
    >>> ExtendedContext.fma(Decimal('888565290'), Decimal('1557.96930'), Decimal('-86087.7578'))\n\
    Decimal('1.38435736E+12')\n\
    >>> ExtendedContext.fma(1, 3, 4)\n\
    Decimal('7')\n\
    >>> ExtendedContext.fma(1, Decimal(3), 4)\n\
    Decimal('7')\n\
    >>> ExtendedContext.fma(1, 3, Decimal(4))\n\
    Decimal('7')\n\
\n");

PyDoc_STRVAR(doc_is_canonical,
"is_canonical($self, /)\n--\n\n\
Return True if the operand is canonical; otherwise return False.\n\
Currently, the encoding of a Decimal instance is always\n\
canonical, so this method returns True for any Decimal.\n\
\n\
    >>> ExtendedContext.is_canonical(Decimal('2.50'))\n\
    True\n\
\n");

PyDoc_STRVAR(doc_is_finite,
"is_finite($self, /)\n--\n\n\
Return True if the operand is finite; otherwise return False.\n\
\n\
A Decimal instance is considered finite if it is neither infinite nor a\n\
NaN.\n\
\n\
    >>> ExtendedContext.is_finite(Decimal('2.50'))\n\
   True\n\
    >>> ExtendedContext.is_finite(Decimal('-0.3'))\n\
    True\n\
    >>> ExtendedContext.is_finite(Decimal('0'))\n\
    True\n\
    >>> ExtendedContext.is_finite(Decimal('Inf'))\n\
    False\n\
    >>> ExtendedContext.is_finite(Decimal('NaN'))\n\
    False\n\
    >>> ExtendedContext.is_finite(1)\n\
    True\n\
\n");

PyDoc_STRVAR(doc_is_infinite,
"is_infinite($self, /)\n--\n\n\
Return True if the operand is infinite; otherwise return False.\n\
\n\
    >>> ExtendedContext.is_infinite(Decimal('2.50'))\n\
    False\n\
    >>> ExtendedContext.is_infinite(Decimal('-Inf'))\n\
    True\n\
    >>> ExtendedContext.is_infinite(Decimal('NaN'))\n\
    False\n\
    >>> ExtendedContext.is_infinite(1)\n\
    False\n\
\n");

PyDoc_STRVAR(doc_is_nan,
"is_nan($self, /)\n--\n\n\
Return True if the operand is a (quiet or signaling) NaN\n\
otherwise return False.\n\
\n\
    >>> ExtendedContext.is_nan(Decimal('2.50'))\n\
    False\n\
    >>> ExtendedContext.is_nan(Decimal('NaN'))\n\
    True\n\
    >>> ExtendedContext.is_nan(Decimal('-sNaN'))\n\
    True\n\
    >>> ExtendedContext.is_nan(1)\n\
    False\n\
\n");

PyDoc_STRVAR(doc_is_normal,
"is_normal($self, /, context=None)\n--\n\n\
Return True if the argument is a normal finite non-zero number with an\n\
adjusted exponent greater than or equal to Emin. Return False if the\n\
argument is zero, subnormal, infinite or a NaN.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> c.is_normal(Decimal('2.50'))\n\
    True\n\
    >>> c.is_normal(Decimal('0.1E-999'))\n\
    False\n\
    >>> c.is_normal(Decimal('0.00'))\n\
    False\n\
    >>> c.is_normal(Decimal('-Inf'))\n\
    False\n\
    >>> c.is_normal(Decimal('NaN'))\n\
    False\n\
    >>> c.is_normal(1)\n\
    True\n\
\n");

PyDoc_STRVAR(doc_is_qnan,
"is_qnan($self, /)\n--\n\n\
Return True if the argument is a quiet NaN; otherwise return False.\n\
\n\
    >>> ExtendedContext.is_qnan(Decimal('2.50'))\n\
    False\n\
    >>> ExtendedContext.is_qnan(Decimal('NaN'))\n\
    True\n\
    >>> ExtendedContext.is_qnan(Decimal('sNaN'))\n\
    False\n\
    >>> ExtendedContext.is_qnan(1)\n\
    False\n\
\n");

PyDoc_STRVAR(doc_is_signed,
"is_signed($self, /)\n--\n\n\
Return True if the argument has a negative sign and False otherwise.\n\
Note that both zeros and NaNs can carry signs.\n\
\n\
    >>> ExtendedContext.is_signed(Decimal('2.50'))\n\
    False\n\
    >>> ExtendedContext.is_signed(Decimal('-12'))\n\
    True\n\
    >>> ExtendedContext.is_signed(Decimal('-0'))\n\
    True\n\
    >>> ExtendedContext.is_signed(8)\n\
    False\n\
    >>> ExtendedContext.is_signed(-8)\n\
    True\n\
\n");

PyDoc_STRVAR(doc_is_snan,
"is_snan($self, /)\n--\n\n\
Return True if the operand is a signaling NaN; otherwise return False.\n\
\n\
    >>> ExtendedContext.is_snan(Decimal('2.50'))\n\
    False\n\
    >>> ExtendedContext.is_snan(Decimal('NaN'))\n\
    False\n\
    >>> ExtendedContext.is_snan(Decimal('sNaN'))\n\
    True\n\
    >>> ExtendedContext.is_snan(1)\n\
    False\n\
\n");

PyDoc_STRVAR(doc_is_subnormal,
"is_subnormal($self, /, context=None)\n--\n\n\
Return True if the argument is subnormal, and False otherwise. A number is\n\
subnormal if it is non-zero, finite, and has an adjusted exponent less\n\
than Emin.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> c.is_subnormal(Decimal('2.50'))\n\
    False\n\
    >>> c.is_subnormal(Decimal('0.1E-999'))\n\
    True\n\
    >>> c.is_subnormal(Decimal('0.00'))\n\
    False\n\
    >>> c.is_subnormal(Decimal('-Inf'))\n\
    False\n\
    >>> c.is_subnormal(Decimal('NaN'))\n\
    False\n\
    >>> c.is_subnormal(1)\n\
    False\n\
\n");

PyDoc_STRVAR(doc_is_zero,
"is_zero($self, /)\n--\n\n\
Return True if the operand is a zero; otherwise return False.\n\
\n\
    >>> ExtendedContext.is_zero(Decimal('0'))\n\
    True\n\
    >>> ExtendedContext.is_zero(Decimal('2.50'))\n\
    False\n\
    >>> ExtendedContext.is_zero(Decimal('-0E+2'))\n\
    True\n\
    >>> ExtendedContext.is_zero(1)\n\
    False\n\
    >>> ExtendedContext.is_zero(0)\n\
    True\n\
\n");

PyDoc_STRVAR(doc_ln,
"ln($self, /, context=None)\n--\n\n\
Return the natural (base e) logarithm of the operand. The function always\n\
uses the ROUND_HALF_EVEN mode and the result is correctly rounded.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> c.ln(Decimal('0'))\n\
    Decimal('-Infinity')\n\
    >>> c.ln(Decimal('1.000'))\n\
    Decimal('0')\n\
    >>> c.ln(Decimal('2.71828183'))\n\
    Decimal('1.00000000')\n\
    >>> c.ln(Decimal('10'))\n\
    Decimal('2.30258509')\n\
    >>> c.ln(Decimal('+Infinity'))\n\
    Decimal('Infinity')\n\
    >>> c.ln(1)\n\
    Decimal('0')\n\
\n");

PyDoc_STRVAR(doc_log10,
"log10($self, /, context=None)\n--\n\n\
Return the base 10 logarithm of the operand. The function always uses the\n\
ROUND_HALF_EVEN mode and the result is correctly rounded.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> c.log10(Decimal('0'))\n\
    Decimal('-Infinity')\n\
    >>> c.log10(Decimal('0.001'))\n\
    Decimal('-3')\n\
    >>> c.log10(Decimal('1.000'))\n\
    Decimal('0')\n\
    >>> c.log10(Decimal('2'))\n\
    Decimal('0.301029996')\n\
    >>> c.log10(Decimal('10'))\n\
    Decimal('1')\n\
    >>> c.log10(Decimal('70'))\n\
    Decimal('1.84509804')\n\
    >>> c.log10(Decimal('+Infinity'))\n\
    Decimal('Infinity')\n\
    >>> c.log10(0)\n\
    Decimal('-Infinity')\n\
    >>> c.log10(1)\n\
    Decimal('0')\n\
\n");

PyDoc_STRVAR(doc_logb,
"logb($self, /, context=None)\n--\n\n\
Returns the exponent of the magnitude of the operand's MSD.\n\
The result is the integer which is the exponent of the magnitude\n\
of the most significant digit of the operand (as though the\n\
operand were truncated to a single digit while maintaining the\n\
value of that digit and without limiting the resulting exponent).\n\
\n\
    >>> ExtendedContext.logb(Decimal('250'))\n\
    Decimal('2')\n\
    >>> ExtendedContext.logb(Decimal('2.50'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logb(Decimal('0.03'))\n\
    Decimal('-2')\n\
    >>> ExtendedContext.logb(Decimal('0'))\n\
    Decimal('-Infinity')\n\
    >>> ExtendedContext.logb(1)\n\
    Decimal('0')\n\
    >>> ExtendedContext.logb(10)\n\
    Decimal('1')\n\
    >>> ExtendedContext.logb(100)\n\
    Decimal('2')\n\
\n");

PyDoc_STRVAR(doc_logical_and,
"logical_and($self, /, other, context=None)\n--\n\n\
Applies the logical operation 'and' between each operand's digits.\n\
The operands must be both logical numbers.\n\
\n\
    >>> ExtendedContext.logical_and(Decimal('0'), Decimal('0'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logical_and(Decimal('0'), Decimal('1'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logical_and(Decimal('1'), Decimal('0'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logical_and(Decimal('1'), Decimal('1'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.logical_and(Decimal('1100'), Decimal('1010'))\n\
    Decimal('1000')\n\
    >>> ExtendedContext.logical_and(Decimal('1111'), Decimal('10'))\n\
    Decimal('10')\n\
    >>> ExtendedContext.logical_and(110, 1101)\n\
    Decimal('100')\n\
    >>> ExtendedContext.logical_and(Decimal(110), 1101)\n\
    Decimal('100')\n\
    >>> ExtendedContext.logical_and(110, Decimal(1101))\n\
    Decimal('100')\n\
\n");

PyDoc_STRVAR(doc_logical_invert,
"logical_invert($self, /, context=None)\n--\n\n\
Invert all the digits in the operand.\n\
\n\
The operand must be a logical number.\n\
\n\
    >>> ExtendedContext.logical_invert(Decimal('0'))\n\
    Decimal('111111111')\n\
    >>> ExtendedContext.logical_invert(Decimal('1'))\n\
    Decimal('111111110')\n\
    >>> ExtendedContext.logical_invert(Decimal('111111111'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logical_invert(Decimal('101010101'))\n\
    Decimal('10101010')\n\
    >>> ExtendedContext.logical_invert(1101)\n\
    Decimal('111110010')\n\
\n");

PyDoc_STRVAR(doc_logical_or,
"logical_or($self, /, other, context=None)\n--\n\n\
Applies the logical operation 'or' between each operand's digits.\n\
The operands must be both logical numbers.\n\
\n\
    >>> ExtendedContext.logical_or(Decimal('0'), Decimal('0'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logical_or(Decimal('0'), Decimal('1'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.logical_or(Decimal('1'), Decimal('0'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.logical_or(Decimal('1'), Decimal('1'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.logical_or(Decimal('1100'), Decimal('1010'))\n\
    Decimal('1110')\n\
    >>> ExtendedContext.logical_or(Decimal('1110'), Decimal('10'))\n\
    Decimal('1110')\n\
    >>> ExtendedContext.logical_or(110, 1101)\n\
    Decimal('1111')\n\
    >>> ExtendedContext.logical_or(Decimal(110), 1101)\n\
    Decimal('1111')\n\
    >>> ExtendedContext.logical_or(110, Decimal(1101))\n\
    Decimal('1111')\n\
\n");

PyDoc_STRVAR(doc_logical_xor,
"logical_xor($self, /, other, context=None)\n--\n\n\
Applies the logical operation 'xor' between each operand's digits.\n\
\n\
The operands must be both logical numbers.\n\
\n\
    >>> ExtendedContext.logical_xor(Decimal('0'), Decimal('0'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logical_xor(Decimal('0'), Decimal('1'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.logical_xor(Decimal('1'), Decimal('0'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.logical_xor(Decimal('1'), Decimal('1'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.logical_xor(Decimal('1100'), Decimal('1010'))\n\
    Decimal('110')\n\
    >>> ExtendedContext.logical_xor(Decimal('1111'), Decimal('10'))\n\
    Decimal('1101')\n\
    >>> ExtendedContext.logical_xor(110, 1101)\n\
    Decimal('1011')\n\
    >>> ExtendedContext.logical_xor(Decimal(110), 1101)\n\
    Decimal('1011')\n\
    >>> ExtendedContext.logical_xor(110, Decimal(1101))\n\
    Decimal('1011')\n\
\n");

PyDoc_STRVAR(doc_max,
"max($self, /, other, context=None)\n--\n\n\
max compares two values numerically and returns the maximum.\n\
\n\
If either operand is a NaN then the general rules apply.\n\
Otherwise, the operands are compared as though by the compare\n\
operation.  If they are numerically equal then the left-hand operand\n\
is chosen as the result.  Otherwise the maximum (closer to positive\n\
infinity) of the two operands is chosen as the result.\n\
\n\
    >>> ExtendedContext.max(Decimal('3'), Decimal('2'))\n\
    Decimal('3')\n\
    >>> ExtendedContext.max(Decimal('-10'), Decimal('3'))\n\
    Decimal('3')\n\
    >>> ExtendedContext.max(Decimal('1.0'), Decimal('1'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.max(Decimal('7'), Decimal('NaN'))\n\
    Decimal('7')\n\
    >>> ExtendedContext.max(1, 2)\n\
    Decimal('2')\n\
    >>> ExtendedContext.max(Decimal(1), 2)\n\
    Decimal('2')\n\
    >>> ExtendedContext.max(1, Decimal(2))\n\
    Decimal('2')\n\
\n");

PyDoc_STRVAR(doc_max_mag,
"max_mag($self, /, other, context=None)\n--\n\n\
Similar to the max() method, but the comparison is done using the absolute\n\
values of the operands.\n\
    >>> ExtendedContext.max_mag(Decimal('7'), Decimal('NaN'))\n\
    Decimal('7')\n\
    >>> ExtendedContext.max_mag(Decimal('7'), Decimal('-10'))\n\
    Decimal('-10')\n\
    >>> ExtendedContext.max_mag(1, -2)\n\
    Decimal('-2')\n\
    >>> ExtendedContext.max_mag(Decimal(1), -2)\n\
    Decimal('-2')\n\
    >>> ExtendedContext.max_mag(1, Decimal(-2))\n\
    Decimal('-2')\n\
\n");

PyDoc_STRVAR(doc_min,
"min($self, /, other, context=None)\n--\n\n\
min compares two values numerically and returns the minimum.\n\
\n\
If either operand is a NaN then the general rules apply.\n\
Otherwise, the operands are compared as though by the compare\n\
operation.  If they are numerically equal then the left-hand operand\n\
is chosen as the result.  Otherwise the minimum (closer to negative\n\
infinity) of the two operands is chosen as the result.\n\
\n\
    >>> ExtendedContext.min(Decimal('3'), Decimal('2'))\n\
    Decimal('2')\n\
    >>> ExtendedContext.min(Decimal('-10'), Decimal('3'))\n\
    Decimal('-10')\n\
    >>> ExtendedContext.min(Decimal('1.0'), Decimal('1'))\n\
    Decimal('1.0')\n\
    >>> ExtendedContext.min(Decimal('7'), Decimal('NaN'))\n\
    Decimal('7')\n\
    >>> ExtendedContext.min(1, 2)\n\
    Decimal('1')\n\
    >>> ExtendedContext.min(Decimal(1), 2)\n\
    Decimal('1')\n\
    >>> ExtendedContext.min(1, Decimal(29))\n\
    Decimal('1')\n\
\n");

PyDoc_STRVAR(doc_min_mag,
"min_mag($self, /, other, context=None)\n--\n\n\
Compare the values numerically with their sign ignored.\n\
\n\
    >>> ExtendedContext.min_mag(Decimal('3'), Decimal('-2'))\n\
    Decimal('-2')\n\
    >>> ExtendedContext.min_mag(Decimal('-3'), Decimal('NaN'))\n\
    Decimal('-3')\n\
    >>> ExtendedContext.min_mag(1, -2)\n\
    Decimal('1')\n\
    >>> ExtendedContext.min_mag(Decimal(1), -2)\n\
    Decimal('1')\n\
    >>> ExtendedContext.min_mag(1, Decimal(-2))\n\
    Decimal('1')\n\
\n");

PyDoc_STRVAR(doc_next_minus,
"next_minus($self, /, context=None)\n--\n\n\
Return the largest number representable in the given context (or in the\n\
current default context if no context is given) that is smaller than the\n\
given operand.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> ExtendedContext.next_minus(Decimal('1'))\n\
    Decimal('0.999999999')\n\
    >>> c.next_minus(Decimal('1E-1007'))\n\
    Decimal('0E-1007')\n\
    >>> ExtendedContext.next_minus(Decimal('-1.00000003'))\n\
    Decimal('-1.00000004')\n\
    >>> c.next_minus(Decimal('Infinity'))\n\
    Decimal('9.99999999E+999')\n\
    >>> c.next_minus(1)\n\
    Decimal('0.999999999')\n\
\n");

PyDoc_STRVAR(doc_next_plus,
"next_plus($self, /, context=None)\n--\n\n\
Return the smallest number representable in the given context (or in the\n\
current default context if no context is given) that is larger than the\n\
given operand.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> ExtendedContext.next_plus(Decimal('1'))\n\
    Decimal('1.00000001')\n\
    >>> c.next_plus(Decimal('-1E-1007'))\n\
    Decimal('-0E-1007')\n\
    >>> ExtendedContext.next_plus(Decimal('-1.00000003'))\n\
    Decimal('-1.00000002')\n\
    >>> c.next_plus(Decimal('-Infinity'))\n\
    Decimal('-9.99999999E+999')\n\
    >>> c.next_plus(1)\n\
    Decimal('1.00000001')\n\
\n");

PyDoc_STRVAR(doc_next_toward,
"next_toward($self, /, other, context=None)\n--\n\n\
If the two operands are unequal, return the number closest to the first\n\
operand in the direction of the second operand.  If both operands are\n\
numerically equal, return a copy of the first operand with the sign set\n\
to be the same as the sign of the second operand.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> c.next_toward(Decimal('1'), Decimal('2'))\n\
    Decimal('1.00000001')\n\
    >>> c.next_toward(Decimal('-1E-1007'), Decimal('1'))\n\
    Decimal('-0E-1007')\n\
    >>> c.next_toward(Decimal('-1.00000003'), Decimal('0'))\n\
    Decimal('-1.00000002')\n\
    >>> c.next_toward(Decimal('1'), Decimal('0'))\n\
    Decimal('0.999999999')\n\
    >>> c.next_toward(Decimal('1E-1007'), Decimal('-100'))\n\
    Decimal('0E-1007')\n\
    >>> c.next_toward(Decimal('-1.00000003'), Decimal('-10'))\n\
    Decimal('-1.00000004')\n\
    >>> c.next_toward(Decimal('0.00'), Decimal('-0.0000'))\n\
    Decimal('-0.00')\n\
    >>> c.next_toward(0, 1)\n\
    Decimal('1E-1007')\n\
    >>> c.next_toward(Decimal(0), 1)\n\
    Decimal('1E-1007')\n\
    >>> c.next_toward(0, Decimal(1))\n\
    Decimal('1E-1007')\n\
\n");

PyDoc_STRVAR(doc_normalize,
"normalize($self, /, context=None)\n--\n\n\
Normalize the number by stripping the rightmost trailing zeros and\n\
converting any result equal to Decimal('0') to Decimal('0e0').  Used\n\
for producing canonical values for members of an equivalence class.\n\
For example, Decimal('32.100') and Decimal('0.321000e+2') both normalize\n\
to the equivalent value Decimal('32.1').\n\
\n\
    >>> ExtendedContext.normalize(Decimal('2.1'))\n\
    Decimal('2.1')\n\
    >>> ExtendedContext.normalize(Decimal('-2.0'))\n\
    Decimal('-2')\n\
    >>> ExtendedContext.normalize(Decimal('1.200'))\n\
    Decimal('1.2')\n\
    >>> ExtendedContext.normalize(Decimal('-120'))\n\
    Decimal('-1.2E+2')\n\
    >>> ExtendedContext.normalize(Decimal('120.00'))\n\
    Decimal('1.2E+2')\n\
    >>> ExtendedContext.normalize(Decimal('0.00'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.normalize(6)\n\
    Decimal('6')\n\
\n");

PyDoc_STRVAR(doc_number_class,
"number_class($self, /, context=None)\n--\n\n\
Return a string describing the class of the operand.  The returned value\n\
is one of the following ten strings:\n\
\n\
    * '-Infinity', indicating that the operand is negative infinity.\n\
    * '-Normal', indicating that the operand is a negative normal number.\n\
    * '-Subnormal', indicating that the operand is negative and subnormal.\n\
    * '-Zero', indicating that the operand is a negative zero.\n\
    * '+Zero', indicating that the operand is a positive zero.\n\
    * '+Subnormal', indicating that the operand is positive and subnormal.\n\
    * '+Normal', indicating that the operand is a positive normal number.\n\
    * '+Infinity', indicating that the operand is positive infinity.\n\
    * 'NaN', indicating that the operand is a quiet NaN (Not a Number).\n\
    * 'sNaN', indicating that the operand is a signaling NaN.\n\
\n\
    >>> c = ExtendedContext.copy()\n\
    >>> c.Emin = -999\n\
    >>> c.Emax = 999\n\
    >>> c.number_class(Decimal('Infinity'))\n\
    '+Infinity'\n\
    >>> c.number_class(Decimal('1E-10'))\n\
    '+Normal'\n\
    >>> c.number_class(Decimal('2.50'))\n\
    '+Normal'\n\
    >>> c.number_class(Decimal('0.1E-999'))\n\
    '+Subnormal'\n\
    >>> c.number_class(Decimal('0'))\n\
    '+Zero'\n\
    >>> c.number_class(Decimal('-0'))\n\
    '-Zero'\n\
    >>> c.number_class(Decimal('-0.1E-999'))\n\
    '-Subnormal'\n\
    >>> c.number_class(Decimal('-1E-10'))\n\
    '-Normal'\n\
    >>> c.number_class(Decimal('-2.50'))\n\
    '-Normal'\n\
    >>> c.number_class(Decimal('-Infinity'))\n\
    '-Infinity'\n\
    >>> c.number_class(Decimal('NaN'))\n\
    'NaN'\n\
    >>> c.number_class(Decimal('-NaN'))\n\
    'NaN'\n\
    >>> c.number_class(Decimal('sNaN'))\n\
    'sNaN'\n\
    >>> c.number_class(123)\n\
    '+Normal'\n\
\n");

PyDoc_STRVAR(doc_quantize,
"quantize($self, /, exp, rounding=None, context=None)\n--\n\n\
Returns a value equal to 'a' (rounded), having the exponent of 'b'.\n\
\n\
The coefficient of the result is derived from that of the left-hand\n\
operand.  It may be rounded using the current rounding setting (if the\n\
exponent is being increased), multiplied by a positive power of ten (if\n\
the exponent is being decreased), or is unchanged (if the exponent is\n\
already equal to that of the right-hand operand).\n\
\n\
Unlike other operations, if the length of the coefficient after the\n\
quantize operation would be greater than precision then an Invalid\n\
operation condition is raised.  This guarantees that, unless there is\n\
an error condition, the exponent of the result of a quantize is always\n\
equal to that of the right-hand operand.\n\
Also unlike other operations, quantize will never raise Underflow, even\n\
if the result is subnormal and inexact.\n\
\n\
    >>> ExtendedContext.quantize(Decimal('2.17'), Decimal('0.001'))\n\
    Decimal('2.170')\n\
    >>> ExtendedContext.quantize(Decimal('2.17'), Decimal('0.01'))\n\
    Decimal('2.17')\n\
    >>> ExtendedContext.quantize(Decimal('2.17'), Decimal('0.1'))\n\
    Decimal('2.2')\n\
    >>> ExtendedContext.quantize(Decimal('2.17'), Decimal('1e+0'))\n\
    Decimal('2')\n\
    >>> ExtendedContext.quantize(Decimal('2.17'), Decimal('1e+1'))\n\
    Decimal('0E+1')\n\
    >>> ExtendedContext.quantize(Decimal('-Inf'), Decimal('Infinity'))\n\
    Decimal('-Infinity')\n\
    >>> ExtendedContext.quantize(Decimal('2'), Decimal('Infinity'))\n\
    Decimal('NaN')\n\
    >>> ExtendedContext.quantize(Decimal('-0.1'), Decimal('1'))\n\
    Decimal('-0')\n\
    >>> ExtendedContext.quantize(Decimal('-0'), Decimal('1e+5'))\n\
    Decimal('-0E+5')\n\
    >>> ExtendedContext.quantize(Decimal('+35236450.6'), Decimal('1e-2'))\n\
    Decimal('NaN')\n\
    >>> ExtendedContext.quantize(Decimal('-35236450.6'), Decimal('1e-2'))\n\
    Decimal('NaN')\n\
    >>> ExtendedContext.quantize(Decimal('217'), Decimal('1e-1'))\n\
    Decimal('217.0')\n\
    >>> ExtendedContext.quantize(Decimal('217'), Decimal('1e-0'))\n\
    Decimal('217')\n\
    >>> ExtendedContext.quantize(Decimal('217'), Decimal('1e+1'))\n\
    Decimal('2.2E+2')\n\
    >>> ExtendedContext.quantize(Decimal('217'), Decimal('1e+2'))\n\
    Decimal('2E+2')\n\
    >>> ExtendedContext.quantize(1, 2)\n\
    Decimal('1')\n\
    >>> ExtendedContext.quantize(Decimal(1), 2)\n\
    Decimal('1')\n\
    >>> ExtendedContext.quantize(1, Decimal(2))\n\
    Decimal('1')\n\
\n");

PyDoc_STRVAR(doc_radix,
"radix($self, /)\n--\n\n\
Return Decimal(10), the radix (base) in which the Decimal class does\n\
all its arithmetic. Included for compatibility with the specification.\n\
\n\
    >>> ExtendedContext.radix()\n\
    Decimal('10')\n\
\n");

PyDoc_STRVAR(doc_remainder_near,
"remainder_near($self, /, other, context=None)\n--\n\n\
Returns to be \"a - b * n\", where n is the integer nearest the exact\n\
value of \"x / b\" (if two integers are equally near then the even one\n\
is chosen).  If the result is equal to 0 then its sign will be the\n\
sign of a.\n\
\n\
This operation will fail under the same conditions as integer division\n\
(that is, if integer division on the same two operands would fail, the\n\
remainder cannot be calculated).\n\
\n\
    >>> ExtendedContext.remainder_near(Decimal('2.1'), Decimal('3'))\n\
    Decimal('-0.9')\n\
    >>> ExtendedContext.remainder_near(Decimal('10'), Decimal('6'))\n\
    Decimal('-2')\n\
    >>> ExtendedContext.remainder_near(Decimal('10'), Decimal('3'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.remainder_near(Decimal('-10'), Decimal('3'))\n\
    Decimal('-1')\n\
    >>> ExtendedContext.remainder_near(Decimal('10.2'), Decimal('1'))\n\
    Decimal('0.2')\n\
    >>> ExtendedContext.remainder_near(Decimal('10'), Decimal('0.3'))\n\
    Decimal('0.1')\n\
    >>> ExtendedContext.remainder_near(Decimal('3.6'), Decimal('1.3'))\n\
    Decimal('-0.3')\n\
    >>> ExtendedContext.remainder_near(3, 11)\n\
    Decimal('3')\n\
    >>> ExtendedContext.remainder_near(Decimal(3), 11)\n\
    Decimal('3')\n\
    >>> ExtendedContext.remainder_near(3, Decimal(11))\n\
    Decimal('3')\n\
\n");

PyDoc_STRVAR(doc_rotate,
"rotate($self, /, other, context=None)\n--\n\n\
Returns a rotated copy of a, b times.\n\
\n\
The coefficient of the result is a rotated copy of the digits in\n\
the coefficient of the first operand.  The number of places of\n\
rotation is taken from the absolute value of the second operand,\n\
with the rotation being to the left if the second operand is\n\
positive or to the right otherwise.\n\
\n\
    >>> ExtendedContext.rotate(Decimal('34'), Decimal('8'))\n\
    Decimal('400000003')\n\
    >>> ExtendedContext.rotate(Decimal('12'), Decimal('9'))\n\
    Decimal('12')\n\
    >>> ExtendedContext.rotate(Decimal('123456789'), Decimal('-2'))\n\
    Decimal('891234567')\n\
    >>> ExtendedContext.rotate(Decimal('123456789'), Decimal('0'))\n\
    Decimal('123456789')\n\
    >>> ExtendedContext.rotate(Decimal('123456789'), Decimal('+2'))\n\
    Decimal('345678912')\n\
    >>> ExtendedContext.rotate(1333333, 1)\n\
    Decimal('13333330')\n\
    >>> ExtendedContext.rotate(Decimal(1333333), 1)\n\
    Decimal('13333330')\n\
    >>> ExtendedContext.rotate(1333333, Decimal(1))\n\
    Decimal('13333330')\n\
\n");

PyDoc_STRVAR(doc_same_quantum,
"same_quantum($self, /, other, context=None)\n--\n\n\
Returns True if the two operands have the same exponent.\n\
\n\
The result is never affected by either the sign or the coefficient of\n\
either operand.\n\
\n\
    >>> ExtendedContext.same_quantum(Decimal('2.17'), Decimal('0.001'))\n\
    False\n\
    >>> ExtendedContext.same_quantum(Decimal('2.17'), Decimal('0.01'))\n\
    True\n\
    >>> ExtendedContext.same_quantum(Decimal('2.17'), Decimal('1'))\n\
    False\n\
    >>> ExtendedContext.same_quantum(Decimal('Inf'), Decimal('-Inf'))\n\
    True\n\
    >>> ExtendedContext.same_quantum(10000, -1)\n\
    True\n\
    >>> ExtendedContext.same_quantum(Decimal(10000), -1)\n\
    True\n\
    >>> ExtendedContext.same_quantum(10000, Decimal(-1))\n\
    True\n\
\n");

PyDoc_STRVAR(doc_scaleb,
"scaleb($self, /, other, context=None)\n--\n\n\
Returns the first operand after adding the second value its exp.\n\
\n\
    >>> ExtendedContext.scaleb(Decimal('7.50'), Decimal('-2'))\n\
    Decimal('0.0750')\n\
    >>> ExtendedContext.scaleb(Decimal('7.50'), Decimal('0'))\n\
    Decimal('7.50')\n\
    >>> ExtendedContext.scaleb(Decimal('7.50'), Decimal('3'))\n\
    Decimal('7.50E+3')\n\
    >>> ExtendedContext.scaleb(1, 4)\n\
    Decimal('1E+4')\n\
    >>> ExtendedContext.scaleb(Decimal(1), 4)\n\
    Decimal('1E+4')\n\
    >>> ExtendedContext.scaleb(1, Decimal(4))\n\
    Decimal('1E+4')\n\
\n");

PyDoc_STRVAR(doc_shift,
"shift($self, /, other, context=None)\n--\n\n\
Returns a shifted copy of a, b times.\n\
\n\
The coefficient of the result is a shifted copy of the digits\n\
in the coefficient of the first operand.  The number of places\n\
to shift is taken from the absolute value of the second operand,\n\
with the shift being to the left if the second operand is\n\
positive or to the right otherwise.  Digits shifted into the\n\
coefficient are zeros.\n\
\n\
    >>> ExtendedContext.shift(Decimal('34'), Decimal('8'))\n\
    Decimal('400000000')\n\
    >>> ExtendedContext.shift(Decimal('12'), Decimal('9'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.shift(Decimal('123456789'), Decimal('-2'))\n\
    Decimal('1234567')\n\
    >>> ExtendedContext.shift(Decimal('123456789'), Decimal('0'))\n\
    Decimal('123456789')\n\
    >>> ExtendedContext.shift(Decimal('123456789'), Decimal('+2'))\n\
    Decimal('345678900')\n\
    >>> ExtendedContext.shift(88888888, 2)\n\
    Decimal('888888800')\n\
    >>> ExtendedContext.shift(Decimal(88888888), 2)\n\
    Decimal('888888800')\n\
    >>> ExtendedContext.shift(88888888, Decimal(2))\n\
    Decimal('888888800')\n\
\n");

PyDoc_STRVAR(doc_sqrt,
"sqrt($self, /, context=None)\n--\n\n\
Square root of a non-negative number to context precision.\n\
\n\
If the result must be inexact, it is rounded using the round-half-even\n\
algorithm.\n\
\n\
    >>> ExtendedContext.sqrt(Decimal('0'))\n\
    Decimal('0')\n\
    >>> ExtendedContext.sqrt(Decimal('-0'))\n\
    Decimal('-0')\n\
    >>> ExtendedContext.sqrt(Decimal('0.39'))\n\
    Decimal('0.624499800')\n\
    >>> ExtendedContext.sqrt(Decimal('100'))\n\
    Decimal('10')\n\
    >>> ExtendedContext.sqrt(Decimal('1'))\n\
    Decimal('1')\n\
    >>> ExtendedContext.sqrt(Decimal('1.0'))\n\
    Decimal('1.0')\n\
    >>> ExtendedContext.sqrt(Decimal('1.00'))\n\
    Decimal('1.0')\n\
    >>> ExtendedContext.sqrt(Decimal('7'))\n\
    Decimal('2.64575131')\n\
    >>> ExtendedContext.sqrt(Decimal('10'))\n\
    Decimal('3.16227766')\n\
    >>> ExtendedContext.sqrt(2)\n\
    Decimal('1.41421356')\n\
    >>> ExtendedContext.prec\n\
    9\n\
\n");

PyDoc_STRVAR(doc_to_eng_string,
"to_eng_string($self, /, context=None)\n--\n\n\
Convert to a string, using engineering notation if an exponent is needed.\n\
\n\
Engineering notation has an exponent which is a multiple of 3. This\n\
can leave up to 3 digits to the left of the decimal place and may\n\
require the addition of either one or two trailing zeros.\n\
\n\
The value of context.capitals determines whether the exponent sign is lower\n\
or upper case. Otherwise, the context does not affect the operation.\n\
\n\
    >>> ExtendedContext.to_eng_string(Decimal('123E+1'))\n\
    '1.23E+3'\n\
    >>> ExtendedContext.to_eng_string(Decimal('123E+3'))\n\
    '123E+3'\n\
    >>> ExtendedContext.to_eng_string(Decimal('123E-10'))\n\
    '12.3E-9'\n\
    >>> ExtendedContext.to_eng_string(Decimal('-123E-12'))\n\
    '-123E-12'\n\
    >>> ExtendedContext.to_eng_string(Decimal('7E-7'))\n\
    '700E-9'\n\
    >>> ExtendedContext.to_eng_string(Decimal('7E+1'))\n\
    '70'\n\
    >>> ExtendedContext.to_eng_string(Decimal('0E+1'))\n\
    '0.00E+3'\n\
\n");

PyDoc_STRVAR(doc_to_integral,
"to_integral($self, /, rounding=None, context=None)\n--\n\n\
Identical to the to_integral_value() method.  The to_integral() name has been\n\
kept for compatibility with older versions.\n\
\n");

PyDoc_STRVAR(doc_to_integral_exact,
"to_integral_exact($self, /, rounding=None, context=None)\n--\n\n\
Round to the nearest integer, signaling Inexact or Rounded as appropriate if\n\
rounding occurs.  The rounding mode is determined by the rounding parameter\n\
if given, else by the given context. If neither parameter is given, then the\n\
rounding mode of the current default context is used.\n\
\n");

PyDoc_STRVAR(doc_to_integral_value,
"to_integral_value($self, /, rounding=None, context=None)\n--\n\n\
Round to the nearest integer without signaling Inexact or Rounded.  The\n\
rounding mode is determined by the rounding parameter if given, else by\n\
the given context. If neither parameter is given, then the rounding mode\n\
of the current default context is used.\n\
\n");


/******************************************************************************/
/*                       Context Object and Methods                           */
/******************************************************************************/

PyDoc_STRVAR(doc_context,
"Context(prec=None, rounding=None, Emin=None, Emax=None, capitals=None, clamp=None, flags=None, traps=None)\n--\n\n\
The context affects almost all operations and controls rounding,\n\
Over/Underflow, raising of exceptions and much more.  A new context\n\
can be constructed as follows:\n\
\n\
    >>> c = Context(prec=28, Emin=-425000000, Emax=425000000,\n\
    ...             rounding=ROUND_HALF_EVEN, capitals=1, clamp=1,\n\
    ...             traps=[InvalidOperation, DivisionByZero, Overflow],\n\
    ...             flags=[])\n\
    >>>\n\
\n\
\n");

#ifdef EXTRA_FUNCTIONALITY
PyDoc_STRVAR(doc_ctx_apply,
"apply($self, x, /)\n--\n\n\
Apply self to Decimal x.\n\
\n");
#endif

PyDoc_STRVAR(doc_ctx_clear_flags,
"clear_flags($self, /)\n--\n\n\
Reset all flags to False.\n\
\n");

PyDoc_STRVAR(doc_ctx_clear_traps,
"clear_traps($self, /)\n--\n\n\
Set all traps to False.\n\
\n");

PyDoc_STRVAR(doc_ctx_copy,
"copy($self, /)\n--\n\n\
Return a duplicate of the context with all flags cleared.\n\
\n");

PyDoc_STRVAR(doc_ctx_copy_decimal,
"copy_decimal($self, x, /)\n--\n\n\
Return a copy of Decimal x.\n\
\n");

PyDoc_STRVAR(doc_ctx_create_decimal,
"create_decimal($self, num=\"0\", /)\n--\n\n\
Create a new Decimal instance from num, using self as the context. Unlike the\n\
Decimal constructor, this function observes the context limits.\n\
\n");

PyDoc_STRVAR(doc_ctx_create_decimal_from_float,
"create_decimal_from_float($self, f, /)\n--\n\n\
Create a new Decimal instance from float f.  Unlike the Decimal.from_float()\n\
class method, this function observes the context limits.\n\
\n");

PyDoc_STRVAR(doc_ctx_Etiny,
"Etiny($self, /)\n--\n\n\
Return a value equal to Emin - prec + 1, which is the minimum exponent value\n\
for subnormal results.  When underflow occurs, the exponent is set to Etiny.\n\
\n");

PyDoc_STRVAR(doc_ctx_Etop,
"Etop($self, /)\n--\n\n\
Return a value equal to Emax - prec + 1.  This is the maximum exponent\n\
if the _clamp field of the context is set to 1 (IEEE clamp mode).  Etop()\n\
must not be negative.\n\
\n");

PyDoc_STRVAR(doc_ctx_abs,
"abs($self, x, /)\n--\n\n\
Return the absolute value of x.\n\
\n");

PyDoc_STRVAR(doc_ctx_add,
"add($self, x, y, /)\n--\n\n\
Return the sum of x and y.\n\
\n");

PyDoc_STRVAR(doc_ctx_canonical,
"canonical($self, x, /)\n--\n\n\
Return a new instance of x.\n\
\n");

PyDoc_STRVAR(doc_ctx_compare,
"compare($self, x, y, /)\n--\n\n\
Compare x and y numerically.\n\
\n");

PyDoc_STRVAR(doc_ctx_compare_signal,
"compare_signal($self, x, y, /)\n--\n\n\
Compare x and y numerically.  All NaNs signal.\n\
\n");

PyDoc_STRVAR(doc_ctx_compare_total,
"compare_total($self, x, y, /)\n--\n\n\
Compare x and y using their abstract representation.\n\
\n");

PyDoc_STRVAR(doc_ctx_compare_total_mag,
"compare_total_mag($self, x, y, /)\n--\n\n\
Compare x and y using their abstract representation, ignoring sign.\n\
\n");

PyDoc_STRVAR(doc_ctx_copy_abs,
"copy_abs($self, x, /)\n--\n\n\
Return a copy of x with the sign set to 0.\n\
\n");

PyDoc_STRVAR(doc_ctx_copy_negate,
"copy_negate($self, x, /)\n--\n\n\
Return a copy of x with the sign inverted.\n\
\n");

PyDoc_STRVAR(doc_ctx_copy_sign,
"copy_sign($self, x, y, /)\n--\n\n\
Copy the sign from y to x.\n\
\n");

PyDoc_STRVAR(doc_ctx_divide,
"divide($self, x, y, /)\n--\n\n\
Return x divided by y.\n\
\n");

PyDoc_STRVAR(doc_ctx_divide_int,
"divide_int($self, x, y, /)\n--\n\n\
Return x divided by y, truncated to an integer.\n\
\n");

PyDoc_STRVAR(doc_ctx_divmod,
"divmod($self, x, y, /)\n--\n\n\
Return quotient and remainder of the division x / y.\n\
\n");

PyDoc_STRVAR(doc_ctx_exp,
"exp($self, x, /)\n--\n\n\
Return e ** x.\n\
\n");

PyDoc_STRVAR(doc_ctx_fma,
"fma($self, x, y, z, /)\n--\n\n\
Return x multiplied by y, plus z.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_canonical,
"is_canonical($self, x, /)\n--\n\n\
Return True if x is canonical, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_finite,
"is_finite($self, x, /)\n--\n\n\
Return True if x is finite, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_infinite,
"is_infinite($self, x, /)\n--\n\n\
Return True if x is infinite, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_nan,
"is_nan($self, x, /)\n--\n\n\
Return True if x is a qNaN or sNaN, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_normal,
"is_normal($self, x, /)\n--\n\n\
Return True if x is a normal number, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_qnan,
"is_qnan($self, x, /)\n--\n\n\
Return True if x is a quiet NaN, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_signed,
"is_signed($self, x, /)\n--\n\n\
Return True if x is negative, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_snan,
"is_snan($self, x, /)\n--\n\n\
Return True if x is a signaling NaN, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_subnormal,
"is_subnormal($self, x, /)\n--\n\n\
Return True if x is subnormal, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_is_zero,
"is_zero($self, x, /)\n--\n\n\
Return True if x is a zero, False otherwise.\n\
\n");

PyDoc_STRVAR(doc_ctx_ln,
"ln($self, x, /)\n--\n\n\
Return the natural (base e) logarithm of x.\n\
\n");

PyDoc_STRVAR(doc_ctx_log10,
"log10($self, x, /)\n--\n\n\
Return the base 10 logarithm of x.\n\
\n");

PyDoc_STRVAR(doc_ctx_logb,
"logb($self, x, /)\n--\n\n\
Return the exponent of the magnitude of the operand's MSD.\n\
\n");

PyDoc_STRVAR(doc_ctx_logical_and,
"logical_and($self, x, y, /)\n--\n\n\
Digit-wise and of x and y.\n\
\n");

PyDoc_STRVAR(doc_ctx_logical_invert,
"logical_invert($self, x, /)\n--\n\n\
Invert all digits of x.\n\
\n");

PyDoc_STRVAR(doc_ctx_logical_or,
"logical_or($self, x, y, /)\n--\n\n\
Digit-wise or of x and y.\n\
\n");

PyDoc_STRVAR(doc_ctx_logical_xor,
"logical_xor($self, x, y, /)\n--\n\n\
Digit-wise xor of x and y.\n\
\n");

PyDoc_STRVAR(doc_ctx_max,
"max($self, x, y, /)\n--\n\n\
Compare the values numerically and return the maximum.\n\
\n");

PyDoc_STRVAR(doc_ctx_max_mag,
"max_mag($self, x, y, /)\n--\n\n\
Compare the values numerically with their sign ignored.\n\
\n");

PyDoc_STRVAR(doc_ctx_min,
"min($self, x, y, /)\n--\n\n\
Compare the values numerically and return the minimum.\n\
\n");

PyDoc_STRVAR(doc_ctx_min_mag,
"min_mag($self, x, y, /)\n--\n\n\
Compare the values numerically with their sign ignored.\n\
\n");

PyDoc_STRVAR(doc_ctx_minus,
"minus($self, x, /)\n--\n\n\
Minus corresponds to the unary prefix minus operator in Python, but applies\n\
the context to the result.\n\
\n");

PyDoc_STRVAR(doc_ctx_multiply,
"multiply($self, x, y, /)\n--\n\n\
Return the product of x and y.\n\
\n");

PyDoc_STRVAR(doc_ctx_next_minus,
"next_minus($self, x, /)\n--\n\n\
Return the largest representable number smaller than x.\n\
\n");

PyDoc_STRVAR(doc_ctx_next_plus,
"next_plus($self, x, /)\n--\n\n\
Return the smallest representable number larger than x.\n\
\n");

PyDoc_STRVAR(doc_ctx_next_toward,
"next_toward($self, x, y, /)\n--\n\n\
Return the number closest to x, in the direction towards y.\n\
\n");

PyDoc_STRVAR(doc_ctx_normalize,
"normalize($self, x, /)\n--\n\n\
Reduce x to its simplest form. Alias for reduce(x).\n\
\n");

PyDoc_STRVAR(doc_ctx_number_class,
"number_class($self, x, /)\n--\n\n\
Return an indication of the class of x.\n\
\n");

PyDoc_STRVAR(doc_ctx_plus,
"plus($self, x, /)\n--\n\n\
Plus corresponds to the unary prefix plus operator in Python, but applies\n\
the context to the result.\n\
\n");

PyDoc_STRVAR(doc_ctx_power,
"power($self, /, a, b, modulo=None)\n--\n\n\
Compute a**b. If 'a' is negative, then 'b' must be integral. The result\n\
will be inexact unless 'a' is integral and the result is finite and can\n\
be expressed exactly in 'precision' digits.  In the Python version the\n\
result is always correctly rounded, in the C version the result is almost\n\
always correctly rounded.\n\
\n\
If modulo is given, compute (a**b) % modulo. The following restrictions\n\
hold:\n\
\n\
    * all three arguments must be integral\n\
    * 'b' must be nonnegative\n\
    * at least one of 'a' or 'b' must be nonzero\n\
    * modulo must be nonzero and less than 10**prec in absolute value\n\
\n\
\n");

PyDoc_STRVAR(doc_ctx_quantize,
"quantize($self, x, y, /)\n--\n\n\
Return a value equal to x (rounded), having the exponent of y.\n\
\n");

PyDoc_STRVAR(doc_ctx_radix,
"radix($self, /)\n--\n\n\
Return 10.\n\
\n");

PyDoc_STRVAR(doc_ctx_remainder,
"remainder($self, x, y, /)\n--\n\n\
Return the remainder from integer division.  The sign of the result,\n\
if non-zero, is the same as that of the original dividend.\n\
\n");

PyDoc_STRVAR(doc_ctx_remainder_near,
"remainder_near($self, x, y, /)\n--\n\n\
Return x - y * n, where n is the integer nearest the exact value of x / y\n\
(if the result is 0 then its sign will be the sign of x).\n\
\n");

PyDoc_STRVAR(doc_ctx_rotate,
"rotate($self, x, y, /)\n--\n\n\
Return a copy of x, rotated by y places.\n\
\n");

PyDoc_STRVAR(doc_ctx_same_quantum,
"same_quantum($self, x, y, /)\n--\n\n\
Return True if the two operands have the same exponent.\n\
\n");

PyDoc_STRVAR(doc_ctx_scaleb,
"scaleb($self, x, y, /)\n--\n\n\
Return the first operand after adding the second value to its exp.\n\
\n");

PyDoc_STRVAR(doc_ctx_shift,
"shift($self, x, y, /)\n--\n\n\
Return a copy of x, shifted by y places.\n\
\n");

PyDoc_STRVAR(doc_ctx_sqrt,
"sqrt($self, x, /)\n--\n\n\
Square root of a non-negative number to context precision.\n\
\n");

PyDoc_STRVAR(doc_ctx_subtract,
"subtract($self, x, y, /)\n--\n\n\
Return the difference between x and y.\n\
\n");

PyDoc_STRVAR(doc_ctx_to_eng_string,
"to_eng_string($self, x, /)\n--\n\n\
Convert a number to a string, using engineering notation.\n\
\n");

PyDoc_STRVAR(doc_ctx_to_integral,
"to_integral($self, x, /)\n--\n\n\
Identical to to_integral_value(x).\n\
\n");

PyDoc_STRVAR(doc_ctx_to_integral_exact,
"to_integral_exact($self, x, /)\n--\n\n\
Round to an integer. Signal if the result is rounded or inexact.\n\
\n");

PyDoc_STRVAR(doc_ctx_to_integral_value,
"to_integral_value($self, x, /)\n--\n\n\
Round to an integer.\n\
\n");

PyDoc_STRVAR(doc_ctx_to_sci_string,
"to_sci_string($self, x, /)\n--\n\n\
Convert a number to a string using scientific notation.\n\
\n");


#endif /* DOCSTRINGS_H */



