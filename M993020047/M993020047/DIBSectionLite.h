#if !defined(AFX_CDIBSECTIONLITE_H__35D9F3D4_B960_11D2_A981_2C4476000000__INCLUDED_)
#define AFX_CDIBSECTIONLITE_H__35D9F3D4_B960_11D2_A981_2C4476000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DIBSectionLite.h : header file
//

// Copyright ?Dundas Software Ltd. 1999, All Rights Reserved

// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	NO	Derived from CWnd
//	NO	Is a CWnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO 	Needs a resource (template)
//	YES	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         

// DIBSection is DIBSection wrapper class for Win32 platforms.
// This class provides a simple interface to DIBSections including loading,
// saving and displaying DIBsections.
//

// Using DIBSection :

// This class is very simple to use. The bitmap can be set using either SetBitmap()
// (which accepts either a Device dependant or device independant bitmap, or a 
// resource ID) or by using Load(), which allows an image to be loaded from disk. 
// To display the bitmap simply use Draw or Stretch.
//
// eg. 
//
//      CDIBSectionLite dibsection;
//      dibsection.Load(_T("image.bmp"));
//      dibsection.Draw(pDC, CPoint(0,0));  // pDC is of type CDC*
//
//      CDIBSectionLite dibsection;
//      dibsection.SetBitmap(IDB_BITMAP); 
//      dibsection.Draw(pDC, CPoint(0,0));  // pDC is of type CDC*
//
// The CDIBSectionLite API includes many methods to extract information about the
// image, as well as palette options for getting and setting the current palette.
//
// Author: Chris Maunder (cmaunder@dundas.com)
// Date  : 12 April 1999

#include <vfw.h>
#pragma comment(lib, "vfw32")

#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// defines

#define DS_BITMAP_FILEMARKER  ((WORD) ('M' << 8) | 'B')    // is always "BM" = 0x4D42

// �T��BYTE�����A�A�ΨӰO���C�� pixel ��B,G,R��
class BGRDATA
{
public:
	BYTE B;
	BYTE G;
	BYTE R;
	BGRDATA(){B=0;G=0;R=0;}
	BGRDATA(COLORREF var){*this = *((BGRDATA*)(&var));}
	BGRDATA(BYTE BB,BYTE GG,BYTE RR){B=BB;G=GG;R=RR;}
	// �۴�����
	inline BGRDATA operator-(BGRDATA var){return BGRDATA(abs(B-var.B),abs(R-var.R),abs(R-var.R));}
	// ������
	inline BGRDATA operator/(BGRDATA var){return BGRDATA((B+var.B)/2,(G+var.G)/2,(R+var.R)/2);}
	// B,G,R �� exp ����M
	inline double operator^(int exp){return double(pow((double)B,exp)+pow((double)G,exp)+pow((double)R,exp));}
	// �N COLORREF ���� BGRDATA
	inline BGRDATA operator=(COLORREF var){*this = *((BGRDATA*)(&var));return *this;}
	// �ন COLORREF �����A
	inline COLORREF ToCOLORREF(){return RGB(R,G,B);}
	// �Ǧ^ B,G,R �Ȫ��M
	inline int Sum(){return B+G+R;}
};

/////////////////////////////////////////////////////////////////////////////
// BITMAPINFO wrapper

struct DIBINFO : public BITMAPINFO
{
	RGBQUAD	 arColors[255];    // Color table info - adds an extra 255 entries to palette

	operator LPBITMAPINFO()          { return (LPBITMAPINFO) this; }
	operator LPBITMAPINFOHEADER()    { return &bmiHeader;          }
	RGBQUAD* ColorTable()            { return bmiColors;           }
};

/////////////////////////////////////////////////////////////////////////////
// LOGPALETTE wrapper

struct PALETTEINFO : public LOGPALETTE
{
    PALETTEENTRY arPalEntries[255];               // Palette entries

    PALETTEINFO() { palVersion = (WORD) 0x300; }

    operator LPLOGPALETTE()   { return (LPLOGPALETTE) this;            }
    operator LPPALETTEENTRY() { return (LPPALETTEENTRY) (palPalEntry); }
};


/////////////////////////////////////////////////////////////////////////////
// CDIBSectionLite object

