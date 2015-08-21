#pragma once
#include "ISink.hpp"

namespace AgaresOS { namespace Debug {
	class IDebugFragment {
		public:
			virtual void WriteTo(ISink &sink) const = 0;
	};
}}
