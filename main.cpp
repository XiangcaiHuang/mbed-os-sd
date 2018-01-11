#include "test_sdhc_driver.h"
#include "test_SDHCBlockDevice.h"
#include "test_SD_FATFS.h"

// #define TEST_SDHC_DRIVER
// #define TEST_SDHC_BLOCK_DEVICE
#define TEST_SD_FATFS

int main(void)
{
#ifdef TEST_SDHC_DRIVER
	if (test_sdhc_driver()){
		return -1;
		printf("err: SDHC test failed.\r\n");
	}
#endif

#ifdef TEST_SDHC_BLOCK_DEVICE
	if (test_SDHCBlockDevice()){
		return -1;
		printf("err: SDHCBlockDevice test failed.\r\n");
	}
#endif

#ifdef TEST_SD_FATFS
	test_SD_FATFS();
#endif

	return 0;
}
