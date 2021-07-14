// eb_defines.h file here
#ifndef __eb_defines_h__
#define __eb_defines_h__
#include "eb_define1.h"

const mycp::bigint theMaxUserId		= 0x1000000000000LL;	// =281474976710656(15λ)
const mycp::bigint theVisitorStartId = 0x2000000000000LL;	// =562949953421312(15λ)
#define is_visitor_uid(id) (id>=theVisitorStartId)
//const int const_max_uid_length = 13;					// UID�13λ�����Դﵽ���ڼ���

typedef enum EB_TO_SHARE_TYPE
{
	EB_TO_SHARE_TYPE_UNKNOWN		//
	, EB_TO_SHARE_TYPE_TEMP				// ��ʱ���������������Զ������
}EB_TO_SHARE_TYPE;

typedef enum EB_SHARE_OWNER_TYPE
{
	EB_SHARE_OWNER_TYPE_UNKNOWN
	, EB_SHARE_OWNER_TYPE_USER				// �û�
	, EB_SHARE_OWNER_TYPE_GROUP			// Ⱥ��
}EB_SHARE_OWNER_TYPE;
typedef enum EB_SHARE_RESOURCE_TYPE
{
	EB_SHARE_RESOURCE_TYPE_RESOURCE		// ��Դ resource_id
	, EB_SHARE_RESOURCE_TYPE_BC_MSG		// �㲥��Ϣ msg_id
}EB_SHARE_RESOURCE_TYPE;

typedef enum EB_CONTACT_TYPE
{
	EB_CONTACT_TYPE_COMMON			= 0x0		// ��ͨ��ϵ��
	, EB_CONTACT_TYPE_AUTH			= 0x01	// ͨ����֤�����ѣ�
	, EB_CONTACT_TYPE_MAIL			= 0x10	// �ʼ���ϵ��
	, EB_CONTACT_TYPE_WHITE			= 0x20	// ������
	, EB_CONTACT_TYPE_BLACK			= 0x40	// ������
	, EB_CONTACT_TYPE_WASTE			= 0x80	// ����������
}EB_CONTACT_TYPE;

typedef enum EB_MAIL_CONTENT_FLAG
{
	EB_MAIL_CONTENT_FLAG_EDIT_MAIL
	, EB_MAIL_CONTENT_FLAG_SEND_MAIL
	, EB_MAIL_CONTENT_FLAG_RECEIVE_MAIL
	, EB_MAIL_CONTENT_FLAG_BLACK_MAIL
	, EB_MAIL_CONTENT_FLAG_WASTE_MAIL
	, EB_MAIL_CONTENT_FLAG_ARCHIVE_MAIL
	, EB_MAIL_CONTENT_FLAG_DELETE_FLAG1_MAIL	= 21
	, EB_MAIL_CONTENT_FLAG_DELETE_FLAG2_MAIL
}EB_MAIL_CONTENT_FLAG;

//typedef enum EB_NAMELIST_TYPE
//{
//	EB_NAMELIST_TYPE_OTHER_CONTACT	// ��ͨ��ϵ������
//	, EB_NAMELIST_TYPE_MAIL_CONTACT	// �ʼ���ϵ������
//	, EB_NAMELIST_TYPE_WHITE_LIST	// ������
//	, EB_NAMELIST_TYPE_BLACK_LIST	// ������
//	, EB_NAMELIST_TYPE_WASTE_LIST	// ����������
//};

typedef enum EB_MEMORY_LOAD_STATE
{
	EB_MEMORY_LOAD_STATE_INIT
	, EB_MEMORY_LOAD_ENT_DATA
	, EB_MEMORY_LOAD_GROUP_DATA
	, EB_MEMORY_LOAD_GROUP_VER_DATA
	, EB_MEMORY_LOAD_GROUP_MEMBER_DATA
	, EB_MEMORY_LOAD_USER_CONTACT_DATA
	, EB_MEMORY_LOAD_UNAUTH_DATA
	, EB_MEMORY_LOAD_OTHER_SERVER_ONLINE_ACCOUNT
	, EB_MEMORY_LOAD_FINISHED
}EB_MEMORY_LOAD_STATE;

#define EB_MAKELONG(lo, hi)    ((long)(((unsigned short)(((unsigned long)(lo)) & 0xffff)) | ((unsigned long)((unsigned short)(((unsigned long)(hi)) & 0xffff))) << 16))
#define EB_LOWORD(l)           ((unsigned short)(((unsigned long)(l)) & 0xffff))
#define EB_HIWORD(l)           ((unsigned short)((((unsigned long)(l)) >> 16) & 0xffff))
#define USES_OFFMSG_PARAM_VERSION2
/*==========================================================
������Ϣ��ʶ
===========================================================*/
typedef enum EB_OFFMSG_PARAM
{
	EB_OFFMSG_PARAM_NULL							= 0x0
	, EB_OFFMSG_PARAM_ACCEPT					= 0x001
	, EB_OFFMSG_PARAM_REJECT					= 0x002
	, EB_OFFMSG_PARAM_MSG							= 0x004
	, EB_OFFMSG_PARAM_SENDER_HIDE			= 0x008
	, EB_OFFMSG_PARAM_PRIVATE					= 0x010
#ifndef USES_OFFMSG_PARAM_VERSION2
	, EB_OFFMSG_PARAM_SUB_TYPE_AUDIO	= 0x020	// ????1.25(2017-01-12)�����ݾɰ汾��1.30�Ժ�ɾ���ô��룻
#endif
	, EB_OFFMSG_PARAM_RICH_CONTENT		= 0x040
	, EB_OFFMSG_PARAM_NOTIFY					= 0x080
}EB_OFFMSG_PARAM;

