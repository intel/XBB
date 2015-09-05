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


static const char * sPartialPrecomputedSxSHxRxTName = "Partial Precomputed S*SH*R*T";
TEST_CASE(sPartialPrecomputedSxSHxRxTName, "")
{    
    // time composing S*SH*R*T with precomputed S,SH,R,T using reference vs XBB
    volatile TestValues tv = TestValues::get();
    
    const int repeatCount = 10000000;
    
    ref::Matrix4x4 refFinalTransform;
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

                // Keeping around a ref::Matrix4x4 takes 128 bytes, so caching
                // Rx, Ry, and Rz would take 384 bytes and is most likely memory
                // prohibitive.
                ref::Matrix4x4 Rx;
                Rx.makeRotationX(tv.rotX);

                ref::Matrix4x4 Ry;
                Ry.makeRotationY(tv.rotY);

                ref::Matrix4x4 Rz;
                Rz.makeRotationZ(tv.rotZ);

                ref::Matrix4x4 T;
                T.makeTranslation(tv.translateX, tv.translateY, tv.translateZ);

                refFinalTransform = S*SH*Rz*Ry*Rx*T;
            }
        }
    }
    
    // Compose a transform using XBB
    xbb::Matrix4x3 xbbFinalTransform;
    double xbbTime = 0.0;
    {
        
        // Keeping around a xbb::RotationX takes only 16 bytes, so caching
        // Rx, Ry, and Rz would only take 48 bytes and avoids 6 calls to 
        // sin and cos and if possible caching will be worth the memory vs.
        // performance tradeoff
        REQUIRE(sizeof(xbb::RotationX) == 16);
        REQUIRE(sizeof(xbb::RotationY) == 16);
        REQUIRE(sizeof(xbb::RotationZ) == 16);
        xbb::RotationX Rx(tv.rotX);
        xbb::RotationY Ry(tv.rotY);
        xbb::RotationZ Rz(tv.rotZ);
        
        ScopedTimer timer(xbbTime);
        
        for (int rep=0; rep < repeatCount; ++rep) {
            XBB_INLINE_BLOCK
            {                    
                xbb::Scale S(tv.scaleX, tv.scaleY, tv.scaleZ);
                xbb::Shear3 SH(tv.shearX, tv.shearY, tv.shearZ);
                xbb::Translation T(tv.translateX, tv.translateY, tv.translateZ);    

                (S*SH*Rz*Ry*Rx*T).to(xbbFinalTransform);
            }
        }
    }
        
    
    std::cout << sPartialPrecomputedSxSHxRxTName << ":"<< std::endl;
    //std::cout << "Ref Transform " << refFinalTransform << std::endl;
    //std::cout << "xbb Transform " << xbbFinalTransform << std::endl;
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    
    std::cout << "    ref Time " << refTime << std::endl;
    std::cout << "    xbb Time " << xbbTime << std::endl;
    std::cout << "    speedup " << refTime/xbbTime << "x" << std::endl << std::endl;
}


