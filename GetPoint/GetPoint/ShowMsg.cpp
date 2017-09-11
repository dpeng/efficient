#include "StdAfx.h"
#include "ShowMsg.h"
#include "GetPoint.h"
#define WORD_HEIGHT 18          //���ֵĸ߶ȣ�����ϵͳ��������� 
#define WORD_WIDTH 7            //���ֵĿ�ȣ�����ϵͳ��������� 
#define OFF_X   15              //������ʾ��λ�������ľ��� 
#define OFF_Y   10              //һ�����������½� 
#define TEXT_COLOR RGB(0,0,0)   //�������ֵ���ɫ 
extern CGetPointApp theApp;
CShowMsg::CShowMsg(void)
{
	m_x = GetSystemMetrics(SM_CXSCREEN);
	m_y = GetSystemMetrics(SM_CYSCREEN);
	m_bCanShow = true;
}

CShowMsg::~CShowMsg(void)
{
}

void CShowMsg::ShowText(CDC* pDC, CPoint Pt, LPCSTR text)
{
	m_bCanShow = false;
	if(!m_bStart) 
		m_bStart = true;
	else 
		DoRubberCoord(pDC);
	if (Pt.y + WORD_HEIGHT + 10 > m_y)
		Pt.y = m_y - WORD_HEIGHT - 10;
	if (Pt.x + m_nCoordStrLen + 15 > m_x)
		Pt.x = m_x - m_nCoordStrLen - 15;
	CopyBitmap(pDC,Pt); 
	DrawCoord(pDC,text,Pt); 
	//ReleaseDC(hWnd, pDC); 
}
void CShowMsg::CopyBitmap(CDC* pDC,CPoint copyPt)
{
	if(m_StoreBmp.GetSafeHandle())
	{
		m_StoreDC.DeleteDC(); 
		m_StoreBmp.DeleteObject(); 
		m_StoreBmp.m_hObject=0; 
	}

	if(m_StoreDC.CreateCompatibleDC(pDC)) 
	{ 
		if(m_StoreBmp.CreateCompatibleBitmap(pDC,m_nCoordStrLen,WORD_HEIGHT)) 
		{ 
			m_StoreDC.SelectObject(&m_StoreBmp); 
			m_StoreDC.BitBlt(0,0,m_nCoordStrLen,WORD_HEIGHT,pDC,copyPt.x+OFF_X,copyPt.y+OFF_Y,SRCCOPY); 
		} 
		else 
		{ 
			if(m_StoreBmp.GetSafeHandle()) 
				m_StoreBmp.DeleteObject(); 
			m_StoreDC.DeleteDC(); 
		} 
	} 
}
void CShowMsg::DrawCoord(CDC* pDC,LPCSTR coordString,CPoint drawPt)
{
	if(m_StoreBmp.GetSafeHandle())
	{ 
		drawPt.Offset(OFF_X,OFF_Y); 
		CRect rect(drawPt,CSize(m_nCoordStrLen,WORD_HEIGHT));
		m_CurRc = rect;
		pDC->SetBkMode(TRANSPARENT);
		COLORREF crf = pDC->SetTextColor(TEXT_COLOR); 
		pDC->DrawText(coordString,rect,DT_CENTER); 
		pDC->SetTextColor(crf); 
		m_bCanShow = true;
	} 
}
void CShowMsg::DoRubberCoord(CDC* pDC)
{
	if(m_StoreBmp.GetSafeHandle()) 
	{ 
		m_StoreDC.SelectObject(&m_StoreBmp); 
		pDC->BitBlt(m_CurRc.left,m_CurRc.top,m_nCoordStrLen,WORD_HEIGHT,&m_StoreDC,0,0,SRCCOPY); 
		m_StoreDC.DeleteDC(); 
		m_StoreBmp.DeleteObject();
	} 
}