/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMAGE.H
 * PURPOSE     : Ray tracing system.
 *               Image system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 25.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef _IMG_H
#define _IMG_H


#include "..\def.h"

namespace tart
{
  class image
  {
  public:
    HWND hWnd;             // Window handle
    HDC hMemDc;            // Context
    HBITMAP hBm;           // Bitmap
    BITMAPINFOHEADER bmih; // Bitmap header
    DWORD *Bits;           // Bitmap data
    INT ImageW, ImageH;    // Image size

    image( const HWND &hWorkWnd );

    VOID DrawImage( VOID );
    VOID PutPixel( const INT X, const INT Y, const DWORD Color );
    VOID SaveBMP( VOID );

    /* Convert components function.
    * ARGUMENTS:
    *   - color components:
    *       INT r, g, b;
    * RETURNS:
    *   (DWORD) color.
    */
    static DWORD DWORDRGB( INT r, INT g, INT b )
    {
      return (DWORD)((r << 16) | (g << 8) | b);
    } /* End of 'DWORDRGB' function */
  }; /* End of 'image' class */

} /* end of 'tart' namespace */

#endif // _IMG_H

/* END OF 'IMAGE.H' FILE */