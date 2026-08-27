// Copyright (C) 2026 emsar69
// SPDX-License-Identifier: GPL-3.0-or-later
// See the LICENSE file for the full license text.

#include <Bliss/Gui.h>

#include <Bliss/Memory.h>
#include <Bliss/Game.h>

#include <imgui/imgui.h>

#include <chrono>

#define IM_COL32_FLOAT(f) IM_COL32(f[0]*255, f[1]*255, f[2]*255, f[3]*255)

#ifdef _WIN32
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>
#include <Bliss/Devices.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

uint64_t tick() {
	 auto now = std::chrono::system_clock::now();

    const int64_t daysBetweenEpochs = 719162; 

    const int64_t secondsBetweenEpochs = daysBetweenEpochs * 24 * 60 * 60;

    int64_t now_seconds = std::chrono::duration_cast<std::chrono::seconds>(
        now.time_since_epoch()).count();

    int64_t total_seconds = now_seconds + secondsBetweenEpochs;

    int64_t ticks = total_seconds * 10000000;

    auto ns_part = std::chrono::duration_cast<std::chrono::nanoseconds>(
        now.time_since_epoch()).count() % 1000000000;
    ticks += ns_part / 100; // 1 tick = 100 ns

	return ticks;
}

void SetupCommon() {
		if (ImGui::CreateContext() == nullptr) printf("NO context created.\n");
	//ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowBorderSize = 1.0f;
	style.WindowTitleAlign = ImVec2(.5, .5);
	style.FrameBorderSize = 1.0f;
	style.WindowRounding = 12;
	style.FrameRounding = 7;
	style.WindowPadding = ImVec2(20, 7);
	style.FontScaleMain = 1.3f;

	ImVec4* colors = style.Colors;
	colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg]                = ImVec4(0.33f, 0.00f, 0.00f, 0.54f);
	colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.90f, 0.22f, 0.06f, 0.40f);
	colors[ImGuiCol_FrameBgActive]          = ImVec4(0.87f, 0.25f, 0.11f, 0.67f);
	colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive]          = ImVec4(0.76f, 0.15f, 0.10f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark]              = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_SliderGrab]             = ImVec4(0.17f, 0.79f, 0.01f, 1.00f);
	colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.44f, 1.00f, 0.03f, 1.00f);
	colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.83f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered]          = ImVec4(0.60f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ButtonActive]           = ImVec4(0.56f, 0.12f, 0.12f, 1.00f);
	colors[ImGuiCol_Header]                 = ImVec4(0.98f, 0.26f, 0.26f, 0.31f);
	colors[ImGuiCol_HeaderHovered]          = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive]           = ImVec4(0.98f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.75f, 0.10f, 0.10f, 0.78f);
	colors[ImGuiCol_SeparatorActive]        = ImVec4(0.66f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.28f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.98f, 0.26f, 0.26f, 0.67f);
	colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.05f, 0.95f, 0.40f, 0.95f);
	colors[ImGuiCol_InputTextCursor]        = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TabHovered]             = ImVec4(0.73f, 0.07f, 0.07f, 0.80f);
	colors[ImGuiCol_Tab]                    = ImVec4(0.58f, 0.18f, 0.18f, 0.86f);
	colors[ImGuiCol_TabSelected]            = ImVec4(0.68f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.89f, 0.22f, 0.22f, 1.00f);
	colors[ImGuiCol_TabDimmed]              = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.14f, 0.21f, 0.42f, 1.00f);
	colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
	colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.58f, 1.00f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextLink]               = ImVec4(0.00f, 0.71f, 0.86f, 1.00f);
	colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.98f, 0.26f, 0.26f, 0.35f);
	colors[ImGuiCol_TreeLines]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_UnsavedMarker]          = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_NavCursor]              = ImVec4(0.83f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	auto& IO = ImGui::GetIO();
	IO.IniFilename = NULL;
	IO.LogFilename = NULL;
}

#if defined(_WIN32)

void Gui::WinSetupMenu(ID3D11Device* device, ID3D11DeviceContext* context) {
	SetupCommon();

	Gui::originalWindowProcess = reinterpret_cast<WNDPROC>(
		SetWindowLongPtr(Gui::window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndProc))
	);

	ImGui_ImplWin32_Init(Gui::window);
	
	if (device == nullptr) MessageBoxA(NULL, "device not found", "ked", 0);
	if (!ImGui_ImplDX11_Init(device, context)) MessageBoxA(NULL, "DX11 INIT ERROR", "!", 0);

	setup = true;
}

