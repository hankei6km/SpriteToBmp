#include <string>
#include <unity.h>
#define private public

#include <BmpHeader.h>
#include <BmpBase64.h>

inline int32_t toInt(uint8_t *a)
{
    return a[0] | (a[1] << 8) | (a[2] << 16) | (a[3] << 24);
}

void test_file_header(void)
{
    SpriteToBmp::BmpHeader bh = SpriteToBmp::BmpHeader(11, 22);
    uint8_t *fh = bh.fileHeader();
    uint32_t fs = toInt(&fh[2]);

    TEST_ASSERT_EQUAL('B', fh[0]);
    TEST_ASSERT_EQUAL('M', fh[1]);
    TEST_ASSERT_EQUAL((14 + 108) + (11 * 22 * 2), fs);
    // TEST_ASSERT_EQUAL(0, fh[6]);
    // TEST_ASSERT_EQUAL(0, fh[7]);
    // TEST_ASSERT_EQUAL(0, fh[8]);
    // TEST_ASSERT_EQUAL(0, fh[9]);
    TEST_ASSERT_EQUAL(14 + 108, fh[10]);
}

void test_file_header_size(void)
{
    SpriteToBmp::BmpHeader bh = SpriteToBmp::BmpHeader(11, 22);
    TEST_ASSERT_EQUAL(14, bh.fileHeaderSize());
}

void test_info_header(void)
{
    SpriteToBmp::BmpHeader bh = SpriteToBmp::BmpHeader(11, 22);
    uint8_t *ih = bh.infoHeader();
    int16_t w = toInt(&ih[4]);
    int16_t h = toInt(&ih[8]);
    uint32_t rMask = toInt(&ih[40]);
    uint32_t gMask = toInt(&ih[44]);
    uint32_t bMask = toInt(&ih[48]);

    TEST_ASSERT_EQUAL(108, ih[0]);
    TEST_ASSERT_EQUAL(11, w);
    TEST_ASSERT_EQUAL(-22, h);
    TEST_ASSERT_EQUAL(16, ih[14]);
    TEST_ASSERT_EQUAL(0x0000f800, rMask); // DEC:63488
    TEST_ASSERT_EQUAL(0x000007e0, gMask); // DEC:2016
    TEST_ASSERT_EQUAL(0x0000001f, bMask); // DEC:31
}

void test_info_header_size(void)
{
    SpriteToBmp::BmpHeader bh = SpriteToBmp::BmpHeader(11, 22);
    TEST_ASSERT_EQUAL(108, bh.infoHeaderSize());
}

void test_header(void)
{
    SpriteToBmp::BmpHeader bh = SpriteToBmp::BmpHeader(11, 22);
    uint8_t *h = bh.header();
    TEST_ASSERT_EQUAL('B', h[0]);
    TEST_ASSERT_EQUAL('M', h[1]);
    TEST_ASSERT_EQUAL(108, h[14]);
}

void test_header_size(void)
{
    SpriteToBmp::BmpHeader bh = SpriteToBmp::BmpHeader(11, 22);
    TEST_ASSERT_EQUAL(14 + 108, bh.headerSize());
}

void test_swap_bytes(void)
{
    SpriteToBmp::Encoder encoder;
    uint8_t src[] = {0x10, 0x20, 0x30, 0x40};
    uint8_t dst[4];
    uint8_t expect[] = {0x20, 0x10, 0x40, 0x30};
    encoder._swapBytes(src, dst, 4);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expect, dst, 4);
}

void test_encode_base64(void)
{
    SpriteToBmp::Encoder encoder;
    uint8_t src[] = {0x00, 0x00};
    bool called = false;
    encoder._encodeBase64(src, 2, [&called](uint8_t *b, size_t s) {
        TEST_ASSERT_EQUAL_INT8_ARRAY((uint8_t *)"ABC123==", b, 8);
        TEST_ASSERT_EQUAL(8, strlen((char *)b));
        TEST_ASSERT_EQUAL(8, s);
        called = true;
    });
    TEST_ASSERT_TRUE(called);
}

// TODO: implement
// void test_to_bmp_base64(void)
// {
// }

int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_file_header);
    RUN_TEST(test_file_header_size);
    RUN_TEST(test_info_header);
    RUN_TEST(test_info_header_size);
    RUN_TEST(test_header);
    RUN_TEST(test_header_size);

    RUN_TEST(test_swap_bytes);
    RUN_TEST(test_encode_base64);
    // TODO: implement
    // RUN_TEST(test_to_bmp_base64);

    UNITY_END();

    return 0;
}
