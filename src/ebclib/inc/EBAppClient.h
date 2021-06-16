// EBAppClient.h file here

#ifndef __EBAppClient_h__
#define __EBAppClient_h__

#include <vector>
#include <string>
#include "../include/EBCallbackInterface.h"
#include "../include/chatroomobject.h"
//using namespace entboost;

#ifdef EB_APPCLIENT_EXPORTS
#define EB_APPCLIENT_API __declspec(dllexport)
#else
#define EB_APPCLIENT_API __declspec(dllimport)
#endif

namespace entboost {

mycp::tstring EB_APPCLIENT_API GetHostIp(const char* lpszHostName,const char* lpszDefaultName);
bool EB_APPCLIENT_API GetAddressPort(const char* sFullAddress, mycp::tstring& sOutAddress, int & nOutPort);
//bool EB_APPCLIENT_API GetAccountAddress(const char* sFullAccount, mycp::tstring& sOutAddress);

//
class EB_APPCLIENT_API CEBAppClient
{
public:
	CEBAppClient(void);
	virtual ~CEBAppClient(void);

	/**** ��ע˵�� ***********************************************************************/
	// 1.int�������أ�0/1Ϊ���óɹ�������Ϊ��������ʧ�ܣ�
	// 2.���óɹ���ʾָ��ͳɹ���ҵ��ִ���Ƿ�ɹ������ص����������¼��ķ������ݣ�
	/*************************************************************************************/

	/**** Ӧ�ã�APP������ ***********************************************************************/
	/****
	���ܣ���ʼ��Ӧ�û���
	������sAddress ��������ַ����ʽ1:ip:port ��122.122.122.122:1234
	������sInitParameter ��ʼ��������Ĭ��Ϊ��
	====================================================================*/
	void EB_Init(const char * sAddress,const char* sInitParameter="");

	/****
	���ܣ��ж��Ƿ��Ѿ���ʼ��Ӧ�û���
	====================================================================*/
	bool EB_IsInited(void) const;

	/****
	���ܣ�ע���¼��ص�������
	������pCallBack �ص������࣬NULL ��Ϊע��
	====================================================================*/
	void EB_SetCallBack(CEBCallbackInterface * pCallBack);

	/****
	���ܣ�ע���¼��ص��������ھ��
	������pHwnd �ص��������ھ����NULL ��Ϊע��
	====================================================================*/
	void EB_SetMsgHwnd(HWND pHwnd);

	/****
	���ܣ�ע��Ӧ�û���
	====================================================================*/
	void EB_UnInit(void);

	/****
	���ܣ�����������״̬��
	====================================================================*/
	EB_STATE_CODE EB_GetLastStateCode(void) const;

	/****
	���ܣ����ط�������ַ
	====================================================================*/
	mycp::tstring EB_GetAddress(void) const;

	/****
	���ܣ�����Ӧ�ó���APP·��
	====================================================================*/
	mycp::tstring EB_GetAppPath(void) const;

	/****
	���ܣ�������Դ�ļ����·��
	====================================================================*/
	mycp::tstring EB_GetResourcePath(void) const;

	/****
	���ܣ�����Ӧ�ó���APP����·��
	====================================================================*/
	mycp::tstring EB_GetAppDataPath(void) const;

	/****
	���ܣ�����Ӧ�ó���APP��ʱ����·��
	====================================================================*/
	mycp::tstring EB_GetAppDataTempPath(void) const;

	/****
	���ܣ�������°汾
	������������°汾���Զ����ظ��°��ļ������سɹ����յ�onNewVersion()��EB_WM_NEW_VERSION֪ͨ
	������sClientVersion ��ǰ�汾
	====================================================================*/
	int EB_CheckVersion(const char* sClientVersion);

	/****
	���ܣ���ȡ������Ϣ
	������nParent ��һ������
	������nParameter �¼�֪ͨ����
	====================================================================*/
	int EB_GetAreaInfo(int nParent,unsigned int nParameter = 0);


	/**** ��������֤ ***********************************************************************/
	/****
	���ܣ����ÿ�����appid��appkey
	������sAppId ������Ӧ��ID
	������sAppKey Ӧ��KEY
	������bReLoadAppOnlineKey true:��֤appid��appkey����ȡ����app online key
	====================================================================*/
	int EB_SetDevAppId(eb::bigint sAppId,const char* sAppKey,bool bReLoadAppOnlineKey=true);

	/****
	���ܣ����ÿ�����appid��app online key
	====================================================================*/
	void EB_SetDevAppOnlineKey(eb::bigint sAppId, const char* sAppOnlineKey);

	/****
	���ܣ���ȡ������appid��applinekey
	====================================================================*/
	eb::bigint EB_GetDevAppId(void) const;
	mycp::tstring EB_GetDevAppOnlineKey(void) const;

	bool EB_SetSystemParameter(EB_SYSTEM_PARAMETER nParameter, unsigned long nParameterValue);
	void EB_GetSystemParameter(EB_SYSTEM_PARAMETER nParameter, unsigned long* pParameterValue) const;
	void EB_FreeSystemParameter(EB_SYSTEM_PARAMETER nParameter, unsigned long nParameterValue) const;

	/**** APPӦ�����Ĺ��� ***********************************************************************/
	/****
	���ܣ���¼APPӦ������
	====================================================================*/
	int EB_LogonAppCenter(void);

	/****
	���ܣ��ǳ�APPӦ������
	====================================================================*/
	void EB_LogoutAppCenter(void);

	/****
	���ܣ�������Ϣ��ָ�����У�Ӧ��
	====================================================================*/
	int EB_SendAPMsg(const EB_APMsgInfo& pAPMsgInfo, bool bSaveOffMsg);

	/****
	���ܣ���Ӧ�յ����У�Ӧ����Ϣ
	====================================================================*/
	void EB_APMsgAck(eb::bigint nMsgId);

	/**** ע�ᡢ��¼��������Ϣ ***********************************************************************/
	/****
	���ܣ�ע��һ�����ʺ�
	������sAccount ע���ʺţ����������ʽ������user@entboost.com
	������sPwd �ʺ�����
	������sUserName �û�����
	������sEnterpriseName ��ҵ���ƣ���Ϊ�գ�ע��һ����ҵ�ʺ�
	====================================================================*/
	int EB_Register(const char* sAccount, const char* sPassword, const char* sUserName="", const char* sEnterpriseName="");

