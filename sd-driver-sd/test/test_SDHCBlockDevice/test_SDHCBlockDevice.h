#ifndef _TEST_SDHCBLOCKDEVICE_H_
#define _TEST_SDHCBLOCKDEVICE_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Test function for SD Card SD Bus mode driver.
 *
 * @retval -1 Test failed.
 * @retval 0  Test successfully.
 */
int test_SDHCBlockDevice(void);

#if defined(__cplusplus)
}
#endif

#endif // _TEST_SDHCBLOCKDEVICE_H_