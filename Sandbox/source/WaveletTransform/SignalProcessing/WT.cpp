#include "WT.h"
#include "SPUtil.h"


namespace WT
{	

	std::vector<double> cwt(const std::vector<double>& data, Wavelet& wv, double scale)
	{
		std::vector<double> result(data.size());
		int length = (scale * 10 + 1);
		if (length % 2 == 0) length += 1;//mb not?
		std::vector<double> wv_data = wv.GenArray(length);

		return std::move(SPUtil::convolve_by_sum(data, wv_data));
	}
}