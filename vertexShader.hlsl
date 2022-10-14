/*===================================================================================
*	Date : 2022/10/14(Fri)
*		Author	: Gakuto.S
*		File	: vertexShader.hlsl
*		Detail	:
===================================================================================*/
#include "common.hlsli"

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;
    
    //matrix wvp = mul(world, view);
    //wvp = mul(wvp, projection);
    
    output.Position = mul(input.Position, world);
    //output.Position = input.Position;
    output.TexCoord = input.TexCoord;
    
	return output;
}