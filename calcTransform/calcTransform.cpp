// calcTransform.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat drawCross(Mat & img,int blockSize = 100) {
	for (int j = 0; j < img.rows; j++)
	{
		if (j % blockSize == (blockSize - 1))
		{
			uchar *data = img.ptr<uchar>(j);
			for (int i = 0; i < img.cols; i++)
			{
				data[3 * i + 1] = 255;
			}
		}
		else
		{
			for (int i = 0; i < img.cols; i++)
			{
				if (i % blockSize == (blockSize - 1))
				{
					uchar *data = img.ptr<uchar>(j);
					data[3 * i + 1] = 255;
				}
			}
		}
	}
	return img;
}
// 透视变换9月份稳定版firstframe.jpg
#if 0
int main()
{
	Mat img = imread("firstframe.jpg");

	int img_height = img.rows;
	int img_width = img.cols;
	//resize(img, img, Size(img.cols / 4, img.rows / 4));
	vector<Point2f> corners(4);
	corners[0] = Point2f(850, 210);  //左上
	corners[1] = Point2f(189, 940);  //左下
	corners[2] = Point2f(1130, 212);  //右上
	corners[3] = Point2f(1770, 1069);  //右下

	vector<Point2f> corners_trans(4);
	corners_trans[0] = Point2f(0, 590);
	corners_trans[1] = Point2f(2070, 590);
	corners_trans[2] = Point2f(4, 200);
	corners_trans[3] = Point2f(2100, 200);

	Mat transform = getPerspectiveTransform(corners, corners_trans);
	cout << transform << endl;
	Mat img_trans = Mat::zeros(1000, 2100, CV_8UC3);
	warpPerspective(img, img_trans, transform, img_trans.size());
	Point2f center;
	center.x = 800.;
	center.y = 350.;

	//circle(img, center, 7, Scalar(255, 0, 0), -1);
	circle(img, center, 7, Scalar(255, 0, 0), -1);
	double * px0 = transform.ptr<double>(0);
	double * px1 = transform.ptr<double>(1);
	double * px2 = transform.ptr<double>(2);
	Point2f center0;
	center0.x = (center.x * px0[0] + center.y * px0[1] + px0[2]) / (center.x * px2[0] + center.y * px2[1] + px2[2]);
	center0.y = (center.x * px1[0] + center.y * px1[1] + px1[2]) / (center.x * px2[0] + center.y * px2[1] + px2[2]);
	
	//cout << center.x * px0[0] + center.y * px0[1] + px0[2] << "  " << center.x * px2[0] + center.y * px2[1] + px2[2] << endl;
	circle(img_trans, center0, 7, Scalar(0, 255, 0), -1);
	resize(img_trans, img_trans, Size(img_trans.cols / 1.5, img_trans.rows / 1.5));
	resize(img, img, Size(img.cols / 1.5, img.rows / 1.5));
	imshow("img", img);
	imshow("result", img_trans);
	waitKey(0);
	//system("pause");
	return 0;
}

#endif


//10月份测试版
#if 1
int main()
{
	Mat img = imread("112.jpg");

	vector<Point2f> corners(4);
	corners[0] = Point2f(169, 164);  //左上
	corners[1] = Point2f(562, 763);  //左下
	corners[2] = Point2f(616, 48);  //右上
	corners[3] = Point2f(1084, 546);  //右下

	for (int i = 0; i < corners.size(); i++)
		circle(img, corners[i], 5, Scalar(0, 0, 255), -1);
	
	int rowblockNum = 3;
	int colblockNum = 2;
	int scalePerPixel = 2;
	int left = 480;
	int up = 320;
	vector<Point2f> corners_trans(4);
	corners_trans[0] = Point2f(left, up);  // 左下
	corners_trans[1] = Point2f(left, up+ 40 * rowblockNum * scalePerPixel);  //右下
	corners_trans[2] = Point2f(left + 40 * colblockNum * scalePerPixel, up);     //左上
	corners_trans[3] = Point2f(left + 40 * colblockNum * scalePerPixel, up + 40 * rowblockNum * scalePerPixel);   //右上

	Mat transform = getPerspectiveTransform(corners, corners_trans);
	cout << transform << endl;
	Mat img_trans = Mat::zeros(1080, 1920, CV_8UC3);
	
	warpPerspective(img, img_trans, transform, img_trans.size());

	/*Point2f center;
	center.x = 800.;
	center.y = 350.;
	double * px0 = transform.ptr<double>(0);
	double * px1 = transform.ptr<double>(1);
	double * px2 = transform.ptr<double>(2);
	Point2f center0;
	center0.x = (center.x * px0[0] + center.y * px0[1] + px0[2]) / (center.x * px2[0] + center.y * px2[1] + px2[2]);
	center0.y = (center.x * px1[0] + center.y * px1[1] + px1[2]) / (center.x * px2[0] + center.y * px2[1] + px2[2]);*/

	imshow("img", img);
	//img_trans = drawCross(img_trans, 40);
	imshow("result", img_trans);
	imwrite("112trans.jpg", img_trans);
	waitKey(0);
	//system("pause");
	return 0;
}
#endif


