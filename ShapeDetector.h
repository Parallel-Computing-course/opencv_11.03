#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

#include <opencv2/opencv.hpp>
#include <vector>

class ShapeDetector {
public:
    void processFrame(const cv::Mat& inputFrame, cv::Mat& outputFrame);
    
private:
    bool isQuadrilateral(const std::vector<cv::Point>& contour, double maxPerimeter) const;
    
    cv::Mat processedImage;
    cv::Mat intermediateImage;
    std::vector<std::vector<cv::Point>> detectedContours;
    std::vector<cv::Vec4i> contourHierarchy;
};

#endif