#ifndef _TEST_SDHC_DRIVER_H_
#define _TEST_SDHC_DRIVER_H_

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Test function for SD Card SD Bus mode driver.
 *
 * @retval -1 Test failed.
 * @retval 0  Test successfully.
 */
int test_sdhc_driver(void);

#if defined(__cplusplus)
}
#endif

#endif // _TEST_SDHC_DRIVER_H_