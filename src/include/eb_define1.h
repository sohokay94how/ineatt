// eb_define1.h file here
#ifndef __eb_define1_h__
#define __eb_define1_h__
#include "eb_define.h"

/*==========================================================
��Ϣ֪ͨ����
===========================================================*/
typedef enum EB_NOTIFY_TYPE
{
	EB_NOTIFY_UNKNOWN
	, EB_NOTIFY_USER_INPUT						// �û���������
	, EB_NOTIFY_UPLOAD_GROUP_FILE			// �û��ϴ�Ⱥ�ļ� notify-data<=1024 size
}EB_NOTIFY_TYPE;

/*==========================================================
��Ϣ����
===========================================================*/
typedef enum EB_MSG_TYPE
{
	EB_MSG_UNKNOWN
	, EB_MSG_RICH		// text&image
	, EB_MSG_FILE

	, EB_MSG_DELETE_GROUP			= 0x101		// ��ɢȺ
	, EB_MSG_EXIT_GROUP							// �����˳�Ⱥ
	, EB_MSG_UPDATE_GROUP						// Ⱥ�����Ѿ��޸ģ���Ҫ���¼���Ⱥ����
	, EB_MSG_REMOVE_GROUP						// ��������Ա�Ƴ�Ⱥ
	, EB_MSG_CALL_2_GROUP						// һ��һ�Ựת������������
	, EB_MSG_ADD_2_GROUP						// ��ӽ�Ⱥ��(����)
	, EB_MSG_REQ_ADD_2_GROUP					// �������Ⱥ��(����)
	, EB_MSG_REJECT_ADD_2_GROUP					// �ܾ�����Ⱥ��(����)
	, EB_MSG_INVITE_ADD_2_GROUP					// ������ӽ�Ⱥ��(����)
	, EB_MSG_USER_LINE_STATE		= 0x111		// �û�����״̬֪ͨ
	, EB_MSG_ONLINE_ANOTHER						// ֪ͨ�Լ����Ѿ��������ط���¼���˳�ǰһ������
	, EB_MSG_USER_ONLINE_INCALL					// �û����ߣ������û������лỰ
	, EB_MSG_RESET_ACCOUNT						// �����ʺţ�����
	, EB_MSG_USER_HEAD_CHANGE		= 0x121		// �û��޸�ͷ����Դ
	, EB_MSG_BROADCAST_MESSAGE					// �㲥��Ϣ
	, EB_MSG_GROUP_MEMBER_CHANGE				// Ⱥ��Ա�����Ѿ��޸ģ���Ҫ���¼���Ⱥ��Ա����
	, EB_MSG_ENT_GROUP_INFO_VERSION				// ��ҵ�������ϰ汾
	, EB_MSG_GROUP_MEMBER_VERSION				// ���ų�Ա���ϰ汾
	, EB_MSG_USER_INFO_CHANGE						// �û����������޸�
	, EB_MSG_DELETE_RESOURCE		= 0x131		// ɾ��������Դ
	, EB_MSG_EMOTION_INFO						// ������Դ��Ϣ
	, EB_MSG_SUBSCRIBE_FUNC_INFO				// ����������Ϣ
	, EB_MSG_ENTGROUP_VER_INFO					// ��ҵ���Ű汾��Ϣ
	, EB_MSG_MYGROUP_VER_INFO					// ����Ⱥ��汾��Ϣ
	, EB_MSG_GROUP_MEMBER_LINESTATE				// Ⱥ�飨���ţ���Ա������ϵ�ˣ�����״̬
	, EB_MSG_AREA_DICT_INFO						// �����ֵ���Ϣ
	, EB_MSG_GROUP_LINESTATE_COUNT				// Ⱥ�飨���ţ���Ա��������
	, EB_MSG_EMOTION_COUNT							// ������Դ����
	, EB_MSG_CONTACT_HEAD_VER_INFO			// ����/��ϵ��ͷ��汾��Ϣ
	, EB_MSG_REQ_ADD_CONTACT		= 0x141		// �������
	, EB_MSG_ACCEPT_ADD_CONTACT					// ���ܼӺ���
	, EB_MSG_REJECT_ADD_CONTACT					// �ܾ��Ӻ���
	, EB_MSG_DELETE_CONTACT							// ɾ������
	, EB_MSG_UPDATE_CONTACT							// �������ϸ���
	, EB_MSG_UPDATE_USER_GROUP					// ���º��ѷ���
	, EB_MSG_DELETE_USER_GROUP					// ɾ�����ѷ���
	, EB_MSG_UPDATE_USER_GROUP2					// ���º��ѷ���
	, EB_MSG_DELETE_USER_GROUP2					// ɾ�����ѷ���
}EB_MSG_TYPE;

