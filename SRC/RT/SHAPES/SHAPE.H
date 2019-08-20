/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SHAPE.H
 * PURPOSE     : Ray tracing system.
 *               Base shape class.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 27.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __SHAPE_H_
#define __SHAPE_H_

#include "..\..\def.h"
#include "intersection.h"
#include "..\mtl\material.h"

namespace tart
{
 
  class mode;

  class shape
  {
  public:
    material Mtl;
    enviroment Envi;
    std::vector<mode *> Modes;
    /* Shape intersect function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersection:
     *       intr inter;
     * RETURNS:
     *   (BOOL) TRUE if intersection is succesful, FALSE otherwise.
     */
    virtual BOOL Intersect( const ray &Ray, intr &Inter ) const
    {
      return FALSE;
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
    virtual INT AllIntersect( const ray &Ray, intr_list &InterList ) const
    {
      return 0;
    } /* End of 'AllIntersect' function */

  }; /* End of 'shape' class */

  class shape_list : public shape
  {
  public:
    std::vector<shape *> Shapes;

    /* Evaluate all intersects function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersections:
     *       intr Inter;
     * RETURNS:
     *   (BOOL) TRUE if intersection is succesful, FALSE otherwise.
     */
    BOOL Intersect( const ray &Ray, intr &Inter ) const
    {
      Inter.T = mth::Infinity;
      BOOL Flag = FALSE;
      for (auto S : Shapes)
      {
        intr I;

        if (S->Intersect(Ray, I))
        {
          if (I.T < Inter.T)
          {
            Inter.Set(I.Shp, I.T, I.IsEnter, I.N, I.P);
            Inter.IsN = I.IsN;
            Inter.IsP = I.IsP;
          }
          Flag = TRUE;
        }
      }
      return Flag;
    } /* End of 'Intersect' function */

    /* Evaluate all intersects function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersections list:
     *       intr_list InterList;
     * RETURNS:
     *   (INT) amount of intersections.
     */
    INT AllIntersect( const ray &Ray, intr_list &InterList ) const
    {
      INT Count = 0;

      for (auto S : Shapes)
        Count += S->AllIntersect(Ray, InterList);

      return Count;
    } /* End of 'AllIntersect' function */
  }; /* End of 'shape_list' class */

  class shade_data : public intr 
  {
  public:
    material Mtl;
    enviroment Envi;
    std::vector<mode *> Modes;
    /* shade_data construcor function.
    * ARGUMENTS:
    *   - intersection:
    *       intr Intr;
    * RETURNS: None.
    */
    shade_data( const intr &Intr )
    {
      Shp = Intr.Shp;
      T = Intr.T;
      IsEnter = Intr.IsEnter;
      N = Intr.N;
      IsN  = Intr.IsN;
      P = Intr.P;
      IsP = Intr.IsP;
	  if (Intr.Shp != 0)
	  { 
	    Mtl = Intr.Shp->Mtl;
        Envi = Intr.Shp->Envi;
        Modes = Intr.Shp->Modes; 
	  } 
    } /* End of 'shade_data' constructor */
  }; /* End 'shade_data' class */

  class mode
  {
  public:
    shape *Shp; // Shape reference
    /* Apply mode function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Apply( shade_data &Shd ) const
    {
      
    } /* End of 'Apply' fucntion */
  }; /* End of 'mode' class */

  class mode_checker : public mode
  {
  public:
    /* Apply mode function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( shade_data &Shd ) const override
    {
      if (INT(abs(floor(Shd.P[0]))) % 2 == INT(abs(floor(Shd.P[2]))) % 2)
        Shd.Mtl.Kd = vec(0);
      else
        Shd.Mtl.Kd = vec(1);
    } /* End of 'Apply' fucntion */
  }; /* End of 'mode_checker' class */

} /* end of 'tart' namespace */

#endif // __SHAPE_H_

/* END OF 'SHAPE.H' FILE */