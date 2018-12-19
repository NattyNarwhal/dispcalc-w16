#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "dpmath.h"
#include "resource.h"     
                          
int calcMode = DP_MODE_DIST;
BOOL metric = FALSE;

char appName[] = "DispCalc";
char winTitle[] = "Display Calculator";
/* These are loaded in by LoadString on demand */
char *dynWinTitle, *aboutText, *errorText;

/* Make these globals because we'd otherwise use Get* a lot */
HMENU hmenu;
HWND pxxi, pxyi, ri, si, ai, di, ci,
	pxxo, pxyo, ro, so, ppio, dio, ixo, iyo;
HANDLE hinst;

void PASCAL ChangeSolveMode (hwnd, type)
	HWND hwnd;
	int type;
{
	if (dynWinTitle == NULL) {
		dynWinTitle = LocalAlloc (LMEM_FIXED, 255);
	 	LoadString (hinst, IDS_ENTRYERR, dynWinTitle, 255);
	}
	switch (type)
	{
	case DP_MODE_DIST:
		LoadString (hinst, IDS_TITLE_DIST, dynWinTitle, 255);
		calcMode = DP_MODE_DIST;
		CheckMenuItem (hmenu, ID_MODE_DISTANCE, MF_CHECKED);
		CheckMenuItem (hmenu, ID_MODE_SIZE, MF_UNCHECKED);
		CheckMenuItem (hmenu, ID_MODE_RESOLUTION, MF_UNCHECKED);
		EnableWindow (pxxi, TRUE);
		EnableWindow (pxyi, TRUE);
		EnableWindow (ri  , FALSE);
		EnableWindow (si,   TRUE);
		EnableWindow (ai,   TRUE);
		EnableWindow (di,   FALSE);
		EnableWindow (ci,   TRUE);
		break;
	case DP_MODE_SIZE:
		LoadString (hinst, IDS_TITLE_SIZE, dynWinTitle, 255);
		calcMode = DP_MODE_SIZE;
		CheckMenuItem (hmenu, ID_MODE_DISTANCE, MF_UNCHECKED);
		CheckMenuItem (hmenu, ID_MODE_SIZE, MF_CHECKED);
		CheckMenuItem (hmenu, ID_MODE_RESOLUTION, MF_UNCHECKED);
		EnableWindow (pxxi, TRUE);
		EnableWindow (pxyi, TRUE);
		EnableWindow (ri  , FALSE);
		EnableWindow (si,   FALSE);
		EnableWindow (ai,   TRUE);
		EnableWindow (di,   TRUE);
		EnableWindow (ci,   TRUE);
		break;
	case DP_MODE_RES:                    
		LoadString (hinst, IDS_TITLE_RES, dynWinTitle, 255);
		calcMode = DP_MODE_RES;
		CheckMenuItem (hmenu, ID_MODE_DISTANCE, MF_UNCHECKED);
		CheckMenuItem (hmenu, ID_MODE_SIZE, MF_UNCHECKED);
		CheckMenuItem (hmenu, ID_MODE_RESOLUTION, MF_CHECKED);
		EnableWindow (pxxi, FALSE);
		EnableWindow (pxyi, FALSE);
		EnableWindow (ri  , TRUE);
		EnableWindow (si,   TRUE);
		EnableWindow (ai,   TRUE);
		EnableWindow (di,   TRUE);
		EnableWindow (ci,   TRUE);
		break;
	}
	SetWindowText (hwnd, dynWinTitle);
}

BOOL PASCAL GetWindowDouble (hwnd, res)
	HWND hwnd;
	long double *res;
{                  
	char buf [255];
	buf [0] = '\0';
	GetWindowText (hwnd, buf, 254);
	if (buf [0] == '\0') {
		return FALSE;
	}
	/* XXX: strold is more tolerant than it should be; better error checking */
	*res = _strtold (buf, NULL);
	return TRUE;
}

void PASCAL SetWindowDouble (hwnd, d)
	HWND hwnd;
	long double d;
{
	char buf [255];
	_snprintf (buf, 255, "%Lf", d);
	SetWindowText (hwnd, buf); 
}

void HandleEntryError (hwnd)
	HWND hwnd;
{
	if (errorText == NULL) {
		errorText = LocalAlloc (LMEM_FIXED, 255);
	 	LoadString (hinst, IDS_ENTRYERR, errorText, 255);
	}
	MessageBox (hwnd, errorText, winTitle, MB_ICONSTOP);
	SetFocus (hwnd);
}

