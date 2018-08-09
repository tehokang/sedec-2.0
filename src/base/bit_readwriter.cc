#include "bit_readwriter.h"

namespace sedec
{

namespace base
{

BitReadWriter::BitReadWriter()
{
    m_byBuffer = 0;
    m_nPos = 0;
    m_nOutCnt = 8;
}

BitReadWriter::~BitReadWriter()
{

}

void BitReadWriter::SetBuffer(unsigned char* buffer)
{
    m_szBuf = buffer;

    m_byBuffer = 0;
    m_nPos = 0;
    m_nOutCnt = 8;
}

int BitReadWriter::Read_On_Buffer(int nLen)
{
    unsigned int res = 0;
    unsigned int mask;
    unsigned char *sp = &m_szBuf[m_nPos];

    mask = 1 << (m_nOutCnt-1);
    m_byBuffer = 0;

    for (int i=0; i<nLen; i++) {
        m_byBuffer <<= 1;

        if (*sp & mask)
            m_byBuffer |= 1;

        mask >>=1;
        m_nOutCnt--;

        if (m_nOutCnt == 0) {
            m_nOutCnt = 8;
            mask = 128;		// 2^7
            m_nPos++;
            sp = &m_szBuf[m_nPos];
        }
    }
    res = m_byBuffer;

    return res;
}


void BitReadWriter::Write_On_Buffer(int Value, int nLen)
{
    unsigned int mask;
    mask = 1 << (nLen-1);         // selects first (leftmost) bit
    //TRACE("m_szBuf : %d \n", m_szBuf);
    //TRACE("m_nPos : %d \n", m_nPos);

    for ( int i=0; i<nLen; i++)
    {
        m_byBuffer <<= 1;
        if (Value & mask)
            m_byBuffer |= 1;

        mask >>= 1;             // select next bit
        m_nOutCnt--;

        if (m_nOutCnt==0) {     // 8 bit buffer full
            m_szBuf[m_nPos] = m_byBuffer;
            m_nOutCnt = 8;
            m_nPos++;
            m_byBuffer = 0;
        }
    }
}

void BitReadWriter::Skip_On_Buffer(int nLen)
{
    for (int i=0; i<nLen; i++) {
        m_nOutCnt--;

        if (m_nOutCnt == 0) {
            m_nOutCnt = 8;
            m_nPos++;
        }
    }
}

unsigned long BitReadWriter::calculate_crc32(unsigned char *temp, int nRd)
{
    int bit_count = 0;
    int bit_in_byte = 0;
    unsigned short int data_bit;
    unsigned short int shift_reg[32];
    unsigned short int g[] = { 1,1,1,0,1,1,0,1,1,0,1,1,1,0,0,
                   0,1,0,0,0,0,0,1,1,0,0,1,0,0,0,
                   0,0,1 };
    int i,nr_bits;
    unsigned char *data;
    unsigned long crc;

    /* Initialize shift register's to '1' */
    for(i=0; i<32; i++)
        shift_reg[i] = 1;

    /* Calculate nr of data bits */
    nr_bits = nRd*8; //((int) (last - first)) * 8;
    data = temp;

    while (bit_count < nr_bits)
    {
        data_bit = (short int) (*data  & (0x80 >> bit_in_byte));
        data_bit = data_bit >> (7 - bit_in_byte);
        bit_in_byte++; bit_count++;
        if (bit_in_byte == 8)
        {
            bit_in_byte = 0;
            data++;
        }

        data_bit ^= shift_reg[31];
        i = 31;
        while (i != 0)
        {
            if (g[i])
                shift_reg[i] = shift_reg[i-1] ^ data_bit;
            else
                shift_reg[i] = shift_reg[i-1];
            i--;
        }
        shift_reg[0] = data_bit;
    }

    /* make CRC an UIMSBF */
    crc = 0x00000000;
    for (i= 0; i<32; i++)
        crc = (crc << 1) | ((unsigned long) shift_reg[31-i]);

    return(crc);
}

unsigned char *BitReadWriter::GetBufAdd()
{
    return m_szBuf;
}

unsigned char* BitReadWriter::GetCurrentBuffer()
{
    return m_szBuf + m_nPos;
}

} // end of base namespace

} // end of sedec namespace
