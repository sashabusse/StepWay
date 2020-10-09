#pragma once
#include <vector>

namespace SPUtil
{
	//now just produces conv of second over the first
	std::vector<double> convolve_by_sum(const std::vector<double>& f, const std::vector<double>& s);
	std::vector<double> convolve_by_fft(const std::vector<double>& f, const std::vector<double>& s);
}