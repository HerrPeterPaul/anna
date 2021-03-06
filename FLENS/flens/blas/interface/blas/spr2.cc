#include <flens/blas/interface/blas/config.h>


using namespace flens;

extern "C" {

void
BLAS(sspr2)(const char      *UPLO,
            const INTEGER   *N,
            const float     *ALPHA,
            const float     *X,
            const INTEGER   *INCX,
            const float     *Y,
            const INTEGER   *INCY,
            float           *AP)
{
#   ifdef TEST_DIRECT_CBLAS

        char    _UPLO   = toupper(*UPLO);

        StorageUpLo    upLo   = StorageUpLo(_UPLO);

        cblas_sspr2(CBLAS_ORDER::CblasColMajor,
                   cxxblas::CBLAS::getCblasType(upLo),
                   *N,
                   *ALPHA,
                   X, *INCX,
                   Y, *INCY,
                   AP);

#   else

        using std::abs;
        using std::max;

        char    _UPLO  = toupper(*UPLO);

#       ifndef NO_INPUT_CHECK
            INTEGER info  = 0;
            if (_UPLO!='U' && _UPLO!='L') {
                info = 1;
            } else if (*N<0) {
                info = 2;
            } else if (*INCX==0) {
                info = 5;
            } else if (*INCY==0) {
                info = 7;
            }
            if (info!=0) {
                BLAS(xerbla)("SSPR2 ", &info);
                return;
            }
#       endif

        StorageUpLo  upLo = StorageUpLo(_UPLO);

        SDenseVectorConstView  x(SConstArrayView(*N, X, abs(*INCX)), *INCX<0);
        SDenseVectorConstView  y(SConstArrayView(*N, Y, abs(*INCY)), *INCY<0);
        SSpMatrixView          A(SPackedView(*N, AP), upLo);

#       ifdef TEST_OVERLOADED_OPERATORS
            const auto alpha  = *ALPHA;

            A += alpha*x*transpose(y) + alpha*y*transpose(x);
#       else
            blas::r2(*ALPHA, x, y, A);
#       endif
#   endif
}

void
BLAS(dspr2)(const char      *UPLO,
            const INTEGER   *N,
            const double    *ALPHA,
            const double    *X,
            const INTEGER   *INCX,
            const double    *Y,
            const INTEGER   *INCY,
            double          *AP)
{
#   ifdef TEST_DIRECT_CBLAS

        char    _UPLO   = toupper(*UPLO);

        StorageUpLo    upLo   = StorageUpLo(_UPLO);

        cblas_dspr2(CBLAS_ORDER::CblasColMajor,
                    cxxblas::CBLAS::getCblasType(upLo),
                    *N,
                    *ALPHA,
                    X, *INCX,
                    Y, *INCY,
                    AP);

#   else

        using std::abs;
        using std::max;

        char    _UPLO  = toupper(*UPLO);

#       ifndef NO_INPUT_CHECK
            INTEGER info  = 0;
            if (_UPLO!='U' && _UPLO!='L') {
                info = 1;
            } else if (*N<0) {
                info = 2;
            } else if (*INCX==0) {
                info = 5;
            } else if (*INCY==0) {
                info = 7;
            }
            if (info!=0) {
                BLAS(xerbla)("DSPR2 ", &info);
                return;
            }
#       endif

        StorageUpLo  upLo = StorageUpLo(_UPLO);

        DDenseVectorConstView  x(DConstArrayView(*N, X, abs(*INCX)), *INCX<0);
        DDenseVectorConstView  y(DConstArrayView(*N, Y, abs(*INCY)), *INCY<0);
        DSpMatrixView          A(DPackedView(*N, AP), upLo);

#       ifdef TEST_OVERLOADED_OPERATORS
            const auto alpha  = *ALPHA;

            A += alpha*x*transpose(y) + alpha*y*transpose(x);
#       else
            blas::r2(*ALPHA, x, y, A);
#       endif
#   endif
}

} // extern "C"
