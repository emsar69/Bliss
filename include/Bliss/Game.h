#pragma once

#include <unordered_map>
#include <cstdint>
#include <string>
#include <Bliss/Offsets.h>
#include <Bliss/il2cpp_Functions.h>
#include <Bliss/UnityTypes.h>

enum AnimType : byte {
    SHIELDS = 1,
    METEOR = 6,
    TRASH = 10 // 10 in mirahq 9 in the skeld. somehow both works in both map
};

struct Color4 {
    float r, g, b, a;
};

struct Vec3 {
    float x,y,z;
};

struct Vec2 {
    float x,y;
};

struct PlayerPhysics : Il2CppObject {
    PlayerPhysics(void* self) : Il2CppObject(self, &Offsets::PlayerPhysicsMembers) {};

    float* GetSpeed(){
        return GetField<float>("Speed");
    }
};

struct Role : Il2CppObject {
    Role(void* self) : Il2CppObject(self, &Offsets::RoleMembers) {};

    int* GetTeamType(){
        return GetField<int>("TeamType");
    }
};

struct PlayerData : Il2CppObject {
    PlayerData(void* self) : Il2CppObject(self, &Offsets::PlayerDataMembers) {};

    Role GetRole() {
        void* addr = *GetField<void*>("Role");
        return Role(addr);
    }

    const wchar_t* GetPlayerName() {
        wchar_t* BaseStringAddr = CallMethod<wchar_t>("get_PlayerName", nullptr) + 0x14/2;
        return BaseStringAddr;
    }

    std::string GetPlayerNameAsString() {
        const wchar_t* wide = GetPlayerName();
        size_t len = std::wcstombs(nullptr, wide, 0);
        std::string name(len, 0);
        std::wcstombs(name.data(), wide, len);
        return name;
    }

    void SetPlayerName(void* CString) {
        void* params[1] = {CString};
        CallMethod<void>("set_PlayerName", params);
    }

    void MarkDirty() {
        CallMethod<void>("MarkDirty");
    }
};

struct CosmeticsLayer : Il2CppObject {
    CosmeticsLayer(void* self) : Il2CppObject(self, &Offsets::CosmeticsLayerMembers) {};

    Color4* GetNameColor() {
        char* nameText = *GetField<char*>("nameText");
        Color4* m_Color = reinterpret_cast<Color4*>(nameText + 0x28); // TextMeshPro
        return m_Color;
    }
};

struct PlayerControl : Il2CppObject {
    PlayerControl(void* self) : Il2CppObject(self, &Offsets::PlayerControlMembers) {};

    bool* GetEnabled() {
        return CallMethod<bool>("get_enabled");
    }

    Vec2* GetPosition() {
        uintptr_t* ret = CallMethod<uintptr_t>("GetTruePosition");
        if(!ret) return nullptr;
        return reinterpret_cast<Vec2*>(reinterpret_cast<uintptr_t>(ret) + 0x10);
    }

    float* GetKillTimer(){
        return GetField<float>("killTimer");
    }

    uint8_t PlayerId(){
        return *GetField<uint8_t>("PlayerId");
    }

    uint32_t NetId(){
        return *GetField<uint32_t>("NetId");
    }

    float* MaxReportDistance() { // Pointer so there's no need for "SetMaxReportDistance" method.
        return GetField<float>("MaxReportDistance");
    }

    CosmeticsLayer GetCosmetics() {
        void* addr = *GetField<void*>("cosmetics");
        return CosmeticsLayer(addr);
    }

    PlayerPhysics GetPlayerPhysics(){
        void* addr = *GetField<void*>("MyPhysics");
        return PlayerPhysics(addr);
    }

    PlayerData GetNetworkedData(){
        void* addr = CallMethod<void>("get_Data");
        return PlayerData(addr);
    }

    void RpcPlayAnimation(AnimType anim) {
        void* params[1];
        params[0] = &anim;
        CallMethod<void>("RpcPlayAnimation", params);
    }

    void RpcSetName(void* str) {
        void* params[1] = {str};
        CallMethod<void>("RpcSetName", params);
    }

    void SetColor(int32_t c) {
        void* params[1];
        params[0] = &c;
        //TODO: Crashes for no reason literally works on cheat engine.
        //TODO: Add crash handler at runtime invoker
        CallMethod<void>("SetColor", params);
    }
};