	/****
	���ܣ��ο͵�¼
	====================================================================*/
	int EB_LogonByVisitor(const char* sReqCode="");

	/****
	���ܣ��û���¼
	====================================================================*/
	int EB_LogonByAccount(const char * sAccount, const char * sPassword, const char* sReqCode="", EB_USER_LINE_STATE nNewLineState=EB_LINE_STATE_ONLINE_NEW);

	/****
	���ܣ�OAUTH��֤
	====================================================================*/
	int EB_LogonOAuth(const char * sAccount="",EB_USER_LINE_STATE nNewLineState=EB_LINE_STATE_ONLINE_NEW);

	/****
	���ܣ����µ�¼����Ҫ���ڵ��Թ��𣬻�����Ͽ�����ʱ��ֱ�����µ�¼
	====================================================================*/
	int EB_ReLogon(void);

	/****
	���ܣ������Ƿ��¼�ɹ�
	====================================================================*/
	bool EB_IsLogoned(void) const;

	/****
	���ܣ������Ƿ��ο�
	====================================================================*/
	bool EB_IsLogonVisitor(void) const;

	/****
	���ܣ��û��˳�
	====================================================================*/
	void EB_Logout(void);

	/**** ������Ϣ���� ***********************************************************************/
	/****
	���ܣ���¼�ɹ��󣬼���������Ϣ
	�������ȵ���EB_LoadEnterprise()������ҵ��֯�ṹ������Ⱥ���EB_LoadContact()����ͨѶ¼�����ٵ���EB_LoadInfo()
	====================================================================*/
	void EB_LoadInfo(void);

	/******
	���ܣ����ص�¼�ʺ���Ϣ
	====================================================================*/
	bool EB_GetMyAccountInfo(EB_AccountInfo* pOutAccountInfo) const;

	/******
	���ܣ����õ�¼�ʺŸ�����Ϣ
	====================================================================*/
	bool EB_SetMyAccountInfo(const EB_AccountInfo* pInAccountInfo);

	/******
	���ܣ���ȡĬ��Ⱥ�飨���ţ���Ա���
	====================================================================*/
	bool EB_GetMyDefaultMemberCode(eb::bigint& pOutDefaultMemberCode) const;

	/******
	���ܣ�����Ĭ��Ⱥ�飨���ţ���Ա���
	������Ĭ��Ⱥ�飨���ţ���Ա��ţ��������ⲿ�������Զ���ʾ������Ƭ��
	====================================================================*/
	bool EB_SetMyDefaultMemberCode(eb::bigint nNewDefaultMemberCode);

	/******
	���ܣ���ȡĬ��Ⱥ�飨���ţ���Ա��Ϣ
	====================================================================*/
	bool EB_GetMyDefaultMemberInfo(EB_MemberInfo* pOutMemberInfo) const;

	/******
	���ܣ���ȡĬ��Ⱥ�飨���ţ���Աͷ���ļ�
	====================================================================*/
	mycp::tstring EB_GetMyDefaultMemberHeadFile(void) const;

	/******
	���ܣ����ظ�������
	====================================================================*/
	int EB_GetMyAccountSetting(void) const;

	/******
	���ܣ����¸�������
	====================================================================*/
	bool EB_SetMyAccountSetting(int nNewSetting);

	/****
	���ܣ����ص�¼�ʺ�
	====================================================================*/
	mycp::tstring EB_GetLogonAccount(void) const;
	eb::bigint EB_GetLogonUserId(void) const;

	/****
	���ܣ������ʺű�ע
	====================================================================*/
	mycp::tstring EB_GetDescription(void) const;

	/****
	���ܣ������ʺű�ע
	====================================================================*/
	bool EB_SetDescription(const char* sNewDescription);

	/****
	���ܣ������ҵ�����״̬
	====================================================================*/
	EB_USER_LINE_STATE EB_GetLineState(void)const;

	/****
	���ܣ���������״̬
	��������������Ⱥ���Ա�������Լ������յ�onUserStateChange()��EB_WM_USER_STATE_CHANGE֪ͨ
	====================================================================*/
	bool EB_SetLineState(EB_USER_LINE_STATE nNewLineState);

	/****
	���ܣ������ʺ����ƺ�����
	�������ʺ�����Ϊ�գ�����=�ʺ�
	====================================================================*/
	//void EB_GetLogonInfo(mycp::tstring& sOutUserName, mycp::tstring& sOutPassword) const;

	/****
	���ܣ������ʺ��û�����
	====================================================================*/
	mycp::tstring EB_GetUserName(void) const;

	/****
	���ܣ��޸��ʺ��û�����
	====================================================================*/
	bool EB_SetUserName(const char* sNewUserName);


	/****
	���ܣ������ʺ�����
	====================================================================*/
	mycp::tstring EB_GetPassword(void) const;

	/****
	���ܣ��޸�����
	====================================================================*/
	bool EB_SetPassword(const char* sOldPassword,const char* sNewPassword);

	/**** Ȩ�޹��� ***********************************************************************/
	/******
	���ܣ��ж��Ƿ��б༭��ҵ����Ȩ��
	������sEnterpriseCode ��ҵ���룬��Ϊ�ж�Ĭ����ҵ
	====================================================================*/
	bool EB_CanEditEnterprise(eb::bigint nEnterpriseCode=0) const;

	/******
	���ܣ��ж��Ƿ��б༭Ⱥ�飨���ţ�����Ȩ��
	������sEnterpriseCode ��ҵ���룬��Ϊ�ж�Ĭ����ҵ
	������sGroupCode Ⱥ����룬��Ϊ�ж��Ƿ��½�Ⱥ��Ȩ��
	====================================================================*/
	bool EB_CanEditGroupInfo(eb::bigint nEnterpriseCode,eb::bigint nGroupId) const;

	/******
	���ܣ��ж��Ƿ���ɾ��Ⱥ�飨���ţ�����Ȩ��
	������sGroupCode Ⱥ�����
	====================================================================*/
	bool EB_CanDeleteGroupInfo(eb::bigint nGroupId) const;
	bool EB_CanDeleteGroupInfo(eb::bigint nGroupId, eb::bigint nMemberUserId) const;

