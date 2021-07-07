// eb_define.h file here
#ifndef __eb_define_h__
#define __eb_define_h__
#ifdef WIN32
#include "Windows.h"
#endif // WIN32

namespace entboost {

#ifndef min
#define min(a, b)  (((a) < (b)) ? (a) : (b)) 
#endif // min
namespace eb
{
#ifdef WIN32
	typedef __int64				bigint;
#define eb_atoi64(a) _atoi64(a)
#define eb_sprintfi64(a,i64) sprintf(a,"%I64d",i64)
#else
	typedef long long			bigint;
#define eb_atoi64(a) atoll(a)
#define eb_sprintfi64(a,i64) sprintf(a,"%lld",i64)
#endif
} // cgc namespace


/*==========================================================
����Ⱥ����չ����
===========================================================*/
typedef enum EB_GROUP_EXT_DATA
{
	EB_GROUP_EXT_DATA_NULL
	, EB_GROUP_EXT_DATA_FORBID_SPEECH		= 0x1	// ����Ⱥ�飨���ţ�
}EB_GROUP_EXT_DATA;

/*==========================================================
��ҵ��չ����
===========================================================*/
typedef enum EB_ENT_EXT_DATA
{
	EB_ENT_EXT_DATA_NULL
	, EB_ENT_EXT_DATA_ENABLE_MODIFY_MEMBER_INFO		= 0x1	// ����Ա���޸��Լ���������
	, EB_ENT_EXT_DATA_DISABLE_MODIFY_ACCOUNT_INFO	= 0x2	// ����Ա���޸��Լ���������
}EB_ENT_EXT_DATA;

/*==========================================================
ϵͳ����
===========================================================*/
typedef enum EB_SYSTEM_PARAMETER
{
	EB_SYSTEM_PARAMETER_UNKNOWN
	, EB_SYSTEM_PARAMETER_ACCOUNT_PREFIX				// 1 char*
	, EB_SYSTEM_PARAMETER_OPEN_REGISTER					// 2 int
	, EB_SYSTEM_PARAMETER_OPEN_VISITOR					// 3 int
	, EB_SYSTEM_PARAMETER_LICENSE_USER					// 4 int 0/1
	, EB_SYSTEM_PARAMETER_FORGET_PWD_URL				// 5 char*
	, EB_SYSTEM_PARAMETER_ENT_LOGO_URL					// 6 char*
	, EB_SYSTEM_PARAMETER_SEND_REG_MAIL					// 7 int 0/1
	, EB_SYSTEM_PARAMETER_DEPLOY_ID							// 8 char*
	, EB_SYSTEM_PARAMETER_PRODUCT_NAME					// 9 char*
	, EB_SYSTEM_PARAMETER_ENT_MANAGER_URL				// 10 char*
	, EB_SYSTEM_PARAMETER_SAVE_CONVERSATIONS		// 11 int 0/1
	, EB_SYSTEM_PARAMETER_GROUP_MSG_SUBID				// 12 char*
	, EB_SYSTEM_PARAMETER_FIND_APP_SUBID				// 13 char*
	, EB_SYSTEM_PARAMETER_AUTH_CONTACT					// 14 int 0/1
	, EB_SYSTEM_PARAMETER_AUTH_INVITEADD2GROUP	// 15 int 0/1
	, EB_SYSTEM_PARAMETER_REGISTER_URL					// 16 char*
	, EB_SYSTEM_PARAMETER_AUTO_OPEN_SUBID				// 17 char*
	, EB_SYSTEM_PARAMETER_AUTOHIDE_MAINFRAME		// 18 int 0/1
	, EB_SYSTEM_PARAMETER_HIDE_MAINFRAME				// 19 int 0/1
	, EB_SYSTEM_PARAMETER_DISABLE_USER_CLOUD_DRIVE		// 20 int 0/1
	, EB_SYSTEM_PARAMETER_DISABLE_GROUP_SHARED_CLOUD	// 21 int 0/1
	, EB_SYSTEM_PARAMETER_DISABLE_MODIFY_PASSWD				// 22 int 0/1
	, EB_SYSTEM_PARAMETER_LOGON_HTTP_REQ_URL					// 23 char*
	, EB_SYSTEM_PARAMETER_DISABLE_VIDEO								// 24 int 0/1
	, EB_SYSTEM_PARAMETER_DISABLE_REMOTE_DESKTOP			// 25 int 0/1
	, EB_SYSTEM_PARAMETER_DISABLE_ACCOUNT_EDIT				// 26 int 0/1
	, EB_SYSTEM_PARAMETER_DEFAULT_BROWSER_TYPE				// 27 int 0=�ȸ�Chrome����� 1=΢��IE�����
	, EB_SYSTEM_PARAMETER_LOGON_USER_DATA							// 28 char* set only
	, EB_SYSTEM_PARAMETER_DISABLE_MSG_RECEIPT					// 29 int 0/1
	, EB_SYSTEM_PARAMETER_LICENSE_TYPE								// 30 int ������ͣ�0=δ��Ȩ��1=������Ȩ��2=ʱ����Ȩ
	, EB_SYSTEM_PARAMETER_STAT_SUB_GROUP_MEMBER				// 31 int �Ƿ�ͳ���Ӳ������� 0/1
	, EB_SYSTEM_PARAMETER_MY_COLLECTION_SUBID					// 32 char*
	, EB_SYSTEM_PARAMETER_EB_SERVER_VERSION						// 33 int ��ǰ����˰汾���� 544=1.25.0.544 544���ϰ汾��ʼ֧��
	, EB_SYSTEM_PARAMETER_DEFAULT_URL									// 34 char*
	, EB_SYSTEM_PARAMETER_SYSTEM_ACCOUNT_FLAG					// 35 int ϵͳ�ʺű�ʾ��1=ϵͳ����Ա��2=��ͨ��ҵ����Ա��0=��ͨ�û�
}EB_SYSTEM_PARAMETER;

/*==========================================================
FUNC BROWSER TYPE
===========================================================*/
typedef enum EB_FUNC_BROWSER_TYPE
{
	EB_FUNC_BROWSER_TYPE_DEFAULT
	, EB_FUNC_BROWSER_TYPE_CEF
	, EB_FUNC_BROWSER_TYPE_IE
}EB_FUNC_BROWSER_TYPE;

/*==========================================================
RICH SUB TYPE
===========================================================*/
typedef enum EB_RICH_SUB_TYPE
{
	EB_RICH_SUB_TYPE_JPG								// Ĭ�����ݣ���JPG��ͼ��
	, EB_RICH_SUB_TYPE_AUDIO			= 11	// ������Ϣ
	, EB_RICH_SUB_TYPE_MAP_POS		= 21	// ��ͼλ��
	, EB_RICH_SUB_TYPE_CARD_INFO				// ��Ƭ��Ϣ�����û���Ƭ
	, EB_RICH_SUB_TYPE_USER_DATA	= 200	// �û��Զ�������
}EB_RICH_SUB_TYPE;

/*==========================================================
RICH SUB TYPE
===========================================================*/
typedef enum EB_BROADCAST_SUB_TYPE
{
	EB_BROADCAST_SUB_TYPE_BC
	, EB_BROADCAST_SUB_TYPE_NEW_EMAIL
	, EB_BROADCAST_SUB_TYPE_UNREAD_EMAIL
	, EB_BROADCAST_SUB_TYPE_TW_MSG							// Эͬ�칫������Ϣ
	, EB_BROADCAST_SUB_TYPE_SUBID_UNREAD_MSG		// ����ID��δ����Ϣ��content��ʽ: [����ID],[δ����Ϣ����]������: "1002300105,3" ��ʾ 1002300105 �ö���ID����3��δ����Ϣ��
}EB_BROADCAST_SUB_TYPE;

/*==========================================================
Ӧ�ù�����ʾλ��
===========================================================*/
typedef enum EB_FUNC_LOCATION
{
	EB_FUNC_LOCATION_UNKNOWN						= 0x0
	, EB_FUNC_LOCATION_MAINFRAME_BTN1				= 0x0001		// �����水ť���ϣ�
	, EB_FUNC_LOCATION_MAINFRAME_BTN2				= 0x0002		// �����水ť���£�
	, EB_FUNC_LOCATION_PHONE_APPFRAME				= 0x0004		// �ֻ�Ӧ�ã�Ӧ����尴ť��
	, EB_FUNC_LOCATION_APPFRAME_BTN					= 0x0008		// Ӧ����尴ť
	, EB_FUNC_LOCATION_RIGHT_CLICK_MENU_MAINFRAME	= 0x0010		// �������Ҽ��˵�
	, EB_FUNC_LOCATION_RIGHT_CLICK_MENU_USER		= 0x0020		// �û��Ҽ��˵�
	, EB_FUNC_LOCATION_RIGHT_CLICK_MENU_GROUP		= 0x0040		// Ⱥ�飨���ţ��Ҽ��˵�
	, EB_FUNC_LOCATION_RIGHT_CLICK_MENU_ENTERPRISE	= 0x0080		// ��ҵ�Ҽ��˵�
	, EB_FUNC_LOCATION_GROUP_CHAT_BTN1				= 0x0100		// Ⱥ��Ự���水ť
	, EB_FUNC_LOCATION_GROUP_CHAT_BTN2				= 0x0200		// Ⱥ��Ự���水ť
	, EB_FUNC_LOCATION_USER_CHAT_BTN1				= 0x0400		// �û��Ự���水ť
	, EB_FUNC_LOCATION_USER_CHAT_BTN2				= 0x0800		// �û��Ự���水ť
	, EB_FUNC_LOCATION_CALL_CHAT = EB_FUNC_LOCATION_GROUP_CHAT_BTN1|EB_FUNC_LOCATION_GROUP_CHAT_BTN2|EB_FUNC_LOCATION_USER_CHAT_BTN1|EB_FUNC_LOCATION_USER_CHAT_BTN2
	, EB_FUNC_LOCATION_RIGHT_CLICK_MENU_USER_CHAT	= 0x1000		// ������������Ҽ��˵�
	, EB_FUNC_LOCATION_RIGHT_CLICK_MENU_GROUP_CHAT	= 0x2000		// Ⱥ����������Ҽ��˵�
	, EB_FUNC_LOCATION_RIGHT_CLICK_MENU_CHAT_RECORD	= 0x4000		// �����¼�Ҽ��˵�
	, EB_FUNC_LOCATION_ALL_RIGHT_CLICK_MENU_CHAT = EB_FUNC_LOCATION_RIGHT_CLICK_MENU_USER_CHAT|EB_FUNC_LOCATION_RIGHT_CLICK_MENU_GROUP_CHAT|EB_FUNC_LOCATION_RIGHT_CLICK_MENU_CHAT_RECORD
	, EB_FUNC_LOCATION_CHAT_COPY_TEXT_TOOLBAR				= 0x8000		// ���촰�ڸ����ı�������
	, EB_FUNC_LOCATION_DISABLE_PC										= 0x10000		// ����PC��
}EB_FUNC_LOCATION;

/*==========================================================
Ӧ�ù���ģʽ
===========================================================*/
typedef enum EB_FUNC_MODE
{
	EB_FUNC_MODE_BROWSER			// �����ģʽ
	, EB_FUNC_MODE_MAINFRAME		// ����壨Ĭ�ϣ�
	, EB_FUNC_MODE_MODAL			// �Ի���ģʽ��ģʽ��
	, EB_FUNC_MODE_PROGRAM			// ��Ӧ�ó���
	, EB_FUNC_MODE_SERVER			// ����ģʽ��HTTP POST��
	, EB_FUNC_MODE_WINDOW			// ����ģʽ����ģʽ��
}EB_FUNC_MODE;

/*==========================================================
Ӧ�ù��ܲ���
===========================================================*/
typedef enum EB_FUNC_PARAM
{
	EB_FUNC_PARAM_NONE				// û�в���
	, EB_FUNC_PARAM_EB_DEFAULT		// ����Ĭ�ϲ�����authid&fk&ums
	, EB_FUNC_PARAM_USER_INFO		// �û���Ϣ��uid&account
}EB_FUNC_PARAM;

/*==========================================================
�Ự���ӱ�ʶ
===========================================================*/
typedef enum EB_CONNECTED_FLAG
{
	EB_CONNECTED_NORMAL				= 0x000
	, EB_CONNECTED_OFFLINE_USER		= 0x001
	, EB_CONNECTED_OWNER_CALL		= 0x002
	, EB_CONNECTED_AUTO_ACK			= 0x004
	, EB_CONNECTED_MSG				= 0x008
}EB_CONNECTED_FLAG;

/*==========================================================
��Դ����
===========================================================*/
typedef enum EB_RESOURCE_TYPE
{
	EB_RESOURCE_UNKNOWN
	, EB_RESOURCE_NOTE				// �ı��ʼ�
	, EB_RESOURCE_MSG				// ��Ϣ��Դ rich&image need cm
	, EB_RESOURCE_HEAD				// ͷ����Դ	need cm
	, EB_RESOURCE_DIR				// Ŀ¼��Դ
	, EB_RESOURCE_FILE				// �ļ���Դ need cm
	, EB_RESOURCE_EMOTION			// ������Դ
	, EB_RESOURCE_FUNCICON			// Ӧ�ù���ͼ�� 
	, EB_RESOURCE_CONTENT			// ���ݣ����ʼ�content-id������
}EB_RESOURCE_TYPE;
/*==========================================================
��Դ��������
===========================================================*/
typedef enum EB_RESOURCE_SHARE_TYPE
{
	EB_RESOURCE_SHARE_UNKNOWN
	, EB_RESOURCE_SHARE_ALL		// ������Դ
	, EB_RESOURCE_SHARE_TEMP	// Ⱥ����ʱ�ļ�
	, EB_RESOURCE_SHARE_COMMENT	// �ƻ�����������۸���
}EB_RESOURCE_SHARE_TYPE;
/*==========================================================
�ļ���չ����
===========================================================*/
typedef enum EB_FILE_EXT_TYPE
{
	EB_FILE_EXT_TYPE_OTHER
	, EB_FILE_EXT_TYPE_PDF
	, EB_FILE_EXT_TYPE_IMAGE
	, EB_FILE_EXT_TYPE_OFFICE
}EB_FILE_EXT_TYPE;
/*==========================================================
��Դ��Դ����
===========================================================*/
typedef enum EB_RESOURCE_FROM_TYPE
{
	EB_RESOURCE_FROM_TYPE_UNKNOWN			= 0
	, EB_RESOURCE_FROM_TYPE_ENT
	, EB_RESOURCE_FROM_TYPE_GROUP
	, EB_RESOURCE_FROM_TYPE_USER
	, EB_RESOURCE_FROM_TYPE_OFFMSG
	, EB_RESOURCE_FROM_TYPE_FUNC			= 10
	, EB_RESOURCE_FROM_TYPE_PLAN			= 11
	, EB_RESOURCE_FROM_TYPE_TASK
	, EB_RESOURCE_FROM_TYPE_REPORT
	, EB_RESOURCE_FROM_TYPE_MCON_ID_ATT		= 20

}EB_RESOURCE_FROM_TYPE;


/*==========================================================
��Ƶ����
===========================================================*/
typedef enum EB_VIDEO_TYPE
{
	EB_VIDEO_UNKNOWN	= 0				// δ֪
	, EB_VIDEO_AUDIO	= 1				// ����
	, EB_VIDEO_BOTH		= 2				// ����&��Ƶ
}EB_VIDEO_TYPE;

/*==========================================================
Զ����������
===========================================================*/
typedef enum EB_REMOTE_DESKTOP_TYPE
{
	EB_RD_UNKNOWN			= 0				// δ֪
	, EB_RD_DESKTOP_SRC		= 1				// ���빲��������
	, EB_RD_DESKTOP_DEST	= 2				// ���빲��Է�����
}EB_REMOTE_DESKTOP_TYPE;

/*==========================================================
�Ա�
===========================================================*/
typedef enum EB_GENDER_TYPE
{
	EB_GENDER_UNKNOWN
	, EB_GENDER_MALE				// ����
	, EB_GENDER_FEMALE				// Ů��
}EB_GENDER_TYPE;

/*==========================================================
Ⱥ������
===========================================================*/
typedef enum EB_GROUP_TYPE
{
	EB_GROUP_TYPE_DEPARTMENT		// ��ҵ���� ���ɹ�˾��Ա�趨��������������û������˳���
	, EB_GROUP_TYPE_PROJECT			// ��Ŀ�� ��ͬ�ϣ�
	, EB_GROUP_TYPE_GROUP			// �̶�Ⱥ�� �������˿��Դ���������Ա��ʱ��ӳ�Ա�����˳���
	, EB_GROUP_TYPE_TEMP = 9		// ��ʱ������ ���������Ա��̬��������������ʱ��ӳ�Ա�����˳���
}EB_GROUP_TYPE;

/*==========================================================
����״̬
===========================================================*/
typedef enum EB_USER_LINE_STATE
{
	EB_LINE_STATE_FREEZE		= -1	// �ʺ���ʱ����
	, EB_LINE_STATE_UNKNOWN		= 0		// �ʺ�δ��֤
	, EB_LINE_STATE_ONLINE_OLD			// ����
	, EB_LINE_STATE_OFFLINE				// ����
	, EB_LINE_STATE_BUSY				// æ
	, EB_LINE_STATE_AWAY				// �뿪
	, EB_LINE_STATE_ONLINE_NEW			// ����
	, EB_USER_CHANGE_STATE		= 0x100
}EB_USER_LINE_STATE;

/*==========================================================
״̬��
===========================================================*/
typedef enum EB_STATE_CODE
{
	EB_STATE_OK							= 0
	, EB_STATE_ERROR					= 1
	, EB_STATE_NOT_AUTH_ERROR					// û��Ȩ��
	, EB_STATE_ACC_PWD_ERROR					// �ʺŻ��������
	, EB_STATE_NEED_RESEND						// ��Ҫ�ط�����
	, EB_STATE_TIMEOUT_ERROR					// ��ʱ����
	, EB_STATE_EXIST_OFFLINE_MSG				// ����������Ϣ
	, EB_STATE_USER_OFFLINE						// �û�����״��
	, EB_STATE_USER_BUSY						// �û���·æ
	, EB_STATE_USER_HANGUP						// �û��ҶϻỰ
	, EB_STATE_OAUTH_FORWARD					// OAUTHת��
	, EB_STATE_UNAUTH_ERROR						// δ��֤����
	, EB_STATE_ACCOUNT_FREEZE					// �ʺ��Ѿ�����
	, EB_STATE_NEED_DELETE_MSG				// 13 ��Ҫɾ����Ϣ
	, EB_STATE_WAITING_PROCESS				// 14 �ȴ�������Ϣ��
	, EB_STATE_PARAMETER_ERROR			= 15	// ��������
	, EB_STATE_DATABASE_ERROR					// ���ݿ��������
	, EB_STATE_NEW_VERSION						// �°汾
	, EB_STATE_FILE_ALREADY_EXIST				// �ļ��Ѿ�����
	, EB_STATE_FILE_BIG_LONG					// �ļ�������С
	, EB_STATE_ACCOUNT_NOT_EXIST		= 20	// �ʺŲ�����
	, EB_STATE_ACCOUNT_ALREADY_EXIST			// �ʺ��Ѿ�����
	, EB_STATE_ACCOUNT_DISABLE_OFFCALL			// ��ֹ���߻Ự
	, EB_STATE_ACCOUNT_DISABLE_EXTCALL			// ��ֹ�ⲿ�Ự
	, EB_STATE_DISABLE_REGISTER_USER	= 25	// ��ֹ�û�ע�Ṧ��
	, EB_STATE_DISABLE_REGISTER_ENT				// ��ֹ��ҵע�Ṧ��
	, EB_STATE_ENTERPRISE_ALREADY_EXIST	= 30	// ��˾�����Ѿ�����
	, EB_STATE_ENTERPRISE_NOT_EXIST				// û�й�˾��Ϣ����ҵ�����ڣ�
	, EB_STATE_DEP_NOT_EXIST					// ������Ⱥ�飨���ţ�
	, EB_STATE_EXIST_SUB_DEPARTMENT				// �����Ӳ���
	, EB_STATE_DEP_ACC_ERROR					// Ⱥ����Ա������
	, EB_STATE_ENT_ACC_ERROR					// ��ҵԱ����Ա������
	, EB_STATE_CS_MAX_ERROR						// �����ͷ���ϯ�������
	, EB_STATE_NOT_CS_ERROR						// û�пͷ���ϯ
	, EB_STATE_EXCESS_QUOTA_ERROR				// ��������������
	, EB_STATE_ENT_GROUP_ERROR					// ��ҵ����
	, EB_STATE_ONLINE_KEY_ERROR			= 40
	, EB_STATE_UM_KEY_ERROR
	, EB_STATE_CM_KEY_ERROR
	, EB_STATE_DEVID_KEY_ERROR
	, EB_STATE_APPID_KEY_ERROR
	, EB_STATE_DEVID_NOT_EXIST
	, EB_STATE_APPID_NOT_EXIST
	, EB_STATE_APP_ONLINE_KEY_TIMEOUT
	, EB_STATE_KEY_ERROR						// KEY����
	, EB_STATE_CALL_NOT_EXIST			= 50
	, EB_STATE_CHAT_NOT_EXIST
	, EB_STATE_MSG_NOT_EXIST
	, EB_STATE_RES_NOT_EXIST
	, EB_STATE_NOT_MEMBER_ERROR
	, EB_STATE_ATTACHMENT_NOT_EXIST
	, EB_STATE_FILE_NOT_EXIST
	, EB_STATE_NO_UM_SERVER				= 60
	, EB_STATE_NO_CM_SERVER
	, EB_STATE_NO_VM_SERVER
	, EB_STATE_NO_AP_SERVER
	, EB_STATE_NO_RD_SERVER
	, EB_STATE_ENT_BLACKLIST			= 70		// 70 ��ҵ�������û�
	, EB_STATE_ANOTHER_ENT_ACCOUNT				// 71 ������ҵ�ʺ�
	, EB_STATE_MAX_CAPACITY_ERROR					// 72 �����������
	, EB_STATE_NOT_SUPPORT_VERSION_ERROR	// 73 ��֧�ֵ�ǰ�汾
	, EB_STATE_FORWARD_MSG								// 74 ת����Ϣ
	, EB_STATE_MAX_RETRY_ERROR						// 75 �������̫�࣬����ʮ���Ӻ����ԣ�
	, EB_STATE_TOKEN_ERROR								// 76 TOKEN����
	, EB_STATE_MAX_UG_ERROR								// 77 ��������������
	, EB_STATE_MAX_CONTACT_ERROR					// 78 ���������ϵ������
	, EB_STATE_CONTACT_NOT_EXIST					// 79 ��ϵ�˲�����
	, EB_STATE_PHONE_ALREADY_EXIST				// 80 �ֻ��ʺ��Ѿ�����
	, EB_STATE_ALREADY_IN_REMOTE_DESKTOP	// 81 �Ѿ���Զ��������
	, EB_STATE_CONTENT_BIG_LENGTH					// 82 ���ݳ�������
	, EB_STATE_MEMORY_ERROR								// 83 �ڴ治��
	, EB_STATE_DATA_ERROR									// 84 ���ݻ��ʽ����
	, EB_STATE_CREATE_FILE_ERROR					// 85 �����ļ�ʧ��
	, EB_STATE_FORBIG_SPEECH							// 86 ��������
	, EB_STATE_GROUP_FORBIG_SPEECH				// 87 Ⱥ��������
	, EB_STATE_ID_NOT_EXIST								// 88 ID���Ų�����

	, EB_STATE_PLAN_NOT_EXIST			= 100		// 100 �ƻ�������
	, EB_STATE_TASK_NOT_EXIST							// 101 ���񲻴���
	, EB_STATE_REPORT_NOT_EXIST						// 102 ���治����

}EB_STATE_CODE;

/*==========================================================
�û�����
===========================================================*/
typedef enum EB_ACCOUNT_TYPE
{
	EB_ACCOUNT_TYPE_VISITOR		// �ο�
	, EB_ACCOUNT_TYPE_IN_ENT	// ͬ��ҵ��ͬȺ��
	, EB_ACCOUNT_TYPE_OUT_ENT	// �ⲿ��Ա
	, EB_ACCOUNT_TYPE_USER		// ��ͨ�û�
}EB_ACCOUNT_TYPE;

/*==========================================================
��������
===========================================================*/
typedef enum EB_SETTING_VALUE
{
	EB_SETTING_ENABLE_OUTENT_CALL		= 0x0001
	, EB_SETTING_AUTO_OUTENT_ACCEPT		= 0x0002
	, EB_SETTING_ENABLE_USER_CALL		= 0x0004
	, EB_SETTING_AUTO_USER_ACCEPT		= 0x0008
	, EB_SETTING_ENABLE_VISITOR_CALL	= 0x0010
	, EB_SETTING_AUTO_VISITOR_ACCEPT	= 0x0020
	, EB_SETTING_ENABLE_OFF_CALL		= 0x0040
	, EB_SETTING_ENABLE_OFF_FILE		= 0x0080
	//, EB_SETTING_CONNECTED_OPEN_CHAT	= 0x0100
	, EB_SETTING_AUTO_CONTACT_ACCEPT	= 0x0200
}EB_SETTING_VALUE;
//(EB_SETTING_ENABLE_OUTENT_CALL|EB_SETTING_AUTO_OUTENT_ACCEPT|EB_SETTING_ENABLE_USER_CALL|EB_SETTING_AUTO_USER_ACCEPT|EB_SETTING_ENABLE_VISITOR_CALL|EB_SETTING_AUTO_VISITOR_ACCEPT|EB_SETTING_ENABLE_OFF_CALL)
#define EB_SETTING_DEFAULT				0x027F // EB_SETTING_ENABLE_OUTENT_CALL-EB_SETTING_ENABLE_OFF_CALL
#define EB_SETTING_DEFAULT_BASE			EB_SETTING_AUTO_CONTACT_ACCEPT
#define EB_SETTING_DEFAULT_OUT_CALL		EB_SETTING_ENABLE_OUTENT_CALL|EB_SETTING_ENABLE_USER_CALL|EB_SETTING_ENABLE_VISITOR_CALL|EB_SETTING_ENABLE_OFF_CALL
#define EB_SETTING_DEFAULT_OUT_ACCEPT	EB_SETTING_AUTO_OUTENT_ACCEPT|EB_SETTING_AUTO_USER_ACCEPT|EB_SETTING_AUTO_VISITOR_ACCEPT

} // namespace entboost

#endif // __eb_define_h__
