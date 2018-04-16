#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    float* A, int64_t lda,
    float* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (m) );

    LAPACK_sgerq2(
        &m_, &n_,
        A, &lda_,
        tau,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    double* A, int64_t lda,
    double* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (m) );

    LAPACK_dgerq2(
        &m_, &n_,
        A, &lda_,
        tau,
        &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<float> > work( (m) );

    LAPACK_cgerq2(
        &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes an RQ factorization of an m-by-n matrix A:
/// \f$ A = R Q \f$.
///
/// This is the unblocked Level 2 BLAS version of the algorithm.
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
///
/// @param[in] m
///     The number of rows of the matrix A. m >= 0.
///
/// @param[in] n
///     The number of columns of the matrix A. n >= 0.
///
/// @param[in,out] A
///     The m-by-n matrix A, stored in an lda-by-n array.
///     On entry, the m-by-n matrix A.
///     On exit:
///     - if m <= n, the upper triangle of the subarray
///     A(1:m,n-m+1:n) contains the m-by-m upper triangular matrix R;
///
///     - if m >= n, the elements on and above the (m-n)-th subdiagonal
///     contain the m-by-n upper trapezoidal matrix R.
///
///     - The remaining elements, with the array tau, represent the
///     unitary matrix Q as a product of min(m,n) elementary
///     reflectors (see Further Details).
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,m).
///
/// @param[out] tau
///     The vector tau of length min(m,n).
///     The scalar factors of the elementary reflectors (see Further
///     Details).
///
/// @retval = 0: successful exit
///
// -----------------------------------------------------------------------------
/// @par Further Details
///
/// The matrix Q is represented as a product of elementary reflectors
///
///     \f[ Q = H(1)^H H(2)^H \dots H(k)^H, \text{ where } k = \min(m,n). \f]
///
/// Each H(i) has the form
///
///     \f[ H(i) = I - \tau v v^H \f]
///
/// where \f$ \tau \f$ is a scalar, and v is a vector with
/// v(n-k+i+1:n) = 0 and v(n-k+i) = 1; conj(v(1:n-k+i-1)) is stored on
/// exit in A(m-k+i,1:n-k+i-1), and \f$ \tau \f$ in tau(i).
///
/// @ingroup gerqf
int64_t gerq2(
    int64_t m, int64_t n,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* tau )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int info_ = 0;

    // allocate workspace
    std::vector< std::complex<double> > work( (m) );

    LAPACK_zgerq2(
        &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) &work[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
