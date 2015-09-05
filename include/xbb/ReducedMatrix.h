/*
Copyright (c) 2014, Intel Corporation

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef XBB_REDUCED_MATRIX_H
#define XBB_REDUCED_MATRIX_H

#include "Base.h"
#include "detail/ConstancyAccess.h"
#include "detail/ElementMultiplier.h"
#include "detail/Entry.h"
#include "ProxyMatrix.h"

namespace xbb {

// We use inheritance to allow Entries with no data members to be 0 sized.
// If we had the Entries as data members then they would take a minimum of 1 
// byte and with data member alignment rules more space would be taken.
//
// To access the inherited Entries, we just specify the base class to access
// before calling the method.  IE:  To access the value of the entry for 
// row 3 and column 1, we just call
// Entry<3, 1>::value()
// It may look like a static function but its really just using scope resolution
// to access the correct base class's value method.
//
// With this approach a ReducedMatrix will have exactly the right number of 
// NonConstant entries and take no more space than necessary, and more 
// importantly when participating in matrix multiplication, can utilize
// the Constancy of each entry to eliminate multiplies and additions based
// on any Constants involved
template<
    Constancy c00T, Constancy c01T, Constancy c02T, Constancy c03T,
    Constancy c10T, Constancy c11T, Constancy c12T, Constancy c13T,
    Constancy c20T, Constancy c21T, Constancy c22T, Constancy c23T,
    Constancy c30T, Constancy c31T, Constancy c32T, Constancy c33T
>        
struct ReducedMatrix : 
    public Base<ReducedMatrix<
        c00T, c01T, c02T, c03T,
        c10T, c11T, c12T, c13T,
        c20T, c21T, c22T, c23T,
        c30T, c31T, c32T, c33T> 
    >,
    public detail::Entry<0, 0, c00T>,
    public detail::Entry<0, 1, c01T>,
    public detail::Entry<0, 2, c02T>,
    public detail::Entry<0, 3, c03T>,

    public detail::Entry<1, 0, c10T>,
    public detail::Entry<1, 1, c11T>,
    public detail::Entry<1, 2, c12T>,
    public detail::Entry<1, 3, c13T>,

    public detail::Entry<2, 0, c20T>,
    public detail::Entry<2, 1, c21T>,
    public detail::Entry<2, 2, c22T>,
    public detail::Entry<2, 3, c23T>,
    
    public detail::Entry<3, 0, c30T>,
    public detail::Entry<3, 1, c31T>,
    public detail::Entry<3, 2, c32T>,
    public detail::Entry<3, 3, c33T>
{
    ReducedMatrix() 
    { 
        // uninitialized 
    }

    static const InverseProvision inverseProvision = InverseDeprived;        
        
    // Column # Row #

    double e00() const { return detail::Entry<0, 0, c00T>::value(); }    
    double e01() const { return detail::Entry<0, 1, c01T>::value(); }    
    double e02() const { return detail::Entry<0, 2, c02T>::value(); }    
    double e03() const { return detail::Entry<0, 3, c03T>::value(); }    

    double e10() const { return detail::Entry<1, 0, c10T>::value(); }    
    double e11() const { return detail::Entry<1, 1, c11T>::value(); }    
    double e12() const { return detail::Entry<1, 2, c12T>::value(); }    
    double e13() const { return detail::Entry<1, 3, c13T>::value(); }    

    double e20() const { return detail::Entry<2, 0, c20T>::value(); }    
    double e21() const { return detail::Entry<2, 1, c21T>::value(); }    
    double e22() const { return detail::Entry<2, 2, c22T>::value(); }    
    double e23() const { return detail::Entry<2, 3, c23T>::value(); }    

    double e30() const { return detail::Entry<3, 0, c30T>::value(); }    
    double e31() const { return detail::Entry<3, 1, c31T>::value(); }    
    double e32() const { return detail::Entry<3, 2, c32T>::value(); }    
    double e33() const { return detail::Entry<3, 3, c33T>::value(); }            

    static const Constancy c00 = c00T;
    static const Constancy c01 = c01T;
    static const Constancy c02 = c02T;
    static const Constancy c03 = c03T;

    static const Constancy c10 = c10T;
    static const Constancy c11 = c11T;
    static const Constancy c12 = c12T;
    static const Constancy c13 = c13T;

    static const Constancy c20 = c20T;
    static const Constancy c21 = c21T;
    static const Constancy c22 = c22T;
    static const Constancy c23 = c23T;

    static const Constancy c30 = c30T;
    static const Constancy c31 = c31T;
    static const Constancy c32 = c32T;
    static const Constancy c33 = c33T;           
    
    
    template<int LeftRowT, int RightColT,
            typename LeftT, typename RightT>
    void setByMatrixMultiply(const LeftT & iLeft, const RightT &iRight) 
    { 
        using namespace detail;
        
        const Constancy entryConstancy = ConstancyAccess<LeftRowT, RightColT, ReducedMatrix>::c;

        // This a matrix multiply iLeft times iRight
        // so we multiply and add individual entries from left and right
        // IE:
        //    Entry<LeftRowT, RightColT, entryConstancy>::set(
        //        iLeft.template e<LeftRowT, 0>()*iRight.template e<0,RightColT>() +
        //        iLeft.template e<LeftRowT, 1>()*iRight.template e<1,RightColT>() +
        //        iLeft.template e<LeftRowT, 2>()*iRight.template e<2,RightColT>() +
        //        iLeft.template e<LeftRowT, 3>()*iRight.template e<3,RightColT>());
        // 
        // But we can do even better by using template specialization to not even
        // access constant elements or multiply by constants or add 0

        // conditional known at compile time
        // dead code elimination will get rid of this block for any constant
        // entries
        if (entryConstancy == NotConstant) {
            const Constancy L0C = ConstancyAccess<LeftRowT, 0, LeftT>::c;
            const Constancy R0C = ConstancyAccess<0, RightColT, RightT>::c;

            const Constancy L1C = ConstancyAccess<LeftRowT, 1, LeftT>::c;
            const Constancy R1C = ConstancyAccess<1, RightColT, RightT>::c;

            const Constancy L2C = ConstancyAccess<LeftRowT, 2, LeftT>::c;
            const Constancy R2C = ConstancyAccess<2, RightColT, RightT>::c;

            const Constancy L3C = ConstancyAccess<LeftRowT, 3, LeftT>::c;
            const Constancy R3C = ConstancyAccess<3, RightColT, RightT>::c;


            Entry<LeftRowT, RightColT, entryConstancy>::set(
                ElementMultiplier<L0C, R0C>::template mul<LeftRowT, 0, RightColT>(iLeft, iRight)
                    .add(ElementMultiplier<L1C, R1C>::template mul<LeftRowT, 1, RightColT>(iLeft, iRight))
                    .add(ElementMultiplier<L2C, R2C>::template mul<LeftRowT, 2, RightColT>(iLeft, iRight))
                    .add(ElementMultiplier<L3C, R3C>::template mul<LeftRowT, 3, RightColT>(iLeft, iRight)).value()
            );
        }
    }
    
    template<int RowT, int ColT,
            typename TransformT>
    void setByTranspose(const TransformT & iTransform) 
    { 
        using namespace detail;
        
        const Constancy entryConstancy = ConstancyAccess<RowT, ColT, ReducedMatrix>::c;

        // But we can do even better by using template specialization to not even
        // access constant elements 

        // conditional known at compile time
        // dead code elimination will get rid of this block for any constant
        // entries
        if (entryConstancy == NotConstant) {
            // NOTE: when accessing iTransform we have transposed the row and column
            Entry<RowT, ColT, entryConstancy>::set(iTransform.template e<ColT, RowT>());
        }
    }    
};


// Enable ReducedMatrix to be used with a ProxyMatrix
// common use case is to mask out/off components
template<
    Constancy c00T, Constancy c01T, Constancy c02T, Constancy c03T,
    Constancy c10T, Constancy c11T, Constancy c12T, Constancy c13T,
    Constancy c20T, Constancy c21T, Constancy c22T, Constancy c23T,
    Constancy c30T, Constancy c31T, Constancy c32T, Constancy c33T
>  
struct MatrixValuesFrom<
    ReducedMatrix<
        c00T, c01T, c02T, c03T,
        c10T, c11T, c12T, c13T,
        c20T, c21T, c22T, c23T,
        c30T, c31T, c32T, c33T
    >
>
{        
    typedef ReducedMatrix<
        c00T, c01T, c02T, c03T,
        c10T, c11T, c12T, c13T,
        c20T, c21T, c22T, c23T,
        c30T, c31T, c32T, c33T> ReducedType;
    
    static double e00(const ReducedType & iFrom)
    {
        return iFrom.e00();
    }
    static double e01(const ReducedType & iFrom)
    {
        return iFrom.e01();
    }
    static double e02(const ReducedType & iFrom)
    {
        return iFrom.e02();
    }

    static double e03(const ReducedType & iFrom)
    {
        return iFrom.e03();
    }

    static double e10(const ReducedType & iFrom)
    {
        return iFrom.e10();
    }
    static double e11(const ReducedType & iFrom)
    {
        return iFrom.e11();
    }
    static double e12(const ReducedType & iFrom)
    {
        return iFrom.e12();
    }

    static double e13(const ReducedType & iFrom)
    {
        return iFrom.e13();
    }

    static double e20(const ReducedType & iFrom)
    {
        return iFrom.e20();
    }
    static double e21(const ReducedType & iFrom)
    {
        return iFrom.e21();
    }
    static double e22(const ReducedType & iFrom)
    {
        return iFrom.e22();
    }

    static double e23(const ReducedType & iFrom)
    {
        return iFrom.e23();
    }

    static double e30(const ReducedType & iFrom)
    {
        return iFrom.e30();
    }
    static double e31(const ReducedType & iFrom)
    {
        return iFrom.e31();
    }
    static double e32(const ReducedType & iFrom)
    {
        return iFrom.e32();
    }        
    static double e33(const ReducedType & iFrom)
    {
        return iFrom.e33();
    }        
};        
    
} // namespace xbb


#endif // XBB_REDUCED_MATRIX_H
