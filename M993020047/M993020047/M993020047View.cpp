// M993020047View.cpp : implementation of the CM993020047View class
//

#include "stdafx.h"
#include "M993020047.h"

#include "M993020047Doc.h"
#include "M993020047View.h"
#include "DIBSectionLite.h"

#include "MainFrm.h"																			//add by fei

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM993020047View

IMPLEMENT_DYNCREATE(CM993020047View, CView)

BEGIN_MESSAGE_MAP(CM993020047View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CM993020047View::OnFileOpen)
	ON_COMMAND(ID_SHOW_RGBCOLOR, &CM993020047View::OnShowRgbcolor)
	ON_COMMAND(ID_SHOW_GRAYCOLOR, &CM993020047View::OnShowGraycolor)
	ON_COMMAND(ID_SHOW_NEGATIVECOLOR, &CM993020047View::OnShowNegativecolor)
	ON_COMMAND(ID_GEOMETRY_REVERSE, &CM993020047View::OnGeometryReverse)
	ON_COMMAND(ID_GEOMETRY_ZOOM, &CM993020047View::OnGeometryZoom)
	ON_COMMAND(ID_SHOW_BITPLANE, &CM993020047View::OnShowBitplane)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CM993020047View::OnGeometryRotate)
	ON_COMMAND(ID_SHOW_WATERMARK, &CM993020047View::OnShowWatermark)
	ON_COMMAND(ID_SHOW_HISTOGRAM, &CM993020047View::OnShowHistogram)
	ON_WM_MOUSEMOVE()																					//add by fei
	ON_COMMAND(ID_SHOW_HEADER, &CM993020047View::OnShowHeader)
	ON_COMMAND(ID_SHOW_PALETTE, &CM993020047View::OnShowPalette)
	ON_COMMAND(ID_SHOW_HISTOGRAMEQUALIZATION, &CM993020047View::OnShowHistogramequalization)
	ON_COMMAND(ID_SHOW_TRANSPARENCY, &CM993020047View::OnShowTransparency)
	ON_COMMAND(ID_SHOW_THRESHOLDING, &CM993020047View::OnShowThresholding)
	ON_COMMAND(ID_FILTER_OUTLIER, &CM993020047View::OnFilterOutlier)
	ON_COMMAND(ID_FILTER_HIGHTBOOST, &CM993020047View::OnFilterHightboost)
	ON_COMMAND(ID_FILTER_LOWPASS, &CM993020047View::OnFilterLowpass)
	ON_COMMAND(ID_FILTER_SOBELANDPREWITT, &CM993020047View::OnFilterSobelandprewitt)
	ON_COMMAND(ID_FILTER_PSEUDO, &CM993020047View::OnFilterPseudo)
	ON_COMMAND(ID_SHOW_HISTOGRAMSPECIFICATIONANDCONTRAST, &CM993020047View::OnShowHistogramspecificationandcontrast)
	ON_COMMAND(ID_SHOW_HUFFMANCOMPRESSION, &CM993020047View::OnShowHuffmancompression)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SHAPE_LINE, &CM993020047View::OnShapeLine)
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CM993020047View::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_ELLIPSE, &CM993020047View::OnShapeEllipse)
	ON_COMMAND(ID_EDIT_CUT, &CM993020047View::OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, &CM993020047View::OnEditPaste)
	ON_COMMAND(ID_EDIT_COPY, &CM993020047View::OnEditCopy)
	ON_COMMAND(ID_SHOW_DCT, &CM993020047View::OnShowDct)
	ON_COMMAND(ID_SHOW_RESTORE, &CM993020047View::OnShowRestore)
END_MESSAGE_MAP()

// CM993020047View construction/destruction

