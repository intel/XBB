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

namespace {

    
    ref::Matrix4x4 gS;
    ref::Matrix4x4 gSH;
    ref::Matrix4x4 gRx;
    ref::Matrix4x4 gRy;
    ref::Matrix4x4 gRz;
    ref::Matrix4x4 gT;
    
    ref::Matrix4x4 * __attribute__((noinline)) getS() {
        return &gS;
    }
    ref::Matrix4x4 * __attribute__((noinline)) getSH() {
        return &gSH;
    }
    ref::Matrix4x4 * __attribute__((noinline)) getRx() {
        return &gRx;
    }
    ref::Matrix4x4 * __attribute__((noinline)) getRy() {
        return &gRy;
    }
    ref::Matrix4x4 * __attribute__((noinline)) getRz() {
        return &gRz;
    }
    ref::Matrix4x4 * __attribute__((noinline)) getT() {
        return &gT;
    }

    bool initRefTransforms() {
        
        volatile TestValues tv = TestValues::get();
    
        gS.makeScale(tv.scaleX, tv.scaleY, tv.scaleZ);
        gSH.makeShear3(tv.shearX, tv.shearY, tv.shearZ);
        gRx.makeRotationX(tv.rotX);
        gRy.makeRotationY(tv.rotY);
        gRz.makeRotationZ(tv.rotZ);
        gT.makeTranslation(tv.translateX, tv.translateY, tv.translateZ);
        return true;
    }
            
    static bool initRefTransformVar = initRefTransforms();
    
}

static const char * sPrecomputedSxSHxRxTName = "Precomputed S*SH*R*T";
TEST_CASE(sPrecomputedSxSHxRxTName, "")
{    
    // time composing S*SH*R*T with precomputed S,SH,R,T using reference vs XBB
    volatile TestValues tv = TestValues::get();
    
    const int repeatCount = 10000000;
    
    // Compose a transform using traditional OO approach
    // Precompute the individual components
    // and just time how long it takes to concatenate them
    double refTime = 0.0;
    {
        XBB_INLINE_BLOCK
        {                            
            // Go through pointers so compiler cannot guarantee the
            // values used in each loop are identical and will actually
            // pull values from the pointers and do the math each
            // iteration
            ref::Matrix4x4 *S = getS();
            ref::Matrix4x4 *SH = getSH();
            ref::Matrix4x4 *Rx = getRx();
            ref::Matrix4x4 *Ry = getRy();
            ref::Matrix4x4 *Rz = getRz();
            ref::Matrix4x4 *T = getT();

            ScopedTimer timer(refTime);

            for (int rep=0; rep < repeatCount; ++rep) {

                *gRefFinalTransform = (*S)*(*SH)*(*Rz)*(*Ry)*(*Rx)*(*T);

            }
        }
    }
    
    // Compose a transform using XBB
    double xbbTime = 0.0;
    {
        
        XBB_INLINE_BLOCK
        {                    
            ScopedTimer timer(xbbTime);
            for (int rep=0; rep < repeatCount; ++rep) {
                
                // Note here we are using cached rotation transforms
                // they already have done the cos and sine of the angles
                // but rather than 128 bytes each, they are only 16 bytes
                // small enough to keep around with along side the angles
                xbb::RotationX Rx(tv.rX.cosineOfAngle, tv.rX.sineOfAngle);
                xbb::RotationY Ry(tv.rY.cosineOfAngle, tv.rY.sineOfAngle);
                xbb::RotationZ Rz(tv.rZ.cosineOfAngle, tv.rZ.sineOfAngle);

                // No value in caching the rest because it take no additional
                // space or overhead.  
                // Ok, there is a little overhead in getting the 
                xbb::Scale S(tv.scaleX, tv.scaleY, tv.scaleZ);
                xbb::Shear3 SH(tv.shearX, tv.shearY, tv.shearZ);
                xbb::Translation T(tv.translateX, tv.translateY, tv.translateZ);    

                (S*SH*Rz*Ry*Rx*T).to(*gXbbFinalTransform);

            }
        }
    }
        
    std::cout << sPrecomputedSxSHxRxTName << ":"<< std::endl;
    //std::cout << "Ref Transform " << *gRefFinalTransform << std::endl;
    //std::cout << "xbb Transform " << *gXbbFinalTransform << std::endl;
    TRANSFORMS_ARE_CLOSE(*gXbbFinalTransform, *gRefFinalTransform);
    
    std::cout << "    ref Time " << refTime << std::endl;
    std::cout << "    xbb Time " << xbbTime << std::endl;
    std::cout << "    speedup " << refTime/xbbTime << "x" << std::endl << std::endl;
}


