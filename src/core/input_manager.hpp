#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <string>

#include "shared/stfr_api.hpp"
#include "shared/input_types.hpp"

namespace stfr_core {

    constexpr size_t MAX_INPUT_STATES = 512;
    constexpr uint8_t MAX_BINDINGS_PER_ACTION = 4;

    struct InputBinding {
        stfr::InputCode code = stfr::INPUT_UNKNOWN;
        float scale = 1.0f;
    };

    struct VirtualAction {
        uint8_t count = 0;
        std::array<InputBinding, MAX_BINDINGS_PER_ACTION> bindings {};
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

            bool IsPressed(stfr::GeneralAction action) const;
            bool IsPressed(stfr::CharacterAction action) const;
            bool IsPressed(stfr::VehicleAction action) const;

            bool IsHeld(stfr::GeneralAction action) const;
            bool IsHeld(stfr::CharacterAction action) const;
            bool IsHeld(stfr::VehicleAction action) const;

            bool IsReleased(stfr::GeneralAction action) const;
            bool IsReleased(stfr::CharacterAction action) const;
            bool IsReleased(stfr::VehicleAction action) const;

            float ReadValue(stfr::GeneralAction action) const;
            float ReadValue(stfr::CharacterAction action) const;
            float ReadValue(stfr::VehicleAction action) const;

            // Event hooks
            void OnInputEvent(stfr::InputCode code, float value);

            void BeginRebind(stfr::GeneralAction action, uint8_t slotIdx, float scale = 1.0f);
            void BeginRebind(stfr::CharacterAction action, uint8_t slotIdx, float scale = 1.0f);
            void BeginRebind(stfr::VehicleAction action, uint8_t slotIdx, float scale = 1.0f);
            void CancelRebind();
            bool IsRebinding() const { return m_RebindContext != RebindContext::None; }

        private:
            void LoadHardcodedDefaults();
            void LoadUserConfig();

            void Bind(stfr::GeneralAction action, stfr::InputCode code, float scale);
            void Bind(stfr::CharacterAction action, stfr::InputCode code, float scale);
            void Bind(stfr::VehicleAction action, stfr::InputCode code, float scale);

            float EvaluateAction(const VirtualAction& actionStruct) const;

        private:
            std::string m_UserConfigPath;

            std::array<VirtualAction, static_cast<size_t>(stfr::GeneralAction::Count)>   m_GeneralActions {};
            std::array<VirtualAction, static_cast<size_t>(stfr::CharacterAction::Count)> m_CharacterActions {};
            std::array<VirtualAction, static_cast<size_t>(stfr::VehicleAction::Count)>   m_VehicleActions {};

            std::array<bool, MAX_INPUT_STATES> m_CurrentStates {};
            std::array<bool, MAX_INPUT_STATES> m_PreviousStates {};

            RebindContext m_RebindContext = RebindContext::None;
            uint8_t m_RebindActionId = 0;
            uint8_t m_RebindSlotIndex = 0;
            float m_RebindScale = 1.0f;
    };

}
