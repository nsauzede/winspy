; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGlowDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Glow.h"

ClassCount=3
Class1=CGlowApp
Class2=CGlowDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_GLOW_DIALOG

[CLS:CGlowApp]
Type=0
HeaderFile=Glow.h
ImplementationFile=Glow.cpp
Filter=N

[CLS:CGlowDlg]
Type=0
HeaderFile=GlowDlg.h
ImplementationFile=GlowDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CGlowDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=GlowDlg.h
ImplementationFile=GlowDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GLOW_DIALOG]
Type=1
Class=CGlowDlg
ControlCount=2
Control1=IDC_STATUS,edit,1484849280
Control2=IDC_ALLOW_GLOW,button,1342242819

