#ifndef __ENGINE_KEYCODE_H__
#define __ENGINE_KEYCODE_H__

#include <SDL2/SDL_keycode.h>

namespace Engine {
    /// @brief The Scancode that used for key handling.
    enum class Scancode {
		Unknown = 0,
		A = 4,
		B = 5,
		C = 6,
		D = 7,
		E = 8,
		F = 9,
		G = 10,
		H = 11,
		I = 12,
		J = 13,
		K = 14,
		L = 15,
		M = 16,
		N = 17,
		O = 18,
		P = 19,
		Q = 20,
		R = 21,
		S = 22,
		T = 23,
		U = 24,
		V = 25,
		W = 26,
		X = 27,
		Y = 28,
		Z = 29,
		Num1 = 30,
		Num2 = 31,
		Num3 = 32,
		Num4 = 33,
		Num5 = 34,
		Num6 = 35,
		Num7 = 36,
		Num8 = 37,
		Num9 = 38,
		Num0 = 39,
		Return = 40,
		Escape = 41,
		Backspace = 42,
		Tab = 43,
		Space = 44,
		Minus = 45,
		Equals = 46,
		LeftBracket = 47,
		RightBracket = 48,
		Backslash = 49,
		NonUSHash = 50,
		Semicolon = 51,
		Apostrophe = 52,
		Grave = 53,
		Comma = 54,
		Period = 55,
		Slash = 56,
		Capslock = 57,
		F1 = 58,
		F2 = 59,
		F3 = 60,
		F4 = 61,
		F5 = 62,
		F6 = 63,
		F7 = 64,
		F8 = 65,
		F9 = 66,
		F10 = 67,
		F11 = 68,
		F12 = 69,
		PrintScreen = 70,
		ScrollLock = 71,
		Pause = 72,
		Insert = 73,
		Home = 74,
		PageUp = 75,
		Delete = 76,
		End = 77,
		PageDown = 78,
		Right = 79,
		Left = 80,
		Down = 81,
		Up = 82,
		NumlockClear = 83,
		Keypad_Divide = 84,
		Keypad_Multiply = 85,
		Keypad_Minus = 86,
		Keypad_Plus = 87,
		Keypad_Enter = 88,
		Keypad_1 = 89,
		Keypad_2 = 90,
		Keypad_3 = 91,
		Keypad_4 = 92,
		Keypad_5 = 93,
		Keypad_6 = 94,
		Keypad_7 = 95,
		Keypad_8 = 96,
		Keypad_9 = 97,
		Keypad_0 = 98,
		Keypad_Period = 99,
		NonUSBackSlash = 100,
		Application = 101,
		Power = 102,
		Keypad_Equals = 103,
		F13 = 104,
		F14 = 105,
		F15 = 106,
		F16 = 107,
		F17 = 108,
		F18 = 109,
		F19 = 110,
		F20 = 111,
		F21 = 112,
		F22 = 113,
		F23 = 114,
		F24 = 115,
		Execute = 116,
		Help = 117,
		Menu = 118,
		Select = 119,
		Stop = 120,
		Again = 121,
		Undo = 122,
		Cut = 123,
		Copy = 124,
		Paste = 125,
		Find = 126,
		Mute = 127,
		VolumeUp = 128,
		VolumeDown = 129,
		Keypad_Comma = 133,
		Keypad_EqualsAs400 = 134,
		International1 = 135,
		International2 = 136,
		International3 = 137,
		International4 = 138,
		International5 = 139,
		International6 = 140,
		International7 = 141,
		International8 = 142,
		International9 = 143,
		Lang1 = 144,
		Lang2 = 145,
		Lang3 = 146,
		Lang4 = 147,
		Lang5 = 148,
		Lang6 = 149,
		Lang7 = 150,
		Lang8 = 151,
		Lang9 = 152,
		AltErase = 153,
		SysReq = 154,
		Cancel = 155,
		Clear = 156,
		Prior = 157,
		Return2 = 158,
		Separator = 159,
		Out = 160,
		Oper = 161,
		ClearAgain = 162,
		Crsel = 163,
		Exsel = 164,
		Keypad_00 = 176,
		Keypad_000 = 177,
		ThousandsSeparator = 178,
		DecimalSeparator = 179,
		CurrencyUnit = 180,
		CurrencySubUnit = 181,
		Keypad_LeftParen = 182,
		Keypad_RightParen = 183,
		Keypad_LeftBrace = 184,
		Keypad_RightBrace = 185,
		Keypad_Tab = 186,
		Keypad_Backspace = 187,
		Keypad_A = 188,
		Keypad_B = 189,
		Keypad_C = 190,
		Keypad_D = 191,
		Keypad_E = 192,
		Keypad_F = 193,
		Keypad_Xor = 194,
		Keypad_Power = 195,
		Keypad_Percent = 196,
		Keypad_Less = 197,
		Keypad_Greater = 198,
		Keypad_Ampersand = 199,
		Keypad_DoubleAmpersand = 200,
		Keypad_VerticalBar = 201,
		Keypad_DoubleVerticalbar = 202,
		Keypad_Colon = 203,
		Keypad_Hash = 204,
		Keypad_Space = 205,
		Keypad_At = 206,
		Keypad_Exclam = 207,
		Keypad_MemStore = 208,
		Keypad_MemRecall = 209,
		Keypad_MemClear = 210,
		Keypad_MemAdd = 211,
		Keypad_MemSubtract = 212,
		Keypad_MemMultiply = 213,
		Keypad_MemDivide = 214,
		Keypad_PlusMinus = 215,
		Keypad_Clear = 216,
		Keypad_ClearEntry = 217,
		Keypad_Binary = 218,
		Keypad_Octal = 219,
		Keypad_Decimal = 220,
		Keypad_Hexadecimal = 221,
		LeftCtrl = 224,
		LelfShift = 225,
		LelfAlt = 226,
		LeftGUI = 227,
		RightCtrl = 228,
		RightShift = 229,
		RightAlt = 230,
		RightGUI = 231,
		Mode = 257,
		AudioNext = 258,
		AudioPrev = 259,
		AudioStop = 260,
		AudioPlay = 261,
		AudioMute = 262,
		MediaSelect = 263,
		WWW = 264,
		Mail = 265,
		Calculator = 266,
		Computer = 267,
		Ac_Search = 268,
		Ac_Home = 269,
		Ac_Back = 270,
		Ac_Forward = 271,
		Ac_Stop = 272,
		Ac_Refresh = 273,
		Ac_Bookmarks = 274,
		BrightnessDown = 275,
		BrightnessUp = 276,
		DisplaySwitch = 277,
		KBDIllumToggle = 278,
		KBDIllumDown = 279,
		KBDIllumUp = 280,
		Eject = 281,
		Sleep = 282,
		App1 = 283,
		App2 = 284,
		AudioRewind = 285,
		AudioFastForward = 286,
		SoftLeft = 287,
		SoftRight = 288,
		Call = 289,
		EndCall = 290
    };

