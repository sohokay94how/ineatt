// DlgRegister.cpp : implementation file
//

#include "stdafx.h"
#include "eblogin.h"
#include "DlgRegister.h"
#include "DlgMessageBox.h"

namespace cgc {
#ifdef WIN32
	typedef __int64				bigint;
#define cgc_atoi64(a) _atoi64(a)
#else
	typedef long long			bigint;
#define cgc_atoi64(a) atoll(a)
#endif
}

// CDlgRegister dialog

IMPLEMENT_DYNAMIC(CDlgRegister, CEbDialogBase)

CDlgRegister::CDlgRegister(CWnd* pParent /*=NULL*/)
	: CEbDialogBase(CDlgRegister::IDD, pParent)
	, m_sAccount(_T(""))
	, m_sUserName(_T(""))
	, m_sPassword(_T(""))
	, m_sPwdConfirm(_T(""))
	, m_sEnterpriseName(_T(""))
{
	//m_bIsEntboostServer = true;
}

CDlgRegister::~CDlgRegister()
{
}

void CDlgRegister::DoDataExchange(CDataExchange* pDX)
{
	CEbDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_sAccount);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_sUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EDIT_PWD_CONFIRM, m_sPwdConfirm);
	DDX_Text(pDX, IDC_EDIT_ENT_NAME, m_sEnterpriseName);
	DDX_Control(pDX, IDC_EDIT_ACCOUNT, m_editAccount);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_editUserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editPassword);
	DDX_Control(pDX, IDC_EDIT_PWD_CONFIRM, m_editPwdConfirm);
	DDX_Control(pDX, IDC_EDIT_ENT_NAME, m_editEnterpriseName);
}


