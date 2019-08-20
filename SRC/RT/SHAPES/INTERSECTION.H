/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : INTERSECTION.H
 * PURPOSE     : Ray tracing system.
 *               Plane shape class.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __INTER_H_
#define __INTER_H_

#include <vector>

#include "..\..\def.h"
#include "..\mtl\material.h"

namespace tart
{
  class shape;
  class intr
  {
  public:
    shape *Shp;   // Shape reference
    DBL T;        // Intersect distance
    BOOL IsEnter; // Is ray starts inside
    vec N;        // Normal at intersected point
    BOOL IsN;     // Is normal calculataed
    vec P;        // Intersected point
    BOOL IsP;     // Is point calculated

    //INT I[5];
    //DBL D[5];
    //vec V[5];

    /* intr constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    intr( VOID )
    {
    
    } /* End of 'intr' constructor */
    
    /* intr constructor function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     * RETURNS: None.
     */
    intr( shape *Sh, const DBL T, const BOOL IsEnter = FALSE) : Shp(Sh), T(T), IsEnter(IsEnter)
    {
    
    } /* End of 'intr' constructor */

    /* intr constructor function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     * RETURNS: None.
     */
    intr( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N ) : Shp(Sh), T(T), IsEnter(IsEnter), N(N)
    {

    } /* End of 'intr' constructor */
   
    /* intr constructor function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     *   - intersection point:
     *       vec P;
     * RETURNS: None.
     */
    intr( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N, const vec &P ) : Shp(Sh), T(T), IsEnter(IsEnter), N(N), P(P)
    {

    } /* End of 'intr' constructor */

    /* Set intersection function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     * RETURNS: None.
     */
    VOID Set( shape *Sh, const DBL T, const BOOL IsEnter = FALSE )
    {
      Shp = Sh;
      this->T = T;
      this->IsEnter = IsEnter;
    } /* End of 'Set' function */

    /* Set intersection function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     * RETURNS: None.
     */
    VOID Set( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N )
    {
      Shp = Sh;
      this->T = T;
      this->IsEnter = IsEnter;
      this->N = N;
    } /* End of 'Set' function */
   
    /* Set intersection function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     *   - intersection point:
     *       vec P;
     * RETURNS: None.
     */
    VOID Set( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N, const vec &P )
    {
      Shp = Sh;
      this->T = T;
      this->IsEnter = IsEnter;
      this->N = N;
      this->P = P;
    } /* End of 'Set' function */

  }; /* End of 'intr' class */

  typedef std::vector<intr> intr_list;

 // class shader_data : public intr
 // {
 //   material Mtl;
 //   shader_data( const intr & I )
 //   {
 //     
 //   }
 // }; /* End of 'shader_data class */

} /* end of 'tart' namespace */


#endif // __INTER_H_

/* END OF 'INTERSECTION.H' FILE */