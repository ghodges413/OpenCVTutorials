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

		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	int frame_width = (int)cap.get( cv::VideoCaptureProperties::CAP_PROP_FRAME_WIDTH ); // get the width of frames of the video
	int frame_height = (int)cap.get( cv::VideoCaptureProperties::CAP_PROP_FRAME_HEIGHT ); // get the height of frames of the video

	cv::Size frame_size( frame_width, frame_height );
	int frames_per_second = 10;

	// Create and initialize the VideoWriter object 
	cv::VideoWriter oVideoWriter( "output/saved.avi", cv::VideoWriter::fourcc( 'M', 'J', 'P', 'G' ), frames_per_second, frame_size, true );

	// If the VideoWriter object is not initialized successfully, exit the program
	if ( !oVideoWriter.isOpened() ) {
		printf( "Cannot save the video to a file\n" );

		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	// create a window called "My Camera Feed"
	const char * window_name = "My Camera Feed";
	cv::namedWindow( window_name );

	while ( 1 ) {
		// read a new frame from the video camera
		cv::Mat frame;
		bool didRead = cap.read( frame );

		// Breaking the while loop if frames cannot be read from the camera
		if ( didRead ) {
			printf( "Video camera is disconnected\n" );

			// Wait for any keystroke in the window
			cv::waitKey( 0 );
			break;
		}

		/*
		Make changes to the frame as necessary
		e.g.  
		1. Change brightness/contrast of the image
		2. Smooth/Blur image
		3. Crop the image
		4. Rotate the image
		5. Draw shapes on the image
		*/

		// write the video frame to the file
		oVideoWriter.write( frame ); 

		// show the frame in the created window
		cv::imshow( window_name, frame );

		// Wait for for 10 milliseconds until any key is pressed.  
		// If the 'Esc' key is pressed, break the while loop.
		// If any other key is pressed, continue the loop 
		// If any key is not pressed within 10 milliseconds, continue the loop 
		if ( cv::waitKey( 10 ) == 27 ) {
			printf( "Esc key is pressed by the user. Stopping the video\n" );
			break;
		}
	}

	// Flush and close the video file
	oVideoWriter.release();

	return 0;
}
