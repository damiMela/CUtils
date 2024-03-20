#pragma once

#include <vector>
#include <inttypes.h>
#include <stddef.h>

class CRC16
{
public:
    static uint16_t crcTableValue(int pos, bool set = false, uint16_t setValue = 0)
    {
        static uint16_t crcTable[256] = {0};
        if (set)
            crcTable[pos] = setValue;
        return crcTable[pos];
    }

    static bool crcTableInitialized(int set = -1)
    {
        static bool crcTableInitialized = false;
        if (set < 0)
            return crcTableInitialized;
        if (set > 1)
            set = 1;
        crcTableInitialized = set;
        return crcTableInitialized;
    }

private:
    static void generateCRCTable()
    {
        const uint16_t polynomial = 0xA001;
        for (uint16_t i = 0; i < 256; ++i)
        {
            uint16_t crc = i;
            for (int j = 0; j < 8; ++j)
            {
                if (crc & 0x0001)
                    crc = (crc >> 1) ^ polynomial;
                else
                    crc >>= 1;
            }
            crcTableValue(i, true, crc);
        }
        crcTableInitialized(true);
    }

public:
    static uint16_t calculateCRC(std::vector<unsigned char> &data)
    {
        return CRC16::calculateCRC(data.data(), data.size());
    }

    static uint16_t calculateCRC(void *data, size_t size)
    {
        if (!crcTableInitialized())
        {
            generateCRCTable();
        }
        uint16_t crc = 0xFFFF;
        for (size_t i = 0; i < size; ++i)
        {
            crc = (crc >> 8) ^ crcTableValue((crc ^ ((uint8_t *)data)[i]) & 0xFF);
        }
        return crc;
    }
};
