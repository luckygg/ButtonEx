// ButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_ButtonEx.h"
#include "ButtonEx.h"


// CButtonEx

IMPLEMENT_DYNAMIC(CButtonEx, CWnd)

CButtonEx::CButtonEx()
{
	m_clrBkg	= Color(255,255,  0,  0);
	m_clrText	= Color(255,255,255,255);
	m_clrBorder = Color(255,255,  0,  0);

	m_bEnable	= true;
	m_bClicked	= false;
	m_bMouseTrack = FALSE;

	m_fSizeBorder	= 4;
	m_fSizeText		= 20;
	m_nOffsetTextX	= 0;
	m_nOffsetTextY	= 0;

	m_nTextAlign1	= 1;
	m_nTextAlign2	= 1;

	m_pBmpImage = NULL;

	m_rcImage = Rect(0,0,0,0);
}

CButtonEx::~CButtonEx()
{
	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}
}


BEGIN_MESSAGE_MAP(CButtonEx, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CButtonEx message handlers

void CButtonEx::PreSubclassWindow()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcImage = Rect(rect.left, rect.top, rect.Width(), rect.Height());

	CWnd::PreSubclassWindow();
}

BOOL CButtonEx::OnEraseBkgnd(CDC* pDC)
{
	//Avoid Flicker.
	//return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}

void CButtonEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	Graphics mainG (dc.GetSafeHdc());

	// �޸� ����
	Bitmap memBmp(rect.Width(), rect.Height());

	Graphics memG(&memBmp);

	// �ܻ��� ���ֱ� ���� white ä��.
	SolidBrush brs(Color(255,0,0,0));
	memG.FillRectangle(&brs,0,0,rect.Width(),rect.Height());

	//----- �޸𸮻� �׸��� �κ� -----//
	DrawBkg(&memG);
	DrawBorder(&memG);
	DrawImage(&memG);
	DrawText(&memG);
	//---------------------------------//

	if (m_bEnable == true)
	{
		if (m_bMouseTrack == TRUE)
		{
			ColorMatrix HotMat = {	
				1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
				0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
				0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
				0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
				0.05f, 0.05f, 0.05f, 0.00f, 1.00f	};

				ImageAttributes ia;
				ia.SetColorMatrix(&HotMat);

				RectF grect; grect.X=0, grect.Y=0; grect.Width = (float)rect.Width(); grect.Height = (float)rect.Height();
				mainG.DrawImage(&memBmp, grect, 0, 0, (float)rect.Width(), (float)rect.Height(), UnitPixel, &ia);
		}
		else
		{
			mainG.DrawImage(&memBmp,0,0);
		}
	}
	else
	{
		ColorMatrix GrayMat = {	
			0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
			0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
			0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};

			ImageAttributes ia;
			ia.SetColorMatrix(&GrayMat);

			RectF grect; grect.X=0, grect.Y=0; grect.Width = (float)rect.Width(); grect.Height = (float)rect.Height();
			mainG.DrawImage(&memBmp, grect, 0, 0, (float)rect.Width(), (float)rect.Height(), UnitPixel, &ia);
	}
}

void CButtonEx::DrawBorder(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	Pen pen(m_clrBorder,m_fSizeBorder);

	pG->DrawRectangle(&pen,rect.left,rect.top,rect.Width(),rect.Height());
	
}

void CButtonEx::DrawBkg(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	SolidBrush brs(m_clrBkg);

	pG->FillRectangle(&brs,rect.left,rect.top,rect.right,rect.bottom);
}

void CButtonEx::DrawImage(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	if (m_pBmpImage == NULL) return;

	Rect rcNew(m_rcImage);
	
	if (m_bClicked == true)
		rcNew.Offset(1,1);
	
	pG->DrawImage(m_pBmpImage, rcNew, 0,0, m_pBmpImage->GetWidth(), m_pBmpImage->GetHeight(), UnitPixel);
}

void CButtonEx::DrawText(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	CString text = L"";
	GetWindowText(text);

	FontFamily fontptroll(L"Arial");
	Gdiplus::Font font(&fontptroll, m_fSizeText, FontStyleRegular, UnitPixel);

	StringFormat formatAlign;
	formatAlign.SetAlignment((Gdiplus::StringAlignment)m_nTextAlign1);		// Left / Center / Right
	formatAlign.SetLineAlignment((Gdiplus::StringAlignment)m_nTextAlign2);	// Top / Middle / Bottom

	SolidBrush brs(m_clrText);
	
	RectF rc((float)rect.left+m_nOffsetTextX, (float)rect.top+m_nOffsetTextY, (float)rect.Width(),(float)rect.Height());
	if (m_bClicked == true)
		rc.Offset(1,1);

	pG->DrawString(text,text.GetLength(),&font,rc,&formatAlign,&brs);
}

bool CButtonEx::LoadImageFromFile(CString strPath)
{
	if (IsFileExist(strPath) == false) return false;

	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}

	m_pBmpImage = (Bitmap*)Image::FromFile(strPath);

	if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
		return false;

	Invalidate();

	return true;
}

bool CButtonEx::LoadImageFromResource(UINT ID, bool bPNG)
{
	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}

	if (bPNG == false)
	{
		m_pBmpImage = Bitmap::FromResource(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(ID));
	}
	else
	{
		// PNG ���ҽ��� Bitmap ���ҽ��� �ҷ����� �ͺ��� �����ϴ�.
		HRSRC hResource = ::FindResource(AfxGetApp()->m_hInstance, (WCHAR*)MAKEINTRESOURCEW(ID), L"PNG");	// 3��° ���ڴ� ���� ���ҽ��� �з��Ǵ� ���ڿ��� ���޵Ǿ�� �Ѵ�.
		if (!hResource) return false;

		DWORD imageSize = ::SizeofResource(AfxGetApp()->m_hInstance, hResource);
		if (!imageSize) return false;

		const void* pResourceData = ::LockResource(::LoadResource(AfxGetApp()->m_hInstance, hResource));
		if (!pResourceData) return false;

		HGLOBAL hBuffer  = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
		if (hBuffer)
		{
			void* pBuffer = ::GlobalLock(hBuffer);
			if (pBuffer)
			{
				CopyMemory(pBuffer, pResourceData, imageSize);

				IStream* pStream = NULL;
				if (::CreateStreamOnHGlobal(hBuffer, FALSE, &pStream) == S_OK)
				{
					m_pBmpImage = Gdiplus::Bitmap::FromStream(pStream);
					pStream->Release();

					if (m_pBmpImage)
					{
						if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
						{
							delete m_pBmpImage;
							m_pBmpImage = NULL;
						}
					}
				}
			}
			::GlobalUnlock(hBuffer);
			::GlobalFree(hBuffer);
		}
	}


	if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
		return false;

	Invalidate();

	return true;
}

bool CButtonEx::IsFileExist(CString strPath)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	if ((hFind = ::FindFirstFile(strPath, &fd)) == INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return false;
	}

	return true;
}

void CButtonEx::OnMouseLeave()
{
	m_bMouseTrack = FALSE;

	CWnd::OnMouseLeave();
}


void CButtonEx::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_bMouseTrack)
	{
		TRACKMOUSEEVENT tme = {0};
		tme.cbSize		= sizeof(tme);
		tme.hwndTrack	= m_hWnd;
		tme.dwFlags		= TME_LEAVE;
		m_bMouseTrack = ::_TrackMouseEvent(&tme);
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CButtonEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bClicked = true;

	CWnd::OnLButtonDown(nFlags, point);
}


void CButtonEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bClicked = false;

	CWnd::OnLButtonUp(nFlags, point);
}