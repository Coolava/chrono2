#pragma once

#include <chrono>
#include <sstream>
#include <iomanip>

namespace std
{
	namespace chrono
	{

		static auto steadyStart = std::chrono::steady_clock::now();
		static auto systemStart = std::chrono::system_clock::now();

		/*Steady clock to system clock*/
		static auto steadyToSystem(std::chrono::steady_clock::time_point steady)
		{
			return systemStart + std::chrono::duration_cast<std::chrono::system_clock::duration>(steady - steadyStart);
		}

		static inline std::string time_toString(std::chrono::system_clock::time_point time)
		{
			using namespace std::chrono;
			// get number of microseconds for the current second
			// (remainder after division into seconds)
			auto us = duration_cast<microseconds>(time.time_since_epoch()) % 1000000;

			// convert to std::time_t in order to convert to std::tm (broken time)
			auto timer = std::chrono::system_clock::to_time_t(time);

			std::tm t;

			localtime_s(&t, &timer);

			std::ostringstream oss;

			oss << std::put_time(&t, "%Y_%m_%d,%H_%M_%S,");
			oss << std::setfill('0') << std::setw(6) << us.count();

			return oss.str();
		}
	}
}