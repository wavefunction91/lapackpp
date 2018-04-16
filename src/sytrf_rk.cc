#include "lapack.hh"
#include "lapack_fortran.h"

#if LAPACK_VERSION >= 30700  // >= 3.7

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup sysv_rk_computational
int64_t sytrf_rk(
    lapack::Uplo uplo, int64_t n,
    float* A, int64_t lda,
    float* E,
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
    float qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_ssytrf_rk(
        &uplo_, &n_,
        A, &lda_,
        E,
        ipiv_ptr,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );

    LAPACK_ssytrf_rk(
        &uplo_, &n_,
        A, &lda_,
        E,
        ipiv_ptr,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup sysv_rk_computational
int64_t sytrf_rk(
    lapack::Uplo uplo, int64_t n,
    double* A, int64_t lda,
    double* E,
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
    double qry_work[1];
    blas_int ineg_one = -1;
    LAPACK_dsytrf_rk(
        &uplo_, &n_,
        A, &lda_,
        E,
        ipiv_ptr,
        qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );

    LAPACK_dsytrf_rk(
        &uplo_, &n_,
        A, &lda_,
        E,
        ipiv_ptr,
        &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    #if 1
        std::copy( ipiv_.begin(), ipiv_.end(), ipiv );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup sysv_rk_computational
int64_t sytrf_rk(
    lapack::Uplo uplo, int64_t n,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* E,
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
    LAPACK_csytrf_rk(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) E,
        ipiv_ptr,
        (lapack_complex_float*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );

    LAPACK_csytrf_rk(
        &uplo_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) E,
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
// this is here just to get a doxygen entry
/// @see lapack::sytrf_rk
/// @ingroup sysv_rk_computational
#define sytrf_3 sytrf_rk

// -----------------------------------------------------------------------------
/// Computes the factorization of a symmetric matrix A
/// using the bounded Bunch-Kaufman (rook) diagonal pivoting method:
///
///     \f$ A = P U D U^T P^T \f$ or
///     \f$ A = P L D L^T P^T, \f$
///
/// where U (or L) is unit upper (or lower) triangular matrix,
/// \f$ U^T \f$ (or \f$ L^T \f$) is the transpose of U (or L), P is a permutation
/// matrix, \f$ P^T \f$ is the transpose of P, and D is symmetric and block
/// diagonal with 1-by-1 and 2-by-2 diagonal blocks.
///
/// This is the blocked version of the algorithm, calling Level 3 BLAS.
/// For more information see Further Details section.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, `lapack::hetrf_rk` is an alias for this.
/// For complex Hermitian matrices, see `lapack::hetrf_rk`.
///
/// @since LAPACK 3.7.0.
/// This interface replaces the older `lapack::sytrf_rook`.
///
/// @param[in] uplo
///     Whether the upper or lower triangular part of the
///     symmetric matrix A is stored:
///     - lapack::Uplo::Upper: Upper triangular
///     - lapack::Uplo::Lower: Lower triangular
///
/// @param[in] n
///     The order of the matrix A. n >= 0.
///
/// @param[in,out] A
///     The n-by-n matrix A, stored in an lda-by-n array.
///     - On entry, the symmetric matrix A.
///       - If uplo = Upper: the leading n-by-n upper triangular part
///       of A contains the upper triangular part of the matrix A,
///       and the strictly lower triangular part of A is not
///       referenced.
///
///       - If uplo = Lower: the leading n-by-n lower triangular part
///       of A contains the lower triangular part of the matrix A,
///       and the strictly upper triangular part of A is not
///       referenced.
///
///     - On exit, contains:
///       - ONLY diagonal elements of the symmetric block diagonal
///         matrix D on the diagonal of A, i.e. D(k,k) = A(k,k);
///         (superdiagonal (or subdiagonal) elements of D
///         are stored on exit in array E), and
///       - If uplo = Upper: factor U in the superdiagonal part of A.
///       - If uplo = Lower: factor L in the subdiagonal part of A.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,n).
///
/// @param[out] E
///     The vector E of length n.
///     On exit, contains the superdiagonal (or subdiagonal)
///     elements of the symmetric block diagonal matrix D
///     with 1-by-1 or 2-by-2 diagonal blocks, where
///     - If uplo = Upper: E(i) = D(i-1,i), i=2:n, E(1) is set to 0;
///     - If uplo = Lower: E(i) = D(i+1,i), i=1:n-1, E(n) is set to 0.
///
///     - Note: For 1-by-1 diagonal block D(k), where
///     1 <= k <= n, the element E(k) is set to 0 in both
///     uplo = Upper or uplo = Lower cases.
///
/// @param[out] ipiv
///     The vector ipiv of length n.
///     ipiv describes the permutation matrix P in the factorization
///     of matrix A as follows. The absolute value of ipiv(k)
///     represents the index of row and column that were
///     interchanged with the k-th row and column. The value of uplo
///     describes the order in which the interchanges were applied.
///     Also, the sign of ipiv represents the block structure of
///     the symmetric block diagonal matrix D with 1-by-1 or 2-by-2
///     diagonal blocks which correspond to 1 or 2 interchanges
///     at each factorization step. For more info see Further
///     Details section.
///     - If uplo = Upper,
///     (in factorization order, k decreases from n to 1):
///       a) A single positive entry ipiv(k) > 0 means:
///         D(k,k) is a 1-by-1 diagonal block.
///         If ipiv(k) != k, rows and columns k and ipiv(k) were
///         interchanged in the matrix A(1:n,1:n);
///         If ipiv(k) = k, no interchange occurred.
///
///       b) A pair of consecutive negative entries
///         ipiv(k) < 0 and ipiv(k-1) < 0 means:
///         D(k-1:k,k-1:k) is a 2-by-2 diagonal block.
///         (NOTE: negative entries in ipiv appear ONLY in pairs).
///         1) If -ipiv(k) != k, rows and columns
///         k and -ipiv(k) were interchanged
///         in the matrix A(1:n,1:n).
///         If -ipiv(k) = k, no interchange occurred.
///         2) If -ipiv(k-1) != k-1, rows and columns
///         k-1 and -ipiv(k-1) were interchanged
///         in the matrix A(1:n,1:n).
///         If -ipiv(k-1) = k-1, no interchange occurred.
///
///       c) In both cases a) and b), always ABS( ipiv(k) ) <= k.
///
///       d) NOTE: Any entry ipiv(k) is always NONZERO on output.
///
///     - If uplo = Lower,
///     (in factorization order, k increases from 1 to n):
///       a) A single positive entry ipiv(k) > 0 means:
///         D(k,k) is a 1-by-1 diagonal block.
///         If ipiv(k) != k, rows and columns k and ipiv(k) were
///         interchanged in the matrix A(1:n,1:n).
///         If ipiv(k) = k, no interchange occurred.
///
///       b) A pair of consecutive negative entries
///         ipiv(k) < 0 and ipiv(k+1) < 0 means:
///         D(k:k+1,k:k+1) is a 2-by-2 diagonal block.
///         (NOTE: negative entries in ipiv appear ONLY in pairs).
///         1) If -ipiv(k) != k, rows and columns
///         k and -ipiv(k) were interchanged
///         in the matrix A(1:n,1:n).
///         If -ipiv(k) = k, no interchange occurred.
///         2) If -ipiv(k+1) != k+1, rows and columns
///         k-1 and -ipiv(k-1) were interchanged
///         in the matrix A(1:n,1:n).
///         If -ipiv(k+1) = k+1, no interchange occurred.
///
///       c) In both cases a) and b), always ABS( ipiv(k) ) >= k.
///
///       d) NOTE: Any entry ipiv(k) is always NONZERO on output.
///
/// @retval = 0: successful exit
/// @retval > 0: If return value = i, the matrix A is singular, because:
///     If uplo = Upper: column i in the upper
///     triangular part of A contains all zeros.
///     If uplo = Lower: column i in the lower
///     triangular part of A contains all zeros.
///
///     Therefore D(i,i) is exactly zero, and superdiagonal
///     elements of column i of U (or subdiagonal elements of
///     column i of L ) are all zeros. The factorization has
///     been completed, but the block diagonal matrix D is
///     exactly singular, and division by zero will occur if
///     it is used to solve a system of equations.
///
///     NOTE: info only stores the first occurrence of
///     a singularity, any subsequent occurrence of singularity
///     is not stored in info even though the factorization
///     always completes.
///
/// @ingroup sysv_rk_computational
int64_t sytrf_rk(
    lapack::Uplo uplo, int64_t n,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* E,
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
    LAPACK_zsytrf_rk(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) E,
        ipiv_ptr,
        (lapack_complex_double*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );

    LAPACK_zsytrf_rk(
        &uplo_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) E,
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

#endif  // LAPACK >= 3.7
