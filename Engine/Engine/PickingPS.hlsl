cbuffer PickCB : register(b0)
{
    uint ObjectID;
    uint3 Padding;
}
   
uint mainPS() : SV_Target
{
    // R32_UINT로 렌더 타깃 바인딩 시, PS 반환형도 uint (정수)로
    return ObjectID;
}