BEGIN_MESSAGE_MAP(CDlgRegister, CEbDialogBase)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgRegister::OnBnClickedButtonClose)
	ON_MESSAGE(EB_WM_REGISTER_RESPONSE, OnMessageRegResponse)
	ON_BN_CLICKED(IDOK, &CDlgRegister::OnBnClickedOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgRegister message handlers

void CDlgRegister::OnPaint()
{
	if (IsIconic())
	{
		//CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//// ʹͼ���ڹ��������о���
		//int cxIcon = GetSystemMetrics(SM_CXICON);
		//int cyIcon = GetSystemMetrics(SM_CYICON);
		//CRect rect;
		//GetClientRect(&rect);
		//int x = (rect.Width() - cxIcon + 1) / 2;
		//int y = (rect.Height() - cyIcon + 1) / 2;

		//// ����ͼ��
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawInfo();
		//CEbDialogBase::OnPaint();
	}
}

BOOL CDlgRegister::OnInitDialog()
{
	CEbDialogBase::OnInitDialog();
	this->SetTransparentType(CEbDialogBase::TT_STATIC);

#ifdef USES_EBCOM_TEST
	CoCreateInstance(__uuidof(EBClientCore),NULL,CLSCTX_INPROC,__uuidof(IEBClientCore),(void**)&m_pEBAppClient);
	if (m_pEBAppClient==NULL) return FALSE;

	(((CEBDispatch*)(CEBCoreEventsSink*)this))->AddRef();	// ���Ӽ���������ɾ���Լ�
	((CEBCoreEventsSink*)this)->m_hFireWnd = this->GetSafeHwnd();
	this->DispEventAdvise(m_pEBAppClient);
#endif
	this->EnableToolTips();
	if (theApp.m_bSendRegMail)
	//const CEBString sAddress = theSetting.GetServerAddress();
	//m_bIsEntboostServer = sAddress.find("entboost.com")!=std::string::npos;
	//if (m_bIsEntboostServer)
	{
		this->SetToolTipText(IDC_EDIT_ACCOUNT,_T("�����������ַע�����ʺţ�"));
	}else
	{
		this->GetDlgItem(IDC_STATIC_ACCOUNT)->SetWindowText(_T("��¼�ʺţ�"));
		this->SetToolTipText(IDC_EDIT_ACCOUNT,_T("�����������ַ���ֻ�����ע�����ʺţ���ѡ����"));
	}
	if ((theApp.m_nOpenRegister&2)==2)
	{
		// ֧����ҵע��
		//this->SetToolTipText(IDC_EDIT_ENT_NAME,_T("�ɹ�ע����ҵ����Ա�ʺź󣬹�˾���Ʋ����޸ģ�"));
	}else
	{
		m_editEnterpriseName.EnableWindow(FALSE);
		this->SetToolTipText(IDC_EDIT_ENT_NAME,_T("��ǰ�汾����֧����ҵ�û�ע�ᣡ"));
	}

	m_btnClose.SetAutoSize(false);
	m_btnClose.SetDrawToolButtonPic(4,theDefaultBtnWhiteColor,-1,-1,-1,2);
	m_btnClose.SetDrawPanelRgn(false);
	m_btnClose.SetToolTipText(_T("�ر�"));
	m_btnOk.SetTextHotMove(false);
	m_btnOk.SetToolTipText(_T("���ע�����ʺ�"));
	//m_btnOk.SetDrawPanelRgn(false);
	m_btnCancel.SetTextHotMove(false);
	m_btnCancel.SetToolTipText(_T("ȡ��"));
	//m_btnCancel.SetDrawPanelRgn(false);
	m_btnCancel.SetDrawLine(5,1,0,theDefaultFlatLineColor);
	float h,s,l;
	::RGBtoHSL(GetRValue(theApp.GetMainColor()), GetGValue(theApp.GetMainColor()), GetBValue(theApp.GetMainColor()),&h,&s,&l);
	const COLORREF crOk = theDefaultBtnNormal==0.0?theApp.GetMainColor():HSLtoRGB(h, s, (l+theDefaultBtnNormal));
	const COLORREF crHot = HSLtoRGB(h, s, min(theDefaultMaxBtnHot,(l+theDefaultBtnHot)));
	const COLORREF crPre = ::HSLtoRGB(h, s, min(theDefaultMaxBtnPre,(l+theDefaultBtnPre)));
	//const COLORREF crOk = HSLtoRGB(h, s, theDefaultBtnOkColorLight1);
	//const COLORREF crHot1 = HSLtoRGB(h, s, theDefaultBtnHotColorLight1);
	//const COLORREF crHot2 = HSLtoRGB(h, s, theDefaultBtnHotColorLight2);
	//const COLORREF crHot = theApp.GetColorGradient()?crHot1:crHot2;
	//const COLORREF crPre = ::HSLtoRGB(h, s, theDefaultColorNormalLight);
	
	m_btnClose.SetDrawPanel(true,theApp.GetMainColor(),theDefaultBtnCloseColor,theDefaultBtnCloseColor);

	m_btnOk.SetDrawPanel(true,crOk,crHot,crPre);
	m_btnOk.SetNorTextColor(theDefaultBtnWhiteColor); 
	m_btnOk.SetHotTextColor(theDefaultBtnWhiteColor); 
	m_btnOk.SetPreTextColor(theDefaultBtnWhiteColor); 
	m_btnCancel.SetDrawLine(5,1,0,theDefaultFlatLineColor,crOk);
	m_btnCancel.SetDrawPanel(true,theDefaultBtnWhiteColor);
	m_btnCancel.SetHotTextColor(crOk); 
	m_btnCancel.SetPreTextColor(crOk); 
	m_editAccount.SetRectangleColor(crHot,theDefaultFlatLineColor);	// crHot1
	m_editUserName.SetRectangleColor(crHot,theDefaultFlatLineColor);	// theDefaultFlatLineColor
	m_editPassword.SetRectangleColor(crHot,theDefaultFlatLineColor);
	m_editPwdConfirm.SetRectangleColor(crHot,theDefaultFlatLineColor);
	m_editEnterpriseName.SetRectangleColor(crHot,theDefaultFlatLineColor);	// crPre

	// 
	const int const_y	= 61;
	const int const_x1	= 52;
	const int const_x2	= 140;
	const int const_static_width	= 80;
	const int const_edit_width		= 245;
	const int const_edit_height		= 21;
	const int const_height_interval	= 44;
	int nX = const_x1;
	int nY = const_y;
	this->GetDlgItem(IDC_STATIC_ACCOUNT)->MoveWindow(nX,nY,const_static_width,const_edit_height);
	nX = const_x2;
	this->GetDlgItem(IDC_EDIT_ACCOUNT)->MoveWindow(nX,nY,const_edit_width,const_edit_height);
	nX = const_x1;
	nY += const_height_interval;
	this->GetDlgItem(IDC_STATIC_NAME)->MoveWindow(nX,nY,const_static_width,const_edit_height);
	nX = const_x2;
	this->GetDlgItem(IDC_EDIT_USERNAME)->MoveWindow(nX,nY,const_edit_width,const_edit_height);
	nX = const_x1;
	nY += const_height_interval;
	this->GetDlgItem(IDC_STATIC_PASSWOR)->MoveWindow(nX,nY,const_static_width,const_edit_height);
	nX = const_x2;
	this->GetDlgItem(IDC_EDIT_PASSWORD)->MoveWindow(nX,nY,const_edit_width,const_edit_height);
	nX = const_x1;
	nY += const_height_interval;
	this->GetDlgItem(IDC_STATIC_PWD_CONFIRM)->MoveWindow(nX,nY,const_static_width,const_edit_height);
	nX = const_x2;
	this->GetDlgItem(IDC_EDIT_PWD_CONFIRM)->MoveWindow(nX,nY,const_edit_width,const_edit_height);
	nX = const_x1;
	nY += const_height_interval;
	this->GetDlgItem(IDC_STATIC_ENT_NAME)->MoveWindow(nX,nY,const_static_width,const_edit_height);
	nX = const_x2;
	this->GetDlgItem(IDC_EDIT_ENT_NAME)->MoveWindow(nX,nY,const_edit_width,const_edit_height);

	const int POS_DLG_WIDTH = 480;
	const int POS_DLG_HEIGHT = 340;
	CRect rectClient;
	this->GetWindowRect(&rectClient);
	rectClient.right = rectClient.left + POS_DLG_WIDTH;
	rectClient.bottom = rectClient.top + POS_DLG_HEIGHT;
	this->MoveWindow(&rectClient);
	this->SetWindowText(_T("ע�����ʺ�"));
	SetCircle();
	SetDlgChildFont(theDefaultDialogFontSize,theFontFace.c_str());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRegister::DrawInfo(void)
{
	CPaintDC dc2(this);
	CRect rectClient;
	this->GetClientRect(&rectClient);
	CSkinMemDC memDC(&dc2, rectClient);
	this->ClearBgDrawInfo();
	//if (theApp.GetColorFlat())
	{
		this->AddBgDrawInfo(CEbBackDrawInfo(theDefaultBgColorTitleHeight,1.0,false));
		this->AddBgDrawInfo(CEbBackDrawInfo(0,1.0,false,false,0,theDefaultFlatBgColor));
		//this->AddBgDrawInfo(CEbBackDrawInfo(0,theDefaultBgColorBgLight2,false));
		this->DrawPopBg(&memDC, theApp.GetMainColor(), 1);
		//this->DrawPopBg(&memDC, theApp.GetMainColor(), 1, theDefaultBgColorTitleHeight, 2);
	//}else
	//{
	//	if (theApp.GetColorGradient())
	//		this->AddBgDrawInfo(CEbBackDrawInfo(theDefaultBgColorTitleHeight,theDefaultBgColorTitleLight1,theApp.GetColorGradient()));
	//	else
	//		this->AddBgDrawInfo(CEbBackDrawInfo(theDefaultBgColorTitleHeight,1.0,theApp.GetColorGradient()));
	//	this->AddBgDrawInfo(CEbBackDrawInfo(246,theDefaultBgColorBgLight1,false));
	//	this->AddBgDrawInfo(CEbBackDrawInfo(0,theDefaultBgColorBgLight3,false));
	//	this->DrawPopBg(&memDC, theApp.GetMainColor());
	}
	Gdiplus::Graphics graphics(memDC.m_hDC);
	Gdiplus::Image * pImage;
	if (theApp.ImageFromIDResource(IDB_PNG_IMG1_REG,_T("png"),pImage))
	{
		graphics.DrawImage(pImage,PointF(10,10));
		delete pImage;
	}
	//graphics.DrawImage(theApp.m_image1Group,PointF(10,10));
	// д����
	const FontFamily fontFamily(theFontFamily.c_str());
	const Gdiplus::Font fontEbTitle(&fontFamily, 14, FontStyleBold, UnitPixel);
	Gdiplus::SolidBrush brushEbTitle(Gdiplus::Color(255,255,255));
	const Gdiplus::PointF pointTitle(40,12);
	graphics.DrawString(L"ע�����ʺ�",-1,&fontEbTitle,pointTitle,&brushEbTitle);

	const Gdiplus::Font fontEbTip(&fontFamily, 12, FontStyleRegular, UnitPixel);
	Gdiplus::SolidBrush brushTip(Gdiplus::Color(128,128,128));
	//Gdiplus::SolidBrush brushTip(Gdiplus::Color(255,0,128));
	if (theApp.m_bSendRegMail)
	//if (m_bIsEntboostServer)
		graphics.DrawString(L"ע��ɹ����뼰ʱ�����ʼ�������ʺ���֤��",-1,&fontEbTip,PointF(138,83),&brushTip);
	else
		graphics.DrawString(L"ע��ɹ�����ʹ���ʺź������¼��",-1,&fontEbTip,PointF(138,83),&brushTip);
	if ((theApp.m_nOpenRegister&2)==2)
		graphics.DrawString(L"����дע������ʺţ���д��˾����ע����ҵ����Ա�ʺţ�",-1,&fontEbTip,PointF(138,258),&brushTip);
	else
		graphics.DrawString(L"��ǰ�汾����֧��ע����ҵ�û���",-1,&fontEbTip,PointF(138,258),&brushTip);
		//graphics.DrawString(L"��ǰ��Ȩ�汾����֧��ע����ҵ�û���",-1,&fontEbTip,PointF(138,258),&brushTip);

	//CPaintDC dc2(this);
	//this->ClearBgDrawInfo();
	//this->AddBgDrawInfo(CEbBackDrawInfo(42,0.7,true));
	//this->AddBgDrawInfo(CEbBackDrawInfo(246,0.98,false));
	//this->AddBgDrawInfo(CEbBackDrawInfo(0,0.9,false));
	//this->DrawPopBg(&dc2, theApp.GetMainColor());
	//// IDB_PNG_IMG1_REG

	//CRect rectClient;
	//this->GetClientRect(&rectClient);
	//HDC m_hdcMemory = dc2.m_hDC;

	//// д����
	//CFont pNewFontTitle;
	//pNewFontTitle.CreatePointFont(115, _T("����"));//������ʾ�ı�������
	//HGDIOBJ pOldFond = SelectObject(m_hdcMemory, pNewFontTitle.m_hObject);
	//::SetBkMode(m_hdcMemory, TRANSPARENT);
	//SetTextColor(m_hdcMemory, RGB(0, 0, 0));	// ��ɫ
	//CString sOutText = _T("ע�����ʺ�");
	//TextOut(m_hdcMemory, 13, 13, sOutText, sOutText.GetLength());
	//SelectObject(m_hdcMemory, pOldFond);
}


void CDlgRegister::OnSize(UINT nType, int cx, int cy)
{
	CEbDialogBase::OnSize(nType, cx, cy);

	const int const_minbtn_width = 24;
	const int const_minbtn_height = 22;
	int btnx = 0;
	btnx = cx-const_minbtn_width-2;
	if (m_btnClose.GetSafeHwnd()!=NULL)
		m_btnClose.MoveWindow(btnx, 1,const_minbtn_width,const_minbtn_height);

	//int x = cx/2;
	////int x = (cx-theDefaultBtnWidth*2-theDefaultBtnIntever)/2;
	//int y = cy-theDefaultBtnHeight-theDefaultBtnBottomIntever;		// ��������
	//m_btnOk.MovePoint(x,y,theDefaultBtnWidth,theDefaultBtnHeight);
	//x += (theDefaultBtnWidth+theDefaultBtnIntever);
	//m_btnCancel.MovePoint(x,y,theDefaultBtnWidth,theDefaultBtnHeight);

	int x = cx-theDefaultBtnWidth-theDefaultBtnRightIntever;					// ���ұ߼��
	const int const_btn_y = cy-theDefaultBtnHeight-theDefaultBtnBottomIntever;	// ��������
	m_btnCancel.MovePoint(x,const_btn_y,theDefaultBtnWidth,theDefaultBtnHeight);
	x -= (theDefaultBtnWidth+theDefaultBtnIntever);
	m_btnOk.MovePoint(x,const_btn_y,theDefaultBtnWidth,theDefaultBtnHeight);
}

void CDlgRegister::OnBnClickedButtonClose()
{
	// TODO: Add your control notification handler code here
	PostMessage(WM_CLOSE, 0, 0);
}

//#ifdef USES_EBCOM_TEST
//void CDlgRegister::Fire_onRegisterResponse(EB_STATE_CODE nState,eb::bigint nUserId)
//{
//	OnRegResponse(nState,nUserId);
//	//this->GetDlgItem(IDOK)->EnableWindow(TRUE);
//	//switch(nState)
//	//{
//	//case EB_STATE_OK:
//	//	{
//	//		if (theApp.m_bSendRegMail)
//	//		//if (m_bIsEntboostServer)
//	//			CDlgMessageBox::EbDoModal(this,"ע��ɹ���","������ʼ��������֤�ʺţ�",CDlgMessageBox::IMAGE_INFORMATION);
//	//		else
//	//			CDlgMessageBox::EbDoModal(this,"ע��ɹ���","��ʹ���ʺź������¼������ҵIM�ͻ��ˣ�",CDlgMessageBox::IMAGE_INFORMATION);
//	//		this->PostMessage(WM_CLOSE, 0, 0);
//	//		//CEbDialogBase::OnOK();
//	//	}break;
//	//case EB_STATE_ERROR:
//	//	{
//	//		this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
//	//		CDlgMessageBox::EbMessageBox(this,"ע��ʧ�ܣ�","�����ԣ�",CDlgMessageBox::IMAGE_WARNING);
//	//	}break;
//	//case EB_STATE_ACCOUNT_ALREADY_EXIST:
//	//	{
//	//		this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
//	//		CDlgMessageBox::EbMessageBox(this,"���ʺ��Ѿ����ڣ�","������ʺ����ƣ�",CDlgMessageBox::IMAGE_WARNING);
//	//	}break;
//	//case EB_STATE_ENTERPRISE_ALREADY_EXIST:
//	//	{
//	//		this->GetDlgItem(IDC_EDIT_ENT_NAME)->SetFocus();
//	//		CDlgMessageBox::EbMessageBox(this,"�ù�˾�����Ѿ���ע�᣺","��ȷ�Ϻ����ԣ�",CDlgMessageBox::IMAGE_WARNING);
//	//	}break;
//	//case EB_STATE_APPID_KEY_ERROR:
//	//	{
//	//		CDlgMessageBox::EbMessageBox(this,"APP KEY����","����ϵ��˾������www.entboost.com��˾��",CDlgMessageBox::IMAGE_WARNING);
//	//	}break;
//	//case EB_STATE_DISABLE_REGISTER_USER:
//	//	CDlgMessageBox::EbMessageBox(this,"��ǰ�汾δ�����û�ע�Ṧ�ܣ�","����ϵ��˾������www.entboost.com��˾��",CDlgMessageBox::IMAGE_WARNING);
//	//	break;
//	//case EB_STATE_DISABLE_REGISTER_ENT:
//	//	CDlgMessageBox::EbMessageBox(this,"��ǰ�汾δ������ҵע�Ṧ�ܣ�","����ϵ��˾������www.entboost.com��˾��",CDlgMessageBox::IMAGE_WARNING);
//	//	break;
//	//default:
//	//	CDlgMessageBox::EbMessageBox(this,"ע��ʧ�ܣ�","����ϵ��˾������www.entboost.com��˾���˳������ԣ�",CDlgMessageBox::IMAGE_WARNING);
//	//	break;
//	//}
//}
//#else
//#endif
LRESULT CDlgRegister::OnMessageRegResponse(WPARAM wParam, LPARAM lParam)
{
	const eb::bigint nUserId = lParam==0?0:eb_atoi64((const char*)lParam);
	OnRegResponse((EB_STATE_CODE)wParam,nUserId);
	return 0;
}

void CDlgRegister::OnRegResponse(EB_STATE_CODE nState,eb::bigint nUserId)
{
	this->GetDlgItem(IDOK)->EnableWindow(TRUE);
	switch(nState)
	{
	case EB_STATE_CONTENT_BIG_LENGTH:
		CDlgMessageBox::EbMessageBox(this,"","�ֶ����ݳ�����󳤶ȣ�\r\n���������룡",CDlgMessageBox::IMAGE_WARNING,5);
		break;
	case EB_STATE_OK:
		{
			if (theApp.m_bSendRegMail)
			//if (m_bIsEntboostServer)
				CDlgMessageBox::EbDoModal(this,"","ע��ɹ���\r\n�뼰ʱ�����ʼ�������ʺ���֤��",CDlgMessageBox::IMAGE_INFORMATION,true);
			else
			{
				CString sText;
				//if (theApp.m_sAccountPrefix.empty())
				{
					if (m_sAccount.IsEmpty())
						sText.Format(_T("ע��ɹ���\r\n��ʹ�� %lld ��¼��"),nUserId);
					else
						sText.Format(_T("ע��ɹ���\r\n��ʹ�� %s �� %lld ��¼��"),m_sAccount,nUserId);
					CDlgMessageBox::EbDoModal(this,"",sText,CDlgMessageBox::IMAGE_INFORMATION,true);
				//}else
				//{
				//	CDlgMessageBox::EbDoModal(this,"ע�����ʺ�","ע��ɹ���\r\n��ʹ��ע���ʺŵ�¼��",CDlgMessageBox::IMAGE_INFORMATION);
				}
			}
			this->PostMessage(WM_CLOSE, 0, 0);
			//CEbDialogBase::OnOK();
		}break;
	case EB_STATE_ERROR:
		{
			this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
			CDlgMessageBox::EbMessageBox(this,"","ע��ʧ�ܣ�\r\n�����ԣ�",CDlgMessageBox::IMAGE_WARNING,5);
		}break;
	case EB_STATE_ACCOUNT_ALREADY_EXIST:
		{
			this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
			CDlgMessageBox::EbMessageBox(this,"","�ʺ��Ѿ����ڣ�\r\n������ʺź����ԣ�",CDlgMessageBox::IMAGE_WARNING,5);
		}break;
	case EB_STATE_ENTERPRISE_ALREADY_EXIST:
		{
			this->GetDlgItem(IDC_EDIT_ENT_NAME)->SetFocus();
			CDlgMessageBox::EbMessageBox(this,"","��˾�����Ѿ���ע�᣺\r\n��ȷ�Ϻ����ԣ�",CDlgMessageBox::IMAGE_WARNING,5);
		}break;
	case EB_STATE_APPID_KEY_ERROR:
		{
			CDlgMessageBox::EbMessageBox(this,"","APP KEY����\r\n����ϵ��˾�ͷ���",CDlgMessageBox::IMAGE_WARNING,5);
		}break;
	case EB_STATE_DISABLE_REGISTER_USER:
		CDlgMessageBox::EbMessageBox(this,"","��ֹ�û�ע�Ṧ�ܣ�\r\n����ϵ��˾�ͷ���",CDlgMessageBox::IMAGE_WARNING,5);
		break;
	case EB_STATE_DISABLE_REGISTER_ENT:
		CDlgMessageBox::EbMessageBox(this,"","��ֹ��ҵע�Ṧ�ܣ�\r\n����ϵ��˾�ͷ���",CDlgMessageBox::IMAGE_WARNING,5);
		break;
	default:
		CDlgMessageBox::EbMessageBox(this,"","ע��ʧ�ܣ�\r\n����ϵ��˾�ͷ������˳������ԣ�",CDlgMessageBox::IMAGE_WARNING,5);
		break;
	}
}

std::string GetHostIp2(const char * lpszHostName,const char* lpszDefaultName)
{
	if (lpszHostName==NULL || strlen(lpszHostName)==0)
		return lpszDefaultName;
	try
	{
		struct hostent *host_entry;
		//struct sockaddr_in addr;
		/* ��Ҫ������������������ */
		host_entry=gethostbyname(lpszHostName);
		//printf("%s\n", dn_or_ip);
		if(host_entry!=0)
		{
			//printf("����IP��ַ: ");
			char lpszIpAddress[50];
			memset(lpszIpAddress, 0, sizeof(lpszIpAddress));
			sprintf(lpszIpAddress, "%d.%d.%d.%d",
				(host_entry->h_addr_list[0][0]&0x00ff),
				(host_entry->h_addr_list[0][1]&0x00ff),
				(host_entry->h_addr_list[0][2]&0x00ff),
				(host_entry->h_addr_list[0][3]&0x00ff));
			return lpszIpAddress;
		}
	}catch(std::exception&)
	{
	}catch(...)
	{}
	return lpszDefaultName;
}

void CDlgRegister::OnBnClickedOk()
{
	UpdateData();

	// *������ж��Ƿ�Ϊ�գ�
	//if (m_sAccount.IsEmpty())
	//{
	//	this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
	//	if (theApp.m_bSendRegMail)
	//		CDlgMessageBox::EbDoModal(this,"�����������ʺţ�","",CDlgMessageBox::IMAGE_WARNING);
	//	else
	//		CDlgMessageBox::EbDoModal(this,"������������ֻ��ʺţ�","",CDlgMessageBox::IMAGE_WARNING);
	//	return;
	//}
//#ifdef USES_EBCOM_TEST
//	const CEBString sAddress = theEBClientCore->GetAccountAddress((LPCTSTR)m_sAccount).GetBSTR();
//#else
//	std::string sAddress;
//	entboost::GetAccountAddress((LPCTSTR)m_sAccount, sAddress);
//#endif
	//if (m_bIsEntboostServer)
	if (theApp.m_bSendRegMail)
	{
		if (m_sAccount.IsEmpty())
		{
			this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
			CDlgMessageBox::EbMessageBox(this,"","�ʺŲ���Ϊ�գ�\r\n�����������ʺţ�",CDlgMessageBox::IMAGE_WARNING,5);
			return;
		}

		const std::string sAccountEmail(m_sAccount);
		bool bError = false;
		const std::string::size_type find = sAccountEmail.find("@");
		if (find == std::string::npos)
			bError = true;
		else
		{
			const std::string sDomain = sAccountEmail.substr(find+1);
			bError = ::GetHostIp2(sDomain.c_str(),"").empty();
			if (bError)
			{
				std::string sWWWDomain("www.");
				sWWWDomain.append(sDomain);
				bError = ::GetHostIp2(sWWWDomain.c_str(),"").empty();
			}
			if (bError)
			{
				std::string sWWWDomain("pop3.");
				sWWWDomain.append(sDomain);
				bError = ::GetHostIp2(sWWWDomain.c_str(),"").empty();
			}
		}
		if (bError)
		{
			this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
			CDlgMessageBox::EbMessageBox(this,"","���������ʺŻ��ʽ��\r\n���������룡",CDlgMessageBox::IMAGE_WARNING,5);
			return;
		}
	}else if (theApp.m_sAccountPrefix.empty() && !m_sAccount.IsEmpty()) // *�ʺŲ�Ϊ�գ���Ҫ�жϸ�ʽ�Ƿ���ȷ��
	{
		const std::string sAccount(m_sAccount);
		const std::string::size_type find = sAccount.find("@",1);
		mycp::bigint nPhone = 0;
		if (find != std::string::npos || !libEbc::IsFullNumber(sAccount.c_str(),sAccount.size()))
		{
			// xx@xx�����ʽ
		}else if (sAccount.size()==11 && sAccount.substr(0,1)=="1")
		{
			nPhone = cgc_atoi64(sAccount.c_str());
		}else
		{
			// �����ʽ��
			this->GetDlgItem(IDC_EDIT_ACCOUNT)->SetFocus();
			CDlgMessageBox::EbMessageBox(this,"","��֧��ȫ�����ʺţ�\r\n���������룡",CDlgMessageBox::IMAGE_WARNING,5);
			return;
		}
	}

	if (m_sPassword.IsEmpty())
	{
		this->GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
		CDlgMessageBox::EbMessageBox(this,"","���벻��Ϊ�գ�\r\n���������룡",CDlgMessageBox::IMAGE_WARNING,5);
		return;
	}
	if (m_sPassword != m_sPwdConfirm)
	{
		this->GetDlgItem(IDC_EDIT_PWD_CONFIRM)->SetFocus();
		CDlgMessageBox::EbMessageBox(this,"","���벻һ�£�\r\n���������룡",CDlgMessageBox::IMAGE_WARNING,5);
		return;
	}

	//if (m_pEBAppClient.IsStart() && m_pEBAppClient.GetAddress()!=sAddress)
	//{
	//	m_pEBAppClient.Stop();
	//}
	//if (!m_pEBAppClient.IsStart())
	//{
	//	m_pEBAppClient.Start(sAddress.c_str());
	//	m_pEBAppClient.SetMsgHwnd(this->GetSafeHwnd());
	//}
	this->GetDlgItem(IDOK)->EnableWindow(FALSE);
	// lib sdk ������жϴ���
	//CString sFullAccount(m_sAccount);
	//if (!sFullAccount.IsEmpty() && !theApp.m_sAccountPrefix.empty() && sFullAccount.Find(theApp.m_sAccountPrefix.c_str())<0)	// "@"��������Ŵ���
	//{
	//	sFullAccount = theApp.m_sAccountPrefix.c_str()+m_sAccount;
	//}
	//const CString sFullAccount = theApp.m_sAccountPrefix.c_str()+m_sAccount;

#ifdef USES_EBCOM_TEST
	const CEBString sAddress = theEBSetting->ServerAddress.GetBSTR();
	m_pEBAppClient->EB_Init(sAddress.c_str(),"");
	if (m_pEBAppClient->EB_IsInited == VARIANT_FALSE)
	{
		CDlgMessageBox::EbMessageBox(this,"","���ط�������ʧ�ܣ�\r\n�����ԣ�",CDlgMessageBox::IMAGE_WARNING,5);
		return;
	}
	m_pEBAppClient->EB_SetDevAppOnlineKey(theEBClientCore->EB_GetDevAppId(),theEBClientCore->EB_GetDevAppOnlineKey());
	m_pEBAppClient->EB_Register((LPCTSTR)m_sAccount,(LPCTSTR)m_sPassword,(LPCTSTR)m_sUserName,(LPCTSTR)m_sEnterpriseName);
#else
	const CEBString sAddress = theSetting.GetServerAddress();
	m_pEBAppClient.EB_Init(sAddress.c_str());
	m_pEBAppClient.EB_SetMsgHwnd(this->GetSafeHwnd());
	if (!m_pEBAppClient.EB_IsInited())
	{
		CDlgMessageBox::EbMessageBox(this,"","���ط�������ʧ�ܣ�\r\n�����ԣ�",CDlgMessageBox::IMAGE_WARNING,5);
		return;
	}
	const eb::bigint sAppId = theEBAppClient.EB_GetDevAppId();
	const tstring sAppOnlineKey = theEBAppClient.EB_GetDevAppOnlineKey();
	m_pEBAppClient.EB_SetDevAppOnlineKey(sAppId,sAppOnlineKey.c_str());
	m_pEBAppClient.EB_Register(m_sAccount,m_sPassword,m_sUserName,m_sEnterpriseName);
#endif
}

void CDlgRegister::OnDestroy()
{
#ifdef USES_EBCOM_TEST
	if (m_pEBAppClient != NULL)
	{
		this->DispEventUnadvise(m_pEBAppClient);
		m_pEBAppClient.Release();
	}
#else
	m_pEBAppClient.EB_SetMsgHwnd(NULL);
	m_pEBAppClient.EB_UnInit();
#endif
	CEbDialogBase::OnDestroy();
}

BOOL CDlgRegister::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam==' ')
	{
		// ���Ʋ�������ո�
		if (pMsg->hwnd == m_editAccount.GetSafeHwnd() ||
			pMsg->hwnd == m_editPassword.GetSafeHwnd() ||
			pMsg->hwnd == m_editPwdConfirm.GetSafeHwnd())
		{
			return TRUE;
		}
	}

	return CEbDialogBase::PreTranslateMessage(pMsg);
}