	bool EB_IsGroupCreator(eb::bigint nGroupId) const;
	bool EB_IsGroupCreator(eb::bigint nGroupId, eb::bigint nMemberUserId) const;
	bool EB_IsGroupManager(eb::bigint nGroupId) const;
	bool EB_IsGroupManager(eb::bigint nGroupId, eb::bigint nMemberUserId) const;

	/******
	���ܣ��ж��Ƿ��б༭Ⱥ�飨���ţ���Ա����Ȩ��
	������sGroupCode Ⱥ�����
	������sMemberAccount ��Ա�ʺ�
	====================================================================*/
	bool EB_CanEditMemberInfo(eb::bigint nGroupId,eb::bigint nMemberUserId) const;

	/******
	���ܣ��ж��Ƿ��б༭�ҵ�Ⱥ�飨���ţ�������Ա����Ȩ��
	������sGroupCode Ⱥ�����
	====================================================================*/
	bool EB_CanEditMyBaseMemberInfo(eb::bigint nGroupId) const;

	bool EB_CanEditMyBaseAccountInfo(void) const;

	/******
	���ܣ��ж��Ƿ���ɾ��Ⱥ�飨���ţ���Ա����Ȩ��
	������sGroupCode Ⱥ�����
	������sMemberAccount ��Ա�ʺ�
	====================================================================*/
	bool EB_CanDeleteMemberInfo(eb::bigint nGroupId,eb::bigint nMemberUserId) const;

	/******
	���ܣ��ж��Ƿ���ɾ��Ⱥ�飨���ţ���Ա����Ȩ��
	������sMemberCode Ⱥ���Ա����
	====================================================================*/
	bool EB_CanDeleteMemberInfo(eb::bigint nMemberId) const;

	/******
	���ܣ��ж��Ƿ��б༭���½���Ⱥ�飨���ţ�������ԴȨ��
	====================================================================*/
	bool EB_CanEditGroupRes(eb::bigint nGroupId) const;

	/******
	���ܣ��ж��Ƿ���ɾ��Ⱥ�飨���ţ�������ԴȨ��
	====================================================================*/
	bool EB_CanDeleteGroupRes(eb::bigint nGroupId) const;

	/* �������̹��� ***********************************************************************/
	/****
	���ܣ�����������Դ�������������
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ�����Ⱥ����Դ����Ϊ���ظ���������Դ
	====================================================================*/
	int EB_LoadRes(eb::bigint nGroupId=0);

	/****
	���ܣ���ȡĿ¼����������Դ
	====================================================================*/
	void EB_GetDirAllRes(eb::bigint sParentResId,std::vector<EB_ResourceInfo>& pOutResourceList) const;

	/****
	���ܣ���ȡû��Ŀ¼��������Դ
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ���ȡȺ����Դ����Ϊ��ȡ����������Դ
	====================================================================*/
	void EB_GetNotDirAllRes(std::vector<EB_ResourceInfo>& pOutResourceList,eb::bigint nGroupId=0) const;

	/****
	���ܣ��ж�Ŀ¼��Դ�£��Ƿ�����Դ��Ϣ
	====================================================================*/
	bool EB_HasSubRes(eb::bigint sParentResId) const;

	/****
	���ܣ���ȡ��������Դ
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ���ȡȺ����Դ����Ϊ��ȡ����������Դ
	====================================================================*/
	void EB_GetAllRes(std::vector<EB_ResourceInfo>& pOutResourceList,eb::bigint nGroupId=0) const;

	/****
	���ܣ���ȡ�������ļ���Դ
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ���ȡȺ����Դ����Ϊ��ȡ����������Դ
	====================================================================*/
	void EB_GetAllFileRes(std::vector<EB_ResourceInfo>& pOutResourceList,eb::bigint nGroupId=0) const;

	/****
	���ܣ���ȡ�����Ʊʼ���Դ
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ���ȡȺ����Դ����Ϊ��ȡ����������Դ
	====================================================================*/
	void EB_GetAllNoteRes(std::vector<EB_ResourceInfo>& pOutResourceList,eb::bigint nGroupId=0) const;

	/****
	���ܣ�����Ŀ¼��Դ
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ�����Ⱥ����Դ����Ϊ���Ӹ���������Դ
	====================================================================*/
	int EB_AddDirRes(const char* sDirName,eb::bigint sParentResId=0,eb::bigint nGroupId=0);

	/****
	���ܣ������ļ���Դ
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ�����Ⱥ����Դ����Ϊ���Ӹ���������Դ
	====================================================================*/
	int EB_AddFileRes(const char* sFilePath,const char* sFileName,const char* sDescription,eb::bigint sParentResId=0,eb::bigint nGroupId=0);

	/****
	���ܣ�������ʱȺ���ļ���Դ
	������nGroupId Ⱥ�飨���ţ����룻
	====================================================================*/
	int EB_AddTempGroupFileRes(const char* sFilePath,const char* sFileName,eb::bigint nGroupId);

	/****
	���ܣ��������߱ʼ���Դ
	������sGroupCode Ⱥ�飨���ţ����룻��Ϊ�գ�����Ⱥ����Դ����Ϊ���Ӹ���������Դ
	====================================================================*/
	int EB_AddNoteRes(const char* sNoteName,const char* sDescription,eb::bigint sParentResId=0,eb::bigint nGroupId=0);

	/****
	���ܣ��޸�������Դ
	====================================================================*/
	int EB_EditRes(eb::bigint sResId,const char* sName,const char* sDescription);

	/****
	���ܣ��ƶ���Դ��ָ��Ŀ¼��
	====================================================================*/
	int EB_MoveRes2Dir(eb::bigint sResId,eb::bigint sParentResId);

	/****
	���ܣ�ɾ��������Դ
	====================================================================*/
	int EB_DeleteRes(eb::bigint sResId);

	/****
	���ܣ���ȡ��Դ������Ϣ
	====================================================================*/
	bool EB_GetResourceInfo(eb::bigint sResId,EB_ResourceInfo* pOutResourceInfo);

	/****
	���ܣ���ȡ��Դ������Ϣ
	====================================================================*/
	bool EB_GetResourceCmInfo(eb::bigint sResId,mycp::tstring& pOutResourceInfo);


	/****
	���ܣ�����������Դ�ļ�
	====================================================================*/
	int EB_DownloadFileRes(eb::bigint sResId,const char * sSaveTo);