CM993020047View::CM993020047View()
: m_FirstPoint(CPoint(0,0))
, m_SecondPoint(CPoint(0,0))
{
	// TODO: add construction code here
	x1=0;
	y1=0;
	x2=0;
	y2=0;
	shapetype=0;
	cuttype=0;
	pastetype=0;
	RGB_Dialog=NULL;
	GRAY_Dialog=NULL;
	NEGATIVE_Dialog=NULL;
	REVERSE_Dialog=NULL;
	ZOOM_Dialog=NULL;
	BITPLANE_Dialog=NULL;
	ROTATE_Dialog=NULL;
	WATERMARK_Dialog=NULL;
	HISTOGRAM_Dialog=NULL;
	HISTOGRAMEQUALIZATION_Dialog=NULL;
	TRANSPARENCY_Dialog=NULL;
	THRESHOLDING_Dialog=NULL;
	OUTLIER_Dialog=NULL;
	HIGHTBOOST_Dialog=NULL;
	LOWPASS_Dialog=NULL;
	SOBEL_Dialog=NULL;
	PSEUDO_Dialog=NULL;
	SPECIFICATION_Dialog=NULL;
	HUFFMAN_Dialog=NULL;
	DCT_Dialog=NULL;
	RESTORE_Dialog=NULL;
}

CM993020047View::~CM993020047View()
{
	if(RGB_Dialog) delete RGB_Dialog;
	if(GRAY_Dialog) delete GRAY_Dialog;
	if(NEGATIVE_Dialog) delete NEGATIVE_Dialog;
	if(REVERSE_Dialog) delete REVERSE_Dialog;
	if(ZOOM_Dialog) delete ZOOM_Dialog;
	if(BITPLANE_Dialog) delete BITPLANE_Dialog;
	if(ROTATE_Dialog) delete ROTATE_Dialog;
	if(WATERMARK_Dialog) delete WATERMARK_Dialog;
	if(HISTOGRAM_Dialog) delete HISTOGRAM_Dialog;
	if(HISTOGRAMEQUALIZATION_Dialog) delete HISTOGRAMEQUALIZATION_Dialog;
	if(TRANSPARENCY_Dialog) delete TRANSPARENCY_Dialog;
	if(THRESHOLDING_Dialog) delete THRESHOLDING_Dialog;
	if(OUTLIER_Dialog) delete OUTLIER_Dialog;
	if(HIGHTBOOST_Dialog) delete HIGHTBOOST_Dialog;
	if(LOWPASS_Dialog) delete LOWPASS_Dialog;
	if(SOBEL_Dialog) delete SOBEL_Dialog;
	if(PSEUDO_Dialog) delete PSEUDO_Dialog;
	if(SPECIFICATION_Dialog) delete SPECIFICATION_Dialog;
	if(HUFFMAN_Dialog) delete HUFFMAN_Dialog;
	if(DCT_Dialog) delete DCT_Dialog;
	if(RESTORE_Dialog) delete RESTORE_Dialog;
}

BOOL CM993020047View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CM993020047View drawing

void CM993020047View::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);
	if(a == 1)
	{
		image->Draw(&dc,CPoint(0,0));
	}

	CM993020047Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CM993020047View printing

BOOL CM993020047View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CM993020047View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CM993020047View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CM993020047View diagnostics

#ifdef _DEBUG
void CM993020047View::AssertValid() const
{
	CView::AssertValid();
}

void CM993020047View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CM993020047Doc* CM993020047View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CM993020047Doc)));
	return (CM993020047Doc*)m_pDocument;
}
#endif //_DEBUG


// CM993020047View message handlers

