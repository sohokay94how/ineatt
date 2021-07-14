// Mixer.cpp: implementation of the CMixer class.
//
//#include "stdwx.h"
#include "Mixer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMixer::CMixer(HWND wnd)
: m_hWnd(wnd)
, m_nParam(0)

{
	m_VolRange = 100;

	for( int i = 0 ; i < MAX_MIXER_HANDLE ; i ++ )
		m_hMixer[i] = NULL;
}

CMixer::~CMixer()
{
	for( int i = 0 ; i < MAX_MIXER_HANDLE ; i ++ )
	{
		if (m_hMixer[i] != NULL)
			mixerClose(m_hMixer[i]);
	}
}

CMixer::CMixer(const int VolRange)
{
	m_VolRange = VolRange;
}
//----------------------------�趨����---------------------------------------

bool CMixer::GetVolumeControl(HMIXER hmixer ,long componentType,long ctrlType,MIXERCONTROL* mxc) const
{
	////��ѯ ¼����������� ��˷���·�ı�� 
	//MIXERLINE mxl_v;
	//UINT cConnections = (UINT)mxl.cConnections;
	//UINT dwSource_v=0;
	//do
	//{
	//	mxl_v.cbStruct = sizeof(mxl_v);
	//	mxl_v.dwDestination = mxl.dwDestination;
	//	mxl_v.dwSource = dwSource_v;
	//	dwSource_v++;
	//	if (MMSYSERR_NOERROR != 
	//		mixerGetLineInfo((HMIXEROBJ)m_hmx2, 
	//		&mxl_v, 
	//		MIXER_GETLINEINFOF_SOURCE))
	//		return FALSE;
	//} while ((dwSource_v < cConnections) && 
	//	(mxl_v.dwComponentType != MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE));

	//if((dwSource_v > cConnections) || 
	//	(mxl_v.dwComponentType !=MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE))
	//	return FALSE; 
	//dwSource_v--;//�õ����


	////����ʵ����"ǿ��"��ѡ��˷���·Ϊ¼��Դ����
	////MIXERCONTROL mxc;
	//MIXERLINECONTROLS mxlc;
	//mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	//mxlc.dwLineID = mxl.dwLineID;
	//mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_MUX;
	////MIXERCONTROL_CONTROLTYPE_MUTE;
	//mxlc.cControls = 1;
	//mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	//mxlc.pamxctrl = mxc; //Ϊ�˵õ���Ӧ��mxc.dwControlID��
	////����mxlc.dwLineID��mxlc.dwControlTypeָ������·����
	////Ŀǰ����¼��Ŀ�굥Ԫ��¼����Դ��·����ѡ����·���ã�
	//if (::mixerGetLineControls((HMIXEROBJ)m_hmx2,
	//	&mxlc,
	//	MIXER_OBJECTF_HMIXER |
	//	MIXER_GETLINECONTROLSF_ONEBYTYPE)
	//	!= MMSYSERR_NOERROR) return -1; 

	////����mxc.dwControlID������·��
	//MIXERCONTROLDETAILS_BOOLEAN mxcdMute[8];
	//MIXERCONTROLDETAILS mxcd;
	//mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	//mxcd.dwControlID = mxc.dwControlID;//�������&mxc�õ�
	//mxcd.cChannels = 1;
	//mxcd.cMultipleItems =mxc.cMultipleItems;//��·������Ŀ
	//mxcd.cbDetails = sizeof(*mxcdMute);
	//mxcd.paDetails =&mxcdMute;//��ż������
	//if (::mixerGetControlDetails((HMIXEROBJ)m_hmx2,
	//	&mxcd,
	//	MIXER_OBJECTF_HMIXER |
	//	MIXER_GETCONTROLDETAILSF_VALUE)
	//	!= MMSYSERR_NOERROR) return -1;

	////����Ӧ��ѡ�ı�
	//int j;
	//for(j=0;j<(int)mxc.cMultipleItems;j++)
	//	mxcdMute[j].fValue=false;
	//mxcdMute[dwSource_v].fValue=true; 

	////��������dwControlID��������·����
	//if (::mixerSetControlDetails((HMIXEROBJ)hmixer,
	//	&mxcd,
	//	MIXER_OBJECTF_HMIXER |
	//	MIXER_GETCONTROLDETAILSF_VALUE)
	//	!= MMSYSERR_NOERROR) return -1; 
//}//for(i;i<devnum;i++)
//return TRUE;
//}
//

	MIXERLINECONTROLS mxlc;
	MIXERLINE mxl;
	bool exist = false;
	memset(&mxl, 0, sizeof(MIXERLINE));
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = componentType;

	if (/*componentType == MIXERLINE_COMPONENTTYPE_SRC_DIGITAL ||
		*/componentType == MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE)
	{
		//mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
		// add by yhz
		MMRESULT mr = mixerGetLineInfo((HMIXEROBJ)hmixer, &mxl, MIXER_OBJECTF_HMIXER|MIXER_GETLINEINFOF_COMPONENTTYPE);
		if (mr |= MMSYSERR_NOERROR)
			return false;
		exist = true;

		////��ȡ¼����˷��豸
		//mxl.dwComponentType   =   MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
		////   �õ�¼�������е�������  
		//MMRESULT mr = mixerGetLineInfo(   (HMIXEROBJ)hmixer,   &mxl,  
		//	MIXER_OBJECTF_HMIXER   |   MIXER_GETLINEINFOF_COMPONENTTYPE   );  

		//if (mr |= MMSYSERR_NOERROR)
		//	return false;

		////   ������������  
		//DWORD   dwConnections   =   mxl.cConnections;  
		////   ׼����ȡ��˷��豸��ID  
		//DWORD   dwLineID   =   0;  
		//for   (   DWORD   i   =   0;   i   <   dwConnections;   i++   )  
		//{  
		//	//   ö��ÿһ���豸����Source��ID���ڵ�ǰ�ĵ�������  
		//	mxl.dwSource   =   i;  
		//	//   ����SourceID������ӵ���Ϣ  
		//	mr   =   mixerGetLineInfo(   (HMIXEROBJ)hmixer,   &mxl,  
		//		MIXER_OBJECTF_HMIXER   |   MIXER_GETLINEINFOF_SOURCE   );  
		//	//   �жϺ���ִ�д���  
		//	if   (   mr   !=   0   )  
		//	{  
		//		// add by yhz
		//		continue;
		//		//break;  
		//	}  
		//	//   �����ǰ�豸��������˷磬������ѭ����  
		//	if   (   mxl.dwComponentType   ==  
		//		MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE   )  
		//	{  
		//		exist = true;
		//		break;  
		//	}  
		//}
	}else if(!mixerGetLineInfo((HMIXEROBJ)hmixer, &mxl, MIXER_GETLINEINFOF_COMPONENTTYPE))
	{
		exist = true;
	}

	if (exist)
	{
		mxlc.cbStruct = sizeof(mxlc);
		mxlc.dwLineID = mxl.dwLineID;
		mxlc.dwControlType = ctrlType;
		mxlc.cControls = 1;
		mxlc.cbmxctrl = sizeof(MIXERCONTROL);
		mxlc.pamxctrl = mxc;
		if(mixerGetLineControls((HMIXEROBJ)hmixer,&mxlc,MIXER_GETLINECONTROLSF_ONEBYTYPE))
			return 0;
		else
			return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------
long CMixer::GetMuteValue(HMIXER hmixer ,MIXERCONTROL *mxc) const
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_BOOLEAN mxcdMute;
	mxcd.hwndOwner = 0;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.dwControlID = mxc->dwControlID;
	mxcd.cbDetails = sizeof(mxcdMute);
	mxcd.paDetails = &mxcdMute;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	if (mixerGetControlDetails((HMIXEROBJ)hmixer, &mxcd,MIXER_OBJECTF_HMIXER|MIXER_GETCONTROLDETAILSF_VALUE))
		return 0;
		//return -1;
	return mxcdMute.fValue;
}

//---------------------------------------------------------------------------
unsigned long CMixer::GetVolumeValue(HMIXER hmixer ,MIXERCONTROL *mxc) const
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_UNSIGNED vol;
	vol.dwValue=0;
	mxcd.hwndOwner = 0;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.dwControlID = mxc->dwControlID;
	mxcd.cbDetails = sizeof(vol);
	mxcd.paDetails = &vol;
	mxcd.cChannels = 1;
	if(mixerGetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER|MIXER_GETCONTROLDETAILSF_VALUE))
		return -1;
	return vol.dwValue;
}