typedef enum PASSWD_AUTH_MODE
{
	PASSWD_AUTH_MODE_ENTBOOST
	, PASSWD_AUTH_MODE_MD5
	, PASSWD_AUTH_MODE_PBKDF2
}PASSWD_AUTH_MODE;


/*==========================================================
Ӧ�ù�����չ
===========================================================*/
typedef enum EB_FUNC_EXT
{
	EB_FUNC_EXT_UNKNOWN							// δ֪
	, EB_FUNC_EXT_DISABLE_CONTEXTMENU	= 0x1	// �����Ҽ��˵�
	, EB_FUNC_EXT_DISABLE_SCROLLBAR		= 0x2	// ���ι�����
	, EB_FUNC_EXT_CLOSE_PROMPT			= 0x10	// �رմ�����ʾ
	, EB_FUNC_EXT_WIN_RESIZABLE			= 0x20	// ���ڿɵ�����С
	, EB_FUNC_EXT_BROWSER_SET_CEF		= 0x100	// Chrome�����
	, EB_FUNC_EXT_BROWSER_SET_IE		= 0x200	// IE�����
}EB_FUNC_EXT;

/*==========================================================
��������
===========================================================*/
typedef enum EB_ENABLE_LEVEL
{
	EB_ENABLE_LEVEL_UNKNOWN
	, EB_ENABLE_LEVEL_VISITOR			= 0x01
	, EB_ENABLE_LEVEL_AUTH				= 0x02
	, EB_ENABLE_LEVEL_MSG				= 0x04
	, EB_ENABLE_LEVEL_NONE_REG_CODE		= 0x08	// û��reg_codeȨ�ޣ�����Ҫ������֤�ʼ�
	, EB_ENABLE_LEVEL_FUNC_AUTH			= 0x10	// 
	, EB_ENABLE_LEVEL_FUNC_MGR			= 0x20	// Ӧ�ù��ܹ���
	, EB_ENABLE_LEVEL_PUSH_MSG			= 0x40	// ��Ϣ���͹���
	, EB_ENABLE_LEVEL_EXECUTE_SQL		= 0x100	// 
	, EB_ENABLE_LEVEL_SELECT_SQL		= 0x200	// 

	, EB_ENABLE_LEVEL_DEV_MGR			= 0x10000	// ***������Ӧ�ù������ǳ���Ӧ�ù���Ȩ�ޣ�
	, EB_ENABLE_LEVEL_SYS_EDIT			= 0x20000	// ***ϵͳ���ù������ǳ���Ӧ�ù���Ȩ�ޣ�
	, EB_ENABLE_LEVEL_LICENSE_MGR		= 0x40000	// ***��Ȩ��ɹ������ǳ���Ӧ�ù���Ȩ�ޣ�
	//, EB_ENABLE_LEVEL_PWD_EDIT			= 0x80000	// ***����������ǳ���Ӧ�ù���Ȩ�ޣ�
}EB_ENABLE_LEVEL;
// 0x17 = 23
#define DEFAULT_LEVEL (EB_ENABLE_LEVEL_VISITOR|EB_ENABLE_LEVEL_AUTH|EB_ENABLE_LEVEL_MSG|EB_ENABLE_LEVEL_FUNC_AUTH)


/*==========================================================
����״̬
===========================================================*/
typedef enum EB_CALL_STATE
{
	EB_CALL_STATE_UNKNOWN
	, EB_CALL_STATE_INCOMING
	, EB_CALL_STATE_ALERTING
	, EB_CALL_STATE_CONNECTED
	, EB_CALL_STATE_INVALIDATE	// ����ʧЧ����Ҫ��������
	, EB_CALL_STATE_EXIT
	, EB_CALL_STATE_HANGUP
	, EB_CALL_STATE_ONLINE_INCALL
	, EB_CALL_STATE_AUTO_ACK
}EB_CALL_STATE;


/*==========================================================
��������
===========================================================*/
typedef enum EB_REQEUST_TYPE
{
	EB_REQ_TYPE_UNKNOWN
	, EB_REQ_TYPE_REG
	, EB_REQ_TYPE_LOGON
	, EB_REQ_TYPE_INVITE
	, EB_REQ_TYPE_DEP
	, EB_REQ_TYPE_FINPWD
	, EB_REQ_TYPE_USER_INFO
	, EB_REQ_TYPE_HTTP_REQ

}EB_REQEUST_TYPE;

