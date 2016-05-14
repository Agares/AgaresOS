#pragma once
#include "../IDebugFragment.hpp"
#include <stdint.h>

namespace AgaresOS { namespace Debug {
	class IntegerFragment : public IDebugFragment {
		public:
			IntegerFragment(uintmax_t value, uint8_t base = 16) 
				: base(base), value(value), is_signed(false) {
			}
			
			void WriteTo(ISink &sink) const;
			void SetBase(uint8_t base);
		private:
			uint8_t base;
			intmax_t value;

			bool is_signed;
	};

	inline void IntegerFragment::WriteTo(ISink &sink) const {
		char buffer[sizeof(intmax_t) * 8];

		for(unsigned int i = 0; i < sizeof(intmax_t); i++) {
			buffer[i] = ' ';
		}

		uintmax_t unsigned_value = is_signed 
				? (value < 0 ? -value : value)
				: static_cast<uintmax_t>(value);
		unsigned int index = 0;

		do {
			buffer[index++] = "0123456789ABCDEFGHIJKLMNOPQRSTUWXYZ"[unsigned_value % base];
		} while((unsigned_value /= base) != 0);

		do {
			index--;
			sink.PutCharacter(buffer[index]);
		} while (index > 0);
	}

	inline void IntegerFragment::SetBase(uint8_t base) {
		this->base = base;
	}

	inline DebugOutput &operator<<(DebugOutput &output, uintmax_t value) {
		return output << IntegerFragment(value);
	}
}}
