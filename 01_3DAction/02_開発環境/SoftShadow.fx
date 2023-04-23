float4x4 m_WVP;					// ワールド座標 * ビュー座標 * 射影座標
float4x4 m_WVPT;				// ワールド座標 * ビュー座標 * 射影座標 * テクスチャ座標
float4x4 m_LWVP;				// ライトの行列変換
float4x4 m_LWVPT;				// ライトの行列をテクスチャ座標に変換

float m_bias = 0.0f;			// Z値の比較による誤差を補正
float m_shadowColor = 0.1f;		// 影によるメッシュカラーの減算値

float4 m_lightDir;				// 平行光源の方向ベクトル
float4 m_ambient = 0.0f;		// アンビエント

sampler tex0 : register(s0);	// オブジェクトのテクスチャ
sampler tex1 : register(s1);	// Pass0 : Zバッファテクスチャ	Pass1 : 影イメージテクスチャ

// 影イメージ作成
struct VS1_OUTPUT
{
	float4 Pos : POSITION;
	float4 LightUV : TEXCORRD0;
	float4 Depth : TEXCOORD1;
};

// 影を適用
struct VS2_OUTPUT
{
	float4 Pos : POSITION;
	float4 Col : COLOR0;
	float2 Tex : TEXCOORD0;
	float4 WVPTPos : TEXCOORD1;
};

float4 main(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

VS1_OUTPUT VertexScene( float4 Pos : POSITION,
						float4 Normal : NORMAL,
						float2 Tex : TEXCOORD0)
{
	VS1_OUTPUT Out;

	Out.Pos = mul(Pos, m_WVP);

	// Zバッファの深度を取得するためにテクセル座標を設定
	Out.LightUV = mul(Pos, m_LWVPT);

	// ライトの行列変換により、深度値を計算
	Out.Depth.xy = mul(Pos, m_LWVP).zw;

	return Out;
}

float4 PixelScene( VS1_OUTPUT In ) : COLOR0
{
	float4 Out = (float4)1;		// 白

	// Zバッファから深度値を取得
	float depth = tex2Dproj(tex1, In.LightUV).r;

	// 影の色を出力
	if (depth * In.Depth.y < In.Depth.x - m_bias)	Out = m_shadowColor;

	return Out;
}

VS2_OUTPUT VertexAdaptation(float4 Pos : POSITION,
							float4 Normal : NORMAL,
							float2 Tex : TEXCOORD0)
{
	VS2_OUTPUT Out;

	Out.Pos = mul(Pos, m_WVP);
	Out.Tex = Tex;

	// ランバート拡散照明
	float3 L = -m_lightDir.xyz;
	float3 N = normalize(Normal.xyz);
	Out.Col = max(m_ambient, dot(N, L));

	// テクスチャー座標系に行列変換
	Out.WVPTPos = mul(Pos, m_WVPT);

	return Out;
}

float4 PixelAdaptation(VS2_OUTPUT In) : COLOR0
{
	float4 Out = (float4)0;

	// 影イメージテクスチャから影情報を取得
	float s = tex2Dproj(tex1, In.WVPTPos).r;

	// 影の色を補正
	s = max(m_shadowColor, s * s);

	// 陰と影を滑らかにするために暗い方を適応
	Out = tex2D(tex0, In.Tex) * min((In.Col.r + In.Col.g + In.Col.b) * 0.3333f, s);

	return Out;
}

technique RenderSoftShadow
{
	// 影イメージを作成
	pass P0
	{
		VertexShader = compile vs_1_1 VertexScene();
		PixelShader = compile ps_2_0 PixelScene();
	}

	// 影を適応
	pass P1
	{
		VertexShader = compile vs_1_1 VertexAdaptation();
		PixelShader = compile ps_2_0 PixelAdaptation();
	}
};