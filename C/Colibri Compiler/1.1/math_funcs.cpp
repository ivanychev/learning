#include "compiler.h"

/**
			@par			These functions are used by tree optimizet to calculate function values if it is possible to calculate
							I suppose, it's not necessary to write docs for every function. Each of them gets number arguments array
							and pointer to result.
							Each function returns condition of proceeding.
**/




#define CHECK_POINTERS_							\
	if (argv == NULL) return TREE_BAD;			\
	if (res  == NULL) return TREE_BAD;				

int cd_tg(const double* argv, double* res)
{
	CHECK_POINTERS_;
	if (fabs(cos(argv[0])) < DBL_EPSILON) return TREE_OPT_INVAL_ARG1;
	*res = tan(argv[0]);
	return TREE_OK;
}

int cd_ctg(const double* argv, double* res)
{
	CHECK_POINTERS_;
	if (fabs(sin(argv[0])) < DBL_EPSILON) return TREE_OPT_INVAL_ARG1;
	*res = cos(argv[0]) / sin(argv[0]);
	return TREE_OK;
}

int cd_sin(const double* argv, double* res)
{
	CHECK_POINTERS_;
	*res = sin(argv[0]);
	return TREE_OK;
}

int cd_cos(const double* argv, double* res)
{
	CHECK_POINTERS_;
	*res = cos(argv[0]);
	return TREE_OK;
}

int cd_ln(const double* argv, double* res)
{
	CHECK_POINTERS_;
	if (argv[0] < 0) return TREE_OPT_INVAL_ARG1;
	*res = log(argv[0]);
	return TREE_OK;
}

int cd_log(const double* argv, double* res)
{
	CHECK_POINTERS_;
	
	if (argv[0] < 0 || fabs(argv[0] - 1) < DBL_EPSILON) return TREE_OPT_INVAL_ARG1;
	if (argv[1] < 0) return TREE_OPT_INVAL_ARG2;
	*res = log(argv[1]) / log(argv[0]);
	return TREE_OK;
}

int cd_sqrt(const double* argv, double* res)
{
	CHECK_POINTERS_;
	if (argv[0] < 0) return TREE_OPT_INVAL_ARG1;
	*res = sqrt(argv[0]);
	return TREE_OK;
}

int cd_arcsin(const double* argv, double* res)
{
	CHECK_POINTERS_;
	if (fabs(argv[0]) > 1) return TREE_OPT_INVAL_ARG1;
	*res = asin(argv[0]);
	return TREE_OK;
}

int cd_arccos(const double* argv, double* res)
{
	CHECK_POINTERS_;
	if (fabs(argv[0]) > 1) return TREE_OPT_INVAL_ARG1;
	*res = acos(argv[0]);
	return TREE_OK;
}

int cd_arctg(const double* argv, double* res)
{
	CHECK_POINTERS_;
	*res = atan(argv[0]);
	return TREE_OK;
}

int cd_exp(const double* argv, double* res)
{
	CHECK_POINTERS_;
	*res = exp(argv[0]);
	return TREE_OK;
}

int cd_pow(const double* argv, double* res)
{
	CHECK_POINTERS_;
	if (argv[0] < 0) return TREE_OPT_INVAL_ARG1;
	*res = pow(argv[0], argv[1]);
	return TREE_OK;
}

int cd_fac(const double* argv, double* res)
{
	CHECK_POINTERS_;
	*res = tgamma(argv[0] + 1);
	return TREE_OK;
}