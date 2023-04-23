float4x4 m_WVP;										// ワールド座標系 × ビュー(カメラ基準)座標系 × 正射影座標系
float4x4 m_LWVP;									// ワールド座標系 × ビュー(ライト基準)座標系 × 正射影座標系
float4x4 m_LWVPT;									// ワールド座標系 × ビュー(ライト基準)座標系 × 正射影座標系 × テクスチャー座標系

float m_Bias = 0.0f;								// Z値の比較による誤差を補正する
float m_ShadowColor = 0.1f;							// 影によるメッシュのカラーの減算値

float4 m_matDiffuse = float4(1.0f,1.0f,1.0f,1.0f);	// マテリアルのディフューズ初期値
float4 m_LightDir;									// ライトの方向
float4 m_Ambient = 0.0f;							// アンビエント値

sampler tex0 : register(s0);						// オブジェクトのテクスチャー
sampler tex1 : register(s1);						// デプスバッファサーフェイスのテクスチャー

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Col : COLOR0;
	float2 Tex : TEXCOORD0;
	float2 Depth : TEXCOORD1;						//正射影座標系 に変換した頂点座標
	float4 LightUV : TEXCOORD2;						//テクスチャー座標系に変換した頂点座標
};

float4 main(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウのVertexShader
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
VS_OUTPUT VS(float4 Pos     : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	// 頂点座標を射影座標系に変換
	Out.Pos = mul(Pos, m_WVP);

	// テクスチャ座標を出力
	Out.Tex = Tex;

	// ランバート拡散照明の光源の方向と頂点の法線の内積を計算し、それを照明の強度（メッシュの色情報）として使用
	float3 L = -m_LightDir.xyz;
	float3 N = normalize(Normal.xyz);
	Out.Col = max(m_Ambient, dot(L, N));

	// 正射影座標系に変換したZ値を計算
	Out.Depth.xy = mul(Pos, m_LWVP).zw;

	// テクスチャ座標系に変換した頂点座標を計算
	Out.LightUV = mul(Pos, m_LWVPT);

	return Out;
}

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// デプスバッファシャドウのPixelShader
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out = m_matDiffuse;
	float4 Tex = tex2D(tex0, In.Tex);

	// テクスチャを掛け合わせる
	Out *= (Tex.x > 0.0f && Tex.y > 0.0f && Tex.z > 0.0f) ? Tex : float4(1.0f, 1.0f, 1.0f, 1.0f);

	// シャドウカラーを計算
	float d = tex2Dproj(tex1, In.LightUV).r;
	float depth = In.Depth.x - m_Bias;
	float shadowValue = (d * In.Depth.y < depth) ? min(dot(In.Col.rgb, float3(0.3333f, 0.3333f, 0.3333f)), m_ShadowColor) : 1.0f;
	float3 ShadowColor = In.Col.rgb * shadowValue;

	// 出力色を求める
	Out.rgb *= ShadowColor;
	return Out;
}

technique TShader
{
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}
}