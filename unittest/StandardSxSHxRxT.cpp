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

#include <stdio.h>
#include <iostream>

#include <CATCH/catch.hpp>

#include <xbb/Transforms.h>
#include "ref/Matrix4x4.h"
#include "ScopedTimer.h"
#include "TestValues.h"
#include "TransformsAreClose.h"


using namespace xbb;


static const char * sStandardSxSHxRxTBestCaseName = "Standard S*SH*R*T (best case)";
TEST_CASE(sStandardSxSHxRxTBestCaseName, "")
{
    // time composing S*SH*R*T with reference vs XBB
    volatile TestValues tv = TestValues::get();

    const int repeatCount = 10000000;
    
    // Compose a transform using traditional OO approach
    double refTime = 0.0;
    {
        ScopedTimer timer(refTime);
        for (int rep=0; rep < repeatCount; ++rep) {
            XBB_INLINE_BLOCK
            {                    
                ref::Matrix4x4 S;
                S.makeScale(tv.scaleX, tv.scaleY, tv.scaleZ);

                ref::Matrix4x4 SH;
                SH.makeShear3(tv.shearX, tv.shearY, tv.shearZ);

                ref::Matrix4x4 Rx;
                Rx.makeRotationX(tv.rotX);

                ref::Matrix4x4 Ry;
                Ry.makeRotationY(tv.rotY);

                ref::Matrix4x4 Rz;
                Rz.makeRotationZ(tv.rotZ);

                ref::Matrix4x4 T;
                T.makeTranslation(tv.translateX, tv.translateY, tv.translateZ);

                // NOTE: if fully inlined, a compiler could do a pretty decent job
                // taking advantage of compile time constants from the "make???" routines.
                // Allowing the results to be on par with the XBB version.
                *gRefFinalTransform = S*SH*Rz*Ry*Rx*T;
            }
        }
    }
    
    // Compose a transform using XBB
    double xbbTime = 0.0;
    {
        ScopedTimer timer(xbbTime);
        for (int rep=0; rep < repeatCount; ++rep) {

            XBB_INLINE_BLOCK
            {                    
                xbb::Scale S(tv.scaleX, tv.scaleY, tv.scaleZ);
                xbb::Shear3 SH(tv.shearX, tv.shearY, tv.shearZ);
                xbb::RotationX Rx(tv.rotX);
                xbb::RotationY Ry(tv.rotY);
                xbb::RotationZ Rz(tv.rotZ);
                xbb::Translation T(tv.translateX, tv.translateY, tv.translateZ);    

                (S*SH*Rz*Ry*Rx*T).to(*gXbbFinalTransform);
            }
        }
    }
        
    
    std::cout << sStandardSxSHxRxTBestCaseName << ":"<< std::endl;
    //std::cout << "Ref Transform " << *gRefFinalTransform << std::endl;
    //std::cout << "xbb Transform " << *gXbbFinalTransform << std::endl;
    TRANSFORMS_ARE_CLOSE(*gXbbFinalTransform, *gRefFinalTransform);
    
    std::cout << "    ref Time " << refTime << std::endl;
    std::cout << "    xbb Time " << xbbTime << std::endl;
    std::cout << "    speedup " << refTime/xbbTime << "x" << std::endl << std::endl;
}


