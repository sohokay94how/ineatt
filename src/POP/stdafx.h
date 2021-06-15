
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once
//#define _BIND_TO_CURRENT_CRT_VERSION 1
//#define _BIND_TO_CURRENT_MFC_VERSION 1
//#define _BIND_TO_CURRENT_ATL_VERSION 1

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����

#define USES_NEW_UI_160111
#define NEW_UI_160111_HEIGHT 42
#define USES_NEW_UI_1220
#define USES_SUPPORT_UI_STYLE

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <afxtempl.h>
#include <memory>   //for auto_ptr
//
//#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
//#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
//#endif
//
//#include <mshtml.h>
//#include <comdef.h>
//#include <comdefsp.h>
//#include <afxdhtml.h>
//#include <atlimage.h>

#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")

#include "../include/SqliteExt.h"
#include "bodb2.h"

#include "Core/ProgressST.h"
#include "Core/SplitterControl.h"
#include "Core/ImageEx.h"
#include "Core/NewMenu.h"
//#include "Core/MenuXP.h"
#include "Core/OleRichEditCtrl.h"
#include "Core/TraButton.h"
//#include "Core/MrFrame.h"
#include "Core/EbTranEdit.h"
#include "Core/HoverEdit.h"
#include "Core/VividTree.h"
#include "Core/SkinMemDC.h"
#include "Core/colorconver.h"
#include "Core/BitComboBox.h"
#include "Core/LabelEx.h"
#include "../include/ebc_public.h"
#include "../include/EbDialogBase.h"

#include <atlcom.h>
#import "..\build\ebvideoroom.dll" no_namespace
#include "EBMMRoomEventsSink.h"
#include "EBVideoDataEventsSink.h"
#ifdef USES_EBCOM_TEST
#import "..\build\ebcore.dll"  no_namespace	// for ebclient&ebrd
#include "../include/eb_object.h"
#include "../include/chatroomhandle.h"
#include "../include/IEB_MemberInfo.h"
#include "../include/IEB_ChatRichInfo.h"
#include "../include/IEB_ChatFileInfo.h"
#include "../include/IEB_ContactInfo.h"
#include "../include/IEB_EnterpriseInfo.h"
#include "../include/IEB_GroupInfo.h"
#include "../include/EBCoreEventsSink.h"
#include "EBSearchEventsSink.h"
#include "atlsafe.h"
#else
#include "../include/EBParseSetting.h"
#include "EBAppClient.h"
//#include "videoroom.h"
#endif
using namespace mycp;
using namespace entboost;

#import "..\build\ebcontrol.dll" no_namespace
#import "..\build\eboleimage.dll" no_namespace
#include "EBRichMessageEventsSink.h"

const mycp::bigint theVisitorStartId = 0x2000000000000LL;	// =562949953421312(15λ)
#define is_visitor_uid(id) (id>=theVisitorStartId)

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


