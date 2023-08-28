Shader "Custom/Swg_body" {
	Properties {
		_Color ("Color", Color) = (1,1,1,1)
		_MainTex ("Albedo (RGB)", 2D) = "white" {}
		_RimColor ("림 색상" , color) = (1,1,1,1)
		_RimPower ("림 세기" , float ) = 1
		_EmissionMap("Emission Map", 2D) = "white" {}
		[HDR] _EmissionColor("Emission Color", Color) = (0,0,0,0)
		//_Glossiness ("Smoothness", Range(0,1)) = 0.5
		//_Metallic ("Metallic", Range(0,1)) = 0.0
	}
	SubShader {
		Tags { "RenderType"="Opaque" }

		CGPROGRAM
		#pragma surface surf SWG

		sampler2D _MainTex;
		sampler2D _EmissionMap;

		struct Input {
			float2 uv_MainTex;
			float2 uv_EmissionMap;
			float3 viewDir;
		};

		float4 LightingSWG(SurfaceOutput s, float3 lightDir, float atten) {
			float NdotL = saturate(dot(s.Normal, lightDir)*0.5+0.5);
			float4 c;
			c.rgb = s.Albedo * _LightColor0.rgb * NdotL * atten;
			c.a = s.Alpha;
			return c;
		}

		//half _Glossiness;
		//half _Metallic;

		fixed4 _Color;
		fixed4 _EmissionColor;
		float4 _RimColor;
		float _RimPower;
			
		UNITY_INSTANCING_BUFFER_START(Props)
		UNITY_INSTANCING_BUFFER_END(Props)

		void surf (Input IN, inout SurfaceOutput o) {
			fixed4 c = tex2D (_MainTex, IN.uv_MainTex) * _Color;
			fixed4 e = tex2D(_EmissionMap, IN.uv_EmissionMap) * _EmissionColor;
			float rim = dot(normalize(IN.viewDir), o.Normal);
			rim = pow(1 - rim, _RimPower);
			o.Albedo = c.rgb + (rim * _RimColor.rgb);
			//o.Metallic = _Metallic;
			//o.Smoothness = _Glossiness;
			//o.Emission = rim * _RimColor.rgb;
			o.Emission = e.rgb;
			o.Alpha = c.a;
		}
		ENDCG
	}
	FallBack "Diffuse"
}
