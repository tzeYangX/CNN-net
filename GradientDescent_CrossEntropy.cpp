// ConsoleApplication9.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include <cmath>
#include <iostream>

int main(void)
{
	float matrix[4][2] = { { 1, 4 }, { 2, 5 }, { 5, 1 }, { 4, 2 } };
	float result[4] = { 0, 0, 1, 1 };
	float theta[2] = { 0.001, -1 };
	float learning_rate = 0.5;
	float loss_sum = 10.;

	for (int i = 0; i<1000 && loss_sum>0.001; ++i)
	{
		printf("\n");
		printf("迭代次数: %d\n", i + 1);
		float loss_sum = 0.0;
		for (int j = 0; j < 4; ++j)
		{
			float b = 0.0;
			for (int k = 0; k < 2; ++k)
			{
				b += matrix[j][k] * theta[k];
			}
			float pred = 1 / (1 + exp(-b));
			//loss_sum += (result[j] - pred)*(result[j] - pred);
			loss_sum += -(result[j] * log(pred) + (1 - result[j])*log(1 - pred));
			for (int k = 0; k < 2; ++k)
			{
				float sig = pred*(1 - pred);
				//theta[k]+=learning_rate*(result[j] - pred)*matrix[j][k]*sig;
				theta[k] += learning_rate*(result[j] - pred)*matrix[j][k];
			}
			
		}

		printf("theta1: %f\n", theta[0]);
		printf("theta2: %f\n", theta[1]);
		printf("loss: %f\n", loss_sum);

	}
	return 0;
}