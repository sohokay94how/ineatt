#ifndef __MediaDevice_h_
#define __MediaDevice_h_

#include "Mixer.h"
#include "MixerWrap.h"
#define  WIN_XP    2
#define  WIN_2003  3
#define  WIN_VISTA 4
#define  WIN_7     5
#define  WIN_2008  6
#define  WIN_8     8
int GetOSVer()  
{  
	OSVERSIONINFO   osver;     
	osver.dwOSVersionInfoSize   =   sizeof(OSVERSIONINFO);     
	GetVersionEx(&osver);     
	if(osver.dwPlatformId == 2)  
	{  
		if(osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)   //xp
		{  
			return WIN_XP;  
		}  
		if(osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)  //2003
		{  
			return WIN_2003;  
		}  
		if(osver.dwMajorVersion ==  6 && (osver.dwMinorVersion == 0 || osver.dwMinorVersion == 1))  //vista or 2008
		{  
			return WIN_VISTA;  
		}  
		if(osver.dwMajorVersion ==  6 && osver.dwMinorVersion == 1 )  //win7
		{  
			return WIN_7;  
		}  
		if(osver.dwMajorVersion ==  6 && osver.dwMinorVersion == 2)  //win8
		{  
			return WIN_8;  
		}  
	}  
	return 0;  
} 

void GetSystemVolume(BOOL &bMute, float &dVolumeValue) //��ȡ��������ֵ
{
	const int nOSVer = GetOSVer();
	if( nOSVer == WIN_XP)
	{
		CMixer mixer;
		bMute = mixer.GetMute(CMixer::SPEAKERS)?TRUE:FALSE;
		dVolumeValue = (float)(mixer.GetVolume(CMixer::SPEAKERS)*1.0);
	}
	else if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::GetSpeakerValue_W72(bMute,dVolumeValue); 
	}
}

void SetSystemVolume(BOOL bMute, float dVolumeValue) //������������ֵ
{
	const int nOSVer = GetOSVer();
	if( nOSVer == WIN_XP)
	{
		CMixer mixer;
		mixer.SetMute(CMixer::SPEAKERS, bMute?true:false);
		if (dVolumeValue>=0.0)
			mixer.SetVolume(CMixer::SPEAKERS,(long)dVolumeValue);
	}
	else if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::SetSpeakerValue_W72(bMute,dVolumeValue);
	}
}

void GetMicrophoneValue(BOOL &bMute,float &dVolumeValue) //��ȡ��˷�����
{
	const int nOSVer = GetOSVer();
	if( nOSVer == WIN_XP)
	{
		CMixer mixer;
		bMute = mixer.GetMute(CMixer::MICROPHONE)?true:false;
		dVolumeValue = (float)mixer.GetVolume(CMixer::MICROPHONE);
	}
	else if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::GetMicphone_W7(bMute,dVolumeValue);
	}
}

void SetMicrophoneValue(BOOL bMute,float dVolumeValue) //������˷�����
{
	const int nOSVer = GetOSVer();
	if( nOSVer == WIN_XP)
	{
		CMixer mixer;
		mixer.SetMute(CMixer::MICROPHONE, bMute?true:false);
		if (dVolumeValue>=0.0)
			mixer.SetVolume(CMixer::MICROPHONE,(long)dVolumeValue);
		//MixerWrap::MicphoneMut(bMute);
	}
	else if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::MicphoneMut_W7(bMute, dVolumeValue);
	}
}

bool GetMicroBoostData(float &fMin, float &fMax, float &fStep) //��ȡ��˷���ǿ�ȼ�����Сֵ�����ֵ������
{
	const int nOSVer = GetOSVer();
	if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::GetMicphoneLevelData(fMin, fMax,fStep);
		return true;
	}
	return false;
}

bool GetMicroBoostLevel(float &dMicroBoostLevel) //��ȡ��˷���ǿ�ȼ�
{
	const int nOSVer = GetOSVer();
	if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::GetMicphoneLevel(dMicroBoostLevel);
		return true;
	}
	return false;
}

void SetMicroBoostLevel(float dMicroBoostLevel) //������˷���ǿ�ȼ�
{
	const int nOSVer = GetOSVer();
	if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::MicphoneBoost_W7(dMicroBoostLevel);
	}else
	{
		// XP: ����0.0Ϊ���ã�С��0.0Ϊ����
		MixerWrap::MicphoneBoost(dMicroBoostLevel>0.0?true:false);
	}
}

void SetStereoMix(BOOL bMute) //���û���������TRUE=����������FALSE����������
{
	const int nOSVer = GetOSVer();
	if( nOSVer == WIN_XP)
	{
		MixerWrap::StereoMix(bMute);
	}
	else if(nOSVer == WIN_7|| nOSVer == WIN_8 || nOSVer == WIN_VISTA)
	{
		MixerWrap::StereoMix_W7(bMute);
	}
}

#endif // __MediaDevice_h_
