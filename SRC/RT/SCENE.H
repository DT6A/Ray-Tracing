/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SCENE.H
 * PURPOSE     : Ray tracing system.
 *               Scene system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __SCENE_H_
#define __SCENE_H_

#include "..\def.h"
#include "shapes\shapes.h"
#include "light\lights.h"
#include "mtl\material.h"
#include "image.h"

namespace tart
{
  class scene
  {
  private:
    shape_list SList;                                   // Shapes list
    std::vector<light *> LList;                         // Lights list
    INT CurrentLevel, MaxLevel = 20;                    // Recursion trackers
    DBL Treshold = 0.000001, ColorTreshold = 1.0 / 256; // Tresholds
    enviroment Air;                                     // Default enviroment
    camera Cam;
  public:
    vec 
      Background = vec(0.1),           // Background color
      Ambient = vec(0.2);              // Default ambient

    /* Scene render function.
     * ARGUMENTS:
     *   - camera:
     *       camera Cam;
     *   - image to draw in:
     *       image *Img;
     * RETURNS: None.
     */
    template <class FeedBack>
      VOID Render( camera &Cam, image *Img, FeedBack &FB )
      {
        Air = enviroment(0, 1);
        this->Cam = Cam;
        for (INT ys = 0; ys < -Img->ImageH; ys++)
          for (INT xs = 0; xs < Img->ImageW; xs++)
          {
            ray R = Cam.CastRay(xs, ys);
            vec Color = Trace(R, Air, vec(1));

            CurrentLevel = 0;
            FB(xs, ys, Color);
          }
      } /* End of 'Render' function */
   
    /* Trace ray function.
     * ARGUMENTS:
     *   - ray to trace:
     *       ray R;
     * RETURNS:
     *   (vec) Color;
     */
    vec Trace( const ray &R, const enviroment &Envi, const vec &Weight )
    {
      vec Color(Background);
      intr Intr;

      if (++CurrentLevel <= MaxLevel)
      {
        if (SList.Intersect(R, Intr))
        {
          Color = Shade(R.Dir, &Intr, Envi, Weight) * exp(-Envi.Decay * Intr.T);
        }
      }
      CurrentLevel--;
      return Color;
    } /* End of 'Trace' function */

    /* Shade function.
     * ARGUMENTS:
     *   - view trace:
     *       vec V;
     *   - interseption info:
     *       intr *Intr;
     *   - enviroment info:
     *       enviroment Envi;
     *   - shade weight:
     *       vec Weight;
     * RETURNS:
     *   (vec) Color;
     */
    vec Shade( const vec &V, intr *Intr, const enviroment &Envi, const vec &Weight )
    {
      vec Color = vec(0);
      shade_data Shd(*Intr);
      DBL vn = Shd.N & V;

	  if (Intr->Shp != nullptr)
	  {
		Shd.Mtl = Intr->Shp->Mtl;
		Shd.Envi = Intr->Shp->Envi;
	  }
      /* processing mods */
       for (auto M : Shd.Modes)
         M->Apply(Shd);

      if (vn > 0)
      {
        vn = -vn;
        Shd.N = -Shd.N;
        Shd.IsEnter = !Shd.IsEnter;
      }

      vec R = V - Intr->N * (2 * vn);

      Color += Ambient * Shd.Mtl.Ka;

      for (auto Lig : LList)
      {
        light_attenuation Att;

        if (Lig->GetData(Att, Shd))
        {
          intr_list il;

          if (SList.AllIntersect(ray(Shd.P + Att.L * Treshold, Att.L), il) > 0)
            for (auto &i : il)
              if (i.T < Att.Dist)
                Att.Color = Att.Color * i.Shp->Mtl.Ktrans;

          
            Att.Color = Att.Color * (1.0 / (Att.Cc + Att.Cl * Att.Dist + Att.Cq * Att.Dist * Att.Dist));

          if (Att.Color < vec(Treshold))
            continue;

            DBL nl = Shd.N & Att.L;

            if (nl > Treshold)
            {
              Color += Shd.Mtl.Kd * Att.Color * nl;

              DBL rl = R & Att.L;

              if (rl > Treshold)
                Color += Shd.Mtl.Ks * Att.Color * pow(rl, Shd.Mtl.Ph);
            }
          }
        }

      vec wr  = vec(Weight * Shd.Mtl.Kref);
      if (vec(ColorTreshold) < wr)
        Color += Trace(ray(Shd.P + R * Treshold, R), Envi, wr);

      vec wt = Weight * Shd.Mtl.Ktrans;

      if (vec(ColorTreshold) < wt)
      {
        DBL Eta = Shd.IsEnter ? Shd.Envi.Refr / Envi.Refr : Air.Refr / Envi.Refr;
        DBL coef = 1 - (1 - vn * vn) * Eta * Eta;

        if (coef > Treshold)
        {
          vec T = (V - Shd.N * vn) * Eta - Shd.N * sqrt(coef);

          Color += Trace(ray(Shd.P + T * Treshold, T), Shd.IsEnter ? Shd.Envi : Air, wt * Shd.Mtl.Ktrans);
        }
      } 

      return vec::Clamp(Color, 0.0, 1.0);
    }

    /* Add shape to list function.
     * ARGUMENTS:
     *   - new shape:
     *       shape *S;
     * RETURNS: None.
     */
    VOID AddShape( shape *S )
    {
      SList.Shapes.push_back(S);
    } /* End of 'AddShape' function */

    /* Add shape to list function.
     * ARGUMENTS:
     *   - new shape:
     *       shape *S;
     * RETURNS: None.
     */
    scene & operator<<( shape *S )
    {
      SList.Shapes.push_back(S);
      return *this;
    } /* End of 'operator<<' function */

    /* Add light to list function.
     * ARGUMENTS:
     *   - new light:
     *       light *L;
     * RETURNS: None.
     */
    VOID AddLight( light *L )
    {
      LList.push_back(L);
    } /* End of 'AddShape' function */

    /* Add shape to list function.
     * ARGUMENTS:
     *   - new light:
     *       light *L;
     * RETURNS: None.
     */
    scene & operator<<( light *L )
    {
      LList.push_back(L);
      return *this;
    } /* End of 'operator<<' function */

    ~scene( VOID )
    {

    }
  };
} /* end of 'tart' namespace */

#endif // __SCENE_H_


/* END OF 'SCENE.H' FILE */