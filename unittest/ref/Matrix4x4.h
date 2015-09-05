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

#ifndef REF_MATRIX_4_X_4_H
#define REF_MATRIX_4_X_4_H

#include <ostream>

namespace ref {
    
enum axis
{
    axisX = 0,
    axisY = 1,
    axisZ = 2
};
    
struct Matrix4x4
{
    Matrix4x4() 
    { 
        // unitialized 
    }

    // Column # Row #
    double m[4][4];

    double e00() const { return m[0][0]; }    
    double e01() const { return m[0][1]; }    
    double e02() const { return m[0][2]; }    
    double e03() const { return m[0][3]; }    

    double e10() const { return m[1][0]; }    
    double e11() const { return m[1][1]; }    
    double e12() const { return m[1][2]; }    
    double e13() const { return m[1][3]; }    

    double e20() const { return m[2][0]; }    
    double e21() const { return m[2][1]; }    
    double e22() const { return m[2][2]; }    
    double e23() const { return m[2][3]; }    

    double e30() const { return m[3][0]; }    
    double e31() const { return m[3][1]; }    
    double e32() const { return m[3][2]; }    
    double e33() const { return m[3][3]; }            
        
    void makeIdentity() 
    {
        m[0][0] = 1.0;
        m[0][1] = 0.0;
        m[0][2] = 0.0;
        m[0][3] = 0.0;
        
        m[1][0] = 0.0;
        m[1][1] = 1.0;
        m[1][2] = 0.0;
        m[1][3] = 0.0;
        
        m[2][0] = 0.0;
        m[2][1] = 0.0;
        m[2][2] = 1.0;
        m[2][3] = 0.0;
        
        m[3][0] = 0.0;
        m[3][1] = 0.0;
        m[3][2] = 0.0;
        m[3][3] = 1.0;        
    }
    
    void makeTranslation(double iTranslateX, double iTranslateY, double iTranslateZ)
    {
        makeIdentity();
        
        m[3][0] = iTranslateX;
        m[3][1] = iTranslateY;
        m[3][2] = iTranslateZ;
    }

    void makeScale(double iScaleX, double iScaleY, double iScaleZ)
    {
        makeIdentity();
        
        m[0][0] = iScaleX;
        m[1][1] = iScaleY;
        m[2][2] = iScaleZ;
    }
    
    
    // Good explanation of shear
    // http://www.flipcode.com/documents/matrfaq.html#Q43
    void makeShearOf(axis iShearedAxis, axis iFixedAxis, double iShearFactor)
    {
        XBB_ASSERT(iShearedAxis != iFixedAxis);
        makeIdentity();
        
        m[iFixedAxis][iShearedAxis] = iShearFactor;
    }
    
    void makeShear3(double iShearX, double iShearY, double iShearZ)
    {
        makeIdentity();
        
        m[1][0] = iShearX;
        m[2][0] = iShearY;
        m[2][1] = iShearZ;
    }

    void makeRotationX(double aAngle)
    {
        makeIdentity();
        
        double cosX = cos(aAngle);
        double sinX = sin(aAngle);

        m[1][1] = cosX;
        m[1][2] = sinX;
        m[2][1] = -sinX;
        m[2][2] = cosX;
    }
    
    void makeRotationY(double aAngle)
    {
        makeIdentity();
        
        double cosY = cos(aAngle);
        double sinY = sin(aAngle);

        m[0][0] = cosY;
        m[0][2] = -sinY;
        m[2][0] = sinY;
        m[2][2] = cosY;
    }
    
    void makeRotationZ(double aAngle)
    {
        makeIdentity();
        
        double cosZ = cos(aAngle);
        double sinZ = sin(aAngle);

        m[0][0] = cosZ;
        m[0][1] = sinZ;
        m[1][0] = -sinZ;
        m[1][1] = cosZ;
    }
    
