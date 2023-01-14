
struct vertex
{
    float4 pos : POSITION0;   // 頂点の座標(射影座標系)
    float4 col : COLOR0;
    float4 nor : NORMAL0;
};

struct pixel
{
    float4 pos : SV_POSITION;
    float4 ShadowMapTex : TEXCOORD0;   // Zバッファテクスチャ
};

cbuffer ConstantBuffer
{
    float4x4 World;         //ワールド変換行列
    float4x4 View;          //ビュー変換行列
    float4x4 Projection;    //透視射影変換行列
    float4   Light;
}

// 頂点シェーダ
pixel ZVS(vertex In)
{
    pixel Out;

    Out.pos = mul(In.pos, World);
    Out.pos = mul(Out.pos, View);
    Out.pos = mul(Out.pos, Projection);

	// テクスチャ座標を頂点に合わせる
	Out.ShadowMapTex = Out.Pos;

	return Out;
}


// ピクセルシェーダ
float4 ZPS(float4 ShadowMapTex : TEXCOORD0) : COLOR
{
	// Z値算出
	return float4(ShadowMapTex.z / ShadowMapTex.w, 0, 0 1);
}