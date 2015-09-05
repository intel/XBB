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
#include "TestValues.h"
#include "TransformsAreClose.h"


using namespace xbb;


static const char * sBasicMatchName = "Basic Transforms Match S, T, R";
TEST_CASE(sBasicMatchName, "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    
    SECTION("SCALE")
    {
        {
            ref::Matrix4x4 S;
            S.makeScale(tv.scaleX, tv.scaleY, tv.scaleZ);
            refFinalTransform = S;
        }
        {
            xbb::Scale S(tv.scaleX, tv.scaleY, tv.scaleZ);
            S.to(xbbFinalTransform);
        }
        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }
    
    SECTION("TRANSLATE")
    {
        {
            ref::Matrix4x4 T;
            T.makeTranslation(tv.translateX, tv.translateY, tv.translateZ);
            refFinalTransform = T;
        }
        {
            xbb::Translation T(tv.translateX, tv.translateY, tv.translateZ);    
            T.to(xbbFinalTransform);
        }
        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }    

    
    SECTION("ROTATE X")
    {
        {
            ref::Matrix4x4 Rx;
            Rx.makeRotationX(tv.rotX);
            refFinalTransform = Rx;
        }
        {
            xbb::RotationX Rx(tv.rotX);
            Rx.to(xbbFinalTransform);
        }
        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }
    
    SECTION("ROTATE Y")
    {
        {
            ref::Matrix4x4 Ry;
            Ry.makeRotationY(tv.rotY);
            refFinalTransform = Ry;
        }
        {
            xbb::RotationY Ry(tv.rotY);
            Ry.to(xbbFinalTransform);
        }
        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }
    
    SECTION("ROTATE Z")
    {
        {
            ref::Matrix4x4 Rz;
            Rz.makeRotationZ(tv.rotZ);
            refFinalTransform = Rz;
        }
        {
            xbb::RotationZ Rz(tv.rotZ);
            Rz.to(xbbFinalTransform);
        }
        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }
}


