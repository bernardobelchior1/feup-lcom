#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"
#include "timer.h"

int timer_set_square(unsigned long timer, unsigned long freq) {

	unsigned int n = TIMER_FREQ / freq;

	char lsb = (char) n;
	char msb = (char) n >> 8;

	sys_outb(TIMER_CTRL, TIMER_SEL0 | TIMER_LSB_MSB | TIMER_SQR_WAVE | TIMER_BIN);
	sys_outb(TIMER_0, n);
	sys_outb(TIMER_0, 0x00);

	return 1;
}

int timer_subscribe_int(void ) {

	return 1;
}

int timer_unsubscribe_int() {

	return 1;
}

void timer_int_handler() {

}

int timer_get_conf(unsigned long timer, unsigned char *st) {
	char read = TIMER_RB_CMD | TIMER_RB_SEL(timer);
	char memory;
	unsigned long conf;

	switch(timer){
		case 0:
			memory = TIMER_0;
			break;
		case 1:
			memory = TIMER_1;
			break;
		case 2:
			memory = TIMER_2;
			break;
	}

	sys_outb(TIMER_CTRL, read);
	int ret = sys_outb(memory, &conf);
	*st = (char) conf;
	return ret;
}

int timer_display_conf(unsigned char conf) {
	
	printf("Output: %d\n", (conf & 0x80) >> 7 );
	printf("Null Count: %d\n", (conf & 0x40) >> 6 );
	printf("Type of Access: ");

	if(conf & 0x30 == 0x30)
			printf("LSB followed by MSB\n");
		else if (conf & 0x20 == 0x20)
			printf("MSB\n");
		else
			printf("LSB\n");

	printf("Programmed Mode: " );

	switch((conf & 0x0E) >> 1){
	case 0x00: printf("Interrupt on Terminal Count");
		break;
	case 0x01: printf("Hardware Retriggerable One-Shot");
		break;
	case 0x02: printf("Rate Generator");
		break;
	case 0x03: printf("Square Wave Mode");
		break;
	case 0x04: printf("Software Triggered Strobe");
			break;
	case 0x05: printf("Hardware Triggered Strobe (Retriggerable)");
			break;
	}

	printf("\n");
	printf("BCD: %s", (conf & 0x01) ? "BCD\n" : "Binary\n");

	return 0;
}

int timer_test_square(unsigned long freq) {
	timer_set_square(0, freq);
}

int timer_test_int(unsigned long time) {
	
	return 1;
}

int timer_test_config(unsigned long timer) {
	unsigned char st;
	timer_get_conf(timer, &st);
	timer_display_conf(st);
	
	return 1;
}