/*==========================================================
Ⱥ�飨���ţ���Ա����Ȩ��
===========================================================*/
typedef enum EB_MANAGER_LEVEL
{
	EB_LEVEL_NONE
	, EB_LEVEL_DEP_EDIT			= 0x0001
	, EB_LEVEL_DEP_DELETE		= 0x0002
	, EB_LEVEL_EMP_EDIT			= 0x0004
	, EB_LEVEL_EMP_DELETE		= 0x0008
	, EB_LEVEL_DEP_RES_EDIT		= 0x0010
	, EB_LEVEL_DEP_RES_DELETE	= 0x0020
	, EB_LEVEL_DEP_ADMIN			= EB_LEVEL_DEP_EDIT|EB_LEVEL_EMP_EDIT|EB_LEVEL_EMP_DELETE|EB_LEVEL_DEP_RES_EDIT|EB_LEVEL_DEP_RES_DELETE
	, EB_LEVEL_FORBID_SPEECH	= 0x1000

	//, EB_LEVEL_MGR				= 0x0001
	//, EB_LEVEL_EDIT				= 0x0002
	//, EB_LEVEL_DELETE			= 0x0004
	////, EB_LEVEL_ENT_MGR			= 0x0010
	//, EB_LEVEL_DEP_MGR			= 0x0020
	//, EB_LEVEL_EMP_MGR			= 0x0040
	//, EB_LEVEL_RES_MGR			= 0x0100
	////, EB_LEVEL_ENT_EDIT			= EB_LEVEL_ENT_MGR|EB_LEVEL_EDIT
	//, EB_LEVEL_DEP_EDIT			= EB_LEVEL_DEP_MGR|EB_LEVEL_EDIT
	//, EB_LEVEL_DEP_DELETE		= EB_LEVEL_DEP_MGR|EB_LEVEL_DELETE
	//, EB_LEVEL_EMP_EDIT			= EB_LEVEL_EMP_MGR|EB_LEVEL_EDIT
	//, EB_LEVEL_EMP_DELETE		= EB_LEVEL_EMP_MGR|EB_LEVEL_DELETE
	////, EB_LEVEL_RES_EDIT		= EB_LEVEL_RES_MGR|EB_LEVEL_EDIT	// ������Դ������ͨ������ʵ�֣���������ҵ��Ⱥ���г�ͻ��
	////, EB_LEVEL_ENT_RES_EDIT		= EB_LEVEL_ENT_MGR|EB_LEVEL_RES_MGR|EB_LEVEL_EDIT
	////, EB_LEVEL_ENT_RES_DELETE	= EB_LEVEL_ENT_MGR|EB_LEVEL_RES_MGR|EB_LEVEL_DELETE
	////, EB_LEVEL_ENT_RES_VIEW		= EB_LEVEL_ENT_MGR|EB_LEVEL_RES_MGR
	//, EB_LEVEL_DEP_RES_EDIT		= EB_LEVEL_DEP_MGR|EB_LEVEL_RES_MGR|EB_LEVEL_EDIT
	//, EB_LEVEL_DEP_RES_DELETE	= EB_LEVEL_DEP_MGR|EB_LEVEL_RES_MGR|EB_LEVEL_DELETE
	////, EB_LEVEL_RES_VIEW		= EB_LEVEL_RES_MGR|EB_LEVEL_MGR
}EB_MANAGER_LEVEL;

