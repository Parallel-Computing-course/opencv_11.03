#include "VideoProcessor.h"

int main() {
    VideoProcessor processor;
    const std::string videoFilePath = "input_video.avi";
    
    if (!processor.initialize(videoFilePath)) {
        return -1;
    }
    
    processor.run();
    processor.release();
    
    return 0;
}