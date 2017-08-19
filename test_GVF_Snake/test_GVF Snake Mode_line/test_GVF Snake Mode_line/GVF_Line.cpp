// GVF_Snake.cpp : 定义控制台应用程序的入口点。

/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#include <iostream>
#include "cv.h"
#include "highgui.h"
#include "GlobalData.h"
#include "GlobalFun.h"
#include "GVFFun.h"
#include <tchar.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	//初始化全局变量
	//cout << "初始化全局变量"<< endl;
	InitGlobalData();

	//读取图像
	//cout << "读取图像" << endl;
	cout << "输入图像文件名：" << endl;
	
	cin >> g_strImageFileName;

	g_pSrcImage = cvLoadImage( g_strImageFileName, CV_LOAD_IMAGE_GRAYSCALE );
	if ( !g_pSrcImage )
	{
		cout << "Load image error." << endl;
		return -1;
	}//if ( !g_pSrcImage )

	g_ImageSize = cvGetSize( g_pSrcImage );

	//为u和v申请空间
	//cout << "为u和v申请空间" << endl;

	g_u = cvCreateMat( g_ImageSize.height, g_ImageSize.width, CV_32FC1 );
	g_v = cvCreateMat( g_ImageSize.height, g_ImageSize.width, CV_32FC1 );

	//求解edge map
	//cout << "求解edge map" << endl;
	g_edge = cvCreateImage( g_ImageSize, IPL_DEPTH_8U, 1 );
	cvConvertScale( g_pSrcImage, g_edge, 1, 0 );	

	for ( int i = 0; i < g_ImageSize.height; i ++ )
	{
		for ( int j = 0; j < g_ImageSize.width; j ++ )
		{
			CvScalar l_s = cvGet2D( g_edge, i, j );
			int l_v = (int)l_s.val[ 0 ];
			if ( l_v < 127 )
			{
				l_v = 1;
			}
			else
			{
				l_v = 0;
			}
			l_s.val[ 0 ] = l_v;
			cvSet2D( g_edge, i, j, l_s );
		}//for ( int j = 0; j < g_ImageSize.width; j ++ )
	}//for ( int i = 0; i < g_ImageSize.height; i ++ )

	//[u,v] = GVF(f, 0.2, 80);         %计算边界图f的GVF
	//计算GVF场
	cout << "计算GVF场" << endl;
	GVFC( g_edge, g_u, g_v, g_mu, g_GVFIter );

	//显示初始图像
	cout << "显示初始图像" << endl;
	cvNamedWindow( "SrcImageWnd" );
	cvShowImage( "SrcImageWnd", g_pSrcImage );

	//初始化鼠标事件响应函数
	//cout << "初始化鼠标事件响应函数" << endl;
	cvSetMouseCallback( "SrcImageWnd", on_mouse, g_pSrcImage );

	//结束初始轮廓输入
	//cout << "结束初始轮廓输入" << endl;
	while ( g_cKey = cvWaitKey( 0 ) )
	{
		if ( g_cKey == 's' || g_cKey == 'S' )
		{
			break;
		}
	}//while ( g_cKey = cvWaitKey( 0 ) )

	//迭代求解snake
	cout << "迭代求解snake" << endl;
	for ( int l_iter = 0;
		l_iter < g_SnakeIter;
		l_iter++)
	{
		//清除可疑点
		//cout << "清除可疑点" << endl;
		vector< CvPoint > l_vecTmpContour( g_InitContour );
		vector< CvPoint >::size_type l_len = g_InitContour.size();

		g_InitContour.clear();

		for ( vector< CvPoint >::size_type l_i = 0;
			l_i < l_len;
			l_i ++ )
		{
			if ( l_vecTmpContour[ l_i ].x < 0
				|| l_vecTmpContour[ l_i ].x >= g_ImageSize.width )
			{
				continue;
			}
			if ( l_vecTmpContour[ l_i ].y < 0
				|| l_vecTmpContour[ l_i ].y >= g_ImageSize.height )
			{
				continue;
			}
			g_InitContour.push_back( l_vecTmpContour[ l_i ] );
		}//for ( vector< CvPoint >::size_type l_i = 0;
			//l_i < l_len;
			//l_i ++ )

		//对轮廓进行插值
		//cout << "对轮廓进行插值" << endl;
		SnakeInterp( g_InitContour );

		if ( g_InitContour.size() < 5 )
		{
			cout << "Contour interp fault." << endl;
			break;
		}//if ( g_InitContour.size() < 5 )

		//snake迭代
		//cout << "snake迭代" << endl;
		SnakeDeform( g_InitContour, g_alpha,g_beta, g_gamma, g_kappa, g_u, g_v, g_DeformIter );

		//显示迭代效果
		//cout << "显示迭代效果" << endl;
		ShowContent( g_pSrcImage );
		cvWaitKey( 20 );
		cout << "迭代了 "
			<< l_iter
			<< " 次"
			<< endl;
	}//	for ( int l_iter = 0;
	 //l_iter < g_SnakeIter;
	 //l_iter++)

	DeleteGlobalData();

	cvWaitKey();

	system("pause");
	return 0;
}

