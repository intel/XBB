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

#ifndef XBB_UNITTEST_FLOATING_POINT_COMPARISONS_H
#define XBB_UNITTEST_FLOATING_POINT_COMPARISONS_H

#ifndef XBB_UNITTEST_DEFAULT_RELATIVE_PERCENTAGE
    #define XBB_UNITTEST_DEFAULT_RELATIVE_PERCENTAGE 0.0005
#endif

#ifndef XBB_UNITTEST_DEFAULT_ABS_TOLERANCE
    #define XBB_UNITTEST_DEFAULT_ABS_TOLERANCE 0.000001
#endif

#include <math.h>

inline
bool isRelOrAbsEqual(double a, double b, double relativePercentage = XBB_UNITTEST_DEFAULT_RELATIVE_PERCENTAGE, double abs = XBB_UNITTEST_DEFAULT_ABS_TOLERANCE)
{
    if(fabs(a - b) < abs)
        return true;

    double relative;
    if(fabs(a) > fabs(b)) {
        relative = fabs((a-b)/a);
    } else {
        relative = fabs((a-b)/b);
    }
    return (relative <= relativePercentage);	
}

inline
bool isRelOrAbsEqual(float a, float b, float relativePercentage = XBB_UNITTEST_DEFAULT_RELATIVE_PERCENTAGE, float abs = XBB_UNITTEST_DEFAULT_ABS_TOLERANCE)
{
    if(fabsf(a - b) < abs)
        return true;

    float relative;
    if(fabsf(a) > fabsf(b)) {
        relative = fabsf((a-b)/a);
    } else {
        relative = fabsf((a-b)/b);
    }
    return (relative <= relativePercentage);	
}



template <typename T>
inline
bool isEqual(T a, T b)
{
	return (!(a > b) && !(a < b));
}


template <typename T>
inline
bool isClose(const T & a, const T & b)
{
	return isRelOrAbsEqual(a, b, XBB_UNITTEST_DEFAULT_RELATIVE_PERCENTAGE, XBB_UNITTEST_DEFAULT_ABS_TOLERANCE);
}

template <typename T>
inline
bool isExactly(const T & a, const T & b)
{
	return isEqual(a, b);
}


#endif // XBB_UNITTEST_FLOATING_POINT_COMPARISONS_H