void CM993020047View::OnFileOpen()
{
	CFileDialog dialog(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,CString("PCX檔案(*.pcx)|*.pcx||"),NULL);
	if(dialog.DoModal()==IDOK)
	{
		a=1;
		CFile file;
		file.Open(dialog.GetFileName(),CFile::modeRead);              
        file.Read(&PCXheader,128);

		if(PCXheader.manufacturer==0x0a) //if the picture file was PCX format
		{
			width=(PCXheader.Xmax-PCXheader.Xmin)+1;
	        height=(PCXheader.Ymax-PCXheader.Ymin)+1;
            bpl=PCXheader.bytes_per_line;
            
			file.Seek(-769,CFile::end); //to seek the minus 769 bytes from the end of the file
			file.Read(&cb,1); //to read the control byte with 1 byte
			
		    Palette_data=new unsigned char [768]; //to set the size of the Palette_data array with 768 bytes

			if(cb==0x0c) //if the PCX file had the 256 color palette
		    {
				file.Seek(-768,CFile::end); //to seek the minus 768 bytes from the end of the file
			    file.Read(Palette_data,768); //to read the palette_data array 
		    	RLE_value=(double)((file.GetLength())-128-769); //to save the value of the RLE to RLE_value array  
			}
		    else //if the PCX file had no the 256 color palette
			{
				RLE_value=double(file.GetLength()-128); //to save the value of the RLE to RLE_value array			
			}

		    pcx_data=new unsigned char [RLE_value]; //to set the size of the pcx_data array
		    pixel_value=new unsigned char [1]; //to set the size of the pixel_value array with 1 byte

            file.Seek(128,CFile::begin); //to seek the 128 bytes from the top of the file
            file.Read(pcx_data,RLE_value); //to read pcx_data with the size of the RLE_value
		}
	}
            
	int count,index=0;
	for(i=0;i<RLE_value;i++)
	{
		count=0;
		if((pcx_data[i] & 0xc0)==0xc0) //if the upper 2 bits of the RLE was 11
		{
			count=(int)(pcx_data[i] & /*0x3f*/63); //to save how many times repeated
		    pixel_value=(unsigned char*)realloc(pixel_value,_msize(pixel_value)+sizeof(char)*(count)); //to extend the array
            for(j=0;j<count;j++)
			{
				pixel_value[index]=pcx_data[i+1];
				index++;
			}
            i++;
		}
		else //if the upper 2 bits of the RLE was not 11
		{
			count=1;
            pixel_value=(unsigned char*)realloc(pixel_value,_msize(pixel_value)+sizeof(char)*count);
            pixel_value[index]=pcx_data[i];	
	        index++;
		}
	}

	R=new int * [height]; 
    for(i=0;i<height;i++) R[i]=new int [width];

    G=new int * [height]; 
    for(i=0;i<height;i++) G[i]=new int [width];

    B=new int * [height]; 
    for(i=0;i<height;i++) B[i]=new int [width];

	if(cb==0x0c && (int)PCXheader.color_planes==1)
    {			
		for(i=0;i<height;i++) 
		{
			for(j=0;j<width;j++)
			{
				R[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width])*3];
	            G[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width])*3+1];
		        B[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width])*3+2];
			}
		}

		for(i=0;i<256;i++)//顯示調色盤
		{
			R_Palette[i]=Palette_data[i*3];
			G_Palette[i]=Palette_data[i*3+1];
			B_Palette[i]=Palette_data[i*3+2];
		}

	}
	else
	{
		for(i=0;i<height;i++) 
		{
			for(j=0;j<width;j++)
			{
				R[i][j]=(int)pixel_value[j+((i)*width*3)];
		        G[i][j]=(int)pixel_value[j+(width*1)+((i)*width*3)];
		        B[i][j]=(int)pixel_value[j+(width*2)+((i)*width*3)];
			}			    
		}				
	}

	CClientDC dc(this);
	image = new CDIBSectionLite();
	image->CreateEmptyDIB(width,height,24);

    for(i=0;i<height;i++) 
	{
		for(j=0;j<width;j++)
	    {
			image->SetPixel(j,i,RGB(R[i][j],G[i][j],B[i][j]));
		}
		
	}image->Draw(&dc,CPoint(0,0));	

}

