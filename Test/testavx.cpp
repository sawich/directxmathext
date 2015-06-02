#include <windows.h>
#include <stdio.h>

#include "DirectXMathAVX.h"

using namespace DirectX;

void main()
{
    if ( XMVerifyCPUSupport() )
    {
        printf("CPU supported for SSE/SSE2\n");
    }

    if ( AVX::XMVerifyAVXSupport() )
    {
        printf("AVX supported\n");
    }
}