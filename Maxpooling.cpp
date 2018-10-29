#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
int const map_height = 4;
int const map_width = 5;
int maxpool()
{

	//int const map_height = 4;
	//int const map_width = 5;
	int const pool_size = 2;
	float A[map_width*map_height] =
	{

		5., 3, 1, 2, 1, 1, 2, 3, 2, 6, 4, 2, 2, 5, 7, 3, 6, 1, 1, 3
	};


	int  dim1 = int(map_height / pool_size) + min(1, map_height%pool_size);
	int  dim2 = int(map_width / pool_size) + min(1, map_width%pool_size);

	vector<float>out = {};
	vector<int> indexout = {};


	for (int i = 0; i < dim1; i++)
	{
		for (int j = 0; j < dim2; j++)
		{
			vector<float> subout = {};
			vector<int> tempindex = {};
			for (int m = 0; m < min(map_height - i*pool_size, pool_size); m++)
			{
				for (int n = 0; n < min(map_width - j*pool_size, pool_size); n++)
				{
					subout.push_back(A[i*map_width*pool_size + m*map_width + j*pool_size + n]);
					tempindex.push_back(i*map_width*pool_size + m*map_width + j*pool_size + n);
				}
			}
			auto maxPosition = max_element(subout.begin(), subout.end());
			out.push_back(*maxPosition);
			subout.~vector<float>();
			tempindex.~vector<int>();
		}
	}
	
	//原始矩阵
	cout << "原始矩阵：" << endl;
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
		{
			cout << A[i*map_width + j] << " ";
		}
		cout << endl;
	}
	
	
	//池化后输出矩阵
	cout << "池化后输出矩阵：" << endl;
	for (int i = 0; i < dim1; i++)
	{
		for (int j = 0; j < dim2; j++)
		{
			cout << out[i*dim2 + j] << " ";
		}
		cout << endl;
	}

	
	return 0;
}


int invmaxpool()
{
	int const dim1b = 3;
	int const dim2b = 2;

	float backpool[dim1b*dim2b] = { 5, 3, 6, 6, 5, 7 };
	float backindex[dim1b*dim2b] = { 0, 7, 9, 16, 13, 14 };
	int num = map_height*map_width;
	vector<float> back_pool(num, 0);

	for (int i = 0; i < dim1b*dim2b; i++)
	{
		back_pool[backindex[i]] = backpool[i];
	}
	
	
	//池化反传矩阵
	cout << "池化反传矩阵：" << endl;
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
		{
			cout << back_pool[i*map_width + j] << " ";
		}
		cout << endl;
	}

	
	return 0;

}


void main()
{
	maxpool();
	invmaxpool();

	system("pause");
}