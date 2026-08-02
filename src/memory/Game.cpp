#include <Bliss/Game.h>
#include <Bliss/Memory.h>
#include <Bliss/il2cpp_Functions.h>

PlayerControl Game::g_LocalPlayer(nullptr);
ListWrapper<PlayerControl> Game::g_PlayerList;
AmongUsClient Game::g_AmongUsClient(nullptr);
RoleManager Game::g_RoleManager(nullptr);
ShipStatus Game::g_ShipStatus(nullptr);
GameOptionsManager Game::g_GameOptionsManager(nullptr);

const char* SystemTypes::the_skeld[7] = {
    "LowerEngine", "Electrical", "MedBay", "Cafeteria", "UpperEngine", "Storage", "Security"
};

const char* SystemTypes::polus[7] = {
    "LifeSupp", "Electrical", "Storage", "Laboratory", "Office", "Comms", "Weapons"
};

const char* SystemTypes::airship[6] = {
    "Comms", "Kitchen", "Brig", "MainHall", "Records", "Medical"
};

const char* SystemTypes::the_fungle[7] = {
    "Storage", "Kitchen", "Laboratory", "Lookout", "MiningPit", "Comms", "Reactor"
};

std::vector<TickTask> TickManager::tasks;

void Game::UpdateGlobals(){
    void* playerClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "PlayerControl");
    void* AmongUsClientClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "AmongUsClient");
    void* RoleManagerClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "RoleManager");
    void* ShipStatusClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "ShipStatus");
    void* SystemTypesClass = il2cpp_Functions::il2cpp_class_from_name(Memory::CSharpAssemble, "", "SystemTypes"); // holds doors enum

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

    void* ShipStatusInstanceField = il2cpp_Functions::il2cpp_class_get_field_from_name(ShipStatusClass, "Instance");
    void* ShipStatusInstance = nullptr;
    il2cpp_Functions::il2cpp_field_static_get_value(ShipStatusInstanceField, &ShipStatusInstance);

    g_LocalPlayer.self = localplr;
    g_AmongUsClient.self = AmongUsClientInstance;
    g_RoleManager.self = RoleManagerInstance;
    g_PlayerList.Update(allPlayersControl);
    g_ShipStatus.self = ShipStatusInstance;
    g_GameOptionsManager.Update();
}