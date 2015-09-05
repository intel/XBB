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


using namespace xbb;


TEST_CASE("TypeChecking", "")
{    
    // exercise helper methods for comparing types, useful for templates to use 
    // conditionals known at compile time vs template specialization
    
    xbb::Translation T;    
    REQUIRE(T.isIdentity() == false) ;
    REQUIRE(T.is<xbb::Identity>() == false) ;
    REQUIRE(T.is<xbb::Translation>() == true);
    REQUIRE(T.is<xbb::Scale>() == false);
    REQUIRE(T.is<xbb::Shear3>() == false);
    REQUIRE(T.is<xbb::RotationX>() == false);
    REQUIRE(T.is<xbb::RotationY>() == false);
    REQUIRE(T.is<xbb::RotationZ>() == false);
    REQUIRE(T.is<xbb::Matrix3x3>() == false);
    REQUIRE(T.is<xbb::Matrix4x3>() == false);
    
    
    xbb::Identity I;
    REQUIRE(I.isIdentity() == true) ;
    REQUIRE(I.is<xbb::Identity>() == true) ;
    REQUIRE(I.is<xbb::Translation>() == false);
    REQUIRE(I.is<xbb::Scale>() == false);
    REQUIRE(I.is<xbb::Shear3>() == false);
    REQUIRE(I.is<xbb::RotationX>() == false);
    REQUIRE(I.is<xbb::RotationY>() == false);
    REQUIRE(I.is<xbb::RotationZ>() == false);
    REQUIRE(I.is<xbb::Matrix3x3>() == false);
    REQUIRE(I.is<xbb::Matrix4x3>() == false);

    xbb::Scale S;
    REQUIRE(S.isIdentity() == false) ;
    REQUIRE(S.is<xbb::Identity>() == false) ;
    REQUIRE(S.is<xbb::Translation>() == false);
    REQUIRE(S.is<xbb::Scale>() == true);
    REQUIRE(S.is<xbb::Shear3>() == false);
    REQUIRE(S.is<xbb::RotationX>() == false);
    REQUIRE(S.is<xbb::RotationY>() == false);
    REQUIRE(S.is<xbb::RotationZ>() == false);
    REQUIRE(S.is<xbb::Matrix3x3>() == false);
    REQUIRE(S.is<xbb::Matrix4x3>() == false);
    
    xbb::Shear3 SH;
    REQUIRE(SH.isIdentity() == false) ;
    REQUIRE(SH.is<xbb::Identity>() == false) ;
    REQUIRE(SH.is<xbb::Translation>() == false);
    REQUIRE(SH.is<xbb::Scale>() == false);
    REQUIRE(SH.is<xbb::Shear3>() == true);
    REQUIRE(SH.is<xbb::RotationX>() == false);
    REQUIRE(SH.is<xbb::RotationY>() == false);
    REQUIRE(SH.is<xbb::RotationZ>() == false);
    REQUIRE(SH.is<xbb::Matrix3x3>() == false);
    REQUIRE(SH.is<xbb::Matrix4x3>() == false);
    
    xbb::RotationX Rx;
    REQUIRE(Rx.isIdentity() == false) ;
    REQUIRE(Rx.is<xbb::Identity>() == false) ;
    REQUIRE(Rx.is<xbb::Translation>() == false);
    REQUIRE(Rx.is<xbb::Scale>() == false);
    REQUIRE(Rx.is<xbb::Shear3>() == false);
    REQUIRE(Rx.is<xbb::RotationX>() == true);
    REQUIRE(Rx.is<xbb::RotationY>() == false);
    REQUIRE(Rx.is<xbb::RotationZ>() == false);
    REQUIRE(Rx.is<xbb::Matrix3x3>() == false);
    REQUIRE(Rx.is<xbb::Matrix4x3>() == false);
    
    xbb::RotationY Ry;
    REQUIRE(Ry.isIdentity() == false) ;
    REQUIRE(Ry.is<xbb::Identity>() == false) ;
    REQUIRE(Ry.is<xbb::Translation>() == false);
    REQUIRE(Ry.is<xbb::Scale>() == false);
    REQUIRE(Ry.is<xbb::Shear3>() == false);
    REQUIRE(Ry.is<xbb::RotationX>() == false);
    REQUIRE(Ry.is<xbb::RotationY>() == true);
    REQUIRE(Ry.is<xbb::RotationZ>() == false);
    REQUIRE(Ry.is<xbb::Matrix3x3>() == false);
    REQUIRE(Ry.is<xbb::Matrix4x3>() == false);
    
    xbb::RotationZ Rz;
    REQUIRE(Rz.isIdentity() == false) ;
    REQUIRE(Rz.is<xbb::Identity>() == false) ;
    REQUIRE(Rz.is<xbb::Translation>() == false);
    REQUIRE(Rz.is<xbb::Scale>() == false);
    REQUIRE(Rz.is<xbb::Shear3>() == false);
    REQUIRE(Rz.is<xbb::RotationX>() == false);
    REQUIRE(Rz.is<xbb::RotationY>() == false);
    REQUIRE(Rz.is<xbb::RotationZ>() == true);
    REQUIRE(Rz.is<xbb::Matrix3x3>() == false);
    REQUIRE(Rz.is<xbb::Matrix4x3>() == false);
    
    xbb::Matrix3x3 mat3;
    REQUIRE(mat3.isIdentity() == false) ;
    REQUIRE(mat3.is<xbb::Identity>() == false) ;
    REQUIRE(mat3.is<xbb::Translation>() == false);
    REQUIRE(mat3.is<xbb::Scale>() == false);
    REQUIRE(mat3.is<xbb::Shear3>() == false);
    REQUIRE(mat3.is<xbb::RotationX>() == false);
    REQUIRE(mat3.is<xbb::RotationY>() == false);
    REQUIRE(mat3.is<xbb::RotationZ>() == false);
    REQUIRE(mat3.is<xbb::Matrix3x3>() == true);
    REQUIRE(mat3.is<xbb::Matrix4x3>() == false);
    
    xbb::Matrix4x3 mat4;
    REQUIRE(mat4.isIdentity() == false) ;
    REQUIRE(mat4.is<xbb::Identity>() == false) ;
    REQUIRE(mat4.is<xbb::Translation>() == false);
    REQUIRE(mat4.is<xbb::Scale>() == false);
    REQUIRE(mat4.is<xbb::Shear3>() == false);
    REQUIRE(mat4.is<xbb::RotationX>() == false);
    REQUIRE(mat4.is<xbb::RotationY>() == false);
    REQUIRE(mat4.is<xbb::RotationZ>() == false);
    REQUIRE(mat4.is<xbb::Matrix3x3>() == false);
    REQUIRE(mat4.is<xbb::Matrix4x3>() == true);
}