    /// @brief The Keycode that used for key handling.
    enum class KeyCode {
		Unknown = 0,
		Return = '\r',
		Escape = '\x1B',
		Backspace = '\b',
		Tab = '\t',
		Space = ' ',
		Exclaim = '!',
		QuoteDouble = '"',
		Hash = '#',
		Percent = '%',
		Dollar = '$',
		Ampersand = '&',
		Quote = '\'',
		LeftParen = '(',
		RightParen = ')',
		Asterisk = '*',
		Plus = '+',
		Comma = ',',
		Minus = '-',
		Period = '.',
		Slash = '/',
		Num0 = '0',
		Num1 = '1',
		Num2 = '2',
		Num3 = '3',
		Num4 = '4',
		Num5 = '5',
		Num6 = '6',
		Num7 = '7',
		Num8 = '8',
		Num9 = '9',
		Colon = ':',
		Semicolon = ';',
		Less = '<',
		Equals = '=',
		Greater = '>',
		Question = '?',
		At = '@',
		LeftBracket = '[',
		Backslash = '\\',
		RightBracket = ']',
		Caret = '^',
		Underscore = '_',
		Backquote = '`',
		A = 'a',
		B = 'b',
		C = 'c',
		D = 'd',
		E = 'e',
		F = 'f',
		G = 'g',
		H = 'h',
		I = 'i',
		J = 'j',
		K = 'k',
		L = 'l',
		M = 'm',
		N = 'n',
		O = 'o',
		P = 'p',
		Q = 'q',
		R = 'r',
		S = 's',
		T = 't',
		U = 'u',
		V = 'v',
		W = 'w',
		X = 'x',
		Y = 'y',
		Z = 'z',
		Capslock = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),
		F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
		F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
		F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
		F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
		F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
		F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
		F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
		F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
		F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
		F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
		F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
		F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),
		PrintScreen = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
		ScrollLock = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
		Pause = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
		Insert = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
		Home = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
		PageUp = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
		Delete = '\x7F',
		End = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
		PageDown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
		Right = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
		Left = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
		Down = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
		Up = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),
		NumlockClear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
		Keypad_Divide = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
		Keypad_Multiply = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
		Keypad_Minus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
		Keypad_Plus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
		Keypad_Enter = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
		Keypad_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
		Keypad_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
		Keypad_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
		Keypad_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
		Keypad_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
		Keypad_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
		Keypad_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
		Keypad_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
		Keypad_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
		Keypad_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
		Keypad_Period = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),
		Application = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APPLICATION),
		Power = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_POWER),
		Keypad_Equals = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
		F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
		F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
		F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
		F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
		F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
		F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
		F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
		F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
		F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
		F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
		F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
		F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
		Execute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXECUTE),
		Help = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HELP),
		Menu = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
		Select = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SELECT),
		Stop = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_STOP),
		Again = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AGAIN),
		Undo = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UNDO),
		Cut = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CUT),
		Copy = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COPY),
		Paste = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PASTE),
		Find = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_FIND),
		Mute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MUTE),
		VolumeUp = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEUP),
		VolumeDown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_VOLUMEDOWN),
		Keypad_Comma = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COMMA),
		Keypad_EqualsAs400 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALSAS400),
		AltErase = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ALTERASE),
		SysReq = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SYSREQ),
		Cancel = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CANCEL),
		Clear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEAR),
		Prior = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRIOR),
		Return2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RETURN2),
		Separator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SEPARATOR),
		Out = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OUT),
		Oper = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_OPER),
		ClearAgain = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CLEARAGAIN),
		Crsel = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CRSEL),
		Exsel = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EXSEL),
		Keypad_00 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_00),
		Keypad_000 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_000),
		ThousandsSeparator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_THOUSANDSSEPARATOR),
		DecimalSeparator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DECIMALSEPARATOR),
		CurrencyUnit = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYUNIT),
		CurrencySubUnit = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CURRENCYSUBUNIT),
		Keypad_Leftparen = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTPAREN),
		Keypad_Rightparen = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTPAREN),
		Keypad_Leftbrace = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LEFTBRACE),
		Keypad_Rightbrace = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_RIGHTBRACE),
		Keypad_Tab = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_TAB),
		Keypad_Backspace = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BACKSPACE),
		Keypad_A = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_A),
		Keypad_B = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_B),
		Keypad_C = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_C),
		Keypad_D = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_D),
		Keypad_E = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_E),
		Keypad_F = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_F),
		Keypad_Xor = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_XOR),
		Keypad_Power = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_POWER),
		Keypad_Percent = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERCENT),
		Keypad_Less = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_LESS),
		Keypad_Greater = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_GREATER),
		Keypad_Ampersand = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AMPERSAND),
		Keypad_DoubleAmpersand = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLAMPERSAND),
		Keypad_VerticalBar = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_VERTICALBAR),
		Keypad_DoubleCerticalBar = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DBLVERTICALBAR),
		Keypad_Colon = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_COLON),
		Keypad_Hash = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HASH),
		Keypad_Space = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_SPACE),
		Keypad_At = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_AT),
		Keypad_Exclam = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EXCLAM),
		Keypad_MemStore = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSTORE),
		Keypad_MemRecall = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMRECALL),
		Keypad_MemClear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMCLEAR),
		Keypad_MemAdd = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMADD),
		Keypad_MemSubtract = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMSUBTRACT),
		Keypad_MemMultiply = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMMULTIPLY),
		Keypad_MemDivide = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MEMDIVIDE),
		Keypad_PlusMinus = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUSMINUS),
		Keypad_Clear = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEAR),
		Keypad_ClearEntry = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_CLEARENTRY),
		Keypad_Binary = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_BINARY),
		Keypad_Octal = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_OCTAL),
		Keypad_Decimal = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DECIMAL),
		Keypad_Hexadecimal = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_HEXADECIMAL),
		LeftCtrl = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
		LeftShift = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
		LeftAlt = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
		LeftGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
		RightCtrl = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
		RightShift = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
		RightAlt = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
		RightGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),
		Mode = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MODE),
		AudioNext = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIONEXT),
		AudioPrev = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPREV),
		AudioStop = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOSTOP),
		AudioPlay = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOPLAY),
		AudioMute = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOMUTE),
		MediaSelect = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MEDIASELECT),
		WWW = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_WWW),
		Mail = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MAIL),
		Calculator = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALCULATOR),
		Computer = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_COMPUTER),
		Ac_Search = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_SEARCH),
		Ac_Home = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_HOME),
		Ac_Back = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BACK),
		Ac_Forward = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_FORWARD),
		Ac_Stop = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_STOP),
		Ac_Refresh = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_REFRESH),
		Ac_Bookmarks = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AC_BOOKMARKS),
		BrightnessDown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSDOWN),
		BrightnessUp = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_BRIGHTNESSUP),
		DisplaySwitch = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DISPLAYSWITCH),
		KBDIllumToggle = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMTOGGLE),
		KBDIllumDown = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMDOWN),
		KBDIllumUp = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KBDILLUMUP),
		Eject = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_EJECT),
		Sleep = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SLEEP),
		App1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP1),
		App2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_APP2),
		AudioRewind = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOREWIND),
		AudioFastForward = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_AUDIOFASTFORWARD),
		SoftLeft = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTLEFT),
		SoftRight = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SOFTRIGHT),
		Call = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CALL),
		EndCall = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_ENDCALL)
    };

	/// @brief The Key Modifier that used for key handling.
	enum class KeyModifier {
		None = 0x0000,
		LeftShift = 0x0001,
		RightShift = 0x0002,
		LeftCtrl = 0x0040,
		RightCtrl = 0x0080,
		LeftAlt = 0x0100,
		RightAlt = 0x0200,
		LeftGUI = 0x0400,
		RightGUI = 0x0800,
		NumLock = 0x1000,
		Capslock = 0x2000,
		Mode = 0x4000,
		Scroll = 0x8000,

		Ctrl = LeftCtrl | RightCtrl,
		Shift = LeftShift | RightShift,
		Alt = LeftAlt | RightAlt,
		GUI = LeftGUI | RightGUI
	};
}

#endif // __ENGINE_KEYCODE_H__