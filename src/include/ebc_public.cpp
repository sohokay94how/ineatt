#include "StdAfx.h"
#include "ebc_public.h"
#include "md5.h"

std::wstring theFontFamily = L"Arial";	// Times New Roman
tstring theFontFace = "Arial";

namespace libEbc
{
long GetFileSize(const char* lpszFile)
{
	long result = 0;
	FILE * f = fopen(lpszFile, "rb");
	if (f != NULL)
	{
#ifdef WIN32
		_fseeki64(f, 0, SEEK_END);
		result = _ftelli64(f);
#else
		fseeko(f, 0, SEEK_END);
		result = ftello(f);
#endif
		fclose(f);
	}
	return result;
}

tstring GetFileName(const tstring & sPathName)
{
	tstring sFileName(sPathName);
	int find = sPathName.rfind("\\");
	if (find < 0)
		find = sPathName.rfind("/");
	if (find > 0)
		sFileName = sPathName.substr(find+1);
	return sFileName;
}
const unsigned int theOneMB = 1024*1024;
bool GetFileMd5(const char* sFilePath,mycp::bigint& pOutFileSize,tstring& pOutFileMd5)
{
	FILE * f = fopen(sFilePath, "rb");
	if (f == NULL)
	{
		return false;
	}
#ifdef WIN32
	_fseeki64(f, 0, SEEK_END);
	pOutFileSize = _ftelli64(f);
	_fseeki64(f, 0, SEEK_SET);
#else
	fseeko(f, 0, SEEK_END);
	pOutFileSize = ftello(f);
	fseeko(f, 0, SEEK_SET);
#endif
	// ��ȡ�ļ�MD5
	entboost::MD5 md5;
	const unsigned int nPackSize = pOutFileSize>theOneMB?theOneMB:pOutFileSize;
	unsigned char * lpszBuffer = new unsigned char[nPackSize+1];
	while (true)
	{
		size_t nReadSize = fread(lpszBuffer,1,nPackSize,f);
		if (nReadSize==0)
			break;
		md5.update(lpszBuffer, nReadSize);
	}
	fclose(f);
	md5.finalize();
	pOutFileMd5 = md5.hex_digest();
	delete[] lpszBuffer;
	return true;
}
void GetFileExt(const tstring & sFileName, tstring & sOutName, tstring & sOutExt)
{
	int find = sFileName.rfind(".");
	if (find > 0)
	{
		sOutName = sFileName.substr(0, find);
		sOutExt = sFileName.substr(find+1);
	}else
	{
		sOutName = sFileName;
	}
}


int   GetCodecClsid(const   WCHAR*   format,   CLSID*   pClsid)
{
	UINT     num   =   0;                     //   number   of   image   encoders
	UINT     size   =   0;                   //   size   of   the   image   encoder   array   in   bytes

	Gdiplus::ImageCodecInfo*   pImageCodecInfo   =   NULL;

	Gdiplus::GetImageEncodersSize(&num,   &size);
	if(size   ==   0)
		return   -1;     //   Failure

	pImageCodecInfo   =   (Gdiplus::ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo   ==   NULL)
		return   -1;     //   Failure

	Gdiplus::GetImageEncoders(num,   size,   pImageCodecInfo);
	for(UINT   j   =   0;   j   <   num;   ++j)
	{
		if(   wcscmp(pImageCodecInfo[j].MimeType,   format)   ==   0   )
		{
			*pClsid   =   pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return   j;     //   Success
		}        
	}   //   for
	free(pImageCodecInfo);
	return   -1;     //   Failure

}   //   GetCodecClsid
int bmp_2_jpg(const WCHAR * sBmpFile, const WCHAR * sJpgFile, long quality)
{
	CLSID                           codecClsid;
	Gdiplus::EncoderParameters		encoderParameters;
	Gdiplus::Status					stat;

	//   Get   an   image   from   the   disk.
	Gdiplus::Image   image(sBmpFile);

	//   Get   the   CLSID   of   the   JPEG   codec.
	GetCodecClsid(L"image/jpeg",   &codecClsid);

	//   Before   we   call   Image::Save,   we   must   initialize   an
	//   EncoderParameters   object.   The   EncoderParameters   object
	//   has   an   array   of   EncoderParameter   objects.   In   this
	//   case,   there   is   only   one   EncoderParameter   object   in   the   array.
	//   The   one   EncoderParameter   object   has   an   array   of   values.
	//   In   this   case,   there   is   only   one   value   (of   type   LONG)
	//   in   the   array.   We   will   set   this   value   to   0,   50,   and   100.

	encoderParameters.Count   =   1;
	encoderParameters.Parameter[0].Guid   =   Gdiplus::EncoderQuality;
	encoderParameters.Parameter[0].Type   =   Gdiplus::EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues   =   1;

	//   Save   the   image   as   a   JPEG   with   quality   level   0.
	encoderParameters.Parameter[0].Value   =   &quality;
	stat   =   image.Save(sJpgFile,   &codecClsid,   &encoderParameters);
	return stat == Gdiplus::Ok ? 0 : -1;
	/*
	if(stat   == Gdiplus::Ok)
		wprintf(L"%s   saved   successfully.\n ",   L"Shapes001.jpg ");
	else
		wprintf(L"%d     Attempt   to   save   %s   failed.\n ",   stat,   L"Shapes001.jpg ");

	//   Save   the   image   as   a   JPEG   with   quality   level   50.
	quality   =   50;
	encoderParameters.Parameter[0].Value   =   &quality;
	stat   =   image.Save(L"d:\\Shapes050.jpg ",   &codecClsid,   &encoderParameters);

	if(stat   ==   Gdiplus::Ok)
		wprintf(L"%s   saved   successfully.\n ",   L"Shapes050.jpg ");
	else
		wprintf(L"%d     Attempt   to   save   %s   failed.\n ",   stat,   L"Shapes050.jpg ");

	//   Save   the   image   as   a   JPEG   with   quality   level   100.
	quality   =   100;
	encoderParameters.Parameter[0].Value   =   &quality;
	stat   =   image.Save(L"d:\\Shapes100.jpg ",   &codecClsid,   &encoderParameters);

	if(stat   ==   Gdiplus::Ok)
		wprintf(L"%s   saved   successfully.\n ",   L"Shapes100.jpg ");
	else
		wprintf(L"%d     Attempt   to   save   %s   failed.\n ",   stat,   L"Shapes100.jpg ");
*/
	return   0; 
}
int bmp_2_png(const WCHAR * sBmpFile, const WCHAR * sJpgFile, long quality)
{
	CLSID                           codecClsid;
	Gdiplus::EncoderParameters		encoderParameters;
	Gdiplus::Status					stat;

	//   Get   an   image   from   the   disk.
	Gdiplus::Image   image(sBmpFile);

	//   Get   the   CLSID   of   the   JPEG   codec.
	GetCodecClsid(L"image/png",   &codecClsid);

	//   Before   we   call   Image::Save,   we   must   initialize   an
	//   EncoderParameters   object.   The   EncoderParameters   object
	//   has   an   array   of   EncoderParameter   objects.   In   this
	//   case,   there   is   only   one   EncoderParameter   object   in   the   array.
	//   The   one   EncoderParameter   object   has   an   array   of   values.
	//   In   this   case,   there   is   only   one   value   (of   type   LONG)
	//   in   the   array.   We   will   set   this   value   to   0,   50,   and   100.

	encoderParameters.Count   =   1;
	encoderParameters.Parameter[0].Guid   =   Gdiplus::EncoderQuality;
	encoderParameters.Parameter[0].Type   =   Gdiplus::EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues   =   1;

	//   Save   the   image   as   a   JPEG   with   quality   level   0.
	encoderParameters.Parameter[0].Value   =   &quality;
	stat   =   image.Save(sJpgFile,   &codecClsid,   &encoderParameters);
	return stat == Gdiplus::Ok ? 0 : -1;
	return   0; 
}
bool ChangeTime(const char* sTimeString, time_t& pOutTime, int* pOutMS)
{
	int nMS = 0;
	tm pTm;
	memset(&pTm,0,sizeof(pTm));
	int nRet = ::sscanf(sTimeString,"%d-%d-%d %d:%d:%d.%d",&pTm.tm_year,&pTm.tm_mon,&pTm.tm_mday,&pTm.tm_hour,&pTm.tm_min,&pTm.tm_sec,&nMS);
	if (nRet != EOF)
	{
		pTm.tm_year -= 1900;
		pTm.tm_mon -= 1;
		pOutTime = mktime(&pTm);
		if (pOutMS != NULL)
			*pOutMS = nMS;
		return true;
	}
	return false;
}

tstring str_convert(const char * strSource, int sourceCodepage, int targetCodepage)
{
	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, strSource, -1, NULL, 0);
	if (unicodeLen <= 0) return "";

