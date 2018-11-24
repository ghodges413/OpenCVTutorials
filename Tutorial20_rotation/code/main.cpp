//
//  main.cpp
//
#include <string>
#include <stdio.h>

#include <opencv2/opencv.hpp>

int iAngle = 180;
int iScale = 50;
int iBorderMode = 0;
cv::Mat imgOriginal;
int iImageCenterY = 0;
int iImageCenterX = 0;
const char * pzRotatedImage = "Rotated Image";

/*
====================================================
CallbackForTrackBar
====================================================
*/
void CallbackForTrackBar( int, void * ) {
	cv::Mat matRotation = cv::getRotationMatrix2D( cv::Point( iImageCenterX, iImageCenterY ), ( iAngle - 180 ), iScale / 50.0 );

	// Rotate the image
	cv::Mat imgRotated;
	cv::warpAffine( imgOriginal, imgRotated, matRotation, imgOriginal.size(), cv::INTER_LINEAR, iBorderMode, cv::Scalar() );

	cv::imshow( pzRotatedImage, imgRotated );
}

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

	iImageCenterY = imgOriginal.rows / 2;
	iImageCenterX = imgOriginal.cols / 2;

	//show the original image
	const char* pzOriginalImage = "Original Image";
	cv::namedWindow( pzOriginalImage, cv::WINDOW_AUTOSIZE );
	cv::imshow( pzOriginalImage, imgOriginal );

	//create the "Rotated Image" window and 3 trackbars in it
	cv::namedWindow( pzRotatedImage, cv::WINDOW_AUTOSIZE );
	cv::createTrackbar( "Angle", pzRotatedImage, &iAngle, 360, CallbackForTrackBar );
	cv::createTrackbar( "Scale", pzRotatedImage, &iScale, 100, CallbackForTrackBar );
	cv::createTrackbar( "Border Mode", pzRotatedImage, &iBorderMode, 5, CallbackForTrackBar );

	int iDummy = 0;

	CallbackForTrackBar( iDummy, &iDummy );

	cv::waitKey( 0 );

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

	const char * pzOriginalWindowName = "Original Video";
	cv::namedWindow(pzOriginalWindowName, cv::WINDOW_AUTOSIZE );

	const char * pzRotatingWindowName = "Rotated Video";
	cv::namedWindow( pzRotatingWindowName, cv::WINDOW_AUTOSIZE );

	int iAngle = 180;
	cv::createTrackbar( "Angle", pzRotatingWindowName, &iAngle, 360 );

	while ( 1 ) {
		cv::Mat matOriginalFrame;

		// read a new frame from video
		bool didRead = cap.read( matOriginalFrame );

		//if not success, break loop
		if ( !didRead ) {
			printf( "Cannot read the frame from video file\n" );
			break;
		}

		cv::imshow(pzOriginalWindowName, matOriginalFrame);

		//get the affine transformation matrix
		cv::Mat matRotation = cv::getRotationMatrix2D( cv::Point( matOriginalFrame.cols / 2, matOriginalFrame.rows / 2 ), ( iAngle - 180 ), 1 );

		// Rotate the image
		cv::Mat matRotatedFrame;
		cv::warpAffine( matOriginalFrame, matRotatedFrame, matRotation, matOriginalFrame.size() );

		cv::imshow( pzRotatingWindowName, matRotatedFrame );

		//wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		if ( cv::waitKey( 30 ) == 27 ) {
			printf( "esc key is pressed by user\n" );
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
