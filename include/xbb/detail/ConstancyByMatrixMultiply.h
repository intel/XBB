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

#ifndef XBB_DETAIL_CONSTANCY_BY_MATRIX_MULTIPLY_H
#define XBB_DETAIL_CONSTANCY_BY_MATRIX_MULTIPLY_H

#include "ConstancyAccess.h"
#include "ConstancyThroughAddition.h"
#include "ConstancyThroughMultiplication.h"

namespace xbb {
namespace detail {
    
    template<
        Constancy M0LT, Constancy M0RT,
        Constancy M1LT, Constancy M1RT,
        Constancy M2LT, Constancy M2RT,
        Constancy M3LT, Constancy M3RT
    >
    struct ConstancyThrough4MultipliesAnd3Adds
    {
        static const Constancy c = 
        ConstancyThroughAddition
        <
            ConstancyThroughAddition
            <
                ConstancyThroughAddition
                <
                    ConstancyThroughMultiplication<M0LT, M0RT>::c
                    ,
                    ConstancyThroughMultiplication<M1LT, M1RT>::c
                >::c
                ,
                ConstancyThroughMultiplication<M2LT, M2RT>::c
            >::c
            ,
            ConstancyThroughMultiplication<M3LT, M3RT>::c
        >::c;                    
    };

    template<int LeftRowT, int RightColT,
            typename LeftT, typename RightT>
    struct ConstancyByMatrixMultiply
    {         
        static const Constancy c =          
            ConstancyThrough4MultipliesAnd3Adds<
                ConstancyAccess<LeftRowT, 0, LeftT>::c, ConstancyAccess<0, RightColT, RightT>::c,
                ConstancyAccess<LeftRowT, 1, LeftT>::c, ConstancyAccess<1, RightColT, RightT>::c,
                ConstancyAccess<LeftRowT, 2, LeftT>::c, ConstancyAccess<2, RightColT, RightT>::c,
                ConstancyAccess<LeftRowT, 3, LeftT>::c, ConstancyAccess<3, RightColT, RightT>::c
            >::c;    
    };
    
} // namespace detail
} // namespace 

#endif // XBB_DETAIL_CONSTANCY_BY_MATRIX_MULTIPLY_H
