#ifndef DEF_TENSOR
#define DEF_TENSOR

#include <vector>
#include <iostream>
#include "Matrix.h"
#include "Filters.h"

class Filters;

class Tensor
{
public:
	Tensor();
	Tensor(int height, int width);
	Tensor(int height, int width, int depth);
	Tensor(std::vector<Matrix> const &layers);

	//vector storing matrices (3D volume of matrices)
	std::vector<Matrix> layers;

	int getDepth() const;
	int getHeight() const;
	int getWidth() const;
	void addLayer(Matrix layer);
	void randomValueInit(int low, int high);
	Matrix getLayer(int index) const;
	Tensor fwdConv(Filters setOfFilters, int stride, int bias);
	Tensor fwdConv(Filters setOfFilters, int stride, int bias, int padding);
	Tensor fwdMaxPool(int pool_filter_height, int pool_filter_width, int stride, int bias);

	double kernel(double A[], double B[], int y, int x, int z, int F, int f_W_padded);
	Tensor fwdConv_baseline(Filters setOfFilters, int stride, int bias, int padding);

protected:
	int height;
	int width;
	int depth;
};

#endif
