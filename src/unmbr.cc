#include "lapack.hh"
#include "lapack/fortran.h"

#include <vector>

namespace lapack {

using blas::max;
using blas::min;
using blas::real;

// -----------------------------------------------------------------------------
/// @ingroup gesvd_computational
int64_t unmbr(
    lapack::Vect vect, lapack::Side side, lapack::Op trans, int64_t m, int64_t n, int64_t k,
    std::complex<float> const* A, int64_t lda,
    std::complex<float> const* tau,
    std::complex<float>* C, int64_t ldc )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
    }
    char vect_ = vect2char( vect );
    char side_ = side2char( side );
    char trans_ = op2char( trans );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<float> qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_cunmbr(
        &vect_, &side_, &trans_, &m_, &n_, &k_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) C, &ldc_,
        (lapack_complex_float*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<float> > work( lwork_ );

    LAPACK_cunmbr(
        &vect_, &side_, &trans_, &m_, &n_, &k_,
        (lapack_complex_float*) A, &lda_,
        (lapack_complex_float*) tau,
        (lapack_complex_float*) C, &ldc_,
        (lapack_complex_float*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

// -----------------------------------------------------------------------------
/// Multiplies the general m-by-n matrix C by P or Q from `lapack::gebrd` as follows:
///
/// - If vect = Q:
///   - side = Left,  trans = NoTrans:   \f$ Q C \f$
///   - side = Right, trans = NoTrans:   \f$ C Q \f$
///   - side = Left,  trans = ConjTrans: \f$ Q^H C \f$
///   - side = Right, trans = ConjTrans: \f$ C Q^H \f$
///
/// - If vect = P:
///   - side = Left,  trans = NoTrans:   \f$ P C \f$
///   - side = Right, trans = NoTrans:   \f$ C P \f$
///   - side = Left,  trans = ConjTrans: \f$ P^H C \f$
///   - side = Right, trans = ConjTrans: \f$ C P^H \f$
///
/// Here \f$ Q \f$ and \f$ P^H \f$ are the unitary matrices determined by `lapack::gebrd` when
/// reducing a complex matrix A to bidiagonal form: \f$ A = Q B P^H. \f$
/// \f$ Q \f$ and \f$ P^H \f$ are defined as products of elementary reflectors H(i) and
/// G(i) respectively.
///
/// Let nq = m if side = Left and nq = n if side = Right. Thus nq is the
/// order of the unitary matrix \f$ Q \f$ or \f$ P^H \f$ that is applied.
///
/// - If vect = Q, A is assumed to have been an nq-by-k matrix:
///   - if nq >= k, \f$ Q = H(1) H(2) \dots H(k); \f$
///   - if nq <  k, \f$ Q = H(1) H(2) \dots H(nq-1). \f$
///
/// - If vect = P, A is assumed to have been a k-by-nq matrix:
///   - if k <  nq, \f$ P = G(1) G(2) \dots G(k); \f$
///   - if k >= nq, \f$ P = G(1) G(2) \dots G(nq-1). \f$
///
/// Overloaded versions are available for
/// `float`, `double`, `std::complex<float>`, and `std::complex<double>`.
/// For real matrices, this is an alias for `lapack::ormbr`.
///
/// @param[in] vect
///     - lapack::Vect::Q: apply \f$ Q \f$ or \f$ Q^H; \f$
///     - lapack::Vect::P: apply \f$ P \f$ or \f$ P^H. \f$
///
/// @param[in] side
///     - lapack::Side::Left:  apply \f$ Q, \f$ \f$ Q^H, \f$ \f$ P, \f$ or \f$ P^H \f$ from the Left;
///     - lapack::Side::Right: apply \f$ Q, \f$ \f$ Q^H, \f$ \f$ P, \f$ or \f$ P^H \f$ from the Right.
///
/// @param[in] trans
///     - lapack::Op::NoTrans:   No transpose, apply \f$ Q \f$ or \f$ P; \f$
///     - lapack::Op::ConjTrans: Conjugate transpose, apply \f$ Q^H \f$ or \f$ P^H. \f$
///
/// @param[in] m
///     The number of rows of the matrix C. m >= 0.
///
/// @param[in] n
///     The number of columns of the matrix C. n >= 0.
///
/// @param[in] k
///     - If vect = Q, the number of columns in the original
///     matrix reduced by `lapack::gebrd`.
///     - If vect = P, the number of rows in the original
///     matrix reduced by `lapack::gebrd`.
///     - k >= 0.
///
/// @param[in] A
///     The vector A of length lda,min(nq,k) if vect = Q; lda,nq if vect = P.
///         (lda,min(nq,k)) if vect = Q
///         (lda,nq) if vect = P
///     The vectors which define the elementary reflectors H(i) and
///     G(i), whose products determine the matrices Q and P, as
///     returned by `lapack::gebrd`.
///     - If vect = Q, the nq-by-min(nq,k) matrix A, stored in an lda-by-min(nq,k) array.
///     - if vect = P, the min(nq,k)-by-nq matrix A, stored in an lda-by-nq array.
///
/// @param[in] lda
///     The leading dimension of the array A.
///     - If vect = Q, lda >= max(1,nq);
///     - if vect = P, lda >= max(1,min(nq,k)).
///
/// @param[in] tau
///     The vector tau of length min(nq,k).
///     tau(i) must contain the scalar factor of the elementary
///     reflector H(i) or G(i) which determines Q or P, as returned
///     by `lapack::gebrd` in the array argument tauq or taup.
///
/// @param[in,out] C
///     The m-by-n matrix C, stored in an ldc-by-n array.
///     On entry, the m-by-n matrix C.
///     On exit, C is overwritten by one of
///     \f$ Q C, \f$ \f$ Q^H C, \f$ \f$ C Q^H, \f$    \f$ C Q, \f$
///     \f$ P C, \f$ \f$ P^H C, \f$ \f$ C P^H, \f$ or \f$ C P. \f$
///
/// @param[in] ldc
///     The leading dimension of the array C. ldc >= max(1,m).
///
/// @retval = 0: successful exit
///
/// @ingroup gesvd_computational
int64_t unmbr(
    lapack::Vect vect, lapack::Side side, lapack::Op trans, int64_t m, int64_t n, int64_t k,
    std::complex<double> const* A, int64_t lda,
    std::complex<double> const* tau,
    std::complex<double>* C, int64_t ldc )
{
    // check for overflow
    if (sizeof(int64_t) > sizeof(lapack_int)) {
        lapack_error_if( std::abs(m) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(n) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(k) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(lda) > std::numeric_limits<lapack_int>::max() );
        lapack_error_if( std::abs(ldc) > std::numeric_limits<lapack_int>::max() );
    }
    char vect_ = vect2char( vect );
    char side_ = side2char( side );
    char trans_ = op2char( trans );
    lapack_int m_ = (lapack_int) m;
    lapack_int n_ = (lapack_int) n;
    lapack_int k_ = (lapack_int) k;
    lapack_int lda_ = (lapack_int) lda;
    lapack_int ldc_ = (lapack_int) ldc;
    lapack_int info_ = 0;

    // query for workspace size
    std::complex<double> qry_work[1];
    lapack_int ineg_one = -1;
    LAPACK_zunmbr(
        &vect_, &side_, &trans_, &m_, &n_, &k_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) C, &ldc_,
        (lapack_complex_double*) qry_work, &ineg_one, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    lapack_int lwork_ = real(qry_work[0]);

    // allocate workspace
    std::vector< std::complex<double> > work( lwork_ );

    LAPACK_zunmbr(
        &vect_, &side_, &trans_, &m_, &n_, &k_,
        (lapack_complex_double*) A, &lda_,
        (lapack_complex_double*) tau,
        (lapack_complex_double*) C, &ldc_,
        (lapack_complex_double*) &work[0], &lwork_, &info_ );
    if (info_ < 0) {
        throw Error();
    }
    return info_;
}

}  // namespace lapack
