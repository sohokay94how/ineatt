#pragma once
#define MAX_VOL 100
class MixerWrap
{
public:
	MixerWrap(void){};
public:
	virtual ~MixerWrap(void){};

	static void MicphoneBoost(bool bIsBoost);	// ��֧��WIN7
	
	static void MicphoneMut(BOOL bIsMut);		// ���þ�����֧��WIN7
	static void StereoMix(BOOL bMute);			// ���û���
	static bool StereoMix_W7(BOOL bMute, float fVolume=-1.0);	// ���û��� С��0.0����������
	static bool MicphoneMut_W7(BOOL bIsMut,float fVolume=-1.0); //������˷�����  С��0.0����������
	static bool GetMicphone_W7(BOOL &bMute,float &pdwVolume); //��ȡ��˷�����
	static void MicphoneBoost_W7(float fValue);//������˷���ǿ�ȼ� 0-30��֧��WIN7
	static void GetMicphoneLevel(float &fValue); //��ȡ��˷���ǿ�ȼ� 0-30��֧��WIN7
	static void GetMicphoneLevelData(float &nMin, float &nMax, float &nStep); //��ȡ��˷���Сֵ�����ֵ������
	static bool GetSpeakerValue_W7(BOOL &bMute, float &fVolume); //��ȡ��������
	static bool GetSpeakerValue_W72(BOOL &bMute, float &fVolume); //��ȡ��������
	static bool SetSpeakerValue_W7(BOOL bMute, float fVolume=-1.0); //�������Ⱦ�����������С��0.0����������
	static bool SetSpeakerValue_W72(BOOL bMute, float fVolume=-1.0); //�������Ⱦ�����������С��0.0����������

		
	//static bool MutSpeaker_W7(bool bMute,float fVolume);

	//������������������
	static void StereoMixVolume(int nVolume);		// ��֧��WIN7
	static void OutPutMicphoneVolume(int nVolume);
	static void InPutMicphoneVolume(int nVolume);


	static int  SelectRecordIn(DWORD  dwSrcType);
	static int  SelectRecordInByName(const TCHAR*  szSrcName);
	

};
