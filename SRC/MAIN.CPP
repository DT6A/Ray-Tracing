/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : MAIN.CPP
 * PURPOSE     : Ray tracing system.
 *               Main file.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "def.h"
#include "rt\rt.h"

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  tart::rt &RayTracing = tart::rt::Get();

  RayTracing.Run();

  return 0x1e;
} /* End of 'WinMain' function *


/* END OF 'MAIN.CPP' FILE */