static const char * sBasicMatchNameShear = "Basic Transforms Match Shear";
TEST_CASE(sBasicMatchNameShear, "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    SECTION("SHEAR X")
    {
        {
            ref::Matrix4x4 SH;
            SH.makeShear3(tv.shearX, tv.shearY, tv.shearZ);
            refFinalTransform = SH;
        }
        {
            xbb::Shear3 SH(tv.shearX, tv.shearY, tv.shearZ);
            SH.to(xbbFinalTransform);
        }

        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }

    SECTION("SHEAR Y BY X")
    {
        {
            ref::Matrix4x4 SH;
            SH.makeShearOf(ref::axisY, ref::axisX, tv.shearX);
            refFinalTransform = SH;
        }
        {
            xbb::ShearOf<xbb::AxisY, xbb::AxisX> SH(tv.shearX);
            SH.to(xbbFinalTransform);
        }

        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }

    SECTION("SHEAR Z BY X")
    {
        {
            ref::Matrix4x4 SH;
            SH.makeShearOf(ref::axisZ, ref::axisX, tv.shearX);
            refFinalTransform = SH;
        }
        {
            xbb::ShearOf<xbb::AxisZ, xbb::AxisX> SH(tv.shearX);
            SH.to(xbbFinalTransform);
        }

        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }
    
    SECTION("SHEAR X BY Y")
    {
        {
            ref::Matrix4x4 SH;
            SH.makeShearOf(ref::axisX, ref::axisY, tv.shearY);
            refFinalTransform = SH;
        }
        {
            xbb::ShearOf<xbb::AxisX, xbb::AxisY> SH(tv.shearY);
            SH.to(xbbFinalTransform);
        }

        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }

    SECTION("SHEAR Z BY Y")
    {
        {
            ref::Matrix4x4 SH;
            SH.makeShearOf(ref::axisZ, ref::axisY, tv.shearY);
            refFinalTransform = SH;
        }
        {
            xbb::ShearOf<xbb::AxisZ, xbb::AxisY> SH(tv.shearY);
            SH.to(xbbFinalTransform);
        }

        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }   
    
    SECTION("SHEAR X BY Z")
    {
        {
            ref::Matrix4x4 SH;
            SH.makeShearOf(ref::axisX, ref::axisZ, tv.shearZ);
            refFinalTransform = SH;
        }
        {
            xbb::ShearOf<xbb::AxisX, xbb::AxisZ> SH(tv.shearZ);
            SH.to(xbbFinalTransform);
        }

        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }

    SECTION("SHEAR Y BY Z")
    {
        {
            ref::Matrix4x4 SH;
            SH.makeShearOf(ref::axisY, ref::axisZ, tv.shearZ);
            refFinalTransform = SH;
        }
        {
            xbb::ShearOf<xbb::AxisY, xbb::AxisZ> SH(tv.shearZ);
            SH.to(xbbFinalTransform);
        }

        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }       
    
    
    SECTION("Shear X by Y * X by Z")
    {
        {
            ref::Matrix4x4 ShXbyY;
            ShXbyY.makeShearOf(ref::axisX, ref::axisY, tv.shearY);
            ref::Matrix4x4 ShXbyZ;
            ShXbyZ.makeShearOf(ref::axisX, ref::axisZ, tv.shearZ);
            
            refFinalTransform = (ShXbyY*ShXbyZ);
        }
        {
            xbb::ShearOf<xbb::AxisX, xbb::AxisY> ShXbyY(tv.shearY);
            xbb::ShearOf<xbb::AxisX, xbb::AxisZ> ShXbyZ(tv.shearZ);
            (ShXbyY*ShXbyZ).to(xbbFinalTransform);            
        }
        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
    }
            
    SECTION("Shear X by Y * X by Z * Y by Z")
    {
        {
            ref::Matrix4x4 ShXbyY;
            ShXbyY.makeShearOf(ref::axisX, ref::axisY, tv.shearX);
            ref::Matrix4x4 ShXbyZ;
            ShXbyZ.makeShearOf(ref::axisX, ref::axisZ, tv.shearY);
            ref::Matrix4x4 ShYbyZ;
            ShYbyZ.makeShearOf(ref::axisY, ref::axisZ, tv.shearZ);
            
            refFinalTransform = (ShXbyY*ShXbyZ*ShYbyZ);
        }
        {
            xbb::ShearOf<xbb::AxisX, xbb::AxisY> ShXbyY(tv.shearX);
            xbb::ShearOf<xbb::AxisX, xbb::AxisZ> ShXbyZ(tv.shearY);
            xbb::ShearOf<xbb::AxisY, xbb::AxisZ> ShYbyZ(tv.shearZ);
            (ShXbyY*ShXbyZ*ShYbyZ).to(xbbFinalTransform);            
        }
        TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);        
    }
}



static const char * sBasicMatchNameTranspose = "Basic Transforms Match Transpose";
TEST_CASE(sBasicMatchNameTranspose, "")
{
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x4 xbbFinalTransform;

    
    {
	ref::Matrix4x4 mat;
        mat.m[0][0] = 100;
        mat.m[0][1] = 110;
        mat.m[0][2] = 120;
        mat.m[0][3] = 130;

        mat.m[1][0] = 101;
        mat.m[1][1] = 111;
        mat.m[1][2] = 121;
        mat.m[1][3] = 131;

        mat.m[2][0] = 102;
        mat.m[2][1] = 112;
        mat.m[2][2] = 122;
        mat.m[2][3] = 132;

        mat.m[3][0] = 103;
        mat.m[3][1] = 113;
        mat.m[3][2] = 123;
        mat.m[3][3] = 133;       	
	refFinalTransform = mat.transpose();
    }
    {
	xbb::Matrix4x4 mat;
        mat.m00 = 100;
        mat.m01 = 110;
        mat.m02 = 120;
        mat.m03 = 130;

        mat.m10 = 101;
        mat.m11 = 111;
        mat.m12 = 121;
        mat.m13 = 131;

        mat.m20 = 102;
        mat.m21 = 112;
        mat.m22 = 122;
        mat.m23 = 132;

        mat.m30 = 103;
        mat.m31 = 113;
        mat.m32 = 123;
        mat.m33 = 133;       	
	mat.transpose().to(xbbFinalTransform);
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}
