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

#ifndef TRANSFORMS_ARE_CLOSE_H
#define TRANSFORMS_ARE_CLOSE_H 1

#include <stdio.h>
#include <iostream>

#include "FloatingPointComparisons.h"


using namespace xbb;

#define TRANSFORMS_ARE_CLOSE(LEFT, RIGHT) \
{ \
    auto left = LEFT; \
    auto right = RIGHT; \
    if (TransformsAreClose(left, right) == false) { \
        std::cout << "Left Transform " << left << std::endl; \
        std::cout << "Right Transform " << right << std::endl; \
        REQUIRE(isClose(left.e00(), right.e00())); \
        REQUIRE(isClose(left.e01(), right.e01())); \
        REQUIRE(isClose(left.e02(), right.e02())); \
        REQUIRE(isClose(left.e03(), right.e03())); \
\
        REQUIRE(isClose(left.e10(), right.e10())); \
        REQUIRE(isClose(left.e11(), right.e11())); \
        REQUIRE(isClose(left.e12(), right.e12())); \
        REQUIRE(isClose(left.e13(), right.e13())); \
\
        REQUIRE(isClose(left.e20(), right.e20())); \
        REQUIRE(isClose(left.e21(), right.e21())); \
        REQUIRE(isClose(left.e22(), right.e22())); \
        REQUIRE(isClose(left.e23(), right.e23())); \
\
        REQUIRE(isClose(left.e30(), right.e30())); \
        REQUIRE(isClose(left.e31(), right.e31())); \
        REQUIRE(isClose(left.e32(), right.e32())); \
        REQUIRE(isClose(left.e33(), right.e33())); \
    } \
}

template<typename LeftT, typename RightT>
bool TransformsAreClose(const LeftT &iLeft, const RightT &iRight)
{
    return (isClose(iRight.e00(), iLeft.e00())) &&
        (isClose(iRight.e01(), iLeft.e01())) &&
        (isClose(iRight.e02(), iLeft.e02())) &&
        (isClose(iRight.e03(), iLeft.e03())) &&

        (isClose(iRight.e10(), iLeft.e10())) &&
        (isClose(iRight.e11(), iLeft.e11())) &&
        (isClose(iRight.e12(), iLeft.e12())) &&
        (isClose(iRight.e13(), iLeft.e13())) &&

        (isClose(iRight.e20(), iLeft.e20())) &&
        (isClose(iRight.e21(), iLeft.e21())) &&
        (isClose(iRight.e22(), iLeft.e22())) &&
        (isClose(iRight.e23(), iLeft.e23())) &&

        (isClose(iRight.e30(), iLeft.e30())) &&
        (isClose(iRight.e31(), iLeft.e31())) &&
        (isClose(iRight.e32(), iLeft.e32())) &&
        (isClose(iRight.e33(), iLeft.e33()));
}

#endif // TRANSFORMS_ARE_CLOSE_H

