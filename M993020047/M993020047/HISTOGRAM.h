#pragma once


// HISTOGRAM dialog

class HISTOGRAM : public CDialog
{
	DECLARE_DYNAMIC(HISTOGRAM)

public:
	HISTOGRAM(CWnd* pParent = NULL);   // standard constructor
	virtual ~HISTOGRAM();

// Dialog Data
	enum { IDD = IDD_DIALOGHISTOGRAM };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **GRAY;
	int rcount[256];
	int gcount[256];
	int bcount[256];
	int grcount[256];
	int height;
	int width;
	int rmax;
	int gmax;
	int bmax;
	int grmax;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