void PASCAL RunCalculate (hwnd)
	HWND hwnd;
{
	long double pxx, pxy, pxd, r, s, a, d, c, ppi, inx, iny;
 	switch (calcMode)
 	{
 	case DP_MODE_DIST:
 		if (!GetWindowDouble (pxxi, &pxx) || pxx <= 0) {
 			HandleEntryError (pxxi);
 			return;
 		}
 		if (!GetWindowDouble (pxyi, &pxy) || pxy <= 0) {
 			HandleEntryError (pxyi);
 			return;
 		}
 		if (!GetWindowDouble (si, &s) || s <= 0) {
 			HandleEntryError (si);
 			return;
 		}
 		if (!GetWindowDouble (ai, &a) || a <= 0) {
 			HandleEntryError (ai);
 			return;
 		}
 		if (!GetWindowDouble (ci, &c) || c <= 0) {
 			HandleEntryError (ci);
 			return;
 		}
 		a = AdjustedAcuity (a, c);      
 		r = AspectRatio (pxx, pxy);
 		ppi = PPI (pxx, pxy, s); //sqrtl (powl (pxx, 2) + powl (pxy, 2)) / s;
 		d = OneInchDistance (a) * (1 / ppi);
 		SetWindowDouble (ro, r);
 		SetWindowDouble (dio, d);
 		SetWindowDouble (ppio, ppi);
 		break;
 	case DP_MODE_SIZE:
 		if (!GetWindowDouble (pxxi, &pxx) || pxx <= 0) {
 			HandleEntryError (pxxi);
 			return;
 		}
 		if (!GetWindowDouble (pxyi, &pxy) || pxy <= 0) {
 			HandleEntryError (pxyi);
 			return;
 		}
 		if (!GetWindowDouble (di, &d) || d <= 0) {
 			HandleEntryError (di);
 			return;
 		}
 		if (!GetWindowDouble (ai, &a) || a <= 0) {
 			HandleEntryError (ai);
 			return;
 		}
 		if (!GetWindowDouble (ci, &c) || c <= 0) {
 			HandleEntryError (ci);
 			return;
 		}
 		a = AdjustedAcuity (a, c);      
 		r = AspectRatio (pxx, pxy);
 		ppi = OptimalPPI (d, a);
 		s = DisplaySize (pxx, pxy, ppi);
 		SetWindowDouble (ro, r);
 		SetWindowDouble (ppio, ppi);
 		SetWindowDouble (so, s);
 		break;
 	case DP_MODE_RES:
 		if (!GetWindowDouble (si, &s) || s <= 0) {
 			HandleEntryError (si);
 			return;
 		}
 		if (!GetWindowDouble (ri, &r) || s <= 0) {
 			HandleEntryError (ri);
 			return;
 		}
 		if (!GetWindowDouble (di, &d) || d <= 0) {
 			HandleEntryError (di);
 			return;
 		}
 		if (!GetWindowDouble (ai, &a) || a <= 0) {
 			HandleEntryError (ai);
 			return;
 		}
 		if (!GetWindowDouble (ci, &c) || c <= 0) {
 			HandleEntryError (ci);
 			return;
 		}
 		a = AdjustedAcuity (a, c);
 		ppi = OptimalPPI (d, a);
 		pxd = DiagResolution(s, ppi);;
 		pxy = VResFromDiag (pxd, r);
 		pxx = r * pxy;
 		SetWindowDouble (pxxo, pxx);
 		SetWindowDouble (pxyo, pxy);
 		SetWindowDouble (ppio, ppi);
 		break;
 	}
 	iny = PhysVRes (s, r);
 	inx = r * iny;
 	if (metric) {
 		inx *= 25.4;
 		iny *= 25.4;
 	}
 	SetWindowDouble (ixo, inx);
 	SetWindowDouble (iyo, iny);
}

