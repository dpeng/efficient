/////////////////////////////////////////////////////////////////////////////
// Project��MYIMGAPP
// Author��NorthTibet
// Date��������, ���� 26, 2002
// Description��ͨ�����Ƶ�C++����MFC�����������ʾ���ָ�ʽ��ͼ��
//
/////////////////////////////////////////////////////////////////////////////
// Doc.cpp : implementation of the CPictureDoc class
//
#include "StdAfx.h"
#include "resource.h"

#include <afxdisp.h>
#include <afxpriv2.h>
#include "Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPictureDoc, CDocument)

BEGIN_MESSAGE_MAP(CPictureDoc, CDocument)
END_MESSAGE_MAP()

CPictureDoc::CPictureDoc()
{
}

CPictureDoc::~CPictureDoc()
{
}

void CPictureDoc::Serialize(CArchive& ar)
{
	if (ar.IsLoading()) {
		VERIFY(m_pict.Load(ar));
	} else {
		
	}
}

//////////////////
// Load initial picture from resource
//
BOOL CPictureDoc::OnNewDocument()
{
	m_pict.Load(IDR_MAINFRAME);
	return TRUE;
}
