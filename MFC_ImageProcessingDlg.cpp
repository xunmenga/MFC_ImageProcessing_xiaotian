﻿
// MFC_ImageProcessingDlg.cpp: 实现文件
//
#include "pch.h"
#include "framework.h"
#include "MFC_ImageProcessing.h"
#include "MFC_ImageProcessingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCImageProcessingDlg* Imagepass;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCImageProcessingDlg 对话框



CMFCImageProcessingDlg::CMFCImageProcessingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_IMAGEPROCESSING_DIALOG, pParent)
	, m_Scale_Height(0)
	, m_Scale_Width(0)
	, nummo(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCImageProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HEIGHT_EDIT, m_Scale_Height);
	DDX_Text(pDX, IDC_WIDTH_EDIT, m_Scale_Width);
	DDX_Control(pDX, IDC_SLIDER1, Slmo);
	DDX_Slider(pDX, IDC_SLIDER1, nummo);
}

BEGIN_MESSAGE_MAP(CMFCImageProcessingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BUTTON, &CMFCImageProcessingDlg::OnClickedOpenButton)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &CMFCImageProcessingDlg::OnClickedSaveButton)
	ON_BN_CLICKED(IDC_Rotation, &CMFCImageProcessingDlg::OnClickedRotation)
	ON_BN_CLICKED(IDOK, &CMFCImageProcessingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BLUR_BUTTON, &CMFCImageProcessingDlg::OnClickedBlurButton)
	ON_BN_CLICKED(IDC_SHARP_BUTTON, &CMFCImageProcessingDlg::OnClickedSharpButton)
	ON_BN_CLICKED(IDC_SCALE_BUTTON, &CMFCImageProcessingDlg::OnClickedScaleButton)
	ON_WM_LBUTTONDBLCLK()
	ON_STN_CLICKED(IDC_STATIC_PIC, &CMFCImageProcessingDlg::OnStnClickedStaticPic)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCImageProcessingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCImageProcessingDlg::OnBnClickedButton2)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMFCImageProcessingDlg 消息处理程序

BOOL CMFCImageProcessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CStatic* pImageControl = (CStatic*)GetDlgItem(IDC_STATIC_PIC);


	Slmo.SetRange(15, 50);//设置滑动范围为15-50
	Slmo.SetTicFreq(5);//每5个单位画一刻度
	Slmo.SetPos(20);//设置滑块初始位置为20 
	nummo = 20;

	SetDlgItemInt(IDC_EDIT_MO, 20);//设置编辑框的初始值SetDlgItemInt(IDC_EDIT1, Start);//设置编辑框的初始值

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCImageProcessingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCImageProcessingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCImageProcessingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 内部函数