    ref::Matrix4x4 operator * (double iScalar) {
        ref::Matrix4x4 result;
        
        result.m[0][0] = m[0][0]*iScalar;
        result.m[0][1] = m[0][1]*iScalar;
        result.m[0][2] = m[0][2]*iScalar;
        result.m[0][3] = m[0][3]*iScalar;

        result.m[1][0] = m[1][0]*iScalar;
        result.m[1][1] = m[1][1]*iScalar;
        result.m[1][2] = m[1][2]*iScalar;
        result.m[1][3] = m[1][3]*iScalar;

        result.m[2][0] = m[2][0]*iScalar;
        result.m[2][1] = m[2][1]*iScalar;
        result.m[2][2] = m[2][2]*iScalar;
        result.m[2][3] = m[2][3]*iScalar;

        result.m[3][0] = m[3][0]*iScalar;
        result.m[3][1] = m[3][1]*iScalar;
        result.m[3][2] = m[3][2]*iScalar;
        result.m[3][3] = m[3][3]*iScalar;        
        
        return result;
    }

    
    ref::Matrix4x4 operator * (const ref::Matrix4x4 &iOther) {
        ref::Matrix4x4 result;
        
        result.m[0][0] = m[0][0]*iOther.m[0][0] +
                          m[0][1]*iOther.m[1][0] +
                          m[0][2]*iOther.m[2][0] +
                          m[0][3]*iOther.m[3][0];
        result.m[0][1] = m[0][0]*iOther.m[0][1] +
                          m[0][1]*iOther.m[1][1] +
                          m[0][2]*iOther.m[2][1] +
                          m[0][3]*iOther.m[3][1];
        result.m[0][2] = m[0][0]*iOther.m[0][2] +
                          m[0][1]*iOther.m[1][2] +
                          m[0][2]*iOther.m[2][2] +
                          m[0][3]*iOther.m[3][2];
        result.m[0][3] = m[0][0]*iOther.m[0][3] +
                          m[0][1]*iOther.m[1][3] +
                          m[0][2]*iOther.m[2][3] +
                          m[0][3]*iOther.m[3][3];

        result.m[1][0] = m[1][0]*iOther.m[0][0] +
                          m[1][1]*iOther.m[1][0] +
                          m[1][2]*iOther.m[2][0] +
                          m[1][3]*iOther.m[3][0];
        result.m[1][1] = m[1][0]*iOther.m[0][1] +
                          m[1][1]*iOther.m[1][1] +
                          m[1][2]*iOther.m[2][1] +
                          m[1][3]*iOther.m[3][1];
        result.m[1][2] = m[1][0]*iOther.m[0][2] +
                          m[1][1]*iOther.m[1][2] +
                          m[1][2]*iOther.m[2][2] +
                          m[1][3]*iOther.m[3][2];
        result.m[1][3] = m[1][0]*iOther.m[0][3] +
                          m[1][1]*iOther.m[1][3] +
                          m[1][2]*iOther.m[2][3] +
                          m[1][3]*iOther.m[3][3];

        result.m[2][0] = m[2][0]*iOther.m[0][0] +
                          m[2][1]*iOther.m[1][0] +
                          m[2][2]*iOther.m[2][0] +
                          m[2][3]*iOther.m[3][0];
        result.m[2][1] = m[2][0]*iOther.m[0][1] +
                          m[2][1]*iOther.m[1][1] +
                          m[2][2]*iOther.m[2][1] +
                          m[2][3]*iOther.m[3][1];
        result.m[2][2] = m[2][0]*iOther.m[0][2] +
                          m[2][1]*iOther.m[1][2] +
                          m[2][2]*iOther.m[2][2] +
                          m[2][3]*iOther.m[3][2];
        result.m[2][3] = m[2][0]*iOther.m[0][3] +
                          m[2][1]*iOther.m[1][3] +
                          m[2][2]*iOther.m[2][3] +
                          m[2][3]*iOther.m[3][3];

        result.m[3][0] = m[3][0]*iOther.m[0][0] +
                          m[3][1]*iOther.m[1][0] +
                          m[3][2]*iOther.m[2][0] +
                          m[3][3]*iOther.m[3][0];
        result.m[3][1] = m[3][0]*iOther.m[0][1] +
                          m[3][1]*iOther.m[1][1] +
                          m[3][2]*iOther.m[2][1] +
                          m[3][3]*iOther.m[3][1];
        result.m[3][2] = m[3][0]*iOther.m[0][2] +
                          m[3][1]*iOther.m[1][2] +
                          m[3][2]*iOther.m[2][2] +
                          m[3][3]*iOther.m[3][2];
        result.m[3][3] = m[3][0]*iOther.m[0][3] +
                          m[3][1]*iOther.m[1][3] +
                          m[3][2]*iOther.m[2][3] +
                          m[3][3]*iOther.m[3][3];
        
        return result;
    }

