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
	// open the video file for reading
	cv::VideoCapture cap( "common/data/sample.mp4" );

	// if not success, exit program
	if ( !cap.isOpened() ) {
		printf( "Cannot open the video file\n" );
		
		// wait for any key press
		cv::waitKey( 0 );
		return -1;
	}

	//Defining window names for above images
	const char * windowNameOriginalImage = "Original Image";
	const char * windowNameContrastHigh2 = "Contrast Increased by 2";
	const char * windowNameContrastHigh4 = "Contrast Increased by 4";
	const char * windowNameContrastLow0_5 = "Contrast Decreased by 0.5";
	const char * windowNameContrastLow0_25 = "Contrast Decreased by 0.25";

	// Create and open windows for above images
	cv::namedWindow( windowNameOriginalImage, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastHigh2, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastHigh4, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastLow0_5, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameContrastLow0_25, cv::WindowFlags::WINDOW_NORMAL );

	while ( 1 ) {
		// read a new frame from video 
		cv::Mat frame;
		bool didRead = cap.read( frame );

		// Breaking the while loop at the end of the video
		if ( !didRead ) {
			printf( "Found the end of the video\n" );
			break;
		}

		cv::Mat frameContrastHigh2;
		frame.convertTo( frameContrastHigh2, -1, 2, 0 ); //increase the contrast by 2

		cv::Mat frameContrastHigh4;
		frame.convertTo( frameContrastHigh4, -1, 4, 0 ); //increase the contrast by 4

		cv::Mat frameContrastLow0_5;
		frame.convertTo( frameContrastLow0_5, -1, 0.5, 0 ); //decrease the contrast by 0.5

		cv::Mat frameContrastLow0_25;
		frame.convertTo( frameContrastLow0_25, -1, 0.25, 0 ); //decrease the contrast by 0.25

		// Show above images inside the created windows.
		cv::imshow( windowNameOriginalImage, frame );
		cv::imshow( windowNameContrastHigh2, frameContrastHigh2 );
		cv::imshow( windowNameContrastHigh4, frameContrastHigh4 );
		cv::imshow( windowNameContrastLow0_5, frameContrastLow0_5 );
		cv::imshow( windowNameContrastLow0_25, frameContrastLow0_25 );

		// wait for for 10 ms until any key is pressed.  
		// If the 'Esc' key is pressed, break the while loop.
		// If the any other key is pressed, continue the loop 
		// If any key is not pressed withing 10 ms, continue the loop
		if ( cv::waitKey( 10 ) == 27 ) {
			printf( "Esc key is pressed by user. Stopping the video.\n" );
			break;
		}
	}

	return 0;
}
