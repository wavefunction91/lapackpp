#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t pteqr(
    lapack::Job compz, int64_t n,
    float* D,
    float* E,
    float* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char compz_ = job_comp2char( compz );
    blas_int n_ = (blas_int) n;
    blas_int ldz_ = (blas_int) ldz;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (4*n) );

    LAPACK_spteqr(
        &compz_, &n_,
        D,
        E,
        Z, &ldz_,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pteqr(
    lapack::Job compz, int64_t n,
    double* D,
    double* E,
    double* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char compz_ = job_comp2char( compz );
    blas_int n_ = (blas_int) n;
    blas_int ldz_ = (blas_int) ldz;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (4*n) );

    LAPACK_dpteqr(
        &compz_, &n_,
        D,
        E,
        Z, &ldz_,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pteqr(
    lapack::Job compz, int64_t n,
    float* D,
    float* E,
    std::complex<float>* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char compz_ = job_comp2char( compz );
    blas_int n_ = (blas_int) n;
    blas_int ldz_ = (blas_int) ldz;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (4*n) );

    LAPACK_cpteqr(
        &compz_, &n_,
        D,
        E,
        (lapack_complex_float*) Z, &ldz_,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t pteqr(
    lapack::Job compz, int64_t n,
    double* D,
    double* E,
    std::complex<double>* Z, int64_t ldz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char compz_ = job_comp2char( compz );
    blas_int n_ = (blas_int) n;
    blas_int ldz_ = (blas_int) ldz;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (4*n) );

    LAPACK_zpteqr(
        &compz_, &n_,
        D,
        E,
        (lapack_complex_double*) Z, &ldz_,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