/*==========================================================
��¼����
===========================================================*/
typedef enum EB_LOGON_TYPE
{
	EB_LOGON_TYPE_UNKNOWN			= 0
	, EB_LOGON_TYPE_EMAIL			= 0x0000001
	, EB_LOGON_TYPE_PHONE			= 0x0000002
	, EB_LOGON_TYPE_VISITOR			= 0x0000004
	, EB_LOGON_TYPE_UID				= 0x0000008
	, EB_LOGON_TYPE_MAIL_TEST		= 0x0000010
	, EB_LOGON_TYPE_PC				= 0x0000100	// EB_LOGON_TYPE_PC-EB_LOGON_TYPE_APPIDΪ���ն˵�¼
	, EB_LOGON_TYPE_IOS				= 0x0000200
	, EB_LOGON_TYPE_ANDROID			= 0x0000400
	, EB_LOGON_TYPE_WP				= 0x0000800
	, EB_LOGON_TYPE_WEB				= 0x0001000
	, EB_LOGON_TYPE_SERVER			= 0x0010000	// ����˵�¼��������IMҵ��
	, EB_LOGON_TYPE_PUSHAPP			= 0x0020000	// ��Ϣ����Ӧ��
	, EB_LOGON_TYPE_APPID			= 0x0100000	// APPID��֤��������IMҵ��
	, EB_LOGON_TYPE_OAUTH			= 0x0200000	// ������֤
}EB_LOGON_TYPE;
const int EB_SID_LOGON_TYPE	= EB_LOGON_TYPE_PC|EB_LOGON_TYPE_IOS|EB_LOGON_TYPE_ANDROID|EB_LOGON_TYPE_WP|EB_LOGON_TYPE_WEB|EB_LOGON_TYPE_SERVER|EB_LOGON_TYPE_APPID;

///*==========================================================
//ANDROID����ƽ̨
//===========================================================*/
//typedef enum EB_ANDROID_PUSH_TYPE
//{
//	EB_ANDROID_PUSH_TYPE_UNKNOWN			= 0	// δ֪����
//	, EB_ANDROID_PUSH_TYPE_IOS						// IOS����ƽ̨
//	, EB_ANDROID_PUSH_TYPE_HUAWEI					// ��Ϊ����ƽ̨
//	, EB_ANDROID_PUSH_TYPE_XIAOMI					// С������ƽ̨
//
//};

#define EB_PUSH_SSLID_HUAWEI_MIN 100	// ��Ϊ���� 100-199
#define EB_PUSH_SSLID_HUAWEI_MAX 199
#define EB_PUSH_SSLID_XIAOMI_MIN 200	// С������ 200-299
#define EB_PUSH_SSLID_XIAOMI_MAX 299
#define EB_PUSH_SSLID_IOS_DEV 7606616803963781LL	// IOS ��������
#define EB_PUSH_SSLID_IOS_RES 7715636013842198LL	// IOS ��ʽ����

/*==========================================================
��¼����
===========================================================*/
typedef enum EB_PUSH_SSLID_TYPE
{
	EB_PUSH_SSLID_TYPE_UNKNOWN								= 0x0		// δ֪���ͣ�˽����Ĭ�����ͣ�
	, EB_PUSH_SSLID_TYPE_USES_ENTBOOST_PUSH		= 0x01	// ͨ������ƽ̨����
	, EB_PUSH_SSLID_TYPE_SUPPORT_OTHER_PHONE	= 0x10	// ֧����������Ʒ���ֻ�
}EB_PUSH_SSLID_TYPE;

