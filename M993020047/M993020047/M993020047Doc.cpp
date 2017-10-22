// M993020047Doc.cpp : implementation of the CM993020047Doc class
//

#include "stdafx.h"
#include "M993020047.h"

#include "M993020047Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CM993020047Doc

IMPLEMENT_DYNCREATE(CM993020047Doc, CDocument)

BEGIN_MESSAGE_MAP(CM993020047Doc, CDocument)
END_MESSAGE_MAP()


// CM993020047Doc construction/destruction

CM993020047Doc::CM993020047Doc()
{
	// TODO: add one-time construction code here

}

CM993020047Doc::~CM993020047Doc()
{
}

BOOL CM993020047Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CM993020047Doc serialization

void CM993020047Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CM993020047Doc diagnostics

#ifdef _DEBUG
void CM993020047Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CM993020047Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CM993020047Doc commands
