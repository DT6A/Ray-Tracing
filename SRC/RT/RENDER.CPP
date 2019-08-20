/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RENDER.CPP
 * PURPOSE     : Ray tracing system.
 *               Render system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "render.h"
#include "shapes\shapes.h"

using namespace tart;

/* rt constructor function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWorkWnd;
 *   - window size:
 *       INT W, H;
 * RETURNS: None.
 */
render::render( const HWND &hWorkWnd, const INT W, const INT H ) : hWnd(hWorkWnd)
{
  
} /* End of 'render' constructor */

/* END OF 'RENDER.CPP' FILE */