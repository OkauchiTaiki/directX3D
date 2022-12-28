struct vertex
{
    float4 pos : POSITION0;   // ���_�̍��W(�ˉe���W�n)
    float4 col : COLOR0;
};

struct pixel
{
    float4 pos : SV_POSITION;
    float4 col : COLOR1;
};

cbuffer ConstantBuffer
{
    float4x4 World;         //���[���h�ϊ��s��
    float4x4 View;          //�r���[�ϊ��s��
    float4x4 Projection;    //�����ˉe�ϊ��s��
}

//========================================
// ���_�V�F�[�_�[
//========================================
pixel VS(vertex In)
{
    pixel Out;
    Out.pos = mul(In.pos, World);
    Out.pos = mul(Out.pos, View);
    Out.pos = mul(Out.pos, Projection);
    Out.col = In.col;
    return Out;
}

//========================================
// �s�N�Z���V�F�[�_�[
//========================================
float4 PS(pixel In) : SV_Target0
{
    return float4(0, 0, 0, 1);
}