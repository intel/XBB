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
#include "ref/Vec3.h"
#include "AdaptRefToXbb.h"
#include "FloatingPointComparisons.h"
#include "TestValues.h"
#include "TransformsAreClose.h"


using namespace xbb;


static const char * sAdaptatersWorkName = "Adapters Work";
TEST_CASE(sAdaptatersWorkName, "")
{
    
    {
	ref::Matrix4x4 rMat;
	rMat.m[0][0] = 100;
	rMat.m[0][1] = 110;
	rMat.m[0][2] = 120;
	rMat.m[0][3] = 130;

	rMat.m[1][0] = 101;
	rMat.m[1][1] = 111;
	rMat.m[1][2] = 121;
	rMat.m[1][3] = 131;

	rMat.m[2][0] = 102;
	rMat.m[2][1] = 112;
	rMat.m[2][2] = 122;
	rMat.m[2][3] = 132;

	rMat.m[3][0] = 103;
	rMat.m[3][1] = 113;
	rMat.m[3][2] = 123;
	rMat.m[3][3] = 133;       	

	xbb::Matrix4x4 xMat(rMat);

	TRANSFORMS_ARE_CLOSE(xMat, rMat);
	
	ref::Matrix4x4 rMat2;
	xMat.to(rMat2);
	
	TRANSFORMS_ARE_CLOSE(xMat, rMat2);	
    }
    
    {
	ref::Vec3 rVec(1.0, 2.0, 3.0);
	xbb::Scale xScale(rVec);
	REQUIRE(isEqual(rVec.x(), xScale.x));
	REQUIRE(isEqual(rVec.y(), xScale.y));
	REQUIRE(isEqual(rVec.z(), xScale.z));
    }

    {
	ref::Vec3 rVec(1.0, 2.0, 3.0);
	xbb::Translation xTrans(rVec);
	REQUIRE(isEqual(rVec.x(), xTrans.x));
	REQUIRE(isEqual(rVec.y(), xTrans.y));
	REQUIRE(isEqual(rVec.z(), xTrans.z));
    }
    
    {
	ref::Vec3 rVec(1.0, 2.0, 3.0);
	xbb::Shear3 xShear(rVec);
	REQUIRE(isEqual(rVec.x(), xShear.x));
	REQUIRE(isEqual(rVec.y(), xShear.y));
	REQUIRE(isEqual(rVec.z(), xShear.z));
    }
    
}
