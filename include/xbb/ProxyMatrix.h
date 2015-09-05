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

#ifndef XBB_PROXY_MATRIX_H
#define XBB_PROXY_MATRIX_H

#include "Base.h"
#include "MatrixValuesFrom.h"

namespace xbb {

template<
    Constancy c00T, Constancy c01T, Constancy c02T, Constancy c03T,
    Constancy c10T, Constancy c11T, Constancy c12T, Constancy c13T,
    Constancy c20T, Constancy c21T, Constancy c22T, Constancy c23T,
    Constancy c30T, Constancy c31T, Constancy c32T, Constancy c33T,
    typename UserTypeT
>        
struct ProxyMatrix: 
    public Base<ProxyMatrix<
        c00T, c01T, c02T, c03T,
        c10T, c11T, c12T, c13T,
        c20T, c21T, c22T, c23T,
        c30T, c31T, c32T, c33T, 
        UserTypeT> 
    >
{
    ProxyMatrix(const UserTypeT &iTransform) 
    : mTransform(iTransform)
    { 
    }

    const UserTypeT & mTransform;
    
    static const InverseProvision inverseProvision = InverseDeprived;        
    
    double e00() const { return MatrixValuesFrom<UserTypeT>::e00(mTransform); }
    double e01() const { return MatrixValuesFrom<UserTypeT>::e01(mTransform); }
    double e02() const { return MatrixValuesFrom<UserTypeT>::e02(mTransform); }
    double e03() const { return MatrixValuesFrom<UserTypeT>::e03(mTransform); }

    double e10() const { return MatrixValuesFrom<UserTypeT>::e10(mTransform); }
    double e11() const { return MatrixValuesFrom<UserTypeT>::e11(mTransform); }
    double e12() const { return MatrixValuesFrom<UserTypeT>::e12(mTransform); }
    double e13() const { return MatrixValuesFrom<UserTypeT>::e13(mTransform); }

    double e20() const { return MatrixValuesFrom<UserTypeT>::e20(mTransform); }
    double e21() const { return MatrixValuesFrom<UserTypeT>::e21(mTransform); }
    double e22() const { return MatrixValuesFrom<UserTypeT>::e22(mTransform); }
    double e23() const { return MatrixValuesFrom<UserTypeT>::e23(mTransform); }

    double e30() const { return MatrixValuesFrom<UserTypeT>::e30(mTransform); }
    double e31() const { return MatrixValuesFrom<UserTypeT>::e31(mTransform); }
    double e32() const { return MatrixValuesFrom<UserTypeT>::e32(mTransform); }
    double e33() const { return MatrixValuesFrom<UserTypeT>::e33(mTransform); }

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
};

template<typename UserTypeT>        
struct ProxyMatrix4x4 : 
    public ProxyMatrix< 
        NotConstant, NotConstant, NotConstant, NotConstant,
        NotConstant, NotConstant, NotConstant, NotConstant,
        NotConstant, NotConstant, NotConstant, NotConstant,
        NotConstant, NotConstant, NotConstant, NotConstant,
        UserTypeT>
{
    ProxyMatrix4x4(const UserTypeT &iTransform)
    :ProxyMatrix<
        NotConstant, NotConstant, NotConstant, NotConstant,
        NotConstant, NotConstant, NotConstant, NotConstant,
        NotConstant, NotConstant, NotConstant, NotConstant,
        NotConstant, NotConstant, NotConstant, NotConstant,
        UserTypeT>(iTransform)
    {}    
};

template<typename UserTypeT>        
struct ProxyMatrix4x3 : 
    public ProxyMatrix< 
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantOne,
        UserTypeT>
{
    typedef ProxyMatrix<
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantOne,
        UserTypeT> Base;
    
    ProxyMatrix4x3(const UserTypeT &iTransform)
    : Base(iTransform)
    {}    
};

template<typename UserTypeT>        
struct ProxyMatrix3x3 : 
    public ProxyMatrix< 
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        ConstantZero, ConstantZero, ConstantZero, ConstantOne,
        UserTypeT>
{
    typedef ProxyMatrix<
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        NotConstant, NotConstant, NotConstant, ConstantZero,
        ConstantZero, ConstantZero, ConstantZero, ConstantOne,
        UserTypeT> Base;
    
    ProxyMatrix3x3(const UserTypeT &iTransform)
    : Base(iTransform)
    {}    
};


// Enable ProxyMatrix to be used with a ProxyMatrix
// common use case is to mask out/off components
template<
    Constancy c00T, Constancy c01T, Constancy c02T, Constancy c03T,
    Constancy c10T, Constancy c11T, Constancy c12T, Constancy c13T,
    Constancy c20T, Constancy c21T, Constancy c22T, Constancy c23T,
    Constancy c30T, Constancy c31T, Constancy c32T, Constancy c33T,
    typename UserTypeT
>        
struct MatrixValuesFrom<
    ProxyMatrix<
        c00T, c01T, c02T, c03T,
        c10T, c11T, c12T, c13T,
        c20T, c21T, c22T, c23T,
        c30T, c31T, c32T, c33T,
        UserTypeT
    >
>
{        
    typedef ProxyMatrix<
        c00T, c01T, c02T, c03T,
        c10T, c11T, c12T, c13T,
        c20T, c21T, c22T, c23T,
        c30T, c31T, c32T, c33T,
        UserTypeT> ProxyType;
    
    static double e00(const ProxyType & iFrom)
    {
        return iFrom.e00();
    }
    static double e01(const ProxyType & iFrom)
    {
        return iFrom.e01();
    }
    static double e02(const ProxyType & iFrom)
    {
        return iFrom.e02();
    }

    static double e03(const ProxyType & iFrom)
    {
        return iFrom.e03();
    }

    static double e10(const ProxyType & iFrom)
    {
        return iFrom.e10();
    }
    static double e11(const ProxyType & iFrom)
    {
        return iFrom.e11();
    }
    static double e12(const ProxyType & iFrom)
    {
        return iFrom.e12();
    }

    static double e13(const ProxyType & iFrom)
    {
        return iFrom.e13();
    }

    static double e20(const ProxyType & iFrom)
    {
        return iFrom.e20();
    }
    static double e21(const ProxyType & iFrom)
    {
        return iFrom.e21();
    }
    static double e22(const ProxyType & iFrom)
    {
        return iFrom.e22();
    }

    static double e23(const ProxyType & iFrom)
    {
        return iFrom.e23();
    }

    static double e30(const ProxyType & iFrom)
    {
        return iFrom.e30();
    }
    static double e31(const ProxyType & iFrom)
    {
        return iFrom.e31();
    }
    static double e32(const ProxyType & iFrom)
    {
        return iFrom.e32();
    }        
    static double e33(const ProxyType & iFrom)
    {
        return iFrom.e33();
    }        
};        

template<typename UserTypeT>        
struct MatrixValuesFrom<
    ProxyMatrix4x3<UserTypeT>
> : public MatrixValuesFrom<typename ProxyMatrix4x3<UserTypeT>::Base>
{          
};

template<typename UserTypeT>        
struct MatrixValuesFrom<
    ProxyMatrix3x3<UserTypeT>
> : public MatrixValuesFrom<typename ProxyMatrix3x3<UserTypeT>::Base>
{          
};

} // namespace xbb


#endif // XBB_PROXY_MATRIX_H
