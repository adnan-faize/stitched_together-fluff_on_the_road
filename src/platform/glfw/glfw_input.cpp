#include <string>
#include <string_view>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "shared/input_types.hpp"

#include "platform/platform_input.hpp"

namespace stfr_platform {

    stfr::InputCode StringToInputCode_Physical(std::string_view str) {
        if (str == "W") { return GLFW_KEY_W; }
        if (str == "A") { return GLFW_KEY_A; }
        if (str == "S") { return GLFW_KEY_S; }
        if (str == "D") { return GLFW_KEY_D; }

        return stfr::INPUT_UNKNOWN;
    }

    static std::unordered_map<std::string, stfr::InputCode> s_LocalizedMap;
    static bool s_MapInitialized = false;

    void InitializeLocalizedMap() {
        if (s_MapInitialized) { return; }

        s_LocalizedMap["Escape"] = GLFW_KEY_ESCAPE;
        s_LocalizedMap["Tab"] = GLFW_KEY_TAB;
        s_LocalizedMap["Enter"] = GLFW_KEY_ENTER;
        s_LocalizedMap["Space"] = GLFW_KEY_SPACE;
        s_LocalizedMap["Left Shift"] = GLFW_KEY_LEFT_SHIFT;
        s_LocalizedMap["Left Ctrl"] = GLFW_KEY_LEFT_CONTROL;
        s_LocalizedMap["Right Shift"] = GLFW_KEY_RIGHT_SHIFT;
        s_LocalizedMap["Right Ctrl"] = GLFW_KEY_RIGHT_CONTROL;

        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) {
            const char* name = glfwGetKeyName(key, 0);
            if (name != nullptr) { s_LocalizedMap[std::string(name)] = key; }
        }

        s_MapInitialized = true;
    }

    stfr::InputCode StringToInputCode_Localized(std::string_view str) {
        InitializeLocalizedMap();
        auto it = s_LocalizedMap.find(std::string(str));
        if (it != s_LocalizedMap.end()) { return it->second; }
        return stfr::INPUT_UNKNOWN;
    }

    std::string_view InputCodeToString_Localized(stfr::InputCode code) {
        switch (code) {
            // Special Keys
            case GLFW_KEY_ESCAPE:        return "Escape";
            case GLFW_KEY_ENTER:         return "Enter";
            case GLFW_KEY_SPACE:         return "Space";
            case GLFW_KEY_LEFT_SHIFT:    return "Left Shift";
            case GLFW_KEY_LEFT_CONTROL:  return "Left Ctrl";
            case GLFW_KEY_RIGHT_SHIFT:   return "Right Shift";
            case GLFW_KEY_RIGHT_CONTROL: return "Right Ctrl";
            // Gamepad

        }

        const char* name = glfwGetKeyName(code, 0);
        if (name) { return std::string_view(name); }
        return "Unknown";
    }

}
