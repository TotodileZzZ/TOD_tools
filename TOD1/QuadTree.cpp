#include "QuadTree.h"
#include "Scene.h"

QuadTreeInfo* QuadTreeInfo::Instance;
uint32_t QuadTree::TreesCreated;

QuadTree::QuadTree(const uint32_t nodes, const uint32_t a2)
{
    if (!QuadTreeInfo::Instance)
    {
        QuadTreeInfo::Instance = new QuadTreeInfo();
        QuadTreeInfo::Instance->field_8 = (uint8_t*)MemoryManager::AllocatorsList[DEFAULT]->AllocateAligned(0x8000, 64, __FILE__, __LINE__);
        QuadTreeInfo::Instance->field_4 = (uint8_t*)MemoryManager::AllocatorsList[SCRATCHPAD]->AllocateAligned(256, 16, __FILE__, __LINE__);
    }

    LeafsTotal = nodes * 2;
    field_8 = a2;
    field_C = (int32_t)(Math::RoundWeird((float)a2) / Math::RoundWeird(2.f));
    field_10 = (int32_t)(Math::RoundWeird((float)(nodes / a2)) / Math::RoundWeird(2.f) + 1.0);

    TreesCreated++;

    field_0 = _89A3E0();

    Scene::QuadTreeNode& kdtreeNode = Scene::MainQuadTreeNodes[field_0];
    kdtreeNode.field_1B &= 252 | 2;
    kdtreeNode.field_18 = -1;
    kdtreeNode.field_1A = 0;

    for (uint32_t i = 0; i < 4; ++i)
    {
        kdtreeNode.field_0[i] = -1;
        kdtreeNode.field_8[i] = 0;
    }

    NoFreeNodes = false;

    QuadTreeInfo::Instance->field_24 = 0;
    QuadTreeInfo::Instance->field_20 = -1;
}

int16_t QuadTree::_89A3E0()
{
    if (Scene::_A120E8 == -1)
    {
        if (!NoFreeNodes)
        {
            LogDump::LogA("\n\n\t*** WARNING: QuadTree ran out of nodes (%d nodes allocated)! ***\n\n\n", Scene::QuadTreeNodesAllocated);
            NoFreeNodes = true;
        }

        return -1;
    }
    else
    {
        Scene::_A120E8 = Scene::MainQuadTreeNodes[Scene::_A120E8].field_0[0];
        return Scene::_A120E8;
    }
}

Node* QuadTree::GetFirstNode() const
{
    const uint32_t depth = clamp(QuadTreeInfo::Instance->field_30, 0, 64);
    if (!depth)
    {
        QuadTreeInfo::Instance->field_0 = 0;
        QuadTreeInfo::Instance->field_20 = -1;
        QuadTreeInfo::Instance->field_24 = 0;

        return nullptr;
    }

    QuadTreeInfo::Instance->field_2C = -1;
    QuadTreeInfo::Instance->field_28++;
    QuadTreeInfo::Instance->field_38 = 1;

    uint8_t* oldRef = QuadTreeInfo::Instance->field_4;
    if (QuadTreeInfo::Instance->field_30 > 64)
        memcpy(QuadTreeInfo::Instance->field_4, QuadTreeInfo::Instance->field_8, 4 * depth);

    QuadTreeInfo::Instance->field_0 = oldRef;

    return GetNextNode(nullptr);
}

Node* QuadTree::GetNextNode(const Node* node) const
{
    return nullptr;
}

QuadTreeInfo::QuadTreeInfo()
{
    field_C = 0.f;
    field_10 = 0.f;
    field_14 = 0.f;
    field_0 = 0;
    field_4 = 0;
    field_18 = 0.f;
    field_1C = 0.f;
    field_20 = -1;
    field_24 = 0;
    field_28 = 0;
    field_30 = 0;
    field_34 = 0;
    field_38 = 0;
    field_3C = 0;
    field_40 = 0;
    field_44 = 0;
    field_48 = 0;
    field_4C = 0;
    field_50 = 0;
    field_54 = 0;
    field_58 = 0;
}

const uint8_t QuadTreeNode::SetLodLevel(const Vector4f&, const uint32_t factor)
{
    const double lodDistanceSqrt = sqrt((double)((uint32_t)LodDistance));
    const uint32_t lodThresholdAdjusted = (uint32_t)lodDistanceSqrt * 64 * LodThreshold;
    const uint32_t lodFactorAdjusted = (uint32_t)(float)((float)(factor << 12) * Script::LodFactor);

    Lod = 0;
    if (lodFactorAdjusted < lodThresholdAdjusted)
    {
        Lod = 1;
        if (lodFactorAdjusted < (lodThresholdAdjusted / 4))
            Lod = 2;
    }

    const uint32_t lodFadeAdjusted = 64 * (FadeThreshold & 127) * ((uint32_t)lodDistanceSqrt - Script::MinFadeDist);
    const uint32_t lodFadeFactorAdjusted = (uint32_t)(float)((float)(factor << 11) * Script::LodFactor);
    const uint32_t lodFadeThresholdAdjusted = lodFadeAdjusted - (lodFadeAdjusted >> (2 - (FadeThreshold >> 7)));

    LodFade = -1;
    if (lodFadeFactorAdjusted < lodFadeAdjusted)
    {
        if (lodFadeFactorAdjusted >= lodFadeThresholdAdjusted)
        {
            LodFade = (1.0 - (double)(lodFadeAdjusted - lodFadeFactorAdjusted) / (double)(lodFadeAdjusted - lodFadeThresholdAdjusted)) * 255.0;
            return Lod;
        }

        LodFade = 0;
        Lod = 6;
    }

    return Lod;
}

void QuadTreeNode::UpdateSiblings()
{
    if (Parent->FirstSibling == this)
    {
        Parent->FirstSibling = NextSibling;
        Parent = nullptr;
    }
    else
    {
        auto firstSibling = Parent->FirstSibling;
        auto nextSibling = firstSibling->NextSibling;
        if (nextSibling)
        {
            while (nextSibling != this)
            {
                firstSibling = nextSibling;
                nextSibling = nextSibling->NextSibling;
                if (!nextSibling)
                    return;
            }

            firstSibling->NextSibling = nextSibling->NextSibling;
            Parent = nullptr;
        }
    }
}