cbuffer PickCB : register(b0)
{
    uint ObjectID;
    uint3 Padding;
}
   
uint mainPS() : SV_Target
{
    // R32_UINT�� ���� Ÿ�� ���ε� ��, PS ��ȯ���� uint (����)��
    return ObjectID;
}