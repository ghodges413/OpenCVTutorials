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
	// Read the image file
	cv::Mat image = cv::imread( "common/data/photo.jpg" );

	// Check for failure
	if ( image.empty() ) {
		printf( "Could not open or find the image\n" );
		system( "pause" ); // wait for any key press
		return -1;
	}

	// Name of the window
	const char * windowName = "My HelloWorld Window";

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
