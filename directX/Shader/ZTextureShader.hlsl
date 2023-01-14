
struct vertex
{
    float4 pos : POSITION0;   // ���_�̍��W(�ˉe���W�n)
    float4 col : COLOR0;
    float4 nor : NORMAL0;
};

struct pixel
{
    float4 pos : SV_POSITION;
    float4 ShadowMapTex : TEXCOORD0;   // Z�o�b�t�@�e�N�X�`��
};

cbuffer ConstantBuffer
{
    float4x4 World;         //���[���h�ϊ��s��
    float4x4 View;          //�r���[�ϊ��s��
    float4x4 Projection;    //�����ˉe�ϊ��s��
    float4   Light;
}

// ���_�V�F�[�_
pixel ZVS(vertex In)
{
    pixel Out;

    Out.pos = mul(In.pos, World);
    Out.pos = mul(Out.pos, View);
    Out.pos = mul(Out.pos, Projection);

	// �e�N�X�`�����W�𒸓_�ɍ��킹��
	Out.ShadowMapTex = Out.Pos;

	return Out;
}


// �s�N�Z���V�F�[�_
float4 ZPS(float4 ShadowMapTex : TEXCOORD0) : COLOR
{
	// Z�l�Z�o
	return float4(ShadowMapTex.z / ShadowMapTex.w, 0, 0 1);
}