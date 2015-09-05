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

#ifndef ADAPT_REF_TO_XBB_H
#define ADAPT_REF_TO_XBB_H

#include "ref/Matrix4x4.h"
#include "ref/Vec3.h"
#include <xbb/MatrixValuesFrom.h>
#include <xbb/Scale.h>
#include <xbb/Shear3.h>
#include <xbb/Translation.h>

// You can adapt existing math libraries to interact with xbb transforms
// Just specialize the From and To templates for the user's type
namespace xbb {

    template <>
    struct MatrixValuesFrom<ref::Matrix4x4>
    {        
        static double e00(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e00();
        }
        static double e01(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e01();
        }
        static double e02(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e02();
        }

        static double e03(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e03();
        }

        static double e10(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e10();
        }
        static double e11(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e11();
        }
        static double e12(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e12();
        }

        static double e13(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e13();
        }

        static double e20(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e20();
        }
        static double e21(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e21();
        }
        static double e22(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e22();
        }
        
        static double e23(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e23();
        }
        
        static double e30(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e30();
        }
        static double e31(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e31();
        }
        static double e32(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e32();
        }        
        static double e33(const ref::Matrix4x4 & iFrom)
        {
            return iFrom.e33();
        }        
    };        
    
    template <>
    struct MatrixValuesTo<ref::Matrix4x4>
    {        
        static void e00(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[0][0] = iValue;
        }
        static void e01(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[0][1] = iValue;
        }
        static void e02(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[0][2] = iValue;
        }

        static void e03(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[0][3] = iValue;
        }

        static void e10(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[1][0] = iValue;
        }
        static void e11(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[1][1] = iValue;
        }
        static void e12(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[1][2] = iValue;
        }

        static void e13(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[1][3] = iValue;
        }

        static void e20(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[2][0]= iValue;
        }
        static void e21(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[2][1] = iValue;
        }
        static void e22(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[2][2] = iValue;
        }
        
        static void e23(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[2][3] = iValue;
        }
        
        static void e30(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[3][0] = iValue;
        }
        static void e31(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[3][1] = iValue;
        }
        static void e32(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[3][2] = iValue;
        }        
        static void e33(ref::Matrix4x4 & iTo, double iValue)
        {
            iTo.m[3][3] = iValue;
        }
    };
    
    template <>
    struct ScaleValuesFrom<ref::Vec3>
    {        
        static double x(const ref::Vec3 & iFrom)
        {
            return iFrom.m[0];
        }
        static double y(const ref::Vec3 & iFrom)
        {
            return iFrom.m[1];
        }
        static double z(const ref::Vec3 & iFrom)
        {
            return iFrom.m[2];
        }        
    };
    
    
   template <>
   struct Shear3ValuesFrom<ref::Vec3>
    {        
        static double x(const ref::Vec3 & iFrom)
        {
            return iFrom.m[0];
        }
        static double y(const ref::Vec3 & iFrom)
        {
            return iFrom.m[1];
        }
        static double z(const ref::Vec3 & iFrom)
        {
            return iFrom.m[2];
        }        
    };    
    
    template <>
    struct TranslateValuesFrom<ref::Vec3>
    {        
        static double x(const ref::Vec3 & iFrom)
        {
            return iFrom.m[0];
        }
        static double y(const ref::Vec3 & iFrom)
        {
            return iFrom.m[1];
        }
        static double z(const ref::Vec3 & iFrom)
        {
            return iFrom.m[2];
        }        
    };
    
} // namespace xbb
    
#endif // ADAPT_REF_TO_XBB_H
