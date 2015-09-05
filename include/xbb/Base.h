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

#ifndef XBB_BASE_H
#define XBB_BASE_H

#if defined(DEBUG) || defined(_DEBUG)
    #define XBB_DEBUG
#endif

#ifdef XBB_DEBUG
    #include <cassert>
    #ifndef XBB_ASSERT
        #define XBB_ASSERT(expression) assert(expression)
    #endif
    #ifndef XBB_DEBUG_ONLY_VAR
        // Since we are in debug, this should be used, no need to attribute
        // it as unused
        #define XBB_DEBUG_ONLY_VAR(variable) variable
    #endif

    #ifndef XBB_INLINE_BLOCK
        #define XBB_INLINE_BLOCK 
    #endif

#else
    #ifndef SBB_ASSERT
        #define XBB_ASSERT(expression)
    #endif
    #ifndef XBB_DEBUG_ONLY_VAR
        #define XBB_DEBUG_ONLY_VAR(variable) __attribute__((unused)) variable
    #endif

    #if __INTEL_COMPILER >= 1100
        #ifndef XBB_INLINE_BLOCK
            #define XBB_INLINE_BLOCK \
                    _Pragma("forceinline recursive")
        #endif
    #else
        #ifndef XBB_INLINE_BLOCK
            #define XBB_INLINE_BLOCK 
        #endif
    #endif
#endif


#include <cassert>
#include <iosfwd>
#include <ostream>

#include "Constancy.h"
#include "InverseProvision.h"
#include "ElementAccess.h"
#include "detail/IsSameType.h"
//#include "Identity.h"

namespace xbb {
    

