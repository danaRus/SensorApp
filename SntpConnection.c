#include "BCDS_NetworkConfig.h"
#include "Serval_Sntp.h"
#include "Serval_Clock.h"

// SNTP server connection properties
#define SNTP_DEFAULT_PORT		UINT16_C(123)
#define SNTP_DEFAULT_ADDRESS	"0.de.pool.ntp.org"

static uint32_t timeOffset = 0;

static void onTimeReceive(Ip_Address_T* sourceIp, Ip_Port_T sourcePort, uint32_t timestamp) {
	uint32_t clockTimestamp;
	Clock_getTime(&clockTimestamp);
	timeOffset = timestamp - clockTimestamp;
	printf("SNTP timestamp: %lu\n\r", timestamp);
	printf("Current time offset: %lu\n\r", timeOffset);
}

static void onSent(Msg_T *msg_ptr, retcode_t status) {
	printf("Sent status: %d\n\r", status);
}

/**
 * Return the UNIX Epoch Time (GMT).
 */
void setupTimeThroughSntp(void) {
	Sntp_initialize();
	Sntp_start(Ip_convertIntToPort(123), onTimeReceive);

	Ip_Address_T destinationAddress;
	NetworkConfig_GetIpAddress((uint8_t *) SNTP_DEFAULT_ADDRESS, &destinationAddress);

	Sntp_getTime(&destinationAddress, Ip_convertIntToPort(SNTP_DEFAULT_PORT), onSent);
}

/**
 * Return the current time, while also ensuring that the seconds are a multiple of 10.
 * This is needed due to the fact that for the Proof of Concept, data will be analyzed
 * and considered only at certain time intervals.
 */
uint32_t getCurrentTime(void) {
	uint32_t clockTimestamp;
	Clock_getTime(&clockTimestamp);
	uint32_t timestamp;
	timestamp = clockTimestamp + timeOffset;
	while (timestamp % 10 != 0) {
		Clock_getTime(&clockTimestamp);
		timestamp = clockTimestamp + timeOffset;
	}
	printf("Current timestamp: %lu\n\r", timestamp);
	return timestamp;
}
