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
	//cv::Mat image = cv::imread( "common/data/photo.jpg" );
	//cv::Mat image = cv::imread( "common/data/TomCruise.jpg" );
	cv::Mat image = cv::imread( "common/data/top-gun-tom-cruise.png" );

	// Check for failure
	if ( image.empty() ) {
		printf( "Could not open or find the image\n" );

		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	cv::Mat imageBrighnessHigh50;
	image.convertTo( imageBrighnessHigh50, -1, 1, 50 ); //increase the brightness by 50

	cv::Mat imageBrighnessHigh100;
	image.convertTo( imageBrighnessHigh100, -1, 1, 100 ); //increase the brightness by 100

	cv::Mat imageBrighnessLow50;
	image.convertTo( imageBrighnessLow50, -1, 1, -50 ); //decrease the brightness by 50

	cv::Mat imageBrighnessLow100;
	image.convertTo( imageBrighnessLow100, -1, 1, -100 ); //decrease the brightness by 100

	// Defining window names for above images
	const char * windowNameOriginalImage = "Original Image";
	const char * windowNameBrightnessHigh50 = "Brightness Increased by 50";
	const char * windowNameWithBrightnessHigh100 = "Brightness Increased by 100";
	const char * windowNameBrightnessLow50 = "Brightness Decreased by 50";
	const char * windowNameBrightnessLow100 = "Brightness Decreased by 100";

	//Create and open windows for above images
	cv::namedWindow( windowNameOriginalImage, cv::WindowFlags::WINDOW_NORMAL );
	cv::namedWindow( windowNameBrightnessHigh50, cv::WindowFlags::WINDOW_NORMAL );
// 	cv::namedWindow( windowNameWithBrightnessHigh100, cv::WindowFlags::WINDOW_NORMAL );
// 	cv::namedWindow( windowNameBrightnessLow50, cv::WindowFlags::WINDOW_NORMAL );
// 	cv::namedWindow( windowNameBrightnessLow100, cv::WindowFlags::WINDOW_NORMAL );

	//Show above images inside the created windows.
	cv::imshow( windowNameOriginalImage, image );
// 	cv::imshow( windowNameBrightnessHigh50, imageBrighnessHigh50 );
// 	cv::imshow( windowNameWithBrightnessHigh100, imageBrighnessHigh100 );
// 	cv::imshow( windowNameBrightnessLow50, imageBrighnessLow50 );
// 	cv::imshow( windowNameBrightnessLow100, imageBrighnessLow100 );

	//
	//	Do the Dew!
	//
	do {
		//C:\Users\Hodges\Documents\GitHub\OpenCVTutorials\Common\libs\opencv4.0.0alpha\sources\data\haarcascades
		cv::CascadeClassifier face_cascade;// = cv::CascadeClassifier('haarcascade_frontalface_default.xml')
		bool didLoad = face_cascade.load( "common/libs/opencv4.0.0alpha/sources/data/haarcascades/haarcascade_frontalface_default.xml" );
		if ( !didLoad ) {
			printf( "fuck couldn't load haar cascade for frontal face!\n" );
			break;
		}

		cv::CascadeClassifier eye_cascade;
		//didLoad = eye_cascade.load( "common/libs/opencv4.0.0alpha/sources/data/haarcascades/haarcascade_eye.xml" );
		didLoad = eye_cascade.load( "common/libs/opencv4.0.0alpha/sources/data/haarcascades/haarcascade_lefteye_2splits.xml" );
		if ( !didLoad ) {
			printf( "fuck couldn't load haar cascade for eyes!\n" );
			break;
		}

		//img = cv.imread('sachin.jpg')
		//gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

		cv::Mat grey;
		cv::cvtColor( image, grey, cv::ColorConversionCodes::COLOR_BGR2GRAY );

		std::vector< cv::Rect > faces;
		face_cascade.detectMultiScale( grey, faces );
		printf( "Num faces detected = %i\n", faces.size() );

		int lineThickness = 3;

		// Stupid BGRA format here
		cv::Scalar colorBlue( 255, 0, 0, 255 );
		for ( int i = 0; i < faces.size(); i++ ) {
			cv::rectangle( image, faces[ i ], colorBlue, lineThickness );
		}

		std::vector< cv::Rect > eyes;
		eye_cascade.detectMultiScale( grey, eyes );
		printf( "Num eyes detected = %i\n", eyes.size() );

		cv::Scalar colorGreen( 0, 255, 0, 255 );
		for ( int i = 0; i < eyes.size(); i++ ) {
			cv::rectangle( image, eyes[ i ], colorGreen, lineThickness );
		}

		cv::imshow( windowNameBrightnessHigh50, image );


// 		faces = face_cascade.detectMultiScale(gray, 1.3, 5)
// 			for (x,y,w,h) in faces:
// 		cv.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
// 			roi_gray = gray[y:y+h, x:x+w]
// 			roi_color = img[y:y+h, x:x+w]
// 			eyes = eye_cascade.detectMultiScale(roi_gray)
// 			for (ex,ey,ew,eh) in eyes:
// 		cv.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
// 			cv.imshow('img',img)
// 			cv.waitKey(0)
// 			cv.destroyAllWindows()
	} while ( false );


	cv::waitKey( 0 ); // Wait for any key stroke

	cv::destroyAllWindows(); //destroy all open windows

	return 0;
}
