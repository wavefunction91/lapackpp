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
int64_t sbtrd(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n, int64_t kd,
    float* AB, int64_t ldab,
    float* D,
    float* E,
    float* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(kd) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int kd_ = (lapack_int) kd;
    lapack_int ldab_ = (lapack_int) ldab;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< float > work( (n) );

    LAPACK_ssbtrd(
        &jobz_, &uplo_, &n_, &kd_,
        AB, &ldab_,
        D,
        E,
        Q, &ldq_,
        &work[0], &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
int64_t sbtrd(
    lapack::Job jobz, lapack::Uplo uplo, int64_t n, int64_t kd,
    double* AB, int64_t ldab,
    double* D,
    double* E,
    double* Q, int64_t ldq )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(kd) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldab) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldq) > std::numeric_limits<lapack_int>::max() );
    }
    char jobz_ = job2char( jobz );
    char uplo_ = uplo2char( uplo );
    lapack_int n_ = (lapack_int) n;
    lapack_int kd_ = (lapack_int) kd;
    lapack_int ldab_ = (lapack_int) ldab;
    lapack_int ldq_ = (lapack_int) ldq;
    lapack_int info_ = 0;

    // allocate workspace
    std::vector< double > work( (n) );

    LAPACK_dsbtrd(
        &jobz_, &uplo_, &n_, &kd_,
        AB, &ldab_,
        D,
        E,
        Q, &ldq_,
        &work[0], &info_
        #ifdef LAPACK_FORTRAN_STRLEN_END
        , 1, 1
        #endif
    );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
