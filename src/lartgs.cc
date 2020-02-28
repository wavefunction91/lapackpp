#include "lapack.hh"
#include "lapack/fortran.h"

#if LAPACK_VERSION >= 30300  // >= v3.3

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
void lartgs(
    float x, float y, float sigma,
    float* cs,
    float* sn )
{

    LAPACK_slartgs(
        &x, &y, &sigma, cs, sn );
}

// -----------------------------------------------------------------------------
void lartgs(
    double x, double y, double sigma,
    double* cs,
    double* sn )
{

    LAPACK_dlartgs(
        &x, &y, &sigma, cs, sn );
}

}  // namespace lapack

#endif  // LAPACK >= v3.3
