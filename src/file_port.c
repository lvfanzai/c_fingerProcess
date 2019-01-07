/*#############################################################################
 * �ļ�����import.c
 * ���ܣ�  һЩ������ͼ�����
 * modified by  PRTsinghua@hotmail.com
#############################################################################*/


#include "file_port.h"

#include <stdio.h>
#include <stdlib.h>

/* ָ��ͼ��ṹ��256���Ҷ�ͼ */
typedef struct iFvsImage_t
{
    FvsByte_t       *pimg;         /* 8-bitͼ������ */    
    FvsInt_t        w;             /* ���          */
    FvsInt_t        h;             /* �߶�          */
    FvsInt_t        pitch;         /* ��б��        */
    FvsImageFlag_t  flags;         /* ���          */
} iFvsImage_t;

FvsByte_t bmpheader[1078] = {0};

/******************************************************************************
  * ���ܣ����ļ��м���ָ��ͼ��
  * ������image       ָ��ͼ��
  *       filename    �ļ���
  * ���أ�������
******************************************************************************/
FvsError_t FvsImageImport(FvsImage_t image, const FvsString_t filename)
{    
    FvsError_t ret = FvsOK;
	iFvsImage_t* img = (iFvsImage_t*)image;

	img->pimg = (FvsByte_t*)malloc(W*H*sizeof(FvsByte_t));
	img->w = W;
	img->h = H;
	img->pitch = W;

    FILE *fpIn;
    if ((fpIn = fopen(filename,"rb"))==0) {
        printf("Can not open file %s\n", filename);
        return -1;
    }

    //2.����H*W�ֽڵ�����
    fread(bmpheader,1, 1078, fpIn);
    fseek(fpIn, 1078, 0);//
    fread(img->pimg, 1, H*W, fpIn);
    return ret;
}

/******************************************************************************
  * ���ܣ���һ��ָ��ͼ�������һ���ļ����ļ��ĸ�ʽ���ļ�����չ������
  * ������filename  ��Ҫ����ͼ����ļ���
  *       image     ��Ҫ������ͼ��
  * ���أ��������
******************************************************************************/
FvsError_t FvsImageExport(const FvsImage_t image, const FvsString_t filename)
{
	FvsError_t ret = FvsOK;

    FvsByte_t*		buffer;
    buffer	= ImageGetBuffer(image);

    //5.���洦��֮���ͼ
    FILE *fpOutBmp;
    if((fpOutBmp = fopen(filename,"wb"))==0)
    {
        printf("Can not open output file %s\n", filename);
        return -1;
    }

    fwrite(bmpheader, 1, 1078, fpOutBmp);
    fseek(fpOutBmp, 1078, 0);//
    fwrite(buffer,1,H*W,fpOutBmp);
    fclose(fpOutBmp);  
	return ret;
}


