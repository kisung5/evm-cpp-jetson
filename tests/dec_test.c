#include <iostream>

#include "opencv2/opencv_modules.hpp"

#if defined(HAVE_OPENCV_CUDACODEC)

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include <opencv2/core.hpp>
// #include <opencv2/core/opengl.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, const char* argv[])
{
    if (argc != 2)
        return -1;

    // std::cout << cv::getBuildInformation() << std::endl;

    const std::string fname(argv[1]);

    // cv::namedWindow("CPU", cv::WINDOW_NORMAL);
    // cv::namedWindow("GPU", cv::WINDOW_OPENGL);
    // cv::cuda::setGlDevice();

    cv::Mat frame;
    cv::VideoCapture reader(fname);

    std::cout << "CPU SET" << std::endl;
    
    // const char *gst =   "rtspsrc location=rtsp://184.72.239.149/vod/mp4:BigBuckBunny_115k.mov ! application/x-rtp, media=(string)video "
	// 		    "! decodebin    ! video/x-raw, format=(string)NV12 "
	// 		    "! videoconvert ! video/x-raw, format=(string)BGR "
	// 		    "! appsink";

    // cv::cuda::GpuMat d_frame;
    cv::Mat d_frame;

    std::string str = "filesrc location=" + fname + 
        " ! qtdemux ! queue ! h264parse ! nvv4l2decoder ! nvvidconv ! video/x-raw,format=BGRx ! queue ! videoconvert ! queue ! video/x-raw,format=BGR ! appsink";

    cv::VideoCapture d_reader(str, cv::CAP_GSTREAMER);

    std::cout << "GPU SET" << std::endl;

    cv::TickMeter tm;
    std::vector<double> cpu_times;
    std::vector<double> gpu_times;

    int gpu_frame_count=0, cpu_frame_count=0;

    std::cout << "CPU READ" << std::endl;
    for (;;)
    {
        tm.reset(); tm.start();
        if (!reader.read(frame))
            break;
        tm.stop();
        cpu_times.push_back(tm.getTimeMilli());
        cpu_frame_count++;

        // cv::imshow("CPU", frame);

        // if (cv::waitKey(3) > 0)
        //     break;
    }

    std::cout << "GPU READ" << std::endl;
    for (;;)
    {
        tm.reset(); tm.start();
        if (!d_reader.read(d_frame))
            break;
        tm.stop();
        gpu_times.push_back(tm.getTimeMilli());
        gpu_frame_count++;

        // cv::imshow("GPU", d_frame);

        // if (cv::waitKey(3) > 0)
        //     break;
    }

    if (!cpu_times.empty() && !gpu_times.empty())
    {
        std::cout << std::endl << "Results:" << std::endl;

        std::sort(cpu_times.begin(), cpu_times.end());
        std::sort(gpu_times.begin(), gpu_times.end());

        double cpu_avg = std::accumulate(cpu_times.begin(), cpu_times.end(), 0.0) / cpu_times.size();
        double gpu_avg = std::accumulate(gpu_times.begin(), gpu_times.end(), 0.0) / gpu_times.size();

        std::cout << "CPU : Avg : " << cpu_avg << " ms FPS : " << 1000.0 / cpu_avg << " Frames " << cpu_frame_count << std::endl;
        std::cout << "GPU : Avg : " << gpu_avg << " ms FPS : " << 1000.0 / gpu_avg << " Frames " << gpu_frame_count << std::endl;
    }

    return 0;
}

#else

int main()
{
    std::cout << "OpenCV was built without CUDA Video decoding support\n" << std::endl;
    return 0;
}

#endif