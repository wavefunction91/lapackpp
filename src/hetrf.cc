#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup hesv_computational
int64_t hetrf(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    int64_t* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( (n) );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_chetrf(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_float*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );

    LAPACK_chetrf(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_float*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes the factorization of a Hermitian matrix A
/// using the Bunch-Kaufman diagonal pivoting method. The form of the
/// factorization is
///
///     \f$ A = U D U^H \f$ or
///     \f$ A = L D L^H \f$
///
/// where U (or L) is a product of permutation and unit upper (lower)
/// triangular matrices, and D is Hermitian and block diagonal with
/// 1-by-1 and 2-by-2 diagonal blocks.
///
/// This is the blocked version of the algorithm, calling Level 3 BLAS.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this in an alias for `lapack::sytrf`.
/// For complex symmetric matrices, see `lapack::sytrf`.
///
/// @param[in] uplo
///     - lapack::Uplo::Upper: Upper triangle of A is stored;
///     - lapack::Uplo::Lower: Lower triangle of A is stored.
///
/// @param[in] n
///     The order of the matrix A. n >= 0.
///
/// @param[in,out] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     On entry, the Hermitian matrix A.
///     - If uplo = Upper, the leading
///     n-by-n upper triangular part of A contains the upper
///     triangular part of the matrix A, and the strictly lower
///     triangular part of A is not referenced.
///
///     - If uplo = Lower, the
///     leading n-by-n lower triangular part of A contains the lower
///     triangular part of the matrix A, and the strictly upper
///     triangular part of A is not referenced.
///
///     - On exit, the block diagonal matrix D and the multipliers used
///     to obtain the factor U or L (see below for further details).
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,n).
///
/// @param[out] ipiv
///     The vector ipiv of length n.
///     Details of the interchanges and the block structure of D.
///     - If ipiv(k) > 0, then rows and columns k and ipiv(k) were
///     interchanged and D(k,k) is a 1-by-1 diagonal block.
///
///     - If uplo = Upper and ipiv(k) = ipiv(k-1) < 0,
///     then rows and columns k-1 and -ipiv(k) were interchanged
///     and D(k-1:k,k-1:k) is a 2-by-2 diagonal block.
///
///     - If uplo = Lower and ipiv(k) = ipiv(k+1) < 0,
///     then rows and columns k+1 and -ipiv(k) were interchanged
///     and D(k:k+1,k:k+1) is a 2-by-2 diagonal block.
///
/// @retval = 0: successful exit
/// @retval > 0: if return value = i,
///     D(i,i) is exactly zero. The factorization
///     has been completed, but the block diagonal matrix D is
///     exactly singular, and division by zero will occur if it
///     is used to solve a system of equations.
///
// -----------------------------------------------------------------------------
/// @par Further Details
///
/// If uplo = Upper, then \f$ A = U D U^H, \f$ where
///     \f[ U = P(n) U(n) \dots P(k) U(k) \dots, \f]
/// i.e., U is a product of terms \f$ P(k) U(k), \f$ where k decreases from n to
/// 1 in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1
/// and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as
/// defined by ipiv(k), and U(k) is a unit upper triangular matrix, such
/// that if the diagonal block D(k) is of order s (s = 1 or 2), then
///
///             (   I    v    0   )   k-s
///     U(k) =  (   0    I    0   )   s
///             (   0    0    I   )   n-k
///                k-s   s   n-k
///
/// If s = 1, D(k) overwrites A(k,k), and v overwrites A(1:k-1,k).
/// If s = 2, the upper triangle of D(k) overwrites A(k-1,k-1), A(k-1,k),
/// and A(k,k), and v overwrites A(1:k-2,k-1:k).
///
/// If uplo = Lower, then \f$ A = L D L^H, \f$ where
///     \f[ L = P(1) L(1) \dots P(k) L(k) \dots, \f]
/// i.e., L is a product of terms \f$ P(k) L(k), \f$ where k increases from 1 to
/// n in steps of 1 or 2, and D is a block diagonal matrix with 1-by-1
/// and 2-by-2 diagonal blocks D(k).  P(k) is a permutation matrix as
/// defined by ipiv(k), and L(k) is a unit lower triangular matrix, such
/// that if the diagonal block D(k) is of order s (s = 1 or 2), then
///
///             (   I    0     0   )  k-1
///     L(k) =  (   0    I     0   )  s
///             (   0    v     I   )  n-k-s+1
///                k-1   s  n-k-s+1
///
/// If s = 1, D(k) overwrites A(k,k), and v overwrites A(k+1:n,k).
/// If s = 2, the lower triangle of D(k) overwrites A(k,k), A(k+1,k),
/// and A(k+1,k+1), and v overwrites A(k+2:n,k:k+1).
///
/// @ingroup hesv_computational
int64_t hetrf(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    int64_t* ipiv )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    #if 1
        // 32-bit copy
        std::vector< blas_int > ipiv_( (n) );
        blas_int* ipiv_ptr = &ipiv_[0];
    #else
        blas_int* ipiv_ptr = ipiv;
    #endif
    blas_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_zhetrf(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_double*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );

    LAPACK_zhetrf(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        ipiv_ptr,
        (lapack_complex_double*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

}  // namespace lapack
