#include "Progress.h"
#include "LogDump.h"
#include "Surface.h"
#include "BuiltinType.h"
#include "FrameBuffer.h"
#include "GfxInternal.h"

Progress* g_Progress = nullptr;
ProgressBase* g_ProgressBase = nullptr;

UINT64 Progress::StartTime;

Progress::~Progress()
{
    MESSAGE_CLASS_DESTROYED(Progress);

    if (g_ProgressBase == this)
        g_ProgressBase = nullptr;

#ifdef INCLUDE_FIXES
    // NOTE: this is not in original code, who is responsible to delete texture?
    delete m_LoadBarTexture;
#endif
}

#pragma message(TODO_IMPLEMENTATION)
void Progress::UpdateProgress(float time, bool unk)
{
    LogDump::LogA("PROGRESS: %.0f%%\n", time * 100.f);

    float spriteSizeX = 0.f;

    if (m_LoadScreenSprite)
        spriteSizeX = m_LoadScreenSprite->m_SpriteSize_X;

    float spriteWidth = ((spriteSizeX - 1) * time) + 0.5f;
    if (m_LoadScreenSprite)
    {
        Vector4f loadSpritePosX;
        m_LoadScreenSprite->GetPos(loadSpritePosX);

        spriteWidth += loadSpritePosX.x;
    }

    if (unk || spriteWidth > m_LoadScreenSpriteResolution.x)
    {
        FrameBuffer fb(50, 4, 2);
        fb.Reset();

        if (m_LoadScreenSprite)
        {
            ScreenResolution screenResolution;
            g_GfxInternal->GetScreenResolution(screenResolution);

            /*fb.SubmitRenderTexturedQuad2D_3Command(
                m_LoadScreenSprite->m_Texture.GetAsset<Texture>(),
                topLeft,
                bottomLeft,
                topRight,
                bottomRight,
                unk1,
                unk2,
                unk3,
                unk4,
                BuiltinType::ColorWhite
            );*/
        }
    }
}

Progress::Progress() : ProgressBase(Timer::ClockGetCycles() / 5)
{
    MESSAGE_CLASS_CREATED(Progress);

    g_Progress = this;

    m_LoadScreenSprite = nullptr;
    m_Enabled = false;

    Surface* spsurf = new Surface(8, 8);

    for (unsigned int x = 0; x < 8; ++x)
        for (unsigned int y = 0; y < 8; ++y)
            spsurf->SetPixelColor(x, y, BuiltinType::ColorWhite);

    MutableTextureBuffer* spsurfmut = new MutableTextureBuffer(spsurf);
    m_LoadBarTexture = new Texture(spsurfmut);
    delete spsurfmut;
}

void Progress::Complete()
{
    field_2C = field_30;

    stub1("");
    UpdateProgress(field_2C, true);
    UpdateProgress(field_2C, true);

    LogDump::LogA("PROGRESS COMPLETE.\n");
}

void Progress::BeginPhase(uint32_t a1, uint64_t timeStart)
{
    if (field_20 + 1 < m_LoadBarPhases.size())
    {
        field_20++;
        field_28 = a1;
        field_2C = field_30;
        field_24 = NULL;
        field_30 += m_LoadBarPhases[field_20].m_Time / m_TotalTimeToLoad;

        stub1(m_LoadBarPhases[field_20].m_Status.m_Str);

        field_38 = m_TimeStart + timeStart;

        if (m_LoadBarPhases[field_20].field_18)
        {
            field_48 = m_LoadBarPhases[field_20].m_Time;
            field_50 = timeStart;
        }
        else
            field_48 = field_50 = NULL;
    }
}

void ProgressBase::Reset()
{
    LogDump::LogA("PROGRESS RESET.\n");

    m_TotalTimeToLoad = NULL;
    field_20 = -1;
    field_30 = 0.f;

    m_LoadBarPhases.clear();
}

void Progress::AddLoadbarPhase(const char* phaseName, UINT64 timeToLoad, bool unk)
{
    ProgressStateInfo stateinfo_(phaseName, timeToLoad, unk);
    m_LoadBarPhases.push_back(stateinfo_);
    m_TotalTimeToLoad += timeToLoad;
}

void Progress::Enable()
{
    g_ProgressBase = this;

    if (m_Enabled)
        return;

    LogDump::LogA("PROGRESS ENABLE.\n");

    if (m_LoadScreenSprite)
    {
        Vector4f spriteres;
        m_LoadScreenSprite->GetPos(spriteres);
        m_LoadScreenSpriteResolution.x = spriteres.x;
        m_LoadScreenSpriteResolution.y = spriteres.y;
    }
    else
        m_LoadScreenSpriteResolution = Vector2<float>();

    UpdateProgress(NULL, 1);
    UpdateProgress(NULL, 1);

    StartTime = __rdtsc();
    m_Enabled = true;
}

void Progress::Disable()
{
    if (!m_Enabled)
        return;

    LogDump::LogA("PROGRESS DISABLE. Loadtime: %d ms\n", (__rdtsc() - StartTime) / Timer::ClockGetCyclesMilliseconds());

    UpdateProgress(1.0, 1);
    UpdateProgress(1.0, 1);

    g_ProgressBase = nullptr;
    m_Enabled = false;
}

void Progress::SetLoadScreenSprite(Sprite* sprite)
{
    m_LoadScreenSprite = sprite;
}

void Progress::UpdateProgressTime(unsigned int unk, UINT64 time)
{
    field_24 += unk;
    if (time >= field_38 || !m_TimeStart)
    {
        float v1 = (float)(field_24 / field_28);
        float v2 = field_48 <= NULL ? 0.f : ((time - field_50) / field_48);

        if (v2 > v1)
            v1 = v2;
        if (v1 > 1.f)
            v1 = 1.f;

        UpdateProgress(((field_30 - field_2C) * v1) + field_2C, false);

        if (m_TimeStart > NULL && field_38 < time)
            do
            {
                field_38 += m_TimeStart;
            } while (field_38 < time);
    }
}

ProgressBase::~ProgressBase()
{
    MESSAGE_CLASS_DESTROYED(ProgressBase);

    if (g_ProgressBase == this)
        g_ProgressBase = nullptr;
}

void ProgressBase::stub1(const char*)
{
    return;
}

void ProgressBase::UpdateProgress(float time, bool unk)
{
    return;
}

ProgressBase::ProgressBase(UINT64 timeStart)
{
    MESSAGE_CLASS_CREATED(ProgressBase);

    m_TimeStart = timeStart;

    Reset();
}