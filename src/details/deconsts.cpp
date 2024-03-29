/**
 * @file   strizeconsts.cpp
 * @author Vic P.
 * @brief  Implementation for Decode Constants
 */

#include "Vutils.h"

#include <Windows.h>

namespace vu
{

struct MappingConstants
{
  ulong id;
  char* str;
};

#define DEF_LIST(name) static const MappingConstants name[] = \

#define DEF_CONST(id) { id, (char*) # id }
#define DEF_CONST_STRING(id, str) { id, (char*) # str}

// Decoding - Encoding

#define DECODE_CONSTANT_A(lst, id) decode_constant_A(lst, lengthof(lst), id);
#define ENCODE_CONSTANT_A(lst, id) encode_constant_A(lst, lengthof(lst), str);

std::string vuapi decode_constant_A(const MappingConstants lst[], int size, const ulong id)
{
  std::string result = "<Unknown>";

  for (int i = 0; i < size; i++)
  {
    auto& e = lst[i];
    if (e.id == id)
    {
      result = e.str;
      break;
    }
  }

  return result;
}

ulong vuapi encode_constant_A(const MappingConstants lst[], int size, const std::string& str)
{
  ulong result = -1;

  for (int i = 0; i < size; i++)
  {
    auto& e = lst[i];
    if (compare_string_A(e.str, str, true))
    {
      result = e.id;
      break;
    }
  }

  return result;
}

// Window Message @refer to window.cpp

DEF_LIST(list_win_messages)
{
  DEF_CONST_STRING(0x0000, WM_NULL),
  DEF_CONST_STRING(0x0001, WM_CREATE),
  DEF_CONST_STRING(0x0002, WM_DESTROY),
  DEF_CONST_STRING(0x0003, WM_MOVE),
  DEF_CONST_STRING(0x0005, WM_SIZE),
  DEF_CONST_STRING(0x0006, WM_ACTIVATE),
  DEF_CONST_STRING(0x0007, WM_SETFOCUS),
  DEF_CONST_STRING(0x0008, WM_KILLFOCUS),
  DEF_CONST_STRING(0x000A, WM_ENABLE),
  DEF_CONST_STRING(0x000B, WM_SETREDRAW),
  DEF_CONST_STRING(0x000C, WM_SETTEXT),
  DEF_CONST_STRING(0x000D, WM_GETTEXT),
  DEF_CONST_STRING(0x000E, WM_GETTEXTLENGTH),
  DEF_CONST_STRING(0x000F, WM_PAINT),
  DEF_CONST_STRING(0x0010, WM_CLOSE),
  DEF_CONST_STRING(0x0011, WM_QUERYENDSESSION),
  DEF_CONST_STRING(0x0013, WM_QUERYOPEN),
  DEF_CONST_STRING(0x0016, WM_ENDSESSION),
  DEF_CONST_STRING(0x0012, WM_QUIT),
  DEF_CONST_STRING(0x0014, WM_ERASEBKGND),
  DEF_CONST_STRING(0x0015, WM_SYSCOLORCHANGE),
  DEF_CONST_STRING(0x0018, WM_SHOWWINDOW),
  DEF_CONST_STRING(0x001A, WM_WININICHANGE),
  DEF_CONST_STRING(0x001B, WM_DEVMODECHANGE),
  DEF_CONST_STRING(0x001C, WM_ACTIVATEAPP),
  DEF_CONST_STRING(0x001D, WM_FONTCHANGE),
  DEF_CONST_STRING(0x001E, WM_TIMECHANGE),
  DEF_CONST_STRING(0x001F, WM_CANCELMODE),
  DEF_CONST_STRING(0x0020, WM_SETCURSOR),
  DEF_CONST_STRING(0x0021, WM_MOUSEACTIVATE),
  DEF_CONST_STRING(0x0022, WM_CHILDACTIVATE),
  DEF_CONST_STRING(0x0023, WM_QUEUESYNC),
  DEF_CONST_STRING(0x0024, WM_GETMINMAXINFO),
  DEF_CONST_STRING(0x0026, WM_PAINTICON),
  DEF_CONST_STRING(0x0027, WM_ICONERASEBKGND),
  DEF_CONST_STRING(0x0028, WM_NEXTDLGCTL),
  DEF_CONST_STRING(0x002A, WM_SPOOLERSTATUS),
  DEF_CONST_STRING(0x002B, WM_DRAWITEM),
  DEF_CONST_STRING(0x002C, WM_MEASUREITEM),
  DEF_CONST_STRING(0x002D, WM_DELETEITEM),
  DEF_CONST_STRING(0x002E, WM_VKEYTOITEM),
  DEF_CONST_STRING(0x002F, WM_CHARTOITEM),
  DEF_CONST_STRING(0x0030, WM_SETFONT),
  DEF_CONST_STRING(0x0031, WM_GETFONT),
  DEF_CONST_STRING(0x0032, WM_SETHOTKEY),
  DEF_CONST_STRING(0x0033, WM_GETHOTKEY),
  DEF_CONST_STRING(0x0037, WM_QUERYDRAGICON),
  DEF_CONST_STRING(0x0039, WM_COMPAREITEM),
  DEF_CONST_STRING(0x003D, WM_GETOBJECT),
  DEF_CONST_STRING(0x0041, WM_COMPACTING),
  DEF_CONST_STRING(0x0044, WM_COMMNOTIFY),
  DEF_CONST_STRING(0x0046, WM_WINDOWPOSCHANGING),
  DEF_CONST_STRING(0x0047, WM_WINDOWPOSCHANGED),
  DEF_CONST_STRING(0x0048, WM_POWER),
  DEF_CONST_STRING(0x004A, WM_COPYDATA),
  DEF_CONST_STRING(0x004B, WM_CANCELJOURNAL),
  DEF_CONST_STRING(0x004E, WM_NOTIFY),
  DEF_CONST_STRING(0x0050, WM_INPUTLANGCHANGEREQUEST),
  DEF_CONST_STRING(0x0051, WM_INPUTLANGCHANGE),
  DEF_CONST_STRING(0x0052, WM_TCARD),
  DEF_CONST_STRING(0x0053, WM_HELP),
  DEF_CONST_STRING(0x0054, WM_USERCHANGED),
  DEF_CONST_STRING(0x0055, WM_NOTIFYFORMAT),
  DEF_CONST_STRING(0x007B, WM_CONTEXTMENU),
  DEF_CONST_STRING(0x007C, WM_STYLECHANGING),
  DEF_CONST_STRING(0x007D, WM_STYLECHANGED),
  DEF_CONST_STRING(0x007E, WM_DISPLAYCHANGE),
  DEF_CONST_STRING(0x007F, WM_GETICON),
  DEF_CONST_STRING(0x0080, WM_SETICON),
  DEF_CONST_STRING(0x0081, WM_NCCREATE),
  DEF_CONST_STRING(0x0082, WM_NCDESTROY),
  DEF_CONST_STRING(0x0083, WM_NCCALCSIZE),
  DEF_CONST_STRING(0x0084, WM_NCHITTEST),
  DEF_CONST_STRING(0x0085, WM_NCPAINT),
  DEF_CONST_STRING(0x0086, WM_NCACTIVATE),
  DEF_CONST_STRING(0x0087, WM_GETDLGCODE),
  DEF_CONST_STRING(0x0088, WM_SYNCPAINT),
  DEF_CONST_STRING(0x00A0, WM_NCMOUSEMOVE),
  DEF_CONST_STRING(0x00A1, WM_NCLBUTTONDOWN),
  DEF_CONST_STRING(0x00A2, WM_NCLBUTTONUP),
  DEF_CONST_STRING(0x00A3, WM_NCLBUTTONDBLCLK),
  DEF_CONST_STRING(0x00A4, WM_NCRBUTTONDOWN),
  DEF_CONST_STRING(0x00A5, WM_NCRBUTTONUP),
  DEF_CONST_STRING(0x00A6, WM_NCRBUTTONDBLCLK),
  DEF_CONST_STRING(0x00A7, WM_NCMBUTTONDOWN),
  DEF_CONST_STRING(0x00A8, WM_NCMBUTTONUP),
  DEF_CONST_STRING(0x00A9, WM_NCMBUTTONDBLCLK),
  DEF_CONST_STRING(0x00AB, WM_NCXBUTTONDOWN),
  DEF_CONST_STRING(0x00AC, WM_NCXBUTTONUP),
  DEF_CONST_STRING(0x00AD, WM_NCXBUTTONDBLCLK),
  DEF_CONST_STRING(0x00FE, WM_INPUT_DEVICE_CHANGE),
  DEF_CONST_STRING(0x00FF, WM_INPUT),
  DEF_CONST_STRING(0x0100, WM_KEYFIRST),
  DEF_CONST_STRING(0x0100, WM_KEYDOWN),
  DEF_CONST_STRING(0x0101, WM_KEYUP),
  DEF_CONST_STRING(0x0102, WM_CHAR),
  DEF_CONST_STRING(0x0103, WM_DEADCHAR),
  DEF_CONST_STRING(0x0104, WM_SYSKEYDOWN),
  DEF_CONST_STRING(0x0105, WM_SYSKEYUP),
  DEF_CONST_STRING(0x0106, WM_SYSCHAR),
  DEF_CONST_STRING(0x0107, WM_SYSDEADCHAR),
  DEF_CONST_STRING(0x0109, WM_UNICHAR),
  DEF_CONST_STRING(0x0109, WM_KEYLAST),
  DEF_CONST_STRING(0x0108, WM_KEYLAST),
  DEF_CONST_STRING(0x010D, WM_IME_STARTCOMPOSITION),
  DEF_CONST_STRING(0x010E, WM_IME_ENDCOMPOSITION),
  DEF_CONST_STRING(0x010F, WM_IME_COMPOSITION),
  DEF_CONST_STRING(0x010F, WM_IME_KEYLAST),
  DEF_CONST_STRING(0x0110, WM_INITDIALOG),
  DEF_CONST_STRING(0x0111, WM_COMMAND),
  DEF_CONST_STRING(0x0112, WM_SYSCOMMAND),
  DEF_CONST_STRING(0x0113, WM_TIMER),
  DEF_CONST_STRING(0x0114, WM_HSCROLL),
  DEF_CONST_STRING(0x0115, WM_VSCROLL),
  DEF_CONST_STRING(0x0116, WM_INITMENU),
  DEF_CONST_STRING(0x0117, WM_INITMENUPOPUP),
  DEF_CONST_STRING(0x0119, WM_GESTURE),
  DEF_CONST_STRING(0x011A, WM_GESTURENOTIFY),
  DEF_CONST_STRING(0x011F, WM_MENUSELECT),
  DEF_CONST_STRING(0x0120, WM_MENUCHAR),
  DEF_CONST_STRING(0x0121, WM_ENTERIDLE),
  DEF_CONST_STRING(0x0122, WM_MENURBUTTONUP),
  DEF_CONST_STRING(0x0123, WM_MENUDRAG),
  DEF_CONST_STRING(0x0124, WM_MENUGETOBJECT),
  DEF_CONST_STRING(0x0125, WM_UNINITMENUPOPUP),
  DEF_CONST_STRING(0x0126, WM_MENUCOMMAND),
  DEF_CONST_STRING(0x0127, WM_CHANGEUISTATE),
  DEF_CONST_STRING(0x0128, WM_UPDATEUISTATE),
  DEF_CONST_STRING(0x0129, WM_QUERYUISTATE),
  DEF_CONST_STRING(0x0132, WM_CTLCOLORMSGBOX),
  DEF_CONST_STRING(0x0133, WM_CTLCOLOREDIT),
  DEF_CONST_STRING(0x0134, WM_CTLCOLORLISTBOX),
  DEF_CONST_STRING(0x0135, WM_CTLCOLORBTN),
  DEF_CONST_STRING(0x0136, WM_CTLCOLORDLG),
  DEF_CONST_STRING(0x0137, WM_CTLCOLORSCROLLBAR),
  DEF_CONST_STRING(0x0138, WM_CTLCOLORSTATIC),
  DEF_CONST_STRING(0x0200, WM_MOUSEFIRST),
  DEF_CONST_STRING(0x0200, WM_MOUSEMOVE),
  DEF_CONST_STRING(0x0201, WM_LBUTTONDOWN),
  DEF_CONST_STRING(0x0202, WM_LBUTTONUP),
  DEF_CONST_STRING(0x0203, WM_LBUTTONDBLCLK),
  DEF_CONST_STRING(0x0204, WM_RBUTTONDOWN),
  DEF_CONST_STRING(0x0205, WM_RBUTTONUP),
  DEF_CONST_STRING(0x0206, WM_RBUTTONDBLCLK),
  DEF_CONST_STRING(0x0207, WM_MBUTTONDOWN),
  DEF_CONST_STRING(0x0208, WM_MBUTTONUP),
  DEF_CONST_STRING(0x0209, WM_MBUTTONDBLCLK),
  DEF_CONST_STRING(0x020A, WM_MOUSEWHEEL),
  DEF_CONST_STRING(0x020B, WM_XBUTTONDOWN),
  DEF_CONST_STRING(0x020C, WM_XBUTTONUP),
  DEF_CONST_STRING(0x020D, WM_XBUTTONDBLCLK),
  DEF_CONST_STRING(0x020E, WM_MOUSEHWHEEL),
  DEF_CONST_STRING(0x020E, WM_MOUSELAST),
  DEF_CONST_STRING(0x020D, WM_MOUSELAST),
  DEF_CONST_STRING(0x020A, WM_MOUSELAST),
  DEF_CONST_STRING(0x0209, WM_MOUSELAST),
  DEF_CONST_STRING(0x0210, WM_PARENTNOTIFY),
  DEF_CONST_STRING(0x0211, WM_ENTERMENULOOP),
  DEF_CONST_STRING(0x0212, WM_EXITMENULOOP),
  DEF_CONST_STRING(0x0213, WM_NEXTMENU),
  DEF_CONST_STRING(0x0214, WM_SIZING),
  DEF_CONST_STRING(0x0215, WM_CAPTURECHANGED),
  DEF_CONST_STRING(0x0216, WM_MOVING),
  DEF_CONST_STRING(0x0218, WM_POWERBROADCAST),
  DEF_CONST_STRING(0x0219, WM_DEVICECHANGE),
  DEF_CONST_STRING(0x0220, WM_MDICREATE),
  DEF_CONST_STRING(0x0221, WM_MDIDESTROY),
  DEF_CONST_STRING(0x0222, WM_MDIACTIVATE),
  DEF_CONST_STRING(0x0223, WM_MDIRESTORE),
  DEF_CONST_STRING(0x0224, WM_MDINEXT),
  DEF_CONST_STRING(0x0225, WM_MDIMAXIMIZE),
  DEF_CONST_STRING(0x0226, WM_MDITILE),
  DEF_CONST_STRING(0x0227, WM_MDICASCADE),
  DEF_CONST_STRING(0x0228, WM_MDIICONARRANGE),
  DEF_CONST_STRING(0x0229, WM_MDIGETACTIVE),
  DEF_CONST_STRING(0x0230, WM_MDISETMENU),
  DEF_CONST_STRING(0x0231, WM_ENTERSIZEMOVE),
  DEF_CONST_STRING(0x0232, WM_EXITSIZEMOVE),
  DEF_CONST_STRING(0x0233, WM_DROPFILES),
  DEF_CONST_STRING(0x0234, WM_MDIREFRESHMENU),
  DEF_CONST_STRING(0x0238, WM_POINTERDEVICECHANGE),
  DEF_CONST_STRING(0x0239, WM_POINTERDEVICEINRANGE),
  DEF_CONST_STRING(0x023A, WM_POINTERDEVICEOUTOFRANGE),
  DEF_CONST_STRING(0x0240, WM_TOUCH),
  DEF_CONST_STRING(0x0241, WM_NCPOINTERUPDATE),
  DEF_CONST_STRING(0x0242, WM_NCPOINTERDOWN),
  DEF_CONST_STRING(0x0243, WM_NCPOINTERUP),
  DEF_CONST_STRING(0x0245, WM_POINTERUPDATE),
  DEF_CONST_STRING(0x0246, WM_POINTERDOWN),
  DEF_CONST_STRING(0x0247, WM_POINTERUP),
  DEF_CONST_STRING(0x0249, WM_POINTERENTER),
  DEF_CONST_STRING(0x024A, WM_POINTERLEAVE),
  DEF_CONST_STRING(0x024B, WM_POINTERACTIVATE),
  DEF_CONST_STRING(0x024C, WM_POINTERCAPTURECHANGED),
  DEF_CONST_STRING(0x024D, WM_TOUCHHITTESTING),
  DEF_CONST_STRING(0x024E, WM_POINTERWHEEL),
  DEF_CONST_STRING(0x024F, WM_POINTERHWHEEL),
  DEF_CONST_STRING(0x0251, WM_POINTERROUTEDTO),
  DEF_CONST_STRING(0x0252, WM_POINTERROUTEDAWAY),
  DEF_CONST_STRING(0x0253, WM_POINTERROUTEDRELEASED),
  DEF_CONST_STRING(0x0281, WM_IME_SETCONTEXT),
  DEF_CONST_STRING(0x0282, WM_IME_NOTIFY),
  DEF_CONST_STRING(0x0283, WM_IME_CONTROL),
  DEF_CONST_STRING(0x0284, WM_IME_COMPOSITIONFULL),
  DEF_CONST_STRING(0x0285, WM_IME_SELECT),
  DEF_CONST_STRING(0x0286, WM_IME_CHAR),
  DEF_CONST_STRING(0x0288, WM_IME_REQUEST),
  DEF_CONST_STRING(0x0290, WM_IME_KEYDOWN),
  DEF_CONST_STRING(0x0291, WM_IME_KEYUP),
  DEF_CONST_STRING(0x02A1, WM_MOUSEHOVER),
  DEF_CONST_STRING(0x02A3, WM_MOUSELEAVE),
  DEF_CONST_STRING(0x02A0, WM_NCMOUSEHOVER),
  DEF_CONST_STRING(0x02A2, WM_NCMOUSELEAVE),
  DEF_CONST_STRING(0x02B1, WM_WTSSESSION_CHANGE),
  DEF_CONST_STRING(0x02c0, WM_TABLET_FIRST),
  DEF_CONST_STRING(0x02df, WM_TABLET_LAST),
  DEF_CONST_STRING(0x02E0, WM_DPICHANGED),
  DEF_CONST_STRING(0x02E2, WM_DPICHANGED_BEFOREPARENT),
  DEF_CONST_STRING(0x02E3, WM_DPICHANGED_AFTERPARENT),
  DEF_CONST_STRING(0x02E4, WM_GETDPISCALEDSIZE),
  DEF_CONST_STRING(0x0300, WM_CUT),
  DEF_CONST_STRING(0x0301, WM_COPY),
  DEF_CONST_STRING(0x0302, WM_PASTE),
  DEF_CONST_STRING(0x0303, WM_CLEAR),
  DEF_CONST_STRING(0x0304, WM_UNDO),
  DEF_CONST_STRING(0x0305, WM_RENDERFORMAT),
  DEF_CONST_STRING(0x0306, WM_RENDERALLFORMATS),
  DEF_CONST_STRING(0x0307, WM_DESTROYCLIPBOARD),
  DEF_CONST_STRING(0x0308, WM_DRAWCLIPBOARD),
  DEF_CONST_STRING(0x0309, WM_PAINTCLIPBOARD),
  DEF_CONST_STRING(0x030A, WM_VSCROLLCLIPBOARD),
  DEF_CONST_STRING(0x030B, WM_SIZECLIPBOARD),
  DEF_CONST_STRING(0x030C, WM_ASKCBFORMATNAME),
  DEF_CONST_STRING(0x030D, WM_CHANGECBCHAIN),
  DEF_CONST_STRING(0x030E, WM_HSCROLLCLIPBOARD),
  DEF_CONST_STRING(0x030F, WM_QUERYNEWPALETTE),
  DEF_CONST_STRING(0x0310, WM_PALETTEISCHANGING),
  DEF_CONST_STRING(0x0311, WM_PALETTECHANGED),
  DEF_CONST_STRING(0x0312, WM_HOTKEY),
  DEF_CONST_STRING(0x0317, WM_PRINT),
  DEF_CONST_STRING(0x0318, WM_PRINTCLIENT),
  DEF_CONST_STRING(0x0319, WM_APPCOMMAND),
  DEF_CONST_STRING(0x031A, WM_THEMECHANGED),
  DEF_CONST_STRING(0x031D, WM_CLIPBOARDUPDATE),
  DEF_CONST_STRING(0x031E, WM_DWMCOMPOSITIONCHANGED),
  DEF_CONST_STRING(0x031F, WM_DWMNCRENDERINGCHANGED),
  DEF_CONST_STRING(0x0320, WM_DWMCOLORIZATIONCOLORCHANGED),
  DEF_CONST_STRING(0x0321, WM_DWMWINDOWMAXIMIZEDCHANGE),
  DEF_CONST_STRING(0x0323, WM_DWMSENDICONICTHUMBNAIL),
  DEF_CONST_STRING(0x0326, WM_DWMSENDICONICLIVEPREVIEWBITMAP),
  DEF_CONST_STRING(0x033F, WM_GETTITLEBARINFOEX),
  DEF_CONST_STRING(0x0358, WM_HANDHELDFIRST),
  DEF_CONST_STRING(0x035F, WM_HANDHELDLAST),
  DEF_CONST_STRING(0x0360, WM_QUERYAFXWNDPROC),
  DEF_CONST_STRING(0x0361, WM_SIZEPARENT),
  DEF_CONST_STRING(0x0362, WM_SETMESSAGESTRING),
  DEF_CONST_STRING(0x0363, WM_IDLEUPDATECMDUI),
  DEF_CONST_STRING(0x0364, WM_INITIALUPDATE),
  DEF_CONST_STRING(0x0365, WM_COMMANDHELP),
  DEF_CONST_STRING(0x0366, WM_HELPHITTEST),
  DEF_CONST_STRING(0x0367, WM_EXITHELPMODE),
  DEF_CONST_STRING(0x0368, WM_RECALCPARENT),
  DEF_CONST_STRING(0x0369, WM_SIZECHILD),
  DEF_CONST_STRING(0x036A, WM_KICKIDLE),
  DEF_CONST_STRING(0x036B, WM_QUERYCENTERWND),
  DEF_CONST_STRING(0x036C, WM_DISABLEMODAL),
  DEF_CONST_STRING(0x036D, WM_FLOATSTATUS),
  DEF_CONST_STRING(0x036E, WM_ACTIVATETOPLEVEL),
  DEF_CONST_STRING(0x036F, WM_RESERVED_036F),
  DEF_CONST_STRING(0x0371, WM_RESERVED_0371),
  DEF_CONST_STRING(0x0372, WM_RESERVED_0372),
  DEF_CONST_STRING(0x0374, WM_SOCKET_DEAD),
  DEF_CONST_STRING(0x0377, WM_OCC_LOADFROMSTORAGE),
  DEF_CONST_STRING(0x0378, WM_OCC_INITNEW),
  DEF_CONST_STRING(0x037A, WM_OCC_LOADFROMSTREAM_EX),
  DEF_CONST_STRING(0x037B, WM_OCC_LOADFROMSTORAGE_EX),
  DEF_CONST_STRING(0x037E, WM_RESERVED_037E),
  DEF_CONST_STRING(0x037F, WM_AFXLAST),
  DEF_CONST_STRING(0x0380, WM_PENWINFIRST),
  DEF_CONST_STRING(0x038F, WM_PENWINLAST),
  DEF_CONST_STRING(0x0400, WM_USER),
};

std::string vuapi decode_const_window_message_A(const ulong id)
{
  return DECODE_CONSTANT_A(list_win_messages, id);
}

std::wstring vuapi decode_const_window_message_W(const ulong id)
{
  return to_string_W(decode_const_window_message_A(id));
}

ulong vuapi decode_const_window_message_A(const std::string& str)
{
  return ENCODE_CONSTANT_A(list_win_messages, str);
}

ulong vuapi decode_const_window_message_W(const std::wstring& str)
{
  return decode_const_window_message_A(to_string_A(str));
}

// Process Page Protection @refer to process.cpp

DEF_LIST(list_process_page_protections)
{
  DEF_CONST(PAGE_NOACCESS),
  DEF_CONST(PAGE_READONLY),
  DEF_CONST(PAGE_READWRITE),
  DEF_CONST(PAGE_WRITECOPY),
  DEF_CONST(PAGE_EXECUTE),
  DEF_CONST(PAGE_EXECUTE_READ),
  DEF_CONST(PAGE_EXECUTE_READWRITE),
  DEF_CONST(PAGE_EXECUTE_WRITECOPY),
  DEF_CONST(PAGE_GUARD),
  DEF_CONST(PAGE_NOCACHE),
  DEF_CONST(PAGE_WRITECOMBINE),
  //DEF_CONST(PAGE_GRAPHICS_NOACCESS),
  //DEF_CONST(PAGE_GRAPHICS_READONLY),
  //DEF_CONST(PAGE_GRAPHICS_READWRITE),
  //DEF_CONST(PAGE_GRAPHICS_EXECUTE),
  //DEF_CONST(PAGE_GRAPHICS_EXECUTE_READ),
  //DEF_CONST(PAGE_GRAPHICS_EXECUTE_READWRITE),
  //DEF_CONST(PAGE_GRAPHICS_COHERENT),
  //DEF_CONST(PAGE_ENCLAVE_THREAD_CONTROL),
  //DEF_CONST(PAGE_REVERT_TO_FILE_MAP),
  //DEF_CONST(PAGE_TARGETS_NO_UPDATE),
  //DEF_CONST(PAGE_TARGETS_INVALID),
  //DEF_CONST(PAGE_ENCLAVE_UNVALIDATED),
  //DEF_CONST(PAGE_ENCLAVE_DECOMMIT),
};

std::string vuapi decode_const_process_page_protection_A(const ulong id)
{
  return DECODE_CONSTANT_A(list_process_page_protections, id);
}

std::wstring vuapi decode_const_process_page_protection_W(const ulong id)
{
  return to_string_W(decode_const_process_page_protection_A(id));
}

ulong vuapi decode_const_process_page_protection_A(const std::string& str)
{
  return ENCODE_CONSTANT_A(list_process_page_protections, str);
}

ulong vuapi decode_const_process_page_protection_W(const std::wstring& str)
{
  return decode_const_process_page_protection_A(to_string_A(str));
}

// Process Memory State @refer to process.cpp

DEF_LIST(list_process_memory_states)
{
  DEF_CONST(MEM_COMMIT),
  DEF_CONST(MEM_RESERVE),
  //DEF_CONST(MEM_REPLACE_PLACEHOLDER),
  //DEF_CONST(MEM_RESERVE_PLACEHOLDER),
  DEF_CONST(MEM_RESET),
  DEF_CONST(MEM_TOP_DOWN),
  DEF_CONST(MEM_WRITE_WATCH),
  DEF_CONST(MEM_PHYSICAL),
  DEF_CONST(MEM_ROTATE),
  //DEF_CONST(MEM_DIFFERENT_IMAGE_BASE_OK),
  //DEF_CONST(MEM_RESET_UNDO),
  DEF_CONST(MEM_LARGE_PAGES),
  DEF_CONST(MEM_4MB_PAGES),
  //DEF_CONST(MEM_64K_PAGES),
  DEF_CONST(MEM_UNMAP_WITH_TRANSIENT_BOOST),
  //DEF_CONST(MEM_COALESCE_PLACEHOLDERS),
  //DEF_CONST(MEM_PRESERVE_PLACEHOLDER),
  DEF_CONST(MEM_DECOMMIT),
  DEF_CONST(MEM_RELEASE),
  DEF_CONST(MEM_FREE),
};

std::string vuapi decode_const_process_memory_state_A(const ulong id)
{
  return DECODE_CONSTANT_A(list_process_memory_states, id);
}

std::wstring vuapi decode_const_process_memory_state_W(const ulong id)
{
  return to_string_W(decode_const_process_memory_state_A(id));
}

ulong vuapi decode_const_process_memory_state_A(const std::string& str)
{
  return ENCODE_CONSTANT_A(list_process_memory_states, str);
}

ulong vuapi decode_const_process_memory_state_W(const std::wstring& str)
{
  return decode_const_process_memory_state_A(to_string_A(str));
}

// HTTP Status @refer to restclient.cpp

DEF_LIST(list_http_status)
{
  // 1xx - Informational
  DEF_CONST_STRING(100, Continue),
  DEF_CONST_STRING(101, Switching Protocols),
  DEF_CONST_STRING(102, Processing),
  DEF_CONST_STRING(103, Early Hints),
  // 2xx - Successful
  DEF_CONST_STRING(200, OK),
  DEF_CONST_STRING(201, Created),
  DEF_CONST_STRING(202, Accepted),
  DEF_CONST_STRING(203, Non-Authoritative Information),
  DEF_CONST_STRING(204, No Content),
  DEF_CONST_STRING(205, Reset Content),
  DEF_CONST_STRING(206, Partial Content),
  DEF_CONST_STRING(207, Multi - Status),
  DEF_CONST_STRING(208, Already Reported),
  DEF_CONST_STRING(226, IM Used),
  // 3xx - Redirection
  DEF_CONST_STRING(300, Multiple Choices),
  DEF_CONST_STRING(301, Moved Permanently),
  DEF_CONST_STRING(302, Found),
  DEF_CONST_STRING(303, See Other),
  DEF_CONST_STRING(304, Not Modified),
  DEF_CONST_STRING(305, Use Proxy),
  DEF_CONST_STRING(307, Temporary Redirect),
  DEF_CONST_STRING(308, Permanent Redirect),
  // 4xx - Client Error
  DEF_CONST_STRING(400, Bad Request),
  DEF_CONST_STRING(401, Unauthorized),
  DEF_CONST_STRING(402, Payment Required),
  DEF_CONST_STRING(403, Forbidden),
  DEF_CONST_STRING(404, Not Found),
  DEF_CONST_STRING(405, Method Not Allowed),
  DEF_CONST_STRING(406, Not Acceptable),
  DEF_CONST_STRING(407, Proxy Authentication Required),
  DEF_CONST_STRING(408, Request Timeout),
  DEF_CONST_STRING(409, Conflict),
  DEF_CONST_STRING(410, Gone),
  DEF_CONST_STRING(411, Length Required),
  DEF_CONST_STRING(412, Precondition Failed),
  DEF_CONST_STRING(413, Content Too Large),
  DEF_CONST_STRING(414, URI Too Long),
  DEF_CONST_STRING(415, Unsupported Media Type),
  DEF_CONST_STRING(416, Range Not Satisfiable),
  DEF_CONST_STRING(417, Expectation Failed),
  DEF_CONST_STRING(418, I''m a teapot),
  DEF_CONST_STRING(421, Misdirected Request),
  DEF_CONST_STRING(422, Unprocessable Content),
  DEF_CONST_STRING(423, Locked),
  DEF_CONST_STRING(424, Failed Dependency),
  DEF_CONST_STRING(425, Too Early),
  DEF_CONST_STRING(426, Upgrade Required),
  DEF_CONST_STRING(428, Precondition Required),
  DEF_CONST_STRING(429, Too Many Requests),
  DEF_CONST_STRING(431, Request Header Fields Too Large),
  DEF_CONST_STRING(451, Unavailable For Legal Reasons),
  // 5xx - Server Error
  DEF_CONST_STRING(500, Internal Server Error),
  DEF_CONST_STRING(501, Not Implemented),
  DEF_CONST_STRING(502, Bad Gateway),
  DEF_CONST_STRING(503, Service Unavailable),
  DEF_CONST_STRING(504, Gateway Timeout),
  DEF_CONST_STRING(505, HTTP Version Not Supported),
  DEF_CONST_STRING(506, Variant Also Negotiates),
  DEF_CONST_STRING(507, Insufficient Storage),
  DEF_CONST_STRING(508, Loop Detected),
  DEF_CONST_STRING(510, Not Extended),
  DEF_CONST_STRING(511, Network Authentication Required),
};

std::string vuapi decode_const_http_status_A(const ulong id)
{
  return DECODE_CONSTANT_A(list_http_status, id);
}

std::wstring vuapi decode_const_http_status_W(const ulong id)
{
  return to_string_W(decode_const_http_status_A(id));
}

} // namespace vu