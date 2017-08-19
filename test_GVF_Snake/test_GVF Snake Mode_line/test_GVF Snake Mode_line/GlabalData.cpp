/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/
#include "GlobalData.h"
#include "cv.h"

char* g_strImageFileName;
IplImage* g_pSrcImage;
CvSize g_ImageSize;
CvMat* g_u;
CvMat* g_v;
IplImage* g_TmpEdge;
IplImage* g_edge;
std::vector< CvPoint > g_InitContour;
IplImage* g_ContourImage;
char g_cKey;

double g_mu;
double g_alpha;
double g_beta;
double g_gamma;
double g_kappa;
int g_SnakeIter;
int g_GVFIter;
int g_DeformIter;

void InitGlobalData()
{
	g_strImageFileName = new char[ 100 ];
	g_pSrcImage = 0;
	g_ImageSize;
	g_u = 0;
	g_v = 0;
	g_TmpEdge = 0;
	g_edge = 0;
	g_ContourImage = 0;
	g_cKey = ' ';
	g_InitContour.clear();

	//对于不同的图像，不同的参数会有不同的效果。
	g_mu = 0.2;
	g_alpha = 0.3;
	g_beta = 0.1;
	g_gamma = 1.0;
	g_kappa = 1.0;
	g_SnakeIter = 100;
	g_GVFIter = 500;
	g_DeformIter = 5;

}

void DeleteGlobalData()
{
}