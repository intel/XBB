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

#ifndef TEST_VALUES_H
#define TEST_VALUES_H

#include <xbb/Transforms.h>
#include "ref/Matrix4x4.h"

// To avoid optimizations where the compiler clones the function and uses
// compile time know values that we put in the unit test, we will use
// test values that are populated in a different compilation unit.
// In a production program one wouldn't care, but usually in production the
// values are not known at compile time and we don't want an unfair advantage
struct TestValues
{
    static TestValues get();

    
    double scaleX, scaleY, scaleZ;    
    double shearX, shearY, shearZ;    
    double translateX, translateY, translateZ;
    double rotX, rotY, rotZ;
    xbb::RotationX rX;
    xbb::RotationY rY;
    xbb::RotationZ rZ;
    
    double parentScaleX, parentScaleY, parentScaleZ;    
    double parentShearX, parentShearY, parentShearZ;    
    
    ref::Matrix4x4 parentWorld;
};

#endif // TEST_VALUES_H

