// BitMapShowView.cpp : implementation of the CBitMapShowView class
//

#include "stdafx.h"
#include "BitMapShow.h"

#include "BitMapShowDoc.h"
#include "BitMapShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitMapShowView

IMPLEMENT_DYNCREATE(CBitMapShowView, CView)

BEGIN_MESSAGE_MAP(CBitMapShowView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CBitMapShowView::OnFileOpen)
END_MESSAGE_MAP()

// CBitMapShowView construction/destruction

CBitMapShowView::CBitMapShowView()
{
	// TODO: add construction code here

}

CBitMapShowView::~CBitMapShowView()
{
}

BOOL CBitMapShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBitMapShowView drawing

void CBitMapShowView::OnDraw(CDC* pDC)
{
	CBitMapShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CFileFind bExit;
	if (!bExit.FindFile(m_sFileName))
	{
		//MessageBox((LPCTSTR)_T("�ļ�������"), (LPCTSTR)_T("fuck"), MB_ICONQUESTION);
		return;
	}
	IStream *pStm; 
	CFileStatus fstatus; 
	CFile file; 
	LONG cb; 
	if (file.Open(m_sFileName,CFile::modeRead)&&file.GetStatus(m_sFileName,fstatus)&& ((cb = fstatus.m_size) != -1)) 
	{ 
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, cb); 
		LPVOID pvData = NULL; 
		if (hGlobal != NULL) 
			if ((pvData = GlobalLock(hGlobal)) != NULL) 
			{ 
				file.Read(pvData, cb); 
				GlobalUnlock(hGlobal); 
				CreateStreamOnHGlobal(hGlobal, TRUE, &pStm); 
			} 
	} 

	IPicture *pPic; 
	if(SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic))) 
	{ 
		OLE_XSIZE_HIMETRIC hmWidth; 
		OLE_YSIZE_HIMETRIC hmHeight; 
		pPic->get_Width(&hmWidth); 
		pPic->get_Height(&hmHeight); 
		double fX,fY; 
		fX = (double)pDC->GetDeviceCaps(HORZRES)*(double)hmWidth/((double)pDC->GetDeviceCaps(HORZSIZE)*100.0); 
		fY = (double)pDC->GetDeviceCaps(VERTRES)*(double)hmHeight/((double)pDC->GetDeviceCaps(VERTSIZE)*100.0); 
		if(FAILED(pPic->Render(*pDC,0,0,(DWORD)fX,(DWORD)fY,0,hmHeight,hmWidth,-hmHeight,NULL))) 
			MessageBox((LPCTSTR)_T("��Ⱦͼ��ʧ��"), (LPCTSTR)_T("fuck"), MB_ICONQUESTION);
		pPic->Release(); 
	} 
	else 
		MessageBox((LPCTSTR)_T("�����м���ͼ��ʧ��"), (LPCTSTR)_T("fuck"), MB_ICONQUESTION);

	// TODO: add draw code for native data here
}


// CBitMapShowView printing

BOOL CBitMapShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBitMapShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBitMapShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBitMapShowView diagnostics

#ifdef _DEBUG
void CBitMapShowView::AssertValid() const
{
	CView::AssertValid();
}

void CBitMapShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitMapShowDoc* CBitMapShowView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitMapShowDoc)));
	return (CBitMapShowDoc*)m_pDocument;
}
#endif //_DEBUG


// CBitMapShowView message handlers

void CBitMapShowView::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog FileChooser(
		TRUE, 
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_T("bmp Files (*.bmp)|*.bmp|All files(*.*)|*.*||"));

	if (FileChooser.DoModal()==IDOK)
	{
		m_sFileName = FileChooser.GetPathName();
		Invalidate(TRUE);
	}
}


