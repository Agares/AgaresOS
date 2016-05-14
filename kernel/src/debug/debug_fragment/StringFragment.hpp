#pragma once
#include "../IDebugFragment.hpp"

namespace AgaresOS { namespace Debug {
	class StringFragment : public IDebugFragment {
		public:
			StringFragment(const char *const value) : value(value) {
			}
			
			void WriteTo(ISink &sink) const;
		private:
			const char *const value;
	};

	inline void StringFragment::WriteTo(ISink &sink) const {
		for (int i = 0; value[i] != '\0'; i++) {
			sink.PutCharacter(value[i]);
		}	
	}

	DebugOutput &operator<<(DebugOutput &sink, const char *const value) {
		return sink << StringFragment(value);
	}
}}