/*==========================================================
��������
===========================================================*/
typedef enum EB_PUT_INFO_TYPE
{
	EB_PUT_INFO_UNKNOWN
	, EB_PUT_INFO_UPDATE_SYS_INFO				= 0x01
	, EB_PUT_INFO_SEND_BC_MSG//					= 0x02
	, EB_PUT_INFO_RESET_DEFAULT_PWD//				= 0x04
	, EB_PUT_INFO_ENT_GROUP_VERSION_CHANGE//		= 0x08
	, EB_PUT_INFO_GROUP_MEMBER_VERSION_CHANGE//	= 0x10
	, EB_PUT_INFO_GROUP_MEMBER_CHANGE		//	= 0x20
	, EB_PUT_INFO_GROUP_MEMBER_DELETE
	, EB_PUT_INFO_LC_STARTUP
	, EB_PUT_INFO_CHECK_USER_EMAIL				// um sendto ebsemail
	, EB_PUT_INFO_USER_RECEIVE_EMAIL			// ebsemail sendto um
	, EB_PUT_INFO_USER_ADD_EMAIL_CONTACT	// ebsemail sendto um
	, EB_PUT_INFO_UM_CURRENT_USERS				// um sendto lc
	, EB_PUT_INFO_LC_CURRENT_USERS				// lc sendto lc
	, EB_PUT_INFO_UNAUTH_ERROR						// um sendto lc
	, EB_PUT_INFO_GROUP_INFO_CHANGE				// um sendto cm
	, EB_PUT_INFO_GROUP_MEMBER_CHANGE2		// um sendto cm

}EB_PUT_INFO_TYPE;

/*==========================================================
��������
===========================================================*/
typedef enum EB_RESET_TYPE
{
	EB_RESET_UNKNOWN
	, EB_RESET_RESET_DEFAULT_PWD
	, EB_RESET_FREEZE_ACCOUNT
	, EB_RESET_ENABLE_ACCOUNT
	, EB_RESET_DELETE_ACCOUNT
	//, EB_RESET_ACTIVE_ACCOUNT

}EB_RESET_TYPE;

/*==========================================================
ͬ������
===========================================================*/
typedef enum EB_SYNC_TYPE
{
	EB_SYNC_UNKNOWN
	, EB_SYNC_EDIT_PWD
	, EB_SYNC_NEW_ACCOUNT
	, EB_SYNC_LINE_STATE

}EB_SYNC_TYPE;


/*==========================================================
�ֵ�����
===========================================================*/
typedef enum EB_DICT_TYPE
{
	EB_DICT_UNKNOWN
	, EB_DICT_AREA_DICT_LIST
	, EB_DICT_AREA_DICT_INFO

}EB_DICT_TYPE;


/*==========================================================
�û���չ����
===========================================================*/
typedef enum EB_ACCOUNT_DATA
{
	EB_DATA_DELETE_OFFLINE_CALL		= 0x01
	, EB_DATA_FROM_OFFLINE_USER		= 0x02
	, EB_DATA_GET_ENT_ID			= 0x04	// �Ƿ��Ѿ���ȡ��ҵID
	, EB_DATA_ERROR_LOAD_CALL		= 0x08	// �쳣���ػỰ��Ϣ
	, EB_DATA_OFF_MSG_CALL_USER		= 0x10	// ������Ϣ�����������û�
	, EB_DATA_LOAD_APP_SUB_INFO		= 0x20	// ����Ӧ�ù��ܶ�����Ϣ
	, EB_DATA_NEED_CHANGE_LINESTATE	= 0x40	// ��Ҫ֪ͨ����״̬
	, EB_DATA_LOAD_SYS_MSG			= 0x80	// �Ѿ�����ϵͳ��Ϣ
	//, EB_DATA_GET_DEVICE_TOKEN		= 0x100	// �Ƿ��Ѿ���ȡIOS SSL ID & DEVICE TOKEN
	, EB_DATA_GET_PHONE				= 0x200	// �Ƿ��Ѿ���ȡ phone
	, EB_DATA_GET_SYMMETRIC_CIPHER	= 0x400	// �Ƿ��Ѿ���ȡ �Գ�����SC
	, EB_DATA_GET_CURRENT_ONLINE	= 0x800	// �Ƿ�ǰ��¼UM
	, EB_DATA_SEND_FILE_CALL		= 0x1000	// �����ļ������Ƿ��Ѿ�����һ�Σ�
	, EB_DATA_CHECK_UNREAD_EMAIL	= 0x2000
	, EB_DATA_ADMIN_MEMBER				= 0x4000	// �����ԱȨ�ޣ����ܽ������ƣ�
	, EB_DATA_FORBID_SPEECH				= 0x8000	// ����
	, EB_DATA_GET_IOS_DEVICE_TOKEN				= 0x10000	// �Ƿ��Ѿ���ȡIOS SSL ID & DEVICE TOKEN
	, EB_DATA_GET_ANDROID_DEVICE_TOKEN		= 0x20000	// �Ƿ��Ѿ���ȡANDROID DEVICE TOKEN
}EB_ACCOUNT_DATA;

