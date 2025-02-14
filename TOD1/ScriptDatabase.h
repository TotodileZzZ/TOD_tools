#pragma once
#include "Globals.h"
#include "LogDump.h"
#include <vector>
#include <map>

#ifdef PLATFORM_PS2
    #define SCRIPT_PROPERTIES_TOTAL         5940
    #define SCRIPT_PROPERTIES_BUILTIN_TOTAL 711

    #define SCRIPT_PROPERTIES_BUILTIN_CRC   0xE99606BA
    #define SCRIPT_PROPERTIES_DATABASE_CRC  0x24A37B21
#endif

#ifdef PLATFORM_XBOX
    #define SCRIPT_PROPERTIES_TOTAL         0
    #define SCRIPT_PROPERTIES_BUILTIN_TOTAL 0

    #define SCRIPT_PROPERTIES_BUILTIN_CRC   0
    #define SCRIPT_PROPERTIES_DATABASE_CRC  0
#endif

#ifdef PLATFORM_PC
    #define SCRIPT_PROPERTIES_TOTAL         5994
    #define SCRIPT_PROPERTIES_BUILTIN_TOTAL 711

    #define SCRIPT_PROPERTIES_BUILTIN_CRC   0xE99606BA
    #define SCRIPT_PROPERTIES_LOADED_CRC    0x65C37710
#endif

class DataType;
class EntityType;
class Entity;
class ScriptThread;

//  NOTE: this is here, because both ScriptThread nad Entity classes are dependant on this header.
struct EntityScriptData
{
    int         field_0;    //  NOTE: flags of some sort.
    ScriptThread*m_ScriptThread;
    void        (*m_Handler)();
    int         field_C;
    int        *field_10;
    int         field_14;
    int         field_18;
    int        *field_1C;
    int        *field_20;
};

//  NOTE: actual header path "kernel/database/propertytype.h".
struct GlobalProperty
{
    int             m_PropertyId = 0;
    char           *m_PropertyName = nullptr;
    DataType       *m_PropertyType = nullptr;

    GlobalProperty() {};
    GlobalProperty(const char* const propertyname, unsigned int ind);   //  @873040
    ~GlobalProperty();

    void            GetNameAndType(String& outStr) const; // @8731C0

    static void     ClearGlobalProperties();    //  @873650

    static GlobalProperty* GetById(unsigned int id); // @872FC0
};

extern std::vector<GlobalProperty>      GlobalPropertiesList; // @A3CF20
extern std::map<String, unsigned int>   GlobalPropertiesMap; // @A3CF30

class GlobalCommand
{
protected:
    struct Argument
    {
        String      m_PropertyName;
        DataType   *m_ScriptType;
        int         m_TotalSizeBytes;

        Argument(String& argname, const DataType* argtype, unsigned int argsize);
    };

    struct Arguments
    {
        std::vector<Argument>   m_ArgumentsList;
        int         field_C;
        int         m_TotalSizeBytes;
        int         m_TotalSize;
    };

    Arguments       m_Arguments; // NOTE: element at index 0 is always return scripttype.
    int             m_GlobalIndex;
    char           *m_ArgumentsString; // NOTE: full name with arguments.
    char           *m_CommandName; // NOTE: the name without arguments (only command name).

private:
    void            AddArgumentType(DataType* argtype); // @862650

public:
    GlobalCommand(const char* const commandname, const unsigned int commandind); // @871FE0
    ~GlobalCommand();

    void            GetReturnTypeString(String& outStr); // @871A90

    static void     ClearGlobalCommands();  //  @8724E0
};

extern std::vector<GlobalCommand>       GlobalCommandsList; // @A11470
extern std::map<String, unsigned int>   GlobalCommandsMap; // @A3CF08

class EntityType;
class ScriptThread;

//  NOTE: actual path to header file "/Kernel/Script/Interface/Scriptbaked.h".
class Scriptbaked
{
    friend class Node;
    friend class Entity;
    friend class EntityType;

    struct Property
    {
        GlobalProperty *m_Info;
        size_t      m_Offset;
        char       *m_DefaultValue;
        int         field_C;
    };

