#include <iostream>
#include "ParallelProcessor.h"
int main()
{
    constexpr int N = 1000000;
    std::vector<int> pixelData(N);
    std::iota(pixelData.begin(), pixelData.end(), 0);
    ParallelProcessor<int> processor(4);

    // 밝기 증가(병렬)
    auto start = std::chrono::high_resolution_clock::now();
    auto brightened = processor.parallel_map(pixelData, [](int pixel)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1)); // 부하 시뮬레이션
        return std::min(255, pixel + 50); 
    });

    auto end = std::chrono::high_resolution_clock::now();
    auto parallelTime = std::chrono::duration<double, std::milli>(end - start).count();

    // 밝기 증가(직렬)
    auto seqStart = std::chrono::high_resolution_clock::now();
    std::vector<int> seqBrightened(N);
    for (size_t i = 0; i < pixelData.size(); ++i)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1)); // 부하 시뮬레이션
        seqBrightened[i] = std::min(255, pixelData[i] + 50);
    }
    auto seqEnd = std::chrono::high_resolution_clock::now();
    auto sequentialTime = std::chrono::duration<double, std::milli>(seqEnd - seqStart).count();

    // ----- 결과 샘플 -----
    std::cout << "brightenedImage[0] = " << brightened[0] << "\n";
    std::cout << "brightenedImage[1] = " << brightened[1] << "\n";
    std::cout << "brightenedImage[100] = " << brightened[100] << "\n";
    std::cout << "brightenedImage[999999] = " << brightened[999999] << "\n";

    // ----- 문자열 변환 -----
    auto pixelStrings = processor.parallel_map(pixelData, [](int pixel)
                                               { return std::string("pixel_") + std::to_string(pixel); });
    std::cout << "\npixelStrings[0] = " << pixelStrings[0] << "\n";
    std::cout << "pixelStrings[1] = " << pixelStrings[1] << "\n";
    std::cout << "pixelStrings[100] = " << pixelStrings[100] << "\n";

    // ----- 제곱 -----
    auto squaredPixels = processor.parallel_map(pixelData, [](int pixel)
                                                { return pixel * pixel; });
    std::cout << "\nsquaredPixels[0] = " << squaredPixels[0] << "\n";
    std::cout << "squaredPixels[1] = " << squaredPixels[1] << "\n";
    std::cout << "squaredPixels[10] = " << squaredPixels[10] << "\n";

    std::cout << "\nProcessing " << N << " elements with 4 threads\n";
    std::cout << "Sequential time: ~" << sequentialTime << "ms\n";
    std::cout << "Parallel time: ~" << parallelTime << "ms\n";
    std::cout << "Speed up: " << sequentialTime / parallelTime << "\n";
    std::cin.get();

}