	wchar_t * pUnicode = new wchar_t[unicodeLen];
	memset(pUnicode,0,(unicodeLen)*sizeof(wchar_t));

	MultiByteToWideChar(sourceCodepage, 0, strSource, -1, (wchar_t*)pUnicode, unicodeLen);

	char * pTargetData = 0;
	int targetLen = WideCharToMultiByte(targetCodepage, 0, (wchar_t*)pUnicode, -1, (char*)pTargetData, 0, NULL, NULL);
	if (targetLen <= 0)
	{
		delete[] pUnicode;
		return "";
	}

	pTargetData = new char[targetLen+1];
	memset(pTargetData, 0, targetLen);
	pTargetData[targetLen] = '0';

	WideCharToMultiByte(targetCodepage, 0, (wchar_t*)pUnicode, -1, (char *)pTargetData, targetLen, NULL, NULL);

	tstring result(pTargetData);
	//tstring result(pTargetData,targetLen);
	delete[] pUnicode;
	delete[] pTargetData;
	return   result;
}
tstring ACP2UTF8(const char* sString)
{
	return str_convert(sString,CP_ACP,CP_UTF8);
}
tstring UTF82ACP(const char* sString)
{
	return str_convert(sString,CP_UTF8,CP_ACP);
}
const tstring & replace(tstring & strSource, const tstring & strFind, const tstring &strReplace)
{
	std::string::size_type pos=0;
	std::string::size_type findlen=strFind.size();
	std::string::size_type replacelen=strReplace.size();
	while ((pos=strSource.find(strFind, pos)) != std::string::npos)
	{
		strSource.replace(pos, findlen, strReplace);
		pos += replacelen;
	}
	return strSource;
}