struct Camera : Il2CppObject {
    Camera() : Il2CppObject(nullptr, &Offsets::CameraMembers) {UpdateSelf();}; // HOWEVER: self isn't fixed here.

    void UpdateSelf(){
        self = CallStaticMethod<void>("get_main");
    }

    Vec2* WorldToScreen(Vec3 vec3) {
        void* params[1];
        params[0] = &vec3;

        uintptr_t* ret = CallMethod<uintptr_t>("WorldToScreenPoint_dup_1", params);
        if(!ret) return nullptr;

        //adding 0x10 cuz it starts from 0x10.
        return reinterpret_cast<Vec2*>(reinterpret_cast<uintptr_t>(ret) + 0x10); //Camera.WorldToScreenPoint_dup_1()
    }
};

struct HazelWriter : Il2CppObject {
    HazelWriter(void* self) : Il2CppObject(self, &Offsets::WriterMembers) {};

    void WriteStr(void* str) {
        void* params[1] = {str};
        CallMethod<void>("Write.String", params);
    }

    void Write(const char* str) {
        void* cs = il2cpp_Functions::il2cpp_string_new(str);
        WriteStr(cs);
    }

    void WriteInt(uint32_t c) {
        void* params[1] = {&c};
        CallMethod<void>("Write.Int32", params);
    }
};

struct AmongUsClient : Il2CppObject {
    AmongUsClient(void* self) : Il2CppObject(self, &Offsets::AmongUsClientMembers) {};

    int32_t GameId() {
        return *GetField<int32_t>("GameId");
    }
    
    int32_t GameState() {
        return *GetField<int32_t>("GameState");
    }

    bool isConnecting() {
        return *GetField<bool>("isConnecting");
    }

    HazelWriter StartRpcImmediately(int32_t targetNetId, byte callId, byte isReliable, int32_t targetClientId) {
        void *params[4];
        params[0] = &targetNetId;
        params[1] = &callId;
        params[2] = &isReliable;
        params[3] = &targetClientId;

        void* writerAddr = CallMethod<void>("StartRpcImmediately", params);
        return HazelWriter(writerAddr);
    }

    void FinishRpcImmediately(HazelWriter writer) {
        void* params[1];
        params[0] = writer.self; // &

        CallMethod<void>("FinishRpcImmediately", params);
    }
};

struct RoleManager : Il2CppObject {
    RoleManager(void* self) : Il2CppObject(self, &Offsets::RoleManager) {};

    void SetRole(PlayerControl plr, uint16_t role) {
        void* params[3];
        params[0] = plr.self;
        params[1] = &role;
        params[2] = nullptr; // r9

        CallMethod<void>("SetRole", params);
    }
};

template <typename T, typename = std::enable_if<std::is_base_of<Il2CppObject, T>::value>::type>
class ListWrapper {
private:
    T** data = nullptr;
    size_t count = 0;

public:
    ListWrapper() = default;
    ListWrapper(void* ListAddr) { Update(ListAddr); }

    void Update(void* ListAddr){
        char* charAddr = reinterpret_cast<char*>(ListAddr);
        char* items = *reinterpret_cast<char**>(charAddr+0x10);
        count = *reinterpret_cast<int*>(charAddr+0x18);
        data = reinterpret_cast<T**>(items + 0x20);
    }

    T operator[](size_t index) {
        return T(data[index]);
    }
    size_t size() const { return count; }

    explicit operator bool() noexcept {
        return data != nullptr;
    }

    class Iterator {
    private:
        T** ptr;

    public:
        Iterator(T** data) : ptr(data) {};

        T operator*() {
            return T(*ptr);
        }
        Iterator& operator++() { ++ptr; return *this; }

        bool operator==(const Iterator& IT) const { return ptr == IT.ptr; }
        bool operator!=(const Iterator& IT) const { return ptr != IT.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data+count); }
};

namespace Game{
    extern PlayerControl g_LocalPlayer;
    extern ListWrapper<PlayerControl> g_PlayerList;
    extern AmongUsClient g_AmongUsClient;
    extern RoleManager g_RoleManager;
    void UpdateGlobals();
}