void CM993020047View::OnShowRgbcolor()
{

    if(RGB_Dialog) delete RGB_Dialog;								//釋放記憶體空間
	RGB_Dialog=new RGBColor();										//動態宣告物件
	RGB_Dialog->Create(IDD_DIALOGRGB,RGB_Dialog);					//新增視窗
	RGB_Dialog->Setting_Picture_Info(height,width,R,G,B);			//取得影像資訊

	if(RGB_Dialog && !RGB_Dialog->SetWindowPos(&CWnd::wndTop,50,50,50+width,50+height+40,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowGraycolor()
{
    if(GRAY_Dialog) delete GRAY_Dialog;								//釋放記憶體空間
	GRAY_Dialog=new GRAYColor();									//動態宣告物件
	GRAY_Dialog->Create(IDD_DIALOGGRAY,GRAY_Dialog);				//新增視窗
	GRAY_Dialog->Setting_Picture_Info(height,width,R,G,B);			//取得影像資訊

	if(GRAY_Dialog && !GRAY_Dialog->SetWindowPos(&CWnd::wndTop,50,50,50+width+50,50+height,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowNegativecolor()
{
    if(NEGATIVE_Dialog) delete NEGATIVE_Dialog;								//釋放記憶體空間
	NEGATIVE_Dialog=new NEGATIVEColor();									//動態宣告物件
	NEGATIVE_Dialog->Create(IDD_DIALOGNEGATIVE,NEGATIVE_Dialog);			//新增視窗
	NEGATIVE_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(NEGATIVE_Dialog && !NEGATIVE_Dialog->SetWindowPos(&CWnd::wndTop,50,50,50+width,50+height+40,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnGeometryReverse()
{	
    if(REVERSE_Dialog) delete REVERSE_Dialog;								//釋放記憶體空間
	REVERSE_Dialog=new REVERSE();											//動態宣告物件
	REVERSE_Dialog->Create(IDD_DIALOGREVERSE,REVERSE_Dialog);				//新增視窗
	REVERSE_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(REVERSE_Dialog && !REVERSE_Dialog->SetWindowPos(&CWnd::wndTop,50,50,50+width,50+height+40,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnGeometryZoom()
{
    if(ZOOM_Dialog) delete ZOOM_Dialog;									//釋放記憶體空間
	ZOOM_Dialog=new ZOOM();												//動態宣告物件
	ZOOM_Dialog->Create(IDD_DIALOGZOOM,ZOOM_Dialog);					//新增視窗
	ZOOM_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(ZOOM_Dialog && !ZOOM_Dialog->SetWindowPos(&CWnd::wndTop,50,50,500,500,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowBitplane()
{
    if(BITPLANE_Dialog) delete BITPLANE_Dialog;								//釋放記憶體空間
	BITPLANE_Dialog=new BITPLANE();											//動態宣告物件
	BITPLANE_Dialog->Create(IDD_DIALOGBITPLAN,BITPLANE_Dialog);				//新增視窗
	BITPLANE_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(BITPLANE_Dialog && !BITPLANE_Dialog->SetWindowPos(&CWnd::wndTop,50,50,50+2*width+50,50+height+50,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnGeometryRotate()
{
    if(ROTATE_Dialog) delete ROTATE_Dialog;								//釋放記憶體空間
	ROTATE_Dialog=new ROTATE();											//動態宣告物件
	ROTATE_Dialog->Create(IDD_DIALOGROTATE,ROTATE_Dialog);				//新增視窗
	ROTATE_Dialog->Setting_Picture_Info(height,width,R,G,B);			//取得影像資訊

	if(ROTATE_Dialog && !ROTATE_Dialog->SetWindowPos(&CWnd::wndTop,10,50,1000,450,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowWatermark()
{
    if(WATERMARK_Dialog) delete WATERMARK_Dialog;								//釋放記憶體空間
	WATERMARK_Dialog=new WATERMARK();											//動態宣告物件
	WATERMARK_Dialog->Create(IDD_DIALOGWATERMARK,WATERMARK_Dialog);				//新增視窗
	WATERMARK_Dialog->Setting_Picture_Info(height,width,R,G,B);					//取得影像資訊

	if(WATERMARK_Dialog && !WATERMARK_Dialog->SetWindowPos(&CWnd::wndTop,10,10,788,555,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowHistogram()
{
    if(HISTOGRAM_Dialog) delete HISTOGRAM_Dialog;								//釋放記憶體空間
	HISTOGRAM_Dialog=new HISTOGRAM();											//動態宣告物件
	HISTOGRAM_Dialog->Create(IDD_DIALOGHISTOGRAM,HISTOGRAM_Dialog);				//新增視窗
	HISTOGRAM_Dialog->Setting_Picture_Info(height,width,R,G,B);					//取得影像資訊

	if(HISTOGRAM_Dialog && !HISTOGRAM_Dialog->SetWindowPos(&CWnd::wndTop,10,10,640,670,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}																																					
void CM993020047View::OnMouseMove(UINT nFlags, CPoint point)
{
	if((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;
		x2 = point.x;
		y2 = point.y;

		CClientDC dc(this);
		image->Draw(&dc,CPoint(0,0));
		CPen pen(PS_DOT,1,RGB(255,0,0));						
		CPen *oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);

		if(shapetype == 1)
		{ dc.MoveTo(x1,y1);    
		  dc.LineTo(x2,y2); }
		if(shapetype == 2)
		{ dc.Rectangle(x1,y1,x2,y2); }
		if(shapetype == 3)
		{ dc.Ellipse(x1,y1,x2,y2); }
		dc.SelectObject(oldPen);
	}

	char strx[5];
		wsprintf(strx,"%d",point.x);
		CString AA="X=";
        AA+=strx;
		((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(1,CString(AA));

	char stry[5];
		wsprintf(stry,"%d",point.y);
		CString BB="Y=";
        BB+=stry;
		((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(2,CString(BB));

		if (R && G && B
		&& point.x<width && point.y<height)
	{	

		unsigned int R_value = R[point.y][point.x];		
		char strr[4];
		wsprintf(strr,"%d", R_value);
		CString CC="R=";
        CC+=strr;
		((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(3,CString(CC));

		unsigned int G_value = G[point.y][point.x];
		char strg[4];
		wsprintf(strg,"%d", G_value);
        CString DD="G=";
        DD+=strg;
		((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(4,CString(DD));

		unsigned int B_value = B[point.y][point.x];
		char strb[4];
		wsprintf(strb,"%d", B_value);
       	CString EE="B=";
        EE+=strb;
	    ((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(5,CString(EE));
	}
		else
		{
			char strr[4];	
			int R_value=255;
			wsprintf(strr,"%d", R_value);		
			CString CC="R=";     			
			CC+=strr;		
			((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(3,CString(CC));
		
			char strg[4];	
			int G_value=255;
			wsprintf(strg,"%d", G_value);		
			CString DD="G=";       
			DD+=strg;		
			((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(4,CString(DD));
		
			char strb[4];		
			int B_value=255;
			wsprintf(strb,"%d", B_value);	
			CString EE="B=";
			EE+=strb;
			((CMainFrame * )AfxGetMainWnd())->m_wndStatusBar.SetPaneText(5,CString(EE));
		}
		
}
void CM993020047View::OnShowHeader()
{
	CClientDC dc(this);
	dc.TextOut(10,height+15,CString("Manufacturer:"));
	CString str;
	str.Format(_T("%d"),PCXheader.manufacturer);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+15,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+35,CString("version:"));
	str.Format(_T("%d"),PCXheader.version);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(75,height+35,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+55,CString("encoding:"));
	str.Format(_T("%d"),PCXheader.encoding);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+55,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+75,CString("BitsPerPixel:"));
	str.Format(_T("%d"),PCXheader.bits_per_pixel);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+75,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+95,CString("Xmax:"));
	str.Format(_T("%d"),PCXheader.Xmax);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(65,height+95,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+115,CString("Xmin:"));
	str.Format(_T("%d"),PCXheader.Xmin);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(65,height+115,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+135,CString("Ymax:"));
	str.Format(_T("%d"),PCXheader.Ymax);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(65,height+135,str);
	
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+155,CString("Ymin:"));
	str.Format(_T("%d"),PCXheader.Ymin);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(65,height+155,str);
	
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+175,CString("width:"));
	str.Format(_T("%d"),width);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(65,height+175,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+195,CString("height:"));
	str.Format(_T("%d"),height);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(65,height+195,str);
	
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+215,CString("Hdpi:"));
	str.Format(_T("%d"),PCXheader.hres);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+215,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+235,CString("Vdpi:"));
	str.Format(_T("%d"),PCXheader.vres);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+235,str);


	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+255,CString("Colormap:"));
	str.Format(_T("%d"),*Palette_data);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+255,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+275,CString("reserved:"));
	str.Format(_T("%d"),PCXheader.reserved);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+275,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+295,CString("NPlanes:"));
	str.Format(_T("%d"),PCXheader.color_planes);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+295,str);

	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+315,CString("BytesPerLine:"));
	str.Format(_T("%d"),bpl);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+315,str);

	
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+335,CString("PaletteInfo:"));
	str.Format(_T("%d"),PCXheader.pallete_type);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+335,str);
	
	dc.SetTextColor(RGB(0,0,0));
	dc.TextOut(10,height+355,CString("Filler:"));
	str.Format(_T("%d"),PCXheader.filler[58]);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOut(105,height+355,str);
}

void CM993020047View::OnShowPalette()
{
	CClientDC dc(this);	
	for(int i=0;i<16;i++) 
	{
		for(int j=0;j<16;j++)
		{
			for(int k=0;k<16;k++) for(int m=0;m<16;m++)
			{
				dc.SetPixel(i*16+k+50+width,j*16+10+m,RGB(R_Palette[i*16+j],G_Palette[i*16+j],B_Palette[i*16+j]));
			}
		}
	}
}

void CM993020047View::OnShowHistogramequalization()
{
    if(HISTOGRAMEQUALIZATION_Dialog) delete HISTOGRAMEQUALIZATION_Dialog;									//釋放記憶體空間
	HISTOGRAMEQUALIZATION_Dialog=new HISTOGRAMEQUALIZATION();																	//動態宣告物件
	HISTOGRAMEQUALIZATION_Dialog->Create(IDD_DIALOGHISTOGRAMEQUALIZATION,HISTOGRAMEQUALIZATION_Dialog);		//新增視窗
	HISTOGRAMEQUALIZATION_Dialog->Setting_Picture_Info(height,width,R,G,B);									//取得影像資訊

	if(HISTOGRAMEQUALIZATION_Dialog && !HISTOGRAMEQUALIZATION_Dialog->SetWindowPos(&CWnd::wndTop,10,10,930,690,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowTransparency()
{
    if(TRANSPARENCY_Dialog) delete TRANSPARENCY_Dialog;								//釋放記憶體空間
	TRANSPARENCY_Dialog=new TRANSPARENCY();											//動態宣告物件
	TRANSPARENCY_Dialog->Create(IDD_DIALOGTRANSPARENCY,TRANSPARENCY_Dialog);		//新增視窗
	TRANSPARENCY_Dialog->Setting_Picture_Info(height,width,R,G,B);					//取得影像資訊

	if(TRANSPARENCY_Dialog && !TRANSPARENCY_Dialog->SetWindowPos(&CWnd::wndTop,10,10,552,572,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowThresholding()
{
    if(THRESHOLDING_Dialog) delete THRESHOLDING_Dialog;								//釋放記憶體空間
	THRESHOLDING_Dialog=new THRESHOLDING();											//動態宣告物件
	THRESHOLDING_Dialog->Create(IDD_DIALOGTHRESHOLDING,THRESHOLDING_Dialog);		//新增視窗
	THRESHOLDING_Dialog->Setting_Picture_Info(height,width,R,G,B);					//取得影像資訊

	if(THRESHOLDING_Dialog && !THRESHOLDING_Dialog->SetWindowPos(&CWnd::wndTop,10,10,552,582,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnFilterOutlier()
{
    if(OUTLIER_Dialog) delete OUTLIER_Dialog;								//釋放記憶體空間
	OUTLIER_Dialog=new OUTLIER();											//動態宣告物件
	OUTLIER_Dialog->Create(IDD_DIALOGOUTLIER,OUTLIER_Dialog);				//新增視窗
	OUTLIER_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(OUTLIER_Dialog && !OUTLIER_Dialog->SetWindowPos(&CWnd::wndTop,10,10,692,306,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnFilterHightboost()
{
    if(HIGHTBOOST_Dialog) delete HIGHTBOOST_Dialog;								//釋放記憶體空間
	HIGHTBOOST_Dialog=new HIGHTBOOST();											//動態宣告物件
	HIGHTBOOST_Dialog->Create(IDD_DIALOGHIGHTBOOST,HIGHTBOOST_Dialog);			//新增視窗
	HIGHTBOOST_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(HIGHTBOOST_Dialog && !HIGHTBOOST_Dialog->SetWindowPos(&CWnd::wndTop,10,10,792,306,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnFilterLowpass()
{
    if(LOWPASS_Dialog) delete LOWPASS_Dialog;								//釋放記憶體空間
	LOWPASS_Dialog=new LOWPASS();											//動態宣告物件
	LOWPASS_Dialog->Create(IDD_DIALOGLOWPASS,LOWPASS_Dialog);				//新增視窗
	LOWPASS_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(LOWPASS_Dialog && !LOWPASS_Dialog->SetWindowPos(&CWnd::wndTop,10,10,992,306,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnFilterSobelandprewitt()
{
    if(SOBEL_Dialog) delete SOBEL_Dialog;								//釋放記憶體空間
	SOBEL_Dialog=new SOBEL();											//動態宣告物件
	SOBEL_Dialog->Create(IDD_DIALOGSOBEL,SOBEL_Dialog);					//新增視窗
	SOBEL_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(SOBEL_Dialog && !SOBEL_Dialog->SetWindowPos(&CWnd::wndTop,10,10,862,346,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnFilterPseudo()
{
    if(PSEUDO_Dialog) delete PSEUDO_Dialog;								//釋放記憶體空間
	PSEUDO_Dialog=new PSEUDO();											//動態宣告物件
	PSEUDO_Dialog->Create(IDD_DIALOGPSEUDO,PSEUDO_Dialog);				//新增視窗
	PSEUDO_Dialog->Setting_Picture_Info(height,width,R,G,B);			//取得影像資訊

	if(PSEUDO_Dialog && !PSEUDO_Dialog->SetWindowPos(&CWnd::wndTop,10,10,692,306,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowHistogramspecificationandcontrast()
{
    if(SPECIFICATION_Dialog) delete SPECIFICATION_Dialog;								//釋放記憶體空間
	SPECIFICATION_Dialog=new SPECIFICATION();											//動態宣告物件
	SPECIFICATION_Dialog->Create(IDD_DIALOGSPECIFICATION,SPECIFICATION_Dialog);			//新增視窗
	SPECIFICATION_Dialog->Setting_Picture_Info(height,width,R,G,B);						//取得影像資訊

	if(SPECIFICATION_Dialog && !SPECIFICATION_Dialog->SetWindowPos(&CWnd::wndTop,10,10,552,582,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowHuffmancompression()
{
    if(HUFFMAN_Dialog) delete HUFFMAN_Dialog;								//釋放記憶體空間
	HUFFMAN_Dialog=new HUFFMAN();											//動態宣告物件
	HUFFMAN_Dialog->Create(IDD_DIALOGHUFFMAN,HUFFMAN_Dialog);				//新增視窗
	HUFFMAN_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(HUFFMAN_Dialog && !HUFFMAN_Dialog->SetWindowPos(&CWnd::wndTop,50,50,50+2*width+125,50+height,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_FirstPoint = point;
	SetCapture();
	x1 = point.x;
	y1 = point.y;
}

void CM993020047View::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(this == GetCapture())
		ReleaseCapture();
	m_SecondPoint;
	x2 = point.x;
	y2 = point.y;	

	CClientDC dc(this);
	CPen pen(PS_DOT,1,RGB(255,0,0));						
	CPen *oldPen = dc.SelectObject(&pen);
	dc.SelectStockObject(NULL_BRUSH);

	if(shapetype == 1)
	{ dc.MoveTo(x1,y1);    
	  dc.LineTo(x2,y2); }
	if(shapetype == 2)
	{ dc.Rectangle(x1,y1,x2,y2); }
	if(shapetype == 3)
	{ dc.Ellipse(x1,y1,x2,y2); }	
	dc.SelectObject(oldPen);
}

void CM993020047View::OnShapeLine()
{
	shapetype = 1;
}

void CM993020047View::OnShapeRectangle()
{
	shapetype = 2;
}

void CM993020047View::OnShapeEllipse()
{
	shapetype = 3;
}

void CM993020047View::OnEditCut()
{
	if(shapetype == 2)
	{
		cuttype=2;
		CClientDC dc(this);
		image = new CDIBSectionLite();
		image->CreateEmptyDIB(width,height,24);
	
	    for(i=0;i<height;i++) 
		{
			for(j=0;j<width;j++)
		    {
				if(j>=x1 && j<=x2 && i>=y1 && i<=y2 )
				{ image->SetPixel(j,i,RGB(255,255,255)); }
				else
				image->SetPixel(j,i,RGB(R[i][j],G[i][j],B[i][j]));
			}
		
		}image->Draw(&dc,CPoint(0,0));
	}
}

void CM993020047View::OnEditPaste()
{
	if(cuttype == 2 || pastetype == 2)
	{
		CClientDC dc(this);
		image = new CDIBSectionLite();
		image->CreateEmptyDIB(width,height,24);
	
	    for(i=0;i<height;i++) 
		{
			for(j=0;j<width;j++)
		    {
				if(j>=x1 && j<=x2 && i>=y1 && i<=y2 )
				{ image->SetPixel(j,i,RGB(R[i][j],G[i][j],B[i][j])); }
				else
				image->SetPixel(j,i,RGB(255,255,255));
			}
		
		}image->Draw(&dc,CPoint(266,0));
	}
}

void CM993020047View::OnEditCopy()
{
	if(shapetype == 2)
	{
		pastetype=2;
		CClientDC dc(this);
		image = new CDIBSectionLite();
		image->CreateEmptyDIB(width,height,24);
	    for(i=0;i<height;i++) 
		{
			for(j=0;j<width;j++)
		    {
				image->SetPixel(j,i,RGB(R[i][j],G[i][j],B[i][j]));
			}
		
		}image->Draw(&dc,CPoint(0,0));
	}
}

void CM993020047View::OnShowDct()
{
    if(DCT_Dialog) delete DCT_Dialog;								//釋放記憶體空間
	DCT_Dialog=new DCT();											//動態宣告物件
	DCT_Dialog->Create(IDD_DIALOGDCT,DCT_Dialog);					//新增視窗
	DCT_Dialog->Setting_Picture_Info(height,width,R,G,B);			//取得影像資訊

	if(DCT_Dialog && !DCT_Dialog->SetWindowPos(&CWnd::wndTop,10,10,552,582,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}

void CM993020047View::OnShowRestore()
{
    if(RESTORE_Dialog) delete RESTORE_Dialog;								//釋放記憶體空間
	RESTORE_Dialog=new RESTORE();											//動態宣告物件
	RESTORE_Dialog->Create(IDD_DIALOGRESTORE,DCT_Dialog);					//新增視窗
	RESTORE_Dialog->Setting_Picture_Info(height,width,R,G,B);				//取得影像資訊

	if(RESTORE_Dialog && !RESTORE_Dialog->SetWindowPos(&CWnd::wndTop,10,10,552,582,SWP_SHOWWINDOW))
	{
		AfxMessageBox("Could not show dialog!");
	}
}
