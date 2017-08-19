/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#include "GlobalFun.h"
#include "GlobalData.h"
#include "highgui.h"

void on_mouse( int event, int x, int y, int flags, void* ptr )
{
	if( event == CV_EVENT_LBUTTONDOWN )
	{
		g_InitContour.push_back( cvPoint( x, y ) );
		ShowContent( ( IplImage* ) ptr );
	}
}

void ShowContent( IplImage* img )
{
	if( g_ContourImage == NULL )
		g_ContourImage = cvCreateImage( cvGetSize( img ), IPL_DEPTH_8U, 1 );
	cvCopyImage( img, g_ContourImage );

	for ( int i = 0; i < g_InitContour.size(); i ++ )
	{
		cvCircle( g_ContourImage, g_InitContour[ i ], 2, cvScalarAll( 155 ) );	
		int j = ( i + 1 ) % g_InitContour.size();
		cvLine( g_ContourImage,  
			g_InitContour[ i ], 
			g_InitContour[ j ] , 
			cvScalarAll( 100 ), 
			1 );           
	}
	cvShowImage( "SrcImageWnd", g_ContourImage );
}

void GetGradient( CvMat* src, CvMat* u, CvMat* v )
{
	CvSize l_ImageSize = cvGetSize( src );
	int l_iWidth = l_ImageSize.width - 1;
	int l_iHeight = l_ImageSize.height - 1;

	//四个角
	cvmSet( u, 0, 0, 0 );
	cvmSet( u, 0, l_iWidth, 0 );
	cvmSet( u, l_iHeight, 0, 0 );
	cvmSet( u, l_iHeight, l_iWidth, 0 );
	cvmSet( v, 0, 0, 0 );
	cvmSet( v, 0, l_iWidth, 0 );
	cvmSet( v, l_iHeight, 0, 0 );
	cvmSet( v, l_iHeight, l_iWidth, 0 );

	//最左最右两个列
	for ( int i = 1; i < l_iHeight; i ++ )
	{
		cvmSet( u, i, 0, 0 );
		cvmSet( u, i, l_iWidth, 0 );

		double l_dAfter = 0.0;
		double l_dBefore = 0.0;

		l_dAfter = cvmGet( src, i + 1, 0 );
		l_dBefore = cvmGet( src, i - 1, 0 );
		cvmSet( v, i, 0, 0.5 * ( l_dAfter - l_dBefore ) );

		l_dAfter = cvmGet( src, i + 1, l_iWidth );
		l_dBefore = cvmGet( src, i - 1, l_iWidth );
		cvmSet( v, i, l_iWidth, 0.5 * ( l_dAfter - l_dBefore ) );
	}//for ( int i = 1; i < l_iHeight; i ++ )

	//最上最下两个行
	for ( int i = 1; i < l_iWidth; i ++ )
	{
		cvmSet( v, 0, i, 0 );
		cvmSet( v, l_iHeight, i, 0 );

		double l_dAfter = 0.0;
		double l_dBefore = 0.0;

		l_dAfter = cvmGet( src, 0, i + 1 );
		l_dBefore = cvmGet( src, 0, i - 1 );
		cvmSet( u, 0, i, 0.5 * ( l_dAfter - l_dBefore ) );

		l_dAfter = cvmGet( src, l_iHeight, i + 1 );
		l_dBefore = cvmGet( src, l_iHeight, i - 1 );
		cvmSet( u, l_iHeight, i, 0.5 * ( l_dAfter - l_dBefore ) );
	}//for ( int i = 1; i < l_iWidth; i ++ )

	//中间点
	for ( int j = 1; j < l_iWidth; j ++ )
	{
		for ( int i = 1; i < l_iHeight; i ++ )
		{
			double l_dAfter = 0;
			double l_dBefore = 0;
			//求u
			l_dAfter = cvmGet( src, i, j + 1 );
			l_dBefore = cvmGet( src, i, j - 1 );
			cvmSet( u, i, j, 0.5 * ( l_dAfter - l_dBefore ) );
			//求v
			l_dAfter = cvmGet( src, i + 1, j );
			l_dBefore = cvmGet( src, i - 1, j );
			cvmSet( v, i, j, 0.5 * ( l_dAfter - l_dBefore ) );
		}//for ( int i = 1; i < l_iHeight; i ++ )
	}//for ( int j = 1; j < l_iWidth; j ++ )
}