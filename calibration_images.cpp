#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/opencv.hpp> //cv.h
#include <opencv2/highgui.hpp> //highgui.h
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d_c.h>
#include <stdio.h>
#include <Windows.h>
//CMD prompt run:
//g++ C:\Users\allen\AnxRobotica_2020\calibration_images.cpp -o code.exe

using namespace cv;

int main2()
{
    int numBoards = 2;
    int numCornersHor=7;
    int numCornersVer=6;


    int numSquares = numCornersHor * numCornersVer;
    Size board_sz = Size(numCornersHor, numCornersVer);

    std::vector<std::vector<Point3f>> object_points;
    std::vector<std::vector<Point2f>> image_points;

    std::vector<Point2f>corners;
    int successes = 0;

    Mat image;
    Mat gray_image;
    std::vector<Point3f> obj;
    for (int k = 0; k < numSquares; k++)
        obj.push_back(Point3f(k / numCornersHor, k % numCornersHor, 0.0f));

    char* filepath = new char[100];
    int imgPos = 1;
    int n_images = 2;
    for (int j = 0; j < n_images - 1; j++) {
        sprintf(filepath, "calibration_images\img%i.jpg", imgPos); // change the path to path of image folder
        // loops through img1, img2, img3...
        printf("file read");
        Mat image = imread(filepath, cv::ImreadModes::IMREAD_GRAYSCALE); //flags: https://www.geeksforgeeks.org/python-opencv-cv2-imread-method/
        // capture >> image

        cvtColor(image, gray_image, COLOR_BGR2GRAY);
        bool found = findChessboardCorners(image, board_sz, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if (found)
        {
            cornerSubPix(gray_image, corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(gray_image, board_sz, corners, found);
        }

        imshow("win1", image);
        imshow("win2", gray_image);
        printf("success!");

        // capture >> image;
        int key = waitKey(1);

        if (key == 27) //esc to quit

            return 0;

        if (key == ' ' && found != 0) //spsace and found will store the result
        {
            image_points.push_back(corners);
            object_points.push_back(obj);
            printf("Snap stored!");

        }
        imgPos++;
    }
    Mat intrinsic = Mat(3, 3, CV_32FC1);
    Mat distCoeffs;
    std::vector<Mat> rvecs;
    std::vector<Mat> tvecs;


    intrinsic.ptr<float>(0)[0] = 1; //aspect ratio
    intrinsic.ptr<float>(1)[1] = 1;

    calibrateCamera(object_points, image_points, image.size(), intrinsic, distCoeffs, rvecs, tvecs);
    Mat imageUndistorted;
    while (1)
    {
        //capture >> image;
        undistort(image, imageUndistorted, intrinsic, distCoeffs);

        imshow("win1", image);
        imshow("win2", imageUndistorted);
        waitKey(1);
    }
    //capture.release();

    return 0;

}