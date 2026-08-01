#pragma once

#include <cstdint>

namespace stfr {

    using PlatformKey = uint16_t;
    using PlatformAxis = uint16_t;

    constexpr PlatformKey PLATFORM_KEY_UNKNOWN = 0xFFFFFFFF;

    enum class GeneralAction : uint8_t {
        Unknown = 0,
        Pause,
        Count
    };

    enum class CharacterAction : uint8_t {
        Unknown = 0,
        Jump,
        Interact,
        Sprint,
        Croutch,
        Count
    };

    enum class CharacterAxis : uint8_t {
        Unknown = 0,
        MoveForward,
        MoveBackward,
        MoveLeft,
        MoveRight,
        Count
    };

    enum class VehicleAction : uint8_t {
        Unknown = 0,
        Engine,
        Handbreak,
        Headlights,
        Horn,
        Count
    };

    enum class VehicleAxis : uint8_t {
        Unknown = 0,
        Accelerate,
        Brake,
        SteerLeft,
        SteerRight,
        Count
    };

}
