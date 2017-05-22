//
//  kinect_1.cpp
//  
//
//  Created by 张映艺 on 2017/5/15.
//
//

#include <stdio.h>
#include <iostream>
#include <Kinect.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <sstream>
#include <omp.h>
#pragma comment(lib, "WINMM.LIB")
#pragma comment ( lib, "kinect20.lib" ) 

using namespace std;
using namespace cv;

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

void showImage(int t) {
	string doc = "C:\\Users\\jx\\Desktop\\jpg\\9s0";
	string str;
	string postfix = ".jpg";
	string imagename;

	Mat img;

	for (int i = 1; i < 110; i++) {
		ostringstream oss;
		oss << i;
		str = oss.str();

		if (i < 10) {
			str = "00" + str;
		}
		else if (i < 100) {
			str = "0" + str;
		}
		imagename = doc + str + postfix;
		img = imread(imagename);
		str = "";

		//如果读入图像失败
		if (img.empty())
		{
			fprintf(stderr, "Can not load image \n");
		}

		//显示图像
		namedWindow("image", CV_WINDOW_NORMAL);
		imshow("image", img);

		//此函数等待按键，按键盘任意键就返回
		waitKey(t);
	}
}

int main(){
	string s1,s2;
	float playS = 0.0;
	int imageV = 0;
	ifstream fin("C:\\Users\\jx\\Desktop\\77\\input.txt");

	fin >> s1 >> playS>>s2>>imageV;
	int playSec = playS * 1000;
	int imageT = 1000 / imageV;
	float time = 109 / imageV;

	float xstart = 1.01718;
	float xend = -2.08849;

	HRESULT hResult = S_OK;
	IKinectSensor *kinect;
	GetDefaultKinectSensor(&kinect);
	kinect->Open();
	IBodyFrameSource* bodysource;
	kinect->get_BodyFrameSource(&bodysource);
	IBodyFrameReader* bodyreader;
	bodysource->OpenReader(&bodyreader);
	ICoordinateMapper* coordinatemapper;
	kinect->get_CoordinateMapper(&coordinatemapper);

#pragma omp parallel sections  
	{
#pragma omp section  
		{
			while (1) {
				showImage(imageT);
			}
		}
#pragma omp section  
		{
		while (1) {
			IBodyFrame* bodyframe = nullptr;
			hResult = bodyreader->AcquireLatestFrame(&bodyframe);
			bool tag = false;

			if (SUCCEEDED(hResult))
			{
				IBody* body[BODY_COUNT] = { 0 };
				if (!tag) {
					hResult = bodyframe->GetAndRefreshBodyData(BODY_COUNT, body);
					tag = true;
					if (SUCCEEDED(hResult))
					{
						for (int i = 0; i < BODY_COUNT; i++)
						{
							BOOLEAN tracked = false;
							hResult = body[i]->get_IsTracked(&tracked);
							if (SUCCEEDED(hResult) && tracked)
							{
								Joint joint[JointType_Count];
								hResult = body[i]->GetJoints(JointType_Count, joint);

								if (SUCCEEDED(hResult))
								{
									float len = 0;
									len = xstart - xend;
									float v = 0;
									v = len / time;

									float xposition[7];
									float yposition[7];
									xposition[0] = joint[JointType_Head].Position.X; yposition[0] = joint[JointType_Head].Position.Y;
									xposition[1] = joint[JointType_ShoulderLeft].Position.X; yposition[1] = joint[JointType_ShoulderLeft].Position.Y;
									xposition[2] = joint[JointType_ShoulderRight].Position.X; yposition[2] = joint[JointType_ShoulderRight].Position.Y;
									xposition[3] = joint[JointType_ElbowLeft].Position.X; yposition[3] = joint[JointType_ElbowLeft].Position.Y;
									xposition[4] = joint[JointType_ElbowRight].Position.X; yposition[4] = joint[JointType_ElbowRight].Position.Y;
									xposition[5] = joint[JointType_HandLeft].Position.X; yposition[5] = joint[JointType_HandLeft].Position.Y;
									xposition[6] = joint[JointType_HandRight].Position.X; yposition[6] = joint[JointType_HandRight].Position.Y;

									float temp = 0;
									for (int j = 0; j < 6; j++) {
										for (int t = j + 1; t < 7; t++) {
											if (yposition[j] > yposition[t]) {
												temp = xposition[j];
												xposition[j] = xposition[t];
												xposition[t] = temp;

												temp = yposition[j];
												yposition[j] = yposition[t];
												yposition[t] = temp;
											}
										}
									}

									float maxh = yposition[6];
									float minh = yposition[0];

									float height = maxh - minh;
									float gap = height / 7;
									int level = 0;

									cout << "get\n" << gap << endl;

									for (int j = 0; j < 6; j++) {
										for (int t = j + 1; t < 7; t++) {
											if (xposition[j] < xposition[t]) {
												temp = xposition[j];
												xposition[j] = xposition[t];
												xposition[t] = temp;

												temp = yposition[j];
												yposition[j] = yposition[t];
												yposition[t] = temp;
											}
										}
									}

									int blank = ((xstart - xposition[0]) / v) * 1000;
									Sleep(blank);

									for (int j = 0; j < 7; j++) {
										level = (yposition[j] - minh) / gap;

										/*
										switch (level) {
										case 0: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\1.wav"), NULL, SND_ASYNC | SND_NODEFAULT); //SND_FILENAME | SND_ASYNC
										Sleep(playSec);
										break;
										}
										case 1: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\2.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 2: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\3.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 3: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\4.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 4: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\5.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 5: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\7.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 6: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\7.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 7: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\8.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 8: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\9.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 9: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\10.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 10: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\11.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 11:{
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\12.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 12: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\13.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 13: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\14.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 14: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\15.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 15: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\16.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 16: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\17.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 17: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\18.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 18: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\19.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 19: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\20.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										case 20: {
										PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\20.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
										Sleep(playSec);
										break;
										}
										default: {
										break;
										}
										}
										*/

										if (level == 0) {
											PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\1.wav"), NULL, SND_ASYNC | SND_NODEFAULT); //SND_FILENAME | SND_ASYNC
											Sleep(playSec);
										}
										else if (level == 1) {
											PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\2.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
											Sleep(playSec);
										}
										else if (level == 2) {
											PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\3.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
											Sleep(playSec);
										}
										else if (level == 3) {
											PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\4.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
											Sleep(playSec);
										}
										else if (level == 4) {
											PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\5.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
											Sleep(playSec);
										}
										else if (level == 5) {
											PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\6.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
											Sleep(playSec);
										}
										else if (level == 6 || level == 7) {
											PlaySound(TEXT("C:\\Users\\jx\\Desktop\\77\\7.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
											Sleep(playSec);
										}
									}
									tag = false;

									blank = ((xposition[6] - xend) / v) * 1000;
									Sleep(blank);
								}
							}
						}
					}
					for (int count = 0; count < BODY_COUNT; count++)
					{
						SafeRelease(body[count]);
					}
					SafeRelease(bodyframe);
				}
			}
		}
}
	}

	
	SafeRelease(bodysource);
	SafeRelease(bodyreader);
	SafeRelease(coordinatemapper);

	if (kinect) {
		kinect->Close();
	}
	SafeRelease(kinect);

	destroyAllWindows();

	return 0;
}