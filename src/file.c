/*#############################################################################
 * �ļ�����file.c
 * ���ܣ�  ʵ����ָ������ļ��Ĳ���
 * modified by  PRTsinghua@hotmail.com
#############################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"


/* �������Щ�ӿ�ʵ����˽�еģ�����Ϊ�û���֪ */
typedef struct iFvsFile_t
{
	FILE	*pf;	/* �ļ�ָ�� */
} iFvsFile_t;


/******************************************************************************
  * ���ܣ�����һ���µ��ļ�����ֻ���ڴ���֮���ļ��������Ϊ�����������á�
  * ��������
  * ���أ�������ʧ�ܣ�����NULL�����򷵻��µĶ�������
******************************************************************************/
FvsFile_t FileCreate()
{
	iFvsFile_t* p = NULL;
	p = (iFvsFile_t*)malloc(sizeof(iFvsFile_t));
	if (p!=NULL)
		p->pf = NULL;
	return (FvsFile_t)p;
}


/******************************************************************************
  * ���ܣ��ƻ�һ���Ѿ����ڵ��ļ������ڻٻ�֮���ļ���������Ϊ�����������á�
  * ������file  ����ɾ�����ļ�����ָ��
  * ���أ��޷���ֵ
******************************************************************************/
void FileDestroy(FvsFile_t file)
{
	iFvsFile_t* p = NULL;
	if (file==NULL)
		return;
	/* �ر��ļ�������������� */
	(void)FileClose(file);
	p = file;
	free(p);
}


/******************************************************************************
  * ���ܣ���һ���µ��ļ���һ���ļ����Զ��򿪣�д�򿪣����߱�������
  * ������file    �ļ�����
  *       name    �����ļ�������
  *       flags   �򿪱�־
  * ���أ�������
******************************************************************************/
FvsError_t FileOpen(FvsFile_t file, const FvsString_t name, 
						const FvsFileOptions_t flags)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	char strFlags[10];
	int nflags = (int)flags;
	/* �ر��ļ�������Ѿ��� */
	(void)FileClose(p);

	strcpy(strFlags, "");
	if ( (nflags & FvsFileRead)!=0   &&
		 (nflags & FvsFileWrite)!=0 )
		strcat(strFlags, "rw");
	else
	{
		if ((nflags & FvsFileRead)!=0)
			strcat(strFlags, "r");
		if ((nflags & FvsFileWrite)!=0)
			strcat(strFlags, "w");
	}    
	strcat(strFlags, "b");
	if ((nflags & FvsFileCreate)!=0)
		strcat(strFlags, "+");

	p->pf = fopen(name, strFlags);

	if (FileIsOpen(file)==FvsTrue)
		return FvsOK;

	return FvsFailure;
}


/******************************************************************************
  * ���ܣ��ر�һ���ļ������ļ��ر�֮���ļ����ٿ��á�
  * ������file    �ļ�����
  * ���أ�������
******************************************************************************/
FvsError_t FileClose(FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	int nerr = -1;
	if (p->pf!=NULL)
	{
		nerr = fclose(p->pf);
		p->pf = NULL;
	}
	if (nerr==0)
		return FvsOK;
	return FvsFailure;
}


/******************************************************************************
  * ���ܣ�����һ���ļ��Ƿ��
  * ������file    �ļ�����
  * ���أ��ļ��򿪣��򷵻�true�����򷵻�false
******************************************************************************/
FvsBool_t FileIsOpen(const FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	return (p->pf!=NULL)?FvsTrue:FvsFalse;
}


/******************************************************************************
  * ���ܣ������Ƿ����ļ���β
  * ������file    �ļ�����
  * ���أ����˽�β������true�����򷵻�false
******************************************************************************/
FvsBool_t FileIsAtEOF(const FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	if (FileIsOpen(p)==FvsFalse)
		return FvsFalse;
	return (feof(p->pf)!=0)?FvsTrue:FvsFalse;
}


