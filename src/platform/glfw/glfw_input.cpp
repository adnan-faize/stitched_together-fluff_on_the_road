#include <string>
#include <string_view>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "shared/input_types.hpp"

#include "platform/platform_input.hpp"

namespace stfr_platform {

    stfr::InputCode StringToPlatformKey_Physical(std::string_view str) {
        if (str == "W") { return GLFW_KEY_W; }
        if (str == "A") { return GLFW_KEY_A; }
        if (str == "S") { return GLFW_KEY_S; }
        if (str == "D") { return GLFW_KEY_D; }

        return stfr::PLATFORM_KEY_UNKNOWN;
    }

    static std::unordered_map<std::string, stfr::PlatformKey> s_localizedKeymap;
    static bool s_MapInitialized = false;

    void InitializeLocalizedMap() {
        if (s_MapInitialized) { return; }

        // Special Keys
        s_localizedKeymap["Escape"] = GLFW_KEY_ESCAPE;
        s_localizedKeymap["Enter"] = GLFW_KEY_ENTER;
        s_localizedKeymap["Tab"] = GLFW_KEY_TAB;
        s_localizedKeymap["Space"] = GLFW_KEY_SPACE;
        s_localizedKeymap["Left Shift"] = GLFW_KEY_LEFT_SHIFT;
        s_localizedKeymap["Left Ctrl"] = GLFW_KEY_LEFT_CONTROL;
        s_localizedKeymap["Right Shift"] = GLFW_KEY_RIGHT_SHIFT;
        s_localizedKeymap["Right Ctrl"] = GLFW_KEY_RIGHT_CONTROL;

        // Gamepad Buttons
        // TODO

        // Loop through all localized printable keys
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
            const char* name = glfwGetKeyName(key, 0);
            if (name) { s_localizedKeymap[std::string(name)] = key; }
        }

        s_MapInitialized = true;
    }

    stfr::PlatformKey StringToPlatformKey_Localized(std::string_view str) {
        InitializeLocalizedMap();
        auto it = s_localizedKeymap.find(std::string(str));
        if (it != s_localizedKeymap.end()) { return it->second; }
        return stfr::PLATFORM_KEY_UNKNOWN;
    }

    std::string_view PlatformKeyToString_Localized(stfr::PlatformKey code) {
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
