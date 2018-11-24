//
//  main.cpp
//
#include <string>
#include <stdio.h>

#include <opencv2/opencv.hpp>

/*
====================================================
MyCallbackForBrightness
====================================================
*/
void MyCallbackForBrightness( int brightnessVal, void * userData ) {
	cv::Mat dst;
	int contrastVal = *( static_cast< int * >( userData ) );

	// Calculating brightness and contrast value
	int brightness = brightnessVal - 50;
	double contrast = contrastVal / 50.0;

	// Calculated contrast and brightness value
	printf( "MyCallbackForBrightness : Contrast = %f, Brightness = %i\n", contrast, brightness );

	//adjust the brightness and contrast
	//src.convertTo(dst, -1, dContrast, iBrightness); 

	// show the brightness and contrast adjusted image
	cv::imshow( "My Window", dst );
}

/*
====================================================
MyCallbackForContrast
====================================================
*/
void MyCallbackForContrast( int contrastVal, void * userData ) {
	cv::Mat dst;
	int brightnessVal = *( static_cast< int * >( userData ) );

	// Calculating brightness and contrast value
	int brightness = brightnessVal - 50;
	double contrast = contrastVal / 50.0;

	// Calculated contrast and brightness value
	printf( "MyCallbackForContrast : Contrast = %f, Brightness = %i\n", contrast, brightness );

	//adjust the brightness and contrast
	//src.convertTo(dst, -1, dContrast, iBrightness); 

	// show the brightness and contrast adjusted image
	cv::imshow( "My Window", dst );
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
	if ( !image.empty() ) {
		printf( "Could not open or find the image\n" );
		cv::waitKey( 0 );
		return -1;
	}

	// Create a window
	cv::namedWindow( "My Window", 1 );

	// Create trackbar to change brightness
 	int iSliderValue1 = 50;
	cv::createTrackbar( "Brightness", "My Window", &iSliderValue1, 100 );
 
 	// Create trackbar to change contrast
 	int iSliderValue2 = 50;
	cv::createTrackbar( "Contrast", "My Window", &iSliderValue2, 100 );

	// Alternative function callback way
// 	int iValueForBrightness = 50;
// 	int iValueForContrast = 50;
// 
// 	//Create track bar to change brightness
// 	cv::createTrackbar( "Brightness", "My Window", &iValueForBrightness, 100, MyCallbackForBrightness, &iValueForContrast );
// 
// 	//Create track bar to change contrast
// 	cv::createTrackbar( "Contrast", "My Window", &iValueForContrast, 100, MyCallbackForContrast, &iValueForBrightness );

	while ( 1 ) {
		//Change the brightness and contrast of the image (For more infomation http://opencv-srf.blogspot.com/2013/07/change-contrast-of-image-or-video.html)
		cv::Mat dst;
		int iBrightness  = iSliderValue1 - 50;
		double dContrast = iSliderValue2 / 50.0;
		image.convertTo( dst, -1, dContrast, iBrightness ); 

		//show the brightness and contrast adjusted image
		cv::imshow("My Window", dst);

		// Wait until user press some key for 50ms
		int iKey = cv::waitKey( 50 );

		//if user press 'ESC' key
		if ( iKey == 27 ) {
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

	return 0;
}
