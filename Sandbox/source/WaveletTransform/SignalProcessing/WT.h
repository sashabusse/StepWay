#pragma once
#include "FFT.h"
#include "SPdef.h"

namespace WT
{
	class Wavelet
	{
	public:
		virtual ~Wavelet() {};

		virtual double GetValue(double x, double s) = 0;
		virtual std::vector<double> GenArray(int N) = 0;
		virtual std::vector<double> GenArg(int N) = 0;

	private:
	};

	class MexHWavelet : public Wavelet
	{
	public:
		virtual ~MexHWavelet() {};

		virtual double GetValue(double x, double s) override
		{
			double first = 2.0 / (sqrt(3.0 * s * sqrt(M_PI)));
			double second = (1.0 - (x / s) * (x / s)) * exp(-x * x / (2 * s * s));
			return first * second;
		}
		virtual std::vector<double> GenArray(int N)
		{
			std::vector<double> result(N);
			SP_ASSERT(N > 1);
			//approximating function from -5 to 5
			double dx = 10.0 / (N - 1);
			for (int i = 0; i < N; i++)
			{
				double x = -5.0 + i * dx;
				result[i] = GetValue(x, 1);
			}
			return std::move(result);
		}
		virtual std::vector<double> GenArg(int N)
		{
			std::vector<double> result(N);
			SP_ASSERT(N > 1);
			//approximating function from -5 to 5
			double dx = 10.0 / (N - 1);
			for(int i = 0; i < N; i++)
			{
				result[i] = -5.0 + i * dx;
			}
			return std::move(result);
		}
	private:
	};


	std::vector<double> cwt(const std::vector<double>& data, Wavelet& wv, double scale);

}