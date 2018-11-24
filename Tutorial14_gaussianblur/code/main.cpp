//
//  main.cpp
//
#include <string>
#include <stdio.h>

#include <opencv2/opencv.hpp>

/*
====================================================
Image
====================================================
*/
int Image() {
	// Read the image file
	cv::Mat image = cv::imread( "common/data/photo.jpg" );

	// Check for failure
	if ( image.empty() ) {
		printf( "Could not open or find the image\n" );
		cv::waitKey( 0 ); // wait for any key press
		return -1;
	}

	//Blur the image with 3x3 Gaussian kernel
	cv::Mat image_blurred_with_3x3_kernel;
	cv::GaussianBlur( image, image_blurred_with_3x3_kernel, cv::Size( 3, 3 ), 0 );

	//Blur the image with 5x5 Gaussian kernel
	cv::Mat image_blurred_with_5x5_kernel;
	cv::GaussianBlur( image, image_blurred_with_5x5_kernel, cv::Size( 5, 5 ), 0 );

	//Define names of the windows
	const char * window_name = "Photo";
	const char * window_name_blurred_with_3x3_kernel = "Photo Blurred with 3 x 3 Gaussian Kernel";
	const char * window_name_blurred_with_5x5_kernel = "Photo Blurred with 5 x 5 Gaussian Kernel";

	// Create windows with above names
	cv::namedWindow( window_name );
	cv::namedWindow( window_name_blurred_with_3x3_kernel );
	cv::namedWindow( window_name_blurred_with_5x5_kernel );

	// Show our images inside the created windows.
	cv::imshow( window_name, image );
	cv::imshow( window_name_blurred_with_3x3_kernel, image_blurred_with_3x3_kernel );
	cv::imshow( window_name_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel );

	cv::waitKey( 0 ); // Wait for any keystroke in the window

	cv::destroyAllWindows(); // destroy all opened windows

	return 0;
}

/*
====================================================
Video
====================================================
*/
int Video() {
	//open the video file for reading
	cv::VideoCapture cap( "common/data/sample.mp4" );

	// if not success, exit program
	if ( !cap.isOpened() ) {
		printf( "Cannot open the video file\n" );
		cv::waitKey( 0 ); // wait for any key press
		return -1;
	}

	// Define names of the window
	const char * window_name_of_original_video = "Original Video";
	const char * window_name_of_video_blurred_with_5x5_kernel = "Video Blurred with 5 x 5 Gaussian Kernel";

	// Create a window with above names
	cv::namedWindow( window_name_of_original_video, cv::WINDOW_NORMAL );
	cv::namedWindow( window_name_of_video_blurred_with_5x5_kernel, cv::WINDOW_NORMAL );

	while ( 1 ) {
		cv::Mat frame;
		bool didRead = cap.read( frame ); // read a new frame from video 
		if ( !didRead ) {
			printf( "Found the end of the video\n" );
			break;
		}

		// Blur the frame with 5x5 Gaussian kernel
		cv::Mat frame_blurred_with_5x5_kernel;
		cv::GaussianBlur( frame, frame_blurred_with_5x5_kernel, cv::Size( 5, 5 ), 0 );

		//show the frames in the created windows
		cv::imshow( window_name_of_original_video, frame );
		cv::imshow( window_name_of_video_blurred_with_5x5_kernel, frame_blurred_with_5x5_kernel );

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop
		if ( cv::waitKey( 10 ) == 27 ) {
			printf( "Esc key is pressed by user. Stoping the video.\n" );
			break;
		}
	}

	return 0;
}

/*
====================================================
main
====================================================
*/
int main( int argc, char * argv[] ) {
	int result = Image();
	if ( 0 != result ) {
		return result;
	}

	result = Video();
	if ( 0 != result ) {
		return result;
	}

	return 0;
}
