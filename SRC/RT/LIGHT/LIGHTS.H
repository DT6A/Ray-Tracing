/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : LIGHTS.H
 * PURPOSE     : Ray tracing system.
 *               Lights system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 27.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __LIGTH_H_
#define __LIGTH_H_

#include "..\..\def.h"
#include "..\shapes\intersection.h"

namespace tart
{
  class light_attenuation
  {
  public:
    vec L;    // Direction to light source
    DBL Dist; // Distance to light source
    DBL Cc = 1, Cl = 1, Cq = 1; // Light coefitients
    vec Color = vec(1);         // Light color

    /* point_light constructor function.
     * ARGUMENTS:
     *   - light:
     *       light Light;
     * RETURNS: None.
     */
 /*`   light_attenuation ( const light &Light )
    {


      L = Light.GetL();
      Dir = Light.GetDist();
    } /* End of 'light_attenuation ' constructor */

  }; /* End of 'light_attenuation' class */

  class light
  {
  public:
    DBL Cc = 1, Cl = 1, Cq = 1; // Light coefitients
    vec Color = vec(1);         // Light color

    /* Get direction to light function.
     * ARGUMENTS:
     *   - point to get direction from:
     *       vec P;
     * RETURNS:
     *   (vec) direction to light;
     */
    virtual vec GetL( const vec &P )
    {
      return vec(0);
    } /* End of 'GetL' function */
    /* Get distance to light function.
     * ARGUMENTS:
     *   - point to get distance from:
     *       vec P;
     * RETURNS:
     *   (DBL) distance to light;
     */
    virtual DBL GetDist( const vec &P )
    {
      return 3;
    } /* End of 'GetDist' function */

    /* Get light data function.
     * ARGUMENTS:
     *   - light attenuation:
     *       light_attenuation &Att;
     *   - shading data:
     *       const shade_data &Shd;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise;
     */
    BOOL GetData( light_attenuation &Att, const shade_data &Shd )
    {
      Att.Cc = Cc;
      Att.Cl = Cl;
      Att.Cq = Cq;
      Att.Color = Color;
      Att.L = GetL(Shd.P);
      Att.Dist = GetDist(Shd.P);

      return TRUE;
    } /* End of 'GetData' function */

  }; /* End of 'light' class */

  class point_light : public light
  {
  public:
    vec Loc; // Light location

    /* point_light constructor function
     * ARGUMENTS:
     *   - location:
     *       vec L;
     * RETURNS: None.
     */
    point_light( const vec &L ) : Loc(L)
    {
    
    } /* End of 'point_light' constructor */

    /* point_light constructor function
     * ARGUMENTS:
     *   - location:
     *       vec L;
     *   - color:
     *       vec C;
     *   - light coefs:
     *       DBL CC, CL, CQ;
     * RETURNS: None.
     */
    point_light( const vec &L, const vec &C, const DBL CC, const DBL CL, const DBL CQ ) : Loc(L)
    {
      Color = C;
      Cc = CC;
      Cl = CL;
      Cq = CQ;
    } /* End of 'point_light' constructor */

    /* Get direction to light function
     * ARGUMENTS:
     *   - point to get direction from:
     *       vec P;
     * RETURNS:
     *   (vec) direction to light;
     */
    vec GetL( const vec &P ) override
    {
      return (Loc - P).Normalize();
    } /* End of 'GetL' function */

    /* Get distance to light function
     * ARGUMENTS:
     *   - point to get distance from:
     *       vec P;
     * RETURNS:
     *   (DBL) distance to light;
     */
    DBL GetDist( const vec &P ) override
    {
      return Loc.Distance(P);
    } /* End of 'GetDist' function */

  }; /* End of 'point_light' class */

  class dir_light : public light
  {
  public:
    vec Dir; // Light direction

    /* dir_light constructor function
     * ARGUMENTS:
     *   - direction:
     *       vec D;
     * RETURNS: None.
     */
    dir_light( const vec &D ) : Dir(D)
    {

    } /* End of 'dir_light' constructor */

    /* dir_light constructor function
     * ARGUMENTS:
     *   - direction:
     *       vec D;
     *   - color:
     *       vec C;
     *   - light coefs:
     *       DBL CC, CL, CQ;
     * RETURNS: None.
     */
    dir_light( const vec &D, const vec &C, const DBL CC, const DBL CL, const DBL CQ ) : Dir(D)
    {
      Color = C;
      Cc = CC;
      Cl = CL;
      Cq = CQ;
    } /* End of 'dir_light' constructor */

    /* Get direction to light function
     * ARGUMENTS:
     *   - point to get direction from:
     *       vec P;
     * RETURNS:
     *   (vec) direction to light;
     */
    vec GetL( const vec &P ) override
    {
      return -(Dir.Normalize());
    } /* End of 'GetL' function */

  }; /* End of 'dir_light' class */

} /* end of 'tart' namespace */

#endif // __LIGTH_H_


/* END OF 'LIGHTS.H' FILE */