BOOL PASCAL ProcessDialogCommand (hwnd, cmd)
	HWND hwnd;
	WORD cmd;
{
	UINT metricState;
	
	switch (cmd)
	{
	case IDOK:
		RunCalculate (hwnd);
		return TRUE;
	case ID_HELP_ABOUT:
		if (aboutText == NULL) {
			aboutText = LocalAlloc (LMEM_FIXED, 255);
		 	LoadString (hinst, IDS_ABOUTTEXT, aboutText, 255);
		}
		MessageBox (hwnd, aboutText, winTitle, 0);
		return TRUE;
	case ID_MODE_DISTANCE:
		ChangeSolveMode (hwnd, DP_MODE_DIST);
		return TRUE;
	case ID_MODE_SIZE:
		ChangeSolveMode (hwnd, DP_MODE_SIZE);
		return TRUE; 
	case ID_MODE_RESOLUTION:
		ChangeSolveMode (hwnd, DP_MODE_RES);
		return TRUE;
	case ID_MODE_METRICPHYSICALDIMENSION:
		metricState = GetMenuState (hmenu,
			ID_MODE_METRICPHYSICALDIMENSION, MF_BYCOMMAND);
		/* toggle it */
		metric = !(metricState & MF_CHECKED);
		CheckMenuItem (hmenu, ID_MODE_METRICPHYSICALDIMENSION,
			metric ? MF_CHECKED : MF_UNCHECKED);
		return TRUE;
	default:
		return FALSE;  	
	}
}

void PASCAL InitializeChildHandles (hwnd)
	HWND hwnd;
{
	hmenu = GetMenu (hwnd);
	pxxi  = GetDlgItem (hwnd, IDC_PIXDEM_X_IN);
	pxyi  = GetDlgItem (hwnd, IDC_PIXDEM_Y_IN);
	ri    = GetDlgItem (hwnd, IDC_RATIO_IN);
	si    = GetDlgItem (hwnd, IDC_SIZE_IN);
	ai    = GetDlgItem (hwnd, IDC_ACUITY_IN);
	di    = GetDlgItem (hwnd, IDC_DISTANCE_IN);
	ci    = GetDlgItem (hwnd, IDC_CYCLES_IN);
	pxxo  = GetDlgItem (hwnd, IDC_PIXDEM_X_OUT);
	pxyo  = GetDlgItem (hwnd, IDC_PIXDEM_Y_OUT);
	ro    = GetDlgItem (hwnd, IDC_RATIO_OUT);
	so    = GetDlgItem (hwnd, IDC_SIZE_OUT);
	ppio  = GetDlgItem (hwnd, IDC_PPI_OUT);
	dio   = GetDlgItem (hwnd, IDC_DISTANCE_OUT);
	ixo   = GetDlgItem (hwnd, IDC_PHYSDEM_X_OUT);
	iyo   = GetDlgItem (hwnd, IDC_PHYSDEM_Y_OUT);
}

BOOL FAR PASCAL DialogProc (hwnd, iMsg, wParam, lParam)
 	HWND hwnd;
 	unsigned int iMsg;
 	WORD wParam;
 	LONG lParam;
{
	switch (iMsg)
	{
	case WM_INITDIALOG:
		InitializeChildHandles (hwnd);
		ChangeSolveMode (hwnd, DP_MODE_DIST);
		SetDlgItemText (hwnd, IDC_ACUITY_IN, "20");
		SetDlgItemText (hwnd, IDC_CYCLES_IN, "30");
		return TRUE;
	/* TODO: Process Key events for auto-updating. */
	case WM_COMMAND:
		return ProcessDialogCommand (hwnd, wParam);
	case WM_CLOSE:
		DestroyWindow (hwnd);
		return TRUE;
	case WM_DESTROY:
		PostQuitMessage (NULL);                          
		return TRUE;
	default:
		return FALSE;
	}
}

int PASCAL WinMain (hInstance, hPrevInst, lpszCmdLine, nCmdShow)
	HANDLE hInstance, hPrevInst;
	LPSTR lpszCmdLine;
	int nCmdShow;
{
	int ret;
	HWND hwnd;
	FARPROC dlgProc;
	MSG msg;
	
	hinst = hInstance;
	
	if ((dlgProc = MakeProcInstance (DialogProc, hInstance)) == NULL) {
		MessageBox (NULL, "There was an error creating the dialog procedure.", winTitle, MB_ICONSTOP);
		return 1;
	}
	/* The API is a filthy liar for Win16. The template name is an ID, NOT a string. */
	if ((hwnd = CreateDialogParam (hInstance, MainDialog, NULL, dlgProc, 0)) == NULL) {
		MessageBox (NULL, "There was an error creating the dialog window.", winTitle, MB_ICONSTOP);
		return 2;
	}
	EnableWindow (hwnd, TRUE);
	ShowWindow (hwnd, nCmdShow);
	
	while (GetMessage (&msg, NULL, 0, 0)) {   
		if (!IsDialogMessage (hwnd, &msg)) {
			TranslateMessage (&msg);
			DispatchMessage (&msg);
		}
	}
	FreeProcInstance (dlgProc);
	
 	return ret;
}