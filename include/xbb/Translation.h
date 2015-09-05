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

#ifndef XBB_TRANSLATION_H
#define XBB_TRANSLATION_H

#include "Base.h"

namespace xbb {
    
    template <typename UserTypeT>
    struct TranslateValuesFrom
    {        
        static double x(const UserTypeT & /*iFrom*/)
        {
            assert(0 && "Caller must provide a specialization of TranslateValuesFrom<UserTypeT> for their type and implement the x(), y(), z() methods");
            return 1.0;
        }
        static double y(const UserTypeT & /*iFrom*/)
        {
            assert(0 && "Caller must provide a specialization of TranslateValuesFrom<UserTypeT> for their type and implement the x(), y(), z() methods");
            return 1.0;
        }
        static double z(const UserTypeT & /*iFrom*/)
        {
            assert(0 && "Caller must provide a specialization of TranslateValuesFrom<UserTypeT> for their type and implement the x(), y(), z() methods");
            return 1.0;
        }        
    };
    
    struct InverseTranslation;
    
    struct Translation : 
        public Base<Translation>
    {
        Translation()
        {
            // uninitialized
        }
        
        Translation(double iX, double iY, double iZ)
        : x(iX)
        , y(iY)
        , z(iZ)
        {}

        template<typename UserTypeT>
        Translation(const UserTypeT &iValue)
        : x(TranslateValuesFrom<UserTypeT>::x(iValue))
        , y(TranslateValuesFrom<UserTypeT>::y(iValue))
        , z(TranslateValuesFrom<UserTypeT>::z(iValue))
        {}
        
        void set(double iX, double iY, double iZ)
        {
            x = iX;
            y = iY;
            z = iZ;
        }
        
        double x;    
        double y;
        double z;

        static const InverseProvision inverseProvision = InverseProvided;        
        typedef InverseTranslation InverseType;
        inline InverseType inverse() const;
        
        double e00() const { return 1.0; }    
        double e01() const { return 0.0; }    
        double e02() const { return 0.0; }    
        double e03() const { return 0.0; }    
        
        double e10() const { return 0.0; }    
        double e11() const { return 1.0; }    
        double e12() const { return 0.0; }    
        double e13() const { return 0.0; }    
        
        double e20() const { return 0.0; }    
        double e21() const { return 0.0; }    
        double e22() const { return 1.0; }    
        double e23() const { return 0.0; }    
            
        double e30() const { return x; }    
        double e31() const { return y; }    
        double e32() const { return z; }    
        double e33() const { return 1.0; }           
        
        static const Constancy c00 = ConstantOne;
        static const Constancy c01 = ConstantZero;
        static const Constancy c02 = ConstantZero;
        static const Constancy c03 = ConstantZero;
        
        static const Constancy c10 = ConstantZero;
        static const Constancy c11 = ConstantOne;
        static const Constancy c12 = ConstantZero;
        static const Constancy c13 = ConstantZero;
        
        static const Constancy c20 = ConstantZero;
        static const Constancy c21 = ConstantZero;
        static const Constancy c22 = ConstantOne;
        static const Constancy c23 = ConstantZero;
            
        static const Constancy c30 = NotConstant;
        static const Constancy c31 = NotConstant;
        static const Constancy c32 = NotConstant;
        static const Constancy c33 = ConstantOne;        
        
    };
    
    struct InverseTranslation : 
        public Base<InverseTranslation>
    {
        InverseTranslation()
        {
            // uninitialized
        }
        
        
        InverseTranslation(double iX, double iY, double iZ)
        : x(iX)
        , y(iY)
        , z(iZ)
        {}

        template<typename UserTypeT>
        InverseTranslation(const UserTypeT &iValue)
        : x(TranslateValuesFrom<UserTypeT>::x(iValue))
        , y(TranslateValuesFrom<UserTypeT>::y(iValue))
        , z(TranslateValuesFrom<UserTypeT>::z(iValue))
        {}
        
        double x;    
        double y;
        double z;
        
        static const InverseProvision inverseProvision = InverseProvided;        
        typedef Translation InverseType;
        InverseType inverse() const { return InverseType(x, y, z); }
        
        
        double e00() const { return 1.0; }    
        double e01() const { return 0.0; }    
        double e02() const { return 0.0; }    
        double e03() const { return 0.0; }    
        
        double e10() const { return 0.0; }    
        double e11() const { return 1.0; }    
        double e12() const { return 0.0; }    
        double e13() const { return 0.0; }    
        
        double e20() const { return 0.0; }    
        double e21() const { return 0.0; }    
        double e22() const { return 1.0; }    
        double e23() const { return 0.0; }    
            
        double e30() const { return -x; }    
        double e31() const { return -y; }    
        double e32() const { return -z; }    
        double e33() const { return 1.0; }            
        
        static const Constancy c00 = ConstantOne;
        static const Constancy c01 = ConstantZero;
        static const Constancy c02 = ConstantZero;
        static const Constancy c03 = ConstantZero;
        
        static const Constancy c10 = ConstantZero;
        static const Constancy c11 = ConstantOne;
        static const Constancy c12 = ConstantZero;
        static const Constancy c13 = ConstantZero;
        
        static const Constancy c20 = ConstantZero;
        static const Constancy c21 = ConstantZero;
        static const Constancy c22 = ConstantOne;
        static const Constancy c23 = ConstantZero;
            
        static const Constancy c30 = NotConstant;
        static const Constancy c31 = NotConstant;
        static const Constancy c32 = NotConstant;
        static const Constancy c33 = ConstantOne;        
    };    
    
    
    Translation::InverseType 
    Translation::inverse() const 
    { 
        return InverseType(x, y, z); 
    }
    
} // namespace xbb     

#endif // XBB_TRANSLATION_H