/*==========================================================
��¼����
===========================================================*/
typedef enum EB_UM_LOAD2_TYPE
{
	EB_UM_LOAD2_TYPE_UNKNOWN								= 0
	, EB_UM_LOAD2_TYPE_CONTACT_HEAD_VER						// 1 ���غ�����ϵ��ͷ��汾
	//, EB_UM_LOAD2_TYPE_GROUP_FORBID_INFO					// 2 ����Ⱥ�����״̬ -1:������� 0:���ý��� >0���Է�����
	//, EB_UM_LOAD2_TYPE_MEMBER_FORBID_INFO					// 3 ����Ⱥ��Ա����״̬ -1:������� 0:���ý��� >0���Է�����
}EB_UM_LOAD2_TYPE;

/*==========================================================
��Ϣ��Ӧ����
===========================================================*/
typedef enum EB_MSG_ACK_TYPE
{
	EB_MAT_SUCCESS											// 0 �ɹ�
	, EB_MAT_ERROR											// 1 ����
	, EB_MAT_CANCEL											// 2 ȡ������ܾ���
	, EB_MAT_REQUEST										// 3 ����
	, EB_MAT_WITHDRAW										// 4 ������Ϣ
	//, EB_MAT_DELETE										// 5 ������δ�ã�
	, EB_MAT_SELF_COLLECT					= 6		// 6 �����ղ�
	, EB_MAT_GROUP_COLLECT							// 7 Ⱥ�ղ�
	, EB_MAT_SAVE2CLOUDDRIVE	= 10			// 10 ��������
	, EB_MAT_RESEND											// 11 ���·���
}EB_MSG_ACK_TYPE;

/*==========================================================
��Ϣ��������
===========================================================*/
typedef enum EB_MSG_CHAT_TYPE
{
	EB_MSG_CHAT_TYPE_UNKNOWN
	, EB_MSG_CHAT_TYPE_USER
	, EB_MSG_CHAT_TYPE_GROUP
}EB_MSG_CHAT_TYPE;
/*==========================================================
�ղ���������
===========================================================*/
typedef enum EB_COLLECT_FROM_TYPE
{
	EB_COLLECT_FROM_TYPE_UNKNOWN
	, EB_COLLECT_FROM_TYPE_USER
	, EB_COLLECT_FROM_TYPE_GROUP
}EB_COLLECT_FROM_TYPE;


/*==========================================================
��������Ӧ����
===========================================================*/
typedef enum EB_DATASTREAM_ACK_TYPE
{
	EB_DSAT_UNKNOWN
	, EB_DSAT_OK
	, EB_DSAT_REQUEST
}EB_DATASTREAM_ACK_TYPE;

/*==========================================================
�Ự��Ӧ����
===========================================================*/
typedef enum EB_CALL_ACK_TYPE
{
	EB_CAT_UNKNOWN
	, EB_CAT_ACCEPT
	, EB_CAT_REJECT
	, EB_CAT_OFF_ACCEPT
	, EB_CAT_TIMEOUT
	, EB_CAT_DELETE
}EB_CALL_ACK_TYPE;

#define OFFLINE_SESSION_CLOSE	1
#define OFFLINE_USES_CLOSE		2
#define OFFLINE_SERVER_CLOSE	3