#elif defined(__ANDROID__)

void Gui::AndSetupMenu() {
	SetupCommon();

	// Android specific shit. TODO

	setup = true;
}

#endif

bool noCooldown = false;
bool ShowImposters = false;
bool Esp = false;
char NameToSet[64] = {};
float EspCrew[4] = {0, 1, 1, 1};
float EspImpostor[4] = {1, 0, 0, 1};

bool SetNoclip(bool active) {
	if(!Game::g_LocalPlayer) return false;
	void* ADDR_CC2D = Game::g_LocalPlayer.GetComponent(Types::CircleCollider2D);
	Behaviour CC2D(ADDR_CC2D);
	printf("CC2D: %p\n", ADDR_CC2D);
	if(!CC2D) return false;
	CC2D.SetEnabled(!active); // Disables/Enables CircleCollider2D inside of the character.

	return true;
}

bool SetShadows(bool active) {
	Camera cam;
	Transform shadows = cam.GetTransform().GetChild(3);
	if(!shadows) return false;
	
	GameObject shadows_gameobject = shadows.GetGameObject();
	if(!shadows_gameobject) return false;
	
	shadows_gameobject.SetActive(active);
	return true;
}

bool CompleteAllTasks(PlayerControl& player) {
	ListWrapper<Empty> tasks = player.GetTasks();
	if(!tasks) return false;

	int task_count = tasks.size();
	for(int i = 0; i < task_count; i++) {
		player.RpcCompleteTask(i);
	}

	return true;
}

void HandleFeatures(){
	Game::UpdateGlobals();

	if(noCooldown && Game::g_LocalPlayer) {
		float* kill_timer = Game::g_LocalPlayer.GetKillTimer();
		*kill_timer = 0;
	}

	if(Esp) {
		Camera cam;
		//cam.UpdateSelf(); Just noticed that's not needed since I do Update in constructor.

		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		ImGuiIO& io = ImGui::GetIO();

		// GameState == 0 ? in menu
		// GetIsGameOver, Player.Canmove
		if(Game::g_PlayerList && Game::g_LocalPlayer){
			Vec2* _ = Game::g_LocalPlayer.GetPosition();
			if(!_) return;
			Vec2 mypos = *_;
			Vec3 mypos3 = {mypos.x, mypos.y, 0};
			Vec2* __ = cam.WorldToScreen(mypos3);
			if(!__) return;
			Vec2 mypos_to_screen = *__;
			mypos_to_screen.y = io.DisplaySize.y - mypos_to_screen.y;

			for(int i = 0; i < Game::g_PlayerList.size(); i++){
				PlayerControl player = Game::g_PlayerList[i];
				if(!player) break;

				Vec2* ___ = player.GetPosition();
				if(!___) break;
				Vec2 pos = *___;
				Vec3 cords = {pos.x, pos.y, 0};

				Vec2* ____ = cam.WorldToScreen(cords);
				if(!____) break;
				Vec2 screen = *____;
				screen.y = io.DisplaySize.y - screen.y;

				PlayerData playerData = player.GetNetworkedData();
				if(!playerData) break;

				Role role = playerData.GetRole();
				if(!role) break;
				int* _____ = role.GetTeamType();
				if(!_____) break;
				bool isBad = *_____;

				ImU32 col = isBad ? IM_COL32_FLOAT(EspImpostor) : IM_COL32_FLOAT(EspCrew);

				draw_list->AddRect({screen.x-50, screen.y-150}, {screen.x+50, screen.y}, col, 0.0f, 0, 4.0f);
				draw_list->AddLine({mypos_to_screen.x, mypos_to_screen.y}, {screen.x, screen.y}, col, 2.0f);

				if(isBad) {
					// Draw kill cooldown
					float timer = player.self == Game::g_LocalPlayer.self ? *player.GetKillTimer() : player.GetKillTimerState();
					int G = 50+timer*10;
					if(G > 255) G = 255;

					char buf[32] = {0};
					std::snprintf(buf, sizeof(buf), "Est. Cooldown: %.1fs", timer);
					draw_list->AddText(ImGui::GetFont(), 25.0f, {screen.x-50, screen.y}, IM_COL32(240, G, 34, 255), buf);
				}
			}
		}
	}
}

unsigned char GetCurrentMapId() {
	if(Game::g_AmongUsClient.NetworkMode() == 2) { // FreePlay
		return Game::g_AmongUsClient.TutorialMapId();
	}else{
		NormalGameOptionsV10 options = Game::g_GameOptionsManager.CurrentGameOptions();
		if(!options) return 255;

		unsigned char* map_id = options.MapId();
		if(map_id == nullptr) return 255;

		return *map_id;
	}
}

