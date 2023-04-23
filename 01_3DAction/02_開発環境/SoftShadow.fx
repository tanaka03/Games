float4x4 m_WVP;					// ���[���h���W * �r���[���W * �ˉe���W
float4x4 m_WVPT;				// ���[���h���W * �r���[���W * �ˉe���W * �e�N�X�`�����W
float4x4 m_LWVP;				// ���C�g�̍s��ϊ�
float4x4 m_LWVPT;				// ���C�g�̍s����e�N�X�`�����W�ɕϊ�

float m_bias = 0.0f;			// Z�l�̔�r�ɂ��덷��␳
float m_shadowColor = 0.1f;		// �e�ɂ�郁�b�V���J���[�̌��Z�l

float4 m_lightDir;				// ���s�����̕����x�N�g��
float4 m_ambient = 0.0f;		// �A���r�G���g

sampler tex0 : register(s0);	// �I�u�W�F�N�g�̃e�N�X�`��
sampler tex1 : register(s1);	// Pass0 : Z�o�b�t�@�e�N�X�`��	Pass1 : �e�C���[�W�e�N�X�`��

// �e�C���[�W�쐬
struct VS1_OUTPUT
{
	float4 Pos : POSITION;
	float4 LightUV : TEXCORRD0;
	float4 Depth : TEXCOORD1;
};

// �e��K�p
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

	// Z�o�b�t�@�̐[�x���擾���邽�߂Ƀe�N�Z�����W��ݒ�
	Out.LightUV = mul(Pos, m_LWVPT);

	// ���C�g�̍s��ϊ��ɂ��A�[�x�l���v�Z
	Out.Depth.xy = mul(Pos, m_LWVP).zw;

	return Out;
}

float4 PixelScene( VS1_OUTPUT In ) : COLOR0
{
	float4 Out = (float4)1;		// ��

	// Z�o�b�t�@����[�x�l���擾
	float depth = tex2Dproj(tex1, In.LightUV).r;

	// �e�̐F���o��
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

	// �����o�[�g�g�U�Ɩ�
	float3 L = -m_lightDir.xyz;
	float3 N = normalize(Normal.xyz);
	Out.Col = max(m_ambient, dot(N, L));

	// �e�N�X�`���[���W�n�ɍs��ϊ�
	Out.WVPTPos = mul(Pos, m_WVPT);

	return Out;
}

float4 PixelAdaptation(VS2_OUTPUT In) : COLOR0
{
	float4 Out = (float4)0;

	// �e�C���[�W�e�N�X�`������e�����擾
	float s = tex2Dproj(tex1, In.WVPTPos).r;

	// �e�̐F��␳
	s = max(m_shadowColor, s * s);

	// �A�Ɖe�����炩�ɂ��邽�߂ɈÂ�����K��
	Out = tex2D(tex0, In.Tex) * min((In.Col.r + In.Col.g + In.Col.b) * 0.3333f, s);

	return Out;
}

technique RenderSoftShadow
{
	// �e�C���[�W���쐬
	pass P0
	{
		VertexShader = compile vs_1_1 VertexScene();
		PixelShader = compile ps_2_0 PixelScene();
	}

	// �e��K��
	pass P1
	{
		VertexShader = compile vs_1_1 VertexAdaptation();
		PixelShader = compile ps_2_0 PixelAdaptation();
	}
};