	/****
	���ܣ�ȡ���ϴ��������أ�������Դ�ļ�
	====================================================================*/
	int EB_CancelFileRes(eb::bigint sResId,eb::bigint nMsgId);

	//bool UpdateInfo(const CPopParameterList& pInfoList);
	//bool EnterChat(eb::bigint nCallId, const char* sAccount);	// ��¼����״��
	//bool ExitChat(eb::bigint nCallId, const char* sAccount);	// ��¼����״��

	/* �Ự���� ***********************************************************************/
	/****
	���ܣ�����Ⱥ���Ա
	������sMemberCode �����û��ʺţ�Ⱥ�飨���ţ���Ա���
	������sExistCallId ��Ϊ�գ���ʾ�����û������˻Ự
	====================================================================*/
	int EB_CallMember(eb::bigint nMemberId,eb::bigint nExistCallId=0);

	/****
	���ܣ������û�
	������sToAccount �����û��ʺ�
	������sExistCallId ��Ϊ�գ���ʾ�����û������˻Ự
	====================================================================*/
	int EB_CallAccount(const char* sToAccount,eb::bigint nExistCallId=0);
	int EB_CallUserId(eb::bigint nToUserId,eb::bigint nExistCallId=0);

	/****
	���ܣ��Ự�����Ա��ת��ʱ������
	������sCallId �ỰID
	������sToAccount ��Ϊ�գ�����������û�
	������sMemberCode ����������û���Ⱥ�飨���ţ���Ա���
	====================================================================*/
	int EB_Call2Group(eb::bigint nCallId,const char* sToAccount);

	/****
	���ܣ�����Ⱥ�飨���ţ��Ự
	������sGroupCode Ⱥ�飨���ţ����
	====================================================================*/
	int EB_CallGroup(eb::bigint nGroupId);

	/****
	���ܣ�Ӧ��һ���Ự����
	������bAccept true:���ܻỰ��false:�ܾ��Ự
	====================================================================*/
	int EB_CallAnswer(eb::bigint nCallId,bool bAccept);

	/****
	���ܣ��ҶϻỰ
	�������Է����յ��ҶϻỰ�¼����������ҶϻỰ��ʹ��EB_CallExit
	====================================================================*/
	int EB_CallHangup(eb::bigint nCallId);

	/****
	���ܣ��˳��Ự
	�����������ϲ��˳����촰�ڣ���ջỰ
	====================================================================*/
	void EB_CallExit(eb::bigint nCallId);

	/****
	���ܣ����ͻỰ֪ͨ
	������nNotifyType=1: �û���������
	====================================================================*/
	void EB_CallNotify(eb::bigint nCallId, eb::bigint nToUserId, int nNotifyType, eb::bigint nNotifyId, const char* sNotifyData);

	/****
	���ܣ����Ự��Ա����Ա���ߣ����º���
	����ֵ��0=�����Ự��1=�������º������߳�Ա��-1=�Ự�����ڵ���������
	====================================================================*/
	//int EB_CheckReCall(eb::bigint nCallId,bool bOffReCall);

	/****
	���ܣ��Ự����RICH��ʽ�������һ���ı�
	====================================================================*/
	void EB_RichBufferAddText(eb::bigint nCallId,const char* sText);

	/****
	���ܣ��Ự����RICH��ʽ�������һ��ͼƬ������JPG��
	====================================================================*/
	void EB_RichBufferAddObject(eb::bigint nCallId,const char* pData,unsigned long nSize);

	/****
	���ܣ��Ự����RICH��ʽ�������һ����Դ��������飩
	====================================================================*/
	void EB_RichBufferAddResource(eb::bigint nCallId,const char* sResource);

	/****
	���ܣ���ջỰ����RICH��ʽ����
	====================================================================*/
	void EB_RichBufferClear(eb::bigint nCallId);

	/****
	���ܣ����ͻỰ����RICH��ʽ�������ݣ���������Զ���ջ���
	������sToAccount �����Ự��ָ���û���������Ⱥ��Ự�У�
	������bPrivate ���Ļ����� true:��˽�ķ�ʽ����ָ���û����Ự�����˿����� false:�Ự������ԱҲ���Կ���
	====================================================================*/
	int EB_SendRichBuffer(eb::bigint nCallId,eb::bigint nToUserId=0,bool bPrivate=false);

	/****
	���ܣ������ı���Ϣ
	������sTextMsg �ı���Ϣ
	������sToAccount �����Ự��ָ���û���������Ⱥ��Ự�У�
	������bPrivate ���Ļ����� true:��˽�ķ�ʽ����ָ���û����Ự�����˿����� false:�Ự������ԱҲ���Կ���
	====================================================================*/
	int EB_SendText(eb::bigint nCallId,const char* sTextMsg,eb::bigint nToUserId=0,bool bPrivate=false);

	/****
	���ܣ�����RICH��Ϣ
	������pRichMsg RICH����ʽ������TEXT��JPGͼƬ
	������sToAccount �����Ự��ָ���û���������Ⱥ��Ự�У�
	������bPrivate ���Ļ����� true:��˽�ķ�ʽ����ָ���û����Ự�����˿����� false:�Ự������ԱҲ���Կ���
	====================================================================*/
	int EB_SendRich(eb::bigint nCallId,const EB_ChatRoomRichMsg* pRichMsg,eb::bigint nToUserId=0,bool bPrivate=false);
	int EB_SendMapPos(eb::bigint nCallId,const char* sMapPosData,eb::bigint nToUserId=0,bool bPrivate=false);
	int EB_SendUserData(eb::bigint nCallId,const char* sUserData,unsigned long nDataSize,eb::bigint nToUserId=0,bool bPrivate=false);

	/****
	���ܣ������ļ�
	������sFilePath �����ļ�·��
	������sToAccount �����Ự��ָ���û���������Ⱥ��Ự�У�
	������bPrivate ���Ļ����� true:��˽�ķ�ʽ����ָ���û����Ự�����˿����� false:�Ự������ԱҲ���Կ���
	������bOffFile ���������ļ� false/true
	====================================================================*/
	int EB_SendFile(eb::bigint nCallId,const char* sFilePath,eb::bigint nToUserId=0,bool bPrivate=false,bool bOffFile=false);

