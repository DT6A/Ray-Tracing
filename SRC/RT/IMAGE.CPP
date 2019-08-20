/***************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : IMAGE.CPP
 * PURPOSE     : Ray tracing system.
 *               Image system.
 * PROGRAMMER  : DT6.
 * LAST UPDATE : 27.08.2018.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <cstdio>
#include <ctime>
#include <string>

#include "image.h"

using namespace tart;

/* image constructor function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWorkWnd;
 * RETURNS: None.
 */
image::image( const HWND &hWorkWnd ) : hWnd(hWorkWnd)
{
  HDC hDC = GetDC(hWnd);
  hMemDc = CreateCompatibleDC(hDC);


  memset(&bmih, 0, sizeof(bmih));
  bmih.biSize = sizeof(BITMAPINFOHEADER);
  bmih.biBitCount = 32;
  bmih.biPlanes = 1;
  bmih.biCompression = BI_RGB;
  ImageW = bmih.biWidth = 1920;
  ImageH = bmih.biHeight = -1080;
  bmih.biSizeImage = ImageW * ImageH * 4;
  bmih.biClrUsed = 0;
  bmih.biClrImportant = 0;
  bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0; // resolution

  hBm = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, NULL, 0);

  for (INT i = 0; i < -ImageH; i++)
    for (INT j = 0; j < ImageW; j++)
      Bits[i * ImageW + j] = i * j + j * i * 4 + 100;
} /* End of 'image' constructor */

/* Draw bitmap image function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID image::DrawImage( VOID )
{
  BITMAP bm;
  HDC hDC = GetDC(hWnd);

  GetObject(hBm, sizeof(BITMAP), &bm);

  SelectObject(hMemDc, hBm);
  BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDc, 0, 0, SRCCOPY);
} /* End of 'DrawImage' function */


/* Save image to BMP function.
 * ARGUMENTS:  None.
 * RETURNS: None.
 */
VOID image::SaveBMP( VOID )
{
  FILE *F;
  time_t sec = time(NULL);
  tm *Time = localtime(&sec);
  CHAR Str[100];

  sprintf(Str, "result/%d_%d_%d_%d.bmp", Time->tm_hour, Time->tm_min, Time->tm_sec, Time->tm_mday);

  if ((F = fopen(Str, "wb")) == nullptr)
    return;

  UINT bpl;
  BITMAPINFOHEADER bih;
  BITMAPFILEHEADER bfh;

  bpl = (ImageW * 3 + 3) / 4 * 4;


  /* заполняем заголовки */
  bfh.bfType = 'B' | ('M' << 8);
  bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bpl * -ImageH;
  bfh.bfReserved1 = 0;
  bfh.bfReserved2 = 0;
  bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  bih.biSize = sizeof(BITMAPINFOHEADER);
  bih.biWidth = ImageW;
  bih.biHeight = -ImageH;
  bih.biPlanes = 1;
  bih.biBitCount = 24;
  bih.biCompression = BI_RGB;
  bih.biSizeImage = bpl * -ImageH;
  bih.biClrImportant = 0;
  bih.biClrUsed = 0;
  bih.biXPelsPerMeter = bih.biYPelsPerMeter = 0;

  /* записываем в файл */
  fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, F);
  fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, F);

  BYTE *row = new BYTE[bpl];

  for (INT y = -ImageH - 1; y >= 0; y--)
  {
    for (INT x = 0; x < ImageW; x++)
    {
      row[x * 3 + 0] = Bits[y * ImageW + x] & 0xFF;
      row[x * 3 + 1] = (Bits[y * ImageW + x] >> 8) & 0xFF;
      row[x * 3 + 2] = (Bits[y * ImageW + x] >> 16) & 0xFF;
    }
    fwrite(row, 1, bpl, F);
  }

  delete[] row;
  fclose(F);
} /* End of 'SaveBMP' function */

/* Set image pixel color function.
 * ARGUMENTS:
 *   - pixel coords:
 *       INT x, y;
 *   - pixel color:
 *       DWORD Color;
 * RETURNS: None.
 */
VOID image::PutPixel( const INT X, const INT Y, const DWORD Color )
{
  Bits[Y * ImageW + X] = Color;
} /* End of 'PutPixel' function */

/* END OF 'IMAGE.CPP' FILE */