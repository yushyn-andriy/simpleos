#include "idt.h"
#include "config.h"
#include "memory/memory.h"

struct id_desc idt_descriptors[SIMPLEOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;


void idt_init() {
	memset(idt_descriptors, 0, sizeof(idt_descriptors));
}

