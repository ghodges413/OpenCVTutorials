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

		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	//Defining window names
	const char * windowNameOriginalVideo = "Original Video";
	const char * windowNameBrightnessHigh50 = "Brightness Increased by 50";
	const char * windowNameWithBrightnessHigh100 = "Brightness Increased by 100";
	const char * windowNameBrightnessLow50 = "Brightness Decreased by 50";
	const char * windowNameBrightnessLow100 = "Brightness Decreased by 100";

	//Create and open windows for above window names
	cv::namedWindow( windowNameOriginalVideo, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameBrightnessHigh50, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameWithBrightnessHigh100, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameBrightnessLow50, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameBrightnessLow100, cv::WindowFlags::WINDOW_NORMAL );

	while ( 1 ) {
		// read a new frame from video 
		cv::Mat frame;
		bool didRead = cap.read( frame );

		// Breaking the while loop at the end of the video
		if ( !didRead ) {
			printf( "Found the end of the video\n" );
			break;
		}

		cv::Mat frameBrighnessHigh50;
		frame.convertTo( frameBrighnessHigh50, -1, 1, 50 ); //increase the brightness by 50

		cv::Mat frameBrighnessHigh100;
		frame.convertTo( frameBrighnessHigh100, -1, 1, 100 ); //increase the brightness by 100

		cv::Mat frameBrighnessLow50;
		frame.convertTo( frameBrighnessLow50, -1, 1, -50 ); //decrease the brightness by 50

		cv::Mat frameBrighnessLow100;
		frame.convertTo( frameBrighnessLow100, -1, 1, -100 ); //decrease the brightness by 100

		// Show above frames inside the created windows.
		cv::imshow( windowNameOriginalVideo, frame );
		cv::imshow( windowNameBrightnessHigh50, frameBrighnessHigh50 );
		cv::imshow( windowNameWithBrightnessHigh100, frameBrighnessHigh100 );
		cv::imshow( windowNameBrightnessLow50, frameBrighnessLow50 );
		cv::imshow( windowNameBrightnessLow100, frameBrighnessLow100 );

		// wait for for 10 ms until any key is pressed.  
		// If the 'Esc' key is pressed, break the while loop.
		// If the any other key is pressed, continue the loop 
		// If any key is not pressed withing 10 ms, continue the loop
		if ( cv::waitKey( 10 ) == 27 ) {
			printf( "Esc key is pressed by user. Stopping the video\n" );
			break;
		}
	}

	return 0;
}
