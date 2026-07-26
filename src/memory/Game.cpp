#include <Bliss/Game.h>
#include <Bliss/Memory.h>
#include <Bliss/il2cpp_Functions.h>

PlayerControl Game::g_LocalPlayer(nullptr);
ListWrapper<PlayerControl> Game::g_PlayerList;
AmongUsClient Game::g_AmongUsClient(nullptr);
RoleManager Game::g_RoleManager(nullptr);

void Game::UpdateGlobals(){
    void* playerClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "PlayerControl");
    void* AmongUsClientClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "AmongUsClient");
    void* RoleManagerClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "RoleManager");

    void* localPlrField = il2cpp_Functions::il2cpp_class_get_field_from_name(playerClass, "LocalPlayer");
    void* localplr = nullptr;
    il2cpp_Functions::il2cpp_field_static_get_value(localPlrField, &localplr);

    void* playerListField = il2cpp_Functions::il2cpp_class_get_field_from_name(playerClass, "AllPlayerControls");
    void* allPlayersControl = nullptr;
    il2cpp_Functions::il2cpp_field_static_get_value(playerListField, &allPlayersControl);

    void* AmongUsClientInstanceField = il2cpp_Functions::il2cpp_class_get_field_from_name(AmongUsClientClass, "Instance");
    void* AmongUsClientInstance = nullptr;
    il2cpp_Functions::il2cpp_field_static_get_value(AmongUsClientInstanceField, &AmongUsClientInstance);

    void* RoleManagerInstanceField = il2cpp_Functions::il2cpp_class_get_field_from_name(RoleManagerClass, "_instance");
    void* RoleManagerInstance = nullptr;
    il2cpp_Functions::il2cpp_field_static_get_value(RoleManagerInstanceField, &RoleManagerInstance);

    g_LocalPlayer.self = localplr;
    g_AmongUsClient.self = AmongUsClientInstance;
    g_RoleManager.self = RoleManagerInstance;
    g_PlayerList.Update(allPlayersControl);
}