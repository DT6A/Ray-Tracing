/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : RT.H
 * PURPOSE     : Ray tracing system.
 *               Scene system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 26.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "..\def.h"
#include "..\win\win.h"
//#include "render.h"
#include "scene.h"
#include "shapes\shapes.h"

namespace tart
{
  class rt : public win
  {
  private:
    rt ( VOID );
    image *Img;
  public:
    scene Scene;
    camera Cam;

    static rt & Get( VOID )
    {
      static rt RT;

      return RT;
    }

    VOID StartRender( VOID )
    {
      Scene.Render(Cam, Img, *this);
    }
    

    /* Put pixel function.
     * ARGUMENTS:
     *   - pixel coords:
     *       INT X, Y;
     *   - color:
     *       vec Color;
     * RETURNS: None.
     */
    VOID operator()( INT X, INT Y, vec Color )
    {
      Img->PutPixel(X, Y, Img->DWORDRGB(Color[0] * 255, Color[1] * 255, Color[2] * 255));
    } /* End of 'operator()' function */
    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID )
    {
      
    } /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC )
    {
      StartRender();
      Img->SaveBMP();
      Img->DrawImage();
    } /* End of 'Paint' function */

    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    VOID Activate( BOOL IsActive )
    {
    } /* End of 'Activate' function */

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID )
    {
    } /* End of 'Idle' function */
  }; /* End of 'rt' class */
} /* end of 'tart' namespace */

/* END OF 'RT.H' FILE */