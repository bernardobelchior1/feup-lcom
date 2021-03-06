#ifndef RTC_H
#define RTC_H

#define BIT(n) (0x01<<(n))
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_UIP BIT(7)
#define RTC_BINARY BIT(2)

#define RTC_SECONDS_REG 0
#define RTC_SECONDS_ALARM_REG 1
#define RTC_MINUTES_REG 2
#define RTC_MINUTES_ALARM_REG 3
#define RTC_HOURS_REG 4
#define RTC_HOURS_ALARM_REG 5
#define RTC_DAY_OF_WEEK_REG 6
#define RTC_DAY_REG 7
#define RTC_MONTH_REG 8
#define RTC_YEAR_REG 9
#define RTC_REGISTER_A 10
#define RTC_REGISTER_B 11

/** @defgroup rtc rtc
 * @{
 * rtc
 */

typedef struct {
	unsigned long day, month, year;
} Date;

/**
 * @brief Checks if there is an update in progress
 *
 * @return Returns 0 if there is an update in progress, returning non-zero otherwise
 */
int can_access_RTC_reg();

/**
 * @brief Reads from RTC's registers
 *
 * @param address Address of the register to read from
 * @param result Where to store the result
 *
 * @return Returns 0 on success, returning non-zero otherwise
 */
int read_from_RTC(unsigned char address, unsigned long *result);

/**
 * @brief Writes to RTC's registers
 *
 * @param address Address of the register to write to
 * @param write What to write
 *
 * @param Returns 0 on success, returning non-zero otherwise
 */
int write_to_RTC(unsigned char address, unsigned long write);

/**
 * @brief Checks if the rtc is binary
 *
 * @return Returns whether or not the rtc is in binary
 */
int is_rtc_binary();

/**
 * @brief Converts a bcd number to binary
 *
 * @param bcd Binary coded decimal number
 *
 * @returne Returns converted number
 */
unsigned long convert_to_binary(unsigned long bcd);

/**
 * @brief Gets today's date
 *
 * @return Returns today's date
 */
Date* get_todays_date();

#endif
