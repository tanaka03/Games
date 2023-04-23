float4x4 m_WVP;					// ワールド座標 * ビュー座標 * 射影座標
float4x4 m_WVPT;				// ワールド座標 * ビュー座標 * 射影座標 * テクスチャ座標

sampler tex0 : register(s0);	// メッシュのテクスチャ
sampler tex1 : register(s1);	// デプスバッファサーフェイスのテクスチャ

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Depth : TEXCOORD0;
};

struct VS1_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;		// テクセル
	float2 Depth : TEXCOORD1;
};

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

VS_OUTPUT VS(float4 Pos : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	// 頂点座標を射影座標系に変換
	Out.Pos = mul(Pos, m_WVP);

	// 射影座標系での深度値を計算
	Out.Depth.xy = Out.Pos.zw;

	return Out;
}

float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	// 深度値を使用して、ピクセルの色を計算
	Out = In.Depth.x / In.Depth.y;

	return Out;
}

VS1_OUTPUT VS1(float4 Pos     : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS1_OUTPUT Out;

	// 頂点座標を行列変換
	Out.Pos = mul(Pos, m_WVP);

	// テクセルを格納
	Out.Tex = Tex;

	// 射影座標系での深度値を計算
	Out.Depth.xy = Out.Pos.zw;

	return Out;
}

float4 PS1(VS1_OUTPUT In) : COLOR0
{
	float4 Out;

	// RGB成分にはZ値を出力
	Out.rgb = In.Depth.x / In.Depth.y;

	// A成分にはアルファブレンドの線形合成で使用するアルファ値を出力
	Out.a = tex2D(tex0, In.Tex).a;

return Out;
}

technique TShader
{
	//カラーキーを考慮しない
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}

	//カラーキーを考慮する
	pass P1
	{
		VertexShader = compile vs_1_1 VS1();
		PixelShader = compile ps_2_0 PS1();
	}
}
