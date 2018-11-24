//
//  main.cpp
//
#include <string>
#include <stdio.h>

#include <opencv2/opencv.hpp>

/*
====================================================
CallBackFunc
====================================================
*/
void CallBackFunc( int event, int x, int y, int flags, void * userdata ) {
	if ( flags == ( cv::EVENT_FLAG_CTRLKEY + cv::EVENT_FLAG_LBUTTON ) ) {
		printf( "Left mouse button is clicked while pressing CTRL key - position ( %i, %i )\n", x, y );
	} else if ( flags == ( cv::EVENT_FLAG_RBUTTON + cv::EVENT_FLAG_SHIFTKEY ) ) {
		printf( "Right mouse button is clicked while pressing SHIFT key- position ( %i, %i )\n", x, y );
	} else if ( event == cv::EVENT_MOUSEMOVE && flags == cv::EVENT_FLAG_ALTKEY ) {
		printf( "Mouse is moved over the window while pressing ALT key - position ( %i, %i )\n", x, y );
	}
}

/*
====================================================
main
====================================================
*/
int main( int argc, char** argv ) {
	// Read image from file 
	cv::Mat img = cv::imread( "common/data/photo.jpg" );

	//if fail to read the image
	if ( img.empty() ) { 
		printf( "Error loading the image\n" );
		return -1; 
	}

	//Create a window
	cv::namedWindow( "My Window", 1 );

	//set the callback function for any mouse event
	cv::setMouseCallback( "My Window", CallBackFunc, NULL );

	//show the image
	cv::imshow( "My Window", img );

	// Wait until user press some key
	cv::waitKey( 0 );

	return 0;
}