/*==========================================================
SOTP SIGN��
===========================================================*/
typedef enum EB_CALL_SIGN
{
	EB_SIGN_UNKNOWN
	//, EB_CS_CS_ONLINE		= 0x001
	//, EB_CS_CS_OFFLINE
	//, EB_CS_CS_ACTIVE
	//, EB_CS_CS_QUERY
	//, EB_CS_CS_LOAD
	// LC
	, EB_SIGN_S_ONLINE		= 0x101		// 257 *���������Ǽ�����
	, EB_SIGN_S_OFFLINE							// 258 *��������ע������
	, EB_SIGN_S_ACTIVE							// 259
	, EB_SIGN_S_QUERY								// 260
	, EB_SIGN_L_LOGON								// 261 ��¼��֤������APPID��֤���û���֤��
	, EB_SIGN_L_LOGOUT							// 262 ע���˳�
	, EB_SIGN_L_QUERY								// 263 �û���ѯ
	, EB_SIGN_L_REGAUTH		= 0x111		// 273 ע����֤
	, EB_SIGN_L_FINDPWD							// 274 �����һ�����
	, EB_SIGN_L_RESETPWD						// 275 ��������
	, EB_SIGN_Q_INFO			= 0x121		// 289 *����������ѯ����
	, EB_SIGN_P_INFO								// 290 *����������������1
	, EB_SIGN_SP_INFO								// 291 *����������ѯ����2
	// UM
	, EB_SIGN_U_REG				= 0x201		// 513 ע���ʺ�
	, EB_SIGN_U_SINFO								// 514 
	, EB_SIGN_U_SHEAD
	, EB_SIGN_U_ONLINE
	, EB_SIGN_U_LOAD
	, EB_SIGN_U_OFFLINE
	, EB_SIGN_U_QUERY
	, EB_SIGN_U_MGR
	, EB_SIGN_U_GINFO
	, EB_SIGN_U_SPUSH
	, EB_SIGN_U_LOAD2
	, EB_SIGN_V_REQUEST			= 0x211	// 529 ������Ƶ�Ự
	, EB_SIGN_FV_REQUEST
	, EB_SIGN_V_ACK
	, EB_SIGN_FV_ACK
	, EB_SIGN_V_END
	, EB_SIGN_FV_END
	, EB_SIGN_RD_REQUEST		= 0x218	// 536 ����Զ��Э��/Զ������
	, EB_SIGN_FRD_REQUEST
	, EB_SIGN_RD_ACK
	, EB_SIGN_FRD_ACK
	, EB_SIGN_RD_END
	, EB_SIGN_FRD_END

	, EB_SIGN_C_CALL			= 0x221		// 545 ������Ự
	, EB_SIGN_C_ENTER
	, EB_SIGN_FC_CALL
	, EB_SIGN_FC_ENTER
	, EB_SIGN_C_ACK
	, EB_SIGN_FC_ACK
	, EB_SIGN_C_HANGUP
	, EB_SIGN_FC_HANGUP
	, EB_SIGN_U_MSG
	, EB_SIGN_FU_MSG
	, EB_SIGN_U_MACK

	, EB_SIGN_AB_EDIT			= 0x231		// 561 �½����޸���ϵ������
	, EB_SIGN_AB_DEL								// 562 ɾ����ϵ������
	, EB_SIGN_AB_LOAD								// 563 ��ѯ������ϵ������
	, EB_SIGN_UG_EDIT								// 564 �½����޸ĺ��ѷ���
	, EB_SIGN_UG_DEL								// 565 ɾ�����ѷ���
	, EB_SIGN_UG_LOAD								// 566 ��ѯ���غ��ѷ���
	, EB_SIGN_ENT_EDIT		= 0x241		// 577 �޸���ҵ����
	, EB_SIGN_DEP_EDIT							// 578 �½����޸Ĳ�������
	, EB_SIGN_DEP_DEL								// 579 ɾ����������
	, EB_SIGN_EMP_EDIT							// 580 �½����޸�Ա������
	, EB_SIGN_EMP_DEL								// 581 ɾ��Ա������
	, EB_SIGN_ENT_LOAD							// 582 ��ѯ������֯�ṹ�����ţ�Ա��������
	, EB_SIGN_FENT_INFO							// 583 ������ҵ����
	, EB_SIGN_FDEP_INFO							// 584 ���в�������
	, EB_SIGN_FEMP_INFO							// 585 ����Ա������
	, EB_SIGN_DEP_GET			= 0x24E		// 590 ��ѯ��ȡ��������
	, EB_SIGN_EMP_GET								// 591 ��ѯ��ȡԱ������
	, EB_SIGN_R_EDIT		= 0x251			// 593 �½����޸�������Դ
	, EB_SIGN_R_DEL									// 594 ɾ��������Դ
	, EB_SIGN_R_LOAD								// 595 ɾ��������Դ
	, EB_SIGN_R_INFO								// 596 ɾ��������Դ
	, EB_SIGN_CS_LOAD		= 0x261
	, EB_SIGN_CS_ADD
	, EB_SIGN_CS_DEL
	, EB_SIGN_FUNC_REQ		= 0x271
	, EB_SIGN_FUNC_AUTH
	, EB_SIGN_FUNC_LOAD
	, EB_SIGN_FUNC_EDIT
	, EB_SIGN_FUNC_DEL
	, EB_SIGN_FUNC_SUB
	, EB_SIGN_FUNC_SETICON
	, EB_SIGN_FNAV_SET
	, EB_SIGN_FNAV_DEL
	, EB_SIGN_FNAV_LOAD

	, EB_SIGN_VER_CHECK		= 0x281
	, EB_SIGN_DICT_LOAD		= 0x291

	// CM
	, EB_SIGN_CM_ENTER		= 0x301
	, EB_SIGN_FCM_ENTER
	, EB_SIGN_CM_EXIT
	, EB_SIGN_FCM_EXIT
	, EB_SIGN_CM_ACTIVE
	, EB_SIGN_CM_MSG
	, EB_SIGN_FCM_MSG
	, EB_SIGN_CM_MACK
	, EB_SIGN_FCM_MACK
	, EB_SIGN_DS_SEND
	, EB_SIGN_FDS_SEND
	, EB_SIGN_DS_CHECK
	, EB_SIGN_DS_ACK
	, EB_SIGN_CM_NOTIFY
	, EB_SIGN_FCM_NOTIFY
	, EB_SIGN_P2P_REQUEST	= 0x311
	, EB_SIGN_P2P_RESPONSE
	, EB_SIGN_FP2P_REQUEST
	, EB_SIGN_FP2P_RESPONSE
	, EB_SIGN_P2P_TRY
	//, EB_SIGN_CR_GET
	, EB_SIGN_PS_SEND	= 0x321
	, EB_SIGN_RTP_ON		= 0x331
	, EB_SIGN_RTP_OFF

	, EB_SIGN_A_ON		= 0x401
	, EB_SIGN_A_OFF
	, EB_SIGN_A_MSG
	, EB_SIGN_FA_MSG
	, EB_SIGN_A_MACK
	, EB_SIGN_FA_MACK
	, EB_SIGN_AU_MSG
	, EB_SIGN_AU_MAIL
	, EB_SIGN_EXE_JOB
	, EB_SIGN_SYNC_EDITPWD	= 0x411
	, EB_SIGN_SYNC_USERINFO
	, EB_SIGN_SYS_EDIT

}EB_CALL_SIGN;

