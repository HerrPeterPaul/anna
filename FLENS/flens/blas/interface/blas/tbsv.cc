#include <flens/blas/interface/blas/config.h>


using namespace flens;

extern "C" {

void
BLAS(stbsv)(const char      *UPLO,
            const char      *TRANS,
            const char      *DIAG,
            const INTEGER   *N,
            const INTEGER   *K,
            const float     *_A,
            const INTEGER   *LDA,
            float           *X,
            const INTEGER   *INCX)
{
#   ifdef TEST_DIRECT_CBLAS

        char    _UPLO   = toupper(*UPLO);
        char    _TRANS  = toupper(*TRANS);
        char    _DIAG   = toupper(*DIAG);

        StorageUpLo    upLo   = StorageUpLo(_UPLO);
        Transpose      trans = convertTo<Transpose>(_TRANS);
        Diag           diag   = Diag(_DIAG);

        cblas_stbsv(CBLAS_ORDER::CblasColMajor,
                    cxxblas::CBLAS::getCblasType(upLo),
                    cxxblas::CBLAS::getCblasType(trans),
                    cxxblas::CBLAS::getCblasType(diag),
                    *N, *K,
                    _A, *LDA, X, *INCX);

#   else
        using std::abs;
        using std::max;

        char    _UPLO  = toupper(*UPLO);
        char    _TRANS = toupper(*TRANS);
        char    _DIAG  = toupper(*DIAG);

#       ifndef NO_INPUT_CHECK
            INTEGER info  = 0;
            if (_UPLO!='U' && _UPLO!='L') {
                info = 1;
            } else if (_TRANS!='N' && _TRANS!='T' && _TRANS!='C') {
                info = 2;
            } else if (_DIAG!='U' && _DIAG!='N') {
                info = 3;
            } else if (*N<0) {
                info = 4;
            } else if (*K<0) {
                info = 5;
            } else if (*LDA<(*K + 1)) {
                info = 7;
            } else if (*INCX==0) {
                info = 9;
            }
            if (info!=0) {
                BLAS(xerbla)("STBSV ", &info);
                return;
            }
#       endif

        StorageUpLo  upLo  = StorageUpLo(_UPLO);
        Transpose    trans = convertTo<Transpose>(_TRANS);
        Diag         diag  = Diag(_DIAG);

        INTEGER      KL   = (upLo==Lower) ? *K : 0;
        INTEGER      KU   = (upLo==Upper) ? *K : 0;

        STbMatrixConstView  A(SBandConstView(*N, *N, KL, KU, _A, *LDA),
                              upLo, diag);
        SDenseVectorView    x(SArrayView(*N, X, abs(*INCX)), *INCX<0);

        blas::sv(trans, A, x);
#   endif
}

void
BLAS(dtbsv)(const char      *UPLO,
            const char      *TRANS,
            const char      *DIAG,
            const INTEGER   *N,
            const INTEGER   *K,
            const double    *_A,
            const INTEGER   *LDA,
            double          *X,
            const INTEGER   *INCX)
{
#   ifdef TEST_DIRECT_CBLAS

        char    _UPLO   = toupper(*UPLO);
        char    _TRANS  = toupper(*TRANS);
        char    _DIAG   = toupper(*DIAG);

        StorageUpLo    upLo   = StorageUpLo(_UPLO);
        Transpose      trans = convertTo<Transpose>(_TRANS);
        Diag           diag   = Diag(_DIAG);

        cblas_dtbsv(CBLAS_ORDER::CblasColMajor,
                    cxxblas::CBLAS::getCblasType(upLo),
                    cxxblas::CBLAS::getCblasType(trans),
                    cxxblas::CBLAS::getCblasType(diag),
                    *N, *K,
                    _A, *LDA, X, *INCX);

#   else
        using std::abs;
        using std::max;

        char    _UPLO  = toupper(*UPLO);
        char    _TRANS = toupper(*TRANS);
        char    _DIAG  = toupper(*DIAG);

#       ifndef NO_INPUT_CHECK
            INTEGER info  = 0;
            if (_UPLO!='U' && _UPLO!='L') {
                info = 1;
            } else if (_TRANS!='N' && _TRANS!='T' && _TRANS!='C') {
                info = 2;
            } else if (_DIAG!='U' && _DIAG!='N') {
                info = 3;
            } else if (*N<0) {
                info = 4;
            } else if (*K<0) {
                info = 5;
            } else if (*LDA<(*K + 1)) {
                info = 7;
            } else if (*INCX==0) {
                info = 9;
            }
            if (info!=0) {
                BLAS(xerbla)("DTBSV ", &info);
                return;
            }
#       endif

        StorageUpLo  upLo  = StorageUpLo(_UPLO);
        Transpose    trans = convertTo<Transpose>(_TRANS);
        Diag         diag  = Diag(_DIAG);

        INTEGER      KL   = (upLo==Lower) ? *K : 0;
        INTEGER      KU   = (upLo==Upper) ? *K : 0;

        DTbMatrixConstView  A(DBandConstView(*N, *N, KL, KU, _A, *LDA),
                              upLo, diag);
        DDenseVectorView    x(DArrayView(*N, X, abs(*INCX)), *INCX<0);

        blas::sv(trans, A, x);
#   endif
}

void
BLAS(ctbsv)(const char      *UPLO,
            const char      *TRANS,
            const char      *DIAG,
            const INTEGER   *N,
            const INTEGER   *K,
            const cfloat    *_A,
            const INTEGER   *LDA,
            cfloat          *X,
            const INTEGER   *INCX)
{
#   ifdef TEST_DIRECT_CBLAS

        char    _UPLO   = toupper(*UPLO);
        char    _TRANS  = toupper(*TRANS);
        char    _DIAG   = toupper(*DIAG);

        StorageUpLo    upLo   = StorageUpLo(_UPLO);
        Transpose      trans = convertTo<Transpose>(_TRANS);
        Diag           diag   = Diag(_DIAG);

        cblas_ctbmv(CBLAS_ORDER::CblasColMajor,
                    cxxblas::CBLAS::getCblasType(upLo),
                    cxxblas::CBLAS::getCblasType(trans),
                    cxxblas::CBLAS::getCblasType(diag),
                    *N, *K,
                    reinterpret_cast<const float *>(_A), *LDA,
                    reinterpret_cast<float *>(X), *INCX);

#   else
        using std::abs;
        using std::max;

        char    _UPLO  = toupper(*UPLO);
        char    _TRANS = toupper(*TRANS);
        char    _DIAG  = toupper(*DIAG);

#       ifndef NO_INPUT_CHECK
            INTEGER info  = 0;
            if (_UPLO!='U' && _UPLO!='L') {
                info = 1;
            } else if (_TRANS!='N' && _TRANS!='T' && _TRANS!='C') {
                info = 2;
            } else if (_DIAG!='U' && _DIAG!='N') {
                info = 3;
            } else if (*N<0) {
                info = 4;
            } else if (*K<0) {
                info = 5;
            } else if (*LDA<(*K + 1)) {
                info = 7;
            } else if (*INCX==0) {
                info = 9;
            }
            if (info!=0) {
                BLAS(xerbla)("CTBSV ", &info);
                return;
            }
#       endif

        StorageUpLo  upLo  = StorageUpLo(_UPLO);
        Transpose    trans = convertTo<Transpose>(_TRANS);
        Diag         diag  = Diag(_DIAG);

        INTEGER      KL   = (upLo==Lower) ? *K : 0;
        INTEGER      KU   = (upLo==Upper) ? *K : 0;

        CTbMatrixConstView  A(CBandConstView(*N, *N, KL, KU, _A, *LDA),
                              upLo, diag);
        CDenseVectorView    x(CArrayView(*N, X, abs(*INCX)), *INCX<0);

        blas::sv(trans, A, x);
#   endif
}

void
BLAS(ztbsv)(const char      *UPLO,
            const char      *TRANS,
            const char      *DIAG,
            const INTEGER   *N,
            const INTEGER   *K,
            const cdouble   *_A,
            const INTEGER   *LDA,
            cdouble         *X,
            const INTEGER   *INCX)
{
#   ifdef TEST_DIRECT_CBLAS

        char    _UPLO   = toupper(*UPLO);
        char    _TRANS  = toupper(*TRANS);
        char    _DIAG   = toupper(*DIAG);

        StorageUpLo    upLo   = StorageUpLo(_UPLO);
        Transpose      trans = convertTo<Transpose>(_TRANS);
        Diag           diag   = Diag(_DIAG);

        cblas_ztbmv(CBLAS_ORDER::CblasColMajor,
                    cxxblas::CBLAS::getCblasType(upLo),
                    cxxblas::CBLAS::getCblasType(trans),
                    cxxblas::CBLAS::getCblasType(diag),
                    *N, *K,
                    reinterpret_cast<const double *>(_A), *LDA,
                    reinterpret_cast<double *>(X), *INCX);

#   else
        using std::abs;
        using std::max;

        char    _UPLO  = toupper(*UPLO);
        char    _TRANS = toupper(*TRANS);
        char    _DIAG  = toupper(*DIAG);

#       ifndef NO_INPUT_CHECK
            INTEGER info  = 0;
            if (_UPLO!='U' && _UPLO!='L') {
                info = 1;
            } else if (_TRANS!='N' && _TRANS!='T' && _TRANS!='C') {
                info = 2;
            } else if (_DIAG!='U' && _DIAG!='N') {
                info = 3;
            } else if (*N<0) {
                info = 4;
            } else if (*K<0) {
                info = 5;
            } else if (*LDA<(*K + 1)) {
                info = 7;
            } else if (*INCX==0) {
                info = 9;
            }
            if (info!=0) {
                BLAS(xerbla)("ZTBSV ", &info);
                return;
            }
#       endif

        StorageUpLo  upLo  = StorageUpLo(_UPLO);
        Transpose    trans = convertTo<Transpose>(_TRANS);
        Diag         diag  = Diag(_DIAG);

        INTEGER      KL   = (upLo==Lower) ? *K : 0;
        INTEGER      KU   = (upLo==Upper) ? *K : 0;

        ZTbMatrixConstView  A(ZBandConstView(*N, *N, KL, KU, _A, *LDA),
                              upLo, diag);
        ZDenseVectorView    x(ZArrayView(*N, X, abs(*INCX)), *INCX<0);

        blas::sv(trans, A, x);
#   endif
}


} // extern "C"
