#include "Bone.h"

EntityType* tBone;

std::map<int, short>    Bone::BonesList;
BoneRewindData         *Bone::BonePositionData;

Bone* Bone::Create(AllocatorIndex)
{
    return new Bone;
}

Bone::~Bone()
{
    MESSAGE_CLASS_DESTROYED(Bone);
}

void Bone::SetBoneWorldPos(float* args)
{
    Vector4f newpos;
    const Vector4f pos = { args[0], args[1], args[2], 0 };
    
    m_Parent->ConvertFromWorldSpace(newpos, pos);
    SetPos(newpos);
}

void Bone::SetBonePos(float* args)
{
    SetPos({ args[0], args[1], args[2], 0 });
}

void Bone::SetBoneWorldOrient(float* args)
{
    SetWorldOrient({ args[0], args[1], args[2], args[3] });
}

void Bone::SetBoneOrient(float* args)
{
    SetOrient({ args[0], args[1], args[2], args[3] });
}

void Bone::Register()
{
    tBone = new EntityType("Bone");
    tBone->InheritFrom(tNode);
    tBone->SetCreator((CREATOR)Create);

    tBone->RegisterScript("setboneworldpos(vector)", (EntityFunctionMember)&SetBoneWorldPos, NULL, NULL, NULL, nullptr, "SetBoneWorldPosMSG");
    tBone->RegisterScript("setboneworldorient(quaternion)", (EntityFunctionMember)&SetBoneWorldOrient, NULL, NULL, NULL, nullptr, "SetBoneWorldOrientMSG");
    tBone->RegisterScript("setboneorient(quaternion)", (EntityFunctionMember)&SetBoneOrient, NULL, NULL, NULL, nullptr, "SetBoneOrientMSG");
    tBone->RegisterScript("setbonepos(vector)", (EntityFunctionMember)&SetBonePos, NULL, NULL, NULL, nullptr, "SetBonePosMSG");

    tBone->PropagateProperties();
}