/*==========================================================
��Ϣ��չ����
===========================================================*/
typedef enum EB_MSG_DATA
{
	EB_MSG_DATA_OFFSET				= 0x01
	,EB_MSG_DATA_FILE_EXIST			= 0x02
	,EB_MSG_DATA_SEND_DS_ACK		= 0x04	// �Ѿ�����ack
	,EB_MSG_DATA_MSG_2_DB			= 0x08	// 
	,EB_MSG_DATA_MSG_2_FILE			= 0x10	// 
	,EB_MSG_DATA_UP_LOAD_FILE		= 0x20	// 
	,EB_MSG_DATA_FROM_LOCAL_FILE	= 0x40	// 
	,EB_MSG_DATA_SAVE_TO_FILE			= 0x80	// 
	,EB_MSG_DATA_FINISHED_TO_REMOVEFILE			= 0x100	// 
	,EB_MSG_DATA_RES_FROM_OFFMSG			= 0x100	// 
}EB_MSG_DATA;
/*==========================================================
��������
===========================================================*/
typedef enum EB_PERMIT_TYPE
{
	EB_PERMIT_TYPE_IP			= 0
	, EB_PERMIT_TYPE_APPID
}EB_PERMIT_TYPE;

/*==========================================================
��������
===========================================================*/
typedef enum EB_SERVER_TYPE
{
	EB_SERVER_TYPE_UNKNOWN
	, EB_SERVER_TYPE_LOGON_CENTER
	, EB_SERVER_TYPE_APP_CENTER
	, EB_SERVER_TYPE_USER_MANAGER	= 11
	, EB_SERVER_TYPE_CHAT_MANAGER
	, EB_SERVER_TYPE_VIDEO_MANAGE
	, EB_SERVER_TYPE_RD_MANAGER
	, EB_SERVER_TYPE_MMV_MANAGE
	, EB_SERVER_TYPE_MMA_MANAGE
	, EB_SERVER_TYPE_FILE_SERVER	= 20
}EB_SERVER_TYPE;

/*==========================================================
Ӧ������
===========================================================*/
typedef enum EB_APP_TYPE
{
	EB_APP_TYPE_CLIENT				= 0x0
	, EB_SERVER_TYPE_SERVER			= 0x1
	, EB_SERVER_TYPE_PUSH			= 0x2	// ���ͷ���
}EB_APP_TYPE;

/*==========================================================
����״̬
===========================================================*/
typedef enum EB_SERVER_STATE
{
	EB_SS_INIT					// ��ʼ��
	, EB_SS_RUNNING				// ������...
	, EB_SS_DISCONNECT			// ���ߣ���Ҫ��������
	, EB_SS_STOPED				// �Ѿ�ֹͣ
	, EB_SS_TIMEOUT				// ��ʱ
	, EB_SS_MOVED		// 
	, EB_SS_RESTART
	, EB_SS_EXIT
}EB_SERVER_STATE;

