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

#ifndef XBB_MULTIPLY_H
#define XBB_MULTIPLY_H

#include "Base.h"
#include "detail/ConstancyByMatrixMultiply.h"
#include "Identity.h"
#include "ReducedMatrix.h"

namespace xbb {

    template <typename LeftT, typename RightT> struct Multiply;

    template <
        InverseProvision InverseLT, 
        InverseProvision InverseRT, 
        typename LeftT, 
        typename RightT>
    struct MultiplyInverseProvider
    {                
        static const InverseProvision inverseProvision = InverseDeprived;        
    };

    template <typename LeftT, typename RightT>
    struct MultiplyInverseProvider<InverseProvided, InverseProvided, LeftT, RightT>
    {                
        static const InverseProvision inverseProvision = InverseProvided;
        
        typedef Multiply<typename RightT::InverseType, typename LeftT::InverseType> InverseType;
        
        InverseType
        inverse() const
        {
            typedef Multiply<LeftT, RightT> Derived;
            const Derived & d = static_cast<const Derived &>(*this);

            return InverseType(d.right.inverse(), d.left.inverse());
        }        
    };
    
    
    template <typename LeftT, typename RightT>
    struct Multiply
        : public Base<Multiply<LeftT, RightT> >
        , public MultiplyInverseProvider<LeftT::inverseProvision, RightT::inverseProvision, LeftT, RightT >
    {
        Multiply()
        {}
        
        Multiply(const LeftT &aLeft, const RightT &aRight)
        : left(aLeft)
        , right(aRight)
        {
        }
        
//        const LeftT &left;
//        const RightT &right;
        LeftT left;
        RightT right;

        // Based on the Constancy of the elements of LeftT and RightT,
        // we should be able to see how the constancy of those elements
        // worths through the 4 multiples and 3 additions used to compute 
        // each element by a matrix multiply 
        static const Constancy c00 = detail::ConstancyByMatrixMultiply<0, 0, LeftT, RightT>::c;
        static const Constancy c01 = detail::ConstancyByMatrixMultiply<0, 1, LeftT, RightT>::c;
        static const Constancy c02 = detail::ConstancyByMatrixMultiply<0, 2, LeftT, RightT>::c;
        static const Constancy c03 = detail::ConstancyByMatrixMultiply<0, 3, LeftT, RightT>::c;
        
        static const Constancy c10 = detail::ConstancyByMatrixMultiply<1, 0, LeftT, RightT>::c;
        static const Constancy c11 = detail::ConstancyByMatrixMultiply<1, 1, LeftT, RightT>::c;
        static const Constancy c12 = detail::ConstancyByMatrixMultiply<1, 2, LeftT, RightT>::c;
        static const Constancy c13 = detail::ConstancyByMatrixMultiply<1, 3, LeftT, RightT>::c;
        
        static const Constancy c20 = detail::ConstancyByMatrixMultiply<2, 0, LeftT, RightT>::c;
        static const Constancy c21 = detail::ConstancyByMatrixMultiply<2, 1, LeftT, RightT>::c;
        static const Constancy c22 = detail::ConstancyByMatrixMultiply<2, 2, LeftT, RightT>::c;
        static const Constancy c23 = detail::ConstancyByMatrixMultiply<2, 3, LeftT, RightT>::c;
        
        static const Constancy c30 = detail::ConstancyByMatrixMultiply<3, 0, LeftT, RightT>::c;
        static const Constancy c31 = detail::ConstancyByMatrixMultiply<3, 1, LeftT, RightT>::c;
        static const Constancy c32 = detail::ConstancyByMatrixMultiply<3, 2, LeftT, RightT>::c;
        static const Constancy c33 = detail::ConstancyByMatrixMultiply<3, 3, LeftT, RightT>::c;
        
        typedef ReducedMatrix
        <
            c00, c01, c02, c03,
            c10, c11, c12, c13,
            c20, c21, c22, c23,
            c30, c31, c32, c33
        > ReducedType;

        ReducedType reduce() const
        {
            const auto tl = left.reduce();
            const auto tr = right.reduce();
            
            ReducedType r;

            // We could let left and right transforms return 1.0 and 0.0
            // and use them in general matrix multiply.
            // Results appeared good with the compiler removing 1.0 multiplies
            // and 0.0 multiplies and terms.
            //
            // However to be sure and not rely on that optimization
            // we can use partial template specialization to generate code
            // that only extracts the exact terms needed and only has the 
            // exact number of multiplies and additions needed based on the 
            // Constancy of the left and right.
            r.template setByMatrixMultiply<0,0>(tl,tr);
            r.template setByMatrixMultiply<0,1>(tl,tr);
            r.template setByMatrixMultiply<0,2>(tl,tr);
            r.template setByMatrixMultiply<0,3>(tl,tr);

            r.template setByMatrixMultiply<1,0>(tl,tr);
            r.template setByMatrixMultiply<1,1>(tl,tr);
            r.template setByMatrixMultiply<1,2>(tl,tr);
            r.template setByMatrixMultiply<1,3>(tl,tr);
            
            r.template setByMatrixMultiply<2,0>(tl,tr);
            r.template setByMatrixMultiply<2,1>(tl,tr);
            r.template setByMatrixMultiply<2,2>(tl,tr);
            r.template setByMatrixMultiply<2,3>(tl,tr);
            
            r.template setByMatrixMultiply<3,0>(tl,tr);
            r.template setByMatrixMultiply<3,1>(tl,tr);
            r.template setByMatrixMultiply<3,2>(tl,tr);
            r.template setByMatrixMultiply<3,3>(tl,tr);
            
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

#endif // XBB_MULTIPLY_H
