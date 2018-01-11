/**
 * Test function for SD Card SD Bus mode driver
 */
#include <stdio.h>
#include "mbed.h"
#include "sd_pin_mux.h"
#include "fsl_card.h"
#include "fsl_mpu.h"

#include "test_sdhc_driver.h"

/*! @brief Data block count accessed in card */
#define DATA_BLOCK_COUNT (5U)
/*! @brief Start data block number accessed in card */
#define DATA_BLOCK_START (2U)
/*! @brief Data buffer size. */
#define DATA_BUFFER_SIZE (FSL_SDMMC_DEFAULT_BLOCK_SIZE * DATA_BLOCK_COUNT)

/*! @brief Card descriptor. */
sd_card_t g_sd;

/*! @brief Data written to the card */
static uint8_t g_dataWrite[DATA_BUFFER_SIZE];
/*! @brief Data read from the card */
static uint8_t g_dataRead[DATA_BUFFER_SIZE];

int test_sdhc_driver(void)
{
	sd_card_t *card = &g_sd;
	bool isReadOnly;

	SD_InitPins();

	// MPU must be enable, or the SD card will init failed
	MPU_Enable(MPU, false);

	card->host.base = SD_HOST_BASEADDR;
	card->host.sourceClock_Hz = SD_HOST_CLK_FREQ;

	/* Init card. */
	if (SD_Init(card)) {
		printf("\r\nSD card init failed.\r\n");
		return -1;
	}

	printf("\r\nTest start. Read/Write/Erase the card......\r\n");
	/* Check if card is readonly. */
	isReadOnly = SD_CheckReadOnly(card);
	if (isReadOnly) {
		printf("\r\nRead one data block......\r\n");
		if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, DATA_BLOCK_START, 1U)) {
			printf("Read one data block failed.\r\n");
			return -1;
		}

		printf("Read multiple data blocks......\r\n");
		if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, DATA_BLOCK_START, DATA_BLOCK_COUNT)) {
			printf("Read multiple data blocks failed.\r\n");
			return -1;
		}
	} else {
		memset(g_dataWrite, 0x67U, sizeof(g_dataWrite));

		printf("\r\nWrite/read one data block......\r\n");
		if (kStatus_Success != SD_WriteBlocks(card, g_dataWrite, DATA_BLOCK_START, 1U)) {
			printf("Write one data block failed.\r\n");
			return -1;
		}

		memset(g_dataRead, 0U, sizeof(g_dataRead));
		if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, DATA_BLOCK_START, 1U)) {
			printf("Read one data block failed.\r\n");
			return -1;
		}

		printf("Compare the read/write content......\r\n");
		if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE)) {
			printf("The read/write content isn't consistent.\r\n");
			return -1;
		}
		printf("The read/write content is consistent.\r\n");

		printf("Write/read multiple data blocks......\r\n");
		if (kStatus_Success != SD_WriteBlocks(card, g_dataWrite, DATA_BLOCK_START, DATA_BLOCK_COUNT)) {
			printf("Write multiple data blocks failed.\r\n");
			return -1;
		}

		memset(g_dataRead, 0U, sizeof(g_dataRead));

		if (kStatus_Success != SD_ReadBlocks(card, g_dataRead, DATA_BLOCK_START, DATA_BLOCK_COUNT)) {
			printf("Read multiple data blocks failed.\r\n");
			return -1;
		}

		printf("Compare the read/write content......\r\n");
		if (memcmp(g_dataRead, g_dataWrite, FSL_SDMMC_DEFAULT_BLOCK_SIZE)) {
			printf("The read/write content isn't consistent.\r\n");
			return -1;
		}
		printf("The read/write content is consistent.\r\n");

		printf("Erase multiple data blocks......\r\n");
		if (kStatus_Success != SD_EraseBlocks(card, DATA_BLOCK_START, DATA_BLOCK_COUNT)) {
			printf("Erase multiple data blocks failed.\r\n");
			return -1;
		}
	}
	printf("\r\nSD card SD bus mode driver test finished.\r\n");

	SD_Deinit(card);

	return 0;
}
