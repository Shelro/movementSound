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
#include <Windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <sstream>
#include <omp.h>
#include <vector>
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

<<<<<<< HEAD
void showImage(int t, int &c, int iv, int time) {
	string doc = "C:/Users/Administrator/Desktop/jpg/a0";
=======
void showImage(int t, int &c) {
	string doc = "C:\\Users\\jx\\Desktop\\jpg\\9s0";
>>>>>>> origin/master
	string str;
	string postfix = ".jpg";
	string imagename;

	Mat img;

	for (int i = 1; i < 9*iv+1; i++) {
		ostringstream oss;
		oss << i;
		str = oss.str();

		c = i;

<<<<<<< HEAD
		if (c > 2*time*iv) {
			c -= 2*time*iv;
		}
		else if (c > time*iv) {
			c -= time*iv;
		}

=======
>>>>>>> origin/master
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

void playBodySound(int playSec, int level) {
	switch (level) {
	case 0: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\1.wav"), NULL, SND_ASYNC | SND_NODEFAULT); //SND_FILENAME | SND_ASYNC
		Sleep(playSec);
		break;
	}
	case 1: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\2.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 2: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\3.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 3: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\4.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 4: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\5.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 5: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\7.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 6: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\7.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 7: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\8.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 8: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\9.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 9: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\10.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 10: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\11.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 11: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\12.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 12: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\13.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 13: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\14.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 14: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\15.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 15: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\16.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 16: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\17.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 17: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\18.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 18: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\19.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 19: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\20.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	case 20: {
		PlaySound(TEXT("C:\\Users\\Administrator\\Desktop\\77\\20.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
		Sleep(playSec);
		break;
	}
	default: {
		break;
	}
	}
}

int main() {
	string s1, s2, s3, s4;
	float playS = 0.0;
	float playS2 = 0.0;
	int imageV = 0;
	ifstream fin("C:\\Users\\Administrator\\Desktop\\77\\input.txt");

	float time;
	fin >> s1 >> playS >> s2 >> playS2 >> s3 >> imageV>>s4>>time;
	int playSec = playS * 1000;
	int playSec2 = playS2 * 1000;
	int imageT = 1000 / imageV;

	float xstart = 1.35;
	float xend = -1.29;

	int count = 0;
	int &cou = count;

<<<<<<< HEAD
	HRESULT hResult1 = S_OK;
	HRESULT hResult2 = S_OK;
	HRESULT hResult3 = S_OK;
=======
	HRESULT hResult = S_OK;
>>>>>>> origin/master
	IKinectSensor *kinect;
	GetDefaultKinectSensor(&kinect);
	kinect->Open();
	IBodyFrameSource* bodysource;
	kinect->get_BodyFrameSource(&bodysource);
	IBodyFrameReader* bodyreader;
	bodysource->OpenReader(&bodyreader);


#pragma omp parallel sections  
	{
#pragma omp section  
		{
			while (1) {
<<<<<<< HEAD
				showImage(imageT, cou, imageV, time);
=======
				showImage(imageT, cou);
>>>>>>> origin/master
			}
		}
#pragma omp section  
		{
			while (1) {
				IBodyFrame* bodyframe = nullptr;
				hResult1 = bodyreader->AcquireLatestFrame(&bodyframe);
				bool tag = false;

				if (SUCCEEDED(hResult1))
				{
					IBody* body[BODY_COUNT] = { 0 };
					if (!tag) {
						hResult1 = bodyframe->GetAndRefreshBodyData(BODY_COUNT, body);
						tag = true;
						vector<int> bodyVec;
						if (SUCCEEDED(hResult1))
						{
							for (int i = 0; i < BODY_COUNT; i++)
							{
								BOOLEAN tracked = false;
								hResult1 = body[i]->get_IsTracked(&tracked);
								if (SUCCEEDED(hResult1) && tracked)
								{
									bodyVec.push_back(i);
								}
							}
							switch (bodyVec.size())
							{
							case 1:
							{
								Joint joint[JointType_Count];
								hResult1 = body[bodyVec[0]]->GetJoints(JointType_Count, joint);

								if (SUCCEEDED(hResult1))
								{
									float len = 0;
									len = xstart - xend;
									float v = 0;
									v = len / time;

<<<<<<< HEAD
									float cgap = len / (time*imageV);
=======
									float cgap = len / 109;
>>>>>>> origin/master

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
									float gap = height / 20;
									int level = 0;

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

									int blank = 0;
									if ((count * cgap) < (xstart - xposition[0])) {
<<<<<<< HEAD
										blank = ((xstart - xposition[0] - count*cgap) / v) * 1000 + 50;
										//cout << blank << endl << xposition[0] << endl;
										Sleep(blank);

										cout << "get\n" << bodyVec.size() <<endl<< joint[JointType_Head].Position.X << endl;

										for (int j = 0; j < 7; j++) {
											level = (yposition[j] - minh) / gap;

											playSec += abs(rand()%150);

											cout << playSec << endl;

											playBodySound(playSec, level);

											playSec = playS * 1000;
										}
										//cout << alltime;
										tag = false;

										/*
										blank = 0;
										blank = ((xposition[0] - xend) / v) * 1000 - alltime;
										cout << blank;
										//cout << blank<<endl<< xposition[6]<<endl;
										Sleep(blank);*/
									}
								}
								break;
							}
							case 2:
							{
								Joint joint1[JointType_Count];
								Joint joint2[JointType_Count];
								hResult1 = body[bodyVec[0]]->GetJoints(JointType_Count, joint1);
								hResult2 = body[bodyVec[1]]->GetJoints(JointType_Count, joint2);

								if (SUCCEEDED(hResult1) && SUCCEEDED(hResult2))
								{
									float len = 0;
									len = xstart - xend;
									float v = 0;
									v = len / time;

									float cgap = len / 109;

									float xposition[14];
									float yposition[14];
									xposition[0] = joint1[JointType_Head].Position.X; yposition[0] = joint1[JointType_Head].Position.Y;
									xposition[1] = joint1[JointType_ShoulderLeft].Position.X; yposition[1] = joint1[JointType_ShoulderLeft].Position.Y;
									xposition[2] = joint1[JointType_ShoulderRight].Position.X; yposition[2] = joint1[JointType_ShoulderRight].Position.Y;
									xposition[3] = joint1[JointType_ElbowLeft].Position.X; yposition[3] = joint1[JointType_ElbowLeft].Position.Y;
									xposition[4] = joint1[JointType_ElbowRight].Position.X; yposition[4] = joint1[JointType_ElbowRight].Position.Y;
									xposition[5] = joint1[JointType_HandLeft].Position.X; yposition[5] = joint1[JointType_HandLeft].Position.Y;
									xposition[6] = joint1[JointType_HandRight].Position.X; yposition[6] = joint1[JointType_HandRight].Position.Y;
									xposition[7] = joint2[JointType_Head].Position.X; yposition[7] = joint2[JointType_Head].Position.Y;
									xposition[8] = joint2[JointType_ShoulderLeft].Position.X; yposition[8] = joint2[JointType_ShoulderLeft].Position.Y;
									xposition[9] = joint2[JointType_ShoulderRight].Position.X; yposition[9] = joint2[JointType_ShoulderRight].Position.Y;
									xposition[10] = joint2[JointType_ElbowLeft].Position.X; yposition[10] = joint2[JointType_ElbowLeft].Position.Y;
									xposition[11] = joint2[JointType_ElbowRight].Position.X; yposition[11] = joint2[JointType_ElbowRight].Position.Y;
									xposition[12] = joint2[JointType_HandLeft].Position.X; yposition[12] = joint2[JointType_HandLeft].Position.Y;
									xposition[13] = joint2[JointType_HandRight].Position.X; yposition[13] = joint2[JointType_HandRight].Position.Y;

									float temp = 0;
									for (int j = 0; j < 13; j++) {
										for (int t = j + 1; t < 14; t++) {
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

									float maxh = yposition[13];
									float minh = yposition[0];

									float height = maxh - minh;
									float gap = height / 20;
									int level = 0;

									for (int j = 0; j < 13; j++) {
										for (int t = j + 1; t < 14; t++) {
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

									int blank = 0;
									if ((count * cgap) < (xstart - xposition[0])) {
										blank = ((xstart - xposition[0] - count*cgap) / v) * 1000;
										Sleep(blank);

										cout << "get\n" << bodyVec.size() << endl;

										for (int j = 0; j < 14; j++) {
											level = (yposition[j] - minh) / gap;

											playBodySound(playSec2, level);
										}
										tag = false;

										blank = ((xposition[13] - xend) / v) * 1000;
										Sleep(blank);
									}
								}
								break;
							}
							/*
							case 3:
							{
								Joint joint1[JointType_Count];
								Joint joint2[JointType_Count];
								Joint joint3[JointType_Count];
								hResult1 = body[0]->GetJoints(JointType_Count, joint1);
								hResult1 = body[1]->GetJoints(JointType_Count, joint2);
								hResult2 = body[2]->GetJoints(JointType_Count, joint3);

								if (SUCCEEDED(hResult1) && SUCCEEDED(hResult2) && SUCCEEDED(hResult3))
								{
									float len = 0;
									len = xstart - xend;
									float v = 0;
									v = len / time;

									float cgap = len / 109;

									float xposition[21];
									float yposition[21];
									xposition[0] = joint1[JointType_Head].Position.X; yposition[0] = joint1[JointType_Head].Position.Y;
									xposition[1] = joint1[JointType_ShoulderLeft].Position.X; yposition[1] = joint1[JointType_ShoulderLeft].Position.Y;
									xposition[2] = joint1[JointType_ShoulderRight].Position.X; yposition[2] = joint1[JointType_ShoulderRight].Position.Y;
									xposition[3] = joint1[JointType_ElbowLeft].Position.X; yposition[3] = joint1[JointType_ElbowLeft].Position.Y;
									xposition[4] = joint1[JointType_ElbowRight].Position.X; yposition[4] = joint1[JointType_ElbowRight].Position.Y;
									xposition[5] = joint1[JointType_HandLeft].Position.X; yposition[5] = joint1[JointType_HandLeft].Position.Y;
									xposition[6] = joint1[JointType_HandRight].Position.X; yposition[6] = joint1[JointType_HandRight].Position.Y;
									xposition[7] = joint2[JointType_Head].Position.X; yposition[7] = joint2[JointType_Head].Position.Y;
									xposition[8] = joint2[JointType_ShoulderLeft].Position.X; yposition[8] = joint2[JointType_ShoulderLeft].Position.Y;
									xposition[9] = joint2[JointType_ShoulderRight].Position.X; yposition[9] = joint2[JointType_ShoulderRight].Position.Y;
									xposition[10] = joint2[JointType_ElbowLeft].Position.X; yposition[10] = joint2[JointType_ElbowLeft].Position.Y;
									xposition[11] = joint2[JointType_ElbowRight].Position.X; yposition[11] = joint2[JointType_ElbowRight].Position.Y;
									xposition[12] = joint2[JointType_HandLeft].Position.X; yposition[12] = joint2[JointType_HandLeft].Position.Y;
									xposition[13] = joint2[JointType_HandRight].Position.X; yposition[13] = joint2[JointType_HandRight].Position.Y;
									xposition[14] = joint3[JointType_Head].Position.X; yposition[14] = joint3[JointType_Head].Position.Y;
									xposition[15] = joint3[JointType_ShoulderLeft].Position.X; yposition[15] = joint3[JointType_ShoulderLeft].Position.Y;
									xposition[16] = joint3[JointType_ShoulderRight].Position.X; yposition[16] = joint3[JointType_ShoulderRight].Position.Y;
									xposition[17] = joint3[JointType_ElbowLeft].Position.X; yposition[17] = joint3[JointType_ElbowLeft].Position.Y;
									xposition[18] = joint3[JointType_ElbowRight].Position.X; yposition[18] = joint3[JointType_ElbowRight].Position.Y;
									xposition[19] = joint3[JointType_HandLeft].Position.X; yposition[19] = joint3[JointType_HandLeft].Position.Y;
									xposition[20] = joint3[JointType_HandRight].Position.X; yposition[20] = joint3[JointType_HandRight].Position.Y;

									float temp = 0;
									for (int j = 0; j < 20; j++) {
										for (int t = j + 1; t < 21; t++) {
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

									float maxh = yposition[20];
									float minh = yposition[0];

									float height = maxh - minh;
									float gap = height / 20;
									int level = 0;

									for (int j = 0; j < 20; j++) {
										for (int t = j + 1; t < 21; t++) {
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

									int blank = 0;
									if ((count * cgap) < (xstart - xposition[0])) {
										blank = ((xstart - xposition[0] - count*cgap) / v) * 1000;
										Sleep(blank);

										cout << "get\n" << bodyVec.size() << endl;

										for (int j = 0; j < 21; j++) {
											level = (yposition[j] - minh) / gap;

											playBodySound(playSec, level);
										}
										tag = false;

										blank = ((xposition[20] - xend) / v) * 1000;
										Sleep(blank);
									}
=======
										blank = ((xstart - xposition[0] - count*cgap) / v) * 1000;
										Sleep(blank);

										for (int j = 0; j < 7; j++) {
											level = (yposition[j] - minh) / gap;

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
											case 11: {
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
										}
										tag = false;

										blank = ((xposition[6] - xend) / v) * 1000;
										Sleep(blank);
									}                                                                                                                                                                                                                                                                                                                      
>>>>>>> origin/master
								}
								break;
							}*/
							default: {
								break;
							}
							}
							for (int bc = 0; bc < bodyVec.size(); bc++)
							{
								bodyVec.pop_back();
							}
						}
					}
					for (int bcount = 0; bcount < BODY_COUNT; bcount++)
					{
						SafeRelease(body[bcount]);
					}
				SafeRelease(bodyframe);
				}
			}
		}
	}


	SafeRelease(bodysource);
	SafeRelease(bodyreader);

	if (kinect) {
		kinect->Close();
	}
	SafeRelease(kinect);

	return 0;
}