/*==========================================================
ϵͳ����
===========================================================*/
const int	EB_MAX_REQUEST_OS_COUNT	= 140;		// һ������������ݲ������ݰ�

///////////////////
#define POP_APP_NAME_CENTER_SERVER		"POPCenterServer"
#define POP_APP_NAME_LOGON_CENTER		"POPLogonCenter"
#define POP_APP_NAME_USER_MANAGER		"POPUserManager"
#define POP_APP_NAME_CHAT_MANAGER		"POPChatManager"
#define POP_APP_NAME_APP_CENTER			"POPAppCenter"
#define EB_APP_NAME_FILE_SERVER			"ebsemail"
#define EB_APP_NAME_RD_SERVER			"ebrds"
#define EB_APP_NAME_MMV_SERVER			"ebmmvs"
#define EB_APP_NAME_MMA_SERVER			"ebmmas"
#define EB_APP_NAME_LOGON_CENTER		"eblc"

//#define EB_CALL_NAME_CS_ONLINE			"pop_cs_online"
//#define EB_CALL_NAME_CS_OFFLINE		"pop_cs_offline"
//#define EB_CALL_NAME_CS_ACTIVE			"pop_cs_active"
//#define EB_CALL_NAME_CS_QUERY			"pop_cs_query"
//#define EB_CALL_NAME_CS_LOAD			"pop_cs_load"

