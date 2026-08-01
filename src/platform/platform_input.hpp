#pragma once

#include <string_view>

#include "shared/stfr_api.hpp"
#include "shared/input_types.hpp"

namespace stfr_platform {

    // Assumes strings are standard physical QWERTY locations
    STFR_API stfr::PlatformKey StringToPlatformKey_Physical(std::string_view str);
    // Uses OS Language detection
    STFR_API stfr::PlatformKey StringToPlatformKey_Localized(std::string_view str);
    // Writes the localized name
    STFR_API std::string_view PlatformKeyToString_Localized(stfr::PlatformKey code);

    STFR_API stfr::PlatformAxis StringToPlatformAxis(std::string_view str);
    STFR_API std::string_view PlatformAxisToString(stfr::PlatformAxis code);

}
