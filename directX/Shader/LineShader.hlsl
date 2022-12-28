struct vertex
{
    float4 pos : POSITION0;   // 頂点の座標(射影座標系)
    float4 col : COLOR0;
};

struct pixel
{
    float4 pos : SV_POSITION;
    float4 col : COLOR1;
};

cbuffer ConstantBuffer
{
    float4x4 World;         //ワールド変換行列
    float4x4 View;          //ビュー変換行列
    float4x4 Projection;    //透視射影変換行列
}

//========================================
// 頂点シェーダー
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
// ピクセルシェーダー
//========================================
float4 PS(pixel In) : SV_Target0
{
    return float4(0, 0, 0, 1);
}