    struct Method
    {
        short       m_Id;
        short       m_PropertyBlockId;
        void        (*m_ThreadHandler)(ScriptThread*);
        void        (*m_MethodPtr)(ScriptThread*, void* args);

        typedef void (*ScriptMethodType)(ScriptThread* thread, void* args);
    };

    struct Parameter
    {
        void        (*m_ProcPtr)(ScriptThread*);
        DataType   *m_ParamType;
    };

protected:
    std::vector<Property>   m_PropertiesList;
    std::map<int, int>      m_PropertiesValues;
    int                     field_1C;
    int                     m_ScriptSize;
    std::vector<Method>     m_MethodsList;
    std::vector<Parameter>  m_ParametersList;
    int                     m_PropertiesBlocksTotal;
    EntityType             *m_BaseEntity;
    String                  m_Name;
    union
    {
        struct
        {
            unsigned        IsCompiled : 1;
            unsigned        _1 : 1;
        };
        uint8_t             DwFlags;
    }                       m_Flags;
    void                    (*field_60)(ScriptThread*);

public:
    Scriptbaked(const char* const scriptName, const char* const parentName, bool a3, bool a4); // @48A530

    void                        AddMember(const int fieldId, char* defaultValue, const int); // @48AF10
    void                        AddMethod(short id, void (*methodHandler)(ScriptThread*), void (*stateHandler)(ScriptThread*, void*)); // @48A690
    void                        AddLocal(void (*procPtr)(ScriptThread*), DataType* localType);  //  @48A700 //  NOTE: upon entering the 'procPtr' the stack must be adjusted accordingly to the number of 'localtype' variables 'added'.
    void                        AddProperty(Node* scriptNode, const unsigned int propertyIndex, const int* const propertyValue);    //  @489EA0
    void                        CalculateSize(); // @48AA60

private:
    bool                        _48A1B0(Node* node, const int32_t scriptId, uint8_t* args); //  @48A1B0

public:

    typedef void (*ScriptProcedureType)(ScriptThread* thread);

    bool                        GetMappedPropertyValue(const uint32_t* const nodeParameters, const uint32_t propertyIndex, uint8_t* outPropertyValue) const;   //  @48B6A0
    bool                        _48A7E0(Node* node, int scriptId, void* args); // @48A7E0
    void                        ClearEntityProperties(Entity* ent); //  @489C90
    EntityType*                 GetAttachedScript() const;  //  @489AE0
    const int                   GetPropertiesListSize() const;  //  @489A20
    void                        GetEntityPropertyValue(Entity* ent, const unsigned int propertyindex, int* outPropValue);   //  @489E50
    bool                        HasPropertyId(const unsigned int propertyid) const; //  @489A30
    void                        CopyScriptParameters(Entity* entity);    //  @489BE0
    void                        GetMethodParams(void (*methodPtr)(ScriptThread*), std::vector<DataType*>& outParams) const;   //  @48A750
    int                         GetParameterProcedureIndex(void (*procedure)(ScriptThread*)) const; //  @489F50
    const int                   GetPropertyValueByIndex(const int index) const; //  @489A70
    void                        AddPropertyByReference(Node* callerNode, const int propertyInd, const void* data); //  @489D40
    void                        SaveNodeProperties(Node* node);    //  @48A070
    ScriptProcedureType         GetParameterProcedure(const uint32_t parameterIndex);   //  @489F80

    EntityType*                 AssignScriptToEntity(EntityType * parent); // @48A3F0

    static Scriptbaked*         GetGlobalScriptByName(const char* name); // @48C590
    static Scriptbaked*         GetGlobalScriptById(const unsigned int id); // @48C580
    static int                  GetScriptIdByName(const char* const name); // @48C910
    static void                 InstantiateGlobalScripts();  //  @48C960
    static void                 AssignCommonNodes();    //  @48C7D0

    static unsigned int         GetScriptIdByFullName(const char* const name);  //  NOTE: a special version of 'GetTypeByName' to be used when loading game-specific scripts. Not in original code.

    static std::vector<Scriptbaked*> ScriptsList; // @A0B424
    static std::vector<Node*>   SceneScriptEntitiesList;    //  @A3B5A4
};

