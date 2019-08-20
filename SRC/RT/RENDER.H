/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RENDER.H
 * PURPOSE     : Ray tracing system.
 *               Render system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "..\def.h"
#include "image.h"

namespace tart
{
  class render
  {
  private:
    HWND hWnd;             // Window handle
    INT WinW, WinH;        // Window size
    image *Img;            // Image with frame


  public:
    camera Cam;

    render( const HWND &hWorkWnd, const INT W, const INT H );
    ~render( VOID )
    {
      delete Img;
    }

    VOID Start( VOID );
    
  }; /* End of 'render' class */
} /* end of 'tart' namespace */

/* END OF 'RENDER.H' FILE */