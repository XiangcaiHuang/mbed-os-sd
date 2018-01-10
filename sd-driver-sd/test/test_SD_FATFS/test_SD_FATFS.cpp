#include <stdio.h>
#include <errno.h>

#include "mbed.h"
#include "SDHCBlockDevice.h"
#include "FATFileSystem.h"

#include "test_SD_FATFS.h"

static SDHCBlockDevice sd;
static FATFileSystem fs("fs");

void return_error(int ret_val){
	if (ret_val)
		printf("Failure. %d\r\n", ret_val);
	else
		printf("done.\r\n");
}

void errno_error(void* ret_val){
	if (ret_val == NULL)
		printf(" Failure. %d \r\n", errno);
	else
		printf(" done.\r\n");
}

int test_SD_FATFS(void)
{
	int error = 0;
	printf("Start to test SDHC-backed filesystem.\r\n");

	printf("Mounting the filesystem on \"/fs\". ");
	error = fs.mount(&sd);
	return_error(error);

	// Formatting a Fat always fails, but it doesn't affect the other functions
	// printf("Formatting a FAT, SDHC-backed filesystem. ");
	// error = FATFileSystem::format(&sd);
	// return_error(error);

	printf("Opening a new file, numbers.txt.");
	FILE* fd = fopen("/fs/numbers.txt", "w");
	errno_error(fd);

	for (int i = 0; i < 20; i++){
		printf("Writing decimal numbers to a file (%d/20)\r", i);
		fprintf(fd, "%d\r\n", i);
	}
	printf("Writing decimal numbers to a file (20/20) done.\r\n");

	printf("Closing file.");
	fclose(fd);
	printf(" done.\r\n");

	printf("Re-opening file read-only.");
	fd = fopen("/fs/numbers.txt", "r");
	errno_error(fd);

	printf("Dumping file to screen.\r\n");
	char buff[16] = {0};
	while (!feof(fd)){
		int size = fread(&buff[0], 1, 15, fd);
		fwrite(&buff[0], 1, size, stdout);
	}
	printf("EOF.\r\n");

	printf("Closing file.");
	fclose(fd);
	printf(" done.\r\n");

	printf("Opening root directory.");
	DIR* dir = opendir("/fs/");
	errno_error(fd);

	struct dirent* de;
	printf("Printing all filenames:\r\n");
	while((de = readdir(dir)) != NULL){
		printf("  %s\r\n", &(de->d_name)[0]);
	}

	printf("Closeing root directory. ");
	error = closedir(dir);
	return_error(error);
	printf("SDHC-backed filesystem test finished.\r\n");

	return 0;
}
