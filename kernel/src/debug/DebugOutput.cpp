#include "DebugOutput.hpp"

using AgaresOS::Debug::DebugOutput;
using AgaresOS::Debug::ISink;

DebugOutput::DebugOutput(ISink &sink) : sink(sink) {
}

DebugOutput &DebugOutput::operator<<(const IDebugFragment &fragment) {
	fragment.WriteTo(sink);

	return *this;
}
