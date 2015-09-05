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

#include "TestValues.h"

TestValues TestValues::get()
{
    TestValues tv;
    
    
    tv.scaleX = 2.0;
    tv.scaleY = 3.0;
    tv.scaleZ = 4.0;
    tv.shearX = 0.1;
    tv.shearY = 0.2;
    tv.shearZ = 0.3;
    tv.translateX = 100;
    tv.translateY = 200;
    tv.translateZ = 300;
    tv.rotX = 1.39; 
    tv.rotY = 2.45; 
    tv.rotZ = 3.0;
    tv.rX.set(tv.rotX);
    tv.rY.set(tv.rotY);
    tv.rZ.set(tv.rotZ);

    tv.parentScaleX = 10;
    tv.parentScaleY = 20;
    tv.parentScaleZ = 30;
    tv.parentShearX = 0.4;
    tv.parentShearY = 0.5;
    tv.parentShearZ = 0.6;    

    // Setup the parent matrix to be the inverse of a local matrix built
    // from the other tv values
    ref::Matrix4x4 S;
    S.makeScale(-tv.scaleX, -tv.scaleY, -tv.scaleZ);

    ref::Matrix4x4 SH;
    SH.makeShear3(tv.shearX, tv.shearY, tv.shearZ);

    ref::Matrix4x4 Rx;
    Rx.makeRotationX(-tv.rotX);

    ref::Matrix4x4 Ry;
    Ry.makeRotationY(-tv.rotY);

    ref::Matrix4x4 Rz;
    Rz.makeRotationZ(-tv.rotZ);

    ref::Matrix4x4 T;
    T.makeTranslation(-tv.translateX, -tv.translateY, -tv.translateZ);

    tv.parentWorld = S*SH.inverse()*Rz*Ry*Rx*T;    
    
    return tv;
}

