#ifndef SYMBOL_HPP_
#define SYMBOL_HPP_

namespace Slots {
    enum class SymbolType {
        Cherry,
        Banana,
        Orange,
    };

    class Symbol {
    public:
        Symbol(const SymbolType st, const int order);

        void increase_offset(const float distance);

        const SymbolType type;
        float offset;
    };
} // namespace Slots

#endif // SYMBOL_HPP_
