#pragma once

#include "stdtypes.h"

class CFileBase
{
public:
    enum OpenFlags 
    {
        modeRead =          0x0000,
        modeWrite =         0x0001,
        modeReadWrite =     0x0002,
        shareCompat =       0x0000,
        shareExclusive =    0x0010,
        shareDenyWrite =    0x0020,
        shareDenyRead =     0x0030,
        shareDenyNone =     0x0040,
        modeNoInherit =     0x0080,
        modeCreate =        0x1000,
        modeNoTruncate =    0x2000,
    };

    enum Attribute 
    {
        normal =    0x00,
        readOnly =  0x01,
        hidden =    0x02,
        system =    0x04,
        volume =    0x08,
        directory = 0x10,
        archive =   0x20
    };

    enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

    virtual bool Open(const char * lpszFileName, uint32_t nOpenFlags ) = 0;

    virtual uint32_t GetPosition() const = 0;
    virtual long Seek(long lOff, SeekPosition nFrom) = 0;
    virtual bool SetLength(uint32_t dwNewLen) = 0;
    virtual uint32_t GetLength() const = 0;

    virtual size_t Read(void* lpBuf, size_t nCount) = 0;
    virtual bool Write(const void* lpBuf, size_t nCount) = 0;

    virtual bool Flush() = 0;
    virtual bool Close() = 0;
    virtual bool IsOpen() const = 0;
    virtual bool SetEndOfFile() = 0;
};

class CFile : public CFileBase
{
    // Attributes
    void *  m_hFile;
    bool    m_bCloseOnDelete;

public:
    // Flag values

    // Constructors
    CFile();
    CFile(void * hFile);
    CFile(const char * lpszFileName, uint32_t nOpenFlags);

    // Deconstructors
    virtual ~CFile();

    // Operations
    virtual bool Open(const char * lpszFileName, uint32_t nOpenFlags );

    uint32_t SeekToEnd   ( void );
    void  SeekToBegin ( void );

    // Overridables
    virtual uint32_t GetPosition() const;
    virtual long Seek(long lOff, SeekPosition nFrom);
    virtual bool SetLength(uint32_t dwNewLen);
    virtual uint32_t GetLength() const;

    virtual size_t Read(void* lpBuf, size_t nCount);
    virtual bool Write(const void* lpBuf, size_t nCount);

    virtual bool Flush();
    virtual bool Close();
    virtual bool IsOpen() const;
    virtual bool SetEndOfFile();
};