typedef enum EB_SYS_EXT_KEY
{
	EB_SYS_EXT_KEY_UNKNOWN
	, EB_SYS_EXT_KEY_CLEAR_UNAUTH_ACCOUNT		// 1 �೤ʱ�����δע���û�����λ��Сʱ��
	, EB_SYS_EXT_KEY_OAUTH_URL							// 2 
	, EB_SYS_EXT_KEY_SEND_MAIL_APPID				// 3
	, EB_SYS_EXT_KEY_OPEN_REGISTER					// 4 �Ƿ񿪷�ע�� 0=�����ţ�1=�����û�ע�᣻2=������ҵע��
	, EB_SYS_EXT_KEY_OPEN_VISITOR						// 5 �Ƿ񿪷��ο͹��� 0/1
	, EB_SYS_EXT_KEY_ACCOUNT_PREFIX					// 6
	, EB_SYS_EXT_KEY_SUPPORT_VERSION				// 7 ��С֧�ְ汾��
	, EB_SYS_EXT_KEY_DATABASE_TYPE					// 8 ���ݿ����� 0=PostgreSQL; 1=MySQL
	, EB_SYS_EXT_KEY_SEND_CALL_APPID				// 9
	, EB_SYS_EXT_KEY_DEFAULT_PWD						// 10 Ĭ������
	, EB_SYS_EXT_KEY_MY_GROUP0				// Ĭ�ϲ�������
	, EB_SYS_EXT_KEY_MY_GROUP2				// Ĭ��Ⱥ������
	, EB_SYS_EXT_KEY_MY_GROUP9				// Ĭ������������
	, EB_SYS_EXT_KEY_FUNC_REQ_URL			// "/rest.v01.ebwebum.freq"
	, EB_SYS_EXT_KEY_AUTH_MSG_URL			// "/"
	, EB_SYS_EXT_KEY_USER_PWD_CALLBACK_URL	// ���ȱ������1�������Զ���Ϊ�գ�
	, EB_SYS_EXT_KEY_CALLBACK_APPID			// �ص�APPID
	, EB_SYS_EXT_KEY_MAX_APP_TEST_ACCOUNT	// 
	, EB_SYS_EXT_KEY_CALLBACK_ENC_MODE		// �ص�����ģʽ��3des,aes_ecb,aes_cbc
	, EB_SYS_EXT_KEY_FORGET_PWD_URL					// 20 ��������URL
	, EB_SYS_EXT_KEY_ENT_LOGO_URL						// 21 ��ҵLOGO URL
	, EB_SYS_EXT_KEY_DEPLOY_TYPE			// �������� 0����ҵ˽���ƣ�1������������
	, EB_SYS_EXT_KEY_DEPLOY_ID				// ����ID��������ID��
	, EB_SYS_EXT_KEY_DEPLOY_KEY				// ����KEY����md5('eb_deploy_id'+[deploy_id])
	, EB_SYS_EXT_KEY_PRODUCT_NAME			// IM��Ʒ���ơ�������������ֻ����Ȩ�û��ſ����޸ģ�
	, EB_SYS_EXT_KEY_PASSWD_AUTH_MODE		// ������֤��ʽ 0=Ĭ�϶���; 1=md5(password)��������
	, EB_SYS_EXT_KEY_ENT_MANAGER_URL		// ��ҵ�����̨URL
	, EB_SYS_EXT_KEY_SAVE_CONVERSATIONS		// ���������¼
	, xEB_SYS_EXT_KEY_INVITE_ADD2GROUP_AUTH	// �����û���Ⱥ��֤ 0/1 default=0
	, xEB_SYS_EXT_KEY_REQ_ADD2GROUP_AUTH			// 30 �����Ⱥ��֤		0/1 default=1
	, EB_SYS_EXT_KEY_MEMBER_CHANGE_EVENT			// 31 Ⱥ��Ա�����޸ģ�֪ͨ��ҵ�¼�		0/1 default=1
	, EB_SYS_EXT_KEY_CONVERSATIONS_URL		// ���������¼URL
	, EB_SYS_EXT_KEY_GROUP_MSG_SUBID		// Ⱥ����ϢӦ�ö���ID
	, EB_SYS_EXT_KEY_OFFFILE_SPACE_SIZE		// �����ļ��ռ��С��Ĭ��50MB����0��֧�����߿ռ�
	, EB_SYS_EXT_KEY_ONLINE_MSG_SAVE_DAY	// ��Ȩ�û�������Ϣ����������Ĭ��30�죩
	, EB_SYS_EXT_KEY_OFFLINE_MSG_SAVE_DAY	// ��Ȩ�û�������Ϣ����������Ĭ��90�죩
	, EB_SYS_EXT_KEY_USER_CD_SPACE_SIZE		// ��Ȩ�û����̿ռ��С��Ĭ��50MB����0��֧�ָ����û�����
	, EB_SYS_EXT_KEY_USERGROUP_CD_SPACE_SIZE	// ��Ȩ����Ⱥ�����̿ռ��С��Ĭ��50MB����0��֧��
	, EB_SYS_EXT_KEY_ENTGROUP_CD_SPACE_SIZE		// ��Ȩ��˾�������̿ռ��С��Ĭ��50MB����0��֧��
	, EB_SYS_EXT_KEY_PUSH_TIME								// 40 ������Ϣʱ������Ĭ��180S,3����
	, EB_SYS_EXT_KEY_TEXT_RESOURCE						// 41 �ı���Դ������,ͼƬ,����,�ļ�,�����ļ�,��Ƭ,������Ƭ,
	, EB_SYS_EXT_KEY_DEFAULT_ALLOW_OUT_CHAT		// ���û�Ĭ���Ƿ������ⲿ��������0/1��Ĭ��1���ܣ�0�ܾ��ⲿ��������
	, EB_SYS_EXT_KEY_DEFAULT_ACCEPT_OUT_CHAT	// ���û�Ĭ���Ƿ��Զ������ⲿ��������0/1��Ĭ��1���ܣ�0��Ҫ�ֹ�ȷ�Ͻ���
	, EB_SYS_EXT_KEY_MAX_RETRY_COUNT			// ������Դ��������Ĭ��5��0������
	, EB_SYS_EXT_KEY_TEMP_LOCK_MINUTE			// ��ʱ�����û�ʱ�䣬��λ���ӣ�Ĭ��30���ӣ�0������
	, EB_SYS_EXT_KEY_DELETE_ENT_MEMBER_OP		// ɾ����ҵԱ��������Ĭ��0�������ʺţ�1����ʱ�����ʺţ����ܵ�¼��2��ɾ���ʺż���������
	, xEB_SYS_EXT_KEY_AUTH_CONTACT				// �Ƿ���֤��ϵ�ˣ�Ĭ��0������֤��1����Ҫ��֤��ͬʱ�ⲿ��ϵ�ˣ��������죩
	, EB_SYS_EXT_KEY_FIND_APP_SUBID				// ��Ⱥ���˶���ID
	, EB_SYS_EXT_KEY_MAX_UG_COUNT				// ������������Ĭ��15
	, EB_SYS_EXT_KEY_MAX_CONTACT_COUNT				// 50 �����ϵ�ˣ�Ĭ��500
	, EB_SYS_EXT_KEY_USES_UID_LIST						// 51 ʹ��UID���ݳ�
	, EB_SYS_EXT_KEY_EMPTY_UID_LIST_AUTO		// UID���ݳ�Ϊ�գ��Ƿ��Զ�����
	, EB_SYS_EXT_KEY_REGISTER_URL				// ע��URL
	, EB_SYS_EXT_KEY_AUTO_OPEN_SUBID			// ��¼�Զ��򿪶���APP
	, xEB_SYS_EXT_KEY_AUTOHIDE_MAIN_FRAME_PC	// ��¼�Զ�����������
	, xEB_SYS_EXT_KEY_HIDE_MAIN_FRAME_PC			// ���������棨ʹ�ô�����APP���棩
	, EB_SYS_EXT_KEY_ENCRYPTION_SALT			// ���ܸ��Ӵ���������md5(salt)
	, EB_SYS_EXT_KEY_PBKDF2_COUNT				// HASH���������Ĭ��1
	, EB_SYS_EXT_KEY_PBKDF2_LENGTH				// ��Ҫ����λ�����룻Ĭ��32����64���ֽ�����
	, EB_SYS_EXT_KEY_OPEN_ENT_MGR							// 60 �Ƿ񿪷���ͨ��ҵ������ 0/1
	, EB_SYS_EXT_KEY_OFFLINE_FILE_SAVE_DAY		// 61 ��Ȩ�û������ļ�����������Ĭ��90�죩
	//, EB_SYS_EXT_KEY_OPEN_UID_REGISTER			// �Ƿ񿪷�UIDע�� 0=�����ţ�1=����ע�� Ĭ��0������
	, xEB_SYS_EXT_KEY_DISABLE_USER_CLOUD_DRIVE	// �Ƿ���ø������̹��� 0/1 Ĭ��0
	, xEB_SYS_EXT_KEY_DISABLE_GROUP_SHARED_CLOUD	// �Ƿ����Ⱥ�飨���ţ������� 0/1 Ĭ��0
	, xEB_SYS_EXT_KEY_DISABLE_MODIFY_PASSWD		// �Ƿ�����޸����빦�� 0/1 Ĭ��0
	, EB_SYS_EXT_KEY_CALLBACK_PARAM				// �ص�����
	, EB_SYS_EXT_KEY_ACCOUNT_AUTH_URL			// �ʺ���֤�ӿ�
	, EB_SYS_EXT_KEY_ACCOUNT_ACTIVE_URL			// �ʺż���ӿ�
	, EB_SYS_EXT_KEY_SYSTEM_VALUE				// xxx
	, EB_SYS_EXT_KEY_AUTO_ADD_GROUPID			// ��ע���û����Զ���ӵ�Ⱥ�飨���ţ�
	//, EB_SYS_EXT_KEY_DISABLE_VIDEO				// �Ƿ������Ƶ���� 0/1 Ĭ��0
	//, EB_SYS_EXT_KEY_DISABLE_REMOTE_DESKTOP		// �Ƿ������Ƶ���� 0/1 Ĭ��0
	, EB_SYS_EXT_KEY_CLUSTER_TYPE						// 70 ��Ⱥ���ͣ�Ĭ��1���Զ��û���̬���� 0������̬����
	, EB_SYS_EXT_KEY_EMAIL_SUBID						// 71 �ʼ�Ӧ��ID
	, EB_SYS_EXT_KEY_POP3_SERVER_LIST				// �������������ӦPOP3,SMTP��ַ����ʽ��tom.com,pop.tom.com,110,smtp.tom.com,25;xxx ~~pop3.server����ʽ���ӣ�vip.sina.com δ���ã�����pop.xxx.com
	, EB_SYS_EXT_KEY_AUTO_TRANSFORM_ACCOUNT		// �Զ�ת���ʺ�Сд�����Ƿ������ʺŴ�Сд�� Ĭ��1��ת���������ִ�С�֣���0����ת�������ִ�Сд��
	, EB_SYS_EXT_KEY_REQUEST_RECEIVE_MIN_TIME		// ��С�����ʼ�ʱ������Ĭ��2����
	, EB_SYS_EXT_KEY_REQUEST_RECEIVE_MAX_TIME		// �������ʼ�ʱ������Ĭ��5����
	, EB_SYS_EXT_KEY_VIEW_OFFICE_URL				// https://view.officeapps.live.com/op/view.aspx?src=
	, EB_SYS_EXT_KEY_VIEW_OFFICE_EXT				// .doc.docx.docm.dotx.dotm.xls.xlsx.xlsm.xltx.xltm.xlsb.xlam.ppt.pptx.pptm.potx.potm.ppam.ppsx.ppsm.sldx.sldm.thmx.pdf
	, EB_SYS_EXT_KEY_VIEW_IMAGE_EXT					// .png.jpg.jpeg.bmp.ico
	, EB_SYS_EXT_KEY_MAX_OFF_FILE_SIZE				// default 20mb
	, EB_SYS_EXT_KEY_MAX_RES_FILE_SIZE					// 80 default 20mb
	//, EB_SYS_EXT_KEY_DISABLE_ENTBOOST_TW			// ����Эͬ�칫����
	//, EB_SYS_EXT_KEY_MAIL_SERVER_LIST					// ���������ʼ���Ӧ��ַ��pop3.server����ʽ���ӣ�vip.sina.com δ���ã�����pop.xxx.com
	, EB_SYS_EXT_KEY_MAX_SYSTEM_TEMP_VALUE			// 81 ��������һЩ��ʱ����
	, EB_SYS_EXT_KEY_MAX_RECEIVE_OFFMSG_COUNT		// 82 ���һ�ν���������Ϣ���� default:200
	, EB_SYS_EXT_KEY_PUSH_CONTENT_TYPE					// 83 ������Ϣ���� 0:�������� 1:ֻ��ʾ����Ϣ
	, EB_SYS_EXT_KEY_MAX_OAUTH_TIME_DAYS				// 84 �ͻ����豸�Զ���¼����֤KEY����������Ĭ��90�죻
	, EB_SYS_EXT_KEY_ECARD_INFO_FLAG						// 85 Ĭ�ϵ�����Ƭ���Ͽ������ã�0:Ĭ�� 1:��ֹ������ϵ�绰���ֻ�����
	, EB_SYS_EXT_KEY_MAX_BCMSG_SAVE_DAYS				// 86 �㲥��Ϣ������������Ĭ��30�죬�����Զ�ɾ��
	, EB_SYS_EXT_KEY_EB_SERVER_VERSION					// 87 ����˰汾�ţ��� 544=1.25.0.544 
	, EB_SYS_EXT_KEY_DEFAULT_URL								// 88 Ĭ��URL��ַ��Ĭ�� http://www.entboost.com
	, EB_SYS_EXT_KEY_ATTEND_START_DATE	= 2000	// 2000 ���ڿ�ʼʱ�ڣ���ʽ:YYYY-mm-dd Ĭ�Ͽ�δ��ʼ
	, EB_SYS_EXT_KEY_ATTEND_DAILY_JOB_DATE			// 2001 ����ÿ����ҵʱ�ڣ���ʽ:YYYY-mm-dd Ĭ�Ͽ�δ��ʼ

}EB_SYS_EXT_KEY;

