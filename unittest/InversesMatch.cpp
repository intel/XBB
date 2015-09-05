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



TEST_CASE("Inverses Match Scale", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 S;
        S.makeScale(tv.scaleX, tv.scaleY, tv.scaleZ);
        refFinalTransform = S.inverse();

        TRANSFORMS_ARE_CLOSE(S*refFinalTransform, refIdentity);
    }
    {
        xbb::Scale S(tv.scaleX, tv.scaleY, tv.scaleZ);
        S.inverse().to(xbbFinalTransform);
        TRANSFORMS_ARE_CLOSE((S*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear Y by X", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 SH;
        SH.makeShearOf(ref::axisY, ref::axisX, tv.shearX);
        refFinalTransform = SH.inverse();
        TRANSFORMS_ARE_CLOSE(SH*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisY, xbb::AxisX> SH(tv.shearX);
        SH.inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE((SH*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear Z by X", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 SH;
        SH.makeShearOf(ref::axisZ, ref::axisX, tv.shearX);
        refFinalTransform = SH.inverse();
        TRANSFORMS_ARE_CLOSE(SH*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisZ, xbb::AxisX> SH(tv.shearX);
        SH.inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE((SH*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear X by Y", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 SH;
        SH.makeShearOf(ref::axisX, ref::axisY, tv.shearY);
        refFinalTransform = SH.inverse();
        TRANSFORMS_ARE_CLOSE(SH*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisX, xbb::AxisY> SH(tv.shearY);
        SH.inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE((SH*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear Z by Y", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 SH;
        SH.makeShearOf(ref::axisZ, ref::axisY, tv.shearY);
        refFinalTransform = SH.inverse();
        TRANSFORMS_ARE_CLOSE(SH*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisZ, xbb::AxisY> SH(tv.shearY);
        SH.inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE((SH*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear X by Z", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 SH;
        SH.makeShearOf(ref::axisX, ref::axisZ, tv.shearZ);
        refFinalTransform = SH.inverse();
        TRANSFORMS_ARE_CLOSE(SH*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisX, xbb::AxisZ> SH(tv.shearZ);
        SH.inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE((SH*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear Y by Z", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 SH;
        SH.makeShearOf(ref::axisY, ref::axisZ, tv.shearZ);
        refFinalTransform = SH.inverse();
        TRANSFORMS_ARE_CLOSE(SH*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisY, xbb::AxisZ> SH(tv.shearZ);
        SH.inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE((SH*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear X by Y * X by Z", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 ShXbyY;
        ShXbyY.makeShearOf(ref::axisX, ref::axisY, tv.shearY);
        ref::Matrix4x4 ShXbyZ;
        ShXbyZ.makeShearOf(ref::axisX, ref::axisZ, tv.shearZ);

        refFinalTransform = (ShXbyY*ShXbyZ).inverse();
        TRANSFORMS_ARE_CLOSE((ShXbyY*ShXbyZ)*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisX, xbb::AxisY> ShXbyY(tv.shearY);
        xbb::ShearOf<xbb::AxisX, xbb::AxisZ> ShXbyZ(tv.shearZ);
        (ShXbyY*ShXbyZ).inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE(((ShXbyY*ShXbyZ)*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear X by Y * X by Z * Y by Z", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

            
    {
        ref::Matrix4x4 ShXbyY;
        ShXbyY.makeShearOf(ref::axisX, ref::axisY, tv.shearX);
        ref::Matrix4x4 ShXbyZ;
        ShXbyZ.makeShearOf(ref::axisX, ref::axisZ, tv.shearY);
        ref::Matrix4x4 ShYbyZ;
        ShYbyZ.makeShearOf(ref::axisY, ref::axisZ, tv.shearZ);

        refFinalTransform = (ShXbyY*ShXbyZ*ShYbyZ).inverse();
        TRANSFORMS_ARE_CLOSE((ShXbyY*ShXbyZ*ShYbyZ)*refFinalTransform, refIdentity);
    }
    {
        xbb::ShearOf<xbb::AxisX, xbb::AxisY> ShXbyY(tv.shearX);
        xbb::ShearOf<xbb::AxisX, xbb::AxisZ> ShXbyZ(tv.shearY);
        xbb::ShearOf<xbb::AxisY, xbb::AxisZ> ShYbyZ(tv.shearZ);
        (ShXbyY*ShXbyZ*ShYbyZ).inverse().to(xbbFinalTransform);            

        TRANSFORMS_ARE_CLOSE(((ShXbyY*ShXbyZ*ShYbyZ)*xbbFinalTransform).reduce(), xbb::Identity());

    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Shear", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 SH;
        SH.makeShear3(tv.shearX, tv.shearY, tv.shearZ);
        refFinalTransform = SH.inverse();
        TRANSFORMS_ARE_CLOSE(SH*refFinalTransform, refIdentity);
    }
    {
        xbb::Shear3 SH(tv.shearX, tv.shearY, tv.shearZ);
        SH.inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE((SH*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Rx", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;
    {
        ref::Matrix4x4 Rx;
        Rx.makeRotationX(tv.rotX);
        refFinalTransform = Rx.inverse();
        TRANSFORMS_ARE_CLOSE(Rx*refFinalTransform, refIdentity);
    }
    {
        xbb::RotationX Rx(tv.rotX);
        Rx.inverse().to(xbbFinalTransform);
        TRANSFORMS_ARE_CLOSE((Rx*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Ry", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    
    {
        ref::Matrix4x4 Ry;
        Ry.makeRotationY(tv.rotY);
        refFinalTransform = Ry.inverse();
        TRANSFORMS_ARE_CLOSE(Ry*refFinalTransform, refIdentity);
    }
    {
        xbb::RotationY Ry(tv.rotY);
        Ry.inverse().to(xbbFinalTransform);
        TRANSFORMS_ARE_CLOSE((Ry*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Rz", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 Rz;
        Rz.makeRotationZ(tv.rotZ);
        refFinalTransform = Rz.inverse();
        TRANSFORMS_ARE_CLOSE(Rz*refFinalTransform, refIdentity);
    }
    {
        xbb::RotationZ Rz(tv.rotZ);
        Rz.inverse().to(xbbFinalTransform);
        TRANSFORMS_ARE_CLOSE((Rz*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Translation", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 T;
        T.makeTranslation(tv.translateX, tv.translateY, tv.translateZ);
        refFinalTransform = T.inverse();
        TRANSFORMS_ARE_CLOSE(T*refFinalTransform, refIdentity);
    }
    {
        xbb::Translation T(tv.translateX, tv.translateY, tv.translateZ);    
        T.inverse().to(xbbFinalTransform);
        TRANSFORMS_ARE_CLOSE((T*xbbFinalTransform).reduce(), xbb::Identity());
    }
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}

TEST_CASE("Inverses Match Scale * SH", "")
{
    TestValues tv = TestValues::get();
    
    ref::Matrix4x4 refIdentity;
    refIdentity.makeIdentity();
    
    ref::Matrix4x4 refFinalTransform;
    xbb::Matrix4x3 xbbFinalTransform;

    {
        ref::Matrix4x4 S;
        S.makeScale(tv.scaleX, tv.scaleY, tv.scaleZ);

        ref::Matrix4x4 SH;
        SH.makeShear3(tv.shearX, tv.shearY, tv.shearZ);

        refFinalTransform = (S*SH).inverse();

        TRANSFORMS_ARE_CLOSE((S*SH)*refFinalTransform, refIdentity);            
    }    

    {
        xbb::Scale S(tv.scaleX, tv.scaleY, tv.scaleZ);
        xbb::Shear3 SH(tv.shearX, tv.shearY, tv.shearZ);

        (S*SH).inverse().to(xbbFinalTransform);

        TRANSFORMS_ARE_CLOSE(((S*SH)*xbbFinalTransform).reduce(), xbb::Identity());            
    }    
    TRANSFORMS_ARE_CLOSE(xbbFinalTransform, refFinalTransform);
}



