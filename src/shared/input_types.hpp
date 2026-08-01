#pragma once

#include <cstdint>

namespace stfr {

    using InputCode = uint16_t;

    constexpr InputCode INPUT_UNKNOWN = 0xFFFFFFFF;

    enum class GeneralAction : uint8_t {
        Unknown = 0,
        Pause,
        Count
    };

    enum class CharacterAction : uint8_t {
        Unknown = 0,
        MoveForward,
        MoveBackward,
        MoveLeft,
        MoveRight,
        Jump,
        Interact,
        Sprint,
        Croutch,
        Count
    };

    enum class VehicleAction : uint8_t {
        Unknown = 0,
        Accelerate,
        Brake,
        SteerLeft,
        SteerRight,
        Engine,
        Handbreak,
        Headlights,
        Horn,
        Count
    };

}
