# Microsoft Visual C++ generated build script - Do not modify

PROJ = DISPCALC
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\MYDOCU~1\DISPCALC\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP =             
RC = rc
CFLAGS_D_WEXE = /nologo /W3 /FR /G2 /Zi /D_DEBUG /Od /AM /GA /Fd"DISPCALC.PDB"
CFLAGS_R_WEXE = /nologo /W3 /FR /O1 /DNDEBUG /AM /GA
LFLAGS_D_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /CO /ALIGN:16 /STACK:10240
LFLAGS_R_WEXE = /NOLOGO /ONERROR:NOEXE /NOD /PACKC:61440 /ALIGN:16 /STACK:10240
LIBS_D_WEXE = mafxcwd oldnames libw commdlg shell olecli olesvr mlibcew
LIBS_R_WEXE = mafxcw oldnames libw commdlg shell olecli olesvr mlibcew
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = DISPCALC.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DISPCALC.SBR \
		DPMATH.SBR


DISPCALC_DEP = c:\mydocu~1\dispcalc\dpmath.h


DPMATH_DEP = 

all:	$(PROJ).EXE $(PROJ).BSC

DISPCALC.OBJ:	DISPCALC.C $(DISPCALC_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c DISPCALC.C

DISPCALC.RES:	DISPCALC.RC $(DISPCALC_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r DISPCALC.RC

DPMATH.OBJ:	DPMATH.C $(DPMATH_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c DPMATH.C


$(PROJ).EXE::	DISPCALC.RES

$(PROJ).EXE::	DISPCALC.OBJ DPMATH.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DISPCALC.OBJ +
DPMATH.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) DISPCALC.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	DISPCALC.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) DISPCALC.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<