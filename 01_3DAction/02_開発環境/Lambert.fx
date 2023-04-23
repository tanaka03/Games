float4x4 m_WVP;					// ���[���h���W * �r���[���W * �ˉe���W
float4x4 m_WVPT;				// ���[���h���W * �r���[���W * �ˉe���W * �e�N�X�`�����W

sampler tex0 : register(s0);	// ���b�V���̃e�N�X�`��
sampler tex1 : register(s1);	// �f�v�X�o�b�t�@�T�[�t�F�C�X�̃e�N�X�`��

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Depth : TEXCOORD0;
};

struct VS1_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;		// �e�N�Z��
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

	// ���_���W���ˉe���W�n�ɕϊ�
	Out.Pos = mul(Pos, m_WVP);

	// �ˉe���W�n�ł̐[�x�l���v�Z
	Out.Depth.xy = Out.Pos.zw;

	return Out;
}

float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	// �[�x�l���g�p���āA�s�N�Z���̐F���v�Z
	Out = In.Depth.x / In.Depth.y;

	return Out;
}

VS1_OUTPUT VS1(float4 Pos     : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS1_OUTPUT Out;

	// ���_���W���s��ϊ�
	Out.Pos = mul(Pos, m_WVP);

	// �e�N�Z�����i�[
	Out.Tex = Tex;

	// �ˉe���W�n�ł̐[�x�l���v�Z
	Out.Depth.xy = Out.Pos.zw;

	return Out;
}

float4 PS1(VS1_OUTPUT In) : COLOR0
{
	float4 Out;

	// RGB�����ɂ�Z�l���o��
	Out.rgb = In.Depth.x / In.Depth.y;

	// A�����ɂ̓A���t�@�u�����h�̐��`�����Ŏg�p����A���t�@�l���o��
	Out.a = tex2D(tex0, In.Tex).a;

return Out;
}

technique TShader
{
	//�J���[�L�[���l�����Ȃ�
	pass P0
	{
		VertexShader = compile vs_1_1 VS();
		PixelShader = compile ps_2_0 PS();
	}

	//�J���[�L�[���l������
	pass P1
	{
		VertexShader = compile vs_1_1 VS1();
		PixelShader = compile ps_2_0 PS1();
	}
}