class CDIBSectionLite : public CObject
{
// Construction
public:
	CDIBSectionLite();
	virtual ~CDIBSectionLite();
    void DeleteObject();

// static helpers
public:
    static int BytesPerLine(int nWidth, int nBitsPerPixel);
    static int NumColorEntries(int nBitsPerPixel);

    static PALETTEENTRY ms_StdColours[];
    static BOOL UsesPalette(CDC* pDC) { return (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE); }
    static BOOL CreateHalftonePalette(CPalette& palette, int nNumColours);

// Attributes
public:
    HBITMAP      GetSafeHandle() const       { return (this)? m_hBitmap : NULL;        }
    CSize        GetSize() const             { return CSize(GetWidth(), GetHeight());  }
    int          GetHeight() const           { return m_DIBinfo.bmiHeader.biHeight;    } 
    int          GetWidth() const            { return m_DIBinfo.bmiHeader.biWidth;     }
    int          GetPlanes() const           { return m_DIBinfo.bmiHeader.biPlanes;    }
    int          GetBitCount() const         { return m_DIBinfo.bmiHeader.biBitCount;  }
    LPVOID       GetDIBits()                 { return m_ppvBits;                       }
    LPBITMAPINFO GetBitmapInfo()             { return  (BITMAPINFO*) m_DIBinfo;        }
    DWORD        GetImageSize() const        { return m_DIBinfo.bmiHeader.biSizeImage; }
    LPBITMAPINFOHEADER GetBitmapInfoHeader() { return (BITMAPINFOHEADER*) m_DIBinfo;   }

    BOOL SetBitmap(UINT nIDResource);
    BOOL SetBitmap(LPCTSTR lpszResourceName);
    BOOL SetBitmap(HBITMAP hBitmap, CPalette* pPalette = NULL);
    BOOL SetBitmap(LPBITMAPINFO lpBitmapInfo, LPVOID lpBits);   

    CPalette *GetPalette()  { return &m_Palette; }
    BOOL SetPalette(CPalette* pPalette);
    BOOL SetLogPalette(LOGPALETTE* pLogPalette);

    BOOL SetDither(BOOL bDither);
    BOOL GetDither();

// Operations
public:
    BOOL Load(LPCTSTR lpszFileName);
    BOOL Save(LPCTSTR lpszFileName);

    BOOL Draw(CDC* pDC, CPoint ptDest, BOOL bForceBackground = FALSE);
    BOOL Stretch(CDC* pDC, CPoint ptDest, CSize size, BOOL bForceBackground = FALSE);

	//-Add By Chinson----------------------------------------------
	BOOL CreateEmptyDIB(int nWidth,int nHeight,int nBits);
	BOOL CreateEmptyDIB(LPBITMAPINFO lpBitmapInfo);
	//-------------------------------------------------------------

	//-Add By Chinson----------------------------------------------
	//inline COLORREF GetPixel(CPoint point);
	COLORREF GetPixel(int x,int y);
	//BOOL SetPixel(CPoint Point,COLORREF color);
	BOOL SetPixel(int x,int y,COLORREF color);
	BOOL SetPixel(int x,int y, BGRDATA color);
	//-------------------------------------------------------------

// Overrideables

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation
protected:
    void _ShowLastError();
    BOOL CreatePalette();
    BOOL FillDIBColorTable(UINT nNumColours, RGBQUAD *pRGB);

protected:
    HBITMAP  m_hBitmap;          // Handle to DIBSECTION
    DIBINFO  m_DIBinfo;          // Bitmap header & color table info
    VOID    *m_ppvBits;          // Pointer to bitmap bits
    UINT     m_iColorDataType;   // color data type (palette or RGB values)
    UINT     m_iColorTableSize;  // Size of color table

    CPalette m_Palette;          // Color palette

    BOOL     m_bDither;          // Use DrawDib routines for dithering?
    HDRAWDIB m_hDrawDib;         // handle to a DrawDib DC 

	//-Add By Chinson--------------------------------------------------------
	unsigned int m_nBmpColumn;		// �v���}�C���A�@�� Row �u������Column��
	//-----------------------------------------------------------------------

private:
    HBITMAP  m_hOldBitmap;      // Storage for previous bitmap in Memory DC
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDIBSECTIONLITE_H__35D9F3D4_B960_11D2_A981_2C4476000000__INCLUDED_)