    ref::Matrix4x4 transpose() const {
        ref::Matrix4x4 result;
        
        result.m[0][0] = m[0][0];
        result.m[0][1] = m[1][0];
        result.m[0][2] = m[2][0];
        result.m[0][3] = m[3][0];

        result.m[1][0] = m[0][1];
        result.m[1][1] = m[1][1];
        result.m[1][2] = m[2][1];
        result.m[1][3] = m[3][1];

        result.m[2][0] = m[0][2];
        result.m[2][1] = m[1][2];
        result.m[2][2] = m[2][2];
        result.m[2][3] = m[3][2];

        result.m[3][0] = m[0][3];
        result.m[3][1] = m[1][3];
        result.m[3][2] = m[2][3];
        result.m[3][3] = m[3][3];        
        
        return result;
    }
    
    
    double determinant2(int iRow0, int iRow1, int iCol0, int iCol1)
    {
        // Take the intersection of two rows and columns as a 2x2 matrix
        // | a b |
        // | c d | = ad - bc
        return m[iRow0][iCol0]*m[iRow1][iCol1] - m[iRow0][iCol1]*m[iRow1][iCol0];
    }

    double determinant3(int iRow0, int iRow1, int iRow2, int iCol0, int iCol1, int iCol2)
    {
        // Take the intersection of two rows and columns as a 3x3 matrix
        // | a b c |
        // | d e f | = a * | e f | - b * | d f | + c * | d e |
        // | g h i |       | h i |       [ g i |       | h i |
        
        return   m[iRow0][iCol0]*determinant2(iRow1, iRow2, iCol1, iCol2)
               - m[iRow0][iCol1]*determinant2(iRow1, iRow2, iCol0, iCol2)
               + m[iRow0][iCol2]*determinant2(iRow1, iRow2, iCol0, iCol1);
    }
    
    
    ref::Matrix4x4 cofactor(double &aDeterminant) {
        ref::Matrix4x4 result;
        
        // NOTE: the we take the determinant of the minor and apply the
        // cofactor sign pattern
        double minor00 = determinant3(1, 2, 3, 1, 2, 3);
        double minor01 = determinant3(1, 2, 3, 0, 2, 3);
        double minor02 = determinant3(1, 2, 3, 0, 1, 3);
        double minor03 = determinant3(1, 2, 3, 0, 1, 2);
        
        aDeterminant = m[0][0]*minor00 - m[0][1]*minor01 + m[0][2]*minor02 - m[0][3]*minor03;
        
        result.m[0][0] = + minor00; 
        result.m[0][1] = - minor01;
        result.m[0][2] = + minor02;
        result.m[0][3] = - minor03;

        result.m[1][0] = - determinant3(0, 2, 3, 1, 2, 3);
        result.m[1][1] = + determinant3(0, 2, 3, 0, 2, 3);
        result.m[1][2] = - determinant3(0, 2, 3, 0, 1, 3);
        result.m[1][3] = + determinant3(0, 2, 3, 0, 1, 2);

        result.m[2][0] = + determinant3(0, 1, 3, 1, 2, 3);
        result.m[2][1] = - determinant3(0, 1, 3, 0, 2, 3);
        result.m[2][2] = + determinant3(0, 1, 3, 0, 1, 3);
        result.m[2][3] = - determinant3(0, 1, 3, 0, 1, 2);

        result.m[3][0] = - determinant3(0, 1, 2, 1, 2, 3);
        result.m[3][1] = + determinant3(0, 1, 2, 0, 2, 3);
        result.m[3][2] = - determinant3(0, 1, 2, 0, 1, 3);
        result.m[3][3] = + determinant3(0, 1, 2, 0, 1, 2);
        
        return result;
    }    
    
    ref::Matrix4x4 adjoint(double &aDeterminant) {
        return cofactor(aDeterminant).transpose();
    }
    
    ref::Matrix4x4 __attribute__((noinline)) inverse() {
        // Cramer's rule
        // https://people.richland.edu/james/lecture/m116/matrices/determinant.html
        double det;        
        ref::Matrix4x4 adj = adjoint(det);
        double reciprocolOfDet = 1.0/det;
        return adj*reciprocolOfDet;
    }
    
    
    
    friend std::ostream& operator<<(std::ostream& iStream, const Matrix4x4 & iMat)
    {
        iStream << std::endl <<
            "[" << iMat.m[0][0] << ", " << iMat.m[0][1] << ", " << iMat.m[0][2] << ", " << iMat.m[0][3] << "], [" << std::endl <<
            "[" << iMat.m[1][0] << ", " << iMat.m[1][1] << ", " << iMat.m[1][2] << ", " << iMat.m[1][3] << "], [" << std::endl <<
            "[" << iMat.m[2][0] << ", " << iMat.m[2][1] << ", " << iMat.m[2][2] << ", " << iMat.m[2][3] << "], [" << std::endl <<
            "[" << iMat.m[3][0] << ", " << iMat.m[3][1] << ", " << iMat.m[3][2] << ", " << iMat.m[3][3] << "]" << std::endl;
        return iStream;
    }
    
};
    
} // namespace ref

#endif // REF_MATRIX_4_X_4_H
