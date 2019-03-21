#include "Liba.h"
#include <iostream>

int main()
{
        uint16_t N = 0;
//      std::cin >> N;
        N = 100;
        double *d= new double[N * (N + 1)];
        for (uint16_t i = 0; i < N; i++)
        {
                for (uint16_t j = 0; j < N; j++)
                {
                        if (j + 2 > i)
                        {
                                if (i == j)
                                        d[i * N + j] = 10.0;
                                else
                                        d[i * N + j] = 1.0 / static_cast<double>((j + 1));
                        }
                        else
                                d[i * N + j] = 0.0;
                }
        }
        for (uint16_t i = 0; i < N; i++)
                d[N * N + i] = static_cast<double>(i + 1);
        double* result = Func1(d, N);
        if (result)
        {
                for (uint16_t j = 0; j < N; j++)
			std::cout << result[j]<<'\n';
		delete[] result;
	}
	delete[] d;
	return 0;
}
