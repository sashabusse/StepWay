#include "FFT.h"
#include <algorithm>
#include <vector>
#include <complex>

namespace FFT
{
	//Implementations
	//input should be power of 2
	void fft_implementation(std::vector<cmplx>& a, bool invert) {
		int n = (int)a.size();
		if (n == 1)  return;

		std::vector<cmplx> a0(n / 2), a1(n / 2);
		for (int i = 0, j = 0; i < n; i += 2, ++j) {
			a0[j] = a[i];
			a1[j] = a[i + 1];
		}
		fft_implementation(a0, invert);
		fft_implementation(a1, invert);

		double ang = 2 * M_PI / n * (invert ? -1 : 1);
		std::complex<double> w(1), wn(cos(ang), sin(ang));
		for (int i = 0; i < n / 2; ++i) {
			a[i] = a0[i] + w * a1[i];
			a[i + n / 2] = a0[i] - w * a1[i];
			if (invert)
				a[i] /= 2, a[i + n / 2] /= 2;
			w *= wn;
		}
	}


	//forward
	std::vector<cmplx> fft(const std::vector<cmplx>& signal)
	{
		std::vector<cmplx> result(signal);
		fft_implementation(result, false);
		return std::move(result);
	}
	std::vector<cmplx> fft(const std::vector<double>& signal)
	{
		std::vector<cmplx> result(signal.size());
		for (int i = 0; i < signal.size(); i++)
		{
			result[i] = signal[i];
		}
		fft_implementation(result, false);
		return std::move(result);
	}

	fft_result fft_ri(const std::vector<cmplx>& signal)
	{
		std::vector<cmplx> result(signal);
		fft_implementation(result, false);
		fft_result res_struct;
		
		res_struct.re.resize(result.size());
		res_struct.im.resize(result.size());
		
		for (int i = 0; i < result.size();i++)
		{
			res_struct.re[i] = result[i].real();
			res_struct.im[i] = result[i].imag();
		}

		return std::move(res_struct);
	}
	fft_result fft_ri(const std::vector<double>& signal)
	{
		std::vector<cmplx> result(signal.size());
		for (int i = 0; i < result.size(); i++)
		{
			result[i] = signal[i];
		}

		fft_implementation(result, false);
		fft_result res_struct;

		res_struct.re.resize(result.size());
		res_struct.im.resize(result.size());

		for (int i = 0; i < result.size(); i++)
		{
			res_struct.re[i] = result[i].real();
			res_struct.im[i] = result[i].imag();
		}

		return std::move(res_struct);
	}

	void fft_inplace(std::vector<cmplx>& inp_out)
	{
		fft_implementation(inp_out, false);
	}

	std::vector<double> fft_freqs(int N, double dt)
	{
		std::vector<double> freqs(N);

		for (int i = 0; i < N / 2; i++)
		{
			freqs[i] = i * 1.0 / (N * dt);
			freqs[N-i-1] = -(i+1) * 1.0 / (N * dt);
		}
			
		return freqs;
	}

	
	//Inverse
	std::vector<cmplx> ifft(const std::vector<cmplx>& spectrum)
	{
		std::vector<cmplx> result(spectrum);
		fft_implementation(result, true);
		return std::move(result);
	}

	std::vector<cmplx> ifft(const std::vector<double>& spectrum_re, const std::vector<double>& spectrum_im)
	{
		std::vector<cmplx> result(spectrum_re.size());
		for (int i = 0; i < result.size(); i++)
			result[i] = spectrum_re[i] + spectrum_im[i] * cmplx(0, 1);
		ifft_inplace(result);
		return std::move(result);
	}

	void ifft_inplace(std::vector<cmplx>& inp_out)
	{
		fft_implementation(inp_out, true);
	}


	//Utils
	std::vector<double> symmetrical_freqs(int N, double dt)
	{
		std::vector<double> result(N);
		for (int i = 0; i < N; i++)
		{
			result[i] = 1.0 / (N * dt) * (i - N / 2.0);
		}
		return std::move(result);
	}

	std::vector<double> abs(const std::vector<cmplx>& data)
	{
		std::vector<double> result(data.size());
		for (int i = 0; i < data.size(); i++)
			result[i] = abs(data[i]);
		return result;
	}

}