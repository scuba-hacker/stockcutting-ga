; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGASettingsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GA.h"
LastPage=0

ClassCount=12
Class1=CGAApp
Class2=CGADoc
Class3=CGAView
Class4=CMainFrame

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDD_GOTO_TEST_DIALOG
Class5=CAboutDlg
Resource3=IDR_MAINFRAME (English (U.S.))
Resource4=IDD_BATCH_SETTINGS
Class6=CGotoTestDialog
Resource5=IDD_ORDER_DIALOG
Class7=COrderDialog
Resource6=IDD_N_SWAP_DIALOG
Resource7=IDD_ABOUTBOX (English (U.S.))
Class8=CNSwapDialog
Class9=CGASettingsDialog
Class10=CSetRegimeDialog
Class11=OutputView
Resource8=IDD_SET_REGIME_DIALOG
Class12=CBatchDialog
Resource9=IDD_GA_SETTINGS

[CLS:CGAApp]
Type=0
HeaderFile=GA.h
ImplementationFile=GA.cpp
Filter=N
LastObject=CGAApp

[CLS:CGADoc]
Type=0
HeaderFile=GADoc.h
ImplementationFile=GADoc.cpp
Filter=N
LastObject=CGADoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CGAView]
Type=0
HeaderFile=GAView.h
ImplementationFile=GAView.cpp
Filter=C
LastObject=CGAView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_EXPORT_CURRENT
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=GA.cpp
ImplementationFile=GA.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=17
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_HELP_FINDER
Command17=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=16
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_EXPORT_CURRENT
Command2=ID_FILE_PRINT
Command3=ID_FILE_PRINT_SETUP
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_VIEW_REFRESH
Command8=ID_VIEW_NORMALISE
Command9=ID_VIEW_SHUFFLE
Command10=ID_VIEW_ORDER
Command11=ID_VIEW_NEXTTEST
Command12=ID_VIEW_PREVTEST
Command13=ID_VIEW_NEXT10TEST
Command14=ID_VIEW_PREV10TEST
Command15=ID_VIEW_GOTO_TEST
Command16=ID_VIEW_NEXT_SHEET
Command17=ID_VIEW_PREV_SHEET
Command18=ID_SET_REGIME
Command19=ID_GA_SETTINGS
Command20=ID_RUN_GA
Command21=ID_BATCH_PROCESS
Command22=ID_DETAILED_OUTPUT
Command23=ID_APP_ABOUT
CommandCount=23

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_VIEW_NEXT_SHEET
Command2=ID_VIEW_PREV_SHEET
Command3=ID_VIEW_PREV10TEST
Command4=ID_VIEW_NEXT10TEST
Command5=ID_RUN_GA
Command6=ID_VIEW_GOTO_TEST
Command7=ID_EXPORT_CURRENT
Command8=ID_VIEW_NORMALISE
Command9=ID_VIEW_ORDER
Command10=ID_FILE_PRINT
Command11=ID_VIEW_REFRESH
Command12=ID_GA_SETTINGS
Command13=ID_SET_REGIME
Command14=ID_HELP
Command15=ID_CONTEXT_HELP
Command16=ID_NEXT_PANE
Command17=ID_PREV_PANE
Command18=ID_VIEW_SHUFFLE
Command19=ID_VIEW_NEXTTEST
Command20=ID_VIEW_PREVTEST
CommandCount=20

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GOTO_TEST_DIALOG]
Type=1
Class=CGotoTestDialog
ControlCount=4
Control1=IDC_TEST_NUMBER,edit,1350639744
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CGotoTestDialog]
Type=0
HeaderFile=GotoTestDialog.h
ImplementationFile=GotoTestDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGotoTestDialog

[DLG:IDD_ORDER_DIALOG]
Type=1
Class=COrderDialog
ControlCount=3
Control1=IDC_GENE_ORDER,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[CLS:COrderDialog]
Type=0
HeaderFile=OrderDialog.h
ImplementationFile=OrderDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=COrderDialog

[DLG:IDD_N_SWAP_DIALOG]
Type=1
Class=CNSwapDialog
ControlCount=4
Control1=IDC_SWAP_NUMBER,edit,1350639744
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CNSwapDialog]
Type=0
HeaderFile=NSwapDialog.h
ImplementationFile=NSwapDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CNSwapDialog
VirtualFilter=dWC

