#define PICKING_CBUFFER b2
   
cbuffer PickCB : register(PICKING_CBUFFER)
{
    int Pick;
    int ObjectID;
    int2 Padding;
}
uint mainPS() : SV_Target
{ 
    return ObjectID;
}