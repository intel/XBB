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

#ifndef XBB_SHEAR_OF_H
#define XBB_SHEAR_OF_H

#include "Axis.h"
#include "Base.h"
#include "detail/NotConstantIfSheared.h"

namespace xbb {

   
template<Axis ShearedAxisT, Axis FixedAxisT> struct InverseShearOf; 
    
// Shear of a single axis by another axis, there are 6 possible combinations
// ShearOf can represent any of the 6 combinations.  For convenience there are
// typedefs for:
//    ShearOfXbyY
//    ShearOfXbyZ
//    ShearOfYbyX
//    ShearOfYbyZ
//    ShearOfZbyX
//    ShearOfZbyY

template<Axis ShearedAxisT, Axis FixedAxisT>
    struct ShearOf : 
        public Base< ShearOf<ShearedAxisT, FixedAxisT> >
    {
        ShearOf()
        {
            // unitialized
        }
        
        ShearOf(double iFactor)
        : factor(iFactor)
        {
            static_assert(ShearedAxisT != FixedAxisT, "The ShearedAxis != FixedAxis is illegal");
        }
        
        double factor;    

        static const InverseProvision inverseProvision = InverseProvided;   
        typedef InverseShearOf<ShearedAxisT, FixedAxisT> InverseType;
        inline InverseType inverse() const;
        
    private:
        // Bit of a workaround for C++ not supporting specialized template
        // member functions, turn enum into concrete type and 
        // overload all variations to provide same effect as template
        // specialization
        template<Constancy CT>
        struct OverloadTypeForEnum
        {};
        
        double getFactorWhen(OverloadTypeForEnum<ConstantZero>) const
        {
            return 0.0;
        }

        double getFactorWhen(OverloadTypeForEnum<ConstantOne>) const
        {
            return 1.0;
        }

        double getFactorWhen(OverloadTypeForEnum<NotConstant>) const
        {
            return factor;
        }
    public:
        
        double e00() const { return 1.0; }    
        double e01() const { return getFactorWhen(OverloadTypeForEnum<c01>()); }    
        double e02() const { return getFactorWhen(OverloadTypeForEnum<c02>()); }    
        double e03() const { return 0.0; }    
        
        double e10() const { return getFactorWhen(OverloadTypeForEnum<c10>()); }
        double e11() const { return 1.0; }
        double e12() const { return getFactorWhen(OverloadTypeForEnum<c12>()); }
        double e13() const { return 0.0; }
        
        double e20() const { return getFactorWhen(OverloadTypeForEnum<c20>()); }
        double e21() const { return getFactorWhen(OverloadTypeForEnum<c21>()); }
        double e22() const { return 1.0; }
        double e23() const { return 0.0; }
            
        double e30() const { return 0.0; }
        double e31() const { return 0.0; }
        double e32() const { return 0.0; }
        double e33() const { return 1.0; }
        
        
        static const Constancy c00 = ConstantOne;
        static const Constancy c01 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 0,1>::c;
        static const Constancy c02 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 0,2>::c;
        static const Constancy c03 = ConstantZero;
        
        static const Constancy c10 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 1,0>::c;
        static const Constancy c11 = ConstantOne;
        static const Constancy c12 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 1,2>::c;
        static const Constancy c13 = ConstantZero;
        
        static const Constancy c20 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 2,0>::c;
        static const Constancy c21 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 2,1>::c;
        static const Constancy c22 = ConstantOne;
        static const Constancy c23 = ConstantZero;
            
        static const Constancy c30 = ConstantZero;
        static const Constancy c31 = ConstantZero;
        static const Constancy c32 = ConstantZero;
        static const Constancy c33 = ConstantOne;        
        
    };
      
template<Axis ShearedAxisT, Axis FixedAxisT>
    struct InverseShearOf : 
        public Base< InverseShearOf<ShearedAxisT, FixedAxisT> >
    {
        InverseShearOf()
        {
            // uninitialized
        }
        
        InverseShearOf(double iFactor)
        : factor(iFactor)
        {
            static_assert(ShearedAxisT != FixedAxisT, "The ShearedAxis != FixedAxis");
        }
        
        double factor;    

        static const InverseProvision inverseProvision = InverseProvided;   
        typedef ShearOf<ShearedAxisT, FixedAxisT> InverseType;
        inline InverseType inverse() const { return InverseType(factor); }
        
    private:
        // Bit of a workaround for C++ not supporting specialized template
        // member functions, turn enum into concrete type and 
        // overload all variations to provide same effect as template
        // specialization
        template<Constancy CT>
        struct OverloadTypeForEnum
        {};
        
        double getFactorWhen(OverloadTypeForEnum<ConstantZero>) const
        {
            return 0.0;
        }

        double getFactorWhen(OverloadTypeForEnum<ConstantOne>) const
        {
            return 1.0;
        }

        double getFactorWhen(OverloadTypeForEnum<NotConstant>) const
        {
            return -factor;
        }
    public:
        
        double e00() const { return 1.0; }    
        double e01() const { return getFactorWhen(OverloadTypeForEnum<c01>()); }    
        double e02() const { return getFactorWhen(OverloadTypeForEnum<c02>()); }    
        double e03() const { return 0.0; }    
        
        double e10() const { return getFactorWhen(OverloadTypeForEnum<c10>()); }
        double e11() const { return 1.0; }
        double e12() const { return getFactorWhen(OverloadTypeForEnum<c12>()); }
        double e13() const { return 0.0; }
        
        double e20() const { return getFactorWhen(OverloadTypeForEnum<c20>()); }
        double e21() const { return getFactorWhen(OverloadTypeForEnum<c21>()); }
        double e22() const { return 1.0; }
        double e23() const { return 0.0; }
            
        double e30() const { return 0.0; }
        double e31() const { return 0.0; }
        double e32() const { return 0.0; }
        double e33() const { return 1.0; }
        
        
        static const Constancy c00 = ConstantOne;
        static const Constancy c01 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 0,1>::c;
        static const Constancy c02 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 0,2>::c;
        static const Constancy c03 = ConstantZero;
        
        static const Constancy c10 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 1,0>::c;
        static const Constancy c11 = ConstantOne;
        static const Constancy c12 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 1,2>::c;
        static const Constancy c13 = ConstantZero;
        
        static const Constancy c20 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 2,0>::c;
        static const Constancy c21 = detail::NotConstantIfSheared<ShearedAxisT, FixedAxisT, 2,1>::c;
        static const Constancy c22 = ConstantOne;
        static const Constancy c23 = ConstantZero;
            
        static const Constancy c30 = ConstantZero;
        static const Constancy c31 = ConstantZero;
        static const Constancy c32 = ConstantZero;
        static const Constancy c33 = ConstantOne;        
        
    };    
    
    
    template<Axis ShearedAxisT, Axis FixedAxisT>
    typename ShearOf<ShearedAxisT, FixedAxisT>::InverseType 
    ShearOf<ShearedAxisT, FixedAxisT>::inverse() const 
    { 
        return InverseType(factor); 
    }
    
    
    typedef ShearOf<AxisX, AxisY> ShearOfXbyY;
    typedef ShearOf<AxisX, AxisZ> ShearOfXbyZ;

    typedef ShearOf<AxisY, AxisX> ShearOfYbyX;
    typedef ShearOf<AxisY, AxisZ> ShearOfYbyZ;

    typedef ShearOf<AxisZ, AxisX> ShearOfZbyX;
    typedef ShearOf<AxisZ, AxisY> ShearOfZbyY;
} // namespace xbb     

#endif // XBB_SHEAR_OF_H