#if defined(__ANDROID__)

void AndRenderBegin() {

}

void AndRenderEnd() {

}

#elif defined(_WIN32)

void WinRenderBegin() {
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
}

void WinRenderEnd() {
	Devices::g_pd3dContext->OMSetRenderTargets(1, &Devices::g_mainTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

#endif

void Gui::Render(){
	if(!Offsets::Initialized) return;
    #if defined(__ANDROID__)
		AndRenderBegin();
	#elif defined(_WIN32)
		WinRenderBegin();
	#endif
	ImGui::NewFrame();
	HandleFeatures();
	TickManager::Tick();

	//ImGui::ShowStyleEditor();
	//ImGui::ShowDemoWindow();
	
	if(Gui::open) {
		ImGui::Begin("Bliss", &Gui::open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
		
		if(ImGui::BeginTabBar("tabs")) {
			if(ImGui::BeginTabItem("Main")) {
				ImGui::Text("testtest gay");
				if(Game::g_LocalPlayer){
					PlayerPhysics physics = Game::g_LocalPlayer.GetPlayerPhysics();
					if(physics){
						float* speed = physics.GetSpeed();
						ImGui::SliderFloat("Speed", speed, 0, 20, "%.1f");
					}

					float* kill = Game::g_LocalPlayer.GetKillTimer();
					ImGui::Text("Cooldown: %.1f", *kill);

					float* report_distance = Game::g_LocalPlayer.MaxReportDistance();
					ImGui::SliderFloat("Report Distance", report_distance, 0.0f, 10.0f, "%.1f", ImGuiSliderFlags_NoSpeedTweaks);

					static const char* anims[] = {
						"Shields",
						"Asteroids",
						"Trash"
					};
					static const AnimType anim_values[] = {
						AnimType::SHIELDS,
						AnimType::METEOR,
						AnimType::TRASH
					};
					static int anim_index = 0;
					ImGui::Combo("Animations", &anim_index, anims, IM_ARRAYSIZE(anims));
					if(ImGui::Button("Play animation")) {
						Game::g_LocalPlayer.RpcPlayAnimation(anim_values[anim_index]);
					}

					PlayerData data = Game::g_LocalPlayer.GetNetworkedData();

					CosmeticsLayer cosmetics = Game::g_LocalPlayer.GetCosmetics();
					Color4* color = cosmetics.GetNameColor();
					color->r = 0;
					/*
					TODO:
					Reach innernetclient so write a program that graphs from root(static fields) to target.
					StartRpcImmediately

					bruh,
					AmongUsInstance addr = InnerNetClientAddr

					RCX (1st param aka. SELF) = AmongUsInstance When calling "StartRpcImmediately"

					*/
					//printf("R: %.1f, G: %.1f, B: %.1f, A: %.1f\n", color->r, color->g, color->b, color->a);
					
					uint32_t netid = Game::g_LocalPlayer.NetId();
					int32_t gameid = Game::g_AmongUsClient.GameId();
					uint8_t playerid = Game::g_LocalPlayer.PlayerId();

					if(ImGui::Button("imp pls")) { //Pls work
						//TODO: Breakpoints in setrole and before calls to see the value retrieved from stack
						Game::g_RoleManager.SetRole(Game::g_LocalPlayer, 1); // so that's the function
					}
					ImGui::InputText("Name", NameToSet, IM_ARRAYSIZE(NameToSet));
					if(ImGui::Button("Set My Name")){
						//uint64_t ticks = tick();

						void* str = il2cpp_Functions::il2cpp_string_new(NameToSet);
						//data.SetPlayerName(str);
						Game::g_LocalPlayer.RpcSetName(str);
						/*data.MarkDirty();

						HazelWriter writer = Game::g_AmongUsClient.StartRpcImmediately(netid, 6, 1, -1); // 6 = setname
						printf("NetId: %d, client: %p, writer: %p\n", netid, Game::g_AmongUsClient.self, writer.self);
						writer.WriteStr(str);
						writer.Write("randomaaa");
						Game::g_AmongUsClient.FinishRpcImmediately(writer);*/

						//printf("PlayerId: %d, gameid: %d, ticks: %llu\n", playerid, gameid, ticks);
					}
					if(ImGui::Button("Set All Names")){
						void* str = il2cpp_Functions::il2cpp_string_new(NameToSet);
						for(int i = 0; i < Game::g_PlayerList.size(); i++){
							PlayerControl plr = Game::g_PlayerList[i];
							if(!plr) break;
							plr.RpcSetName(str);
						}
					}

					if(ImGui::Button("me red")) {
						Game::g_LocalPlayer.SetColor(0); //red
						//rpc
						//HazelWriter writer = Game::g_AmongUsClient.StartRpcImmediately(netid, 8, 1, -1); // 8 = setcolor
						//printf("NetId: %d, client: %p, writer: %p\n", netid, Game::g_AmongUsClient.self, writer.self);
						//writer.WriteInt(0);
						//Game::g_AmongUsClient.FinishRpcImmediately(writer);
					}
				}

				ImGui::Separator();
				
				ImGui::Checkbox("No Kill Cooldown", &noCooldown);
				ImGui::Checkbox("Label Impostors", &ShowImposters); // didn't implement yet.

				ImGui::Separator();

				if(ImGui::Button("Enable Shadows")) SetShadows(true);
				if(ImGui::Button("Disable Shadows")) SetShadows(false);

				ImGui::Separator();

				if(ImGui::Button("Enable Noclip")) SetNoclip(true);
				if(ImGui::Button("Disable Noclip")) SetNoclip(false);

				ImGui::Separator();

				if(ImGui::Button("Complete my tasks")) {
					if(!CompleteAllTasks(Game::g_LocalPlayer)) {
						printf("Complete All tasks returns false. No list of tasks found.\n");
					}
				}

				ImGui::EndTabItem();
			}
			
			if(ImGui::BeginTabItem("Impostor")) {
				if(ImGui::Button("Close All Doors") && Game::g_ShipStatus) {
					unsigned char MapId = GetCurrentMapId();
					Game::g_ShipStatus.RpcCloseAllDoors(MapId);
				}

				ImGui::Separator();
				if(ImGui::Button("Sabotage Reactor") && Game::g_ShipStatus) {
					int system_type = SystemTypes::GetType("Reactor");
					Game::g_ShipStatus.RpcUpdateSystem(system_type, 128);
				}
				if(ImGui::Button("Sabotage O2") && Game::g_ShipStatus) {
					int system_type = SystemTypes::GetType("LifeSupp");
					Game::g_ShipStatus.RpcUpdateSystem(system_type, 128);
				}
				if(ImGui::Button("Sabotage Lights (Unfixable)") && Game::g_ShipStatus) {
					int system_type = SystemTypes::GetType("Electrical");
					Game::g_ShipStatus.RpcUpdateSystem(system_type, 7); // 7 somehow is unfixable^^
				}

				ImGui::EndTabItem();
			}

			if(ImGui::BeginTabItem("Players")) {
				if(Game::g_PlayerList){
					for(int i = 0; i < Game::g_PlayerList.size(); i++){
						PlayerControl player = Game::g_PlayerList[i];
						if(!player) break;

						PlayerData playerData = player.GetNetworkedData();
						if(!playerData) continue;

						ImGui::Separator();
						ImGui::Text("Name: %ls", playerData.GetPlayerName());

						Role role = playerData.GetRole();
						if(!role) continue;
						bool isBad = *role.GetTeamType();
						ImGui::TextColored(ImVec4(isBad, !isBad, !isBad, 1), "Team: %d", isBad);
					}
				}else{
					ImGui::Text("Couldn't find player list.");
				}
				ImGui::EndTabItem();
			}

			if(ImGui::BeginTabItem("Esp")) {
				ImGui::Checkbox("Esp", &Esp);
				ImGui::ColorPicker4("Esp Crew", EspCrew);
				ImGui::ColorPicker4("Esp Impostor", EspImpostor);
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
		
		ImGui::End();
	}
	
	ImGui::Render();

	#if defined(__ANDROID__)
		AndRenderEnd();
	#elif defined(_WIN32)
		WinRenderEnd();
	#endif
}

#ifdef _WIN32
LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (GetAsyncKeyState(VK_DELETE) & 1)
		Gui::open = !Gui::open;

	if(Gui::open) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		ImGuiIO& io = ImGui::GetIO();

		if (io.WantCaptureMouse && (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST)) return 0;
		if (io.WantCaptureKeyboard && (msg >= WM_KEYFIRST && msg <= WM_KEYLAST)) return 0;
	}

	return CallWindowProc(Gui::originalWindowProcess, hWnd, msg, wParam, lParam);
}
#endif