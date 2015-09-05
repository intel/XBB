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


#ifndef XBB_TRANSPOSE_H
#define XBB_TRANSPOSE_H

#include "Base.h"
#include "ReducedMatrix.h"

namespace xbb {

    template <typename TransformT> struct Transpose;

    template <
        InverseProvision InverseT, 
        typename TransformT>
    struct TransposeInverseProvider
    {                
        static const InverseProvision inverseProvision = InverseDeprived;        
    };

    template <typename TransformT>
    struct TransposeInverseProvider<InverseProvided, TransformT>
    {                
        static const InverseProvision inverseProvision = InverseProvided;
        
        typedef Transpose<typename TransformT::InverseType> InverseType;
        
        InverseType
        inverse() const
        {
            typedef Transpose<TransformT> Derived;
            const Derived & d = static_cast<const Derived &>(*this);

            return InverseType(d.transform.inverse());
        }        
    };
    
    
    template <typename TransformT>
    struct Transpose
        : public Base<Transpose<TransformT> >
        , public TransposeInverseProvider<TransformT::inverseProvision, TransformT >
    {
        Transpose()
        {
            // uninitialized
        }
        
        Transpose(const TransformT &aTransform)
        : transform(aTransform)
        {
        }
        
        TransformT transform;

        TransformT
        transpose() const
        {
            return transform;
        }
        
        // transposed constancy 
        static const Constancy c00 = TransformT::c00;
        static const Constancy c01 = TransformT::c10;
        static const Constancy c02 = TransformT::c20;
        static const Constancy c03 = TransformT::c30;
        
        static const Constancy c10 = TransformT::c01;
        static const Constancy c11 = TransformT::c11;
        static const Constancy c12 = TransformT::c21;
        static const Constancy c13 = TransformT::c31;
        
        static const Constancy c20 = TransformT::c02;
        static const Constancy c21 = TransformT::c12;
        static const Constancy c22 = TransformT::c22;
        static const Constancy c23 = TransformT::c32;
        
        static const Constancy c30 = TransformT::c03;
        static const Constancy c31 = TransformT::c13;
        static const Constancy c32 = TransformT::c23;
        static const Constancy c33 = TransformT::c33;
        
        typedef ReducedMatrix
        <
            c00, c01, c02, c03,
            c10, c11, c12, c13,
            c20, c21, c22, c23,
            c30, c31, c32, c33
        > ReducedType;

        ReducedType reduce() const
        {
            const auto t = transform.reduce();
            
            ReducedType r;

            r.template setByTranspose<0,0>(t);
            r.template setByTranspose<0,1>(t);
            r.template setByTranspose<0,2>(t);
            r.template setByTranspose<0,3>(t);

            r.template setByTranspose<1,0>(t);
            r.template setByTranspose<1,1>(t);
            r.template setByTranspose<1,2>(t);
            r.template setByTranspose<1,3>(t);
            
            r.template setByTranspose<2,0>(t);
            r.template setByTranspose<2,1>(t);
            r.template setByTranspose<2,2>(t);
            r.template setByTranspose<2,3>(t);
            
            r.template setByTranspose<3,0>(t);
            r.template setByTranspose<3,1>(t);
            r.template setByTranspose<3,2>(t);
            r.template setByTranspose<3,3>(t);
            
            return r;
        }                
               
        template <typename UserMatrixTypeT>       
        void to(UserMatrixTypeT &aMat) const
        {
            const auto r = reduce();
            
            MatrixValuesTo<UserMatrixTypeT>::e00(aMat, r.e00());
            MatrixValuesTo<UserMatrixTypeT>::e01(aMat, r.e01());
            MatrixValuesTo<UserMatrixTypeT>::e02(aMat, r.e02());
            MatrixValuesTo<UserMatrixTypeT>::e03(aMat, r.e03());

            MatrixValuesTo<UserMatrixTypeT>::e10(aMat, r.e10());
            MatrixValuesTo<UserMatrixTypeT>::e11(aMat, r.e11());
            MatrixValuesTo<UserMatrixTypeT>::e12(aMat, r.e12());
            MatrixValuesTo<UserMatrixTypeT>::e13(aMat, r.e13());
            
            MatrixValuesTo<UserMatrixTypeT>::e20(aMat, r.e20());
            MatrixValuesTo<UserMatrixTypeT>::e21(aMat, r.e21());
            MatrixValuesTo<UserMatrixTypeT>::e22(aMat, r.e22());
            MatrixValuesTo<UserMatrixTypeT>::e23(aMat, r.e23());

            MatrixValuesTo<UserMatrixTypeT>::e30(aMat, r.e30());
            MatrixValuesTo<UserMatrixTypeT>::e31(aMat, r.e31());
            MatrixValuesTo<UserMatrixTypeT>::e32(aMat, r.e32());
            MatrixValuesTo<UserMatrixTypeT>::e33(aMat, r.e33());            
        }       
       
        // To explicitly cast down to a 4x3 ignoring extra elements
        // versus requiring them to match Identity
        template <typename UserMatrixTypeT>       
        void to4x3(UserMatrixTypeT &aMat) const
        {
            const auto r = reduce();
            // Purposefully ignore d.e03(), d.e13(), d.e23(), d.e33()
            
            MatrixValuesTo<UserMatrixTypeT>::e00(aMat, r.e00());
            MatrixValuesTo<UserMatrixTypeT>::e01(aMat, r.e01());
            MatrixValuesTo<UserMatrixTypeT>::e02(aMat, r.e02());

            MatrixValuesTo<UserMatrixTypeT>::e10(aMat, r.e10());
            MatrixValuesTo<UserMatrixTypeT>::e11(aMat, r.e11());
            MatrixValuesTo<UserMatrixTypeT>::e12(aMat, r.e12());
            
            MatrixValuesTo<UserMatrixTypeT>::e20(aMat, r.e20());
            MatrixValuesTo<UserMatrixTypeT>::e21(aMat, r.e21());
            MatrixValuesTo<UserMatrixTypeT>::e22(aMat, r.e22());

            MatrixValuesTo<UserMatrixTypeT>::e30(aMat, r.e30());
            MatrixValuesTo<UserMatrixTypeT>::e31(aMat, r.e31());
            MatrixValuesTo<UserMatrixTypeT>::e32(aMat, r.e32());
        }       

        // To explicitly cast down to a 3x3 ignoring extra elements
        // versus requiring them to match Identity
        template <typename UserMatrixTypeT>       
        void to3x3(UserMatrixTypeT &aMat) const
        {
            const auto r = reduce();
            // Purposefully ignore d.e03(), d.e13(), d.e23(), d.e30(), d.e31(),
            // d.e32(), d.e32(), d.e33()
            
            MatrixValuesTo<UserMatrixTypeT>::e00(aMat, r.e00());
            MatrixValuesTo<UserMatrixTypeT>::e01(aMat, r.e01());
            MatrixValuesTo<UserMatrixTypeT>::e02(aMat, r.e02());

            MatrixValuesTo<UserMatrixTypeT>::e10(aMat, r.e10());
            MatrixValuesTo<UserMatrixTypeT>::e11(aMat, r.e11());
            MatrixValuesTo<UserMatrixTypeT>::e12(aMat, r.e12());
            
            MatrixValuesTo<UserMatrixTypeT>::e20(aMat, r.e20());
            MatrixValuesTo<UserMatrixTypeT>::e21(aMat, r.e21());
            MatrixValuesTo<UserMatrixTypeT>::e22(aMat, r.e22());
        }               

        
    };

    
} // namespace xbb     

#endif // XBB_TRANSPOSE_H
