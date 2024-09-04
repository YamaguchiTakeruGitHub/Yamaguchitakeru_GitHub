#include "Matrix.h"

MATRIX math::Matrix::MultiplyMatrix(const MATRIX& mat1, const MATRIX& mat2)
{
	MATRIX result;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result.m[i][j] = mat1.m[i][0] * mat2.m[0][j] +
				mat1.m[i][1] * mat2.m[1][j] +
				mat1.m[i][2] * mat2.m[2][j] +
				mat1.m[i][3] * mat2.m[3][j];
		}
	}
	return result;

}
