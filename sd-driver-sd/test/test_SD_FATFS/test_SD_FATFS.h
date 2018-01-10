#ifndef _TEST_SD_FATFS_H_
#define _TEST_SD_FATFS_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Test function for SD Card SD Bus mode driver.
 *
 * @retval -1 Test failed.
 * @retval 0  Test successfully.
 */
int test_SD_FATFS(void);

#if defined(__cplusplus)
}
#endif

#endif // _TEST_SD_FATFS_H_