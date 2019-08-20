/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : WIN.H
 * PURPOSE     : Ray tracing system.
 *               Windows support system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "..\def.h"

namespace tart
{
  class win
  {
  protected :
    HWND hWnd;           // window handle
    INT W, H;            // windwo size
    HINSTANCE hInstance; // application handle

  private:
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
      WPARAM wParam, LPARAM lParam );
    BOOL IsInit = TRUE;

  public:
    BOOL IsActive, IsFullScreen;

    win( HINSTANCE hInst = GetModuleHandle(NULL) );
    ~win( VOID );

    VOID Run( VOID );
    VOID FlipFullScreen( BOOL IsFullScreen );

    // message cracks
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );
    BOOL OnCreate( CREATESTRUCT *CS )
    {
      SetTimer(hWnd, 30, 10, NULL);
      return TRUE;
    }
    VOID OnSize( UINT State, INT W, INT H )
    {
      this->W = W;
      this->H = H;
    }
    VOID OnTimer( INT Id )
    {
      if (!IsInit)
        IsInit = TRUE; 
      Timer();
    }
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
    {

    }
    BOOL OnEraseBackground( HDC hDC )
    {
       return FALSE;
    }
    VOID OnPaint( VOID )
    {
      HDC hDC;
      PAINTSTRUCT ps;

      hDC = BeginPaint(hWnd, &ps);
      if (IsInit)
        Paint(hDC);
      EndPaint(hWnd, &ps); 
    }
    VOID OnClose( VOID )
    {
      PostMessage(hWnd, WM_DESTROY, 0, 0);
    }
    VOID OnDestroy( VOID )
    {

    }
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

    /***
    * Virtual functions for window customization
    ***/

   /* Initialization function.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    virtual VOID Activate( BOOL IsActive )
    {
    } /* End of 'Activate' function */

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */
  }; /* End of 'win' class */
} /* end of 'tart' namspace */

/* END OF 'WIN.H' FILE */