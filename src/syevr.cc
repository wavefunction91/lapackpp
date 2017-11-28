#include "lapack.hh"
#include "lapack_fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
int64_t syevr(
    lapack::Job jobz, lapack::Range range, lapack::Uplo uplo, int64_t n,
    float* A, int64_t lda, float vl, float vu, int64_t il, int64_t iu, float abstol,
    int64_t* m,
    float* W,
    float* Z, int64_t ldz,
    int64_t* isuppz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(il) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(iu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char range_ = range2char( range );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int il_ = (blas_int) il;
    blas_int iu_ = (blas_int) iu;
    blas_int m_ = (blas_int) *m;
    blas_int ldz_ = (blas_int) ldz;
    #if 1
        // 32-bit copy
        std::vector< blas_int > isuppz_( (2*max( 1, n )) );  // was max(1,m), n >= m
        blas_int* isuppz_ptr = &isuppz_[0];
    #else
        blas_int* isuppz_ptr = isuppz;
    #endif
    blas_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_ssyevr( &jobz_, &range_, &uplo_, &n_, A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &m_, W, Z, &ldz_, isuppz_ptr, qry_work, &ineg_one, qry_iwork, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );
    std::vector< blas_int > iwork( liwork_ );

    LAPACK_ssyevr( &jobz_, &range_, &uplo_, &n_, A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &m_, W, Z, &ldz_, isuppz_ptr, &work[0], &lwork_, &iwork[0], &liwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *m = m_;
    #if 1
        std::copy( isuppz_.begin(), isuppz_.end(), isuppz );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
int64_t syevr(
    lapack::Job jobz, lapack::Range range, lapack::Uplo uplo, int64_t n,
    double* A, int64_t lda, double vl, double vu, int64_t il, int64_t iu, double abstol,
    int64_t* m,
    double* W,
    double* Z, int64_t ldz,
    int64_t* isuppz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(blas_int)) {
        throw_if_( std::abs(n) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(lda) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(il) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(iu) > std::numeric_limits<blas_int>::max() );
        throw_if_( std::abs(ldz) > std::numeric_limits<blas_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char range_ = range2char( range );
    char uplo_ = uplo2char( uplo );
    blas_int n_ = (blas_int) n;
    blas_int lda_ = (blas_int) lda;
    blas_int il_ = (blas_int) il;
    blas_int iu_ = (blas_int) iu;
    blas_int m_ = (blas_int) *m;
    blas_int ldz_ = (blas_int) ldz;
    #if 1
        // 32-bit copy
        std::vector< blas_int > isuppz_( (2*max( 1, n )) );  // was max(1,m), n >= m
        blas_int* isuppz_ptr = &isuppz_[0];
    #else
        blas_int* isuppz_ptr = isuppz;
    #endif
    blas_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    blas_int qry_iwork[1];
    blas_int ineg_one = -1;
    LAPACK_dsyevr( &jobz_, &range_, &uplo_, &n_, A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &m_, W, Z, &ldz_, isuppz_ptr, qry_work, &ineg_one, qry_iwork, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    blas_int lwork_ = real(qry_work[0]);
    blas_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );
    std::vector< blas_int > iwork( liwork_ );

    LAPACK_dsyevr( &jobz_, &range_, &uplo_, &n_, A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &m_, W, Z, &ldz_, isuppz_ptr, &work[0], &lwork_, &iwork[0], &liwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    *m = m_;
    #if 1
        std::copy( isuppz_.begin(), isuppz_.end(), isuppz );
    #endif
    return info_;
}

}  // namespace lapack