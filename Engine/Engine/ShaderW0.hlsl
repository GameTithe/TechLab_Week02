
#define PICKING_CBUFFER b2
   
cbuffer PickCB : register(PICKING_CBUFFER)
{
    int Pick;
    int ObjectID;
    int2 Padding;
}
cbuffer TransformCBuffer : register(b0)
{
    float4x4 Model;
}

cbuffer CommonCBUffer : register(b1)
{
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
    output.position = mul(Model, input.position);
    output.position = mul(View, output.position);
    output.position = mul(Perspective, output.position);
    output.color = input.color; 
    
    return output;
}


float4 mainPS(PS_INPUT input) : SV_Target
{
    float4 color = input.color; 
    
    if(Pick == ObjectID)
        color = (color + float4(0.2, 0.2, 0.2, 1.0f) * float4(1.5, 1.5, 1.5, 1.0f));
    
    return color;
}
