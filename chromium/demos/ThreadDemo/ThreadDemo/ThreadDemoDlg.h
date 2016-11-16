// ThreadDemoDlg.h : header file
//

#pragma once

#include "Frontend.h"

// CThreadDemoDlg dialog
class CThreadDemoDlg : public CDialog
{
// Construction
public:
	CThreadDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_THREADDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	scoped_refptr<CFrontend> frontend_;
	//CFrontend * frontend_;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton2();
};
