#include "calc.h"

/**
                        @par				There all math
functions, which are used in calculator are contained. They are needed to turn
them to the same type of arguments
**/

#define CHECK_POINTERS_                                                        \
  if (argv == NULL)                                                            \
    return GRAM_ARGV_NULL;                                                     \
  if (res == NULL)                                                             \
    return GRAM_RES_NULL;

int c_tan(const double *argv, double *res) {
  CHECK_POINTERS_;
  if (fabs(cos(argv[0])) < DBL_EPSILON)
    return GRAM_FUNC_INVAL_ARG1;
  *res = tan(argv[0]);
  return GRAM_OK;
}

int c_ctan(const double *argv, double *res) {
  CHECK_POINTERS_;
  if (fabs(sin(argv[0])) < DBL_EPSILON)
    return GRAM_FUNC_INVAL_ARG1;
  *res = cos(argv[0]) / sin(argv[0]);
  return GRAM_OK;
}

int c_sin(const double *argv, double *res) {
  CHECK_POINTERS_;
  *res = sin(argv[0]);
  return GRAM_OK;
}

int c_cos(const double *argv, double *res) {
  CHECK_POINTERS_;
  *res = cos(argv[0]);
  return GRAM_OK;
}

int c_ln(const double *argv, double *res) {
  CHECK_POINTERS_;
  if (argv[0] < 0)
    return GRAM_FUNC_INVAL_ARG1;
  *res = log(argv[0]);
  return GRAM_OK;
}

int c_log(const double *argv, double *res) {
  CHECK_POINTERS_;

  if (argv[0] < 0 || fabs(argv[0] - 1) < DBL_EPSILON)
    return GRAM_FUNC_INVAL_ARG1;
  if (argv[1] < 0)
    return GRAM_FUNC_INVAL_ARG2;
  *res = log(argv[1]) / log(argv[0]);
  return GRAM_OK;
}

int c_sqrt(const double *argv, double *res) {
  CHECK_POINTERS_;
  if (argv[0] < 0)
    return GRAM_FUNC_INVAL_ARG1;
  *res = sqrt(argv[0]);
  return GRAM_OK;
}

int c_asin(const double *argv, double *res) {
  CHECK_POINTERS_;
  if (fabs(argv[0]) > 1)
    return GRAM_FUNC_INVAL_ARG1;
  *res = asin(argv[0]);
  return GRAM_OK;
}

int c_acos(const double *argv, double *res) {
  CHECK_POINTERS_;
  if (fabs(argv[0]) > 1)
    return GRAM_FUNC_INVAL_ARG1;
  *res = acos(argv[0]);
  return GRAM_OK;
}

int c_atan(const double *argv, double *res) {
  CHECK_POINTERS_;
  *res = atan(argv[0]);
  return GRAM_OK;
}

int c_exp(const double *argv, double *res) {
  CHECK_POINTERS_;
  *res = exp(argv[0]);
  return GRAM_OK;
}

int c_pow(const double *argv, double *res) {
  CHECK_POINTERS_;
  if (argv[0] < 0)
    return GRAM_FUNC_INVAL_ARG1;
  *res = pow(argv[0], argv[1]);
  return GRAM_OK;
}

int c_fac(const double *argv, double *res) {
  CHECK_POINTERS_;
  *res = tgamma(argv[0] + 1);
  return GRAM_OK;
}