	/****
	���ܣ������ļ�
	������nMsgId �ļ���Ϣ���
	������sSaveTo �����ļ�
	====================================================================*/
	int EB_AcceptFile(eb::bigint nCallId,eb::bigint nMsgId,const char * sSaveTo);

	/****
	���ܣ����������ļ����ҵ�����
	������nMsgId �ļ���Ϣ���
	====================================================================*/
	int EB_Save2CloudDrive(eb::bigint nCallId,eb::bigint nMsgId);

	/****
	���ܣ����������ļ�����Դ�ļ���
	������sResId �����ļ���Դ���
	������sSaveTo ����·��
	====================================================================*/
	//int EB_AcceptFileRes(eb::bigint nCallId,const char * sResId,const char * sSaveTo);

	/****
	���ܣ�ȡ����ܾ������ļ�
	������nMsgId �ļ���Ϣ���
	====================================================================*/
	int EB_CancelFile(eb::bigint nCallId,eb::bigint nMsgId);

	/****
	���ܣ���ȡ�Ự��Ա��Ϣ
	====================================================================*/
	bool EB_GetCallAccountInfoList(eb::bigint nCallId,std::vector<EB_AccountInfo>& pOutUserList) const;
	bool EB_GetCallUserIdList(eb::bigint nCallId,std::vector<eb::bigint>& pOutUserList) const;
	bool EB_GetCallAccountList(eb::bigint nCallId,std::vector<mycp::tstring>& pOutUserList) const;

	/****
	���ܣ���ȡ�Ự��ǰ�����û�����
	====================================================================*/
	//int EB_GetCallOnlineSize(eb::bigint nCallId) const;

	/****
	���ܣ���ȡ�Ựָ���û���Ϣ
	====================================================================*/
	bool EB_GetCallAccountInfo(eb::bigint nCallId,eb::bigint nUserId,EB_AccountInfo* pOutAccountInfo) const;

	/* ͨѶ¼����ϵ�ˣ� ***********************************************************************/
	/****
	���ܣ������ҵ�����ͨѶ¼����ϵ�ˣ����������з�����Ϣ
	��������¼�ɹ��󣬵��ü���һ��
	====================================================================*/
	int EB_LoadContact(void);

	/****
	���ܣ��޸ģ����½���һ���û�������Ϣ
	������nUGId �û�����ID��0��ʾ�½�
	������sGroupName �ּ����ƣ�����Ϊ��
	====================================================================*/
	int EB_EditUGInfo(eb::bigint nUGId, const char* sGroupName);

	/****
	���ܣ�ɾ��һ���û�������Ϣ
	====================================================================*/
	int EB_DeleteUGInfo(eb::bigint nUGId);

	/****
	���ܣ�ɾ��һ���û�������Ϣ
	====================================================================*/
	int EB_GetUGContactSize(eb::bigint nUGId, int& pOutContactSize, int& pOutOnlineSize);

	/****
	���ܣ���ȡ��ϵ����Ϣ�б�
	====================================================================*/
	void EB_GetUGInfoList(std::vector<EB_UGInfo>& pOutUGInfoList) const;

	/****
	���ܣ�������˺���
	====================================================================*/
	int EB_ReqAddContact(eb::bigint nContactUserId,const char * sDescription);

	/****
	���ܣ��޸ģ����½���һ����ϵ������
	====================================================================*/
	int EB_EditContact(const EB_ContactInfo* pContactInfo);

	/****
	���ܣ�ɾ��һ����ϵ������
	====================================================================*/
	int EB_DeleteContact(eb::bigint nContactId,bool bDeleteDest);
	//int EB_DeleteContact(const char* sContactAccount);

	/****
	���ܣ���ȡ��ϵ����Ϣ�б�
	====================================================================*/
	void EB_GetContactList(std::vector<EB_ContactInfo>& pOutContactList) const;

	/****
	���ܣ���ȡ��ϵ����Ϣ
	====================================================================*/
	bool EB_GetContactInfo1(eb::bigint nContactId,EB_ContactInfo* pOutContactInfo) const;
	bool EB_GetContactInfo2(eb::bigint nContactUserId,EB_ContactInfo* pOutContactInfo) const;
	//bool EB_GetContactInfo(const char* sContactAccount,EB_ContactInfo* pOutContactInfo) const;

	/****
	���ܣ��ж��Ƿ��ҵ���ϵ���ʺ�
	====================================================================*/
	bool EB_IsMyContactAccount1(eb::bigint nContactId) const;
	bool EB_IsMyContactAccount2(eb::bigint nContactUserId) const;
	//bool EB_IsMyContactAccount(const char* sContactAccount) const;

	/* ��ҵ��֯�ṹ������Ⱥ����Ϣ�� ***********************************************************************/
	/****
	���ܣ���������������ҵ��֯�ṹ�͸���Ⱥ��
	��������¼�ɹ��󣬵��ü���һ��
	====================================================================*/
	int EB_LoadOrg(void);

	/****
	���ܣ���������ָ��Ⱥ�飨���ţ���Ϣ
	������bLoadMember true:ͬʱ���س�Ա��Ϣ
	====================================================================*/
	int EB_LoadGroup(eb::bigint nGroupId,bool bLoadMember);

	/****
	���ܣ���ȡ��ҵ��Ϣ
	������sEnterpriseCode ��ҵ���룻��Ϊ��ǰĬ����ҵ����
	====================================================================*/
	bool EB_GetEnterpriseInfo(EB_EnterpriseInfo* pOutEnterpriseInfo,eb::bigint nEnterpriseCode=0) const;

	bool EB_IsEnterpriseUser(eb::bigint nEnterpriseCode=0) const;

	/****
	���ܣ���ȡ��ҵ����
	������sEnterpriseCodeΪ�գ���ȡ��ǰĬ����ҵ����
	====================================================================*/
	bool EB_GetEnterpriseName(mycp::tstring& pOutEnterpriseName,eb::bigint nEnterpriseCode=0) const;

	/****
	���ܣ���ȡ��ҵ�����û���Ϣ
	������sEnterpriseCode����ҵ����
	====================================================================*/
	void EB_GetEnterpriseMemberSize(eb::bigint nEnterpriseCode,int& pOutMemberSize,int& pOutOnlineSize) const;

