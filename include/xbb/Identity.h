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

#ifndef XBB_IDENTITY_H
#define XBB_IDENTITY_H

#include "Base.h"

namespace xbb {
    
    struct Identity : 
        public Base<Identity>
    {
        Identity()
        {}
        

        static const InverseProvision inverseProvision = InverseProvided;
        typedef Identity InverseType;
        inline InverseType inverse() const { return Identity(); }
        
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
            
        double e30() const { return 0.0; }    
        double e31() const { return 0.0; }    
        double e32() const { return 0.0; }    
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
            
        static const Constancy c30 = ConstantZero;
        static const Constancy c31 = ConstantZero;
        static const Constancy c32 = ConstantZero;
        static const Constancy c33 = ConstantOne;        
        
        
        // Identity multiplied by any other Transform
        // is just the other Transform
        // NOTE: return type is new instance vs.
        // a const & to enable predictable results when used inside of 
        // decltype() for templates.
        // Performance should not suffer due to 
        // return value optimization
        template <typename OtherT>
        OtherT 
        operator*(const OtherT &aOther) const
        {
            return aOther;
        }
        
    };
} // namespace xbb     

#endif // XBB_IDENTITY_H
