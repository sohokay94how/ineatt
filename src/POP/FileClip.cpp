// FileClip.cpp: implementation of the FileClip class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "������а�.h"
#include "FileClip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FileClip::FileClip()
{

}

FileClip::~FileClip()
{

}

void FileClip::Set_hWnd(HWND wnd)
{

	////////��ʼ��/////////////////////////////
     hWnd=wnd;
	 count=0;
     fileClip.dataLength=0;
	 full=false;
	 show=false;
	 for(int i=0;i<5;i++){
	     fileData[i].time="";
		 fileData[i].fileclass="�ļ�";
	 }
	////////////////////////////////////////
}



void FileClip::ReadData()
{

     if(OpenClipboard(hWnd)==false){ //�򿪼��а�
	    return;
	}
         HDROP hClip;

	     BYTE *pBuf=NULL;         //���а�����				
		 BYTE *buf=NULL;          //��ǰ����
		int format=0;           //��ʽ
		unsigned int size=0;            //���ݳ���
		int sum;              //�ļ�����
        CTime time=CTime::GetCurrentTime();
		CString str,str1;         //��ʾ������
   	 			 
///////////////////////////ö����������////////////////////////
		while(1)
		{
			format++;
			if(format>=400){
			   CloseClipboard();       //�رռ��а� 
				return ;
			}
			if(IsClipboardFormatAvailable(format)){
				break;
			} 
				 
		}
//////////////////�Ǻ�������//////////////////////////////////////////////////////
        if(format==CF_HDROP){           //�ļ�
			   HDROP hDrop;
			   BYTE* buf=NULL;
			   unsigned int j=0;
			   int sum=0;           //����
			   unsigned int dataLength=0;     //����
               hDrop=(HDROP__ *)GetClipboardData(format);      //ȡ������
			    GlobalUnlock(hDrop);               //����
			   sum=DragQueryFile(hDrop,0xFFFFFFFF,(char *)buf,0);   //�õ��ļ�����
			   int i=0;
			  for(i=0;i<sum;i++){
			          j=DragQueryFile(hDrop,i,NULL,0)+1;       //�õ���ǰ�ļ�������
                     
					  dataLength+=j;  //�õ���ǰ�ļ���������
			   }
               pBuf=(BYTE *)malloc(++(dataLength));    //�����µĻ���
			   memset(pBuf,0,dataLength);
			  buf= pBuf;
			   for(i=0;i<sum;i++){
				      j=DragQueryFile(hDrop,i,NULL,0)+1;       //�õ���ǰ�ļ�������
					  DragQueryFile(hDrop,i,(char *)buf,j);         //�õ��ļ���
					  //buf[j]=NULL;                    //���һ���ַ�Ϊ��
					  //str1.Format("%s",buf);
					 
					  *(buf+j-1)='\0';      //��ʽΪ:"·����\0�ļ�1\0�ļ�2\0" 
					   str+=PathToName(buf);//str+(str1+"\r\n");
					  buf=buf+j;
			   }
///////////////////////////�ж������Ƿ�һ��//////////////////////////////////////////////////
               if(fileClip.dataLength!=dataLength){        //�͵�ǰ���Ȳ�һ��
			         fileClip.data=pBuf;
					 fileClip.dataLength=dataLength;
					 fileClip.sum=sum;
                     fileClip.fileclass="�ļ�";
					 fileClip.time.Format("%s",time.Format("%H:%M:%S"));
					 fileClip.str=str;
                     WriteData(&fileClip);   //д������
			   }else{                         //�͵�ǰ����һ��
				   if(!(ByteCmp(fileClip.data,pBuf,dataLength))){    //�����ݲ�һ��
				     fileClip.data=pBuf;
					 fileClip.dataLength=dataLength;
					 fileClip.sum=sum;
                     fileClip.fileclass="�ļ�";
					 fileClip.time.Format("%s",time.Format("%H:%M:%S"));
					 fileClip.str=str;
					 WriteData(&fileClip);   //д������
				   }
			   }
			   
			    /*
			   buf=(unsigned char *)hDrop;
			   int ii=strlen((char *)buf);
               fileClip.str.Format("%s",buf+sizeof(DROPFILES));
			   */
			  
			   //fileClip.sum=DragQueryFile(hDrop,0xFFFFFFFF,(char *)buf,0)+1;
                //pBuf=(BYTE *)malloc(size);    //�����µĻ���
               //DragQueryFile(fileClip.hClip,0,(char*)pBuf,size);
			    //memcpy(pBuf,fileClip.hClip,size);
        }
		CloseClipboard();       //�رռ��а�  
}