BOOL ImageFromIDResource(UINT nID, LPCTSTR sTR, Image * & pImg)
{
	pImg = NULL;
	//HINSTANCE hInst = GetModuleHandle("test.dll");
	HINSTANCE hInst = AfxGetResourceHandle();
    HRSRC hRsrc = ::FindResource (hInst,MAKEINTRESOURCE(nID),sTR); // type
    if (!hRsrc)
        return FALSE;
    // load resource into memory
    DWORD len = SizeofResource(hInst, hRsrc);
    BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
    if (!lpRsrc)
        return FALSE;
    // Allocate global memory on which to create stream
    HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len);
    BYTE* pmem = (BYTE*)GlobalLock(m_hMem);
    memcpy(pmem,lpRsrc,len);
    IStream* pstm;
    if (CreateStreamOnHGlobal(m_hMem,TRUE,&pstm)==S_OK)	// TRUE:���Զ��ͷ�
	{
		// load from stream
		pImg = Gdiplus::Image::FromStream(pstm,FALSE);
		// free/release stuff
		pstm->Release();
	}else
	{
		GlobalUnlock(m_hMem);
		GlobalFree(m_hMem);
	}
	// **�����ͷţ�����ᵼ��ͼƬ�ҶȻ�ʧ�ܣ�
    //GlobalUnlock(m_hMem);
    //GlobalFree(m_hMem);
    FreeResource(lpRsrc);
    return TRUE;
}
// ���ڴ����ͼƬ��ʧ�ܷ���NULL
Gdiplus::Image* LoadImageFromMemory(const void* memory, DWORD size)
{
    Gdiplus::Image* pImage = NULL;
    IStream* stream = NULL;
    if (CreateStreamOnHGlobal(NULL, TRUE, &stream) == S_OK)
    {
        ULARGE_INTEGER uli;
        uli.QuadPart = size;
        stream->SetSize(uli);
        if (stream->Write(memory, size, NULL) == S_OK)
					pImage = new Gdiplus::Image(stream);
        stream->Release();
    }
    return pImage;
}
Gdiplus::Bitmap* LoadBitmapFromMemory(const void* memory, DWORD size)
{
    Gdiplus::Bitmap* pImage = NULL;
    IStream* stream = NULL;
    if (CreateStreamOnHGlobal(NULL, TRUE, &stream) == S_OK)
    {
        ULARGE_INTEGER uli;
        uli.QuadPart = size;
        stream->SetSize(uli);
        if (stream->Write(memory, size, NULL) == S_OK)
					pImage = new Gdiplus::Bitmap(stream);
        stream->Release();
    }
    return pImage;
}
Gdiplus::Image * LoadImageFromFile(const TCHAR* file_name)
{
    Image* pImage = NULL;
    HANDLE file_handle = CreateFile(file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle != INVALID_HANDLE_VALUE)
    {
        DWORD temp = 0;
				DWORD file_size = ::GetFileSize(file_handle, &temp);
        if (file_size && !temp)  // ���������4G���ļ�
        {
            // ��ͼƬ�ļ������ڴ���ٴ��ڴ洴��Bitmap
            unsigned char* buffer = new unsigned char[file_size];
            if (ReadFile(file_handle, buffer, file_size, &temp, NULL))
                pImage = LoadImageFromMemory(buffer, temp);
            delete [] buffer;
        }
        CloseHandle(file_handle);
    }
    return pImage;
}
Gdiplus::Bitmap * LoadBitmapFromFile(const TCHAR* file_name)
{
	Gdiplus::Bitmap* pImage = NULL;
    HANDLE file_handle = CreateFile(file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle != INVALID_HANDLE_VALUE)
    {
        DWORD temp = 0;
				DWORD file_size = ::GetFileSize(file_handle, &temp);
        if (file_size && !temp)  // ���������4G���ļ�
        {
            // ��ͼƬ�ļ������ڴ���ٴ��ڴ洴��Bitmap
            unsigned char* buffer = new unsigned char[file_size];
            if (ReadFile(file_handle, buffer, file_size, &temp, NULL))
                pImage = LoadBitmapFromMemory(buffer, temp);
            delete [] buffer;
        }
        CloseHandle(file_handle);
    }
    return pImage;
}
int ParseString(const char * lpszString, const char * lpszInterval, std::vector<tstring> & pOut)
{
	const tstring sIn(lpszString);
	const size_t nInLen = sIn.size();
	const size_t nIntervalLen = strlen(lpszInterval);
	pOut.clear();
	std::string::size_type nFindBegin = 0;
	while (nFindBegin<nInLen)
	{
		std::string::size_type find = sIn.find(lpszInterval,nFindBegin);
		if (find == std::string::npos)
		{
			pOut.push_back(sIn.substr(nFindBegin));
			break;
		}
		if (find==nFindBegin)
		{
			pOut.push_back("");	// ��
		}else
		{
			pOut.push_back(sIn.substr(nFindBegin, (find-nFindBegin)));
		}
		nFindBegin = find+nIntervalLen;
	}
	return (int)pOut.size();
	//tstring sIn(lpszString);
	//pOut.clear();
	//while (!sIn.empty())
	//{
	//	std::string::size_type find = sIn.find(lpszInterval);
	//	if (find == std::string::npos)
	//	{
	//		pOut.push_back(sIn);
	//		break;
	//	}
	//	if (find==0)
	//		pOut.push_back("");	// ��
	//	else
	//		pOut.push_back(sIn.substr(0, find));
	//	sIn = sIn.substr(find+strlen(lpszInterval));
	//}
	//return (int)pOut.size();
}
bool IsFullNumber(const char* pString, size_t nLen)
{
	for (size_t i=0;i<nLen; i++)
	{
		const char pChar = pString[i];
		if (pChar<'0' || pChar>'9')
			return false;
	}
	return true;
}
//typedef char      s8;    //�з���8λ����  
//typedef short     s16;   //�з���16λ����  
//typedef int       s32;   //�з���32λ����  
//struct WAVE_TAG  
//{  
//	s8     riff[4];            //"RIFF",��Դ�����ļ���־  
//	s32    fsize;              //�ļ���С(���¸���ַ��ʼ���ļ�β�����ֽ���)  
//	s8     wave[4];            //"WAVE",�ļ���־  
//};  
//struct WAVE_FMT  
//{  
//	s8     fmt[4];             //"fmt ",���θ�ʽ��־   
//	s32    chunsize;           //�ļ��ڲ���ʽ��Ϣ��С  
//	s16    wformattag;         //��Ƶ���ݱ��뷽ʽ 1PCM  
//	s16    wchanles;           //������ 1,2  
//	s32    dwsamplespersec;    //������ 441000  
//	s32    dwavgbytespersec;   //�������ݴ������ʣ�ÿ��ƽ���ֽ�����  
//	s16    wblockalign;        //���ݵĵ����������ֽڼ��㣩  
//	s16    wbitspersample;     //��������λ��  
//};  
//struct WAVE_DAT  
//{  
//	s8     data[4];            //"data",���ݱ�־��  
//	s32    datasize;           //���������ܳ���   
//};  
//struct WAVE_HEAD  
//{  
//	WAVE_TAG   WaveTag;   
//	WAVE_FMT   WaveFmt;  
//	WAVE_DAT   WaveDat;  
//}wavhead;  

