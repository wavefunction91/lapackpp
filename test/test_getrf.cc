#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"

#include <vector>
#include <omp.h>
#include <lapacke.h>

// -----------------------------------------------------------------------------
// simple overloaded wrappers around LAPACKE
int LAPACKE_getrf( int m, int n, float* A, int lda, int* ipiv )
{
    return LAPACKE_sgetrf( LAPACK_COL_MAJOR, m, n, A, lda, ipiv );
}

int LAPACKE_getrf( int m, int n, double* A, int lda, int* ipiv )
{
    return LAPACKE_dgetrf( LAPACK_COL_MAJOR, m, n, A, lda, ipiv );
}

int LAPACKE_getrf( int m, int n, std::complex<float>* A, int lda, int* ipiv )
{
    return LAPACKE_cgetrf( LAPACK_COL_MAJOR, m, n, A, lda, ipiv );
}

int LAPACKE_getrf( int m, int n, std::complex<double>* A, int lda, int* ipiv )
{
    return LAPACKE_zgetrf( LAPACK_COL_MAJOR, m, n, A, lda, ipiv );
}

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_getrf_work( Params& params, bool run )
{
    using namespace blas;
    typedef typename traits< scalar_t >::real_t real_t;
    typedef long long lld;

    // get & mark input values
    int64_t m = params.dim.m();
    int64_t n = params.dim.n();
    int64_t align   = params.align.value();
    int64_t verbose = params.verbose.value();

    // mark non-standard output values
    params.ref_time.value();
    params.ref_gflops.value();

    if (! run)
        return;

    // ---------- setup
    int64_t lda = roundup( max( 1, m ), align );
    size_t size_A = size_t(lda)*n;
    size_t size_ipiv = min(m,n);

    std::vector< scalar_t > A_tst( size_A );
    std::vector< scalar_t > A_ref( size_A );
    std::vector< int64_t > ipiv_tst( size_ipiv );
    std::vector< int     > ipiv_ref( size_ipiv );

    int64_t idist = 1;
    int64_t iseed[4] = { 1, 2, 3, 4 };
    lapack::larnv( idist, iseed, A_tst.size(), &A_tst[0] );
    A_ref = A_tst;

    if (verbose >= 1) {
        printf( "\n"
                "A m=%5lld, n=%5lld, lda=%5lld\n",
                m, n, lda );
    }
    if (verbose >= 2) {
        printf( "A = " ); print_matrix( m, n, &A_tst[0], lda );
    }

    // test error exits
    if (params.error_exit.value() == 'y') {
        assert_throw( lapack::getrf( -1,  n, &A_tst[0], lda, &ipiv_tst[0] ), lapack::Error );
        assert_throw( lapack::getrf(  m, -1, &A_tst[0], lda, &ipiv_tst[0] ), lapack::Error );
        assert_throw( lapack::getrf(  m,  n, &A_tst[0],  -1, &ipiv_tst[0] ), lapack::Error );
    }

    // ---------- run test
    libtest::flush_cache( params.cache.value() );
    double time = omp_get_wtime();
    int64_t info_tst = lapack::getrf( m, n, &A_tst[0], lda, &ipiv_tst[0] );
    time = omp_get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::getrf returned error %lld\n", (lld) info_tst );
    }

    double gflop = lapack::Gflop< scalar_t >::getrf( m, n );
    params.time.value()   = time;
    params.gflops.value() = gflop / time;

    if (verbose >= 2) {
        printf( "A2 = " ); print_matrix( m, n, &A_tst[0], lda );
    }

    if (params.ref.value() == 'y' || params.check.value() == 'y') {
        // ---------- run reference
        libtest::flush_cache( params.cache.value() );
        time = omp_get_wtime();
        int64_t info_ref = LAPACKE_getrf( m, n, &A_ref[0], lda, &ipiv_ref[0] );
        time = omp_get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_getrf returned error %lld\n", (lld) info_ref );
        }

        params.ref_time.value()   = time;
        params.ref_gflops.value() = gflop / time;

        if (verbose >= 2) {
            printf( "A2ref = " ); print_matrix( m, n, &A_ref[0], lda );
        }

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( A_tst, A_ref );
        error += abs_error( ipiv_tst, ipiv_ref );
        params.error.value() = error;
        params.okay.value() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_getrf( Params& params, bool run )
{
    switch (params.datatype.value()) {
        case libtest::DataType::Integer:
            throw std::exception();
            break;

        case libtest::DataType::Single:
            test_getrf_work< float >( params, run );
            break;

        case libtest::DataType::Double:
            test_getrf_work< double >( params, run );
            break;

        case libtest::DataType::SingleComplex:
            test_getrf_work< std::complex<float> >( params, run );
            break;

        case libtest::DataType::DoubleComplex:
            test_getrf_work< std::complex<double> >( params, run );
            break;
    }
}
