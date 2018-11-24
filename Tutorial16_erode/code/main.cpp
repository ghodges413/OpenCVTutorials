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
		cv::waitKey( 0 );
		return -1;
	}

	//Erode the image with 3x3 kernel
	cv::Mat image_eroded_with_3x3_kernel;
	cv::erode( image, image_eroded_with_3x3_kernel, cv::getStructuringElement( cv::MORPH_RECT, cv::Size( 3, 3 ) ) );

	//Erode the image with 5x5 kernel
	cv::Mat image_eroded_with_5x5_kernel;
	cv::erode( image, image_eroded_with_5x5_kernel, cv::getStructuringElement( cv::MORPH_RECT, cv::Size( 5, 5 ) ) );

	//Define names of the windows
	const char * window_name = "Lotus";
	const char * window_name_eroded_with_3x3_kernel = "Lotus eroded with 3 x 3 kernel";
	const char * window_name_eroded_with_5x5_kernel = "Lotus eroded with 5 x 5 kernel";

	// Create windows with above names
	cv::namedWindow( window_name);
	cv::namedWindow( window_name_eroded_with_3x3_kernel );
	cv::namedWindow( window_name_eroded_with_5x5_kernel );

	// Show our images inside the created windows.
	cv::imshow( window_name, image );
	cv::imshow( window_name_eroded_with_3x3_kernel, image_eroded_with_3x3_kernel );
	cv::imshow( window_name_eroded_with_5x5_kernel, image_eroded_with_5x5_kernel );

	cv::waitKey( 0 ); // Wait for any keystroke in the window

	cv::destroyAllWindows(); //destroy all opened windows

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
		cv::waitKey( 0 );
		return -1;
	}


	//Define names of the window
	const char * window_name_of_original_video = "Original Video";
	const char * window_name_of_video_eroded_with_5x5_kernel = "Video eroded with 5 x 5 kernel";

	// Create a window with above names
	cv::namedWindow( window_name_of_original_video, cv::WINDOW_NORMAL );
	cv::namedWindow( window_name_of_video_eroded_with_5x5_kernel, cv::WINDOW_NORMAL );

	while ( 1 ) {
		cv::Mat frame;
		bool didRead = cap.read( frame ); // read a new frame from video 
		if ( !didRead ) {
			printf( "Found the end of the video\n" );
			break;
		}

		//erode the frame with 5x5 kernel
		cv::Mat frame_eroded_with_5x5_kernel;
		cv::erode( frame, frame_eroded_with_5x5_kernel, cv::getStructuringElement( cv::MORPH_RECT, cv::Size( 5, 5 ) ) );

		//show the frames in the created windows
		cv::imshow( window_name_of_original_video, frame );
		cv::imshow( window_name_of_video_eroded_with_5x5_kernel, frame_eroded_with_5x5_kernel );

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
