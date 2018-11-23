//
//  main.cpp
//
#include <string>
#include <stdio.h>

#include <opencv2/opencv.hpp>

/*
====================================================
main
====================================================
*/
int main( int argc, char * argv[] ) {
	// create a new image which consists of 
	// 3 channels 
	// image depth of 8 bits 
	// 800 x 600 of resolution (800 wide and 600 high)
	// each pixels initialized to the value of (100, 250, 30) for Blue, Green and Red planes respectively.
	cv::Mat image( 600, 800, CV_8UC3, cv::Scalar( 100, 250, 30 ) );

	// Name of the window
	const char * windowName = "Window with Blank Image";

	// Create a window
	cv::namedWindow( windowName );
	
	// Show our image inside the created window.
	cv::imshow( windowName, image );

	// Wait for any keystroke in the window
	cv::waitKey( 0 );

	// destroy the created window
	cv::destroyWindow( windowName );

	return 0;
}
