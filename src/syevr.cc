// Copyright (c) 2017-2020, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "lapack.hh"
#include "lapack/fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup heev
int64_t syevr(
    lapack::Job jobz, lapack::Range range, lapack::Uplo uplo, int64_t n,
    float* A, int64_t lda, float vl, float vu, int64_t il, int64_t iu, float abstol,
    int64_t* nfound,
    float* W,
    float* Z, int64_t ldz,
    int64_t* isuppz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(il) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(iu) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char range_ = range2char( range );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int il_ = (lapack_int) il;
    lapack_int iu_ = (lapack_int) iu;
    lapack_int nfound_;  // output
    lapack_int ldz_ = (lapack_int) ldz;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > isuppz_( (2*max( 1, n )) );  // was max(1,m), n >= m
        lapack_int* isuppz_ptr = &isuppz_[0];
    #else
        lapack_int* isuppz_ptr = isuppz;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    float qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_ssyevr(
        &jobz_, &range_, &uplo_, &n_,
        A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &nfound_,
        W,
        Z, &ldz_,
        isuppz_ptr,
        qry_work, &ineg_one,
        qry_iwork, &ineg_one, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);
    lapack_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    std::vector< float > work( lwork_ );
    std::vector< lapack_int > iwork( liwork_ );

    LAPACK_ssyevr(
        &jobz_, &range_, &uplo_, &n_,
        A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &nfound_,
        W,
        Z, &ldz_,
        isuppz_ptr,
        &work[0], &lwork_,
        &iwork[0], &liwork_, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    *nfound = nfound_;
    #ifndef LAPACK_ILP64
        std::copy( isuppz_.begin(), isuppz_.end(), isuppz );
    #endif
    return info_;
}

// -----------------------------------------------------------------------------
/// @see lapack::heevr
/// @ingroup heev
int64_t syevr(
    lapack::Job jobz, lapack::Range range, lapack::Uplo uplo, int64_t n,
    double* A, int64_t lda, double vl, double vu, int64_t il, int64_t iu, double abstol,
    int64_t* nfound,
    double* W,
    double* Z, int64_t ldz,
    int64_t* isuppz )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(il) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(iu) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldz) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char range_ = range2char( range );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int il_ = (lapack_int) il;
    lapack_int iu_ = (lapack_int) iu;
    lapack_int nfound_;  // output
    lapack_int ldz_ = (lapack_int) ldz;
    #ifndef LAPACK_ILP64
        // 32-bit copy
        std::vector< lapack_int > isuppz_( (2*max( 1, n )) );  // was max(1,m), n >= m
        lapack_int* isuppz_ptr = &isuppz_[0];
    #else
        lapack_int* isuppz_ptr = isuppz;
    #endif
    lapack_int info_ = 0;

    // query for workspace size
    double qry_work[1];
    lapack_int qry_iwork[1];
    lapack_int ineg_one = -1;
    LAPACK_dsyevr(
        &jobz_, &range_, &uplo_, &n_,
        A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &nfound_,
        W,
        Z, &ldz_,
        isuppz_ptr,
        qry_work, &ineg_one,
        qry_iwork, &ineg_one, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);
    lapack_int liwork_ = real(qry_iwork[0]);

    // allocate workspace
    std::vector< double > work( lwork_ );
    std::vector< lapack_int > iwork( liwork_ );

    LAPACK_dsyevr(
        &jobz_, &range_, &uplo_, &n_,
        A, &lda_, &vl, &vu, &il_, &iu_, &abstol, &nfound_,
        W,
        Z, &ldz_,
        isuppz_ptr,
        &work[0], &lwork_,
        &iwork[0], &liwork_, &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    *nfound = nfound_;
    #ifndef LAPACK_ILP64
        std::copy( isuppz_.begin(), isuppz_.end(), isuppz );
    #endif
    return info_;
}

}  // namespace lapack
