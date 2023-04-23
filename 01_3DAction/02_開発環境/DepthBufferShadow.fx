float4x4 m_WVP;										// ���[���h���W�n �~ �r���[(�J�����)���W�n �~ ���ˉe���W�n
float4x4 m_LWVP;									// ���[���h���W�n �~ �r���[(���C�g�)���W�n �~ ���ˉe���W�n
float4x4 m_LWVPT;									// ���[���h���W�n �~ �r���[(���C�g�)���W�n �~ ���ˉe���W�n �~ �e�N�X�`���[���W�n

float m_Bias = 0.0f;								// Z�l�̔�r�ɂ��덷��␳����
float m_ShadowColor = 0.1f;							// �e�ɂ�郁�b�V���̃J���[�̌��Z�l

float4 m_matDiffuse = float4(1.0f,1.0f,1.0f,1.0f);	// �}�e���A���̃f�B�t���[�Y�����l
float4 m_LightDir;									// ���C�g�̕���
float4 m_Ambient = 0.0f;							// �A���r�G���g�l

sampler tex0 : register(s0);						// �I�u�W�F�N�g�̃e�N�X�`���[
sampler tex1 : register(s1);						// �f�v�X�o�b�t�@�T�[�t�F�C�X�̃e�N�X�`���[

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float4 Col : COLOR0;
	float2 Tex : TEXCOORD0;
	float2 Depth : TEXCOORD1;						//���ˉe���W�n �ɕϊ��������_���W
	float4 LightUV : TEXCOORD2;						//�e�N�X�`���[���W�n�ɕϊ��������_���W
};

float4 main(float4 pos : POSITION) : SV_POSITION
{
	return pos;
}

//��������������������������������������������������������������
// �f�v�X�o�b�t�@�V���h�E��VertexShader
//��������������������������������������������������������������
VS_OUTPUT VS(float4 Pos     : POSITION,
	float4 Normal : NORMAL,
	float2 Tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	// ���_���W���ˉe���W�n�ɕϊ�
	Out.Pos = mul(Pos, m_WVP);

	// �e�N�X�`�����W���o��
	Out.Tex = Tex;

	// �����o�[�g�g�U�Ɩ��̌����̕����ƒ��_�̖@���̓��ς��v�Z���A������Ɩ��̋��x�i���b�V���̐F���j�Ƃ��Ďg�p
	float3 L = -m_LightDir.xyz;
	float3 N = normalize(Normal.xyz);
	Out.Col = max(m_Ambient, dot(L, N));

	// ���ˉe���W�n�ɕϊ�����Z�l���v�Z
	Out.Depth.xy = mul(Pos, m_LWVP).zw;

	// �e�N�X�`�����W�n�ɕϊ��������_���W���v�Z
	Out.LightUV = mul(Pos, m_LWVPT);

	return Out;
}

//��������������������������������������������������������������
// �f�v�X�o�b�t�@�V���h�E��PixelShader
//��������������������������������������������������������������
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out = m_matDiffuse;
	float4 Tex = tex2D(tex0, In.Tex);

	// �e�N�X�`�����|�����킹��
	Out *= (Tex.x > 0.0f && Tex.y > 0.0f && Tex.z > 0.0f) ? Tex : float4(1.0f, 1.0f, 1.0f, 1.0f);

	// �V���h�E�J���[���v�Z
	float d = tex2Dproj(tex1, In.LightUV).r;
	float depth = In.Depth.x - m_Bias;
	float shadowValue = (d * In.Depth.y < depth) ? min(dot(In.Col.rgb, float3(0.3333f, 0.3333f, 0.3333f)), m_ShadowColor) : 1.0f;
	float3 ShadowColor = In.Col.rgb * shadowValue;

	// �o�͐F�����߂�
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