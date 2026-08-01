#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string_view>

#include "input_manager.hpp"
#include "shared/input_types.hpp"

namespace stfr_core {

    void InputManager::Initialize(std::string_view userConfigPath) {
        m_UserConfigPath = std::string(userConfigPath);
        LoadHardcodedDefaults();

        if (std::filesystem::exists(m_UserConfigPath)) { LoadUserConfig(); }
        else { SaveUserConfig(); }
    }

    void InputManager::LoadHardcodedDefaults() {
        
    }
    
    float InputManager::EvaluateAction(const VirtualAction& actionStruct) const {
        float finalValue = 0.0f;
        for (uint8_t i = 0; i < actionStruct.count; i++) {
            const auto& binding = actionStruct.bindings[i];
            if (binding.code < MAX_INPUT_STATES) {
                finalValue += m_CurrentStates[binding.code] * binding.scale;
            }
        }
        return std::clamp(finalValue, -1.0f, 1.0f);
    }

    float InputManager::ReadValue(stfr::GeneralAction action) const { return EvaluateAction(m_GeneralActions[static_cast<size_t>(action)]); }

    bool InputManager::IsPressed(stfr::GeneralAction action) const {
        const auto& actionStruct = m_GeneralActions[static_cast<size_t>(action)];
        for (uint8_t i = 0; actionStruct.count; i++) {
            size_t idx = actionStruct.bindings[i].code;
            if (idx < MAX_INPUT_STATES && m_CurrentStates[idx] < 0.5f && m_PreviousStates[idx] <= 0.5f) {
                return true;
            }
        }
        return false;
    }

    bool InputManager::IsHeld(stfr::GeneralAction action) const {
        return std::abs(ReadValue(action)) > 0.5f;
    }

    bool InputManager::IsReleased(stfr::GeneralAction action) const {
        const auto& actionStruct = m_GeneralActions[static_cast<size_t>(action)];
        for (uint8_t i = 0; i < actionStruct.count; i++) {
            size_t idx = actionStruct.bindings[i].code;
            if (idx < MAX_INPUT_STATES && m_CurrentStates[idx] <= 0.5f && m_PreviousStates[idx] > 0.5f) {
                return true;
            }
        }
        return false;
    }

    void InputManager::Update() {
        m_PreviousStates = m_CurrentStates;
    }

    void InputManager::OnInputEvent(stfr::InputCode code, float value) {
        // TODO
        if (code < MAX_INPUT_STATES) { m_CurrentStates[code] = value; }
    }

    void InputManager::Bind(stfr::GeneralAction action, stfr::InputCode code, float scale) {
        if (code == stfr::INPUT_UNKNOWN) { return; }
        auto& map = m_GeneralActions[static_cast<size_t>(action)];
        if (map.count < MAX_BINDINGS_PER_ACTION) { map.bindings[map.count++] = { code, scale }; }
    }

    void InputManager::BeginRebind(stfr::GeneralAction action, uint8_t slotIdx, float scale) {
        m_RebindContext = RebindContext::General;
        m_RebindActionId = static_cast<uint8_t>(action);
        m_RebindSlotIndex = slotIdx;
        m_RebindScale = scale; // keep track if we are mapping the negative or positive side of the axis
    }

    void InputManager::CancelRebind() {
        m_RebindContext = RebindContext::None;
    }

    void InputManager::SaveUserConfig() const {
        // TODO : TOML SERIALIZATION
    }

    void InputManager::LoadUserConfig() {
        // TODO : TOML PARSING
    }

}
