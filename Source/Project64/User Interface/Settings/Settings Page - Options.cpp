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
#include "stdafx.h"

#include "Settings Page.h"

CGeneralOptionsPage::CGeneralOptionsPage(CSettingConfig * SettingsConfig, HWND hParent, const RECT & rcDispay) :
m_SettingsConfig(SettingsConfig)
{
	if (!Create(hParent, rcDispay))
	{
		return;
	}

	//Set the text for all gui Items
	SetDlgItemTextW(m_hWnd, IDC_AUTOSLEEP, GS(OPTION_AUTO_SLEEP));
	SetDlgItemTextW(m_hWnd, IDC_LOAD_FULLSCREEN, GS(OPTION_AUTO_FULLSCREEN));
	SetDlgItemTextW(m_hWnd, IDC_SCREEN_SAVER, GS(OPTION_DISABLE_SS));
	SetDlgItemTextW(m_hWnd, IDC_BASIC_MODE, GS(OPTION_BASIC_MODE));
	SetDlgItemTextW(m_hWnd, IDC_MAXROMS_TXT, GS(RB_MAX_ROMS));
	SetDlgItemTextW(m_hWnd, IDC_ROMSEL_TEXT2, GS(RB_ROMS));
	SetDlgItemTextW(m_hWnd, IDC_MAXROMDIR_TXT, GS(RB_MAX_DIRS));
	SetDlgItemTextW(m_hWnd, IDC_ROMSEL_TEXT4, GS(RB_DIRS));

	AddModCheckBox(GetDlgItem(IDC_AUTOSLEEP), Setting_AutoSleep);
	AddModCheckBox(GetDlgItem(IDC_LOAD_FULLSCREEN), Setting_AutoFullscreen);
	AddModCheckBox(GetDlgItem(IDC_SCREEN_SAVER), Setting_DisableScrSaver);
	AddModCheckBox(GetDlgItem(IDC_BASIC_MODE), UserInterface_BasicMode);

	CModifiedEditBox * TxtBox = AddModTextBox(GetDlgItem(IDC_REMEMBER), File_RecentGameFileCount, false);
	TxtBox->SetTextField(GetDlgItem(IDC_MAXROMS_TXT));

	TxtBox = AddModTextBox(GetDlgItem(IDC_REMEMBERDIR), Directory_RecentGameDirCount, false);
	TxtBox->SetTextField(GetDlgItem(IDC_MAXROMDIR_TXT));

	UpdatePageSettings();
}

void CGeneralOptionsPage::HidePage()
{
	ShowWindow(SW_HIDE);
}

void CGeneralOptionsPage::ShowPage()
{
	ShowWindow(SW_SHOW);
}

void CGeneralOptionsPage::ApplySettings(bool UpdateScreen)
{
	CSettingsPageImpl<CGeneralOptionsPage>::ApplySettings(UpdateScreen);
}

bool CGeneralOptionsPage::EnableReset(void)
{
	if (CSettingsPageImpl<CGeneralOptionsPage>::EnableReset()) { return true; }
	return false;
}

void CGeneralOptionsPage::ResetPage()
{
	CSettingsPageImpl<CGeneralOptionsPage>::ResetPage();
	m_SettingsConfig->UpdateAdvanced((int)::SendMessage(GetDlgItem(IDC_BASIC_MODE), BM_GETCHECK, 0, 0) == 0);
}

void CGeneralOptionsPage::OnBasicMode(UINT Code, int id, HWND ctl)
{
	CheckBoxChanged(Code, id, ctl);
	m_SettingsConfig->UpdateAdvanced((int)::SendMessage(ctl, BM_GETCHECK, 0, 0) == 0);
}
