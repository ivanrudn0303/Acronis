#include "Liba.h"

double * Func1(double *p,  uint32_t d)
{
	if ((p != nullptr) && d)
	{
		for (uint32_t i = 0; i < d; i++)
		{
			for (uint32_t j = d- 1; j > i; j--)
			{
				double coeff = -p[d * i + j] / p[d * i + i];
				for (uint32_t k = i; k < d + 1; k++)
					p[k * d + j] += p[k * d + i] * coeff;
			}
		}
		double *res = new double[d], sum = 0.0;
		for (int64_t i = d - 1; i >= 0; i--)
		{
			sum = p[d* d+ i];
			for (uint32_t j = 1; j < d- i; j++)
			{
				sum -= p[(d- j) * d+ i] * res[d- j];
			}
			if (p[i * d+ i] == 0)
			{
				delete[] res;
				return nullptr;
			}
			res[i] = sum / p[i * d+ i];
		}
		return res;
	}
	else
		return nullptr;
}
