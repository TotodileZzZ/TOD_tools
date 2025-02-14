#include "CutsceneAsset.h"
#include "Platform.h"

AssetInstance* CutsceneAsset::Instance;

CutsceneAsset::CutsceneAsset() : Asset(false)
{
    MESSAGE_CLASS_CREATED(CutsceneAsset);

    field_40 = 1;
    field_44 = 30;
    field_48 = 1;
}

CutsceneAsset::~CutsceneAsset()
{
    MESSAGE_CLASS_DESTROYED(CutsceneAsset);
}

AssetInstance* CutsceneAsset::GetInstancePtr() const
{
    return Instance;
}

void CutsceneAsset::CreateInstance()
{
    Instance = new AssetInstance("cutscene", (CREATOR)Create);

    Instance->m_FileExtensions.push_back("cutscene");
    Instance->SetAlignment(16, 1);
    Instance->SetAlignment(16, 2);
    Instance->SetAlignment(16, 0);
}

CutsceneAsset* CutsceneAsset::Create()
{
    return new CutsceneAsset;
}