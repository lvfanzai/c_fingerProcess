/*#############################################################################
 * 文件名：import.c
 * 功能：  一些基本的图像操作
 * modified by  PRTsinghua@hotmail.com
#############################################################################*/


#include "file_port.h"

#include <stdio.h>
#include <stdlib.h>

/* 指纹图像结构。256级灰度图 */
typedef struct iFvsImage_t
{
    FvsByte_t       *pimg;         /* 8-bit图像数组 */    
    FvsInt_t        w;             /* 宽度          */
    FvsInt_t        h;             /* 高度          */
    FvsInt_t        pitch;         /* 倾斜度        */
    FvsImageFlag_t  flags;         /* 标记          */
} iFvsImage_t;

FvsByte_t bmpheader[1078] = {0};

/******************************************************************************
  * 功能：从文件中加载指纹图像
  * 参数：image       指纹图像
  *       filename    文件名
  * 返回：错误编号
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

    //2.读入H*W字节的数据
    fread(bmpheader,1, 1078, fpIn);
    fseek(fpIn, 1078, 0);//
    fread(img->pimg, 1, H*W, fpIn);
    return ret;
}

/******************************************************************************
  * 功能：将一个指纹图像输出到一个文件，文件的格式由文件的扩展名决定
  * 参数：filename  将要保存图像的文件名
  *       image     将要导出的图像
  * 返回：错误代码
******************************************************************************/
FvsError_t FvsImageExport(const FvsImage_t image, const FvsString_t filename)
{
	FvsError_t ret = FvsOK;

    FvsByte_t*		buffer;
    buffer	= ImageGetBuffer(image);

    //5.保存处理之后的图
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


