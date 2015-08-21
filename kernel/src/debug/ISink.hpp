#pragma once

namespace AgaresOS { namespace Debug {
	class ISink {
		public:
			virtual void PutCharacter(char c) = 0;
	};
}}