[DLG:IDD_GA_SETTINGS]
Type=1
Class=CGASettingsDialog
ControlCount=74
Control1=IDC_SIMILARITIES_INDEX,edit,1350631552
Control2=IDC_STATIC,button,1342177287
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_BREED_SELECTION,combobox,1344340227
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_REMOVAL_SELECTION,combobox,1344340227
Control9=IDC_STATIC,static,1342308354
Control10=IDC_OPERATOR_ADAPTOR,combobox,1344339971
Control11=IDC_STATIC,static,1342308354
Control12=IDC_GENERATION_MODEL,combobox,1344339971
Control13=IDC_ORDER_CHECK,button,1342242851
Control14=IDC_POSITION_CHECK,button,1342242851
Control15=IDC_HALF_UNIFORM_CHECK,button,1342242851
Control16=IDC_HEURISTIC_N_POINT_CHECK,button,1342242851
Control17=IDC_ORIENTATION_N_POINT_CHECK,button,1342242851
Control18=IDC_SINGLE_SWAP_CHECK,button,1342242851
Control19=IDC_MULTI_SWAP_CHECK,button,1342242851
Control20=IDC_INVERSION_CHECK,button,1342242851
Control21=IDC_HEURISTIC_FLIP_CHECK,button,1342242851
Control22=IDC_SHUNT_CHECK,button,1342242851
Control23=IDC_ORIENTATION_FLIP_CHECK,button,1342242851
Control24=IDC_CROSSOVER_OPERATORS,button,1342177287
Control25=IDC_STATIC,static,1342308354
Control26=IDC_POPULATION_SIZE,combobox,1344339971
Control27=IDC_CATACLYSMS_ACTIVE,button,1342242851
Control28=IDC_STATIC,static,1342308354
Control29=IDC_REPORT_EVERY,combobox,1344340227
Control30=IDC_CATACLYSMIC_MUTATION,button,1342177287
Control31=IDC_STATIC,static,1342308354
Control32=IDC_STATIC,static,1342308354
Control33=IDC_STATIC,static,1342308354
Control34=IDC_MUTATION_RATE,edit,1350631552
Control35=IDC_CATACLYSM_TRIGGER,edit,1350631552
Control36=IDC_GENERATION_EPOCH,edit,1350631552
Control37=IDC_STATIC,static,1342308354
Control38=IDC_HILL_CLIMBING_SETTINGS,button,1342177287
Control39=IDC_STATIC,button,1342177287
Control40=IDC_RESTART_THRESHOLD,edit,1350631552
Control41=IDC_STATIC,static,1342308354
Control42=IDC_NEIGHBOURHOOD,edit,1350631552
Control43=IDC_STATIC,static,1342308354
Control44=IDC_SIMULATED_ANNEALING_SETTINGS,button,1342177287
Control45=IDC_START_TEMP,edit,1350631552
Control46=IDC_STATIC,static,1342308354
Control47=IDC_END_TEMP,edit,1350631552
Control48=IDC_STATIC,static,1342308354
Control49=IDC_COOLING_RATIO,edit,1350631552
Control50=IDC_STATIC,static,1342308354
Control51=IDC_EDGE_RECOMBINATION,button,1342242851
Control52=IDC_SEG_POSITION_BASED,button,1342242851
Control53=IDC_SEG_ORDER_BASED,button,1342242851
Control54=IDC_STATIC,button,1342177287
Control55=IDC_TOURNAMENT_SIZE,edit,1350631552
Control56=IDC_STATIC,static,1342308354
Control57=IDC_MULTI_SWAP_SIZE,edit,1350631552
Control58=IDC_STATIC,static,1342308354
Control59=IDC_MAX_SEGMENT_LENGTH,edit,1350631552
Control60=IDC_STATIC,static,1342308354
Control61=IDC_MIN_SEGMENT_LENGTH,edit,1350631552
Control62=IDC_STATIC,static,1342308354
Control63=IDC_SEGMENT_RESTRICTIONS,button,1342242851
Control64=IDC_N_POINT_SIZE,edit,1350631552
Control65=IDC_STATIC,static,1342308354
Control66=IDC_SEGMENT_SETTINGS,button,1342177287
Control67=IDC_COBRA_ITERATIONS,edit,1350631552
Control68=IDC_STATIC,static,1342308354
Control69=IDC_FLIP_SIZE,edit,1350631552
Control70=IDC_STATIC,static,1342308354
Control71=IDC_STATIC,static,1342308354
Control72=IDC_SETTINGS,combobox,1344340226
Control73=IDC_STORE,button,1342254848
Control74=IDC_REMOVE_FROM_SETUPS,button,1342254848

[CLS:CGASettingsDialog]
Type=0
HeaderFile=GASettingsDialog.h
ImplementationFile=GASettingsDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NEIGHBOURHOOD
VirtualFilter=dWC

[DLG:IDD_SET_REGIME_DIALOG]
Type=1
Class=CSetRegimeDialog
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LEFTMOST,button,1342308361
Control4=IDC_ITOPMOST,button,1342177289
Control5=IDC_TOPMOST,button,1342177289
Control6=IDC_DYNAMIC,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_ILEFTMOST,button,1342177289

[CLS:CSetRegimeDialog]
Type=0
HeaderFile=SetRegimeDialog.h
ImplementationFile=SetRegimeDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DYNAMIC
VirtualFilter=dWC

[CLS:OutputView]
Type=0
HeaderFile=OutputView.h
ImplementationFile=OutputView.cpp
BaseClass=CScrollView
Filter=C
LastObject=ID_APP_ABOUT

[DLG:IDD_BATCH_SETTINGS]
Type=1
Class=CBatchDialog
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_LAYOUT_COUNT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EXPERIMENT_COUNT,edit,1350631552
Control7=IDC_STATIC,static,1342308353
Control8=IDC_STATIC,static,1342308352
Control9=IDC_PREFIX,edit,1350631552

[CLS:CBatchDialog]
Type=0
HeaderFile=BatchDialog.h
ImplementationFile=BatchDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CBatchDialog