typedef enum EB_APP_EXT_KEY
{
	EB_APP_EXT_KEY_UNKNOWN
	, EB_APP_EXT_KEY_CAPACITY_REG_USER	// ֧��ע������û�����-1=���ƣ�0=�����ƣ�>0=ÿ������λע��һǧ�û�
	, EB_APP_EXT_KEY_CURRENT_REG_USER	// ��ǰע���û���
	, EB_APP_EXT_KEY_CAPACITY_REG_ENT	// ֧��ע����ҵ����-1=���ƣ�0=�����ƣ�>0=ÿ������λע��һ����ҵ
	, EB_APP_EXT_KEY_CURRENT_REG_ENT	// ��ǰע����ҵ��

}EB_APP_EXT_KEY;

#define MAX_USER_EXT_STRING_LEN 1024
typedef enum EB_USER_EXT_KEY
{
	EB_USER_EXT_KEY_UNKNOWN
	, EB_USER_EXT_KEY_LICENSE						// �Ƿ�����Ȩ��Ϣ
	, EB_USER_EXT_KEY_VIDEO_CONFERENCE_COUNT		// ��Ȩ��Ƶ������
	, EB_USER_EXT_KEY_REG_EXT						// �û�ע����չ��Ϣ
	, EB_USER_EXT_KEY_AUTO_ACK_UID					// �û��Զ�Ӧ��UID
	, EB_USER_EXT_KEY_GROUP_INFO_VERSION			// ����Ⱥ�飨�����飩���ϰ汾��
	, EB_USER_EXT_KEY_OLD_AUTH_MODE					// ����ɵ���֤��ʽ��
	, EB_USER_EXT_KEY_OLD_ACCOUNT_PREFIX			// ����ɵ��ʺ�ǰ׺
	, EB_USER_EXT_KEY_DEVICE_TOKEN_IOS			// SSL ID & device token for ios
	, EB_USER_EXT_KEY_PUSH_TIME						// �����Ϣ����ʱ�� for ios
	, EB_USER_EXT_KEY_CONTACT_INFO_VERSION			// ��ϵ�����ϰ汾��
	, EB_USER_EXT_KEY_ACCESS_TOKEN					// 
	//, EB_USER_EXT_KEY_CSP_LOGIN						// ����CSP��¼KEY
	, EB_USER_EXT_KEY_DEVICE_TOKEN_ANDROID		// device token for android
	, EB_USER_EXT_KEY_USER_HEAD_VERSION				// �û�ͷ��汾��
	, EB_USER_EXT_KEY_LOGON_TYPE_IP_BEGIN	= 101	// �����û���ͬ��¼���� IP1
	, EB_USER_EXT_KEY_LOGON_TYPE_IP_END		= 120	// �����û���ͬ��¼���� IP2
	, EB_USER_EXT_KEY_LOGON_TYPE_KEY_BEGIN	= 121	// �����û���ͬ��¼���� LOGONKEY1
	, EB_USER_EXT_KEY_LOGON_TYPE_KEY_END	= 140	// �����û���ͬ��¼���� LOGONKEY2
	, EB_USER_EXT_KEY_LOGON_TYPE_SOTP_BEGIN	= 141	// �����û���ͬ��¼���� SOTP ID
	, EB_USER_EXT_KEY_LOGON_TYPE_SOTP_END	= 160	// �����û���ͬ��¼���� SOTP ID

}EB_USER_EXT_KEY;

