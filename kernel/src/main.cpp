#include <stdint.h>
#include <video/video.hpp>
#include <debug/VideoSink.hpp>
#include <debug/DebugOutput.hpp>
#include <debug/debug_fragment/StringFragment.hpp>
#include <debug/debug_fragment/IntegerFragment.hpp>

using AgaresOS::Debug::VideoSink;
using AgaresOS::Debug::DebugOutput;
using AgaresOS::Debug::StringFragment;
using AgaresOS::Debug::IntegerFragment;
using AgaresOS::Video;

extern "C" void __cxa_pure_virtual() {
	// fixme add kernel panic
}

extern "C" int kmain(uint32_t memoryMapAddress) {
	Video video;
	VideoSink sink(video);
	DebugOutput output(sink);

	video.Clear();
	output << "Hello from AgaresOS kernel!";
	output << "We can print numbers! \n";
	output << "Hex (default): " << 987 << "\n";
	output << "Decimal      : " << IntegerFragment(987, 10) << "\n";
	output << "Binary       : " << IntegerFragment(987, 2) << "\n";
	output << "The memory map is located at: 0x" << memoryMapAddress << "\n";

	while(true) {}
}
