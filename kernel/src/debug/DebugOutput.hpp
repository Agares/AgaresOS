#pragma once
#include "ISink.hpp"
#include "IDebugFragment.hpp"

namespace AgaresOS { namespace Debug {
	class DebugOutput {
		public:
			DebugOutput(ISink &sink);

			DebugOutput &operator <<(const IDebugFragment &fragment);
		private:
			ISink &sink;
	};
}}