	/****
	���ܣ��޸���ҵ����
	====================================================================*/
	int EB_EditEnterprise(const EB_EnterpriseInfo* pEnterpriseInfo);

	/****
	���ܣ��޸Ļ��½�Ⱥ�飨���ţ�������Ϣ
	������pGroupInfo->m_sGroupCodeΪ�գ���ʾ�½�
	====================================================================*/
	int EB_EditGroup(const EB_GroupInfo* pGroupInfo);

	/****
	���ܣ�ɾ�����Ż��ɢȺ��
	====================================================================*/
	int EB_DeleteGroup(eb::bigint nGroupId);

	/****
	���ܣ��������Ⱥ�飨���ţ�
	====================================================================*/
	int EB_JoinGroup(eb::bigint nGroupId,const char* sDescription);

	/****
	���ܣ��˳�Ⱥ�飨���ţ�
	====================================================================*/
	int EB_ExitGroup(eb::bigint nGroupId);

	/****
	���ܣ����ø���Ⱥ�飨���ţ�ͷ��
	������<= 1Mb
	====================================================================*/
	int EB_SetMyGroupHeadFile(eb::bigint nGroupId,const char* sImagePath);

	/****
	���ܣ����ø���Ⱥ�飨���ţ�ͷ��
	====================================================================*/
	int EB_SetMyGroupHeadRes(eb::bigint nGroupId,eb::bigint sResId);

	/****
	���ܣ���ȡȺ�飨���ţ���Ϣ
	====================================================================*/
	bool EB_GetGroupInfo(eb::bigint nGroupId,EB_GroupInfo* pOutGroupInfo) const;

	/****
	���ܣ���ȡȺ�飨���ţ�����
	====================================================================*/
	bool EB_GetGroupName(eb::bigint nGroupId,mycp::tstring& pOutGroupName) const;

	/****
	���ܣ���ȡȺ�飨���ţ�������
	====================================================================*/
	bool EB_GetGroupCreator(eb::bigint nGroupId,eb::bigint& pOutGroupCreator) const;

	/****
	���ܣ���ȡȺ�飨���ţ�����
	====================================================================*/
	bool EB_GetGroupType(eb::bigint nGroupId,EB_GROUP_TYPE& pOutGroupType) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա��Ϣ
	====================================================================*/
	bool EB_GetGroupMemberInfoList(eb::bigint nGroupId,std::vector<EB_MemberInfo>& pOutMemberInfoList) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա�ʺ�
	====================================================================*/
	bool EB_GetGroupMemberUserIdList(eb::bigint nGroupId,std::vector<eb::bigint>& pOutMemberUserIdList) const;
	bool EB_GetGroupMemberCodeList(eb::bigint nGroupId,std::vector<eb::bigint>& pOutMemberCodeList) const;
	bool EB_GetGroupMemberAccountList(eb::bigint nGroupId,std::vector<mycp::tstring>& pOutMemberAccountList) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա����
	====================================================================*/
	int EB_GetGroupMemberSize(eb::bigint nGroupId) const;

	/****
	���ܣ���ȡȺ�飨���ţ����߳�Ա����
	====================================================================*/
	int EB_GetGroupOnlineSize(eb::bigint nGroupId) const;

	/****
	���ܣ��ж��Ƿ����ҵ�Ⱥ�飨���ţ�
	������sGroupCode Ⱥ�飨���ţ�����
	====================================================================*/
	bool EB_IsMyGroup(eb::bigint nGroupId) const;

	/****
	���ܣ��޸Ļ��½�Ⱥ�飨���ţ���Ա��Ϣ����Ҫ������Ӳ���Ա�����޸�Ա������
	������pMemberInfo->m_sMemberCode��Ա���Ϊ�գ���ʾ�½�
	====================================================================*/
	int EB_EditMember(const EB_MemberInfo* pMemberInfo);

	bool EB_IsGroupAdminLevel(eb::bigint nGroupId) const;	// �Ƿ�Ⱥ�����ԱȨ��
	bool EB_IsGroupAdminLevel(eb::bigint nGroupId, eb::bigint nMemberUserId) const;	// �Ƿ�Ⱥ�����ԱȨ��
	int EB_AddGroupAdminLevel(eb::bigint nGroupId, eb::bigint nMemberUserId);	// ����Ⱥ�����ԱȨ��
	int EB_DelGroupAdminLevel(eb::bigint nGroupId, eb::bigint nMemberUserId);	// ɾ��Ⱥ�����ԱȨ��

	/****
	���ܣ�ɾ��Ⱥ�飨���ţ���Ա
	====================================================================*/
	int EB_DeleteMember(eb::bigint nMemberId, bool bDeleteAccount=true);

	/****
	���ܣ���ȡȺ�飨���ţ���Ա��Ϣ
	====================================================================*/
	bool EB_GetMemberInfoByUserId(EB_MemberInfo* pOutMemberInfo,eb::bigint nGroupId,eb::bigint nMemberUserId) const;
	bool EB_GetMemberInfoByAccount(EB_MemberInfo* pOutMemberInfo,eb::bigint nGroupId,const char* sMemberAccount) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա��Ϣ
	====================================================================*/
	bool EB_GetMemberInfoByUserId2(EB_MemberInfo* pOutMemberInfo,eb::bigint nMemberUserId) const;
	bool EB_GetMemberInfoByAccount2(EB_MemberInfo* pOutMemberInfo,const char* sMemberAccount) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա��Ϣ
	====================================================================*/
	bool EB_GetMemberInfoByMemberCode(EB_MemberInfo* pOutMemberInfo,eb::bigint nMemberId) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա����
	====================================================================*/
	bool EB_GetMemberNameByUserId(eb::bigint nGroupId,eb::bigint nMemberUserId,mycp::tstring& pOutMemberName) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա����
	====================================================================*/
	bool EB_GetMemberNameByMemberCode(eb::bigint nMemberId,mycp::tstring& pOutMemberName) const;

	/****
	���ܣ���ȡȺ�飨���ţ���Ա����״̬
	====================================================================*/
	bool EB_GetMemberLineState(eb::bigint nMemberId,EB_USER_LINE_STATE& pOutLineState) const;

