#include "lapack.hh"
#include "lapack/fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t upgtr(
    lapack::Uplo uplo, int64_t n,
    std::complex<float> const* AP,
    std::complex<float> const* tau,
    std::complex<float>* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (n-1) );

    LAPACK_cupgtr(
        &uplo_, &n_,
        (lapack_complex_float*) AP,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) Q, &ldq_,
        (lapack_complex_float*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t upgtr(
    lapack::Uplo uplo, int64_t n,
    std::complex<double> const* AP,
    std::complex<double> const* tau,
    std::complex<double>* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (n-1) );

    LAPACK_zupgtr(
        &uplo_, &n_,
        (lapack_complex_double*) AP,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) Q, &ldq_,
        (lapack_complex_double*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