typedef struct eb_waveformat_tag {
    unsigned short	wFormatTag;        /* format type */
    unsigned short	nChannels;         /* number of channels (i.e. mono, stereo, etc.) */
    unsigned long	nSamplesPerSec;    /* sample rate */
    unsigned long	nAvgBytesPerSec;   /* for buffer estimation */
    unsigned short	nBlockAlign;       /* block size of data */
} EB_WAVEFORMAT;
typedef struct eb_pcmwaveformat_tag {
    EB_WAVEFORMAT	wf;
    unsigned short	wBitsPerSample;
} EB_PCMWAVEFORMAT;

int GetWaveTimeLength(const char* lpszWavFilePath)
{
	FILE * f = fopen(lpszWavFilePath,"rb");
	if (f==NULL)
		return -1;

	char style[4];//����һ�����ֽڵ����ݣ���������ļ������ͣ�
	fseek(f,8,SEEK_SET);
	fread(style,1,4,f);
	if(style[0]!='W'||style[1]!='A'||style[2]!='V'||style[3]!='E')//�жϸ��ļ��Ƿ�Ϊ"WAVE"�ļ���ʽ
	{
		fclose(f);
		return -2;
	}

	// WAV��ʽ�ļ���ռ������KB) = ��ȡ��Ƶ�� X ����λ�� X ������ X ʱ�� / 8 (�ֽ�= 8bit) ��ÿһ����WAV��ʽ����Ƶ�ļ��Ĵ�СΪ10MB�����С����������С�������ȵı仯���仯��

	EB_PCMWAVEFORMAT format; //����PCMWAVEFORMAT�ṹ���������ж�WAVE�ļ���ʽ��
	fseek(f,20,SEEK_SET);
	fread((char*)&format,1,sizeof(EB_PCMWAVEFORMAT),f);//��ȡ�ýṹ�����ݣ�
	if (format.wf.nAvgBytesPerSec==0)
	{
		fclose(f);
		return -3;
	}

	// ��ȡWAVE�ļ� data ���ݱ�ʶ
	fseek(f,36,SEEK_SET);
	fread(style,1,4,f);
	if(style[0]!='d'||style[1]!='a'||style[2]!='t'||style[3]!='a')	//�ж��Ƿ��׼data�ļ��������ʹ��44�ֽ��ļ�ͷ������ʹ��46�ֽ��ļ�ͷ
		fseek(f,42,SEEK_SET);
	//fseek(f,40,SEEK_SET);
	////��ȡWAVE�ļ����������ݵĴ�С��
	unsigned long size = 0;
	fread((char*)&size,1,4,f);

	//�����ļ�ʱ��
	const int timeLength = size/format.wf.nAvgBytesPerSec;
	fclose(f);
	return timeLength;
}

