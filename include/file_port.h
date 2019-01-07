/*#############################################################################
 * �ļ�����file_port.h
 * ���ܣ�  ����ͼ��
 * modified by  PRTsinghua@hotmail.com
#############################################################################*/

#if !defined FVS__IMPORT_HEADER__INCLUDED__
#define FVS__IMPORT_HEADER__INCLUDED__

#include "file.h"
#include "image.h"


/******************************************************************************
  * ���ܣ����ļ��м���ָ��ͼ��
  * ������image       ָ��ͼ��
  *       filename    �ļ���
  * ���أ�������
******************************************************************************/
FvsError_t FvsImageImport(FvsImage_t image, const FvsString_t filename);

/******************************************************************************
  * ���ܣ���һ��ָ��ͼ�������һ���ļ����ļ��ĸ�ʽ���ļ�����չ������
  * ������filename  ��Ҫ����ͼ����ļ���
  *       image     ��Ҫ������ͼ��
  * ���أ��������
******************************************************************************/
FvsError_t FvsImageExport(const FvsImage_t image, const FvsString_t filename);

#endif /* FVS__IMPORT_HEADER__INCLUDED__ */

