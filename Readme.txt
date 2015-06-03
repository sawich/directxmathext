----------------------
DirectXMath Extensions
----------------------

Copyright (c) Microsoft Corporation. All rights reserved.

June 2, 2015

This package contains headers for advanced instruction set variants of DirectXMath routines for use in Windows applications in guarded code-paths.

    DirectXMathSSE3.h
    - SSE3

    DirectXMathBE.h
    - Supplemental SSE3 (SSSE3)

    DirectXMathSSE4.h
    - SSE4.1

    DirectXMathAVX.h
    - Advanced Vector Extensions (AVX)

    DirectXMathAVX2.h
    - Advanced Vector Extensions 2 (AVX2)

    DirectXMathF16C.h
    - Half-precision conversions (F16C)

    DirectXMathFMA3.h
    - Fused multiply-accumulate (FMA3)

    DirectXMathFMA4.h
    - Fused multiply-accumulate (FMA4)

    Test\
    - Tester applications

http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse-sse2-and-arm-neon.aspx
http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse3-and-ssse3.aspx
http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse4-1-and-sse-4-2.aspx
http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-avx.aspx
http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-f16c-and-fma.aspx
http://blogs.msdn.com/b/chuckw/archive/2015/06/03/directxmath-avx2.aspx

http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx

All content and source code for this package are subject to the terms of the MIT License.
<http://opensource.org/licenses/MIT>.

For the latest version and documentation, please visit the GitHub site.

https://github.com/walbourn/directxmathext

---------------
RELEASE HISTORY
---------------

June 2, 2015
    AVX2 header
    Added FMA implementations of XMVectorNegativeMultiplySubtract, XMMatrixMultiplyTranspose

September 11, 2012
    Original release
