/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : CAMERA.H
 * PURPOSE     : Ray tracing system.
 *               Base defenitions.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 24.07.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __DEF_H_
#define __DEF_H_

//#include "Z:\T05ANIM\stdafx.h"

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

#define GLEW_STATIC

#pragma warning (disable: 4305 4244)

#include "mth/mth.h"

namespace tart
{
  typedef mth::vec<DBL> vec;
  typedef mth::vec2<DBL> vec2;
  typedef mth::vec4<DBL> vec4;
  typedef mth::matr<DBL> matr;
  typedef mth::camera<DBL> camera;
  typedef mth::ray<DBL> ray;
}

static class __Dummy
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __MemAlocSupport;

#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

#endif // __DEF_H_

/* END OF 'DEF.H' FILE */
