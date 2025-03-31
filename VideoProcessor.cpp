#include "VideoProcessor.h"
#include "ShapeDetector.h"
#include <iostream>

bool VideoProcessor::initialize(const std::string& videoPath) {
    videoSource.open(videoPath);
    if (!videoSource.isOpened()) {
        std::cerr << "Failed to open video source" << std::endl;
        return false;
    }
    cv::namedWindow("Detection Results", cv::WINDOW_NORMAL);
    return true;
}

void VideoProcessor::run() {
    ShapeDetector detector;
    cv::Mat currentFrame;
    cv::Mat processedFrame;
    
    while (true) {
        videoSource >> currentFrame;
        if (currentFrame.empty()) break;
        
        detector.processFrame(currentFrame, processedFrame);
        cv::imshow("Detection Results", processedFrame);
        
        if (cv::waitKey(1) == 27) break;
    }
}

void VideoProcessor::release() {
    videoSource.release();
    cv::destroyAllWindows();
}