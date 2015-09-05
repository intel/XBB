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

#ifndef XBB_DETAIL_ELEMENT_PRODUCT_H
#define XBB_DETAIL_ELEMENT_PRODUCT_H

#include "../Constancy.h"


namespace xbb {    
namespace detail {    

// To hold the result of an ElementMultiplier,
// the ElementProduct has to model constant and nonconstant results
// and support adding other ElementProducts to produce another ElementProduct
template<Constancy cT>
struct ElementProduct
{    
};

template<>
struct ElementProduct<NotConstant>
{    
    ElementProduct() {}
    ElementProduct(double iValue)
    : mValue(iValue) 
    {}
    
    const ElementProduct<NotConstant> & add(const ElementProduct<ConstantZero> &) const
    {
        return *this;
    }
    ElementProduct<NotConstant> add(const ElementProduct<ConstantOne> &) const 
    {
        return ElementProduct<NotConstant>(mValue + 1.0);
    }
    ElementProduct<NotConstant> add(const ElementProduct<NotConstant> & iOther) const
    {
        return ElementProduct<NotConstant>(mValue + iOther.mValue);
    }
    
    double mValue;
    
    double value() const { return mValue; }
};

template<>
struct ElementProduct<ConstantZero>
{    
    template<Constancy OtherCT>
    const ElementProduct<OtherCT> & add(const ElementProduct<OtherCT> & iOther) const 
    {
        return iOther;
    }
    double value() const { return 0.0; }    
};

template<>
struct ElementProduct<ConstantOne>
{    
    const ElementProduct<ConstantOne> & add(const ElementProduct<ConstantZero> &) const 
    {
        return *this;
    }
    ElementProduct<NotConstant> add(const ElementProduct<ConstantOne> &) const 
    {
        return ElementProduct<NotConstant>(2.0);
    }
    ElementProduct<NotConstant> add(const ElementProduct<NotConstant> &iOther) const 
    {
        return ElementProduct<NotConstant>(iOther.mValue + 1.0);
    }
    
    double value() const { return 1.0; }
    
};



} // namespace detail
} // namespace xbb


#endif // XBB_DETAIL_ELEMENT_PRODUCT_H
