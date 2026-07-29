#pragma once

#include <Bliss/UnityTypes.h>

namespace Offsets {
    inline bool Initialized = false;

    inline MemberMap PlayerControlMembers;
    inline MemberMap PlayerDataMembers;
    inline MemberMap PlayerPhysicsMembers;
    inline MemberMap RoleMembers;
    inline MemberMap CosmeticsLayerMembers;
    inline MemberMap AmongUsClientMembers;
    inline MemberMap InnerNetMembers;
    inline MemberMap WriterMembers;
    inline MemberMap RoleManager;
    inline MemberMap CameraMembers;

    void Init();
}