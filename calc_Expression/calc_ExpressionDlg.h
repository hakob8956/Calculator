
// calc_ExpressionDlg.h : header file
//

#pragma once


// Ccalc_ExpressionDlg dialog
class Ccalc_ExpressionDlg : public CDialogEx
{
// Construction
public:
	Ccalc_ExpressionDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CALC_EXPRESSION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation

public:
	float unit_Expretion(CString st);
	void Change(char a[]);
	float Calc_Expretion(CString st);
	CString build_string(CString stt, int i, int n);
	CString delete_bracket(CString stt);
	
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedOk();
	CString m_stExpr;
	afx_msg void OnBnClickedButtonCalc();
	double m_Res;
	CString m_stResult;
};