//---------------------------------------------------------------------------
bool CMixer::SetMuteValue(HMIXER hmixer ,MIXERCONTROL *mxc, bool mute)
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_BOOLEAN mxcdMute;
	mxcdMute.fValue=mute;
	mxcd.hwndOwner = 0;
	mxcd.dwControlID = mxc->dwControlID;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.cbDetails = sizeof(mxcdMute);
	mxcd.paDetails = &mxcdMute;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	if (mixerSetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER|MIXER_SETCONTROLDETAILSF_VALUE))
		return false;
	return true;
}

//---------------------------------------------------------------------------

bool CMixer::SetVolumeValue(HMIXER hmixer ,MIXERCONTROL *mxc, long volume)
{
	MIXERCONTROLDETAILS mxcd;
	MIXERCONTROLDETAILS_UNSIGNED vol;
	vol.dwValue = volume;
	mxcd.hwndOwner = 0;
	mxcd.dwControlID = mxc->dwControlID;
	mxcd.cbStruct = sizeof(mxcd);
	mxcd.cbDetails = sizeof(vol);
	mxcd.paDetails = &vol;
	mxcd.cChannels = 1;
	return (mixerSetControlDetails((HMIXEROBJ)hmixer, &mxcd, MIXER_OBJECTF_HMIXER|MIXER_SETCONTROLDETAILSF_VALUE)) == 0;
}

