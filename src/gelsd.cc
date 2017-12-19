#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup gels
int64_t gelsd(
    int64_t m, int64_t n, int64_t nrhs,
    float* A, int64_t lda,
    float* B, int64_t ldb,
    float* S, float rcond,
    int64_t* rank )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int rank_ = (blas_int) *rank;
    blas_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_sgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, qry_work, &ineg_one, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int liwork_ = qry_iwork[0];

    // allocate workspace
    std::vector< float > work( lwork_ );
    std::vector< blas_int > iwork( liwork_ );

    LAPACK_sgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, &work[0], &lwork_, &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *rank = rank_;
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gels
int64_t gelsd(
    int64_t m, int64_t n, int64_t nrhs,
    double* A, int64_t lda,
    double* B, int64_t ldb,
    double* S, double rcond,
    int64_t* rank )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int rank_ = (blas_int) *rank;
    blas_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_dgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, qry_work, &ineg_one, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int liwork_ = qry_iwork[0];

    // allocate workspace
    std::vector< double > work( lwork_ );
    std::vector< blas_int > iwork( liwork_ );

    LAPACK_dgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, &work[0], &lwork_, &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *rank = rank_;
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gels
int64_t gelsd(
    int64_t m, int64_t n, int64_t nrhs,
    std::complex<float>* A, int64_t lda,
    std::complex<float>* B, int64_t ldb,
    float* S, float rcond,
    int64_t* rank )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int rank_ = (blas_int) *rank;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_cgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, qry_work, &ineg_one, qry_rwork, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int lrwork_ = qry_rwork[0];
    blas_int liwork_ = qry_iwork[0];

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );
    std::vector< float > rwork( lrwork_ );
    std::vector< blas_int > iwork( liwork_ );

    LAPACK_cgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, &work[0], &lwork_, &rwork[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *rank = rank_;
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes the minimum-norm solution to a real linear least
/// squares problem:
///     minimize \f$ || b - A x ||_2 \f$
/// using the singular value decomposition (SVD) of A. A is an m-by-n
/// matrix which may be rank-deficient.
///
/// Several right hand side vectors b and solution vectors x can be
/// handled in a single call; they are stored as the columns of the
/// m-by-nrhs right hand side matrix B and the n-by-nrhs solution
/// matrix X.
///
/// The problem is solved in three steps:
/// (1) Reduce the coefficient matrix A to bidiagonal form with
///     Householder transformations, reducing the original problem
///     into a "bidiagonal least squares problem" (BLS)
/// (2) Solve the BLS using a divide and conquer approach.
/// (3) Apply back all the Householder transformations to solve
///     the original least squares problem.
///
/// The effective rank of A is determined by treating as zero those
/// singular values which are less than rcond times the largest singular
/// value.
///
/// The divide and conquer algorithm makes very mild assumptions about
/// floating point arithmetic. It will work on machines with a guard
/// digit in add/subtract, or on those binary machines without guard
/// digits which subtract like the Cray X-MP, Cray Y-MP, Cray C-90, or
/// Cray-2. It could conceivably fail on hexadecimal or decimal machines
/// without guard digits, but we know of none.
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
/// @param[in] nrhs
///     The number of right hand sides, i.e., the number of columns
///     of the matrices B and X. nrhs >= 0.
///
/// @param[in,out] A
///     The m-by-n matrix A, stored in an lda-by-n array.
///     On entry, the m-by-n matrix A.
///     On exit, A has been destroyed.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,m).
///
/// @param[in,out] B
///     The max(m,n)-by-nrhs matrix B or X, stored in an ldb-by-nrhs array.
///     On entry, the m-by-nrhs right hand side matrix B.
///     On exit, B is overwritten by the n-by-nrhs solution matrix X.
///     If m >= n and rank = n, the residual sum-of-squares for
///     the solution in the i-th column is given by the sum of
///     squares of the modulus of elements n+1:m in that column.
///
/// @param[in] ldb
///     The leading dimension of the array B. ldb >= max(1,m,n).
///
/// @param[out] S
///     The vector S of length min(m,n).
///     The singular values of A in decreasing order.
///     The condition number of A in the 2-norm = S(1)/S(min(m,n)).
///
/// @param[in] rcond
///     rcond is used to determine the effective rank of A.
///     Singular values S(i) <= rcond*S(1) are treated as zero.
///     If rcond < 0, machine precision is used instead.
///
/// @param[out] rank
///     The effective rank of A, i.e., the number of singular values
///     which are greater than rcond*S(1).
///
/// @retval = 0: successful exit
/// @retval > 0: the algorithm for computing the SVD failed to converge;
///     if return value = i, i off-diagonal elements of an intermediate
///     bidiagonal form did not converge to zero.
///
/// @ingroup gels
int64_t gelsd(
    int64_t m, int64_t n, int64_t nrhs,
    std::complex<double>* A, int64_t lda,
    std::complex<double>* B, int64_t ldb,
    double* S, double rcond,
    int64_t* rank )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(m) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(nrhs) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldb) > std::numeric_limits<blas_int>::max() );
    }
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int nrhs_ = (blas_int) nrhs;
    blas_int lda_ = (blas_int) lda;
    blas_int ldb_ = (blas_int) ldb;
    blas_int rank_ = (blas_int) *rank;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_zgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, qry_work, &ineg_one, qry_rwork, qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int lrwork_ = qry_rwork[0];
    blas_int liwork_ = qry_iwork[0];

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );
    std::vector< double > rwork( lrwork_ );
    std::vector< blas_int > iwork( liwork_ );

    LAPACK_zgelsd( &m_, &n_, &nrhs_, A, &lda_, B, &ldb_, S, &rcond, &rank_, &work[0], &lwork_, &rwork[0], &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *rank = rank_;
    return info_;
}

}  // namespace lapack
