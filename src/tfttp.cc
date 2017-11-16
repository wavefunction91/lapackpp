#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using std::max;
using std::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t tfttp(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    float const* ARF,
    float* AP )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_stfttp( &transr_, &uplo_, &n_, ARF, AP, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tfttp(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    double const* ARF,
    double* AP )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_dtfttp( &transr_, &uplo_, &n_, ARF, AP, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tfttp(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<float> const* ARF,
    std::complex<float>* AP )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_ctfttp( &transr_, &uplo_, &n_, ARF, AP, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t tfttp(
    lapack::Op transr, lapack::Uplo uplo, int64_t n,
    std::complex<double> const* ARF,
    std::complex<double>* AP )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
    }
    char transr_ = op2char( transr );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int info_ = 0;

    LAPACK_ztfttp( &transr_, &uplo_, &n_, ARF, AP, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
