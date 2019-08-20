/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : PLANE.H
 * PURPOSE     : Ray tracing system.
 *               Plane shape class.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __PLANE_H_
#define __PLANE_H_


#include "..\..\def.h"
#include "shape.h"

namespace tart
{
  class plane : public shape
  {
  public:
    vec N;     // plane normal
    DBL D;     // distance to cs begin

    /* plane constructor function.
     * ARGUMENTS:
     *   - plane normal:
     *       vec Normal;
     *   - plane distance:
     *       DBL Dist;
     * RETURNS: None.
     */
    plane( const vec &Normal, const DBL Dist ) : N(Normal), D(Dist)
    {

    } /* End of 'plane' constructor */


    /* Plane intersect function.
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
      Inter.T = -((Ray.Org & N) - D) / (Ray.Dir & N);

      if (Inter.T < 0)
        return FALSE;

      Inter.Shp = (shape *)this;
      Inter.IsP = TRUE;
      Inter.P = Ray(Inter.T);
      Inter.IsN = TRUE;
      Inter.N = N;

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
      intr Inter;
      Inter.T = -((Ray.Org & N) - D) / (Ray.Dir & N);

      if (Inter.T < 0)
        return 0;

      Inter.Shp = (shape *)this;
      Inter.IsP = TRUE;
      Inter.P = Ray(Inter.T);
      Inter.IsN = TRUE;
      Inter.N = N;
      InterList.push_back(Inter);
      return 1;
    } /* End of 'AllIntersect' function */

  }; /* End of 'plane' class */
} /* end of 'tart' namespace */

#endif // __PLANE_H_


/* END OF 'PLANE.H' FILE */