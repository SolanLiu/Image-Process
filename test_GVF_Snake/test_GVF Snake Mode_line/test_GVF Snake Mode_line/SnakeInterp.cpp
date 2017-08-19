/*==================================================================
=  代码内容：GVF Snake                                      
=  修改日期: 2010.10.20                                                                                                        
=  作者:BeanYoung
=  email:guobasanxian@gmail.com                                                
====================================================================*/

#include "GVFFun.h"

void GetContourDistance( std::vector < CvPoint >& l_Contour,
						std::vector< double >& l_Distance)
{
	//记录轮廓点大小
	std::vector < CvPoint >::size_type l_ContourSize
		= l_Contour.size();  

	//初始化距离数组
	l_Distance.clear();
	l_Distance.reserve( l_ContourSize );
	l_Distance.resize( l_ContourSize, 0.0 );

	for ( std::vector < CvPoint >::size_type l_i = 0;
		l_i < l_ContourSize;
		l_i ++ )
	{
		// 记录下一个点的位置
		std::vector < CvPoint >::size_type l_j
			= ( l_i + 1 ) % l_ContourSize; 
		int l_x = l_Contour[ l_i ].x - l_Contour[ l_j ].x;
		int l_y = l_Contour[ l_i ].y - l_Contour[ l_j ].y;
		double l_DistanceSquare = ( double ) l_x * ( double ) l_x
			+ ( double ) l_y * ( double ) l_y;
		l_Distance[ l_i ] = sqrt( l_DistanceSquare );
	}
}

void SnakeInterp( std::vector<CvPoint>& l_Contour )
{
	std::vector < CvPoint > l_tempContour;
	std::vector < double > l_Distance;

	l_tempContour.clear();
	l_tempContour = l_Contour;
	l_Distance.clear();

	//循环10次，求解轮廓插值，最大插值为1024距离
	for ( int l_Count = 0; l_Count < 10; l_Count ++ )
	{
		l_Contour.clear();
		l_Contour = l_tempContour;
		l_tempContour.clear();

		//记录轮廓点的数组大小
		std::vector < CvPoint >::size_type l_ContourSize 
			= l_Contour.size();  
			
		//得到相邻点的距离
		GetContourDistance( l_Contour, l_Distance );   

		for ( std::vector < CvPoint >::size_type l_i = 0;
			l_i < l_ContourSize;
			l_i ++ )
		{
			if ( l_Distance[ l_i ] < 0.5 )
			{
				continue;
			}
			l_tempContour.push_back( l_Contour[ l_i ] );

			if ( l_Distance[ l_i ] > 1.8 )
			{
				std::vector < CvPoint >::size_type l_j 
					= ( l_i + 1 ) % l_ContourSize;
				CvPoint l_tmpMidPoint 
					= cvPoint( ( l_Contour[ l_i ].x + l_Contour[ l_j ].x ) / 2,
					           ( l_Contour[ l_i ].y + l_Contour[ l_j ].y ) / 2 );
				l_tempContour.push_back( l_tmpMidPoint );
			}
		}//for()
	}//for ( int l_Count = 0; l_Count < 10; l_Count ++ )
	l_Contour.clear();
	l_Contour = l_tempContour;
}  