/*#############################################################################
 * 文件名：file_port.h
 * 功能：  加载图像
 * modified by  PRTsinghua@hotmail.com
#############################################################################*/

#if !defined FVS__IMPORT_HEADER__INCLUDED__
#define FVS__IMPORT_HEADER__INCLUDED__

#include "file.h"
#include "image.h"


/******************************************************************************
  * 功能：从文件中加载指纹图像
  * 参数：image       指纹图像
  *       filename    文件名
  * 返回：错误编号
******************************************************************************/
FvsError_t FvsImageImport(FvsImage_t image, const FvsString_t filename);

/******************************************************************************
  * 功能：将一个指纹图像输出到一个文件，文件的格式由文件的扩展名决定
  * 参数：filename  将要保存图像的文件名
  *       image     将要导出的图像
  * 返回：错误代码
******************************************************************************/
FvsError_t FvsImageExport(const FvsImage_t image, const FvsString_t filename);

#endif /* FVS__IMPORT_HEADER__INCLUDED__ */