#define EB_CALL_NAME_S_ONLINE			"eb_s_online"
#define EB_CALL_NAME_S_OFFLINE			"eb_s_offline"
#define EB_CALL_NAME_S_ACTIVE			"eb_s_active"
#define EB_CALL_NAME_S_QUERY			"eb_s_query"
#define EB_CALL_NAME_LC_LOGON			"eb_l_logon"
#define EB_CALL_NAME_LC_LOGOUT			"eb_l_logout"
#define EB_CALL_NAME_LC_QUERY			"eb_l_query"
#define EB_CALL_NAME_LC_REGAUTH			"eb_l_regauth"
#define EB_CALL_NAME_LC_FINDPWD			"eb_l_findpwd"
#define EB_CALL_NAME_LC_RESETPWD		"eb_l_resetpwd"
#define EB_CALL_NAME_Q_INFO				"eb_q_info"
#define EB_CALL_NAME_P_INFO				"eb_p_info"
#define EB_CALL_NAME_SP_INFO			"eb_sp_info"

#define EB_CALL_NAME_RD_REQUEST			"eb_rd_request"
#define EB_CALL_NAME_RD_ACK				"eb_rd_ack"
#define EB_CALL_NAME_RD_END				"eb_rd_end"
#define EB_CALL_NAME_V_REQUEST			"eb_v_request"
#define EB_CALL_NAME_V_ACK				"eb_v_ack"
#define EB_CALL_NAME_V_END				"eb_v_end"
#define EB_CALL_NAME_UM_REG				"eb_u_reg"
#define EB_CALL_NAME_UM_QUERY			"eb_u_query"
#define EB_CALL_NAME_UM_SINFO			"eb_u_sinfo"
#define EB_CALL_NAME_UM_GINFO			"eb_u_ginfo"
#define EB_CALL_NAME_UM_MGR				"eb_u_mgr"
#define EB_CALL_NAME_UM_SHEAD			"eb_u_shead"
#define EB_CALL_NAME_UM_ONLINE			"eb_u_online"
#define EB_CALL_NAME_UM_LOAD			"eb_u_load"
#define EB_CALL_NAME_UM_LOAD2			"eb_u_load2"
#define EB_CALL_NAME_UM_OFFLINE			"eb_u_offline"
//#define EB_CALL_NAME_UMIU_GROUP		"eb_umiu_group"
#define EB_CALL_NAME_UM_MSG				"eb_u_msg"
#define EB_CALL_NAME_UM_MACK			"eb_u_mack"
#define EB_CALL_NAME_UM_CALL			"eb_c_call"
#define EB_CALL_NAME_C_ENTER			"eb_c_enter"
#define EB_CALL_NAME_UM_CACK			"eb_c_ack"
#define EB_CALL_NAME_UM_HANGUP			"eb_c_hangup"

#define EB_CALL_NAME_AB_EDIT			"eb_ab_edit"
#define EB_CALL_NAME_AB_DEL				"eb_ab_del"
#define EB_CALL_NAME_AB_LOAD			"eb_ab_load"
#define EB_CALL_NAME_UG_EDIT			"eb_ug_edit"
#define EB_CALL_NAME_UG_DEL				"eb_ug_del"
#define EB_CALL_NAME_UG_LOAD			"eb_ug_load"

#define EB_CALL_NAME_R_EDIT				"eb_r_edit"
#define EB_CALL_NAME_R_DEL				"eb_r_del"
#define EB_CALL_NAME_R_LOAD				"eb_r_load"

