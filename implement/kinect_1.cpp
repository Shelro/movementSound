//
//  kinect_1.cpp
//  
//
//  Created by 张映艺 on 2017/5/15.
//
//

#include <stdio.h>
#include <iostream>
#include <NuiApi.h>

using namespace std;

int main(){
    //1、初始化NUI，注意这里是USES_SKELETON
    HRESULT hr = NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON);
    if (FAILED(hr)){
        cout<<"NuiInitialize failed"<<endl;
        return hr;
    }
    
    //2、开始读取骨骼跟踪数据
    NUI_SKELETON_FRAME skeletonFrame = {0};  //骨骼帧的定义
    bool bFoundSkeleton = false;

    SkeletonFrameReady(&skeletonFrame);
    for( int i = 0 ; i < NUI_SKELETON_COUNT ; i++ ){
        NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[i].eTrackingState;
        //4.3、Kinect最多检测六个人，但只能跟踪两个人的骨骼，再检查每个“人”（有可能是空，不是人）
        //是否跟踪到了
        if( trackingState == NUI_SKELETON_TRACKED ){
            bFoundSkeleton = true;
        }
    }
    
    if( !bFoundSkeleton ){
        //continue;
        cout<<"没有检测到骨骼";
    }
            
    //4.4、平滑骨骼帧，消除抖动
    NuiTransformSmooth(&skeletonFrame, NULL);
    
    for( int i = 0 ; i < NUI_SKELETON_COUNT ; i++ ){
    // Show skeleton only if it is tracked, and the center-shoulder joint is at least inferred.
    //断定是否是一个正确骨骼的条件：骨骼被跟踪到并且肩部中心（颈部位置）必须跟踪到。
    if( skeletonFrame.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED &&
    skeletonFrame.SkeletonData[i].eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_SHOULDER_CENTER] != NUI_SKELETON_POSITION_NOT_TRACKED){
        float fx, fy;
        //拿到所有跟踪到的关节点的坐标，并转换为我们的深度空间的坐标，因为我们是在深度图像中
        //把这些关节点标记出来的
        //NUI_SKELETON_POSITION_COUNT为跟踪到的一个骨骼的关节点的数目，为20
        /*
        for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++){
            NuiTransformSkeletonToDepthImage(skeletonFrame.SkeletonData[i].SkeletonPositions[j], &fx, &fy );
            skeletonPoint[i][j].x = (int)fx;
            skeletonPoint[i][j].y = (int)fy;
        }*/
                    
        for (int j=0; j<NUI_SKELETON_POSITION_COUNT ; j++){
            if (skeletonFrame.SkeletonData[i].eSkeletonPositionTrackingState[j] != NUI_SKELETON_POSITION_NOT_TRACKED){//跟踪点一用有三种状态：1没有被跟踪到，2跟踪到，3根据跟踪到的估计到
                //circle(skeletonImage, skeletonPoint[i][j], 3, cvScalar(0, 255, 255), 1, 8, 0);
                tracked[i] = TRUE;
            }
        }
        
    }
        
    double maxh = pointSet[NUI_SKELETON_POSITION_HEAD].y;
    double minh = pointSet[NUI_SKELETON_POSITION_HIP_CENTER].y;
    
    double height = maxh - minh;
    double gap = height / 20;
    int level = 0;
        
    for (int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++){
        level = (skeletonFrame.SkeletonData[i].SkeletonPositions[j].y - minh) / gap;
        
        switch (level){
            case 0 : //play music1
            case 1 : //play music2
            case 2 : //play music1
            case 3 : //play music2
            case 4 : //play music1
            case 5 : //play music2
            case 6 : //play music1
            case 7 : //play music2
            case 8 : //play music1
            case 9 : //play music2
            case 10 : //play music1
            case 11 : //play music2
            case 12 : //play music1
            case 13 : //play music2
            case 14 : //play music1
            case 15 : //play music2
            case 16 : //play music1
            case 17 : //play music2
            case 18 : //play music1
            case 19 : //play music2
        }
    }
    
    
    //5、关闭NUI链接
    NuiShutdown();
    return 0;
}
}