inline unsigned char toHex(const unsigned char &x)
{
	return x > 9 ? x -10 + 'A': x + '0';
}
tstring URLEncode(const char *sIn)
{
	const size_t nLen = strlen(sIn);
	unsigned char buf[4];
	tstring sOut;
	for( size_t ix = 0; ix < nLen; ix++ )
	{
		memset( buf, 0, 4 );
		if( isalnum( (unsigned char)sIn[ix] ) )
		{      
			buf[0] = sIn[ix];
		}
		else
		{
			buf[0] = '%';
			buf[1] = toHex( (unsigned char)sIn[ix] >> 4 );
			buf[2] = toHex( (unsigned char)sIn[ix] % 16);
		}
		sOut += (char *)buf;
	}
	return sOut;
}
inline unsigned char fromHex(const unsigned char &x)
{
	return isdigit(x) ? x-'0' : x-'A'+10;
}
tstring URLDecode(const char *sIn, bool bTranPlusSign)
{
	tstring sOut;
	const size_t nLen = strlen(sIn);
	for( size_t ix = 0; ix < nLen; ix++ )
	{
		unsigned char ch = 0;
		if(sIn[ix]=='%')
		{
			ch = (fromHex(sIn[ix+1])<<4);
			ch |= fromHex(sIn[ix+2]);
			ix += 2;
		}
		else if(bTranPlusSign && sIn[ix] == '+')
		{
			ch = ' ';
		}
		else
		{
			ch = sIn[ix];
		}
		sOut += (char)ch;
	}
	return sOut;
}
tstring GetHostIp(const char * lpszHostName,const char* lpszDefault)
{
	try
	{
		struct hostent *host_entry;
		//struct sockaddr_in addr;
		/* ��Ҫ������������������ */
		host_entry=gethostbyname(lpszHostName);
		//printf("%s\n", dn_or_ip);
		if (host_entry!=0)
		{
			//printf("����IP��ַ: ");
			char lpszIpAddress[50];
			sprintf(lpszIpAddress, "%d.%d.%d.%d",
				(host_entry->h_addr_list[0][0]&0x00ff),
				(host_entry->h_addr_list[0][1]&0x00ff),
				(host_entry->h_addr_list[0][2]&0x00ff),
				(host_entry->h_addr_list[0][3]&0x00ff));
			return lpszIpAddress;
		}
	}catch(std::exception&)
	{
	}catch(...)
	{}
	return lpszDefault;
}
};