#define EB_CALL_NAME_ENT_EDIT			"eb_ent_edit"
#define EB_CALL_NAME_DEP_EDIT			"eb_dep_edit"
#define EB_CALL_NAME_DEP_DEL			"eb_dep_del"
#define EB_CALL_NAME_DEP_OP				"eb_dep_op"
#define EB_CALL_NAME_EMP_EDIT			"eb_emp_edit"
#define EB_CALL_NAME_EMP_DEL			"eb_emp_del"
#define EB_CALL_NAME_ENT_LOAD			"eb_ent_load"

#define EB_CALL_NAME_FUNC_REQ			"eb_func_req"
#define EB_CALL_NAME_FUNC_AUTH			"eb_func_auth"
#define EB_CALL_NAME_FUNC_LOAD			"eb_func_load"
#define EB_CALL_NAME_FUNC_EDIT			"eb_func_edit"
#define EB_CALL_NAME_FUNC_SETICON		"eb_func_seticon"
#define EB_CALL_NAME_FUNC_DEL			"eb_func_del"
#define EB_CALL_NAME_FUNC_SUB			"eb_func_sub"
#define EB_CALL_NAME_FNAV_SET			"eb_fnav_set"
#define EB_CALL_NAME_FNAV_DEL			"eb_fnav_del"
#define EB_CALL_NAME_FNAV_LOAD			"eb_fnav_load"

#define EB_CALL_NAME_CS_ADD				"eb_cs_add"
#define EB_CALL_NAME_CS_DEL				"eb_cs_del"

#define EB_CALL_NAME_VER_CHECK			"eb_ver_check"
#define EB_CALL_NAME_DICT_LOAD			"eb_dict_load"

//#define EB_CALL_NAME_CR_SET				"eb_cr_set"
//#define EB_CALL_NAME_CR_GET				"eb_cr_get"
#define EB_CALL_NAME_CM_ENTER			"eb_cm_enter"
#define EB_CALL_NAME_CM_EXIT			"eb_cm_exit"
#define EB_CALL_NAME_CM_NOTIFY			"eb_cm_notify"
#define EB_CALL_NAME_CM_ACTIVE			"eb_cm_active"
#define EB_CALL_NAME_CM_MSG				"eb_cm_msg"
#define EB_CALL_NAME_CM_QUERY			"eb_cm_query"
#define EB_CALL_NAME_CM_MACK			"eb_cm_mack"
#define EB_CALL_NAME_DS_SEND			"eb_ds_send"
#define EB_CALL_NAME_DS_CHECK			"eb_ds_check"
#define EB_CALL_NAME_DS_ACK				"eb_ds_ack"
#define EB_CALL_NAME_P2P_REQ			"eb_p2p_req"
#define EB_CALL_NAME_P2P_RES			"eb_p2p_res"
#define EB_CALL_NAME_P2P_TRY			"~eb_p2p_try"
#define EB_CALL_NAME_PS_SEND			"eb_ps_send"

#define EB_CALL_NAME_RTP_ON				"eb_rtp_on"
#define EB_CALL_NAME_RTP_OFF			"eb_rtp_off"

#define EB_CALL_NAME_A_ON				"eb_a_on"
#define EB_CALL_NAME_A_OFF				"eb_a_off"
#define EB_CALL_NAME_A_MSG				"eb_a_msg"
#define EB_CALL_NAME_A_MACK				"eb_a_mack"
#define EB_CALL_NAME_AU_MSG				"eb_au_msg"
#define EB_CALL_NAME_AU_MAIL			"eb_au_mail"
#define EB_CALL_NAME_EXE_JOB			"eb_exe_job"
#define EB_CALL_NAME_SYNC_EDITPWD		"eb_sync_editpwd"
#define EB_CALL_NAME_SYNC_USERINFO		"eb_sync_userinfo"
#define EB_CALL_NAME_SYS_EDIT			"eb_sys_edit"

#endif // __eb_define1_h__
