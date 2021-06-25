#include <opencv2/opencv.hpp> //cv.h
#include <opencv2/highgui.hpp> //highgui.h
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d_c.h>
using namespace cv;

int main()
{
    int numBoards = 0;
    int numCornersHor;
    int numCornersVer;
    
    printf("Enter number of corners along width: "); 
    scanf("%d", &numCornersHor);

    printf("Enter number of corners along height: ");
    scanf("%d", &numCornersVer);

    printf("Enter number of boards: ");
    scanf("%d", &numBoards);

    int numSquares = numCornersHor * numCornersVer;
    Size board_sz = Size(numCornersHor, numCornersVer);

    VideoCapture capture = VideoCapture(0);
'''
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
'''
	std::vector<std::vector<Point3f>> object_points;
	std::vector<std::vector<Point2f>> image_points;
    
    std::vector<Point2f> corners;
    int successes=0;

    Mat image;
    Mat gray_image;
    capture >> image;

    std::vector<Point3f> obj;
    for(int j = 0; j<numSquares; j++)
        obj.push_back(Point3f(j/numCornersHor, j%numCornersHor, 0.0f));

    while (successes < numBoards)
    {
        cvtColor(image, gray_image, CV_BGR2GRAY);
        bool found = findChessboardCorners(image, board_sz, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if(found)
        {
            cornerSubPix(gray_image, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(gray_image, board_sz, corners, found);
        }

        imshow("win1", image);
        imshow("win2", gray_image);

        capture >> image;
        int key = waitKey(1);
        
        if(key==27) //esc to quit

            return 0;

        if(key==' ' && found!=0) //spsace and found will store the result
        {
            image_points.push_back(corners);
            object_points.push_back(obj);

            printf("Snap stored!");

            successes++;

            if(successes>=numBoards)
                break;
        }
    }
    Mat intrinsic = Mat(3, 3, CV_32FC1);
    Mat distCoeffs;
    std::vector<Mat> rvecs;
    std::vector<Mat> tvecs;


    intrinsic.ptr<float>(0)[0] = 1; //aspect ratio
    intrinsic.ptr<float>(1)[1] = 1;
    
    calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);
    Mat imageUndistorted;
    while(1)
    {
        capture >> image;
        undistort(image, imageUndistorted, intrinsic, distCoeffs);

        imshow("win1", image);
        imshow("win2", imageUndistorted);
        waitKey(1);
    }
    capture.release();

    return 0;
}