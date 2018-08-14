#if !defined(__BIT_READ_WRITER__)
#define __BIT_READ_WRITER__

namespace sedec
{
/**
    @addtogroup Sedec
    @{
*/

namespace base
{
/**
    @addtogroup base
    @{
*/
class BitReadWriter
{
public:
    BitReadWriter();
    virtual ~BitReadWriter();

    unsigned char* GetCurrentBuffer();
    unsigned char* GetBufAdd();
    unsigned long calculate_crc32(unsigned char *temp, int nRd);
    void	Skip_On_Buffer(int nLen);
    void	SetBuffer(unsigned char* buffer);
    int		Read_On_Buffer(int nLen);
    void	Write_On_Buffer(int Value, int nLen);

private:
    unsigned char*	m_szBuf;
    int		m_nPos;
    int		m_nOutCnt;
    unsigned int m_byBuffer;
};

/** @} */

}  // end of base namespace

/** @} */

} // end of sedec namespace
#endif
