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

	// Convert the image from BGR to YCrCb color space
	cv::Mat hist_equalized_image;
	cv::cvtColor( image, hist_equalized_image, cv::COLOR_BGR2YCrCb );

	// Split the image into 3 channels; Y, Cr and Cb channels respectively and store it in a std::vector
	std::vector< cv::Mat > vec_channels;
	cv::split( hist_equalized_image, vec_channels ); 

	// Equalize the histogram of only the Y channel 
	cv::equalizeHist( vec_channels[ 0 ], vec_channels[ 0 ] );

	// Merge 3 channels in the vector to form the color image in YCrCB color space.
	cv::merge( vec_channels, hist_equalized_image );

	// Convert the histogram equalized image from YCrCb to BGR color space again
	cv::cvtColor( hist_equalized_image, hist_equalized_image, cv::COLOR_YCrCb2BGR );

	//Define the names of windows
	const char * windowNameOfOriginalImage = "Original Image"; 
	const char * windowNameOfHistogramEqualized = "Histogram Equalized Color Image";

	// Create windows with the above names
	cv::namedWindow( windowNameOfOriginalImage, cv::WINDOW_NORMAL );
	cv::namedWindow( windowNameOfHistogramEqualized, cv::WINDOW_NORMAL );

	// Show images inside the created windows.
	cv::imshow( windowNameOfOriginalImage, image );
	cv::imshow( windowNameOfHistogramEqualized, hist_equalized_image );

	cv::waitKey( 0 ); // Wait for any keystroke in any one of the windows

	cv::destroyAllWindows(); // Destroy all opened windows

	return 0;
}
