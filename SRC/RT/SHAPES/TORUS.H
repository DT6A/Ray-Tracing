/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : TORUS.H
 * PURPOSE     : Ray tracing system.
 *               Torus shape class.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 27.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __TORUS_H_
#define __TORUS_H_


#include "..\..\def.h"
#include "shape.h"
#include <alg.h>

namespace tart
{
  class torus : public shape
  {
  public:
   // vec C;     // Sphere center
    DBL R, // Iner radius
		r; // Outer radius

    /* sphere constructor function.
     * ARGUMENTS:
     *   - sphrere center:
     *       vec Center;
     *   - sphere radius:
     *       DBL Radius;
     * RETURNS: None.
     */
    torus( const DBL RI, const DBL RO ) : R(RI), r(RO)
    {

    } /* End of 'sphere' constructor */


    /* Torus intersect function.
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
	  DBL G = 4 * R * R * (Ray.Dir[0] * Ray.Dir[0] + Ray.Dir[1] * Ray.Dir[1]),
	    H = 8 * R * R * (Ray.Org[0] * Ray.Dir[0] + Ray.Org[1] * Ray.Dir[1]),
		I = 4 * R * R * (Ray.Org[0] * Ray.Org[0] + Ray.Org[1] * Ray.Org[1]),
		J = Ray.Dir & Ray.Dir,
		K = 2 * (Ray.Dir & Ray.Org),
		L = (Ray.Org & Ray.Org) + R * R - r * r;
	  DBL *A4, Root = mth::Infinity;
	  
	  A4 = mth::SolveQuartic(J * J, 
		  2 * J * K, 
		  2 * (Ray.Dir & Ray.Dir) * ((Ray.Org & Ray.Org) - r * r - R * R) + K * K + 4 * R * R * Ray.Dir[1] * Ray.Dir[1],
		  2 * ((Ray.Org & Ray.Org) - r * r - R * R) * K + 8 * R * R * Ray.Org[1] * Ray.Dir[1],
		  ((Ray.Org & Ray.Org) - r * r - R * R) * ((Ray.Org & Ray.Org) - r * r - R * R) - 4 * R * R * (r * r - Ray.Org[1] * Ray.Org[1]));
	  //A4 = mth::SolveQuartic(J * J, 2 * J * K, 2 * J * L + K * K - G, 2 * K * L - H, L * L - I);
	 
	  for (INT i = 0; i < 4; i++)
		  Root = (Root > A4[i] && A4[i] > 0) ? A4[i] : Root;
	  if (Root < 0 || Root == mth::Infinity)
  	    return FALSE;

	  Inter.T = Root;
	  vec P = Ray(Inter.T),
		  P1 = vec(P[0], 0, P[2]);
	  Inter.Shp = (shape *)this;
	  Inter.IsEnter = TRUE;
	  Inter.P = P;
	  Inter.IsP = TRUE;
	  Inter.N = (P - (P1 * (R / !P1))).Normalize();
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
		DBL G = 4 * R * R * (Ray.Dir[0] * Ray.Dir[0] + Ray.Dir[1] * Ray.Dir[1]),
			H = 8 * R * R * (Ray.Org[0] * Ray.Dir[0] + Ray.Org[1] * Ray.Dir[1]),
			I = 4 * R * R * (Ray.Org[0] * Ray.Org[0] + Ray.Org[1] * Ray.Org[1]),
			J = (Ray.Dir & Ray.Dir),
			K = 2 * (Ray.Dir & Ray.Org),
			L = (Ray.Org & Ray.Org) + R * R - r * r;
		DBL *A4, Root = mth::Infinity;

		A4 = mth::SolveQuartic(J * J,
			2 * J * K,
			2 * (Ray.Dir & Ray.Dir) * ((Ray.Org & Ray.Org) - r * r - R * R) + K * K + 4 * R * R * Ray.Dir[1] * Ray.Dir[1],
			2 * ((Ray.Org & Ray.Org) - r * r - R * R) * K + 8 * R * R * Ray.Org[1] * Ray.Dir[1],
			((Ray.Org & Ray.Org) - r * r - R * R) * ((Ray.Org & Ray.Org) - r * r - R * R) - 4 * R * R * (r * r - Ray.Org[1] * Ray.Org[1]));
		//A4 = mth::SolveQuartic(J * J, 2 * J * K, 2 * J * L + K * K - G, 2 * K * L - H, L * L - I);
		
		for (INT i = 0; i < 4; i++)
			Root = (Root > A4[i] && A4[i] > 0) ? A4[i] : Root;
		if (Root < 0 || abs(Root) == mth::Infinity)
			return 0;
		
		intr Inter;
		Inter.T = Root;
		vec P = Ray(Inter.T),
			P1 = vec(P[0], 0, P[2]);
		Inter.Shp = (shape *)this;
		Inter.IsEnter = TRUE;
		Inter.P = P;
		Inter.IsP = TRUE;
		Inter.N = (P - (P1 * (R / !P1))).Normalize();
		Inter.IsN = TRUE;
		
		InterList.push_back(Inter);
		return 1;

    } /* End of 'AllIntersect' function */
  }; /* End of 'sphere' class */
} /* end of 'tart' namespace */

#endif // __TORUS_H_

/* END OF 'TORUS.H' FILE */