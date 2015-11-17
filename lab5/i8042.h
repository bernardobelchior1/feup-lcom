#define DELAY_US    20000
#define BIT(n) (0x01<<(n))
#define KB_IRQ 1
#define KB_STATUS 0x64
#define KBC_COMMAND 0x64
#define KB_OUT_BUF 0x60
#define KB_IN_BUF 0x60
#define KB_INBUF_FULL BIT(1)
#define KB_OUTBUF_FULL BIT(0)
#define KB_STAT_PARITY BIT(7)
#define KB_STAT_TIMEOUT BIT(6)
#define KB_2BYTE_SCODE 0xE0
#define KB_LED_CMD 0xED
#define ACK 0xFA
#define RESEND 0xFE
#define ERROR 0xFC