long CMixer::GetComponentType(MixerDevice dev) const
{
	switch (dev)
	{
	case WAVEOUT:
		return MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT;
	case SYNTHESIZER:
		return MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER;
	//case WAVEIN:
	//	return MIXERLINE_COMPONENTTYPE_DST_WAVEIN;
	//case DIGITAL:
	//	return MIXERLINE_COMPONENTTYPE_SRC_DIGITAL;
	case MICROPHONE:
		//return MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;    //��˷�����
		return MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC;		// cd ����
		// device=MIXERLINE_COMPONENTTYPE_SRC_LINE; break;         //PC ����������

	case STEREOMIX:
		return MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER;	// ??
	default:
		return MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	}

}

bool CMixer::OpenMixer(MixerDevice dev)
{
	if (m_hMixer[dev] == NULL)
	{
		DWORD dwOpen = 0;
		if (m_hWnd)
			dwOpen |= CALLBACK_WINDOW;

		if(mixerOpen(&m_hMixer[dev], 0, (DWORD)m_hWnd, 0, dwOpen)) return false;
	}
	return true;
}

void CMixer::CloseMixer(MixerDevice dev)
{
	if (m_hMixer[dev] != NULL)
	{
		mixerClose(m_hMixer[dev]);
		m_hMixer[dev] = NULL;
	}
}

//---------------------------------------------------------------------------
unsigned long /*WINAPI */CMixer::GetVolume(MixerDevice dev)//�õ��豸������dev=0��������1WAVE ,2MIDI ,3 LINE IN
{

	unsigned rt=0;
	MIXERCONTROL volCtrl;

	if (!OpenMixer(dev)) return -1;

	long device = GetComponentType(dev);
	if(!GetVolumeControl(m_hMixer[dev],device,MIXERCONTROL_CONTROLTYPE_VOLUME,&volCtrl))
	{
		return -1;
	}
	rt=GetVolumeValue(m_hMixer[dev],&volCtrl)*m_VolRange /volCtrl.Bounds.lMaximum;
	return rt;
}

bool CMixer::GetMaxMin(MixerDevice dev, long & min, long & max)
{
	bool rc=false;
	MIXERCONTROL volCtrl;
	long device = GetComponentType(dev);

	if (!OpenMixer(dev)) return false;

	if(GetVolumeControl(m_hMixer[dev],device,MIXERCONTROL_CONTROLTYPE_VOLUME,&volCtrl))
	{
		min = volCtrl.Bounds.lMinimum;
		max = volCtrl.Bounds.lMaximum;
		rc = true;
	}
	return rc;
}

bool CMixer::SelectSteteoMix(int SteteoMix)
{
	if (SteteoMix == 0)
	{
		SetMute(CMixer::MICROPHONE, false);
		//SetMute(CMixer::DIGITAL, false);
		SetMute(CMixer::WAVEOUT, true);
	}else if (SteteoMix == 1)
	{
		SetMute(CMixer::MICROPHONE, true);
		//SetMute(CMixer::DIGITAL, true);
		SetMute(CMixer::WAVEOUT, false);
	}else
	{
		SetMute(CMixer::MICROPHONE, false);
		//SetMute(CMixer::DIGITAL, false);
		SetMute(CMixer::WAVEOUT, false);
	}
	return true;

	bool rc=false;
	//MIXERCONTROL volCtrl;
	//MixerDevice dev = STEREOMIX;
	//long device = GetComponentType(dev);

	//if (m_hMixer[STEREOMIX] == NULL)
	//	if(mixerOpen(&m_hMixer[dev], 0, 0, 0, 0)) return false;

	//if(GetVolumeControl(m_hMixer[dev],device,MIXERCONTROL_CONTROLTYPE_ONOFF,&volCtrl))
	//	if(SetMuteValue(m_hMixer[dev],&volCtrl,(bool)false))
	//		rc=true;

	return rc;
}

