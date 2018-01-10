#include "test_sdhc_driver.h"
#include "test_SDHCBlockDevice.h"
#include "test_SD_FATFS.h"

int main(void)
{
	// if (test_sdhc_driver()){
	// 	return -1;
	// 	printf("err: SDHC test failed.\r\n");
	// }

	// if (test_SDHCBlockDevice()){
	// 	return -1;
	// 	printf("err: SDHCBlockDevice test failed.\r\n");
	// }

	test_SD_FATFS();
}
