/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : CUADRATIC.H
 * PURPOSE     : Ray tracing system.
 *               Sphere shape class.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 04.09.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __CUADRATIC_H_
#define __CUADRATIC_H_


#include "..\..\def.h"
#include "shape.h"

namespace tart
{
  class cuadric : public shape
  {
  public:
    DBL A, B, C, D, E, F, G, H, I, J; // Figure coefs

    /* sphere constructor function.
     * ARGUMENTS:
     *   - sphrere center:
     *       vec Center;
     *   - sphere radius:
     *       DBL Radius;
     * RETURNS: None.
     */
    cuadric( const DBL A, const DBL B, const DBL C, const DBL D, const DBL E, 
         const DBL F, const DBL G, const DBL H, const DBL I, const DBL J) : A(A), B(B), C(C), D(D), E(E), 
                                                                            F(F), G(G), H(H), I(I), J(J)
    {

    } /* End of 'sphere' constructor */


    /* Sphere intersect function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersection:
     *       intr Inter;
     * RETURNS:
     *   (BOOL) TRUE if intersection is succesful, FALSE otherwise.
     */
    BOOL Intersect( const ray &Ray, intr &Inter ) const override
    {
      DBL a, b, c, x1, x2, t = -1, x, y, z;
	  DBL Dx = Ray.Dir[0], Dy = Ray.Dir[1], Dz = Ray.Dir[2],
          Ox = Ray.Org[0], Oy = Ray.Org[1], Oz = Ray.Org[2];

      a = A * Dx * Dx + 2 * B * Dx * Dy + 2 * C * Dx * Dz +
        E * Dy * Dy + 2 * F * Dy * Dz + H * Dz * Dz;
      b = 2 * ((A * Dx * Ox + B * (Dy * Ox + Dx * Oy)) +
        C * (Dz * Ox + Dx * Oz) + D * Dx + E * Dy * Oy +
        F * (Dz * Oy + Dy * Oz) + G * Dy + H * Dz * Oz +
        I * Dz);
      c = A * Ox * Ox + 2 * B * Ox * Oy + 2 * C * Ox * Oz +
        2 * D * Ox + 2 * G * Oy +
        E * Oy * Oy + 2 * F * Oy * Oz + H * Oz * Oz + 2 * I * Oz + J;
    
      DBL Dis2 = b * b - 4 * a * c;
      if (Dis2 < 0)
        return FALSE;
      DBL Dis = sqrt(b * b - 4 * a * c);
      x1 = (-b + Dis) / (2 * a);
      x2 = (-b - Dis) / (2 * a);
      if (x1 > 0 && x2 > 0)
        t = x1 > x2 ? x2 : x1;
      else if (x1 > 0 && x2 < 0)
        t = x1;
      else if (x1 < 0 && x2 > 0)
        t = x2;
      else
        return FALSE;
	  
      Inter.Shp = (shape *)this;
      Inter.T = t;
      Inter.IsEnter = TRUE;
      Inter.P = Ray(Inter.T);
      Inter.IsP = TRUE;
      // f(x, y, z) = A * Inter.P[0] * Inter.P[0] + 2 * B * Inter.P[0] * Inter.P[1] + 2 * C * Inter.P[0] * Inter.P[2] + 2 * D * Inter.P[0] +
      //              + E * Inter.P[1] * Inter.P[1] + 2 * F * Inter.P[1] * Inter.P[2] + 2 * G * Inter.P[1] +
      //              + H * Inter.P[2] * Inter.P[2] + 2 * I * Inter.P[2] + J
	  x = 2 * A * Inter.P[0] + 2 * B * Inter.P[1] + 2 * C * Inter.P[2] + 2 * D;
	  y = 2 * B * Inter.P[0] + 2 * E * Inter.P[1] + 2 * F * Inter.P[2] + 2 * G;
      z = 2 * C * Inter.P[0] + 2 * F * Inter.P[1] + 2 * H * Inter.P[2] + 2 * I;
      Inter.N = vec(x, y, z).Normalize();
	  Inter.IsN = TRUE;
      return TRUE;
    } /* End of 'Intersect' function */

    /* Evaluate all intersections function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersections:
     *       intr inter;
     * RETURNS:
     *   (INT) amount of intersections.
     */
    INT AllIntersect( const ray &Ray, intr_list &InterList ) const override
    {
      DBL a, b, c, x1, x2, t, x, y, z;
	  DBL Dx = Ray.Dir[0], Dy = Ray.Dir[1], Dz = Ray.Dir[2],
          Ox = Ray.Org[0], Oy = Ray.Org[1], Oz = Ray.Org[2];

      a = A * Dx * Dx + 2 * B * Dx * Dy + 2 * C * Dx * Dz +
        E * Dy * Dy + 2 * F * Dy * Dz + H * Dz * Dz;
      b = 2 * ((A * Dx * Ox + B * (Dy * Ox + Dx * Oy)) +
        C * (Dz * Ox + Dx * Oz) + D * Dx + E * Dy * Oy +
        F * (Dz * Oy + Dy * Oz) + G * Dy + H * Dz * Oz +
        I * Dz);
      c = A * Ox * Ox + 2 * B * Ox * Oy + 2 * C * Ox * Oz +
        2 * D * Ox + 2 * G * Oy +
        E * Oy * Oy + 2 * F * Oy * Oz + H * Oz * Oz + 2 * I * Oz + J;

      DBL Dis2 = b * b - 4 * a * c;

      if (Dis2 < 0)
        return 0;
      DBL Dis = sqrt(b * b - 4 * a * c);
      x1 = (-b + Dis) / (2 * a);
      x2 = (-b - Dis) / (2 * a);
      if (x1 > x2)
        t = x1;
      else
        t = x2;
	  
      if (t < 0)
        return 0;
	  
	  INT count = 0;

      intr Inter;
      if (x1 >= 0)
      {
        Inter.Shp = (shape *)this;
        Inter.T = x1;
        Inter.IsEnter = (x1 < x2);
        Inter.P = Ray(Inter.T);
        x = 2 * A * Inter.P[0] + 2 * B * Inter.P[1] + 2 * C * Inter.P[2] + 2 * D;
        y = 2 * B * Inter.P[0] + 2 * E * Inter.P[1] + 2 * F * Inter.P[2] + 2 * G;
        z = 2 * C * Inter.P[0] + 2 * F * Inter.P[1] + 2 * H * Inter.P[2] + 2 * I;
        Inter.N = vec(x, y, z).Normalize();
        Inter.IsP = TRUE;
        Inter.IsN = TRUE;
        InterList.push_back(Inter);
		count++;
      }
      if (x2 >= 0)
      {
        Inter.Shp = (shape *)this;
        Inter.T = x2;
        Inter.IsEnter = 1 - Inter.IsEnter;
        Inter.P = Ray(Inter.T);
        x = 2 * A * Inter.P[0] + 2 * B * Inter.P[1] + 2 * C * Inter.P[2] + 2 * D;
        y = 2 * B * Inter.P[0] + 2 * E * Inter.P[1] + 2 * F * Inter.P[2] + 2 * G;
        z = 2 * C * Inter.P[0] + 2 * F * Inter.P[1] + 2 * H * Inter.P[2] + 2 * I;
        Inter.N = vec(x, y, z).Normalize();
        Inter.IsP = TRUE;
        Inter.IsN = TRUE;
        InterList.push_back(Inter);
		count++;
      }
      return count;
    } /* End of 'AllIntersect' function */
  }; /* End of 'sphere' class */
} /* end of 'tart' namespace */

#endif // __SPH_H_

/* END OF 'SPHERE.H' FILE */