	/****
	���ܣ���ȡȺ�飨���ţ�ͷ���ļ�
	====================================================================*/
	bool EB_GetMemberHeadFile(eb::bigint nMemberId,eb::bigint& pOutResourceId,mycp::tstring& pOutHeadPath,int& pOutFileSize);
	bool EB_GetMemberHeadFile(eb::bigint nGroupId,eb::bigint nUserId,eb::bigint& pOutResourceId,mycp::tstring& pOutHeadPath,int& pOutFileSize);

	/****
	���ܣ���ȡ�ҵ�Ⱥ�飨���ţ���Ա��Ϣ
	������sGroupCode Ⱥ����Ϊ�գ���ȡĬ��Ⱥ���Ա��Ϣ
	====================================================================*/
	bool EB_GetMyMemberInfo(EB_MemberInfo* pOutMemberInfo,eb::bigint nGroupId=0) const;

	/****
	���ܣ���ȡ�ҵ�����Ⱥ�飨���ţ���Ա��Ϣ
	������������ҵ����Ա����Ϣ�͸���Ⱥ���Ա��Ϣ
	====================================================================*/
	void EB_GetMyMemberList(std::vector<EB_MemberInfo>& pOutMemberInfoList) const;

	/****
	���ܣ��ж��Ƿ����Ⱥ�飨���ţ���Ա
	������sGroupCode Ⱥ�飨���ţ�����
	������sMemberAccount ��Ա�ʺ�
	====================================================================*/
	bool EB_IsExistMemberByUserId(eb::bigint nGroupId,eb::bigint nMemberUserId) const;
	bool EB_IsExistMemberByAccount(eb::bigint nGroupId,const char* sMemberAccount) const;

	/****
	���ܣ��ж��Ƿ����Ⱥ�飨���ţ���Ա
	������sMemberCode ��Ա����
	====================================================================*/
	bool EB_IsExistMemberByMemberCode(eb::bigint nMemberId) const;

	/****
	���ܣ���ȡ�������Ϣ
	====================================================================*/
	bool EB_GetMyEmotionList(std::vector<EB_EmotionInfo>& pOutEmotionList) const;

	/****
	���ܣ���ȡĬ��ͷ����Ϣ
	====================================================================*/
	bool EB_GetDefaultHeadList(std::vector<EB_EmotionInfo>& pOutEmotionList) const;

	/**** �������� ***********************************************************************/
	/****
	���ܣ�������ҵ���в�����Ϣ����֯�ṹ��
	������sEnterpriseCodeΪ�գ�����Ĭ����ҵ
	������dwParam ��CEBSearchCallback�ص��������أ�
	====================================================================*/
	void EB_FindAllGroupInfo(CEBSearchCallback * pCallback,eb::bigint nEnterpriseCode=0,unsigned long dwParam=0);

	/****
	���ܣ���������ͨѶ¼����ϵ�ˣ���Ϣ
	������dwParam ��CEBSearchCallback�ص��������أ�
	====================================================================*/
	void EB_FindAllContactInfo(CEBSearchCallback * pCallback,unsigned long dwParam=0);

	/****
	���ܣ������û���������ҵ����Ա��������Ⱥ���Ա��ͨѶ¼�û�
	������sSearchKey �����ؼ��ʣ�""����������
	������dwParam ��CEBSearchCallback�ص��������أ�
	====================================================================*/
	void EB_SearchUserInfo(CEBSearchCallback * pCallback,const char* sSearchKey,unsigned long dwParam=0);

	/**** Զ�����棨Զ��Э���� ***********************************************************************/
	/****
	���ܣ�����ỰԶ�����棨Զ��Э����
	====================================================================*/
	int EB_RDRequest(eb::bigint nCallId,EB_REMOTE_DESKTOP_TYPE nRDType=EB_RD_DESKTOP_SRC);

	/****
	���ܣ� ���ܣ����룩��ܾ�Զ�����棨Զ��Э����
	������bAccept true:����Զ������ false:�ܾ�Զ������
	====================================================================*/
	int EB_RDAck(eb::bigint nCallId,bool bAccept,eb::bigint nToUserId);

	/****
	���ܣ� �������˳�Զ������
	====================================================================*/
	int EB_RDEnd(eb::bigint nCallId);

	void EB_SetDesktopHwnd(eb::bigint nCallId,HWND pHwnd);

	// quant : 1-20; default 12
	// fps : 0-10; 0=disable; default 2
	int EB_OpenLocalDesktop(eb::bigint nCallId, int quant=12, int fps = 2);
	// eb::bigint nUserId : 0 disable
	void EB_EnableControlLocalDesktop(eb::bigint nCallId, eb::bigint nUserId);
	eb::bigint EB_EnableControlLocalDesktop(eb::bigint nCallId) const;
	void EB_CloseLocalDesktop(eb::bigint nCallId);

	bool EB_OpenRemoteDesktop(eb::bigint nCallId,eb::bigint nUserId, HWND hWndParent);
	// int nMouseMoveFPS: 0: disable
	bool EB_ControlRemoteDesktop(eb::bigint nCallId,eb::bigint nUserId, int nMouseMoveFPS = 3);
	int EB_ControlRemoteDesktop(eb::bigint nCallId,eb::bigint nUserId) const;
	void EB_MoveRemoteDesktopWindow(eb::bigint nCallId, eb::bigint nUserId, int x, int y, int width, int height, BOOL bRepaint);
	void EB_CloseRemoteDesktop(eb::bigint nCallId,eb::bigint nUserId);

	void EB_CloseAllDesktop(eb::bigint nCallId);

	bool EB_GetUserRDInfo(eb::bigint nCallId,std::vector<EB_UserVideoInfo>& pOutVideoUserInfo) const;

	/**** ��ƵͨѶ ***********************************************************************/
	/****
	���ܣ���ȡ������Ƶ�豸�����б�
	====================================================================*/
	static void EB_GetVideoDeviceList(std::vector<mycp::tstring>& pOutVideoDeviceList);

	/****
	���ܣ���ȡĬ����Ƶý������
	====================================================================*/
	//static int EB_GetDefaultVideoMediaType(void);

	/****
	���ܣ����ûỰ��Ƶ��ʾ����ͳһ�ص�����
	====================================================================*/
	void EB_SetVideoCallback(eb::bigint nCallId, PEBVideoCallBack cbAudio);
	//void EB_SetVideoCallback(eb::bigint nCallId,PVideoDataCallBack cbVideo,PAudioDataCallBack cbAudio);

