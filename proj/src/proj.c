#include "proj.h"

extern menu* start_menu;

int main(int argc, char **argv) {
	sef_startup();
	vg_exit();//TODO ELIMINAR
	start();
	leave();
	return 0;
}

int start() {
	unsigned short character = 0x00;
	int ipc_status;
	message msg;
	int irq_set_kb = kb_subscribe_int();
	int irq_set_timer = timer_subscribe_int();
	int irq_set_mouse = mouse_subscribe_int();
	int r;
	unsigned char packet[3];
	unsigned short counter = 0;

	space_invaders_font = font_init("spaceinvader_font_transparent.bmp");
	srand(1);
	options_load();
	mouse_init();
	init_state();
	highscore_load();
	vg_init(VBE_VIDEO_MODE);

	while (1) { //TODO change condition
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kb) { /* keyboard interrupt */
					character = kb_int_handler();
					if (character != KB_2BYTE_SCODE)
						kb_event_handler(character);
				}
				if (msg.NOTIFY_ARG & irq_set_mouse){ /* mouse interrupt */
					mouse_int_handler(counter, packet);
					if(packet[0] != MOUSE_ACK && (packet[0] & BIT(3)))
						counter++;
					if(counter == 3){
						counter = 0;
						mouse_event_handler(packet);
					}

				}
				if (msg.NOTIFY_ARG & irq_set_timer){ /* timer interrupt */
					timer_int_handler();
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
		else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	return 0;
}

void leave(){
	timer_unsubscribe_int();
	kb_unsubscribe_int();
	mouse_unsubscribe_int();
	empty_out_buf();
	vg_exit();
	highscore_save();
	options_save();
	exit(0);
}