    template <typename UserTypeT>
    struct MatrixValuesTo
    {        
        static void e00(UserTypeT & iTo, double iValue)
        {
            assert( 0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e01(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e02(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }

        static void e03(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }

        static void e10(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e11(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e12(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }

        static void e13(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }

        static void e20(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e21(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e22(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        
        static void e23(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        
        static void e30(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e31(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }
        static void e32(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }        
        static void e33(UserTypeT & iTo, double iValue)
        {
            assert(0 && "Caller must provide a specialization of MatrixValuesTo<UserTypeT> for their type and implement the e?? methods");
        }        
    };                
    
    template <typename LeftT, typename RightT> struct Multiply;
    template <typename TransformT> struct Transpose;
    struct Matrix3x3;
    struct Matrix4x3;
    struct Identity;
    
    template<
        Constancy c00T, Constancy c01T, Constancy c02T, Constancy c03T,
        Constancy c10T, Constancy c11T, Constancy c12T, Constancy c13T,
        Constancy c20T, Constancy c21T, Constancy c22T, Constancy c23T,
        Constancy c30T, Constancy c31T, Constancy c32T, Constancy c33T
    >        
    struct ReducedMatrix;
    
    template<typename DerivedT>
    struct Base {
    protected:
        Base() {}
    public:
        
        template <typename OtherT>
        static bool is() {
            return detail::IsSameType<DerivedT, OtherT>::value;
        }

        // non-templated version so callers do not use the template keyword
        static bool isIdentity() {
            return is<xbb::Identity>();
        }
        
        template <typename UserMatrixTypeT>       
        void to(UserMatrixTypeT &aMat) const
        {
            const DerivedT & d = static_cast<const DerivedT &>(*this);
            
            MatrixValuesTo<UserMatrixTypeT>::e00(aMat, d.e00());
            MatrixValuesTo<UserMatrixTypeT>::e01(aMat, d.e01());
            MatrixValuesTo<UserMatrixTypeT>::e02(aMat, d.e02());
            MatrixValuesTo<UserMatrixTypeT>::e03(aMat, d.e03());

            MatrixValuesTo<UserMatrixTypeT>::e10(aMat, d.e10());
            MatrixValuesTo<UserMatrixTypeT>::e11(aMat, d.e11());
            MatrixValuesTo<UserMatrixTypeT>::e12(aMat, d.e12());
            MatrixValuesTo<UserMatrixTypeT>::e13(aMat, d.e13());
            
            MatrixValuesTo<UserMatrixTypeT>::e20(aMat, d.e20());
            MatrixValuesTo<UserMatrixTypeT>::e21(aMat, d.e21());
            MatrixValuesTo<UserMatrixTypeT>::e22(aMat, d.e22());
            MatrixValuesTo<UserMatrixTypeT>::e23(aMat, d.e23());

            MatrixValuesTo<UserMatrixTypeT>::e30(aMat, d.e30());
            MatrixValuesTo<UserMatrixTypeT>::e31(aMat, d.e31());
            MatrixValuesTo<UserMatrixTypeT>::e32(aMat, d.e32());
            MatrixValuesTo<UserMatrixTypeT>::e33(aMat, d.e33());            
        }       

        // To explicitly cast down to a 4x3 ignoring extra elements
        // versus requiring them to match Identity
        template <typename UserMatrixTypeT>       
        void to4x3(UserMatrixTypeT &aMat) const
        {
            const DerivedT & d = static_cast<const DerivedT &>(*this);
            // Purposefully ignore d.e03(), d.e13(), d.e23(), d.e33()
            
            MatrixValuesTo<UserMatrixTypeT>::e00(aMat, d.e00());
            MatrixValuesTo<UserMatrixTypeT>::e01(aMat, d.e01());
            MatrixValuesTo<UserMatrixTypeT>::e02(aMat, d.e02());

            MatrixValuesTo<UserMatrixTypeT>::e10(aMat, d.e10());
            MatrixValuesTo<UserMatrixTypeT>::e11(aMat, d.e11());
            MatrixValuesTo<UserMatrixTypeT>::e12(aMat, d.e12());
            
            MatrixValuesTo<UserMatrixTypeT>::e20(aMat, d.e20());
            MatrixValuesTo<UserMatrixTypeT>::e21(aMat, d.e21());
            MatrixValuesTo<UserMatrixTypeT>::e22(aMat, d.e22());

            MatrixValuesTo<UserMatrixTypeT>::e30(aMat, d.e30());
            MatrixValuesTo<UserMatrixTypeT>::e31(aMat, d.e31());
            MatrixValuesTo<UserMatrixTypeT>::e32(aMat, d.e32());
        }       

        // To explicitly cast down to a 3x3 ignoring extra elements
        // versus requiring them to match Identity
        template <typename UserMatrixTypeT>       
        void to3x3(UserMatrixTypeT &aMat) const
        {
            const DerivedT & d = static_cast<const DerivedT &>(*this);
            // Purposefully ignore d.e03(), d.e13(), d.e23(), d.e30(), d.e31(),
            // d.e32(), d.e32(), d.e33()
            MatrixValuesTo<UserMatrixTypeT>::e00(aMat, d.e00());
            MatrixValuesTo<UserMatrixTypeT>::e01(aMat, d.e01());
            MatrixValuesTo<UserMatrixTypeT>::e02(aMat, d.e02());

            MatrixValuesTo<UserMatrixTypeT>::e10(aMat, d.e10());
            MatrixValuesTo<UserMatrixTypeT>::e11(aMat, d.e11());
            MatrixValuesTo<UserMatrixTypeT>::e12(aMat, d.e12());
            
            MatrixValuesTo<UserMatrixTypeT>::e20(aMat, d.e20());
            MatrixValuesTo<UserMatrixTypeT>::e21(aMat, d.e21());
            MatrixValuesTo<UserMatrixTypeT>::e22(aMat, d.e22());
        }       
        
        
//        template <typename UserMatrixTypeT>       
//        operator UserMatrixTypeT() const
//        {
//            const DerivedT & d = static_cast<const DerivedT &>(*this);
//            
//            UserMatrixTypeT m;
//            ConvertToMatrix<UserMatrixTypeT>::from(d, m);
//            return m;
//        }

        const DerivedT &
        operator*(const Identity & /*aOther*/) const
        {
            const DerivedT & d = static_cast<const DerivedT &>(*this);
            return d;
        }
        
        template <typename OtherT>
        Multiply<DerivedT, OtherT>
        operator*(const OtherT &aOther) const
        {
            return Multiply<DerivedT, OtherT>(static_cast<const DerivedT &>(*this), aOther);
        }

        
        Transpose<DerivedT>
        transpose() const
        {
            return Transpose<DerivedT>(static_cast<const DerivedT &>(*this));
        }
        // Consider adding scalar multiplication, transpose, addition, subtraction
       
        typedef DerivedT ReducedType;

        const ReducedType & reduce() const
        {
            const DerivedT & d = static_cast<const DerivedT &>(*this);
            return d;
        }
        
        template<int RowT, int ColT>
        double e() const
        {
            const DerivedT & d = static_cast<const DerivedT &>(*this);            
            return ElementAccess<RowT, ColT>::e(d);
        }        
        
    };

    template<typename DerivedT>
    std::ostream& operator<<(std::ostream& iStream, const Base<DerivedT> & iMat)
    {
        iStream << std::endl <<
            "[" << iMat.template e<0,0>() << ", " << iMat.template e<0,1>() << ", " << iMat.template e<0,2>() << ", " << iMat.template e<0,3>() << "], [" << std::endl <<
            "[" << iMat.template e<1,0>() << ", " << iMat.template e<1,1>() << ", " << iMat.template e<1,2>() << ", " << iMat.template e<1,3>() << "], [" << std::endl <<
            "[" << iMat.template e<2,0>() << ", " << iMat.template e<2,1>() << ", " << iMat.template e<2,2>() << ", " << iMat.template e<2,3>() << "], [" << std::endl <<
            "[" << iMat.template e<3,0>() << ", " << iMat.template e<3,1>() << ", " << iMat.template e<3,2>() << ", " << iMat.template e<3,3>() << "]" << std::endl;
        return iStream;        
    }
    
} // namespace xbb     

#endif // XBB_BASE_H
