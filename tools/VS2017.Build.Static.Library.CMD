@ECHO OFF

SET VU_VSVER=2017
SET VU_TSVER=v141
SET VU_VSDEV=%ProgramFiles(x86)%\Microsoft Visual Studio\%VU_VSVER%\%%L\Common7\Tools\VsDevCmd.bat

CALL Others\VSX.Update.License.Type.CMD
CALL Others\VSX.Build.Static.Library.CMD