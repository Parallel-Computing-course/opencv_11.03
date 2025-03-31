#include "ShapeDetector.h"

void ShapeDetector::processFrame(const cv::Mat& inputFrame, cv::Mat& outputFrame) {
    cv::cvtColor(inputFrame, intermediateImage, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(intermediateImage, processedImage, cv::Size(5, 5), 0);
    cv::Canny(processedImage, intermediateImage, 50, 150, 3);
    cv::findContours(intermediateImage, detectedContours, contourHierarchy, 
                    cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    outputFrame = inputFrame.clone();
    
    for (const auto& contour : detectedContours) {
        if (isQuadrilateral(contour, 900.0)) {
            double perimeter = cv::arcLength(contour, true);
            std::vector<cv::Point> approximated;
            cv::approxPolyDP(contour, approximated, 0.02 * perimeter, true);
            
            cv::drawContours(outputFrame, std::vector<std::vector<cv::Point>>{approximated}, 
                           -1, cv::Scalar(0, 255, 0), 2);
            cv::putText(outputFrame, "quadrilateral", approximated[0], 
                       cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
        }
    }
}

bool ShapeDetector::isQuadrilateral(const std::vector<cv::Point>& contour, double maxPerimeter) const {
    double perimeter = cv::arcLength(contour, true);
    if (perimeter >= maxPerimeter) return false;
    
    std::vector<cv::Point> approximated;
    cv::approxPolyDP(contour, approximated, 0.02 * perimeter, true);
    
    return approximated.size() == 4 && cv::isContourConvex(approximated);
}