
cbuffer PickCB : register(b0)
{
    int Pick;
    int ObjectID;
    int2 Padding;
}
   
uint mainPS() : SV_Target
{ 
    return ObjectID;
}