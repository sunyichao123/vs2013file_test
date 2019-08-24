
// MyfiletestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Myfiletest.h"
#include "MyfiletestDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
#include "afx.h"
#include <map>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMyfiletestDlg �Ի���



CMyfiletestDlg::CMyfiletestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyfiletestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyfiletestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_1, m_static_1);
	DDX_Control(pDX, IDC_STATIC_2, m_static_2);
}

BEGIN_MESSAGE_MAP(CMyfiletestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyfiletestDlg ��Ϣ�������

BOOL CMyfiletestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	brush.CreateSolidBrush(RGB(0, 255, 0));


	CString FilePath;
	TCHAR lpFileName[256];
	GetModuleFileName(NULL, lpFileName, 256);
	FilePath.Format(_T("%s"), lpFileName);
	FilePath = FilePath.Left(FilePath.ReverseFind(_T('\\')));  //·�����û��'\\'
	CString File_Path_and_Name;

	if (!PathIsDirectory(FilePath + _T("\\config")))
	{
		::CreateDirectory(FilePath + _T("\\config"), NULL);//����Ŀ¼,���еĻ���Ӱ��  
	}
	CFileFind finder;
	bool bWorking = finder.FindFile(FilePath + _T("\\config\\") + _T("*.bin"));
	while (bWorking)
	{
		bWorking = finder.FindNextFileW();
		TRACE(_T("%s\n"), finder.GetFileTitle());

	}
	File_Path_and_Name = FilePath + _T("\\config\\") + finder.GetFileTitle() + _T(".txt");

	CFile ConfigFile;
#if 0
	if (ConfigFile.Open(File_Path_and_Name, CFile::modeCreate | CFile::modeReadWrite, NULL))
	{
		Config config_read;
		config_read.INT = 12;
		config_read.ModuleType = "SD16ATSC";
		CString str;
		str.Format(_T("%s, %d\n"), config_read.ModuleType, config_read.INT);
		ConfigFile.Write(&str, sizeof(str));

		DWORD FileLength = ConfigFile.GetLength();
		while (FileLength)
		{
			Config config;
			UINT ReadBytes = ConfigFile.Read(&config, sizeof(Config));
			ConfigVector.push_back(config);
			FileLength -= ReadBytes;
		}
#endif

		Config config_read;
		config_read.ModuleType = "SD16ATSC";
		config_read.INT = 12;
		config_read.VBB = 2.5;
		float test[6];
		test[0] = 2.01;
		test[1] = 2.5;
		test[2] = 2.6;
		test[3] = 2.7;
		test[4] = 2.8;
		test[5] = 2.91;
		int index = 35;
		int testint = test[0] * 4095 / 5;
		ofstream out(File_Path_and_Name, ios::out);
		//		CFile fileout;
		string strp = "sd16a";
		//		out.write((char *)test, sizeof(float)*6);

		float threshold[2];
		threshold[0] = 2.01;
		threshold[1] = 2.03;
		map<string, float*> testmap;
		testmap.insert({ strp, threshold });

		map<string, float*>::iterator ite;
		for (ite = testmap.begin(); ite != testmap.end(); ite++){
			out << ite->first;
			out << ":";
			out << ite->second[0] << "," << ite->second[1] << endl;
		}
		//		out.write((char*)str2, sizeof(str2));

		//		out.write((char *)test, sizeof(float)*3);
		//		for (int i = 0; i < 6; i++){
		//			out << test[i] << " ";
		//			TRACE("11111\n");
		//		}
		//		TRACE("%d\n", out.tellp());
		out.close();
		//		fileout.Open(File_Path_and_Name, CFile::modeWrite | CFile::modeCreate);

		//		fileout.Write(str, strlen(str));
		//		fileout.Close();



		float configIn[6];
		//		Config config;
		char moduletype[20];
		CFile in;
		in.Open(File_Path_and_Name, CFile::modeRead);
		//		ifstream filein;

		//		filein.open(File_Path_and_Name, ios::in);
		//		int readlength = 0;
		//		while (in.){
		//		filein >> configIn[0] >> configIn[1] >> configIn[2];
		//		TRACE("%d\n", filein.tellg());
		//			readlength += 12;
		//		}
		//		config.ModuleType = (char*)malloc(sizeof(moduletype));
		//		::memcpy(config.ModuleType, moduletype, sizeof(moduletype));
		char readbuffer[20];
		//		in.Read(readbuffer, in.GetLength());
		in.Close();
		TRACE("%s\n", readbuffer);

		ifstream filein;
		float config[6] = { 0 };
		filein.open(File_Path_and_Name, ios::in | ios::binary);
		filein.seekg(0, filein.end);
		int ret = filein.tellg();
		filein.seekg(0, filein.beg);

		char *temp = new char[ret];
		filein.read(temp, ret);

		for (int i = 0; i < ret / 4; i++)
			configIn[i] = *((float *)temp + i);
		delete[]temp;
		filein.close();

		ifstream mapin;
		string index2;
		float threshold_read[2];
		map<string, float*> readmap;
		char buffer[1024];
		char p1[25] = { 0 }, p2[10] = { 0 }, p3[10] = {0};

		mapin.open(File_Path_and_Name, ios::in);
		while (mapin.getline(buffer, 1024)){
			//mapin >> index2;
			//readmap.insert({index2, threshold_read});
			TRACE("%s,%d\n", buffer, strlen(buffer));
			int x, y;

			for (int i = 0; i < strlen(buffer); i++){
				if (buffer[i] == ':'){
					x = i;
				}
				else if (buffer[i] == ','){
					y = i;
				}
			}
			for (int j = 0; j < strlen(buffer); j++){
				if (j == x || j == y)
					continue;
				if (j < x){
					p1[j] = buffer[j];
				}
				else if (j < y){
					p2[j - x -1] = buffer[j];
				}
				else{
					p3[j - y -1] = buffer[j];
				}
			}
		}
		float z = atof(p2);
		TRACE("%s\n%s\n%g\n", p1, p2, z);

		mapin.close();
		//		TRACE("%s\n", index2);


		//		TRACE("%u\n", ret);

		//		TRACE("%d, %.2f, %s\n", config.INT, config.VBB, config.ModuleType);
		for (int i = 0; i < 6; i++)
		{
			//			TRACE("%g\n", configIn[i]);
		}

		float a = 10.1;
		CString str;
		str.Format(_T("%g"), a);
		SetDlgItemText(IDC_STATIC_2, str);
		SetTimer(1, 1000, NULL);

		//	UpdateData(false);
		return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMyfiletestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyfiletestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyfiletestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CMyfiletestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->m_hWnd == m_static_1 
		|| pWnd->m_hWnd == m_static_2)
	{
		return (HBRUSH)brush;
	}


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
int i = 0;
void CMyfiletestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
		//::PostMessage(GetSafeHwnd(),WM_CTLCOLOR, (WPARAM)&m_static_1, (LPARAM);
		if (i % 2 == 1){
			brush.DeleteObject();
			brush.CreateSolidBrush(RGB(0, 255, 0));
		}
		else{
			brush.DeleteObject();
			brush.CreateSolidBrush(RGB(255,0,0));
		}
		m_static_1.Invalidate();
		m_static_2.Invalidate();
		i++;
		break;

	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMyfiletestDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	brush.DeleteObject();

	CDialogEx::OnClose();
}
