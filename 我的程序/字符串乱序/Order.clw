; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COrderDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Order.h"

ClassCount=4
Class1=COrderApp
Class2=COrderDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ORDER_DIALOG

[CLS:COrderApp]
Type=0
HeaderFile=Order.h
ImplementationFile=Order.cpp
Filter=N

[CLS:COrderDlg]
Type=0
HeaderFile=OrderDlg.h
ImplementationFile=OrderDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=OrderDlg.h
ImplementationFile=OrderDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ORDER_DIALOG]
Type=1
Class=COrderDlg
ControlCount=7
Control1=IDC_EDIT_CONTENT,edit,1350631552
Control2=IDC_EDIT_FILENAME,edit,1350631552
Control3=IDC_EDIT_NUMBER,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BTN_BEGIN,button,1342242816

