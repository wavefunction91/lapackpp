#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup gesvd
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    float* A, int64_t lda,
    float* S,
    float* U, int64_t ldu,
    float* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_sgesdd(
        &jobz_, &m_, &n_,
        A, &lda_,
        S,
        U, &ldu_,
        VT, &ldvt_,
        qry_work, &ineg_one,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_sgesdd(
        &jobz_, &m_, &n_,
        A, &lda_,
        S,
        U, &ldu_,
        VT, &ldvt_,
        &work[0], &lwork_,
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gesvd
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    double* A, int64_t lda,
    double* S,
    double* U, int64_t ldu,
    double* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_dgesdd(
        &jobz_, &m_, &n_,
        A, &lda_,
        S,
        U, &ldu_,
        VT, &ldvt_,
        qry_work, &ineg_one,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_dgesdd(
        &jobz_, &m_, &n_,
        A, &lda_,
        S,
        U, &ldu_,
        VT, &ldvt_,
        &work[0], &lwork_,
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// @ingroup gesvd
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    std::complex<float>* A, int64_t lda,
    float* S,
    std::complex<float>* U, int64_t ldu,
    std::complex<float>* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    float qry_rwork[1] = { 0 };
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_cgesdd(
        &jobz_, &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        S,
        (lapack_complex_float*) U, &ldu_,
        (lapack_complex_float*) VT, &ldvt_,
        (lapack_complex_float*) qry_work, &ineg_one,
        qry_rwork,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int lrwork_ = qry_rwork[0];
    if (lrwork_ == 0) {
        // if query doesn't work, this is from documentation
        blas_int mx = max( m, n );
        blas_int mn = min( m, n );
        if (jobz == lapack::Job::NoVec) {
            lrwork_ = 7*mn;  // LAPACK > 3.6 needs only 5*mn
        }
        else {
            lrwork_ = max( 5*mn*mn + 5*mn, 2*mx*mn + 2*mn*mn + mn );
        }
        lrwork_ = max( 1, lrwork_ );
    }

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );
    std::vector< float > rwork( lrwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_cgesdd(
        &jobz_, &m_, &n_,
        (lapack_complex_float*) A, &lda_,
        S,
        (lapack_complex_float*) U, &ldu_,
        (lapack_complex_float*) VT, &ldvt_,
        (lapack_complex_float*) &work[0], &lwork_,
        &rwork[0],
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Computes the singular value decomposition (SVD) of a
/// m-by-n matrix A, optionally computing the left and/or right singular
/// vectors, by using divide-and-conquer method. The SVD is written
///
///     \f[ A = U \Sigma V^H \f]
///
/// where \f$ \Sigma \f$ is an m-by-n matrix which is zero except for its
/// min(m,n) diagonal elements, U is an m-by-m unitary matrix, and
/// V is an n-by-n unitary matrix. The diagonal elements of \f$ \Sigma \f$
/// are the singular values of A; they are real and non-negative, and
/// are returned in descending order. The first min(m,n) columns of
/// U and V are the left and right singular vectors of A.
///
/// Note that the routine returns VT \f$ = V^H \f$, not V.
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
/// @param[in] jobz
///     Specifies options for computing all or part of the matrix U:
///     - lapack::Job::AllVec:
///         all m columns of U and all n rows of \f$ V^H \f$ are
///         returned in the arrays U and VT;
///     - lapack::Job::SomeVec:
///         the first min(m,n) columns of U and the first
///         min(m,n) rows of \f$ V^H \f$ are returned in the arrays U
///         and VT;
///     - lapack::Job::OverwriteVec:
///         + If m >= n, the first n columns of U are overwritten
///           in the array A and all rows of \f$ V^H \f$ are returned in
///           the array VT;
///
///         + otherwise, all columns of U are returned in the
///           array U and the first m rows of \f$ V^H \f$ are overwritten
///           in the array A;
///     - lapack::Job::NoVec:
///         no columns of U or rows of \f$ V^H \f$ are computed.
///
/// @param[in] m
///     The number of rows of the input matrix A. m >= 0.
///
/// @param[in] n
///     The number of columns of the input matrix A. n >= 0.
///
/// @param[in,out] A
///     The m-by-n matrix A, stored in an lda-by-n array.
///     On entry, the m-by-n matrix A.
///     On exit:
///     - If jobz = OverwriteVec,
///       + if m >= n, A is overwritten with the first n columns
///         of U (the left singular vectors, stored
///         columnwise);
///       + if m < n, A is overwritten with the first m rows
///         of \f$ V^H \f$ (the right singular vectors, stored
///         rowwise).
///     - Otherwise, the contents of A are destroyed.
///
/// @param[in] lda
///     The leading dimension of the array A. lda >= max(1,m).
///
/// @param[out] S
///     The vector S of length min(m,n).
///     The singular values of A, sorted so that S(i) >= S(i+1).
///
/// @param[out] U
///     The m-by-ucol matrix U, stored in an ldu-by-ucol array.
///     - If jobz = AllVec or (jobz = OverwriteVec and m < n),
///       ucol = m and U contains the m-by-m unitary matrix U;
///
///     - if jobz = SomeVec, ucol = min(m,n) and U contains the first min(m,n)
///       columns of U (the left singular vectors, stored columnwise);
///
///     - if (jobz = OverwriteVec and m >= n), or jobz = NoVec,
///       U is not referenced.
///
/// @param[in] ldu
///     The leading dimension of the array U. ldu >= 1;
///     if jobz = SomeVec or AllVec or (jobz = OverwriteVec and m < n), ldu >= m.
///
/// @param[out] VT
///     The vrow-by-n matrix VT, stored in an ldvt-by-n array.
///     - If jobz = AllVec or (jobz = OverwriteVec and m >= n),
///       vrow = n and VT contains the n-by-n unitary matrix \f$ V^H \f$;
///
///     - if jobz = SomeVec, vrow = min(m,n) and VT contains the first min(m,n)
///       rows of \f$ V^H \f$ (the right singular vectors, stored rowwise);
///
///     - if (jobz = OverwriteVec and m < n), or jobz = NoVec,
///       VT is not referenced.
///
/// @param[in] ldvt
///     The leading dimension of the array VT. ldvt >= 1;
///     - if jobz = AllVec or (jobz = OverwriteVec and m >= n), ldvt >= n;
///     - if jobz = SomeVec, ldvt >= min(m,n).
///
/// @retval = 0: successful exit.
/// @retval > 0: The updating process of `lapack::bdsdc` did not converge.
///
/// @ingroup gesvd
int64_t gesdd(
    lapack::Job jobz, int64_t m, int64_t n,
    std::complex<double>* A, int64_t lda,
    double* S,
    std::complex<double>* U, int64_t ldu,
    std::complex<double>* VT, int64_t ldvt )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldu) > std::numeric_limits<blas_int>::max() );
        lapack_error_if( std::abs(ldvt) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    blas_int m_ = (blas_int) m;
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int ldu_ = (blas_int) ldu;
    blas_int ldvt_ = (blas_int) ldvt;
    blas_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    double qry_rwork[1] = { 0 };
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_zgesdd(
        &jobz_, &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        S,
        (lapack_complex_double*) U, &ldu_,
        (lapack_complex_double*) VT, &ldvt_,
        (lapack_complex_double*) qry_work, &ineg_one,
        qry_rwork,
        qry_iwork, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int lrwork_ = qry_rwork[0];
    if (lrwork_ == 0) {
        // if query doesn't work, this is from documentation
        blas_int mx = max( m, n );
        blas_int mn = min( m, n );
        if (jobz == lapack::Job::NoVec) {
            lrwork_ = 7*mn;  // LAPACK > 3.6 needs only 5*mn
        }
        else {
            lrwork_ = max( 5*mn*mn + 5*mn, 2*mx*mn + 2*mn*mn + mn );
        }
        lrwork_ = max( 1, lrwork_ );
    }

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );
    std::vector< double > rwork( lrwork_ );
    std::vector< blas_int > iwork( (8*min(m,n)) );

    LAPACK_zgesdd(
        &jobz_, &m_, &n_,
        (lapack_complex_double*) A, &lda_,
        S,
        (lapack_complex_double*) U, &ldu_,
        (lapack_complex_double*) VT, &ldvt_,
        (lapack_complex_double*) &work[0], &lwork_,
        &rwork[0],
        &iwork[0], &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
