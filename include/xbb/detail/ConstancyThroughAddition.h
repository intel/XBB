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

#ifndef XBB_DETAIL_CONSTANCY_THROUGH_ADDITION_H
#define XBB_DETAIL_CONSTANCY_THROUGH_ADDITION_H

namespace xbb {
namespace detail {
    
    // Use template specialization to specify the constancy when two
    // values are added together
    template<Constancy LeftT, Constancy RightT>
    struct ConstancyThroughAddition
    {};

    template<>
    struct ConstancyThroughAddition<ConstantZero, ConstantZero>
    { static const Constancy c = ConstantZero; };
    
    template<>
    struct ConstancyThroughAddition<ConstantZero, ConstantOne>
    { static const Constancy c = ConstantOne; };
    
    template<>
    struct ConstancyThroughAddition<ConstantZero, NotConstant>
    { static const Constancy c = NotConstant; };

    
    template<>
    struct ConstancyThroughAddition<ConstantOne, ConstantZero>
    { static const Constancy c = ConstantOne; };
    
    template<>
    struct ConstancyThroughAddition<ConstantOne, ConstantOne>
    { static const Constancy c = NotConstant; };
    
    template<>
    struct ConstancyThroughAddition<ConstantOne, NotConstant>
    { static const Constancy c = NotConstant; };
    
    template<>
    struct ConstancyThroughAddition<NotConstant, ConstantZero>
    { static const Constancy c = NotConstant; };
    
    template<>
    struct ConstancyThroughAddition<NotConstant, ConstantOne>
    { static const Constancy c = NotConstant; };
    
    template<>
    struct ConstancyThroughAddition<NotConstant, NotConstant>
    { static const Constancy c = NotConstant; };    
    
} // namespace detail
} // namespace 

#endif // XBB_DETAIL_CONSTANCY_THROUGH_ADDITION_H
