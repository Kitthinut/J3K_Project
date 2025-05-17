#pragma once
#include <string>

/// @brief สำหรับผู้ใดก็ตามที่กำลังจะทำระบบ Skill อันนี้คือตัว Dummy ของ Jangkun เอาไว้เทสระบบนะ
//// @note  อย่างน้อยจะได้ไล่โค้ดเราถูกว่าเอาไปเขียนไว้ตรงไหน Good Luck Have Fun (Jangkun 17/May)
struct Skill {
        std::string name;
        // พวก Mana อื่น ๆ เอามาใส่ในนี้ได้
};

// Dummy for testing system. ข้าพเจ้าไม่ทราบว่าจะ รวมโค้ดยังไงดี
namespace SkillDB {
    const Skill FireBall  = {"Fire Ball"};
    const Skill IceSpike  = {"Ice Spike"};
    const Skill Heal      = {"Heal"};
    const Skill Thunder   = {"Thunder"};
    const Skill WindSlash = {"Wind Slash"};
}