typedef enum EB_ENT_EXT_KEY
{
	EB_ENT_EXT_KEY_UNKNOWN
	, EB_ENT_EXT_KEY_LICENSE							// �Ƿ�����Ȩ��Ϣ
	, EB_ENT_EXT_KEY_VIDEO_CONFERENCE_COUNT				// ��Ȩ��Ƶ������
	, EB_ENT_EXT_KEY_USER_PWD_CALLBACK_URL				// �û�����ص�URL
	, EB_ENT_EXT_KEY_DEPARTMENT_INFO_VERSION			// ��ҵ�������ϰ汾��
	, EB_ENT_EXT_KEY_SETTING_VALUE						// ������Ϣ
	, xEB_ENT_EXT_KEY_ENABLE_MODIFY_MEMBER_INFO = 0x10	// ����Ա���޸��Լ����� 0/1 default 0
}EB_ENT_EXT_KEY;
//typedef enum EB_ENT_EXT_KEY_SETTING_VALUE
//{
//	EB_ENT_EXT_KEY_SETTING_VALUE_ENABLE_MODIFY_MEMBER_INFO		= 0x1	// ����Ա���޸��Լ����� 0/1 default 0
//	, EB_ENT_EXT_KEY_SETTING_VALUE_DISABLE_MODIFY_ACCOUNT_INFO	= 0x2	// ����Ա���޸ĸ������� 0/1 default 1
//};

