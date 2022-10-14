/*===================================================================================
*	Date : 2022/10/14(Fri)
*		Author	: Gakuto.S
*		File	: pixelShader.hlsl
*		Detail	:
===================================================================================*/
#include "common.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
    // float4 texColor = g_texture.Sample(g_sampler, input.TexCoord);
    
    return float4(input.TexCoord, 1.0, 1.0);
}