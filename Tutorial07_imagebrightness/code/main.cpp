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

		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	cv::Mat imageBrighnessHigh50;
	image.convertTo( imageBrighnessHigh50, -1, 1, 50 ); //increase the brightness by 50

	cv::Mat imageBrighnessHigh100;
	image.convertTo( imageBrighnessHigh100, -1, 1, 100 ); //increase the brightness by 100

	cv::Mat imageBrighnessLow50;
	image.convertTo( imageBrighnessLow50, -1, 1, -50 ); //decrease the brightness by 50

	cv::Mat imageBrighnessLow100;
	image.convertTo( imageBrighnessLow100, -1, 1, -100 ); //decrease the brightness by 100

	// Defining window names for above images
	const char * windowNameOriginalImage = "Original Image";
	const char * windowNameBrightnessHigh50 = "Brightness Increased by 50";
	const char * windowNameWithBrightnessHigh100 = "Brightness Increased by 100";
	const char * windowNameBrightnessLow50 = "Brightness Decreased by 50";
	const char * windowNameBrightnessLow100 = "Brightness Decreased by 100";

	//Create and open windows for above images
	cv::namedWindow( windowNameOriginalImage, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameBrightnessHigh50, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameWithBrightnessHigh100, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameBrightnessLow50, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameBrightnessLow100, cv::WindowFlags::WINDOW_NORMAL );

	//Show above images inside the created windows.
	cv::imshow( windowNameOriginalImage, image );
	cv::imshow( windowNameBrightnessHigh50, imageBrighnessHigh50 );
	cv::imshow( windowNameWithBrightnessHigh100, imageBrighnessHigh100 );
	cv::imshow( windowNameBrightnessLow50, imageBrighnessLow50 );
	cv::imshow( windowNameBrightnessLow100, imageBrighnessLow100 );

	cv::waitKey( 0 ); // Wait for any key stroke

	cv::destroyAllWindows(); //destroy all open windows

	return 0;
}
