#include "test.hh"
#include "lapack.hh"
#include "lapack_flops.hh"
#include "print_matrix.hh"
#include "error.hh"
#include "lapacke_wrappers.hh"
#include "print_matrix.hh"

#include <vector>

#if LAPACK_VERSION >= 30700  // >= 3.7.0

// -----------------------------------------------------------------------------
template< typename scalar_t >
void test_tpmlqt_work( Params& params, bool run )
{
    using namespace libtest;
    using namespace blas;
    using real_t = blas::real_type< scalar_t >;
    typedef long long lld;

    // get & mark input values
    lapack::Side side = params.side();
    lapack::Op trans = params.trans();
    int64_t m = params.dim.m();
    int64_t n = params.dim.n();
    int64_t k = params.dim.k();
    int64_t l = params.l();
    int64_t nb = params.nb();
    int64_t align = params.align();
    int64_t verbose = params.verbose();

    // mark non-standard output values
    params.ref_time();
    params.ref_gflops();
    params.gflops();

    if (! run)
        return;

    if (k < l || k < nb || nb < 1) {
        printf( "skipping because tpmlqt requires k >= l >= 0 and k >= nb >= 1\n" );
        return;
    }

    // ---------- setup
    int64_t Vn = (side == Side::Left ? m : n);
    int64_t Am = (side == Side::Left ? k : m);
    int64_t An = (side == Side::Left ? n : k);
    int64_t ldv = roundup( max( 1, k  ), align );
    int64_t ldt = roundup( max( 1, nb ), align );
    int64_t lda = roundup( max( 1, Am ), align );
    int64_t ldb = roundup( max( 1, m  ), align );
    int64_t ldw = roundup( max( 1, k  ), align );
    size_t size_V  = (size_t) ldv * Vn;  // k-by-m (Left) or k-by-n (Right)
    size_t size_T  = (size_t) ldt * k;   // nb-by-k
    size_t size_A  = (size_t) lda * An;  // k-by-n (Left) or m-by-k (Right)
    size_t size_B  = (size_t) ldb * n;   // m-by-n
    size_t size_W0 = (size_t) ldw * k;   // k-by-k

    std::vector< scalar_t > V( size_V );
    std::vector< scalar_t > T( size_T );
    std::vector< scalar_t > A_tst( size_A );
    std::vector< scalar_t > A_ref( size_A );
    std::vector< scalar_t > B_tst( size_B );
    std::vector< scalar_t > B_ref( size_B );
    std::vector< scalar_t > W0( size_W0 );

    int64_t idist = 1;
    int64_t iseed[4] = { 0, 1, 2, 3 };
    lapack::larnv( idist, iseed, V.size(), &V[0] );
    lapack::larnv( idist, iseed, T.size(), &T[0] );
    lapack::larnv( idist, iseed, A_tst.size(), &A_tst[0] );
    lapack::larnv( idist, iseed, B_tst.size(), &B_tst[0] );
    lapack::larnv( idist, iseed, W0.size(), &W0[0] );
    A_ref = A_tst;
    B_ref = B_tst;

    // Get data for Householder reflectors in V and T by factoring matrix
    //     D = [ W0  V ] = LQ.
    // When applying Q = I - W T W^H with
    //     W = [ I  V ],
    // the left block, corresponding to W0, is identity, so isn't used in tpmlqt.
    // Using random data, without factoring, can lead to nan in tpmlqt.
    int64_t info = lapack::tplqt( k, Vn, l, nb, &W0[0], ldw, &V[0], ldv, &T[0], ldt );
    if (info != 0) {
        fprintf( stderr, "lapack::tplqt returned error %lld\n", (lld) info );
    }

    if (verbose > 1) {
        printf( "V =" ); print_matrix( k,  Vn, &V[0], ldv );
        printf( "T =" ); print_matrix( nb, k,  &T[0], ldt );
        printf( "A =" ); print_matrix( Am, An, &A_tst[0], lda );
        printf( "B =" ); print_matrix( m,  n,  &B_tst[0], ldb );
    }

    // ---------- run test
    libtest::flush_cache( params.cache() );
    double time = get_wtime();
    int64_t info_tst = lapack::tpmlqt( side, trans, m, n, k, l, nb, &V[0], ldv, &T[0], ldt, &A_tst[0], lda, &B_tst[0], ldb );
    time = get_wtime() - time;
    if (info_tst != 0) {
        fprintf( stderr, "lapack::tpmlqt returned error %lld\n", (lld) info_tst );
    }

    params.time() = time;
    double gflop = lapack::Gflop< scalar_t >::unmlq( side, m, n, k );  // estimate
    params.gflops() = gflop / time;

    if (verbose > 1) {
        printf( "Aout =" ); print_matrix( Am, An, &A_tst[0], lda );
        printf( "Bout =" ); print_matrix( m,  n,  &B_tst[0], ldb );
    }

    if (params.ref() == 'y' || params.check() == 'y') {
        // ---------- run reference
        libtest::flush_cache( params.cache() );
        time = get_wtime();
        int64_t info_ref = LAPACKE_tpmlqt( side2char(side), op2char(trans), m, n, k, l, nb, &V[0], ldv, &T[0], ldt, &A_ref[0], lda, &B_ref[0], ldb );
        time = get_wtime() - time;
        if (info_ref != 0) {
            fprintf( stderr, "LAPACKE_tpmlqt returned error %lld\n", (lld) info_ref );
        }

        params.ref_time() = time;
        params.ref_gflops() = gflop / time;

        if (verbose > 1) {
            printf( "Aref =" ); print_matrix( Am, An, &A_ref[0], lda );
            printf( "Bref =" ); print_matrix( m,  n,  &B_ref[0], ldb );
        }

        // ---------- check error compared to reference
        real_t error = 0;
        if (info_tst != info_ref) {
            error = 1;
        }
        error += abs_error( A_tst, A_ref );
        error += abs_error( B_tst, B_ref );
        params.error() = error;
        params.okay() = (error == 0);  // expect lapackpp == lapacke
    }
}

// -----------------------------------------------------------------------------
void test_tpmlqt( Params& params, bool run )
{
    switch (params.datatype()) {
        case libtest::DataType::Integer:
            throw std::exception();
            break;

        case libtest::DataType::Single:
            test_tpmlqt_work< float >( params, run );
            break;

        case libtest::DataType::Double:
            test_tpmlqt_work< double >( params, run );
            break;

        case libtest::DataType::SingleComplex:
            test_tpmlqt_work< std::complex<float> >( params, run );
            break;

        case libtest::DataType::DoubleComplex:
            test_tpmlqt_work< std::complex<double> >( params, run );
            break;
    }
}

#else

// -----------------------------------------------------------------------------
void test_tpmlqt( Params& params, bool run )
{
    fprintf( stderr, "tpmlqt requires LAPACK >= 3.7.0\n\n" );
    exit(0);
}

#endif  // LAPACK >= 3.7.0