extern void* GlobalScriptsArray[410]; // @A3B7A4 // TODO: this could be just a global 'scripts space' where mixed objects are contained.
extern Node* CacheScriptNode;    //  @A3B58C
extern Node* CommonScriptNode;   //  @A3B590
extern Node* CommonAnimSlotScriptNode;   //  @A3B594
extern Node* CommonTriggerScriptNode;    //  @A3B598
extern Node* IntroCommonScriptNode;  //  @A3B59C

ASSERT_CLASS_SIZE(Scriptbaked, 100);

extern unsigned int GlobalPropertyListChecksum; // @A3CF40
extern bool   GlobalPropertyListChecksumObtained; // @A3CF1C
extern unsigned int GlobalCommandListChecksum; // @A3CF18
extern bool   GlobalCommandListChecksumObtained; // @A3CEF4

extern unsigned int GetGlobalPropertyListChecksum(); // @873440
extern unsigned int GetGlobalCommandListChecksum(); // @871DD0
extern unsigned int GetGlobalPropertyListSize();    //  @872FB0
extern unsigned int GetGlobalCommandListSize(); //  @871A20
extern int GetPropertyIdByName(const char* const propertyname); // @8732C0
extern int GetCommandByName_Impl(const char* const commandname); // @872360
extern int GetCommandByName(const char* const commandname); // @872410
extern short GetProperty(const char* const propertyname, bool existingProperty); // @8736B0
extern int32_t GetCommand(const char* const commandname, bool existingCommand); // @872590

extern void ReadDatabaseFile(const char* path); // @48C400
extern void LoadScripts(); // @7A1F60
extern bool FindScript(const char* const scriptname, String& zipname);   //  @48C680

namespace Script
{
    static bool FileCheck = false; // @A35DE0
    static bool ForceFeedback = false; // @A35E70
    static bool SavePlatformPS2 = true; // @A090C8
    static unsigned int Ps2MaxTextureSize = 1024; // @A10FF0
    static const char* const CountryCodes[] = {
        "uk", "fr", "it", "de", "es", "dk"
    }; // @A089BC
    static bool _A1B98D = true; // @A1B98D
    static bool CheckOriginalAsset = true; // @A11540
    static bool WarningShow = true; // @A082FE
    static bool FrameConsoleMarker = true; // @A1B98C
    static float MinFadeDist = 15.f; // @A11C8C
    static bool LodAndFade = true; // @A11C88
    static bool FixDanglingRefs = true; // @A1207D
    static float LodFactor = 1.0f; // @A12090
    static unsigned int LanguageStringsOffset = 0; // @A35E28
    static bool RelaxBuildVersionCheck; // @A5D5B0
    static bool CutsceneDisableAware; // @A3D892
    static bool CutsceneForceCompleteLodUpdates; // @A5D5A8
    static bool ShowHud; // @A3E0C8
    static bool CheckDataSanity; // @A5D5A9
    static bool CheckDivisionByZero; // @A5D5AA
    static bool Ps2PlayCtrl; // @A5D5B8
    static bool CheckDanglingRefs; // @A3DC4C
    static bool SimulateReleaseBuild; // @A3B584
    static float _A11C90 = 1.f; // @A11C90

    static bool LoadBlocks;
    static bool Fullscreen;
    static unsigned int IconResourceId;

    extern String Filesystem;
    extern String ControlType;
    extern String Region;
    extern String VersionName; // @A1B9C8
    extern String StreamedSoundExt; // @A35EE4
    extern String LanguageMode; // @A086A8
    extern String ScriptsPath; // @A0B434
    extern std::vector<StringTuple> DirectoryMappings; // @A35DE4

    static const char* GetCurrentCountryCode() { return CountryCodes[LanguageStringsOffset]; }; // @42E500
    static void SetCountryCode(const char* const lang) // @42E530
    {
        unsigned int languageIndex = NULL;

        for (unsigned int i = 0; i < (sizeof(CountryCodes) / sizeof(char*)); i++)
            if (*CountryCodes[i] == *lang && CountryCodes[i][1] == lang[1])
                languageIndex = i;

        Script::LanguageStringsOffset = languageIndex;
    }
}