namespace {

__attribute__((noinline)) void multiplySxSHxRzxRyxRxxT(
    ref::Matrix4x4 & result, 
    const ref::Matrix4x4 & S, 
    const ref::Matrix4x4 & SH, 
    const ref::Matrix4x4 & Rz, 
    const ref::Matrix4x4 & Ry, 
    const ref::Matrix4x4 & Rx, 
    const ref::Matrix4x4 & T);

__attribute__((noinline)) void multiplySxSHxRzxRyxRxxT(
    xbb::Matrix4x3 & result,
    const xbb::Scale & S,
    const xbb::Shear3 & SH,
    const xbb::RotationZ & Rz,
    const xbb::RotationY & Ry,
    const xbb::RotationX & Rx,
    const xbb::Translation & T);

void multiplySxSHxRzxRyxRxxT(
    ref::Matrix4x4 & result, 
    const ref::Matrix4x4 & S, 
    const ref::Matrix4x4 & SH, 
    const ref::Matrix4x4 & Rz, 
    const ref::Matrix4x4 & Ry, 
    const ref::Matrix4x4 & Rx, 
    const ref::Matrix4x4 & T)
{
    result = S*SH*Rz*Ry*Rx*T;
}
    

void multiplySxSHxRzxRyxRxxT(
    xbb::Matrix4x3 & result,
    const xbb::Scale & S,
    const xbb::Shear3 & SH,
    const xbb::RotationZ & Rz,
    const xbb::RotationY & Ry,
    const xbb::RotationX & Rx,
    const xbb::Translation & T)
{
   (S*SH*Rz*Ry*Rx*T).to(result);
}

}


static const char * sStandardSxSHxRxTWorstCaseName = "Standard S*SH*R*T (worst case)";
TEST_CASE(sStandardSxSHxRxTWorstCaseName, "")
{
    // time composing S*SH*R*T with reference vs XBB
    volatile TestValues tv = TestValues::get();

    const int repeatCount = 10000000;
    
    // Compose a transform using traditional OO approach
    double refTime = 0.0;
    {
        ScopedTimer timer(refTime);
        for (int rep=0; rep < repeatCount; ++rep) {
            XBB_INLINE_BLOCK
            {                    
                ref::Matrix4x4 S;
                S.makeScale(tv.scaleX, tv.scaleY, tv.scaleZ);

                ref::Matrix4x4 SH;
                SH.makeShear3(tv.shearX, tv.shearY, tv.shearZ);

                ref::Matrix4x4 Rx;
                Rx.makeRotationX(tv.rotX);

                ref::Matrix4x4 Ry;
                Ry.makeRotationY(tv.rotY);

                ref::Matrix4x4 Rz;
                Rz.makeRotationZ(tv.rotZ);

                ref::Matrix4x4 T;
                T.makeTranslation(tv.translateX, tv.translateY, tv.translateZ);
                
                // NOTE: what we found in practice is 4x4 matrices being passed to functions
                // where the optimizer doesn't know the 0's or 1's.
                // So this represents a worst case scenario.
                multiplySxSHxRzxRyxRxxT(*gRefFinalTransform, S, SH, Rz, Ry, Rx, T);
            }
        }
    }
    
    // Compose a transform using XBB
    double xbbTime = 0.0;
    {
        ScopedTimer timer(xbbTime);
        for (int rep=0; rep < repeatCount; ++rep) {

            XBB_INLINE_BLOCK
            {                    
                xbb::Scale S(tv.scaleX, tv.scaleY, tv.scaleZ);
                xbb::Shear3 SH(tv.shearX, tv.shearY, tv.shearZ);
                xbb::RotationX Rx(tv.rotX);
                xbb::RotationY Ry(tv.rotY);
                xbb::RotationZ Rz(tv.rotZ);
                xbb::Translation T(tv.translateX, tv.translateY, tv.translateZ);    

		        multiplySxSHxRzxRyxRxxT(*gXbbFinalTransform, S, SH, Rz, Ry, Rx, T);
            }
        }
    }
        
    
    std::cout << sStandardSxSHxRxTWorstCaseName << ":"<< std::endl;
    //std::cout << "Ref Transform " << *gRefFinalTransform << std::endl;
    //std::cout << "xbb Transform " << *gXbbFinalTransform << std::endl;
    TRANSFORMS_ARE_CLOSE(*gXbbFinalTransform, *gRefFinalTransform);
    
    std::cout << "    ref Time " << refTime << std::endl;
    std::cout << "    xbb Time " << xbbTime << std::endl;
    std::cout << "    speedup " << refTime/xbbTime << "x" << std::endl << std::endl;
}


