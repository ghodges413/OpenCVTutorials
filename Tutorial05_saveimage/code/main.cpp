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
	cv::Mat image = cv::imread( "common/data/photo.jpg" );

	// Check for failure
	if ( image.empty() ) {
		printf( "Could not open or find the image\n" );
		
		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	/*
	Make changes to the image as necessary
	e.g.  
	1. Change brightness/contrast of the image
	2. Smooth/Blur image
	3. Crop the image
	4. Rotate the image
	5. Draw shapes on the image
	*/

	//write the image to a file as JPEG 
	bool didWrite = imwrite( "output/saved.png", image );
	if ( !didWrite ) {
		printf( "Failed to save the image\n" );
		
		// Wait for any keystroke in the window
		cv::waitKey( 0 );
		return -1;
	}

	printf( "Image is successfully saved to a file\n" );

	// Create a window
	const char * windowName = "The Saved Image";
	cv::namedWindow( windowName );

	// Show our image inside the created window.
	cv::imshow( windowName, image );

	// Wait for any keystroke in the window
	cv::waitKey( 0 );

	// destroy the created window
	cv::destroyWindow( windowName );

	return 0;
}
