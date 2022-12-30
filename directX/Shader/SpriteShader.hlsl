struct vertex
{
    float4 pos : POSITION0;   // ���_�̍��W(�ˉe���W�n)
    float4 col : COLOR0;
    float4 nor : NORMAL0;
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
    float4   Light;
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
// �������݂̒��_�V�F�[�_�[
//========================================
pixel LVS(vertex In)
{
    pixel Out;

    Out.pos = mul(In.pos, World);
    Out.pos = mul(Out.pos, View);
    Out.pos = mul(Out.pos, Projection);
    
    float3 nor;
    nor = -1.0f * mul(In.nor, World).xyz;
    nor = normalize(nor);

    float  lightPower;
    lightPower = saturate(dot(nor, (float3)Light));
    lightPower = lightPower * 0.5f + 0.5f;
    Out.col = lightPower * In.col;

    return Out;
}

//========================================
// �s�N�Z���V�F�[�_�[
//========================================
float4 PS(pixel In) : SV_Target0
{
    //return float4(0, 1, 0, 1);
    return In.col;
}