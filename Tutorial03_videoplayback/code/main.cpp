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
	if ( cap.isOpened() == false ) {
		printf( "Cannot open the video file\n" );
		
		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	// Uncomment the following line if you want to start the video in the middle
	//cap.set( CAP_PROP_POS_MSEC, 300 ); 

	//get the frames rate of the video
	double fps = cap.get( cv::VideoCaptureProperties::CAP_PROP_FPS ); 
	printf( "Frames per seconds : %f\n", fps );

	const char * window_name = "My First Video";

	// create a window
	cv::namedWindow( window_name, cv::WindowFlags::WINDOW_NORMAL );

	while ( true ) {
		// read a new frame from video 
		cv::Mat frame;
		const bool didRead = cap.read( frame );

		// Breaking the while loop at the end of the video
		if ( !didRead ) {
			printf( "Found the end of the video\n" );
			break;
		}

		// show the frame in the created window
		cv::imshow( window_name, frame );

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
