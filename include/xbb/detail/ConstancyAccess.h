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

#ifndef XBB_DETAIL_CONSTANCY_ACCESS_H
#define XBB_DETAIL_CONSTANCY_ACCESS_H

namespace xbb {
namespace detail {
    
    // Use template specialization to access the correct static constancy enum
    // of a Transform
    template<int RowT, int ColT, typename T>
    struct ConstancyAccess    
    {
        //static const Constancy c;
    };
    
    template<typename T>
    struct ConstancyAccess<0, 0, T>
    {
        static const Constancy c = T::c00;
    };    
    template<typename T>
    struct ConstancyAccess<0, 1, T>
    {
        static const Constancy c = T::c01;
    };
    template<typename T>
    struct ConstancyAccess<0, 2, T>
    {
        static const Constancy c = T::c02;
    };
    
    template<typename T>
    struct ConstancyAccess<0, 3, T>
    {
        static const Constancy c = T::c03;
    };
    
    
    template<typename T>
    struct ConstancyAccess<1, 0, T>
    {
        static const Constancy c = T::c10;
    };    
    template<typename T>
    struct ConstancyAccess<1, 1, T>
    {
        static const Constancy c = T::c11;
    };
    template<typename T>
    struct ConstancyAccess<1, 2, T>
    {
        static const Constancy c = T::c12;
    };
    
    template<typename T>
    struct ConstancyAccess<1, 3, T>
    {
        static const Constancy c = T::c13;
    };
    
    template<typename T>
    struct ConstancyAccess<2, 0, T>
    {
        static const Constancy c = T::c20;
    };    
    template<typename T>
    struct ConstancyAccess<2, 1, T>
    {
        static const Constancy c = T::c21;
    };
    template<typename T>
    struct ConstancyAccess<2, 2, T>
    {
        static const Constancy c = T::c22;
    };
    
    template<typename T>
    struct ConstancyAccess<2, 3, T>
    {
        static const Constancy c = T::c23;
    };
    
    template<typename T>
    struct ConstancyAccess<3, 0, T>
    {
        static const Constancy c = T::c30;
    };    
    template<typename T>
    struct ConstancyAccess<3, 1, T>
    {
        static const Constancy c = T::c31;
    };
    template<typename T>
    struct ConstancyAccess<3, 2, T>
    {
        static const Constancy c = T::c32;
    };
    
    template<typename T>
    struct ConstancyAccess<3, 3, T>
    {
        static const Constancy c = T::c33;
    };
    
} // namespace detail
} // namespace 

#endif // XBB_DETAIL_CONSTANCY_ACCESS_H
