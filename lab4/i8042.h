#define DELAY_US    20000
#define BIT(n) (0x01<<(n))
#define KB_IRQ 1
#define KBC_STATUS 0x64
#define KBC_COMMAND 0x64
#define KBC_OUT_BUF 0x60
#define KBC_IN_BUF 0x60
#define KBC_INBUF_FULL BIT(1)
#define KBC_OUTBUF_FULL BIT(0)
#define KBC_STAT_PARITY BIT(7)
#define KBC_STAT_TIMEOUT BIT(6)
#define KB_2BYTE_SCODE 0xE0
#define KB_LED_CMD 0xED
#define MOUSE_ACK 0xFA
#define RESEND 0xFE
#define ERROR 0xFC
#define MOUSE_IRQ 12
#define KBC_ENABLE_MOUSE 0xA8
#define WRITE_TO_MOUSE 0xD4
#define MOUSE_STATUS_REQUEST 0xE9
#define ENABLE_DATA_PACKETS 0xF4
#define MOUSE_RESET 0xFF
#define MOUSE_SET_DEFAULT 0xF6
#define DISABLE_STRM_MODE 0xF5
#define SET_SAMPLE_RATE 0xF3
#define SET_STREAM_MODE 0xEA
#define SET_RES 0xE8
#define SET_ACC_SCALE 0xE7
#define SET_LIN_SCALE 0xE6
