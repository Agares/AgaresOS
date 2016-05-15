#include <stdint.h>
#include <video/video.hpp>
#include <debug/VideoSink.hpp>
#include <debug/DebugOutput.hpp>
#include <debug/debug_fragment/StringFragment.hpp>
#include <debug/debug_fragment/IntegerFragment.hpp>
#include "early/bootloader_information.hpp"

using AgaresOS::Debug::VideoSink;
using AgaresOS::Debug::DebugOutput;
using AgaresOS::Debug::StringFragment;
using AgaresOS::Debug::IntegerFragment;
using AgaresOS::Video;
using AgaresOS::Early::BootloaderInformation;

extern "C" void __cxa_pure_virtual() {
	// fixme add kernel panic
}

extern "C" int kmain(const uint32_t bootloaderInfoAddress) {
	Video video;
	VideoSink sink(video);
	DebugOutput output(sink);

	video.Clear();
	output << "Hello from AgaresOS kernel!\n";
	output << "We can print numbers! \n";
	output << "Hex (default): " << 987 << "\n";
	output << "Decimal      : " << IntegerFragment(987, 10) << "\n";
	output << "Binary       : " << IntegerFragment(987, 2) << "\n";

	// fixme this is just debug code
	BootloaderInformation *bi = reinterpret_cast<BootloaderInformation *>(bootloaderInfoAddress);
	output << bi->Version << "\n" << bi->BootloaderTag << "\n";

	for(int i = 0; i < 64; i++) {
		if(bi->MemoryMap[i].EndAddress == 0) {
			continue;
		}

		output << bi->MemoryMap[i].StartAddress
				<< " "
				<< bi->MemoryMap[i].EndAddress
				<< " (" << (uintmax_t)bi->MemoryMap[i].Type << ")\n";
	}

	while(true) {}
}