typedef enum EB_DEP_EXT_KEY
{
	EB_DEP_EXT_KEY_UNKNOWN
	, EB_DEP_EXT_KEY_ORG_GROUP_ID						// ԭʼȺ�飨���ţ�ID������������
	, EB_DEP_EXT_KEY_DISPLAY_INDEX					// Ⱥ�飨���ţ�����ʾ���򣬵������棬��������

}EB_DEP_EXT_KEY;

typedef enum EB_EMP_EXT_KEY
{
	EB_EMP_EXT_KEY_UNKNOWN
	, EB_EMP_EXT_KEY_MEMBER_FORBID_SPEECH		// Ⱥ�飨���ţ�����Ա�������� 0���ý��ԣ�>0��ʾ���Է���

}EB_EMP_EXT_KEY;

typedef enum EB_MAIL_MSG_TYPE
{
	EB_MAIL_MSG_TYPE_REGISTER
	, EB_MAIL_MSG_TYPE_NEW_MEMBER
	, EB_MAIL_MSG_TYPE_RESET_PASSWD
	, EB_MAIL_MSG_TYPE_RESEND_REGCODE	= 5
	, EB_MAIL_MSG_TYPE_MAX_SYSTEM		= 100

}EB_MAIL_MSG_TYPE;


//const int	EB_MAX_FILESIZE_SAVE_DISK			= 50*1024*1025;	// 50M
const int	EB_MAX_TIME_OFFLINE						= 5*1000;		// 5-minute
const int	EB_MAX_APP_ONLINE_KEY_TIMEOUT	= 7*24*3600;		// 7-day //24-hour
const int	EB_MAX_HEART_BEAT_SECOND			= 25;			// 25-second��40SĳЩ�����������⣻����WIN8���������30��һЩ�������ǻᳬʱ��
const int	EB_MAX_RICH_FORMAT_SIZE				= 1024*8;		// *8KB
const int	EB_MAX_RICH_TOTAL_SIZE				= 1024*1024*10;	// 10MB
const int	EB_MAX_ALL_RICH_SIZE					= 1024*1024*100;// 100MB
const int	EB_MAX_MEMORY_SIZE						= 1024*1024*50;	// 50MB

#define TEMP_INT_VALUE_LICENSE_INFO	1	// ��Ȩ��Ϣ
//#define TEMP_INT_VALUE_LICENSE		1	// �Ƿ��Ѿ���Ȩ
//#define TEMP_INT_VALUE_USER_COUNT	2	// ��Ȩ�û�����
//#define TEMP_INT_VALUE_VCC_COUNT	3	// ��Ȩ��Ƶ��������

#define TEMP_INT_VALUE_USER_EB_SID			100
#define TEMP_INT_VALUE_USER_ONLINE_KEY	101

#endif // __eb_defines_h__
