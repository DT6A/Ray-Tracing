/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MTHDEF.H
 * PURPOSE     : Ray tracing system.
 *               Math base defenitions.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MTHDEF_H_
#define __MTHDEF_H_

#include <cmath>
#include <ctime>

#include <commondf.h>

typedef double DBL;
typedef float FLT;

namespace mth
{
  const long double PI = 3.141592653589793; // PI constant
  const DBL Infinity = 99999;

  /* Swap two variables data function.
   * ARGUMENTS:
   *   - variables to swap:
   *       Type X, Y;
   * RETURNS: None.
   */
  template <class Type>
    VOID Swap( Type &X, Type &Y )
    {
      Type tmp = X;

      X = Y;
      Y = tmp;
    } /* End of 'Swap' function */

  /* Get minimum of two variables function.
   * ARGUMENTS:
   *   - variables to compare:
   *       Type X, Y;
   * RETURNS:
   *   (Type) smaller variable.
   */
  template <class Type>
    Type Min( const Type X, const Type Y )
    {
      return X > Y ? Y : X;
    } /* End of 'Min' function */
 
  /* Get maximum of two variables function.
   * ARGUMENTS:
   *   - variables to compare:
   *       Type X, Y;
   * RETURNS:
   *   (Type) bigger variable.
   */
  template <class Type>
    Type Max( const Type X, const Type Y )
    {
      return X < Y ? Y : X;
    } /* End of 'Max' function */

  /* Get variable sign function.
   * ARGUMENTS:
   *   - variables to get sign from:
   *       Type C;
   * RETURNS:
   *   (INT) 1 if positive, -1 if negative, 0 if zero.
   */
  template <class Type>
    INT Sign( const Type C )
    {
      return C > 0 ? 1 : C < 0 ? -1 : 0;
    } /* End of 'Sign' function */
  
  static DBL arch(DBL X)
  {
    return log(X + sqrt(X * X - 1));
  }

  static DBL sh(DBL X)
  {
    return (exp(X) - exp(-X)) / 2;
  }

  static DBL ch(DBL X)
  {
    return (exp(X) + exp(-X)) / 2;
  }

  static DBL * SolveSqure(DBL a, DBL b, DBL c)
  {
	static DBL Answers[2];
	Answers[0] = -Infinity;
	Answers[1] = -Infinity;
	DBL D = b * b - 4 * a * c;
	if (D < 0)
		return Answers;
	Answers[0] = (-b + sqrt(D)) / (2 * a);
	Answers[1] = (-b - sqrt(D)) / (2 * a);
	return Answers;
  }
  /* Solve cubic equation function.
   * ARGUMENTS:
   *   - coefs:
   *       DBL a0, a1, a2, a3;
   * RETURNS:
   *   (FLT *) array of answers.
   */
  static DBL * SolveCubic( DBL a0, DBL a1, DBL a2, DBL a3 )
  {
    static DBL Answers[3];
	Answers[0] = -Infinity;
	Answers[1] = -Infinity;
	Answers[2] = -Infinity;
	DBL a = a1 / a0, b = a2 / a0, c = a3 / a0;
	DBL Q = (a * a - 3 * b) / 9, R = (2 * a * a * a - 9 * a * b + 27 * c) / 54;
	DBL S = Q * Q * Q - R * R;
	
	if (S > 0)
	{
	  DBL phi = acos(R / (sqrt(Q * Q * Q))) / 3;
	  Answers[0] = -2 * sqrt(Q) * cos(phi) - a / 3;
	  return Answers;
	}
	
	if (S < 0)
	{
		if (Q > 0)
		{
			DBL phi = acosh(abs(R) / sqrt(Q * Q * Q)) / 3;
			Answers[0] = -2 * Sign(R) * sqrt(Q) * cosh(phi) - a / 3;
			return Answers;
		}

		else if (Q < 0)
		{
			DBL phi = asinh(abs(R) / sqrt(abs(Q * Q * Q))) / 3;
			Answers[0] = -2 * Sign(R) * sqrt(abs(Q)) * sinh(phi) - a / 3;
			return Answers;
		}

		else
		{
			Answers[0] = -pow(c - a * a * a / 27, 1.0 / 3) - a / 3;
			return Answers;
		}
	}
	else
		Answers[0] = Sign(R) * sqrt(Q) - a / 3;
	/*
	DBL p = c / a - b * b / (3 * a * a), q = (2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a);
	DBL Q = (p / 3) * (p / 3) * (p / 3) + (q / 2) * (q / 2);

	if (Q > 0)
	{
		DBL alpha = pow(-q / 2 + sqrt(Q), 1 / 3), beta = pow(-q / 2 - sqrt(Q), 1 / 3);
		Answers[0] = alpha + beta;
	}*/
	return Answers;
  }

  /* Solve quartic equation function.
   * ARGUMENTS:
   *   - coefs:
   *       DBL a0, a1, a2, a3, a4;
   * RETURNS:
   *   (FLT *) array of answers.
   */
  static DBL * SolveQuartic( DBL a0, DBL a1, DBL a2, DBL a3, DBL a4 )
  {
    static DBL Answers[4];
	Answers[0] = -Infinity;
	Answers[1] = -Infinity;
	Answers[2] = -Infinity;
	Answers[3] = -Infinity;
	DBL a = a1 / a0, b = a2 / a0, c = a3 / a0, d = a4 / a0;
	DBL p = b - (3 * a * a / 8), q = a * a * a / 8 - a * b / 2 + c, r = -3 * a * a * a * a / 256 + a * a * b / 16 - c * a / 4 + d;
	DBL s;
	DBL *A3, *A2;
	A3 = SolveCubic(2, -p, -2 * r, r * p - q * q / 4);
	s = A3[0];

	if (s == -Infinity)
		return Answers;
	if (2 * s - p >= 0)
	{
		A2 = SolveSqure(1, -sqrt(2 * s - p), q / (2 * sqrt(2 * s - p)) + s);
		Answers[0] = A2[0] - a / 4;
		Answers[1] = A2[1] - a / 4;

		A2 = SolveSqure(1, sqrt(2 * s - p), -q / (2 * sqrt(2 * s - p)) + s);
		Answers[2] = A2[0] - a / 4;
		Answers[3] = A2[1] - a / 4;
	}
	return Answers;
  }
}

#endif // __MTHDEF_H_

