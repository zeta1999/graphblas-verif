//------------------------------------------------------------------------------
// GrB_eWiseMult_Vector: vector element-wise multiplication
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2018, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

// w<mask> = accum (w,u.*v)

#include "GB.h"

#define EWISE(op)                                                           \
{                                                                           \
    /* check inputs */                                                      \
    RETURN_IF_NULL_OR_UNINITIALIZED (w) ;                                   \
    RETURN_IF_NULL_OR_UNINITIALIZED (u) ;                                   \
    RETURN_IF_NULL_OR_UNINITIALIZED (v) ;                                   \
    RETURN_IF_UNINITIALIZED (mask) ;                                        \
    /* get the descriptor */                                                \
    GET_DESCRIPTOR (info, desc, C_replace, Mask_comp, ignore1, ignore2) ;   \
    /* C<mask> = accum (C,T) where T = A.*B, A'.*B, A.*B', or A'.*B' */     \
    return (GB_eWise (                                                      \
        (GrB_Matrix) w,    C_replace,   /* w and its descriptor         */  \
        (GrB_Matrix) mask, Mask_comp,   /* mask and its descriptor      */  \
        accum,                          /* for accum (w,t)              */  \
        op,                             /* operator that defines t=u.*v */  \
        (GrB_Matrix) u,    false,       /* u, never transposed          */  \
        (GrB_Matrix) v,    false,       /* v, never transposed          */  \
        false)) ;                       /* do eWiseMult                 */  \
}

//------------------------------------------------------------------------------
// GrB_eWiseMult_Vector_BinaryOp: vector element-wise multiplication
//------------------------------------------------------------------------------

GrB_Info GrB_eWiseMult_Vector_BinaryOp       // w<mask> = accum (w, u.*v)
(
    GrB_Vector w,                   // input/output vector for results
    const GrB_Vector mask,          // optional mask for w, unused if NULL
    const GrB_BinaryOp accum,       // optional accum for z=accum(w,t)
    const GrB_BinaryOp mult,        // defines '.*' for t=u.*v
    const GrB_Vector u,             // first input:  vector u
    const GrB_Vector v,             // second input: vector v
    const GrB_Descriptor desc       // descriptor for w and mask
)
{

    //--------------------------------------------------------------------------
    // check inputs
    //--------------------------------------------------------------------------

    WHERE ("GrB_eWiseMult_Vector_BinaryOp (w, mask, accum, mult, u, v, desc)") ;
    RETURN_IF_NULL_OR_UNINITIALIZED (mult) ;

    //--------------------------------------------------------------------------
    // apply the eWise kernel (using set intersection)
    //--------------------------------------------------------------------------

    EWISE (mult) ;
}

//------------------------------------------------------------------------------
// GrB_eWiseMult_Vector_Monoid: vector element-wise multiplication
//------------------------------------------------------------------------------

GrB_Info GrB_eWiseMult_Vector_Monoid         // w<mask> = accum (w, u.*v)
(
    GrB_Vector w,                   // input/output vector for results
    const GrB_Vector mask,          // optional mask for w, unused if NULL
    const GrB_BinaryOp accum,       // optional accum for z=accum(w,t)
    const GrB_Monoid monoid,        // defines '.*' for t=u.*v
    const GrB_Vector u,             // first input:  vector u
    const GrB_Vector v,             // second input: vector v
    const GrB_Descriptor desc       // descriptor for w and mask
)
{

    //--------------------------------------------------------------------------
    // check inputs
    //--------------------------------------------------------------------------

    WHERE ("GrB_eWiseMult_Vector_Monoid (w, mask, accum, monoid, u, v, desc)") ;
    RETURN_IF_NULL_OR_UNINITIALIZED (monoid) ;

    //--------------------------------------------------------------------------
    // eWise multiply using the monoid operator
    //--------------------------------------------------------------------------

    EWISE (monoid->op) ;
}

//------------------------------------------------------------------------------
// GrB_eWiseMult_Vector_Semiring: vector element-wise multiplication
//------------------------------------------------------------------------------

GrB_Info GrB_eWiseMult_Vector_Semiring       // w<Mask> = accum (w, u.*v)
(
    GrB_Vector w,                   // input/output vector for results
    const GrB_Vector mask,          // optional mask for w, unused if NULL
    const GrB_BinaryOp accum,       // optional accum for z=accum(w,t)
    const GrB_Semiring semiring,    // defines '.*' for t=u.*v
    const GrB_Vector u,             // first input:  vector u
    const GrB_Vector v,             // second input: vector v
    const GrB_Descriptor desc       // descriptor for w and mask
)
{

    //--------------------------------------------------------------------------
    // check inputs
    //--------------------------------------------------------------------------

    WHERE ("GrB_eWiseMult_Vector_Semiring (w, mask, accum, semiring, u, v, desc)") ;
    RETURN_IF_NULL_OR_UNINITIALIZED (semiring) ;

    //--------------------------------------------------------------------------
    // eWise multiply using the semiring's multiply operator
    //--------------------------------------------------------------------------

    EWISE (semiring->multiply) ;
}

#undef EWISE

