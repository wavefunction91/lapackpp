#include "lapack.hh"
#include "lapack/fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup hesv_computational
int64_t hetri(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = ipiv;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (n) );

    LAPACK_chetri(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_float*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes the inverse of a Hermitian indefinite matrix
/// A using the factorization \f$ A = U D U^H \f$ or \f$ A = L D L^H \f$ computed by
/// `lapack::hetrf`.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this in an alias for `lapack::sytri`.
/// For complex symmetric matrices, see `lapack::sytri`.
///
/// @see hetri2
///
/// @param[in] uplo
///     Whether the details of the factorization are stored
///     as an upper or lower triangular matrix.
///     - lapack::Uplo::Upper: Upper triangular, form is \f$ A = U D U^H; \f$
///     - lapack::Uplo::Lower: Lower triangular, form is \f$ A = L D L^H. \f$
///
/// @param[in] n
///     The order of the matrix A. n >= 0.
///
/// @param[in,out] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     On entry, the block diagonal matrix D and the multipliers
///     used to obtain the factor U or L as computed by `lapack::hetrf`.
///     On successful exit, the (Hermitian) inverse of the original
///     matrix.
///     - If uplo = Upper, the upper triangular part of the
///     inverse is formed and the part of A below the diagonal is not
///     referenced;
///     - if uplo = Lower the lower triangular part of the
///     inverse is formed and the part of A above the diagonal is
///     not referenced.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,n).
///
/// @param[in] ipiv
///     The vector ipiv of length n.
///     Details of the interchanges and the block structure of D
///     as determined by `lapack::hetrf`.
///
/// @retval = 0: successful exit
/// @retval > 0: if return value = i, D(i,i) = 0; the matrix is singular and its
///     inverse could not be computed.
///
/// @ingroup hesv_computational
int64_t hetri(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    int64_t const* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > ipiv_( &ipiv[0], &ipiv[(n)] );
        lapack_int const* ipiv_ptr = &ipiv_[0];
    #else
        lapack_int const* ipiv_ptr = ipiv;
    #endif
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (n) );

    LAPACK_zhetri(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_double*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
