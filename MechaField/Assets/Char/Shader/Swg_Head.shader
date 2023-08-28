Shader "Custom/Swg_body" {
	Properties {
		_Color ("Color", Color) = (1,1,1,1)
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_RimColor ("림 색상" , color) = (1,1,1,1)
		_RimPower ("림 세기" , float ) = 1
	}
	SubShader {
		Tags { "RenderType"="Opaque" }

		CGPROGRAM
		#pragma surface surf SWG noambient

		sampler2D _MainTex;

		struct Input {
			float2 uv_MainTex;
			float3 viewDir;
		};

		float4 LightingSWG(SurfaceOutput s, float3 lightDir, float atten) {
			float NdotL = saturate(dot(s.Normal, lightDir)*0.5+0.55);
			float4 c;
			c.rgb = s.Albedo * _LightColor0.rgb * NdotL * atten;
			c.a = s.Alpha;
			return c;
		}

		//half _Glossiness;
		//half _Metallic;

		fixed4 _Color;
		float4 _RimColor;
		float _RimPower;
			
		UNITY_INSTANCING_BUFFER_START(Props)
		UNITY_INSTANCING_BUFFER_END(Props)

		void surf (Input IN, inout SurfaceOutput o) {
			fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
			o.Albedo = c.rgb;
			//o.Metallic = _Metallic;
			//o.Smoothness = _Glossiness;
			float rim = dot(normalize(IN.viewDir), o.Normal);
			rim = pow(1 - rim, _RimPower);
			o.Emission = rim * _RimColor.rgb;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
