
cbuffer PickCB : register(b0)
{
    int Pick;
    int ObjectID;
    float2 Padding;
}
   
uint mainPS() : SV_Target
{ 
    return ObjectID;
}