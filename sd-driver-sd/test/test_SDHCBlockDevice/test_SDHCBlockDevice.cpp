#include "mbed.h"
#include "SDHCBlockDevice.h"

#include "test_SDHCBlockDevice.h"

#define BLOCK_SIZE FSL_SDMMC_DEFAULT_BLOCK_SIZE

#define DATA_BLOCK_COUNT (5U)
#define DATA_START_ADDR (2U * BLOCK_SIZE)
#define DATA_BUFFER_SIZE (FSL_SDMMC_DEFAULT_BLOCK_SIZE * DATA_BLOCK_COUNT)

static SDHCBlockDevice sd;

static uint8_t g_dataWrite[DATA_BUFFER_SIZE];
static uint8_t g_dataRead[DATA_BUFFER_SIZE];

int test_SDHCBlockDevice(void)
{
	if (sd.init()){
		printf("err: SDHC init failed.\r\n");
		return -1;
	}

	memset(g_dataWrite, 0x67U, sizeof(g_dataWrite));

	printf("\r\nWrite/read one data block......\r\n");
	if (sd.program(g_dataWrite, DATA_START_ADDR, BLOCK_SIZE)){
		printf("err: SDHC write failed.\r\n");
		return -1;
	}

	memset(g_dataRead, 0U, sizeof(g_dataRead));
	if (sd.read(g_dataRead, DATA_START_ADDR, BLOCK_SIZE)){
		printf("err: SDHC read failed.\r\n");
		return -1;
	}

	printf("Compare the read/write content......\r\n");
	if (memcmp(g_dataRead, g_dataWrite, BLOCK_SIZE)) {
		printf("The read/write content isn't consistent.\r\n");
		return -1;
	}
	printf("The read/write content is consistent.\r\n");


	printf("Write/read multiple data blocks......\r\n");
	if (sd.program(g_dataWrite, DATA_START_ADDR, DATA_BUFFER_SIZE)){
		printf("err: SDHC write failed.\r\n");
		return -1;
	}

	memset(g_dataRead, 0U, sizeof(g_dataRead));
	if (sd.read(g_dataRead, DATA_START_ADDR, DATA_BUFFER_SIZE)){
		printf("err: SDHC read failed.\r\n");
		return -1;
	}

	printf("Compare the read/write content......\r\n");
	if (memcmp(g_dataRead, g_dataWrite, BLOCK_SIZE)) {
		printf("The read/write content isn't consistent.\r\n");
		return -1;
	}
	printf("The read/write content is consistent.\r\n");


	printf("Erase multiple data blocks......\r\n");
	if (sd.erase(DATA_START_ADDR, DATA_BUFFER_SIZE)){
		printf("err: SDHC erase failed.\r\n");
		return -1;
	}

	printf("\r\nSDHC driver test finished.\r\n");

	sd.deinit();

	return 0;
}
