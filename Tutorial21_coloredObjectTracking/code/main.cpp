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
const char* pzRotatedImage = "Rotated Image";

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
Red Object Detection
====================================================
*/
int ObjectDetection() {
	cv::VideoCapture cap( 0 ); //capture the video from web cam

	if ( !cap.isOpened() ) {
		printf( "Cannot open the web cam\n" );
		return -1;
	}

	cv::namedWindow( "Control", cv::WINDOW_AUTOSIZE ); //create a window called "Control"

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0; 
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	// Create trackbars in "Control" window
	cv::createTrackbar( "LowH", "Control", &iLowH, 179 ); //Hue (0 - 179)
	cv::createTrackbar( "HighH", "Control", &iHighH, 179 );

	cv::createTrackbar( "LowS", "Control", &iLowS, 255 ); //Saturation (0 - 255)
	cv::createTrackbar( "HighS", "Control", &iHighS, 255 );

	cv::createTrackbar( "LowV", "Control", &iLowV, 255 ); //Value (0 - 255)
	cv::createTrackbar( "HighV", "Control", &iHighV, 255 );

	while ( 1 ) {
		cv::Mat imgOriginal;

		bool didRead = cap.read(imgOriginal); // read a new frame from video

		if ( !didRead ) {
			printf( "Cannot read a frame from video stream\n" );
			break;
		}

		cv::Mat imgHSV;

		cv::cvtColor( imgOriginal, imgHSV, cv::COLOR_BGR2HSV ); //Convert the captured frame from BGR to HSV

		cv::Mat imgThresholded;

		cv::inRange( imgHSV, cv::Scalar( iLowH, iLowS, iLowV ), cv::Scalar( iHighH, iHighS, iHighV ), imgThresholded ); //Threshold the image

																									  //morphological opening (remove small objects from the foreground)
		cv::erode( imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) );
		cv::dilate( imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) ); 

		//morphological closing (fill small holes in the foreground)
		cv::dilate( imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) ); 
		cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) );

		cv::imshow( "Thresholded Image", imgThresholded ); //show the thresholded image
		cv::imshow( "Original", imgOriginal ); //show the original image

		if ( cv::waitKey( 30 ) == 27 ) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
			printf( "esc key is pressed by user\n" );
			break; 
		}
	}

	return 0;
}

/*
====================================================
red object tracking
====================================================
*/
int ObjectTracking() {
	cv::VideoCapture cap( 0 ); //capture the video from webcam

	if ( !cap.isOpened() ) {
		printf( "Cannot open the web cam\n" );
		return -1;
	}

	cv::namedWindow( "Control", cv::WINDOW_AUTOSIZE ); //create a window called "Control"

	int iLowH = 170;
	int iHighH = 179;

	int iLowS = 150; 
	int iHighS = 255;

	int iLowV = 60;
	int iHighV = 255;

	// Create trackbars in "Control" window
	cv::createTrackbar( "LowH", "Control", &iLowH, 179 ); //Hue (0 - 179)
	cv::createTrackbar( "HighH", "Control", &iHighH, 179 );

	cv::createTrackbar( "LowS", "Control", &iLowS, 255 ); //Saturation (0 - 255)
	cv::createTrackbar( "HighS", "Control", &iHighS, 255 );

	cv::createTrackbar( "LowV", "Control", &iLowV, 255 ); //Value (0 - 255)
	cv::createTrackbar( "HighV", "Control", &iHighV, 255 );

	int iLastX = -1; 
	int iLastY = -1;

	//Capture a temporary image from the camera
	cv::Mat imgTmp;
	cap.read(imgTmp); 

	//Create a black image with the size as the camera output
	cv::Mat imgLines = cv::Mat::zeros( imgTmp.size(), CV_8UC3 );


	while ( 1 )	{
		cv::Mat imgOriginal;

		bool didRead = cap.read( imgOriginal ); // read a new frame from video

		if ( !didRead ) {
			printf( "Cannot read a frame from video stream\n" );
			break;
		}

		cv::Mat imgHSV;

		cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		cv::Mat imgThresholded;

		cv::inRange( imgHSV, cv::Scalar( iLowH, iLowS, iLowV ), cv::Scalar( iHighH, iHighS, iHighV), imgThresholded ); //Threshold the image

																									  //morphological opening (removes small objects from the foreground)
		cv::erode( imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) );
		cv::dilate( imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) ); 

		//morphological closing (removes small holes from the foreground)
		cv::dilate( imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) ); 
		cv::erode( imgThresholded, imgThresholded, cv::getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 5, 5 ) ) );

		//Calculate the moments of the thresholded image
		cv::Moments oMoments = cv::moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
		if ( dArea > 10000 ) {
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;        

			if ( iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0 ) {
				//Draw a red line from the previous point to the current point
				line( imgLines, cv::Point( posX, posY ), cv::Point( iLastX, iLastY ), cv::Scalar( 0, 0, 255 ), 2 );
			}

			iLastX = posX;
			iLastY = posY;
		}

		cv::imshow( "Thresholded Image", imgThresholded ); //show the thresholded image

		imgOriginal = imgOriginal + imgLines;
		cv::imshow( "Original", imgOriginal ); //show the original image

		if ( cv::waitKey( 30 ) == 27 ) { //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
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
	int result = ObjectDetection();
	if ( 0 != result ) {
		return result;
	}

	result = ObjectTracking();
	if ( 0 != result ) {
		return result;
	}

	return 0;
}
