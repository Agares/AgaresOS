#pragma once

void mm_set_top(void *end);
void mm_mark_as_used(void *start, void *end);
void *mm_find_hole(int pages);
void *mm_get_map(void);
