#include <stdexcept>
#include <iostream>

#include "symbol.hpp"
#include "../util/constants.hpp"

namespace {
    int calculate_symbol_offset(const int order) {
        const int rcp = Slots::Constants::reel_center_percent;
        const int sdp = Slots::Constants::symbols_distance_percent;

        return rcp + ((order - 1) * sdp);
    }
}

namespace Slots {
    Symbol::Symbol(const SymbolType st, const int order) :
        type { st },
        offset { calculate_symbol_offset(order) }
    { }

    void Symbol::increase_offset(const float distance) {
        offset += distance;
        if (offset - Constants::symbol_height_percent / 2.0 > 100.0f) {
            offset = offset - 100.0f;
        }
    }
} // namespace Slots
