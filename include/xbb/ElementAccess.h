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

#ifndef XBB_ELEMENT_ACCESS_H
#define XBB_ELEMENT_ACCESS_H

namespace xbb {
    

    template<int RowT, int ColT>
    struct ElementAccess    
    {
        template<typename T>
        static double e(const T &iTransform);
    };
    
    template<>
    struct ElementAccess<0,0>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e00(); }
    };
    
    template<>
    struct ElementAccess<0,1>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e01(); }
    };
    
    template<>
    struct ElementAccess<0,2>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e02(); }
    };
    
    template<>
    struct ElementAccess<0,3>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e03(); }
    };
    
    template<>
    struct ElementAccess<1,0>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e10(); }
    };
    
    template<>
    struct ElementAccess<1,1>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e11(); }
    };
    
    template<>
    struct ElementAccess<1,2>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e12(); }
    };
    
    template<>
    struct ElementAccess<1,3>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e13(); }
    };
        
    
    
    template<>
    struct ElementAccess<2,0>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e20(); }
    };
    
    template<>
    struct ElementAccess<2,1>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e21(); }
    };
    
    template<>
    struct ElementAccess<2,2>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e22(); }
    };
    
    template<>
    struct ElementAccess<2,3>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e23(); }
    };
      
    
    template<>
    struct ElementAccess<3,0>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e30(); }
    };
    
    template<>
    struct ElementAccess<3,1>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e31(); }
    };
    
    template<>
    struct ElementAccess<3,2>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e32(); }
    };
    
    template<>
    struct ElementAccess<3,3>    
    {
        template<typename T>
        static double e(const T &iTransform) { return iTransform.e33(); }
    };

    
    
    
} // namespace xbb     

#endif // XBB_ELEMENT_ACCESS_H