CMixer::MixerDevice CMixer::GetMixerDevice(HMIXER hMixer) const
{
	for( int i = 0 ; i < MAX_MIXER_HANDLE ; i++ )
	{
		if (m_hMixer[i] == hMixer)
			return (MixerDevice)i;
	}

	return UNKNOWN;
}

//---------------------------------------------------------------------------

bool /*WINAPI*/ CMixer::SetVolume(MixerDevice dev,long vol)//�����豸������
{
	// dev =0,1,2   �ֱ��ʾ������,����,MIDI ,LINE IN
	// vol=0-m_VolRange      ��ʾ�����Ĵ�С , �����뷵��������ֵ�õ��ǰٷֱȣ���������0 - m_VolRange ���������豸�ľ���ֵ
	// retrun false ��ʾ���������Ĵ�С�Ĳ������ɹ�
	// retrun true ��ʾ���������Ĵ�С�Ĳ����ɹ�

	bool rc=false;
	MIXERCONTROL volCtrl;
	long device = GetComponentType(dev);

	if (!OpenMixer(dev)) return false;

	if(GetVolumeControl(m_hMixer[dev],device,MIXERCONTROL_CONTROLTYPE_VOLUME,&volCtrl))
	{
		vol=vol*volCtrl.Bounds.lMaximum/m_VolRange ;
		if(SetVolumeValue(m_hMixer[dev],&volCtrl,vol))
			rc=true;
	}
	return rc;
}

//---------------------------------------------------------------------------
#include <stdio.h>
bool /*WINAPI*/ CMixer::SetMute(MixerDevice dev,/*long*/bool vol)//�����豸����
{
	// dev =0,1,2   �ֱ��ʾ������,����,MIDI ,LINE IN
	// vol=0,1      �ֱ��ʾȡ������,���þ���
	// retrun false ��ʾȡ�������þ����������ɹ�
	// retrun true ��ʾȡ�������þ��������ɹ�

	bool rc=false;
	MIXERCONTROL volCtrl;
	long device = GetComponentType(dev);

	//if (dev == MICROPHONE)
	//{
	//	long device2 = MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED;
	//	while (device2 < MIXERLINE_COMPONENTTYPE_SRC_LAST)
	//	{
	//		if (!OpenMixer(dev)) return false;

	//		if(GetVolumeControl(m_hMixer[dev],device2,MIXERCONTROL_CONTROLTYPE_MUTE,&volCtrl))
	//		{
	//			if(SetMuteValue(m_hMixer[dev],&volCtrl,(bool)vol))
	//			{
	//				rc=true;
	//				int i = device2 - MIXERLINE_COMPONENTTYPE_SRC_FIRST;
	//				char buffer[20];
	//				sprintf(buffer, "set mute = %d", i);
	//				MessageBoxA(NULL, buffer, buffer, MB_OK);
	//				//break;
	//			}
	//		}

	//		device2 += 1;
	//	}
	//}

	if (!OpenMixer(dev)) return false;

	if(GetVolumeControl(m_hMixer[dev],device,MIXERCONTROL_CONTROLTYPE_MUTE,&volCtrl))
		if(SetMuteValue(m_hMixer[dev],&volCtrl,(bool)vol))
			rc=true;

	//if (!rc)
	//	CloseMixer(dev);

	return rc;
}

//---------------------------------------------------------------------------

bool /*WINAPI */CMixer::GetMute(MixerDevice dev)//����豸�Ƿ���
{
	//dev =0,1,2 �ֱ��ʾ������������,MIDI ,LINE IN
	// retrun false ��ʾû�о���
	// retrun true ��ʾ����
	bool rc=false;
	MIXERCONTROL volCtrl;
	long device = GetComponentType(dev);

	if (!OpenMixer(dev)) return false;

	if(GetVolumeControl(m_hMixer[dev],device,MIXERCONTROL_CONTROLTYPE_MUTE,&volCtrl))
		rc=GetMuteValue(m_hMixer[dev],&volCtrl)==0?true:false;
	return rc;
}