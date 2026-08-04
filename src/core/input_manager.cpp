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
        // TODO
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

    float InputManager::ReadValue(stfr::GeneralAction action) const {
        return EvaluateAction(m_GeneralActions[static_cast<size_t>(action)]);
    }

    float InputManager::ReadValue(stfr::CharacterAction action) const {
        return EvaluateAction(m_CharacterActions[static_cast<size_t>(action)]);
    }

    float InputManager::ReadValue(stfr::VehicleAction action) const {
        return EvaluateAction(m_VehicleActions[static_cast<size_t>(action)]);
    }

    bool InputManager::IsPressed(stfr::GeneralAction action) const {
        const auto& actionStruct = m_GeneralActions[static_cast<size_t>(action)];
        for (uint8_t i = 0; i < actionStruct.count; i++) {
            size_t idx = actionStruct.bindings[i].code;
            if (idx < MAX_INPUT_STATES && m_CurrentStates[idx] < 0.5f && m_PreviousStates[idx] <= 0.5f) {
                return true;
            }
        }
        return false;
    }

    bool InputManager::IsPressed(stfr::CharacterAction action) const {
        const auto& actionStruct = m_CharacterActions[static_cast<size_t>(action)];
        for (uint8_t i = 0; i < actionStruct.count; i++) {
            size_t idx = actionStruct.bindings[i].code;
            if (idx < MAX_INPUT_STATES && m_CurrentStates[idx] < 0.5f && m_PreviousStates[idx] <= 0.5f) {
                return true;
            }
        }
        return false;
    }

    bool InputManager::IsPressed(stfr::VehicleAction action) const {
        const auto& actionStruct = m_VehicleActions[static_cast<size_t>(action)];
        for (uint8_t i = 0; i < actionStruct.count; i++) {
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

    bool InputManager::IsHeld(stfr::CharacterAction action) const {
        return std::abs(ReadValue(action)) > 0.5f;
    }

    bool InputManager::IsHeld(stfr::VehicleAction action) const {
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

    bool InputManager::IsReleased(stfr::CharacterAction action) const {
        const auto& actionStruct = m_CharacterActions[static_cast<size_t>(action)];
        for (uint8_t i = 0; i < actionStruct.count; i++) {
            size_t idx = actionStruct.bindings[i].code;
            if (idx < MAX_INPUT_STATES && m_CurrentStates[idx] <= 0.5f && m_PreviousStates[idx] > 0.5f) {
                return true;
            }
        }
        return false;
    }

    bool InputManager::IsReleased(stfr::VehicleAction action) const {
        const auto& actionStruct = m_VehicleActions[static_cast<size_t>(action)];
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
        if (m_RebindContext != RebindContext::None && std::abs(value) > 0.5f) {
            if (m_RebindContext == RebindContext::General) {
                auto& actionStruct = m_GeneralActions[m_RebindActionId];
                actionStruct.bindings[m_RebindSlotIndex] = { code, m_RebindScale };
                if (actionStruct.count <= m_RebindSlotIndex) { actionStruct.count = m_RebindSlotIndex + 1; }
            } else if (m_RebindContext == RebindContext::Character) {
                auto& actionStruct = m_CharacterActions[m_RebindActionId];
                actionStruct.bindings[m_RebindSlotIndex] = { code, m_RebindScale };
                if (actionStruct.count <= m_RebindSlotIndex) { actionStruct.count = m_RebindSlotIndex + 1; }
            } else if (m_RebindContext == RebindContext::Vehicle) {
                auto& actionStruct = m_VehicleActions[m_RebindActionId];
                actionStruct.bindings[m_RebindSlotIndex] = { code, m_RebindScale };
                if (actionStruct.count <= m_RebindSlotIndex) { actionStruct.count = m_RebindSlotIndex + 1; }
            }
            m_RebindContext = RebindContext::None;
            SaveUserConfig();
            return;
        }
        if (code < MAX_INPUT_STATES) { m_CurrentStates[code] = value; }
    }

    void InputManager::Bind(stfr::GeneralAction action, stfr::InputCode code, float scale) {
        if (code == stfr::INPUT_UNKNOWN) { return; }
        auto& map = m_GeneralActions[static_cast<size_t>(action)];
        if (map.count < MAX_BINDINGS_PER_ACTION) { map.bindings[map.count++] = { code, scale }; }
    }

    void InputManager::Bind(stfr::CharacterAction action, stfr::InputCode code, float scale) {
        if (code == stfr::INPUT_UNKNOWN) { return; }
        auto& map = m_CharacterActions[static_cast<size_t>(action)];
        if (map.count < MAX_BINDINGS_PER_ACTION) { map.bindings[map.count++] = { code, scale }; }
    }

    void InputManager::Bind(stfr::VehicleAction action, stfr::InputCode code, float scale) {
        if (code == stfr::INPUT_UNKNOWN) { return; }
        auto& map = m_VehicleActions[static_cast<size_t>(action)];
        if (map.count < MAX_BINDINGS_PER_ACTION) { map.bindings[map.count++] = { code, scale }; }
    }

    void InputManager::BeginRebind(stfr::GeneralAction action, uint8_t slotIdx, float scale) {
        m_RebindContext = RebindContext::General;
        m_RebindActionId = static_cast<uint8_t>(action);
        m_RebindSlotIndex = slotIdx;
        m_RebindScale = scale; // keep track if we are mapping the negative or positive side of the axis
    }

    void InputManager::BeginRebind(stfr::CharacterAction action, uint8_t slotIdx, float scale) {
        m_RebindContext = RebindContext::Character;
        m_RebindActionId = static_cast<uint8_t>(action);
        m_RebindSlotIndex = slotIdx;
        m_RebindScale = scale; // keep track if we are mapping the negative or positive side of the axis
    }

    void InputManager::BeginRebind(stfr::VehicleAction action, uint8_t slotIdx, float scale) {
        m_RebindContext = RebindContext::Vehicle;
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
