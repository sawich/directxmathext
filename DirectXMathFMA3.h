//-------------------------------------------------------------------------------------
// DirectXMathFMA3.h -- FMA3 extensions for SIMD C++ Math library
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//  
// Copyright (c) Microsoft Corporation. All rights reserved.
//-------------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _M_ARM
#error FMA3 not supported on ARM platform
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1700)
#error FMA3 intrinsics requires Visual C++ 2012 or later.
#endif

#pragma warning(push)
#pragma warning(disable : 4987)
#include <intrin.h>
#pragma warning(pop)

#include <immintrin.h>

#include <DirectXMath.h>

namespace DirectX
{
#if (DIRECTXMATH_VERSION < 305) && !defined(XM_CALLCONV)
#define XM_CALLCONV __fastcall
typedef const DirectX::XMVECTOR& HXMVECTOR;
typedef const DirectX::XMMATRIX& FXMMATRIX;
#endif

namespace FMA3
{

inline bool XMVerifyFMA3Support()
{
    // Should return true for AMD "Pildriver" and Intel "Haswell" processors
    // with OS support for AVX (Windows 7 Service Pack 1, Windows Server 2008 R2 Service Pack 1, Windows 8, Windows Server 2012)

    // See http://msdn.microsoft.com/en-us/library/hskdteyh.aspx
    int CPUInfo[4] = {-1};
    __cpuid( CPUInfo, 0 );

    if ( CPUInfo[0] < 1  )
        return false;

    __cpuid(CPUInfo, 1 );

    // We check for FMA3, AVX, OSXSAVE
    return ( (CPUInfo[2] & 0x18001000) == 0x18001000 );
}


//-------------------------------------------------------------------------------------
// Vector
//-------------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVectorMultiplyAdd
(
    FXMVECTOR V1, 
    FXMVECTOR V2, 
    FXMVECTOR V3
)
{
    return _mm_fmadd_ps( V1, V2, V3 );
}


//-------------------------------------------------------------------------------------
// Vector2
//-------------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector2Transform
(
    FXMVECTOR V, 
    CXMMATRIX M
)
{
    XMVECTOR vResult = _mm_permute_ps(V,_MM_SHUFFLE(1,1,1,1)); // Y
    vResult = _mm_fmadd_ps( vResult, M.r[1], M.r[3] );
    XMVECTOR vTemp = _mm_permute_ps(V,_MM_SHUFFLE(0,0,0,0)); // X
    vResult = _mm_fmadd_ps( vTemp, M.r[0], vResult );
    return vResult;
}

inline XMVECTOR XM_CALLCONV XMVector2TransformCoord
(
    FXMVECTOR V, 
    CXMMATRIX M
)
{
    XMVECTOR vResult = _mm_permute_ps(V,_MM_SHUFFLE(1,1,1,1)); // Y
    vResult = _mm_fmadd_ps( vResult, M.r[1], M.r[3] );
    XMVECTOR vTemp = _mm_permute_ps(V,_MM_SHUFFLE(0,0,0,0)); // X
    vResult = _mm_fmadd_ps( vTemp, M.r[0], vResult );
    XMVECTOR W = _mm_permute_ps(vResult,_MM_SHUFFLE(3,3,3,3));
    vResult = _mm_div_ps( vResult, W );
    return vResult;
}

inline XMVECTOR XM_CALLCONV XMVector2TransformNormal
(
    FXMVECTOR V, 
    CXMMATRIX M
)
{
    XMVECTOR vResult = _mm_permute_ps(V,_MM_SHUFFLE(1,1,1,1)); // Y
    vResult = _mm_mul_ps( vResult, M.r[1] );
    XMVECTOR vTemp = _mm_permute_ps(V,_MM_SHUFFLE(0,0,0,0)); // X
    vResult = _mm_fmadd_ps( vTemp, M.r[0], vResult );
    return vResult;
}


//-------------------------------------------------------------------------------------
// Vector3
//-------------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector3Transform
(
    FXMVECTOR V, 
    CXMMATRIX M
)
{
    XMVECTOR vResult = _mm_permute_ps(V,_MM_SHUFFLE(2,2,2,2)); // Z
    vResult = _mm_fmadd_ps( vResult, M.r[2], M.r[3] );
    XMVECTOR vTemp = _mm_permute_ps(V,_MM_SHUFFLE(1,1,1,1)); // Y
    vResult = _mm_fmadd_ps( vTemp, M.r[1], vResult );
    vTemp = _mm_permute_ps(V,_MM_SHUFFLE(0,0,0,0)); // X
    vResult = _mm_fmadd_ps( vTemp, M.r[0], vResult );
    return vResult;
}

inline XMVECTOR XM_CALLCONV XMVector3TransformCoord
(
    FXMVECTOR V, 
    CXMMATRIX M
)
{
    XMVECTOR vResult = _mm_permute_ps(V,_MM_SHUFFLE(2,2,2,2)); // Z
    vResult = _mm_fmadd_ps( vResult, M.r[2], M.r[3] );
    XMVECTOR vTemp = _mm_permute_ps(V,_MM_SHUFFLE(1,1,1,1)); // Y
    vResult = _mm_fmadd_ps( vTemp, M.r[1], vResult );
    vTemp = _mm_permute_ps(V,_MM_SHUFFLE(0,0,0,0)); // X
    vResult = _mm_fmadd_ps( vTemp, M.r[0], vResult );
    XMVECTOR W = _mm_permute_ps(vResult,_MM_SHUFFLE(3,3,3,3));
    vResult = _mm_div_ps( vResult, W );
    return vResult;
}

inline XMVECTOR XM_CALLCONV XMVector3TransformNormal
(
    FXMVECTOR V, 
    CXMMATRIX M
)
{
    XMVECTOR vResult = _mm_permute_ps(V,_MM_SHUFFLE(2,2,2,2)); // Z
    vResult = _mm_mul_ps( vResult, M.r[2] );
    XMVECTOR vTemp = _mm_permute_ps(V,_MM_SHUFFLE(1,1,1,1)); // Y
    vResult = _mm_fmadd_ps( vTemp, M.r[1], vResult );
    vTemp = _mm_permute_ps(V,_MM_SHUFFLE(0,0,0,0)); // X
    vResult = _mm_fmadd_ps( vTemp, M.r[0], vResult );
    return vResult;
}

XMMATRIX XM_CALLCONV XMMatrixMultiply(CXMMATRIX M1, CXMMATRIX M2);

inline XMVECTOR XM_CALLCONV XMVector3Project
(
    FXMVECTOR V, 
    float    ViewportX, 
    float    ViewportY, 
    float    ViewportWidth, 
    float    ViewportHeight, 
    float    ViewportMinZ, 
    float    ViewportMaxZ, 
    CXMMATRIX Projection, 
    CXMMATRIX View, 
    CXMMATRIX World
)
{
    const float HalfViewportWidth = ViewportWidth * 0.5f;
    const float HalfViewportHeight = ViewportHeight * 0.5f;

    XMVECTOR Scale = XMVectorSet(HalfViewportWidth, -HalfViewportHeight, ViewportMaxZ - ViewportMinZ, 0.0f);
    XMVECTOR Offset = XMVectorSet(ViewportX + HalfViewportWidth, ViewportY + HalfViewportHeight, ViewportMinZ, 0.0f);

    XMMATRIX Transform = FMA3::XMMatrixMultiply(World, View);
    Transform = FMA3::XMMatrixMultiply(Transform, Projection);

    XMVECTOR Result = FMA3::XMVector3TransformCoord(V, Transform);

    Result = FMA3::XMVectorMultiplyAdd(Result, Scale, Offset);

    return Result;
}

inline XMVECTOR XM_CALLCONV XMVector3Unproject
(
    FXMVECTOR V, 
    float     ViewportX, 
    float     ViewportY, 
    float     ViewportWidth, 
    float     ViewportHeight, 
    float     ViewportMinZ, 
    float     ViewportMaxZ, 
    CXMMATRIX Projection, 
    CXMMATRIX View, 
    CXMMATRIX World
)
{
    static const XMVECTORF32 D = { -1.0f, 1.0f, 0.0f, 0.0f };

    XMVECTOR Scale = XMVectorSet(ViewportWidth * 0.5f, -ViewportHeight * 0.5f, ViewportMaxZ - ViewportMinZ, 1.0f);
    Scale = XMVectorReciprocal(Scale);

    XMVECTOR Offset = XMVectorSet(-ViewportX, -ViewportY, -ViewportMinZ, 0.0f);
    Offset = FMA3::XMVectorMultiplyAdd(Scale, Offset, D.v);

    XMMATRIX Transform = FMA3::XMMatrixMultiply(World, View);
    Transform = FMA3::XMMatrixMultiply(Transform, Projection);
    Transform = XMMatrixInverse(nullptr, Transform);

    XMVECTOR Result = FMA3::XMVectorMultiplyAdd(V, Scale, Offset);

    return FMA3::XMVector3TransformCoord(Result, Transform);
}


//-------------------------------------------------------------------------------------
// Vector4
//-------------------------------------------------------------------------------------

inline XMVECTOR XM_CALLCONV XMVector4Transform
(
    FXMVECTOR V, 
    CXMMATRIX M
)
{
    XMVECTOR vResult = _mm_permute_ps(V,_MM_SHUFFLE(3,3,3,3)); // W
    vResult = _mm_mul_ps( vResult, M.r[3] );
    XMVECTOR vTemp = _mm_permute_ps(V,_MM_SHUFFLE(2,2,2,2)); // Z
    vResult = _mm_fmadd_ps( vTemp, M.r[2], vResult );
    vTemp = _mm_permute_ps(V,_MM_SHUFFLE(1,1,1,1)); // Y
    vResult = _mm_fmadd_ps( vTemp, M.r[1], vResult );
    vTemp = _mm_permute_ps(V,_MM_SHUFFLE(0,0,0,0)); // X
    vResult = _mm_fmadd_ps( vTemp, M.r[0], vResult );
    return vResult;
}


//-------------------------------------------------------------------------------------
// Matrix
//-------------------------------------------------------------------------------------

inline XMMATRIX XM_CALLCONV XMMatrixMultiply
(
    CXMMATRIX M1, 
    CXMMATRIX M2
)
{
    XMMATRIX mResult;
    // Use vW to hold the original row
    XMVECTOR vW = M1.r[0];
    // Splat the component X,Y,Z then W
    XMVECTOR vX = _mm_permute_ps(vW,_MM_SHUFFLE(0,0,0,0));
    XMVECTOR vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    XMVECTOR vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    // Perform the operation on the first row
    vX = _mm_mul_ps(vX,M2.r[0]);
    vX = _mm_fmadd_ps(vY,M2.r[1],vX);
    vX = _mm_fmadd_ps(vZ,M2.r[2],vX);
    vX = _mm_fmadd_ps(vW,M2.r[3],vX);
    mResult.r[0] = vX;
    // Repeat for the other 3 rows
    vW = M1.r[1];
    vX = _mm_permute_ps(vW,_MM_SHUFFLE(0,0,0,0));
    vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    vX = _mm_mul_ps(vX,M2.r[0]);
    vX = _mm_fmadd_ps(vY,M2.r[1],vX);
    vX = _mm_fmadd_ps(vZ,M2.r[2],vX);
    vX = _mm_fmadd_ps(vW,M2.r[3],vX);
    mResult.r[1] = vX;
    vW = M1.r[2];
    vX = _mm_permute_ps(vW,_MM_SHUFFLE(0,0,0,0));
    vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    vX = _mm_mul_ps(vX,M2.r[0]);
    vX = _mm_fmadd_ps(vY,M2.r[1],vX);
    vX = _mm_fmadd_ps(vZ,M2.r[2],vX);
    vX = _mm_fmadd_ps(vW,M2.r[3],vX);
    mResult.r[2] = vX;
    vW = M1.r[3];
    vX = _mm_permute_ps(vW,_MM_SHUFFLE(0,0,0,0));
    vY = _mm_permute_ps(vW,_MM_SHUFFLE(1,1,1,1));
    vZ = _mm_permute_ps(vW,_MM_SHUFFLE(2,2,2,2));
    vW = _mm_permute_ps(vW,_MM_SHUFFLE(3,3,3,3));
    vX = _mm_mul_ps(vX,M2.r[0]);
    vX = _mm_fmadd_ps(vY,M2.r[1],vX);
    vX = _mm_fmadd_ps(vZ,M2.r[2],vX);
    vX = _mm_fmadd_ps(vW,M2.r[3],vX);
    mResult.r[3] = vX;
    return mResult;
}

}; // namespace FMA3

}; // namespace DirectX;