void FileClip::Put(int i)
{
     if(OpenClipboard(hWnd)){
		    HANDLE hClip;
	       DROPFILES  dFiles;
            BYTE *pBuf;
           
	      EmptyClipboard();
          hClip=GlobalAlloc(GMEM_SHARE|GMEM_MOVEABLE|GMEM_ZEROINIT,sizeof(DROPFILES)+(fileData[i].dataLength));            //�����ƶ���
          
          pBuf=(BYTE*)GlobalLock(hClip);
		  tagPOINT pt;
		  pt.x=0; 
		  pt.y=0;
		  dFiles.pt=pt;
		  dFiles.fNC=false;
          dFiles.pFiles=sizeof(DROPFILES);
		  dFiles.fWide=false;
	      memcpy((char *)pBuf,((char *)&dFiles),sizeof(DROPFILES));
          BYTE *buf;
		  buf=pBuf+sizeof(DROPFILES);
		  //str+='\0';
	       //BYTE str[25]="d:\\123.gif\0d:\\lang.lang";
		   //fileData[i].data=str;
          memcpy(buf,fileData[i].data,fileData[i].dataLength);	
	      GlobalUnlock(hClip);         //����
          
	      SetClipboardData(CF_HDROP,hClip);        //��������
          CloseClipboard();                 //�ر�  
		}

}

bool FileClip::ByteCmp(BYTE *left, BYTE *right,unsigned size)            //�����ַ����Ƿ�һ��
{
	  for(unsigned long i=0;i<size;i++){
	       if((BYTE)left[i]!=(BYTE)right[i]) 
		    	 return false;         //��һ��
		}
     return true;
}

void FileClip::WriteData(FileData *fd)     //д������
{
	if(count>0||full==true){            //fileData���Ƿ���һ��������
	    Data_YN(fd);
	}

    if(!full){
	    fileData[count]=*fd; 
	}else{        
		free(fileData[0].data);       //�ͷ�
		for(int i=0;i<4;i++){
		       fileData[i]=fileData[i+1];
		}
		fileData[4]=*fd;	
	}
    
	count++;
	if(count==5){
	   count=0;
	   full=true;
	}
	show=true;

}

bool FileClip::Data_YN(FileData *fd)          //fileData���Ƿ���һ��������
{
    int count2=count;
    if(full) count2=5;
	for(int i=0;i<count2;i++){
		if(fd->dataLength==fileData[i].dataLength){  //����һ��
			if(ByteCmp(fd->data,fileData[i].data,fd->dataLength)){  //����һ��
				  free(fileData[i].data);   //�ͷ�
				  for(int j=i;j<count2-1;j++){
						  fileData[j]=fileData[j+1];
				  }
				  count--;     //������һ
				  if(full){    //�������
					  full=false;
					  count=4;
				  }
			}
            
		}
	}
    
    count<0?count=4:count;
	 if(count==5){
		full=true;
	}
	return true;
}


CString FileClip::PathToName(BYTE *b)                 //ȡ���ļ���
{    CString name;
    int size=strlen((char *)b);
	for(int i=size-1;i>0;i--){        //�ҵ�'\'
		if(b[i]=='\\'){
		     name.Format("%s",b+i+1);
			 break;
		}
	}
	name+=",";
    return name;
}
