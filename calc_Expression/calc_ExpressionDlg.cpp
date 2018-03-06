
// calc_ExpressionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "calc_Expression.h"
#include "calc_ExpressionDlg.h"
#include "afxdialogex.h"
#include <atlconv.h>
#include <string>

using namespace std;



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Ccalc_ExpressionDlg dialog




Ccalc_ExpressionDlg::Ccalc_ExpressionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Ccalc_ExpressionDlg::IDD, pParent)
	, m_stExpr(_T(""))
	, m_stError(_T(""))
	, m_stResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ccalc_ExpressionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EXPRESION, m_stExpr);
	DDX_Text(pDX, IDC_EDIT_RES, m_stError);
	DDX_Text(pDX, IDC_STATIC_RESULT, m_stResult);
}

BEGIN_MESSAGE_MAP(Ccalc_ExpressionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//	ON_BN_CLICKED(IDOK, &Ccalc_ExpressionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK, &Ccalc_ExpressionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &Ccalc_ExpressionDlg::OnBnClickedButtonCalc)
END_MESSAGE_MAP()


// Ccalc_ExpressionDlg message handlers

BOOL Ccalc_ExpressionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//m_stExpr = L"(2+5)*2";
	CString stt = L"a = 1\r\nb = 2\r\na + b";
//	 m_stExpr = L"1*((-3 + 7)*(4 - 8) + 2 * (25 - 25))";
	//m_stExpr = L"(5-2)+2";//-3 + 2//-1

	 m_stExpr = stt;
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Ccalc_ExpressionDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Ccalc_ExpressionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Ccalc_ExpressionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//////////////////////////////////////////////////////////////////////////
void Ccalc_ExpressionDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

//

//
void Ccalc_ExpressionDlg::OnBnClickedButtonCalc()
{
	UpdateData(TRUE);

	CString st0 = L"";
	st0 = m_stExpr;
	m_stExpr = st0;

	st0 = delete_bracket(st0);
	st0 = Set_Variable(st0);
//...........

	if (Check_Systax(st0) != 0)
	{
		Return_Error(st0,Check_Systax(st0));
		return;
	}
	
	float a =  Calc_Expretion(st0);

	CString s;
	s.Format(L"%.6f", a );

	m_stResult = s;
	UpdateData(FALSE);


}

//Enum
enum Errors 
{
	ErLetters = -1,
	ErBracket = -2,

};
void Ccalc_ExpressionDlg::Return_Error(CString st,int err)
{
	switch(err)
	{
		case ErLetters:
			m_stError = "Error Letters";
			break;
		case ErBracket:
			m_stError = "Error Bracket";
			break;

	}
	UpdateData(FALSE);
}
int Ccalc_ExpressionDlg::Check_Systax(CString st)
{
	CString stt = st;
	CString st1,s;
	int is = 0, ie = 0, i;



	while(true)//Check Bracket
	{	
		if(ie == -1 && is == -1)
			break;
		if((ie != -1 || is != -1) && (ie == -1 || is == -1))
			return ErBracket;
		ie = stt.Find(')');
		st1 = stt.Left(ie + 1);
		is = st1.ReverseFind('(');
		stt.Delete(ie);
		stt.Delete(is);
	}

	bool b1, b2, b3;

	for (i = 0;i<stt.GetLength();i++)//Check !Letters
	{
		b1 =  stt.GetAt(i) == '+' || stt.GetAt(i) == '-';
		b2  = stt.GetAt(i) == '*' || stt.GetAt(i) == '/';
		b3 = stt.GetAt(i) == '.' || stt.GetAt(i) == ')' || stt.GetAt(i) == '(';
		if(!(isdigit(stt.GetAt(i)) || b1 || b2 || b3))
			return ErLetters;
	}
	return 0;
	
}
CString Ccalc_ExpressionDlg::Set_Variable(CString stt)//TODO FIX ERROR-->CHECK_SYNTAX()
{
	CString st =stt;
	char lett[10] = {' '};
	CString var[10] = {L""};
	int k = 0,i = 0, o = 0,u=0;
	CString  sVar = L"";
	char sLett = ' ';
	bool unl = false;

	if (st.GetAt (0) >= 'A' && st.GetAt(0)  <= 'Z' || st.GetAt(0)  >= 'a' && st.GetAt(0)  <= 'z') 
	{ 
		for (int q = 0;q < st.GetLength()+1; q++)//stuguma qanak@ toxeri
		{
			if(st.GetAt(q) == '\r')
				o++;
		}
		while(u < o)
		{
			if(unl == false)
			{
				if(st.GetAt(i) == '=')
				{
					unl = true;
				}
				else 
				{
					sLett = st.GetAt(i);
				}
			}
			else if(unl = true)
			{
				if(st.GetAt(i) == '\r' || st.GetAt(i) == ';')
				{
					var[k] = sVar;
					lett[k] = sLett;
					sVar = L"";
					sLett = ' ';
					k ++;
					
					u++;
					unl = false;
				}
				else if(isdigit(st.GetAt(i)))
				{		
					sVar += st.GetAt(i);
				}
			}
			i++;
		
		}
		st.Delete(0,i + 1);
	    return Insert_Variable(st,var,lett,k);
	}

	return st;

}


//
CString Ccalc_ExpressionDlg::Insert_Variable(CString stt, CString *var, char *let, int n )
{
	CString st = stt;
	for (int s = 0;s < st.GetLength(); s++)
	{
		if(st.GetAt(s) == '\r' || st.GetAt(s) == '\n')
			st.Delete(s);
	}

	char ch  = ' ';
	for (int i = 0;i < st.GetLength(); i++)
	{
		 ch = (char)st.GetAt(i);

		for (int j = 0;j < n; j++)
		{
			if(ch == let[j])
			{
				st.Delete(i);
				st.Insert(i,var[j]);
				
			}
		}
	}
	return st;
}
//
CString Ccalc_ExpressionDlg::build_string(CString stt,int i,int n)
{
	int k;
	if(i == -1 || n == -1)
		return stt;
	CString stExpretion = L"";
	for (k = i + 1; k < n ;k++)
		stExpretion+= stt[k];
	return stExpretion;
}

CString Ccalc_ExpressionDlg:: delete_bracket(CString stt)
{
	int i, j;
	char ch;
	CString st = L"";
	int n = stt.GetLength();

	j = 0;
	for(i = 0; i < n; i++)
	{
		ch = stt.GetAt(i);
		if(ch != ' ')
		{
			st.Insert(j, ch);
			j++;
		}

	}
	return st;
}

float Ccalc_ExpressionDlg::Calc_Expretion(CString st)
{
	

	CString stt = L"", st1 = L"";
	CString s = L"";
	CString floatString = L"";
	CString sValue = L"";

	stt = st;

	int is, ie = 0, i;
	float value; 
	bool check = true;
	// 

	while(ie != -1)
	{
		ie = stt.Find(')');
		st1 = stt.Left(ie + 1);
		is = st1.ReverseFind('(');
		s = build_string(stt, is, ie);
		

		if(is != -1 && ie != -1)
			stt.Delete(is,ie - is + 1);
			//Remove_str(stt,is,ie);
		else
		{
			value = unit_Expretion(s);
			break;
		}




		value = unit_Expretion(s);
		check = true;
		if(stt ==  ""){return value;}///ETE @ndamen@ mek arsheqne 
		if (value < 0)//erkrord payman@ stugel ardyoq mekne vor pakagic uner
		{
			i  = is;
			while(check)
			{
				i --;
				if(i < 0)
				{
					if(check == true)
					{
						stt.Insert(0,'-');
						check = false;
						break;
					}
					else
						break;
				}
				switch (stt[i])
				{
				case '+':
					stt.SetAt('-',i);
					check = false;
					break;
				case '-':
					stt.SetAt('+',i);
					check = false;
					break;
				}

			}
			value *= -1;

		}
		

		//Remove_str(stt,is,ie,value);
	
		sValue = L"";
		sValue.Format(L"%d", (int) value );
		if(check == false){is+=1;}////Minus Avelanaluc "is" petqe poxvi +1 ov-->indeks@ avelanuma
		stt.Insert(is ,sValue);

	}

	float a = unit_Expretion(stt);
	return a;

}
//st -> Expretion
float Ccalc_ExpressionDlg::unit_Expretion(CString st)
{
	int i, j, k,temp = 0,l = 1;
	float answer = 0;
	int jo, js, je;
	m_stResult = L"";
	char chOp[] = {'^','*','/','+','-'};
	char  a[20] = {' '}, b[20] = {' '};
	float op1, op2;
	int y=0;
	int z = 0;
	CString stt = st;
//	int f;
	int noop = 0;
	BOOL bs = TRUE,Go = FALSE;
	while(bs)
	{
		noop = 0;	
		for (i = 0; i < 5; i++)
		{
			if(z == 0)
			{
				if(stt[0] == chOp[4])
				{
					l = 1;
					Go = FALSE;
					while(true)
					{		
						if ((isdigit(stt[l]) || stt[i] == '.'))
							l++;
						else{Go = TRUE;break;}
						if(stt.GetLength() < l){Go = FALSE;break;}

					}
					if (Go == FALSE)
					{
						bs = FALSE;
						break;
					}	
				}
			}
			//Stugel ete skzbi tiv@ minusa gtel arhamarel
			jo = stt.Find(chOp[i]);
			if(Go && jo == 0)
			{
				jo = stt.Find(chOp[i],1);
			}
			
			if(jo < 0)
			{
				noop++;
				if(noop == 5)
				{
					bs = FALSE;
					break;  
				}
				z = 1;
				continue;
			}
			else
				z = 0;

			//Operant 2
			j = jo;
			k = 0;
			while(true)
			{
				j++;
				if (isdigit(stt[j]) || stt[j] == '.')
				{
					b[k] = (char) stt.GetAt(j);
					k++;

				}
				else
					break;
			}
			b[k] = '\0';

			op1 = atoi(b);


			//Operant 1

			je = j - 1;
			k = 0;
			j = jo;
			while(true)
			{
				j--;
				if (j < 0)
					break;
				
				if(Go && st[j] == '-')
				{
					a[k] = (char) stt.GetAt(j);
					k++;
				}
				if (isdigit(stt[j]) || stt[j] == '.')
				{
					a[k] = (char) stt.GetAt(j);
					k++;

				}
				else
					break;
			}
			a[k] = '\0';

			js = j + 1;

			Change(a);
			op2 = atoi(a);

			/////
			switch(chOp[i])
			{
			case '^':
				answer = pow(op2,op1);
				op2 = 0;
				op1 = 0;
				break;
			case '*':
				answer = op2 * op1;
				op2 = 0;
				op1 = 0;
				break;
			case '/':
				if(op1 == 0)
				{
					m_stError = L"Dived Error";
					return -1;
				}
				if(op1 != 0)
					answer = op2 / op1;
				op2 = 0;
				op1 = 0;
				break;
			case '+':
				answer = op2 + op1;
				op2 = 0;
				op1 = 0;
				break;
			case '-':
				answer = op2 - op1;
				op2 = 0;
				op1 = 0;
				break;

			}

			CString str = L"";
			str.Format(L"%.3f", answer );
			if(stt.GetAt(0) == '-' && js==1)// FOR stt[0]== -x
			{
				stt.Delete(0, je + 1);
				stt.Insert(0, str);
			}
			else
			{
				stt.Delete(js, je - js + 1);
				stt.Insert(js, str);
			}
			break;
		}

	}
	//TODO UPDATE THIS FUNCTION It's Not Working
	CString canswer = L"";
	canswer.Format(L"%.6f",answer);
	for(int o = 0;o < canswer.GetLength();o++)
	{
		if(canswer.GetAt(o)== '.')
		{
			for(int g = o;g < canswer.GetLength();g++)
			{
				if(!isdigit(canswer.GetAt(g)))
				{
					int k = g;
					break;
				}
			}
		}
		if(k != 0)
			break;
	}
	//


	return answer;
}
//
void Ccalc_ExpressionDlg::Change(char a[])
{
	int i;
	char cht[20] = {' '};
	int n = strlen(a);
	for(i = 0;i < n; i++)
	{
		cht[i] = a[i];
	}
	for(i = 0; i < n; i++)
	{
		a[i] = cht[n - i - 1];
	}
}