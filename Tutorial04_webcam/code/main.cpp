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
	// Open the default video camera
	cv::VideoCapture cap( 0 );

	// if not success, exit program
	if ( !cap.isOpened() ) {
		printf( "Cannot open the video camera\n" );
		
		// Wait for any key press
		cv::waitKey( 0 );
		return -1;
	} 

	int width = (int)cap.get( cv::VideoCaptureProperties::CAP_PROP_FRAME_WIDTH ); // get the width of frames of the video
	int height = (int)cap.get( cv::VideoCaptureProperties::CAP_PROP_FRAME_HEIGHT ); // get the height of frames of the video

	printf( "Resolution of the video : ( %i, %i )\n", width, height );

	// create a window called "My Camera Feed"
	const char * window_name = "My Camera Feed";
	cv::namedWindow( window_name );

	while ( 1 ) {
		// read a new frame from video 
		cv::Mat frame;
		bool didRead = cap.read( frame );
		
		// Breaking the while loop if the frames cannot be captured
		if ( !didRead ) {
			printf( "Video camera is disconnected\n" );
			
			// Wait for any key press
			cv::waitKey( 0 );
			break;
		}

		// show the frame in the created window
		cv::imshow( window_name, frame );

		// wait for for 10 ms until any key is pressed.  
		// If the 'Esc' key is pressed, break the while loop.
		// If the any other key is pressed, continue the loop 
		// If any key is not pressed withing 10 ms, continue the loop 
		if ( cv::waitKey( 10 ) == 27 ) {
			printf( "Esc key is pressed by user. Stoping the video\n" );
			break;
		}
	}

	return 0;
}
