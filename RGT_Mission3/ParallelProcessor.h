#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <numeric>
#include <memory>
#include <algorithm>
#include <chrono>

template <typename T>
class ParallelProcessor
{
private:
	size_t _threadCount;

public:
	explicit ParallelProcessor(size_t threads) : _threadCount(threads) {}

	template <typename Func>
	auto parallel_map(const std::vector<T>& input, Func func) -> std::vector<decltype(func(input[0]))>
	{
		using R = decltype(func(input[0]));
		std::vector<std::future<std::vector<R>>> futures;
		std::vector<R> result(input.size());

		size_t chunkSize = input.size() / _threadCount;

		for (size_t i = 0; i < _threadCount; ++i)
		{
			size_t start = i * chunkSize;
			size_t end = (i == _threadCount - 1) ? input.size() : (i + 1) * chunkSize;

			futures.push_back(std::async(std::launch::async,
				[start, end, func, &input]() {
					std::vector<R> local;
					local.reserve(end - start);
					for (size_t j = start; j < end; ++j)
						local.push_back(func(input[j]));
					return local;
				}));
		}

		size_t pos = 0;
		for (auto& f : futures)
		{
			auto part = f.get();
			std::copy(part.begin(), part.end(), result.begin() + pos);
			pos += part.size();
		}

		return result;
	}
};
