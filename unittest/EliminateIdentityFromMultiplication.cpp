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


TEST_CASE("Elimination of Identity from Multiplication")
{    
    // When multiplying transforms together, Identity should disappear
    
    xbb::Identity I;
    xbb::Translation T;
    xbb::Scale S;
    xbb::Shear3 SH;
    xbb::RotationX Rx;
    xbb::RotationY Ry;
    xbb::RotationZ Rz;
    
    // Require identity to quietly disappear from multiplication chains
    {    
        auto result = T*I;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::Translation>() == true);
    }

    {    
        auto result = I*T;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::Translation>() == true);
    }
    
    {    
        auto result = S*I;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::Scale>() == true);
    }

    {    
        auto result = I*S;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::Scale>() == true);
    }
    
    {    
        auto result = SH*I;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::Shear3>() == true);
    }

    {    
        auto result = I*SH;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::Shear3>() == true);
    }    

    {    
        auto result = Rx*I;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::RotationX>() == true);
    }

    {    
        auto result = I*Rx;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::RotationX>() == true);
    }    

    {    
        auto result = Ry*I;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::RotationY>() == true);
    }

    {    
        auto result = I*Ry;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<xbb::RotationY>() == true);
    }    

    {    
        auto result = I*S*SH;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<decltype(S*SH)>() == true);
    }    
    
    {    
        auto result = S*SH*I;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<decltype(S*SH)>() == true);
    }    

    {    
        auto result = S*I*SH;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<decltype(S*SH)>() == true);
    }

    {    
        auto result = S*SH*I*Rz*Ry*Rz*I*T;
        REQUIRE(result.is<xbb::Identity>() == false) ;
        REQUIRE(result.is<decltype(S*SH*Rz*Ry*Rz*T)>() == true);
    }    
    
}

