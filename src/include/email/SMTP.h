// SMTP.h: interface for the CSMTP class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMTP_H__55DE48CB_BEA4_11D1_870E_444553540000__INCLUDED_)
#define AFX_SMTP_H__55DE48CB_BEA4_11D1_870E_444553540000__INCLUDED_

//#define USES_AFX_SOCKET
//#ifdef USES_AFX_SOCKET
//#include "afxsock.h"
//#endif
#include "../CgcTcpClient.h"
#include "MailMessage.h"
#include "ebmailobj.h"

// SMTP��������׼�˿ں�
#define SMTP_PORT 25
#define SMTP_SSL_PORT 465
// ������ջ�������С		
#define RESPONSE_BUFFER_SIZE 1024

CEBMailInfo::pointer ParserMailInfo(const tstring& sMailString, bool bMailMessage, bool bParserHeadOnly);

class CSmtpResponseInfo
{
public:
	typedef boost::shared_ptr<CSmtpResponseInfo> pointer;
	static CSmtpResponseInfo::pointer create(int nCode, const tstring& sMsg)
	{
		return CSmtpResponseInfo::pointer(new CSmtpResponseInfo(nCode, sMsg));
	}

	int m_nResponseCode;
	tstring m_sResponseMsg;
	CSmtpResponseInfo(int nCode, const tstring& sMsg)
		: m_nResponseCode(nCode), m_sResponseMsg(sMsg)
	{
	}
	CSmtpResponseInfo(void)
		: m_nResponseCode(0)
	{}
};

class CSMTP  
	: public entboost::TcpClient_Callback	// for ssl tcp
{
public:
	typedef boost::shared_ptr<CSMTP> pointer;
	enum MAIL_TYPE
	{
		MAIL_TYPE_SMTP
		, MAIL_TYPE_POP3
	};
	static CSMTP::pointer create(const char* szSMTPServerName, size_t nPort, bool bSSL, MAIL_TYPE nMailType=MAIL_TYPE_SMTP)
	{
		return CSMTP::pointer(new CSMTP(szSMTPServerName,nPort,bSSL,nMailType));
	}
	CSMTP( const char* szSMTPServerName, size_t nPort, bool bSSL, MAIL_TYPE nMailType=MAIL_TYPE_SMTP);
	virtual ~CSMTP(void);

	static const tstring & replace(tstring & strSource, const tstring & strFind, const tstring &strReplace);
	//static void Test2_SSL_library_init(void);

	// ��¼���������ԵĽӿ�
	void SetServerProperties( const char* szSMTPServerName, size_t nPort = SMTP_PORT);
	tstring GetLastError(void) const;
	size_t GetPort(void) const {return m_nPort;}

	// �����������ϵ����
	bool Disconnect(void);
	int Connect(const char* sMailAccount, const char* sPasswd, bool* pOutTimeout = NULL);	// 1:ok -1:server error 0:user error
	bool IsConnected(void) const;
	//bool Login(void);
	void SetMailId(const std::string& v) {m_sMailId = v;}
	const std::string& GetMailId(void) const {return m_sMailId;}

	// �����յ��Ļ�Ӧ��Ϣ
	virtual bool FormatMailMessage( CMailMessage* msg );
	bool SendMailMessage( CMailMessage* msg );
	bool SendSTATCommand(void);
	bool SendLISTCommand(int nMailId,std::vector<int>& pOutMailSizeList,bool& pOutFinished);
	bool SendUIDLCommand(int nMailId, std::vector<tstring>& pOutMailIdList,bool& pOutFinished);
	CEBMailInfo::pointer SendRETRCommand(int nMailId, bool& pOutGetDataError);
	bool SendTOPCommand(int nMailId, int nNumber);
	bool SendDELECommand(int nMailId);
	bool SendRSETCommand(void);
	bool SendNOOPCommand(void);
	tstring GetServerHostName(void) const {return m_sSMTPServerHostName;}
	const tstring& GetErrorString(void) const {return m_sError;}

	//// ����������ʽ�ģ����Ҫ�ṩȡ��ͨ�ŵķ���
	//void Cancel(void);
	inline bool IsFullNumber(const char* pString, size_t nLen)
	{
		for (size_t i=0;i<nLen; i++)
		{
			const char pChar = pString[i];
			if (pChar<'0' || pChar>'9')
				return false;
		}
		return true;
	}
	inline bool IsFullNumberX(const char* pString, size_t nLen)
	{
		for (size_t i=0;i<nLen; i++)
		{
			const char pChar = pString[i];
			if (pChar==' ')
				continue;
			if (pChar<'0' || pChar>'9')
				return false;
		}
		return true;
	}
	void SetSSLContext(bool bDelete, boost::asio::ssl::context * sslctx);

private:
	void ClearTcpClient(void);
	// �����ʼ�����
	tstring cook_body( CMailMessage* msg ) const;
	// ������õĻ�Ӧ��Ϣ
	bool getMailResponseSMTP(size_t response_expected, int nTimeoutSecond = 5, bool* pOutTimeout = NULL);
	bool getMailResponsePOP3(int nTimeoutSecond = 5, CSmtpResponseInfo::pointer* pOutResponse=NULL, bool* pOutTimeout = NULL);

	tstring m_sError;
	tstring m_sSMTPServerHostName;
	size_t m_nPort;
	bool m_bSsl;
	MAIL_TYPE m_nMailType;
	bool m_bDeleteMail;

	// ��SMTP������ͨ�ŵ��׽���
//#ifdef USES_AFX_SOCKET
//	CSocket* m_wsSMTPServer;
//#else
	boost::asio::ssl::context * m_sslctx;
	bool m_bDeleteCtx;
	entboost::CgcTcpClient::pointer m_wsSMTPServer;
	virtual void OnReceiveData(const mycp::asio::ReceiveBuffer::pointer& data);
//#endif

protected:
	// �����ʼ���Ϣ
	virtual bool transmit_message( CMailMessage* msg );

	CLockList<CSmtpResponseInfo::pointer> m_pResponseList;

	struct response_code
	{
		// ���û�еõ���Ӧ��Ϣ�������������Ϣ
		int nResponse;		
		std::string sMessage;	
	};

	enum eResponse
	{
		GENERIC_SUCCESS = 0,
		CONNECT_SUCCESS,
		PASS_SUCCESS,
		AUTH_LOGIN_SUCCESS,
		DATA_SUCCESS,
		QUIT_SUCCESS,
		// ����ֻ���ǵ��������ֻ�Ӧ��Ϣ
		// LAST_RESPONSE�����һ��Ԫ��
		LAST_RESPONSE	
	};
	static response_code response_table_smtp[];
	static response_code response_table_pop3[];
	std::string m_sMailId;
};

/*
Delivered-To: akee.yang@gmail.com

#endif // !defined(AFX_SMTP_H__55DE48CB_BEA4_11D1_870E_444553540000__INCLUDED_)