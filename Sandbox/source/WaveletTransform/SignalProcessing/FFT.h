#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <complex>


namespace FFT
{
	//forward
	typedef std::complex<double> cmplx;
	std::vector<cmplx> fft(const std::vector<cmplx>& signal);
	std::vector<cmplx> fft(const std::vector<double>& signal);

	struct fft_result { std::vector<double> re, im; };
	fft_result fft_ri(const std::vector<cmplx>& signal);
	fft_result fft_ri(const std::vector<double>& signal);

	void fft_inplace(std::vector<cmplx>& inp_out);

	//inverse
	std::vector<cmplx> ifft(const std::vector<cmplx>& spectrum);
	//std::vector<double> irfft(const std::vector<cmplx>& spectrum);

	std::vector<cmplx> ifft(const std::vector<double>& spectrum_re, const std::vector<double>& spectrum_im);
	//std::vector<double> irfft(const std::vector<double>& spectrum_re, const std::vector<double>& spectrum_im);

	void ifft_inplace(std::vector<cmplx>& inp_out);

	//Util
	std::vector<double> fft_freqs(int N, double dt);

	template<typename T>
	void make_symmetrical_inplace(std::vector<T>& fft_sig)
	{
		for (int i = 0; i < fft_sig.size() / 2; i++)
		{
			std::swap(fft_sig[i], fft_sig[fft_sig.size() / 2 + i]);
		}
	}
	std::vector<double> symmetrical_freqs(int N, double dt);

	std::vector<double> abs(const std::vector<cmplx>& cmplx);


}