	/****
	���ܣ����ûỰ��Ƶҵ��ص����ھ������Ϊȡ����ʹ��Ĭ�Ͼ�� EB_SetMsgHwnd
	====================================================================*/
	void EB_SetVideoHwnd(eb::bigint nCallId,HWND pHwnd);

	/****
	���ܣ�ȡ���Ự��Ƶҵ��ص����ھ����ʹ��Ĭ�Ͼ�� EB_SetMsgHwnd
	====================================================================*/
	//void EB_DelVideoHwnd(eb::bigint nCallId);

	/****
	���ܣ�����Ự��ƵͨѶ
	====================================================================*/
	int EB_VideoRequest(eb::bigint nCallId,EB_VIDEO_TYPE nVideoType=EB_VIDEO_BOTH);

	/****
	���ܣ� ���ܣ����룩��ܾ��Ự��ƵͨѶ
	������bAccept true:������ƵͨѶ false:�ܾ���ƵͨѶ
	====================================================================*/
	int EB_VideoAck(eb::bigint nCallId,bool bAccept,eb::bigint nToUserId);

	/****
	���ܣ� �������˳��Ự��ƵͨѶ
	====================================================================*/
	int EB_VideoEnd(eb::bigint nCallId);

	/****
	���ܣ� ��ȡ�Ự�������û���Ƶ��ţ�
	====================================================================*/
	bool EB_GetUserVideoInfo(eb::bigint nCallId,std::vector<EB_UserVideoInfo>& pOutVideoUserInfo) const;

	/****
	���ܣ��򿪻Ự��������Ƶ�豸
	������������Ƶ���󣬴���Ƶ�豸���������豸�������ͬʱ�򿪣�
	������sCallId �Ự���
	������nLocalVideoIndex ��ָ������λ����Ƶ�豸��0��ʼ��EB_VIDEO_BOTH��Ч��
	������[���]���ر�����Ƶý�����ͣ�������Ƶ��ʾ��
	������PAudioDataCallBack cbAudio ��Ƶ���ݻص�����
	������void* pParam ��Ƶ���ݻص�����
	���أ����ر����û���Ƶ��� -1��ʾʧ��
	====================================================================*/
	int EB_OpenLocalVideo(eb::bigint nCallId,int nLocalVideoIndex,HWND hVideoWndParent, void* pUserData=0);
	//int EB_OpenLocalVideo(eb::bigint nCallId,int nLocalVideoIndex,int& pOutVideoMediaType,DWORD dwParamVideo,DWORD dwParamAudio);


	/****
	���ܣ��򿪻Ự��Զ���û���Ƶ
	������sCallId �Ự���
	������sUserAccount �Ự�û��ʺ�
	������PAudioDataCallBack cbAudio ��Ƶ���ݻص�����
	������void* pParam ��Ƶ���ݻص�����
	====================================================================*/
	bool EB_OpenUserVideo(eb::bigint nCallId,eb::bigint nUserId,HWND hVideoWndParent, void* pUserData=0);
	//bool EB_OpenVideo(eb::bigint nCallId,eb::bigint nUserId,DWORD dwParamVideo,DWORD dwParamAudio);

	/****
	���ܣ����ô򿪻�������Ƶ
	������sCallId �Ự���
	������nUserId �Ự�û��ʺ�
	������bOpen �򿪻�������Ƶ
	====================================================================*/
	bool EB_SetVideoOpenClose(eb::bigint nCallId,eb::bigint nUserId,bool bOpen);

	/****
	���ܣ����ô򿪻���������
	������sCallId �Ự���
	������nUserId �Ự�û��ʺ�
	������bOpen �򿪻���������
	====================================================================*/
	bool EB_SetAudioOpenClose(eb::bigint nCallId,eb::bigint nUserId,bool bOpen);
	//bool EB_GetAudioOpenClose(eb::bigint nCallId,eb::bigint nUserId) const;

	/****
	���ܣ��رջỰ������Ƶ
	====================================================================*/
	void EB_CloseAllVideo(eb::bigint nCallId);

	/**** Ӧ�ù��� ***********************************************************************/
	/****
	���ܣ����ݶ�λλ�ã���ȡ����Ӧ�ù�����Ϣ
	������nFuncLocation����λλ��
	====================================================================*/
	int EB_GetSubscribeFuncList(EB_FUNC_LOCATION nFuncLocation,std::vector<EB_SubscribeFuncInfo>& pOutFuncInfo) const;

	/****
	���ܣ����ݶ�λλ�ã���ȡ����Ӧ�ù�������
	������nFuncLocation����λλ��
	====================================================================*/
	int EB_GetSubscribeFuncSize(EB_FUNC_LOCATION nFuncLocation) const;

	/****
	���ܣ����ݶ���ID����ȡ����Ӧ�ù�����Ϣ
	������nSubId������ID
	====================================================================*/
	bool EB_GetSubscribeFuncInfo(eb::bigint nSubId, EB_SubscribeFuncInfo* pOutFuncInfo) const;

	/****
	���ܣ���ĳ��Ӧ�ù���
	������nSubscribeId������ID
	====================================================================*/
	mycp::tstring EB_GetSubscribeFuncUrl(eb::bigint nSubscribeId,eb::bigint nCallId=0,eb::bigint nFromUserId=0,const mycp::tstring& sFromAccount="",eb::bigint nGroupId=0) const;

	/****
	���ܣ���ȡ���������¼URL
	������nSubscribeId������ID
	====================================================================*/
	mycp::tstring EB_GetConversationsUrl(eb::bigint nFromUserId,eb::bigint nGroupId) const;

	/****
	���ܣ����ܻ�ܾ�ĳ��ҵ���������������Ⱥ�飩
	������sMsgId����ϢID
	������bAccept�����ܻ�ܾ� true/false
	====================================================================*/
	void EB_AckMsg(eb::bigint nMsgId,bool bAccept) const;
	// 1=���ܣ�ȷ�ϣ�; 2=�ܾ�; 3=���߽���; 4=��ʱ; 5=ɾ��
	void EB_AckMsg(eb::bigint nMsgId,int nAckType) const;

private:
	void* m_handle;
};

} // namespace entboost

#endif // __EBAppClient_h__
