#include "SPUtil.h"
#include "FFT.h"

namespace SPUtil
{
	//convolve second over first should be repaired later
	std::vector<double> convolve_by_sum(const std::vector<double>& f, const std::vector<double>& s)
	{
		std::vector<double> result(f.size());

		int n2 = s.size() / 2;
		for (int i = 0; i < f.size(); i++)
		{
			result[i] = 0;
			for (int j = 0; j < s.size(); j++)
			{
				if (i + (j - n2) < 0 || i + (j - n2) >= f.size()) continue;
				result[i] += s[s.size() - 1 - j] * f[i + (j - n2)];
			}
		}

		return std::move(result);
	}

	//now f and s should be the same size
	std::vector<double> convolve_by_fft(const std::vector<double>& f, const std::vector<double>& s)
	{
		std::vector<FFT::cmplx> fft_f(f.size() * 2);
		std::vector<FFT::cmplx> fft_s(s.size() * 2);

		for (int i = f.size(); i < f.size() * 2; i++)
		{
			fft_f[i] = f[i - f.size()];
			fft_s[i] = s[i - f.size()];
		}

		FFT::fft_inplace(fft_f);
		FFT::fft_inplace(fft_s);

		for (int i = 0; i < fft_f.size(); i++)
			fft_f[i] *= fft_s[i];

		FFT::ifft_inplace(fft_f);

		std::vector<double> result(f.size());

		for (int i = 0; i < result.size(); i++)
		{
			result[i] = fft_f[i + f.size() / 2].real();
		}

		return std::move(result);
	}
}