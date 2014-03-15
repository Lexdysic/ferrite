
#include "System/SysPch.h"

using namespace Gdiplus;

namespace System {

//=============================================================================
Surface::Surface(uint width, uint height) :
    mBitmap(width, height, PixelFormat32bppARGB)
{
}

//=============================================================================
Surface::~Surface()
{
}

////=============================================================================
//void Surface::DrawPixel(uint32 x, uint32 y)
//{
//  x, y;
//}
//
////=============================================================================
//void Surface::DrawSurface(const ISurface * surface, uint32 dX, uint32 dY)
//{
//  const CSurface & src = *(CSurface *)surface;
//
//  Graphics g(&mBitmap);
//  g.DrawImage(
//      &src.mBitmap, 
//      dX, dY,
//      0, 0,
//      src.GetWidth(), src.GetHeight(), 
//      UnitPixel
//  );
//}
//
////=============================================================================
//void Surface::DrawSurface(const ISurface * surface, uint32 dX, uint32 dY, uint32 sX, uint32 sY, uint32 width, uint32 height)
//{
//  const Surface & src = *(Surface *)surface;
//
//  Graphics g(&mBitmap);
//  g.DrawImage(
//      &src.mBitmap,
//      (INT)dX, dY,
//      sX, sY,
//      width, height,
//      UnitPixel
//  );
//}

} // namespace System;

//=============================================================================
void NormalBlit(Bitmap & srcBmp,uint32 destX, uint32 destY, Graphics & gDest)
{
    HBITMAP srcBitmap;
    if( srcBmp.GetHBITMAP(Color(255, 255, 255), &srcBitmap) != Gdiplus::Ok )
        return;

    const HDC destDc = gDest.GetHDC();
    const HDC srcDc = CreateCompatibleDC(destDc);

    SelectObject(srcDc, (HGDIOBJ)srcBitmap);

    const uint32 srcWidth  = srcBmp.GetWidth();
    const uint32 srcHeight = srcBmp.GetHeight();

    BOOL rv = BitBlt(
        destDc, 
        destX, destY, 
        srcWidth, srcHeight, 
        srcDc, 
        0, 0,
        SRCCOPY
    );

    if( !rv ) {
        DWORD error = GetLastError();
        assert(false);
    }

    DeleteObject((HGDIOBJ)srcBitmap);
    DeleteDC(srcDc);
    gDest.ReleaseHDC(destDc);
}

//=============================================================================
void FastBlit(Bitmap & srcBmp, Gdiplus::Rect destRect, Graphics & gDest)
{
    HBITMAP srcBitmap;
    if( srcBmp.GetHBITMAP(Color(255, 255, 255), &srcBitmap) != Gdiplus::Ok )
        return;

    const HDC destDc = gDest.GetHDC();
    const HDC srcDc = CreateCompatibleDC(destDc);

    SelectObject(srcDc, (HGDIOBJ)srcBitmap);

    const uint32 srcWidth  = srcBmp.GetWidth();
    const uint32 srcHeight = srcBmp.GetHeight();

    SetStretchBltMode(destDc, STRETCH_HALFTONE);

    StretchBlt(
        destDc, 
        destRect.X, destRect.Y, 
        destRect.Width, destRect.Height, 
        srcDc, 
        0, 0, 
        srcWidth, srcHeight, 
        SRCCOPY
    );

    DeleteObject((HGDIOBJ)srcBitmap);
    DeleteDC(srcDc);
    gDest.ReleaseHDC(destDc);
}

//=============================================================================
void FastBlit(Bitmap & srcBmp, uint32 destX, uint32 destY, uint32 destWidth, uint32 destHeight, Graphics & gDest)
{
    FastBlit(srcBmp, Gdiplus::Rect(destX, destY, destWidth, destHeight), gDest);
}

//=============================================================================
void SlowBlit(Bitmap & srcBmp, Gdiplus::Rect destRect, Graphics & gDest)
{
    gDest.DrawImage(&srcBmp, destRect);
}
