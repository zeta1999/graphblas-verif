//------------------------------------------------------------------------------
// GB_mex_qsort_1: sort using GB_qsort_1
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2018, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

#include "GB_mex.h"

void mexFunction
(
    int nargout,
    mxArray *pargout [ ],
    int nargin,
    const mxArray *pargin [ ]
)
{
    if (nargin != 1)
    {
        mexErrMsgTxt ("Usage: J = qsort (I)") ;
    }
    if (!mxIsClass (pargin [0], "int64"))
    {
        mexErrMsgTxt ("I must be a int64 array") ;
    }
    int64_t *I = mxGetData (pargin [0]) ;
    int64_t n = (uint64_t) mxGetNumberOfElements (pargin [0]) ;

    pargout [0] = mxCreateNumericMatrix (n, 1, mxINT64_CLASS, mxREAL) ;
    int64_t *J = mxGetData (pargout [0]) ;
    memcpy (J, I, n * sizeof (int64_t)) ;

    GB_qsort_1 (J, n) ;
}

