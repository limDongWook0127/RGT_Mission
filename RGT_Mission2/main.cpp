#include <iostream>
#include <numeric>
#include <algorithm>
#include "CircularBuffer.h"

int main()
{
    CircularBuffer<double> tempBuffer(5);

    tempBuffer.push_back(23.5);
    tempBuffer.push_back(24.1);
    tempBuffer.push_back(23.8);
    tempBuffer.push_back(25.2);
    tempBuffer.push_back(24.7);
    tempBuffer.push_back(26.1); // 가장 오래된 데이터 덮어쓰기

    tempBuffer.PrintBufferIndex();

    std::cout << "버퍼 내용(begin부터): ";
    for (auto it = tempBuffer.begin(); it != tempBuffer.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";

    std::cout << "size = " << tempBuffer.size() << "\n";
    std::cout << "capacity = " << tempBuffer.capacity() << "\n";
    std::cout << "empty = " << std::boolalpha << tempBuffer.empty() << "\n";

    double maxTemp = *std::max_element(tempBuffer.begin(), tempBuffer.end());
    double avgTemp = std::accumulate(tempBuffer.begin(), tempBuffer.end(), 0.0) / tempBuffer.size();

    std::cout << "maxTemp = " << maxTemp << "\n";
    std::cout << "avgTemp = " << avgTemp << "\n";
    std::cout << "front = " << tempBuffer.front() << " // 가장 오래된 데이터\n";
    std::cout << "back = " << tempBuffer.back() << " // 가장 최근 데이터\n";
}