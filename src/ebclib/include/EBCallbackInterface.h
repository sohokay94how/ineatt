// EBCallbackInterface.h file here

#ifndef __EBCallbackInterface_h__
#define __EBCallbackInterface_h__
#ifdef WIN32
#include "Windows.h"
#endif // WIN32
#include "eb_object.h"
#include "chatroomhandle.h"

namespace entboost {

//�����ص�����
class CEBSearchCallback
{
public:
	virtual void onGroupInfo(const EB_GroupInfo* pGroupInfo,const EB_EnterpriseInfo* pEnterpriseInfo, unsigned long dwParam) = 0;
	virtual void onMemberInfo(const EB_GroupInfo* pGroupInfo, const EB_MemberInfo* pMemberInfo, unsigned long dwParam) = 0;
	virtual void onContactInfo(const EB_ContactInfo* pContactInfo, unsigned long dwParam) = 0;
};

#define EB_CALLBACK_FIRST_VIDEO_FPS	1
#define EB_CALLBACK_VOICE_VOLUME	2
typedef void (*PEBVideoCallBack) (eb::bigint nUserId, int nCallBackType, unsigned int lParam, unsigned int wParam, void* pUserData);


// Ӧ�ûص�����
class CEBCallbackInterface
#ifdef USES_CHATROOM
	: public CChatRoomCallBack
#endif
{
public:
	// APP
	virtual void onAppIdSuccess(eb::bigint appId,const char* appOnlineKey) {}
	virtual void onAppIdError(EB_STATE_CODE nState) {}

	virtual void onLogonAppCenter(EB_STATE_CODE nState) {}
	virtual void onLogoutAppCenter(EB_STATE_CODE nState) {}
	virtual int onAPMsgInfo(const EB_APMsgInfo& pAPMsgInfo) {return 1;}	// ����1���Զ���Ӧ

	virtual void onRegisterResponse(EB_STATE_CODE nState,eb::bigint nUserId) {}

	virtual void onOAuthForward(const std::string& sOAuthUrl) {}
	virtual void onLogonSuccess(const EB_AccountInfo& pAccountInfo) {}
	virtual void onLogonTimeout(const EB_AccountInfo& pAccountInfo) {}
	virtual void onLogonError(const EB_AccountInfo& pAccountInfo,EB_STATE_CODE nState) {}
	virtual void onOnlineAnother(void) {}	// �������ط���¼
	virtual void onLogout(void) {}
	virtual void onAccountInfoChange(const EB_AccountInfo& pAccountInfo) {}

	virtual void onEditInfoResponse(EB_STATE_CODE nState, int nFlag) {}								// ���������޸ķ���
	virtual void onUserStateChange(const EB_MemberInfo* pMemberInfo, bool bIsOwnerMember) {}		// �޸�����״̬
	virtual void onUserHeadChange(const EB_MemberInfo* pMemberInfo, bool bIsOwnerMember) {}			// �޸�Ⱥ��ͷ��

	// ���У��Ự��
	virtual void onCallIncoming(const EB_CallInfo& pCallInfo, const EB_AccountInfo& pFromAccount) {}
	virtual void onCallAlerting(const EB_CallInfo& pCallInfo) {}
	virtual void onCallBusy(const EB_CallInfo& pCallInfo) {}
	virtual void onCallHangup(const EB_CallInfo& pCallInfo, bool bOwner) {}
	virtual void onCallError(const EB_CallInfo& pCallInfo,EB_STATE_CODE nState) {}
	virtual void onCallConnected(const EB_CallInfo& pCallInfo, int nConnectFlag) {}

	// Զ�����棨Զ��Э����
	virtual void onRDRequestResponse(const EB_RemoteDesktopInfo& pRDInfo, EB_STATE_CODE nState) {}
	virtual void onRDAckResponse(const EB_RemoteDesktopInfo& pRDInfo, EB_STATE_CODE nState) {}
	virtual void onRDRequest(const EB_RemoteDesktopInfo& pRDInfo) {}									// �յ�һ��RD��������
	virtual void onRDAccept(const EB_RemoteDesktopInfo& pRDInfo) {}										// �Է�����RD
	virtual void onRDReject(const EB_RemoteDesktopInfo& pRDInfo) {}										// �Է��ܾ�RD
	virtual void onRDClose(const EB_RemoteDesktopInfo& pRDInfo) {}										// �Է��ر�RD

	// ��Ƶ
	virtual void onVRequestResponse(const EB_VideoInfo& pVideoInfo, EB_STATE_CODE nState) {}
	virtual void onVAckResponse(const EB_VideoInfo& pVideoInfo, EB_STATE_CODE nState) {}
	virtual void onVideoRequest(const EB_VideoInfo& pVideoInfo, const EB_UserVideoInfo& sFromAccount) {}		// �յ�һ����Ƶ��������
	virtual void onVideoAccept(const EB_VideoInfo& pVideoInfo, const EB_UserVideoInfo& sFromAccount) {}		// �Է�������Ƶ
	virtual void onVideoReject(const EB_VideoInfo& pVideoInfo, const EB_UserVideoInfo& sFromAccount) {}		// �Է��ܾ���Ƶ
	virtual void onVideoTimeout(const EB_VideoInfo& pVideoInfo, const EB_UserVideoInfo& sFromAccount) {}	// ��Ƶ����ʱ
	virtual void onVideoClose(const EB_VideoInfo& pVideoInfo, const EB_UserVideoInfo& sFromAccount) {}		// �Է��ر���Ƶ
	
	// ��֯�ṹ
	virtual void onEnterpriseInfo(const EB_EnterpriseInfo* pEnterpriseInfo) {}						// 
	virtual void onGroupInfo(const EB_GroupInfo* pGroupInfo, bool bIsMyGroup) {}			// 
	virtual void onGroupDelete(const EB_GroupInfo* pGroupInfo, bool bIsMyGroup) {}			//
	virtual void onGroupEditError(const EB_GroupInfo* pGroupInfo, EB_STATE_CODE nState) {}			//
	virtual void onRemoveGroup(const EB_GroupInfo* pGroupInfo, const EB_MemberInfo* pMemberInfo) {}			// ��Ա���Ƴ�Ⱥ��
	virtual void onExitGroup(const EB_GroupInfo* pGroupInfo, const EB_MemberInfo* pMemberInfo) {}			// �û��˳�Ⱥ��
	virtual void onRequestAdd2Group(const EB_AccountInfo* pAccountInfo,const EB_APMsgInfo* pApMsgInfo) {}	// �û��������Ⱥ��
	virtual void onInviteAdd2Group(const EB_AccountInfo* pAccountInfo,const EB_APMsgInfo* pApMsgInfo) {}	// �û��������Ⱥ��
	virtual void onRejectAdd2Group(const EB_AccountInfo* pAccountInfo,const EB_APMsgInfo* pApMsgInfo) {}	// �ܾ�����Ⱥ��
	virtual void onMemberInfo(const EB_MemberInfo* pMemberInfo, bool bIsMyDefaultMember) {}							// 
	virtual void onMemberDelete(const EB_MemberInfo* pMemberInfo, bool bIsMyDefaultMember) {}						// 
	virtual void onMemberEditError(const EB_MemberInfo* pMemberInfo, EB_STATE_CODE nState) {}						// 

	// ͨѶ¼����ϵ�ˣ�
	virtual void onUGInfo(const EB_UGInfo* pUGInfo) {}							// 
	virtual void onUGDelete(const EB_UGInfo* pUGInfo) {}							// 
	virtual void onContactInfo(const EB_ContactInfo* pContactInfo) {}							// 
	virtual void onContactDelete(const EB_ContactInfo* pContactInfo) {}							// 
	virtual void onRequestAddContact(const EB_AccountInfo* pAccountInfo,const EB_APMsgInfo* pApMsgInfo) {}	// �û������Ϊ����
	virtual void onRejectAddContact(const EB_AccountInfo* pAccountInfo,const EB_APMsgInfo* pApMsgInfo) {}	// �Է��ܾ���Ϊ����
	virtual void onAcceptAddContact(const EB_ContactInfo* pContactInfo) {}									// ��Ϊ���ѳɹ�
	virtual void onContactStateChange(const EB_ContactInfo* pContactInfo) {}								// �޸�����״̬
	
	// ������Դ�����̣�
	virtual void onResourceInfo(const EB_ResourceInfo* pResourceInfo) {}							// 
	virtual void onResourceDelete(const EB_ResourceInfo* pResourceInfo) {}							// 
	virtual void onResourceMove(const EB_ResourceInfo* pResourceInfo,eb::bigint sOldParentResId) {}							// 

	virtual void onBroadcastMsg(const EB_AccountInfo* pAccountInfo,const EB_APMsgInfo* pApMsgInfo) {}	// �յ�һ���㲥��Ϣ
	virtual void onAreaInfo(const EB_AreaInfo* pAreaInfo,unsigned int nParameter) {}					// �յ�����������Ϣ

	virtual void onNewVersion(const EB_VersionInfo& pVersionInfo) {}		// ���°汾��Ҫ����
	typedef enum SERVER_STATE
	{
		SERVER_UNKNOWN		// ����״̬
		, SERVER_STOPED		// ������ֹͣ��ά��״̬�У���ʾ�û�
		, SERVER_MOVED		// ������ҵ���Ѿ�ת�ƣ���Ҫ���µ�¼
		, SERVER_RESTART	// �������Ѿ���������Ҫ���µ�¼
		, SERVER_TIMEOUT	// ���������ӳ�ʱ���п����Ǳ�����������
	};
	virtual void onServerChange(SERVER_STATE nServerState) {}			// ������״̬�ı�
	virtual void onStateCode(EB_STATE_CODE nStateCode, unsigned long nParam) {}			// ����״̬��
};

#ifdef EB_SERVER
#define WM_USER 0
#endif
#ifndef WM_USER
#define WM_USER 0
#endif

typedef enum EB_WINDOW_MESSAGE_TYPE
{
	EB_WM_UNKNOWN				= 0
	, EB_WM_APPID_SUCCESS		= WM_USER+0x101
	
	// EB_STATE_CODE nState = (EB_STATE_CODE)wp;
	, EB_WM_APPID_ERROR

	// EB_STATE_CODE nState = (EB_STATE_CODE)wp;
	, EB_WM_LOGON_APPCENTER
	, EB_WM_LOGOUT_APPCENTER

	// const EB_APMsgInfo* pAPMsgInfo = (const EB_APMsgInfo*)wp;
	, EB_WM_AP_MSG

	// EB_STATE_CODE nState = (EB_STATE_CODE)wp;
	// const char* pUserId = (const chat*)lp;
	, EB_WM_REGISTER_RESPONSE

	// EB_STATE_CODE nState = (EB_STATE_CODE)wp;
	// int nFlag = (int)lp;
	, EB_WM_EDITINFO_RESPONSE

	// const EB_MemberInfo* pMemberInfo = (const EB_MemberInfo*)wp;
	// bool bIsOwnerMember = (bool)(lp==1);
	, EB_WM_USER_STATE_CHANGE
	, EB_WM_USER_HEAD_CHANGE

	// const char* sOAuthUrl = (const char*)wp;
	, EB_WM_OAUTH_FORWARD

	// const EB_AccountInfo* pAccountInfo = (const EB_AccountInfo*)wp;
	, EB_WM_LOGON_SUCCESS
	, EB_WM_LOGON_TIMEOUT

	// const EB_AccountInfo* pAccountInfo = (const EB_AccountInfo*)wp;
	// EB_STATE_CODE nState = (EB_STATE_CODE)lp;
	, EB_WM_LOGON_ERROR

	, EB_WM_ONLINE_ANOTHER
	, EB_WM_LOGOUT
	// const EB_AccountInfo* pAccountInfo = (const EB_AccountInfo*)wp;
	, EB_WM_ACCOUNT_INFO_CHANGE

	/*==========================================================
	�Ự
	===========================================================*/
	// const EB_CallInfo* pCallInfo = (const EB_CallInfo*)wp;
	// const EB_AccountInfo* pFromAccount = (const EB_AccountInfo*)lp;
	, EB_WM_CALL_INCOMING	= WM_USER+0x201
	// const EB_CallInfo* pCallInfo = (const EB_CallInfo*)wp;
	, EB_WM_CALL_ALERTING
	, EB_WM_CALL_BUSY
	// const EB_CallInfo* pCallInfo = (const EB_CallInfo*)wp;
	// bool bOwner = (bool)(lp==1);
	, EB_WM_CALL_HANGUP
	// const EB_CallInfo* pCallInfo = (const EB_CallInfo*)wp;
	// EB_STATE_CODE nState = (EB_STATE_CODE)lp;
	, EB_WM_CALL_ERROR
	// const EB_CallInfo* pCallInfo = (const EB_CallInfo*)wp;
	// int nConnectFlag = (int)lp;
	, EB_WM_CALL_CONNECTED

	/*==========================================================
	��Ƶ
	===========================================================*/
	// const EB_VideoInfo* pVideoInfo = (const EB_VideoInfo*)wp;
	// EB_STATE_CODE nState = (EB_STATE_CODE)lp;
	, EB_WM_V_REQUEST_RESPONSE	= WM_USER+0x211
	, EB_WM_V_ACK_RESPONSE

	// const EB_VideoInfo* pVideoInfo = (const EB_VideoInfo*)wp;
	// const EB_UserVideoInfo* pUserVideoInfo = (const EB_UserVideoInfo*)lp;
	, EB_WM_VIDEO_REQUEST
	, EB_WM_VIDEO_ACCEPT
	, EB_WM_VIDEO_REJECT
	, EB_WM_VIDEO_TIMEOUT
	, EB_WM_VIDEO_CLOSE

	/*==========================================================
	��Ƶ
	===========================================================*/
	// const EB_RemoteDesktopInfo* pRemoteDesktopInfo = (const EB_RemoteDesktopInfo*)wp;
	// EB_STATE_CODE nState = (EB_STATE_CODE)lp;
	, EB_WM_RD_REQUEST_RESPONSE	= WM_USER+0x221
	, EB_WM_RD_ACK_RESPONSE

	// const EB_RemoteDesktopInfo* pRemoteDesktopInfo = (const EB_RemoteDesktopInfo*)wp;
	, EB_WM_RD_REQUEST
	, EB_WM_RD_ACCEPT
	, EB_WM_RD_REJECT
	, EB_WM_RD_CLOSE

	/*==========================================================
	��֯�ṹ
	===========================================================*/
	// const EB_EnterpriseInfo* pEnterpriseInfo = (const EB_EnterpriseInfo*)wp;
	, EB_WM_ENTERPRISE_INFO	= WM_USER+0x301

	// const EB_GroupInfo* pGroupInfo = (const EB_GroupInfo*)wp;
	// bool bIsMyGroup = (bool)(lp==1);
	, EB_WM_GROUP_INFO
	, EB_WM_GROUP_DELETE
	// const EB_GroupInfo* pGroupInfo = (const EB_GroupInfo*)wp;
	// EB_STATE_CODE nState = (EB_STATE_CODE)lp;
	, EB_WM_GROUP_EDIT_ERROR

	// const EB_GroupInfo* pGroupInfo = (const EB_GroupInfo*)wp;
	// const EB_MemberInfo* pMemberInfo = (const EB_MemberInfo*)lp;
	, EB_WM_REMOVE_GROUP
	, EB_WM_EXIT_GROUP

	// const EB_AccountInfo* pAccountInfo = (const EB_AccountInfo*)wp;
	// const EB_APMsgInfo* pApMsgInfo = (const EB_APMsgInfo*)lp;
	, EB_WM_REQUEST_ADD2GROUP
	, EB_WM_INVITE_ADD2GROUP
	, EB_WM_REJECT_ADD2GROUP

	// const EB_MemberInfo* pMemberInfo = (const EB_MemberInfo*)wp;
	// bool bIsMyDefaultMember = (bool)(lp==1);
	, EB_WM_MEMBER_INFO
	, EB_WM_MEMBER_DELETE
	// const EB_MemberInfo* pMemberInfo = (const EB_MemberInfo*)wp;
	// EB_STATE_CODE nState = (EB_STATE_CODE)lp;
	, EB_WM_MEMBER_EDIT_ERROR
	// const EB_AccountInfo* pAccountInfo = (const EB_AccountInfo*)wp;
	// const EB_APMsgInfo* pApMsgInfo = (const EB_APMsgInfo*)lp;
	, EB_WM_REQUEST_ADDCONTACT
	, EB_WM_REJECT_ADDCONTACT
	// const EB_ContactInfo* pContactInfo = (const EB_ContactInfo*)wp;
	, EB_WM_ACCEPT_ADDCONTACT

	/*==========================================================
	ͨѶ¼����ϵ�ˣ�
	===========================================================*/
	// const EB_ContactInfo* pContactInfo = (const EB_ContactInfo*)wp;
	, EB_WM_CONTACT_INFO	= WM_USER+0x311
	, EB_WM_CONTACT_DELETE

	// const EB_ResourceInfo* pResourceInfo = (const EB_ResourceInfo*)wp;
	, EB_WM_RESOURCE_INFO
	, EB_WM_RESOURCE_DELETE
	// const EB_ResourceInfo* pResourceInfo = (const EB_ResourceInfo*)wp;
	// const char* sOldParentResId = (const char*)lp;
	, EB_WM_RESOURCE_MOVE

	// const EB_UGInfo* pUGInfo = (const EB_UGInfo*)wp;
	, EB_WM_UG_INFO
	, EB_WM_UG_DELETE

	// const EB_ContactInfo* pContactInfo = (const EB_ContactInfo*)wp;
	, EB_WM_CONTACT_STATE_CHANGE

	// const EB_AccountInfo* pAccountInfo = (const EB_AccountInfo*)wp;
	// const EB_APMsgInfo* pApMsgInfo = (const EB_APMsgInfo*)lp;
	, EB_WM_BROADCAST_MSG		= WM_USER+0x321

	// const EB_AreaInfo* pAreaInfo = (const EB_AreaInfo*)wp;
	// unsigned int nParameter = (unsigned int)lp;
	, EB_WM_AREA_INFO

	// const EB_VersionInfo* pNewVersionInfo = (const EB_VersionInfo*)wp;
	, EB_WM_NEW_VERSION			= WM_USER+0x401

	// SERVER_STATE nServerState = (SERVER_STATE)wp;
	, EB_WM_SERVER_CHENGE		= WM_USER+0x411
	// EB_STATE_CODE nState = (EB_STATE_CODE)wp;
	, EB_WM_STATE_CODE
	, EB_WM_SUBSCRIBE_FUNC_INFO	= WM_USER+0x501

};

} // namespace entboost

#endif // __EBCallbackInterface_h__
