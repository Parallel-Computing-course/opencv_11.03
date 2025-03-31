#ifndef VIDEO_PROCESSOR_H
#define VIDEO_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoProcessor {
public:
    bool initialize(const std::string& videoPath);
    void run();
    void release();
    
private:
    cv::VideoCapture videoSource;
};

#endif