/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MATERIAL.H
 * PURPOSE     : Ray tracing system.
 *               Materials system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 27.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "..\..\def.h"

namespace tart
{
  class material
  {
  public:
    vec 
      Ka,     // ambient
      Ks,     // specular
      Kd,     // diffuse
      Kref,   // reflection
      Ktrans; // transparency

    DBL Ph; // phong coef

    /* material constructor function.
     * ARGUMENTS:
     *   - material coefitients:
     *       vec Ka, Kd, Ks, Kref, Ktrans;
     *   - phong coefitient:
     *       DBL Ph;
     * RETURNS: None.
     */
    material( const vec &Ka = vec(0.6), const vec &Kd = vec(0.6), const vec &Ks = vec(0.6), const DBL Ph = 10,
              const vec &Kref = vec(0.5), const vec Ktrans = vec(0.6)) : Ka(Ka), Kd(Kd), Ks(Ks), Ph(Ph), Kref(Kref), Ktrans(Ktrans)
    {
    
    } /* End of 'material' constructor function */
  }; /* End of 'material' class */

  class enviroment
  {
  public:
    DBL Decay, Refr; // Enviroment 

    /* enviroment constructor function.
     * ARGUMENTS:
     *   - decay:
     *       vec Dec;
     *   - refraction:
     *       DBL Re;
     * RETURNS: None.
     */
    enviroment( const DBL Dec = 0, const DBL Re = 1 ) : Decay(Dec), Refr(Re)
    {
    
    } /* End of 'enviroment' constructor */
  }; /* End of 'enviroment' class */
} /* end of 'tart' namespace */

#endif // __MATERIAL_H_

/* END OF 'MATERIAL.H' FILE */