#if 0
int m_nState = 3;
if (m_nState == 1)   //��һ�ַ�ʽ��ͨ��������Ķ�ȡ��ʽ�����
{
	CFile file;               //��ʾ���򿪵�bmp�ļ�
	char *pColor;
	int i,j;
	file.Open(m_sFileName,CFile::modeRead,NULL);
	ULONGLONG ulSize = file.GetLength();
	char *pBuf = new char[ulSize];                         //����һ��ͬλͼ�ļ���ͬ��С�Ļ�����
	UINT uiTemp = file.Read(pBuf,ulSize);            //��ȡλͼ���ݵ�������
	file.Close();

	LONG cx,cy;

	DWORD bfOffBits;
	WORD biBitCount;
	bfOffBits = *(DWORD*)(pBuf+10);                //�ƶ�10λ����ȡ��DWORD   bfOffBits;

	cx = *(LONG*)(pBuf+18);                              //�ֱ�ȡ��x��y��������ֵ���ƶ�18��22(ʵ�� 
	cy = *(LONG*)(pBuf+22);                              //�Ͼ���bfOffBits 40��
	biBitCount = *(WORD*)(pBuf+28);                //����ȡbiBitCount
	BYTE byBlue,byGreen,byRed;
	if (biBitCount == 24)//��������ɫ24λͼƬ
	{
		char *pTemp;

		pTemp = pBuf+54;//54λ�󴦣���ÿ�����صľ�����ɫֵ
		for(j=cy-1;j>=0;j--)
		{
			for(i=0;i<cx;i++)
			{
				byBlue = *pTemp;   //��Ϊ�����ɫ24λ�����Ըպ�8λ��һ����ɫ,++�Ϳ���ȡ��һ��ɫ
				//ֵ��
				pTemp++;
				byGreen = *pTemp;
				pTemp++;
				byRed = *pTemp;
				pTemp++;
				SetPixel(pDC->m_hDC,i,j,RGB(byRed,byGreen,byBlue));  //����Ļ����Ӧλ�û�����ɫ
			}
			if ((cx*3)%4 != 0)
			{
				pTemp += (4-(cx*3)%4);
			}
		}
	}
	else if(biBitCount == 8) //256ɫͼƬ
	{
		unsigned char *pTemp = (unsigned char*)(void*)(pBuf+bfOffBits);
		pColor = pBuf+54;
		int nIndex;
		for(j=cy-1;j>=0;j--)
		{
			for(i=0;i<cx;i++)
			{
				nIndex = (UINT)*pTemp;//ע��������256ɫͼƬ����ɫֵȡ��������ͬ
				byBlue = *(pColor+nIndex*4);
				byGreen = *(pColor+nIndex*4+1);
				byRed = *(pColor+nIndex*4+2);
				SetPixel(pDC->m_hDC,i,j,RGB(byRed,byGreen,byBlue));    
				pTemp++;
			}
			pTemp += (4-cx%4);
		}
	}
	else;//ʣ�µ�16ɫͼƬ�͵�ɫͼƬ�������Լ�������������
	//AfxMessageBox("Init Decvice failed!");;//��ɫ��16ɫͼƬ�򿪹�����δ�ṩ!
	delete []pBuf;
	pBuf = NULL;
}
if (m_nState == 2)//�ڶ��ַ���ʹ��SetDIBitsToDevice���������
{
	CFile file;
	file.Open(m_sFileName,CFile::modeRead,NULL);
	ULONGLONG ulSize = file.GetLength();
	char *pBuf = new char[ulSize];
	file.Read(pBuf,ulSize);
	file.Close();
	LONG cx,cy;
	DWORD bfOffBits;
	bfOffBits = *(DWORD*)(pBuf+10);
	cx = *(LONG*)(pBuf+18);
	cy = *(LONG*)(pBuf+22);
	void *pBmpInfo,*lpvBufBmp;
	lpvBufBmp = pBuf+bfOffBits;
	pBmpInfo = pBuf+14;
	BITMAPINFO bmpInfo;
	memcpy(&bmpInfo.bmiHeader,pBmpInfo,40);
	SetDIBitsToDevice(pDC->m_hDC,0,0,cx,cy,0,0,0,cy,lpvBufBmp,
		&bmpInfo,DIB_PAL_COLORS);  
	delete [] pBuf;
	pBuf = NULL;
}
if (m_nState == 3)//�����ַ���ʹ��BitBlt��������ɣ����ַ�����Ϊ���ʵ�á�
{
	//CDC *pDC = GetDC();
	CDC dcMemory;
	CFile file;
	file.Open(m_sFileName,CFile::modeRead,NULL);
	ULONGLONG ulSize = file.GetLength();
	char *pBuf = new char[ulSize];
	file.Read(pBuf,ulSize);
	file.Close();
	LONG cx,cy;
	DWORD bfOffBits;
	bfOffBits = *(DWORD*)(pBuf+10);
	cx = *(LONG*)(pBuf+18);
	cy = *(LONG*)(pBuf+22);
	dcMemory.CreateCompatibleDC(pDC);
	HBITMAP hbitmap = (HBITMAP)::LoadImage(
		0,
		m_sFileName,
		IMAGE_BITMAP,  
		cx,
		cy, 
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	CBitmap bmp;
	bmp.Attach(hbitmap);

	CBitmap *pOldBitmap = dcMemory.SelectObject(&bmp);
	pDC->BitBlt(10,10,cx,cy,&dcMemory,0,0,SRCCOPY);
}

// ��������CSDN���ͣ�ת�������������http://blog.csdn.net/welcome_ck/archive/2004/12/24/228185.aspx
#endif