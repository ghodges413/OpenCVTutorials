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
		
		// wait for any key press
		cv::waitKey( 0 );
		return -1;
	}

	cv::Mat imageContrastHigh2;
	image.convertTo( imageContrastHigh2, -1, 2, 0 ); //increase the contrast by 2

	cv::Mat imageContrastHigh4;
	image.convertTo( imageContrastHigh4, -1, 4, 0 ); //increase the contrast by 4

	cv::Mat imageContrastLow0_5;
	image.convertTo( imageContrastLow0_5, -1, 0.5, 0 ); //decrease the contrast by 0.5

	cv::Mat imageContrastLow0_25;
	image.convertTo( imageContrastLow0_25, -1, 0.25, 0 ); //decrease the contrast by 0.25


	// Defining window names for above images
	const char * windowNameOriginalImage = "Original Image";
	const char * windowNameContrastHigh2 = "Contrast Increased by 2";
	const char * windowNameContrastHigh4 = "Contrast Increased by 4";
	const char * windowNameContrastLow0_5 = "Contrast Decreased by 0.5";
	const char * windowNameContrastLow0_25 = "Contrast Decreased by 0.25";

	//Create and open windows for above images
	cv::namedWindow( windowNameOriginalImage, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastHigh2, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastHigh4, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastLow0_5, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastLow0_25, cv::WindowFlags::WINDOW_NORMAL );

	//Show above images inside the created windows.
	cv::imshow( windowNameOriginalImage, image );
	cv::imshow( windowNameContrastHigh2, imageContrastHigh2 );
	cv::imshow( windowNameContrastHigh4, imageContrastHigh4 );
	cv::imshow( windowNameContrastLow0_5, imageContrastLow0_5 );
	cv::imshow( windowNameContrastLow0_25, imageContrastLow0_25 );

	cv::waitKey( 0 ); // Wait for any key stroke

	cv::destroyAllWindows(); //destroy all open windows

	return 0;
}