// 显示位图函数
void CMFCImageProcessingDlg::Show_Bmp(double hfactor = 1,double wfactor = 1)
{
	// 清除图片控件
	GetDlgItem(IDC_STATIC_PIC)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PIC)->ShowWindow(TRUE);

	// 获取图片控件基本变量
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC); //获得pictrue控件窗口的句柄
	CDC* pDC = pWnd->GetDC(); //获得pictrue控件的DC
	CRect rect;
	pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域

	// 计算宽高比，使用浮点数避免精度问题
	double wid_hei_ratio = (double)bmpInfo.biWidth / (double)bmpInfo.biHeight;
	int image_width = bmpInfo.biWidth;
	int image_height = bmpInfo.biHeight;

	// 调整缩略图大小
	if (rect.Width() < wid_hei_ratio * rect.Height())
	{
		if (wfactor <= 1 && hfactor <= 1) 
		{
			image_width = static_cast<int>(rect.Width() * wfactor);
			image_height = static_cast<int>(image_width / wid_hei_ratio * hfactor);
		}
		else 
		{
			AfxMessageBox(_T("倍数大于一将无法在缩略图中呈现缩放效果"));
			image_width = rect.Width();
			image_height = static_cast<int>(image_width / wid_hei_ratio);
		}
		
	}
	else
	{
		if (wfactor <= 1 && hfactor <= 1) 
		{
			image_height = static_cast<int>(rect.Height() * hfactor);
			image_width = static_cast<int>(wid_hei_ratio * image_height * wfactor);
		}
		else 
		{
			AfxMessageBox(_T("倍数大于一将无法在缩略图中呈现缩放效果"));
			image_height = rect.Height();
			image_width = static_cast<int>(wid_hei_ratio * image_height);
		}
	}

	// 确保图像宽高不为负数
	if (image_width <= 0 || image_height <= 0)
	{
		AfxMessageBox(_T("宽高为负数！"));
		return;
	}

	// 计算每行的填充字节数
	int rowSize = ((bmpInfo.biWidth * bmpInfo.biBitCount + 31) / 32) * 4;
	int bmpDataSize = bmpInfo.biHeight * rowSize;

	// 显示位图
	pDC->SetStretchBltMode(COLORONCOLOR);
	StretchDIBits(pDC->GetSafeHdc(),
		(rect.Width() - image_width) / 2,
		(rect.Height() - image_height) / 2,
		image_width,
		image_height,
		0,
		0,
		bmpInfo.biWidth,
		bmpInfo.biHeight,
		pBmpData,
		pBmpInfo,
		DIB_RGB_COLORS,
		SRCCOPY);

	pWnd->ReleaseDC(pDC);
}

// 保存并打开临时位图
void CMFCImageProcessingDlg::Save_Open_Temp_Bmp()
{
	// 保存临时位图
	CString TempPath = _T(".\\Temp");
	if (!PathIsDirectory(TempPath)) CreateDirectory(TempPath, 0); //不存在临时文件夹则创建

	CString TempFilePath = _T(".\\Temp\\Temp.bmp");
	if (!bmpFile.Open(TempFilePath, CFile::modeCreate |
		CFile::modeWrite | CFile::typeBinary))
	{
		AfxMessageBox(_T("无法打开临时文件进行写入"));
		return;
	}

	bmpFile.Write(&bmpHeader, sizeof(BITMAPFILEHEADER));
	bmpFile.Write(&bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD bmpDataSize = bmpInfo.biSizeImage;
	if (bmpDataSize == 0)
	{
		bmpDataSize = ((bmpInfo.biWidth * bmpInfo.biBitCount
			+ 31) / 32) * 4 * bmpInfo.biHeight;
	}
	bmpFile.Write(pBmpData, bmpDataSize);
	bmpFile.Close();

	// 打开临时位图
	if (!bmpFile.Open(TempFilePath, CFile::modeRead | CFile::typeBinary))
		return;
	if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
		return;
	if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
		return;
	pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];

	memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
	DWORD Bytes = bmpInfo.biWidth * bmpInfo.biHeight * (bmpInfo.biBitCount / 8);
	pBmpData = new BYTE[Bytes];
	bmpFile.Read(pBmpData, Bytes);
	bmpFile.Close();
}

// 将 BGR 编码的位图转换成 OpenCV Mat 格式
void CMFCImageProcessingDlg::Bmp2Mat(cv::Mat img, int height, int width)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = (y * width + x) * 3; // 每个像素 3 byte
			img.at<cv::Vec3b>(y, x)[0] = pBmpData[index + 2]; // B
			img.at<cv::Vec3b>(y, x)[1] = pBmpData[index + 1]; // G
			img.at<cv::Vec3b>(y, x)[2] = pBmpData[index];     // R
		}
	}
}

// 将 OpenCV Mat 格式还原成 BGR 编码的位图文件
void CMFCImageProcessingDlg::Mat2Bmp(cv::Mat img, int height, int width)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = (y * width + x) * 3; // 每个像素 3 byte
			pBmpData[index + 2] = img.at<cv::Vec3b>(y, x)[0]; // B
			pBmpData[index + 1] = img.at<cv::Vec3b>(y, x)[1]; // G
			pBmpData[index] = img.at<cv::Vec3b>(y, x)[2];     // R
		}
	}
}