/******************************************************************************
  * ���ܣ��ύ���ļ������ĸ���
  * ������file    �ļ�����
  * ���أ�������
******************************************************************************/
FvsError_t FileCommit(FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	return (fflush(p->pf)==0)?FvsOK:FvsFailure;
}


/******************************************************************************
  * ���ܣ������ļ��Ŀ�ͷ
  * ������file    �ļ�����
  * ���أ�������
******************************************************************************/
FvsError_t FileSeekToBegin(FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	if (FileIsOpen(p)==FvsTrue)
	{
		if (fseek(p->pf, 0, SEEK_SET)!=0)
			return FvsFailure;
		return FvsOK;
	}
	return FvsFailure;
}


/******************************************************************************
  * ���ܣ������ļ��Ľ�β
  * ������file    �ļ�����
  * ���أ�������
******************************************************************************/
FvsError_t FileSeekToEnd(FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	if (FileIsOpen(p)==FvsTrue)
	{
		if (fseek(p->pf, 0, SEEK_END)!=0)
			return FvsFailure;
		return FvsOK;
	}
	return FvsFailure;
}


/******************************************************************************
  * ���ܣ��õ���ǰ���ļ�ָ��λ��
  * ������file    �ļ�����
  * ���أ���ǰ��ָ��λ��
******************************************************************************/
FvsUint_t FileGetPosition(FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	if (FileIsOpen(p)==FvsTrue)
		return (FvsUint_t)ftell(p->pf);
	return 0;
}


/******************************************************************************
  * ���ܣ������ļ���ָ��λ��
  * ������file     �ļ�����
  *       position ָ�����ļ�λ��
  * ���أ�������
******************************************************************************/
FvsError_t FileSeek(FvsFile_t file, const FvsUint_t position)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	if (FileIsOpen(p)==FvsTrue)
	{
		if (fseek(p->pf, (long int)position, SEEK_SET)!=0)
			return FvsFailure;
		return FvsOK;
	}
	return FvsFailure;
}


/******************************************************************************
  * ���ܣ����ļ��ж����ݣ�����ȡ���ֽ�����length��������ȡ�����ݱ�����ָ��data��
  * ������file    �ļ�����
  *       data    ָ��洢���ݵ�����
  *       length  Ҫ��ȡ���ֽ���
  * ���أ�ʵ�ʶ�ȡ���ֽ���
******************************************************************************/
FvsUint_t FileRead(FvsFile_t file, FvsPointer_t data, const FvsUint_t length)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	return (FvsUint_t)fread(data, (size_t)1, (size_t)length, p->pf);
}


/******************************************************************************
  * ���ܣ����ļ���д���ݣ���д���ֽ�����length������Ҫд������ݱ�����ָ��data��
  * ������file    �ļ�����
  *       data    ָ��洢���ݵ�����
  *       length  Ҫд����ֽ���
  * ���أ�ʵ��д����ֽ���
******************************************************************************/
FvsUint_t FileWrite(FvsFile_t file, const FvsPointer_t data, const FvsUint_t length)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	return (FvsUint_t)fwrite(data, (size_t)1, (size_t)length, p->pf);
}


/******************************************************************************
  * ���ܣ����ļ��еõ�һ���ֽ�
  * ������file    �ļ�����
  * ���أ���ȡ���ֽ�
******************************************************************************/
FvsByte_t FileGetByte(FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	return (FvsByte_t)fgetc(p->pf);
}


/******************************************************************************
  * ���ܣ����ļ��ж�ȡһ����
  * ������file    �ļ�����
  * ���أ���ȡ����
******************************************************************************/
FvsWord_t FileGetWord(FvsFile_t file)
{
	iFvsFile_t* p = (iFvsFile_t*)file;
	FvsWord_t w = (FvsWord_t)fgetc(p->pf);
	return (w<<8)+fgetc(p->pf);
}

