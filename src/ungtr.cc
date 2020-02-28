#include "lapack.hh"
#include "lapack/fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup heev_computational
int64_t ungtr(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    std::complex<float> const* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_cungtr(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );

    LAPACK_cungtr(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Generates an n-by-n unitary matrix Q which is defined as the
/// product of n-1 elementary reflectors of order n, as returned by
/// `lapack::hetrd`:
///
/// - if uplo = Upper, \f$ Q = H(n-1) \dots H(2) H(1), \f$
/// - if uplo = Lower, \f$ Q = H(1) H(2) \dots H(n-1). \f$
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this is an alias for `lapack::orgtr`.
///
/// @param[in] uplo
///     - lapack::Uplo::Upper: Upper triangle of A contains elementary reflectors
///         from `lapack::hetrd`;
///     - lapack::Uplo::Lower: Lower triangle of A contains elementary reflectors
///         from `lapack::hetrd`.
///
/// @param[in] n
///     The order of the matrix Q. n >= 0.
///
/// @param[in,out] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     On entry, the vectors which define the elementary reflectors,
///     as returned by `lapack::hetrd`.
///     On exit, the n-by-n unitary matrix Q.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= n.
///
/// @param[in] tau
///     The vector tau of length n-1.
///     tau(i) must contain the scalar factor of the elementary
///     reflector H(i), as returned by `lapack::hetrd`.
///
/// @retval = 0: successful exit
///
/// @ingroup heev_computational
int64_t ungtr(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    std::complex<double> const* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_zungtr(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );

    LAPACK_zungtr(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
