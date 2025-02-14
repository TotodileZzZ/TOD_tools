#pragma once
#include "Globals.h"
#include "MemoryManager.h"

#define AUDIO_DIESELPO_CLASS_SIZE 40
#define AUDIO_DIESELPO_DLL_NAME "DieselPowerImplementation.dll"
//#define AUDIO_DIESELPO_DLL_SUPPORTED_VERSION "DieselPower Level One, v.1.2.10."
#define AUDIO_DIESELPO_DLL_SUPPORTED_VERSION "v.1.2.10." // NOTE: this has been altered to use new detection method.

enum DieselPowerErrorCode
{
    ERROR_CANT_ACQUIRE_FACTORY = -8,
    ERROR_DLL_CANT_BE_FOUND = -11,
    ERROR_SUCCESSFULLY_ACQUIRED = 0,
    ERROR_VERSIONS_MISMATCH = -14,
    ERROR_VERSIONS_HIGHER = -12,
    ERROR_VERSION_LOWER = -13,
    ERROR_DLL_NOT_LOADED = -3,
    ERROR_RELEASE_POINTERS_MISMATCH = -9,
    ERROR_PROBLEM_RELEASING_DLL = -8,
    ERROR_PROBLEM_RELEASING_INSTANCE = -1
};

static const char* DieselPowerErrorStrings[] =
{
 "Error loading DieselPowerImplementation.dll - file not found.",
 "DieselPower succesfully loaded, created and initialized.",
 "The DieselPower Level One DLL has a LOWER INTERFACE version!",
 "The DieselPower Level One DLL has a HIGHER INTERFACE version!",
 "The found DieselPower DLL has a different LEVEL version!",
 "DieselPower DLL version successfully acquired.",
 "Error getting the factory function from DieselPowerImplementation.dll",

 "Invalid pointer specified: Mismatch between the given pointer and the DieselPower mother object pointer.",
 "NULL pointer specified!",
 "Unloaded the DieselPower Level One DLL succesfully.",
 "Problem releasing the DieselPower Level One DLL",
 "DieselPower Level One DLL is not loaded."
};

typedef class DieselPower* (CALLBACK* DIESELPOWERCREATEPROC)(int, int, int, float, HWND, int, int, int, char*);

class DieselPower
{
private:
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;

    static bool CheckDllVersion(); // @940F30

public:
    // TODO: complete these methods. There are 69 of them. Nice.
    virtual void stub1() {};
    virtual void stub2(const float, const float, const float, const float, const float, const float) {};    //  NOTE: It's used in 'SetListener3DOrientation' method.
    virtual char* GetSoundBufferPtr() const { return nullptr; };
    virtual void stub4() {};
    virtual void stub5() {};
    virtual void IsLooped() {};
    virtual void stub7() {};
    virtual void stub8() {};
    virtual int stub9() { return NULL; };
    virtual void stub10() {};
    virtual void stub11() {};
    virtual void stub12() {};
    virtual void stub13() {};
    virtual void stub14() {};
    virtual void SetFrequency(const float_t frequency) {};
    virtual int* stub16(DWORD, signed int, LPWAVEFORMATEX*) { return nullptr; };
    virtual void SetPan(const float_t pan) {};
    virtual void stub18() {};
    virtual void stub19() {};
    virtual const float_t GetFrequency() const { return 0.f; };
    virtual const float_t GetVolume() { return 0.f; };
    virtual const float_t GetPan() { return 0.f; };
    virtual int* stub23() { return nullptr; };
    virtual int* stub24() { return nullptr; };
    virtual void stub25(signed int) {};
    virtual void stub26(signed int) {};
    virtual void stub27() {};
    virtual void stub28() {};
    virtual void stub29() {};
    virtual void stub30() {};
    virtual void stub31() {};
    virtual void stub32() {};
    virtual void stub33() {};
    virtual void stub34() {};
    virtual void stub35() {};
    virtual const char* GetSystemName() { return nullptr; };
    virtual IDirectSound* GetDirectSound() { return nullptr; };
    virtual void stub38() {};
    virtual void Release() {};
    virtual void stub40() {};
    virtual void stub41() {};
    virtual void stub42() {};
    virtual void stub43() {};
    virtual void stub44() {};
    virtual void stub45() {};
    virtual void SetAudioEnvironmentParams(const float_t mindistance, const float_t maxdistance, const float_t rolloff) {};
    virtual float_t GetMinDistance() const { return 0.f; };
    virtual float_t GetMaxDistance() const { return 0.f; };
    virtual float_t GetRollOff() { return 0.f; };
    virtual void SetPosition(const float_t x, const float_t y, const float_t z) {};
    virtual void SetVelocity(const float_t x, const float_t y, const float_t z) {};
    virtual void stub52() {};
    virtual void stub53() {};
    virtual void stub54() {};
    virtual void SetDopplerFactor(const float_t factor) {};
    virtual void GetPosition(float& x, float& y, float& z) {};
    virtual void stub57() {};
    virtual void stub58() {};
    virtual void stub59() {};
    virtual void stub60() {};
    virtual void stub61() {};
    virtual void stub62() {};
    virtual void stub63() {};
    virtual void stub64() {};
    virtual void stub65() {};
    virtual void stub66() {};
    virtual void stub67() {};
    virtual void stub68() {};
    virtual void stub69() {};

    DieselPower();
    ~DieselPower();

    void* operator new (size_t size)
    {
        return MemoryManager::AllocatorsList[DEFAULT]->Allocate(size, __FILE__, __LINE__);
    }
    void operator delete(void* ptr)
    {
        if (ptr)
            MemoryManager::ReleaseMemory(ptr, 0);
        ptr = nullptr;
    }

    static DieselPower* CallFactory(unsigned int versionMajor, unsigned int versionMinor, unsigned int versionBuild, float unk, HWND windowHandle, int unk1, int unk2, int unk3); // @940A70

    static const char* RequiredVersion; // @A1BA50
    static char DetectedVersion[64]; // @A5E800
    static HMODULE LibraryHandle; // @A5E840
    static int ErrorCode; // @A5E844
    static char* ErrorMessageBuffer; // @A5E700
    static bool InstanceAcquired; // @A5E84C
    static unsigned int VersionNumberMajor; // @A5E850
    static unsigned int VersionNumberMinor; // @A5E854
    static unsigned int VersionNumberBuild; // @A5E858
    static unsigned int VersionNumberRequiredMajor; // @A5E85C
    static unsigned int VersionNumberRequiredMinor; // @A5E860
    static unsigned int VersionNumberRequiredBuild; // @A5E864
    static DIESELPOWERCREATEPROC FactoryFunction; // @A5E868
};

extern DieselPower* g_DieselPower; // @A5E848

ASSERT_CLASS_SIZE(DieselPower, 40);