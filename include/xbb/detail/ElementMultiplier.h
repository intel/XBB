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

#ifndef XBB_DETAIL_ELEMENT_MULTIPLIER_H
#define XBB_DETAIL_ELEMENT_MULTIPLIER_H

#include "../Constancy.h"
#include "ElementProduct.h"


namespace xbb {
namespace detail {    


// Access left and right elements and multply them together into ElementProduct
// However the elements themselves may be constants or non constant
// So provide specializations to handle all combinations and produce a correctly
// typed ElementProduct that is constant or not constant as needed
template<Constancy LCT, Constancy RCT>
struct ElementMultiplier
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<NotConstant> mul(const LeftT & iLeft, const RightT &iRight)
    {
       ElementProduct<NotConstant> p;
       p.mValue = iLeft.template e<LeftRowT, CommonT>()*iRight.template  e<CommonT, RightColT>();
       return p;
    }
};

template<>
struct ElementMultiplier<ConstantZero, ConstantZero>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<ConstantZero> mul(const LeftT &, const RightT &)
    {
       return ElementProduct<ConstantZero>();
    }
};

template<>
struct ElementMultiplier<ConstantZero, ConstantOne>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<ConstantZero> mul(const LeftT &, const RightT &)
    {
       return ElementProduct<ConstantZero>();
    }
};

template<>
struct ElementMultiplier<ConstantZero, NotConstant>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<ConstantZero> mul(const LeftT &, const RightT &)
    {
       return ElementProduct<ConstantZero>();
    }
};

template<>
struct ElementMultiplier<ConstantOne, ConstantZero>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<ConstantZero> mul(const LeftT &, const RightT &)
    {
       return ElementProduct<ConstantZero>();
    }
};

template<>
struct ElementMultiplier<ConstantOne, ConstantOne>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<ConstantOne> mul(const LeftT &, const RightT &)
    {
       return ElementProduct<ConstantOne>();
    }
};

template<>
struct ElementMultiplier<ConstantOne, NotConstant>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<NotConstant> mul(const LeftT &, const RightT &iRight)
    {
       ElementProduct<NotConstant> p;
       p.mValue = iRight.template  e<CommonT, RightColT>();
       return p;
    }
};

template<>
struct ElementMultiplier<NotConstant, ConstantZero>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<ConstantZero> mul(const LeftT &, const RightT &)
    {
       return ElementProduct<ConstantZero>();
    }
};

template<>
struct ElementMultiplier<NotConstant, ConstantOne>
{
    template<int LeftRowT, int CommonT, int RightColT, typename LeftT, typename RightT>
    static ElementProduct<NotConstant> mul(const LeftT &iLeft, const RightT &)
    {
       ElementProduct<NotConstant> p;
       p.mValue = iLeft.template e<LeftRowT, CommonT>();
       return p;
    }
};

} // namespace detail
} // namespace xbb


#endif // XBB_DETAIL_ELEMENT_MULTIPLIER_H
