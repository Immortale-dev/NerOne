#ifndef NN_NERCELLTYPE
#define NN_NERCELLTYPE

#define DEFINE_CELL_TYPE(name) constexpr auto name = __COUNTER__

namespace nerone {
	namespace CellType {
		class Type {
			public:
				explicit constexpr Type(uint8_t value): value(value){}
				constexpr Type() = default;
				~Type() = default;
				constexpr explicit Type(const Type &) = default;
				constexpr Type &operator=(const Type &) = default;

			private:
				uint8_t value;
		}
	}
}

#endif NN_NERCELLTYPE