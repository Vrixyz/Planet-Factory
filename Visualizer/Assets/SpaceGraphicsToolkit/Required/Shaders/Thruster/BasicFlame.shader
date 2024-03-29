Shader "SGT/Thruster/Basic Flame"
{
	Properties
	{
		thrusterTexture("thrusterTexture", 2D) = "gray" {}
		thrusterGlow("thrusterGlow", Float) = 0.0
		thrusterColour("thrusterColour", Color) = (1.0, 1.0, 1.0, 1.0)
	}
	
	Category
	{
		Blend One One
		Cull Off
		ZWrite Off
		ZTest LEqual
		
		SubShader
		{
			Tags {"Queue"="Transparent"}
			Pass
			{
				CGPROGRAM
				
				#pragma vertex   Vert
				#pragma fragment Frag
				
				
				#include "../CGInclude/Thruster.cginc"
				
				ENDCG
			}
		}
	}
}