//11月份测试版
#if 0
int main()
{
	double buffer[216] = { -1.44414197, 57.92899679, -18382.4639275,-0.000263781, 0.01973591,800.0,-4.88313192975, 6.9290561117, 7404.3825287,
		0.0266114199,12.49875,-1793.61905679,0.0000532228,0.0053939,800.0,-1.40798789,1.68514313,2606.724,
		-0.518201725,17.39,-1909.47555,-0.0001605237,0.007575767,800.0,-1.83142386,2.45142133,3366.50673723,
		-0.518201725,17.39,-1909.47555,-0.0001605237,0.007575767,800.0,-1.83142386,2.45142133,3366.50673723,
		-0.518201725,17.39,-1909.47555,-0.0001605237,0.007575767,800.0,-1.83142386,2.45142133,3366.50673723,
		-0.518201725,17.39,-1909.47555,-0.0001605237,0.007575767,800.0,-1.83142386,2.45142133,3366.50673723,
		-0.518201725,17.39,-1909.47555,-0.0001605237,0.007575767,800.0,-1.83142386,2.45142133,3366.50673723,
		-0.518201725,17.39,-1909.47555,-0.0001605237,0.007575767,800.0,-1.83142386,2.45142133,3366.50673723,
		-0.2713409211074551, 15.36501250157372, -1995.390547498214,-0.00008966774, 0.0063403036,800.0,-1.136913481875062, 2.498340439183149, 1568.091473,
		-0.2779434615846037, -18.25687245060054, 7262.007521567891,-0.00009377, -0.00720688,800.0,1.099057615813086, -3.578727683041722, -611.4883,
		-0.081892,-6.9132747443,3021.7135169,-0.0000171762239,-0.0032864587,800.0,0.466817,-1.66715891,87.3929725,
		0.051448838219,-4.64555855,2732.43,0.0000143627296,-0.00206541,800.0,0.3540213867,-0.763380192,36.031329899,
		-0.0488131651688446, -15.53271955932264, 4150.918252762291,-0.000028835, -0.00718818,800.0,1.146632705927627, -4.365251309918572, -469.3922983,
		-0.227381627,-6.47518818,2902.73044,-0.000111414,-0.00287076861,800.0,0.42571801,-1.374132188,10.51953837,
		-0.2108643,-5.82502266,2823.4098376,-0.00011191,-0.002651447,800.0,0.3970225127,-1.4260879,105.5318911,
		-0.1264449, -13.85608988, 3653.54501,-0.0001422989, -0.00656,800.0,1.006925313753079, -3.178137843095292, -542.49945232,
		0.025961326, -19.61981928, 4396.428568,-0.00004705378894, -0.00928152,800.0,1.6251971, -4.445396912, -1090.856,
		-0.13035819,-11.6749743,3546.5059748,-0.000053936225,-0.005293468,800.0,0.8732291,-2.72468659,-330.147242265,
		-0.01734116,-25.208992469,4982.92255154,-0.0000525489719,-0.011415,800.0,1.91635,-6.2968402,-1301.14047,
		0.847713,-31.6271298,6319.84,0.0004329,-0.0146749,800.0,2.57263888,-7.137054368,-1619.3869,
		0.246923261,-26.1324,5295.16343899,0.00017512288,-0.012285466,800.0,2.224647949,-5.3890293,-1518.524187917,
		-0.4779101901787682, -24.47035534030185, 5730.041651238,-0.0002287001523675897, -0.011025186,800.0,1.859411878561688, -4.757235149206822, -1389.311295698737,
		0.246923261,-26.1324,5295.16343899,0.00017512288,-0.012285466,800.0,2.224647949,-5.3890293,-1518.524187917,
		0.00958638,-21.223159,4641.2059697686,0.000029049636,-0.010104,800.0,1.669546,-5.6781561978,-933.94126377 };
	Mat transform;
	transform.create(3, 3, CV_32FC1);
	for (int k = 1; k < 25; k++)
	{
		char path[64];
		sprintf(path, "%s%d%s", "C:\\Users\\handewei\\Desktop\\1080p高速视频\\", k, ".bmp");
		Mat img = imread(path);
		if (img.empty())
		{
			continue;
		}
		int img_height = img.rows;
		int img_width = img.cols;

		vector<Point2f> corners(4);
		corners[0] = Point2f(898, 241);  //左上
		corners[1] = Point2f(860, 1015);  //左下
		corners[2] = Point2f(1034, 241);  //右上
		corners[3] = Point2f(1738, 1001);  //右下
		vector<Point2f> corners_trans(4);
		corners_trans[0] = Point2f(330, 570);  // 左下
		corners_trans[1] = Point2f(1830, 570);  //右下
		corners_trans[2] = Point2f(330, 410);     //左上
		corners_trans[3] = Point2f(1830, 410);   //右上
		transform = getPerspectiveTransform(corners, corners_trans);

		transform.ptr<double>(0)[0] = buffer[(k * 9 - 9)];
		transform.ptr<double>(0)[1] = buffer[(k * 9 - 9) + 1];
		transform.ptr<double>(0)[2] = buffer[(k * 9 - 9) + 2];
		transform.ptr<double>(1)[0] = buffer[(k * 9 - 9) + 6];
		transform.ptr<double>(1)[1] = buffer[(k * 9 - 9) + 7];
		transform.ptr<double>(1)[2] = buffer[(k * 9 - 9) + 8];
		transform.ptr<double>(2)[0] = buffer[(k * 9 - 9) + 3];
		transform.ptr<double>(2)[1] = buffer[(k * 9 - 9) + 4];

		Mat img_trans = Mat::zeros(1000, 1900, CV_8UC3);
		warpPerspective(img, img_trans, transform, img_trans.size());
		Point2f center;
		center.x = 800.;
		center.y = 350.;

		//circle(img, center, 7, Scalar(255, 0, 0), -1);
		//circle(img, center, 7, Scalar(255, 0, 0), -1);
		double * px0 = transform.ptr<double>(0);
		double * px1 = transform.ptr<double>(1);
		double * px2 = transform.ptr<double>(2);
		Point2f center0;
		center0.x = (center.x * px0[0] + center.y * px0[1] + px0[2]) / (center.x * px2[0] + center.y * px2[1] + px2[2]);
		center0.y = (center.x * px1[0] + center.y * px1[1] + px1[2]) / (center.x * px2[0] + center.y * px2[1] + px2[2]);

		//cout << center.x * px0[0] + center.y * px0[1] + px0[2] << "  " << center.x * px2[0] + center.y * px2[1] + px2[2] << endl;
		//circle(img_trans, center0, 7, Scalar(0, 255, 0), -1);
		//resize(img_trans, img_trans, Size(img_trans.cols / 1.5, img_trans.rows / 1.5));
		//resize(img, img, Size(img.cols / 1.5, img.rows / 1.5));
		
		//imshow("img", img);
		img_trans = drawCross(img_trans);
		cout << path << endl;
		//resize(img_trans, img_trans, Size(img_trans.rows/2, img_trans.cols/2));
		imshow("result", img_trans);
		waitKey(0);
	}
	return 0;
}
#endif


#if 0
int main() 
{
	VideoCapture cap;
	cap.open("C:\\Users\\handewei\\Desktop\\1080p高速视频\\4.mp4");
	Mat frame;
	while (true) 
	{
		cap >> frame;
		imshow("win", frame);
		imwrite("C:\\Users\\handewei\\Desktop\\1080p高速视频\\4.bmp", frame);
		waitKey(0);
		//break;
	}
	return 0;
}
#endif