// 控件函数
void CMFCImageProcessingDlg::OnClickedOpenButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器
	LPCTSTR szFilter = _T("bmp (*.bmp)|*.bmp|");

	// 构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T(".bmp"), NULL, 
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, szFilter, this);
	CString FilePath;

	// 显示打开文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		FilePath = fileDlg.GetPathName(); // 获取文件路径
		SetDlgItemText(IDC_OPEN_EDIT, FilePath); // 在编辑框显示文件路径

		// 打开对话框获取图像信息
		CString BmpName = fileDlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
		CString EntName = fileDlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();                     //将文件扩展名转换为一个小写字符

		if (EntName.Compare(_T("bmp")) == 0)
		{
			// 以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
			if (!bmpFile.Open(BmpName, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO*)new char[sizeof(BITMAPINFOHEADER)];

			// 为图像数据申请空间
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			DWORD Bytes = bmpInfo.biWidth * bmpInfo.biHeight * (bmpInfo.biBitCount / 8);
			pBmpData = new BYTE[Bytes];
			bmpFile.Read(pBmpData, Bytes);
			bmpFile.Close();

			// 显示位图
			Show_Bmp();
		}
	}


}


void CMFCImageProcessingDlg::OnClickedSaveButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器
	LPCTSTR szFilter = _T("bmp (*.bmp)|*.bmp|");

	// 构造保存文件对话框    
	CFileDialog fileDlg(FALSE, _T(".bmp"), _T("default.bmp"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	fileDlg.m_ofn.lpstrTitle = _T("保存");  // 保存对话窗口标题名
	CString FilePath;

	// 显示保存文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		FilePath = fileDlg.GetPathName();  // 获取文件路径
		SetDlgItemText(IDC_SAVE_EDIT, FilePath);

		if (!bmpFile.Open(FilePath, CFile::modeCreate | 
			CFile::modeWrite | CFile::typeBinary)) 
		{
			AfxMessageBox(_T("无法打开文件进行写入"));
			return;
		}

		// 写入文件头
		bmpFile.Write(&bmpHeader, sizeof(BITMAPFILEHEADER));

		// 写入信息头
		bmpFile.Write(&bmpInfo, sizeof(BITMAPINFOHEADER));

		// 计算位图数据大小
		DWORD bmpDataSize = bmpInfo.biSizeImage;
		if (bmpDataSize == 0) 
		{
			bmpDataSize = ((bmpInfo.biWidth * bmpInfo.biBitCount 
				+ 31) / 32) * 4 * bmpInfo.biHeight;
		}

		// 写入位图数据
		bmpFile.Write(pBmpData, bmpDataSize);

		// 关闭文件
		bmpFile.Close();
	}
}


void CMFCImageProcessingDlg::OnClickedRotation()
{
	// TODO: 在此添加控件通知处理程序代码
	// 获取原始位图的宽度和高度
	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;

	// 计算新的宽度和高度
	double wid_hei_ratio = (double)bmpInfo.biWidth / (double)bmpInfo.biHeight;
	int newWidth = height;
	int newHeight = width;

	// 分配新的位图数据数组
	BYTE* pNewBmpData = new BYTE[newWidth * newHeight * (bmpInfo.biBitCount / 8)];
	memset(pNewBmpData, 0, newWidth * newHeight * (bmpInfo.biBitCount / 8)); // 初始化为 0

	// 进行旋转变换
	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			// 计算新坐标
			int newX = y;
			int newY = width-x-1;

			// 计算原始和新的数据偏移
			int oldIndex = static_cast<int>((y * width + x) * (bmpInfo.biBitCount / 8));
			int newIndex = static_cast<int>((newY * newWidth + newX) * (bmpInfo.biBitCount / 8));
			memcpy(&pNewBmpData[newIndex], &pBmpData[oldIndex], (bmpInfo.biBitCount / 8)); // 复制像素
		}
	}

	// 更新位图信息
	bmpInfo.biWidth = newWidth;
	bmpInfo.biHeight = newHeight;
	bmpInfo.biSizeImage = newWidth * newHeight * (bmpInfo.biBitCount / 8);
	delete[] pBmpData;
	pBmpData = pNewBmpData;

	// 保存并打开临时位图
	Save_Open_Temp_Bmp();

	// 显示位图
	Show_Bmp();
}

void CMFCImageProcessingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CMFCImageProcessingDlg::OnClickedBlurButton()
{
	// TODO: 在此添加控件通知处理程序代码
	 // 1. 将位图数据转换为 OpenCV Mat
	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	cv::Mat img(height, width, CV_8UC3);

	// 假设位图数据是 BGR 格式
	Bmp2Mat(img, height, width);

	// 2. 应用高斯模糊
	cv::Mat blurredImg;
	cv::GaussianBlur(img, blurredImg, cv::Size(19, 19), 0);

	// 3. 将处理后的图像转换回位图格式
	Mat2Bmp(blurredImg, height, width);

	// 4. 显示图像
	Show_Bmp();
}


void CMFCImageProcessingDlg::OnClickedSharpButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 1. 将位图数据转换为 OpenCV Mat
	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	cv::Mat img(height, width, CV_8UC3);

	// 假设位图数据是 BGR 格式
	Bmp2Mat(img, height, width);

	// 2. 应用高斯滤波锐化模糊图片
	cv::Mat SharpenedImg;
	cv::GaussianBlur(img, SharpenedImg, cv::Size(0, 0), 3);
	cv::addWeighted(img, 2, SharpenedImg, -1, 0, SharpenedImg);
	
	// 3. 将处理后的图像转换回位图格式
	Mat2Bmp(SharpenedImg, height, width);

	// 4. 显示图像
	Show_Bmp();
}


void CMFCImageProcessingDlg::OnClickedScaleButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 1. 将位图数据转换为 OpenCV Mat
	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	cv::Mat img(height, width, CV_8UC3);

	// 假设位图数据是 BGR 格式
	Bmp2Mat(img, height, width);

	// 2. 用 opencv resize 函数放缩图片
	UpdateData(TRUE);
	if (m_Scale_Height == 0 || m_Scale_Width==0)
	{
		AfxMessageBox(_T("倍数不能为零！"));
		return;
	}
	cv::Mat ResizedImg;
	cv::resize(img, ResizedImg, cv::Size(0,0),m_Scale_Width,m_Scale_Height);
	UpdateData(FALSE);

	// 更新位图信息
	int NewWidth = static_cast<int>(width * m_Scale_Width);
	int NewHeight = static_cast<int>(height * m_Scale_Height);
	bmpInfo.biWidth = NewWidth;
	bmpInfo.biHeight = NewHeight;
	bmpInfo.biSizeImage = NewWidth * NewHeight * (bmpInfo.biBitCount / 8);
	pBmpData = new BYTE[NewWidth * NewHeight * (bmpInfo.biBitCount / 8)];

	// 3. 将处理后的图像转换回位图格式
	Mat2Bmp(ResizedImg, NewHeight, NewWidth);

	Save_Open_Temp_Bmp();

	// 4. 显示图像
	Show_Bmp(m_Scale_Height, m_Scale_Width);
}

void CMFCImageProcessingDlg::OnStnClickedStaticPic()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCImageProcessingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	/*ismosaic = 1;*/

	CDialogEx::OnLButtonUp(nFlags, point);
}

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define _MinDefTmp_
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define _MaxDefTmp_
#endif



void CMFCImageProcessingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	if (ismosaic) {
		// 获取图片控件的指针
		CWnd* pWnd = GetDlgItem(IDC_STATIC_PIC);

		// 获取图片控件的客户区矩形
		CRect picRect;

		// 获取控件相对于屏幕的位置
		GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&picRect);

		//将控件转化为对话框上的相对位置
		ScreenToClient(picRect);

		//将鼠标位置转换为相对于控件的位置
		point.x -= picRect.left;
		point.y -= picRect.top;

		//转换为相对于控件的位置
		pWnd->GetClientRect(&picRect);

		// 获取控件的宽高
		int ctrlWidth = picRect.Width();
		int ctrlHeight = picRect.Height();

		// 计算图像的缩放比例
		double wid_hei_ratio = (double)bmpInfo.biWidth / (double)bmpInfo.biHeight;
		double scaleWidth = (double)ctrlWidth / bmpInfo.biWidth;
		double scaleHeight = (double)ctrlHeight / bmpInfo.biHeight;

		double scaleFactor = min(scaleWidth, scaleHeight);

		int imageWidth = static_cast<int>(bmpInfo.biWidth * scaleFactor);
		int imageHeight = static_cast<int>(bmpInfo.biHeight * scaleFactor);

		// 确定图像在控件中的位置（居中显示）
		int xOffset = (ctrlWidth - imageWidth) / 2;
		int yOffset = (ctrlHeight - imageHeight) / 2;

		// 将鼠标点击点从控件坐标转换为图像坐标
		int imgX = (point.x - xOffset) / scaleFactor;
		int imgY = (ctrlHeight - point.y - yOffset) / scaleFactor;


		// 确保点击点在图片范围内
		if (imgX >= 0 && imgX < bmpInfo.biWidth && imgY >= 0 && imgY < bmpInfo.biHeight) {
			int bpp = bmpInfo.biBitCount / 8; // 每个像素的字节数

			// 计算马赛克区域的边界
			int mosaicSize = nummo/ scaleFactor; // 设置马赛克的大小
			int halfSize = mosaicSize / 2;
			int left = max(imgX - halfSize, 0);
			int right = min(imgX + halfSize, bmpInfo.biWidth);
			int top = min(imgY + halfSize, bmpInfo.biHeight);
			int bottom = max(imgY - halfSize, 0);

			// 计算平均颜色
			COLORREF avgColor = RGB(0, 0, 0);
			long totalRed = 0;
			long totalGreen = 0;
			long totalBlue = 0;
			int count = 0;

			for (int j = bottom; j < top; ++j) {
				for (int i = left; i < right; ++i) {
					int index = (j * bmpInfo.biWidth + i) * bpp;
					COLORREF color = *((COLORREF*)(&pBmpData[index]));

					totalRed += GetRValue(color);
					totalGreen += GetGValue(color);
					totalBlue += GetBValue(color);
					++count;
				}
			}

			if (count > 0) {
				avgColor = RGB(totalRed / count, totalGreen / count, totalBlue / count);
			}

			// 填充马赛克区域
			for (int j = bottom; j < top; ++j) {
				for (int i = left; i < right; ++i) {
					int index = (j * bmpInfo.biWidth + i) * bpp;
					memcpy(&pBmpData[index], &avgColor, bpp);
				}
			}


			// 保存并打开临时位图
			Save_Open_Temp_Bmp();

			// 显示位图
			Show_Bmp();

		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCImageProcessingDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	ismosaic = 1;
}


void CMFCImageProcessingDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	ismosaic = 0;
}





void CMFCImageProcessingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (pScrollBar != nullptr)
	{
		// 强制转换成CSliderCtrl
		CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
		// 根据CSlider控件的ID 来判断是哪一个滚动条

		if (pSlider->GetDlgCtrlID() == IDC_SLIDER1)//对第一个滚动条进行操作
		{
			//获取当前位置值，放在变量nummo中
			nummo = Slmo.GetPos();
			//内容设置到编辑框中，编辑框的ID是IDC_EDIT_MO
			SetDlgItemInt(IDC_EDIT_MO, nummo);   //将数值显示到编辑框中
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
