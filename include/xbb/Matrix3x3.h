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

#ifndef XBB_MATRIX_3_X_3_H
#define XBB_MATRIX_3_X_3_H

#include "Base.h"
#include "MatrixValuesFrom.h"


namespace xbb {

struct Matrix3x3 : 
    public Base<Matrix3x3>
{
    Matrix3x3() 
    { 
        // uninitialized 
    }
    Matrix3x3(
        double i00, double i01, double i02,
        double i10, double i11, double i12,
        double i20, double i21, double i22)
    : m00(i00)
    , m01(i01)
    , m02(i02)
    , m10(i10)
    , m11(i11)
    , m12(i12)
    , m20(i20)
    , m21(i21)
    , m22(i22)
    {}

    template<typename UserTypeT>
    Matrix3x3(const UserTypeT &iValue)
    : m00(MatrixValuesFrom<UserTypeT>::e00(iValue))
    , m01(MatrixValuesFrom<UserTypeT>::e01(iValue))
    , m02(MatrixValuesFrom<UserTypeT>::e02(iValue))
    , m10(MatrixValuesFrom<UserTypeT>::e10(iValue))
    , m11(MatrixValuesFrom<UserTypeT>::e11(iValue))
    , m12(MatrixValuesFrom<UserTypeT>::e12(iValue))
    , m20(MatrixValuesFrom<UserTypeT>::e20(iValue))
    , m21(MatrixValuesFrom<UserTypeT>::e21(iValue))
    , m22(MatrixValuesFrom<UserTypeT>::e22(iValue))
    {}
    
    static const InverseProvision inverseProvision = InverseDeprived;
    
    // Column # Row #
    double m00;
    double m01;
    double m02;

    double m10;
    double m11;
    double m12;

    double m20;
    double m21;
    double m22;

    double e00() const { return m00; }    
    double e01() const { return m01; }    
    double e02() const { return m02; }    
    double e03() const { return 0.0; }    

    double e10() const { return m10; }    
    double e11() const { return m11; }    
    double e12() const { return m12; }    
    double e13() const { return 0.0; }    

    double e20() const { return m20; }    
    double e21() const { return m21; }    
    double e22() const { return m22; }    
    double e23() const { return 0.0; }    

    double e30() const { return 0.0; }    
    double e31() const { return 0.0; }    
    double e32() const { return 0.0; }    
    double e33() const { return 1.0; }            

    static const Constancy c00 = NotConstant;
    static const Constancy c01 = NotConstant;
    static const Constancy c02 = NotConstant;
    static const Constancy c03 = ConstantZero;

    static const Constancy c10 = NotConstant;
    static const Constancy c11 = NotConstant;
    static const Constancy c12 = NotConstant;
    static const Constancy c13 = ConstantZero;

    static const Constancy c20 = NotConstant;
    static const Constancy c21 = NotConstant;
    static const Constancy c22 = NotConstant;
    static const Constancy c23 = ConstantZero;

    static const Constancy c30 = ConstantZero;
    static const Constancy c31 = ConstantZero;
    static const Constancy c32 = ConstantZero;
    static const Constancy c33 = ConstantOne;        
    
};

template <>
struct MatrixValuesTo<Matrix3x3>
{        
    static void e00(Matrix3x3 & iTo, double iValue)
    {
        iTo.m00 = iValue;
    }
    static void e01(Matrix3x3 & iTo, double iValue)
    {
        iTo.m01 = iValue;
    }
    static void e02(Matrix3x3 & iTo, double iValue)
    {
        iTo.m02 = iValue;
    }

    static void e03(Matrix3x3 & /*iTo*/, double XBB_DEBUG_ONLY_VAR(iValue))
    {
        XBB_ASSERT(!(iValue > 0.0) && !(iValue < 0.0));
    }

    static void e10(Matrix3x3 & iTo, double iValue)
    {
        iTo.m10 = iValue;
    }
    static void e11(Matrix3x3 & iTo, double iValue)
    {
        iTo.m11 = iValue;
    }
    static void e12(Matrix3x3 & iTo, double iValue)
    {
        iTo.m12 = iValue;
    }

    static void e13(Matrix3x3 & /*iTo*/, double XBB_DEBUG_ONLY_VAR(iValue))
    {
        XBB_ASSERT(!(iValue > 0.0) && !(iValue < 0.0));
    }

    static void e20(Matrix3x3 & iTo, double iValue)
    {
        iTo.m20= iValue;
    }
    static void e21(Matrix3x3 & iTo, double iValue)
    {
        iTo.m21 = iValue;
    }
    static void e22(Matrix3x3 & iTo, double iValue)
    {
        iTo.m22 = iValue;
    }

    static void e23(Matrix3x3 & /*iTo*/, double XBB_DEBUG_ONLY_VAR(iValue))
    {
        XBB_ASSERT(!(iValue > 0.0) && !(iValue < 0.0));
    }

    static void e30(Matrix3x3 & /*iTo*/, double XBB_DEBUG_ONLY_VAR(iValue))
    {
        XBB_ASSERT(!(iValue > 0.0) && !(iValue < 0.0));
    }
    static void e31(Matrix3x3 & /*iTo*/, double XBB_DEBUG_ONLY_VAR(iValue))
    {
        XBB_ASSERT(!(iValue > 0.0) && !(iValue < 0.0));
    }
    static void e32(Matrix3x3 & /*iTo*/, double XBB_DEBUG_ONLY_VAR(iValue))
    {
        XBB_ASSERT(!(iValue > 0.0) && !(iValue < 0.0));
    }        
    static void e33(Matrix3x3 & /*iTo*/, double XBB_DEBUG_ONLY_VAR(iValue))
    {
        XBB_ASSERT(!(iValue > 1.0) && !(iValue < 1.0));
    }        
};            

} // namespace xbb


#endif // XBB_MATRIX_3_X_3_H
