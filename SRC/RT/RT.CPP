/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : SCENE.H
 * PURPOSE     : Ray tracing system.
 *               Scene system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "rt.h"

using namespace tart;

/* rt constructor function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
rt::rt ( VOID ) : win()
{
  material DefM, PlM;
  enviroment DefE;
  torus *T = new torus(2, 0.7);
  sphere *Sph = new sphere(vec(0, 1, -4), 1);
  sphere *Sph1 = new sphere(vec(2, 1, 2), 1);
  sphere *Sph2 = new sphere(vec(3, 1, 0), 1);
  sphere *Sph3 = new sphere(vec(-2, 1, 4), 1);
  box *Box = new box(vec(-3, 0, -3), vec(-1, 2, -1));
  cuadric *Cuad = new cuadric(1, 0., 0., 0, 0.25, 0.1, 0., 0.1, 1, 0.4);
  plane *Pl = new plane(vec(0, 1, 0), -1);

  // 255 205 148
  DefE.Decay = 0.1;
  DefE.Refr = 0.979;
  DefM.Ka = vec(0);
  DefM.Kd = vec(0);//vec(255 / 255.0, 205 / 255.0, 148 / 255.0);
  DefM.Ks = vec(0.0);
  DefM.Ph = 10;
  DefM.Kref = vec(1);
  DefM.Ktrans = vec(0);
  Sph->Mtl = DefM;
  Sph->Envi = DefE;
  Box->Mtl = DefM;
  DefM.Ka = vec(1);
  DefM.Ph = 100;
  DefM.Kd = vec(0.5);//vec(255 / 255.0, 205 / 255.0, 148 / 255.0);
  DefM.Ks = vec(0.02);
  DefM.Ktrans = vec(0);
  DefM.Kref = vec(0);
  Pl->Mtl = DefM;
  Pl->Envi = DefE;
  DefM.Ka = vec(0.3);
  DefM.Kd = vec(0.8, 0.8, 0);//vec(255 / 255.0, 205 / 255.0, 148 / 255.0);
  DefM.Ks = vec(0.3);
  DefM.Ph = 100;
  DefM.Kref = vec(0);
  DefM.Ktrans = vec(0);
  Sph1->Mtl = DefM;
  Sph1->Envi = DefE;
  Cuad->Envi = DefE;
  Cuad->Mtl = DefM;
  T->Envi = DefE;
  DefM.Kd = vec(0, 0.0, 0);//vec(255 / 255.0, 205 / 255.0, 148 / 255.0);
  Sph2->Mtl = DefM;
  Sph2->Envi = DefE;
  DefM.Kd = vec(0, 0, 0.8);//vec(255 / 255.0, 205 / 255.0, 148 / 255.0);
  T->Mtl = material(vec(0.4), vec(0, 1), vec(0.5), 10, vec(0.6), vec(0));
  Cuad->Mtl = material(vec(0.2), vec(0, 1, 0), vec(1), 100, vec(0.7), vec(0.0));
  Sph3->Mtl = DefM;
  Box->Envi = DefE;
  Sph3->Envi = DefE;

  Pl->Modes.push_back(new mode_checker());

  Scene /*<< Sph/* << Sph1 << Sph2 << Sph3*/ << Pl << Cuad /*<< Box*/ << T /*<< new dir_light(vec(0, -1, 0), vec(1), 0.001, 0.001, 0.001)*/ << 
    new point_light(vec(7, 50, 4), vec(1), 0.001, 0.001, 0.001);// << new point_light(vec(0, 10, -5), vec(1), 0.001, 0.001, 0.001);// <<
    //new point_light(vec(-7, 5, -4), vec(0, 0, 0), 0.001, 0.001, 0.001) << new point_light(vec(10, 0, 0), vec(0, 0, 1), 0.001, 0.001, 0.001);// << 
    //new point_light(vec(5, 2, 1), vec(0, 1, 0), 0.01, 0.01, 0.01);
    
  Img = new image(win::hWnd);

  Cam = camera();
  Cam.Loc = vec(-8 * 2, 10, 10 * 2);
  Cam.At = vec(0);
  Cam.Up = vec(0, 1, 0);
  Cam.UpdateView();
  Cam.ProjSize = 1;
  Cam.Near = 1;
  Cam.SetRayTracing(Img->ImageW, -Img->ImageH);
} /* End of 'rt' constructor */

/* END OF 'RT.CPP' FILE */