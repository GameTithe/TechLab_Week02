cbuffer constants : register(b0)
{
    float3 Offset;
    float Scale;
    int Pick;
    float Padding; 
}

cbuffer MVPTransform : register(b1)
{
    float4x4 Model;
    float4x4 View;
    float4x4 Perspective;
}
 
struct VS_INPUT
{
    float4 position : POSITION;    // input position
    float4 color : COLOR;           // input color 
};

struct PS_INPUT
{
    float4 position : SV_POSITION; // Transformed position
    float4 color : COLOR;
};

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    //output.position = input.position * float4(Scale, Scale, Scale,1) + float4(Offset, 0);
    output.position = mul(Model, input.position);
    output.position = mul(View, output.position);
    output.position = mul(Perspective, output.position);
    output.color = input.color; 
    
    return output;
}


float4 mainPS(PS_INPUT input) : SV_Target
{
    float4 color = input.color;
    if (Pick)
        color * 1.5;
    
    return color;
}
