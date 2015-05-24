#include "module.h"
#include "tag.h"
#include "../early/log.h"
#include <stddef.h>

static multiboot_module modules[64];
static int modules_current = 0;

multiboot_module *
multiboot_module_read_next(struct multiboot_tag *multiboot_tags) {
	struct multiboot_tag *tag = multiboot_find_next_tag(MULTIBOOT_TAG_TYPE_MODULE, multiboot_tags);
	struct multiboot_tag_module *module_tag = (struct multiboot_tag_module *)tag;
	
	LOG("= Found module\n");
	LOG("== Start address: ");
	LOG_NUMBER_HEX((int)module_tag->mod_start);
	LOG("== End address: ");
	LOG_NUMBER_HEX((int)module_tag->mod_end);
	LOG("== Command line: ");
	LOG(module_tag->cmdline);
	LOG("\n= Module end\n");

	modules[modules_current].load_address = (void *)module_tag->mod_start;
	modules[modules_current].size = module_tag->mod_end - module_tag->mod_start;
	modules_current++;
	return &modules[modules_current-1];
}
