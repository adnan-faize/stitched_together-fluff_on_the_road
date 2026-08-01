#pragma once

#include <cstdint>
#include <string_view>
#include <string>
#include <array>

#include "shared/stfr_api.hpp"
#include "shared/input_types.hpp"

namespace stfr_core {

    constexpr size_t MAX_KEYS = 512;
    constexpr size_t MAX_AXES = 32;
    constexpr uint8_t MAX_BINDINGS_PER_ACTION = 4;

    struct ActionBinding {
        uint8_t count = 0;
        std::array<stfr::PlatformKey, MAX_BINDINGS_PER_ACTION> keys {};
    };

    struct AxisBinding {
        uint8_t count = 0;
        std::array<stfr::PlatformAxis, MAX_BINDINGS_PER_ACTION> axes {};
    };

    enum class RebindContext : uint8_t {
        None = 0,
        General,
        Character,
        Vehicle
    };

    class STFR_API InputManager {
        public:
            void Initialize(std::string_view userConfigPath);
            void SaveUserConfig() const;
            void Update();

            bool IsActionPressed(stfr::GeneralAction action) const;
            bool IsActionPressed(stfr::CharacterAction action) const;
            bool IsActionPressed(stfr::VehicleAction action) const;

            bool IsActionHeld(stfr::GeneralAction action) const;
            bool IsActionHeld(stfr::CharacterAction action) const;
            bool IsActionHeld(stfr::VehicleAction action) const;

            bool IsActionReleased(stfr::GeneralAction action) const;
            bool IsActionReleased(stfr::CharacterAction action) const;
            bool IsActionReleased(stfr::VehicleAction action) const;

            float GetAxis(stfr::CharacterAxis axis) const;
            float GetAxis(stfr::VehicleAxis axis) const;

            // Event hooks
            void OnKeyEvent(stfr::PlatformKey key, int action);
            void OnAxisEvent(stfr::PlatformAxis axis, float value);

            void BeginRebind(stfr::GeneralAction action, uint8_t slotIdx = 0);
            void BeginRebind(stfr::CharacterAction action, uint8_t slotIdx = 0);
            void BeginRebind(stfr::VehicleAction action, uint8_t slotIdx = 0);
            void CancelRebind();
            bool IsRebinding() const { return m_RebindContext != RebindContext::None; }

        private:
            void LoadHardcodedDefaults();
            void LoadUserConfig();

            void BindAction(stfr::GeneralAction action, stfr::PlatformKey key);
            void BindAction(stfr::CharacterAction action, stfr::PlatformKey key);
            void BindAction(stfr::VehicleAction action, stfr::PlatformKey key);
            void CompleteRebind(stfr::PlatformKey key);

            std::string m_UserConfigPath;

            std::array<ActionBinding, static_cast<size_t>(stfr::GeneralAction::Count)>   m_GeneralActions {};
            std::array<ActionBinding, static_cast<size_t>(stfr::CharacterAction::Count)> m_CharacterActions {};
            std::array<ActionBinding, static_cast<size_t>(stfr::VehicleAction::Count)>   m_VehicleActions {};

            std::array<AxisBinding, static_cast<size_t>(stfr::CharacterAxis::Count)>     m_CharacterAxes {};
            std::array<AxisBinding, static_cast<size_t>(stfr::VehicleAxis::Count)>       m_VehicleAxes {};

            std::array<bool, MAX_KEYS> m_CurrentKeys {};
            std::array<bool, MAX_KEYS> m_PreviousKeys {};
            std::array<float, MAX_AXES> m_AxisStates {};

            RebindContext m_RebindContext = RebindContext::None;
            uint8_t m_RebindActionId = 0;
            uint8_t m_RebindSlotIndex = 0;
    };

}
