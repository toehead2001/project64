/****************************************************************************
*                                                                           *
* Project64 - A Nintendo 64 emulator.                                      *
* http://www.pj64-emu.com/                                                  *
* Copyright (C) 2012 Project64. All rights reserved.                        *
*                                                                           *
* License:                                                                  *
* GNU/GPLv2 http://www.gnu.org/licenses/gpl-2.0.html                        *
*                                                                           *
****************************************************************************/
#pragma once

#include <Common/Ini File Class.h>
#include "SettingsType-Base.h"

class CSettingTypeRomDatabase :
    public CSettingType
{
public:
    CSettingTypeRomDatabase(const char * Name, const char * DefaultValue, bool DeleteOnDefault = false );
    CSettingTypeRomDatabase(const char * Name, bool DefaultValue, bool DeleteOnDefault = false );
    CSettingTypeRomDatabase(const char * Name, int DefaultValue, bool DeleteOnDefault = false );
    CSettingTypeRomDatabase(const char * Name, SettingID DefaultSetting, bool DeleteOnDefault = false );

    virtual ~CSettingTypeRomDatabase();

    virtual bool        IndexBasedSetting ( void ) const { return false; }
    virtual SettingType GetSettingType    ( void ) const { return SettingType_RomDatabase; }

    //return the values
    virtual bool Load   ( int Index, bool & Value   ) const;
    virtual bool Load   ( int Index, uint32_t & Value  ) const;
    virtual bool Load   ( int Index, stdstr & Value ) const;

    //return the default values
    virtual void LoadDefault ( int Index, bool & Value   ) const;
    virtual void LoadDefault ( int Index, uint32_t & Value  ) const;
    virtual void LoadDefault ( int Index, stdstr & Value ) const;

    //Update the settings
    virtual void Save   ( int Index, bool Value );
    virtual void Save   ( int Index, uint32_t Value );
    virtual void Save   ( int Index, const stdstr & Value );
    virtual void Save   ( int Index, const char * Value );

    // Delete the setting
    virtual void Delete ( int Index );

    static void Initialize( void );
    static void CleanUp   ( void );

protected:
    static void GameChanged ( void * /*Data */ );

    static bool IsGlideSetting (const char * Name);
    static const char * StripNameSection (const char * Name);
    virtual const char * Section ( void ) const { return m_SectionIdent->c_str(); }

    mutable stdstr  m_KeyName;
    const char *const m_DefaultStr;
    const int       m_DefaultValue;
    const SettingID m_DefaultSetting;
    const bool      m_DeleteOnDefault;
    bool            m_GlideSetting;

    static stdstr   * m_SectionIdent;
    static CIniFile * m_SettingsIniFile;
    static CIniFile * m_GlideIniFile;

private:
    CSettingTypeRomDatabase();                                          // Disable default constructor
    CSettingTypeRomDatabase(const CSettingTypeRomDatabase&);            // Disable copy constructor
    CSettingTypeRomDatabase& operator=(const CSettingTypeRomDatabase&); // Disable assignment
};
