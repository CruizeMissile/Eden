
#include "win32_keymap.hpp"

#include <array>

namespace eden::render::internal
{
using eden::input::key_t;

// The list of keycode https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes
static const std::array<key_t, 256> win32_keycode_to_key_map = {
    key_t::any,              // 0x00
    key_t::left_button,      // 0x01 | VK_LBUTTON
    key_t::right_button,     // 0x02 | VK_RBUTTON
    key_t::cancel,           // 0x03 | VK_CANCEL
    key_t::middle_button,    // 0x04 | VK_MBUTTON
    key_t::any,              // 0x05 | VK_XBUTTON1
    key_t::any,              // 0x06 | VK_XBUTTON2
    key_t::any,              // 0x07 | Undefined
    key_t::backspace,        // 0x08 | VK_BACK
    key_t::tab,              // 0x09 | VK_TAB
    key_t::any,              // 0x0a | Reserved
    key_t::any,              // 0x0b | Reserved
    key_t::any,              // 0x0c | VK_CLEAR
    key_t::enter,            // 0x0d | VK_RETURN
    key_t::any,              // 0x0e | Undefined
    key_t::any,              // 0x0f | Undefined
    key_t::shift,            // 0x10 | VK_SHIFT
    key_t::ctrl,             // 0x11 | VK_CONTROL
    key_t::alt,              // 0x12 | VK_MENU
    key_t::pause,            // 0x13 | VK_PAUSE
    key_t::caps_lock,        // 0x14 | VK_CAPITAL
    key_t::any,              // 0x15 | VK_KANA VK_HANGUEL VK_HANGUL
    key_t::any,              // 0x16 | Undefined
    key_t::any,              // 0x17 | VK_JUNJA
    key_t::any,              // 0x18 | VK_FINAL
    key_t::any,              // 0x19 | VK_HANJA VK_KANJI
    key_t::any,              // 0x1a | Undefined
    key_t::escape,           // 0x1b | VK_ESCAPE
    key_t::any,              // 0x1c | VK_CONVERT
    key_t::any,              // 0x1d | VK_NONCONVERT
    key_t::any,              // 0x1e | VK_ACCEPT
    key_t::any,              // 0x1f | VK_MODECHANGE
    key_t::space,            // 0x20 | VK_SPACE
    key_t::page_up,          // 0x21 | VK_PRIOR
    key_t::page_down,        // 0x22 | VK_NEXT
    key_t::end,              // 0x23 | VK_END
    key_t::home,             // 0x24 | VK_HOME
    key_t::left_arrow,       // 0x25 | VK_LEFT
    key_t::up_arrow,         // 0x26 | VK_UP
    key_t::right_arrow,      // 0x27 | VK_RIGHT
    key_t::down_arrow,       // 0x28 | VK_DOWN
    key_t::select,           // 0x29 | VK_SELECT
    key_t::print_screen,     // 0x2a | VK_PRINT
    key_t::any,              // 0x2b | VK_EXECUTE
    key_t::any,              // 0x2c | VK_SNAPSHOT
    key_t::insert,           // 0x2d | VK_INSERT
    key_t::delete_key,       // 0x2e | VK_DELETE
    key_t::help,             // 0x2f | VK_HELP
    key_t::d0,               // 0x30 | 0
    key_t::d1,               // 0x31 | 1
    key_t::d2,               // 0x32 | 2
    key_t::d3,               // 0x33 | 3
    key_t::d4,               // 0x34 | 4
    key_t::d5,               // 0x35 | 5
    key_t::d6,               // 0x36 | 6
    key_t::d7,               // 0x37 | 7
    key_t::d8,               // 0x38 | 8
    key_t::d9,               // 0x39 | 9
    key_t::any,              // 0x3a | Undefined
    key_t::any,              // 0x3b | Undefined
    key_t::any,              // 0x3c | Undefined
    key_t::any,              // 0x3d | Undefined
    key_t::any,              // 0x3e | Undefined
    key_t::any,              // 0x3f | Undefined
    key_t::any,              // 0x40 | Undefined
    key_t::a,                // 0x41 | a
    key_t::b,                // 0x42 | b
    key_t::c,                // 0x43 | c
    key_t::d,                // 0x44 | d
    key_t::e,                // 0x45 | e
    key_t::f,                // 0x46 | f
    key_t::g,                // 0x47 | g
    key_t::h,                // 0x48 | h
    key_t::i,                // 0x49 | i
    key_t::j,                // 0x4a | j
    key_t::k,                // 0x4b | k
    key_t::l,                // 0x4c | l
    key_t::m,                // 0x4d | m
    key_t::n,                // 0x4e | n
    key_t::o,                // 0x4f | o
    key_t::p,                // 0x50 | p
    key_t::q,                // 0x51 | q
    key_t::r,                // 0x52 | r
    key_t::s,                // 0x53 | s
    key_t::t,                // 0x54 | t
    key_t::u,                // 0x55 | u
    key_t::v,                // 0x56 | v
    key_t::w,                // 0x57 | w
    key_t::x,                // 0x58 | x
    key_t::y,                // 0x59 | y
    key_t::z,                // 0x5a | z
    key_t::left_window,      // 0x5b | VK_LWIN
    key_t::right_window,     // 0x5c | VK_RWIN
    key_t::application,      // 0x5d | VK_APPS
    key_t::any,              // 0x5e | Reserved
    key_t::sleep,            // 0x5f | VK_SLEEP
    key_t::key_pad0,         // 0x60 | VK_NUMPAD0
    key_t::key_pad1,         // 0x61 | VK_NUMPAD1
    key_t::key_pad2,         // 0x62 | VK_NUMPAD2
    key_t::key_pad3,         // 0x63 | VK_NUMPAD3
    key_t::key_pad4,         // 0x64 | VK_NUMPAD4
    key_t::key_pad5,         // 0x65 | VK_NUMPAD5
    key_t::key_pad6,         // 0x66 | VK_NUMPAD6
    key_t::key_pad7,         // 0x67 | VK_NUMPAD7
    key_t::key_pad8,         // 0x68 | VK_NUMPAD8
    key_t::key_pad9,         // 0x69 | VK_NUMPAD9
    key_t::key_pad_multiply, // 0x6a | VK_MULTIPLY
    key_t::key_pad_add,      // 0x6b | VK_ADD
    key_t::any,              // 0x6c | VK_SEPARATOR
    key_t::key_pad_subtract, // 0x6d | VK_SUBTRACT
    key_t::key_pad_decimal,  // 0x6e | VK_DECIMAL
    key_t::key_pad_divide,   // 0x6f | VK_DIVIDE
    key_t::f1,               // 0x70 | VK_F1
    key_t::f2,               // 0x71 | VK_F2
    key_t::f3,               // 0x72 | VK_F3
    key_t::f4,               // 0x73 | VK_F4
    key_t::f5,               // 0x74 | VK_F5
    key_t::f6,               // 0x75 | VK_F6
    key_t::f7,               // 0x76 | VK_F7
    key_t::f8,               // 0x77 | VK_F8
    key_t::f9,               // 0x78 | VK_F9
    key_t::f10,              // 0x79 | VK_F10
    key_t::f11,              // 0x7a | VK_F11
    key_t::f12,              // 0x7b | VK_F12
    key_t::any,              // 0x7c | VK_F13
    key_t::any,              // 0x7d | VK_F14
    key_t::any,              // 0x7e | VK_F15
    key_t::any,              // 0x7f | VK_F16
    key_t::any,              // 0x80 | VK_F17
    key_t::any,              // 0x81 | VK_F18
    key_t::any,              // 0x82 | VK_F19
    key_t::any,              // 0x83 | VK_F20
    key_t::any,              // 0x84 | VK_F21
    key_t::any,              // 0x85 | VK_F22
    key_t::any,              // 0x86 | VK_F23
    key_t::any,              // 0x87 | VK_F24
    key_t::any,              // 0x88 | Unassigned
    key_t::any,              // 0x89 | Unassigned
    key_t::any,              // 0x8a | Unassigned
    key_t::any,              // 0x8b | Unassigned
    key_t::any,              // 0x8c | Unassigned
    key_t::any,              // 0x8d | Unassigned
    key_t::any,              // 0x8e | Unassigned
    key_t::any,              // 0x8f | Unassigned
    key_t::num_lock,         // 0x90 | VK_NUMLOCK
    key_t::scroll_lock,      // 0x91 | VK_SCROLL
    key_t::any,              // 0x92 | OEM specific
    key_t::any,              // 0x93 | OEM specific
    key_t::any,              // 0x94 | OEM specific
    key_t::any,              // 0x95 | OEM specific
    key_t::any,              // 0x96 | OEM specific
    key_t::any,              // 0x97 | Unassigned
    key_t::any,              // 0x98 | Unassigned
    key_t::any,              // 0x99 | Unassigned
    key_t::any,              // 0x9a | Unassigned
    key_t::any,              // 0x9b | Unassigned
    key_t::any,              // 0x9c | Unassigned
    key_t::any,              // 0x9d | Unassigned
    key_t::any,              // 0x9e | Unassigned
    key_t::any,              // 0x9f | Unassigned
    key_t::left_shift,       // 0xa0 | VK_LSHIFT
    key_t::right_shift,      // 0xa1 | VK_RSHIFT
    key_t::left_ctrl,        // 0xa2 | VK_LCONTROL
    key_t::right_ctrl,       // 0xa3 | VK_RCONTROL
    key_t::left_alt,         // 0xa4 | VK_LMENU
    key_t::right_alt,        // 0xa5 | VK_RMENU
    key_t::any,              // 0xa6 | VK_BROWSER_BACK
    key_t::any,              // 0xa7 | VK_BROWSER_FORWARD
    key_t::any,              // 0xa8 | VK_BROWSER_REFRESH
    key_t::any,              // 0xa9 | VK_BROWSER_STOP
    key_t::any,              // 0xaa | VK_BROWSER_SEARCH
    key_t::any,              // 0xab | VK_BROWSER_FAVORITES
    key_t::any,              // 0xac | VK_BROWSER_HOME
    key_t::any,              // 0xad | VK_VOLUME_MUTE
    key_t::any,              // 0xae | VK_VOLUME_DOWN
    key_t::any,              // 0xaf | VK_VOLUME_UP
    key_t::any,              // 0xb0 | VK_MEDIA_NEXT_TRACK
    key_t::any,              // 0xb1 | VK_MEDIA_PREV_TRACK
    key_t::any,              // 0xb2 | VK_MEDIA_STOP
    key_t::any,              // 0xb3 | VK_MEDIA_PLAY_PAUSE
    key_t::any,              // 0xb4 | VK_LAUNCH_MAIL
    key_t::any,              // 0xb5 | VK_LAUNCH_MEDIA_SELECT
    key_t::any,              // 0xb6 | VK_LAUNCH_APP1
    key_t::any,              // 0xb7 | VK_LAUNCH_APP2
    key_t::any,              // 0xb8 | Reserved
    key_t::any,              // 0xb9 | Reserved
    key_t::any,              // 0xba | VK_OEM_1
    key_t::plus,             // 0xbb | VK_OEM_PLUS
    key_t::comma,            // 0xbc | VK_OEM_COMMA
    key_t::minus,            // 0xbd | VK_OEM_MINUS
    key_t::period,           // 0xbe | VK_OEM_PERIOD
    key_t::forward_slash,    // 0xbf | VK_OEM_2
    key_t::tilda,            // 0xc0 | VK_OEM_3
    key_t::any,              // 0xc1 | Reserved
    key_t::any,              // 0xc2 | Reserved
    key_t::any,              // 0xc3 | Reserved
    key_t::any,              // 0xc4 | Reserved
    key_t::any,              // 0xc5 | Reserved
    key_t::any,              // 0xc6 | Reserved
    key_t::any,              // 0xc7 | Reserved
    key_t::any,              // 0xc8 | Reserved
    key_t::any,              // 0xc9 | Reserved
    key_t::any,              // 0xca | Reserved
    key_t::any,              // 0xcb | Reserved
    key_t::any,              // 0xcc | Reserved
    key_t::any,              // 0xcd | Reserved
    key_t::any,              // 0xce | Reserved
    key_t::any,              // 0xcf | Reserved
    key_t::any,              // 0xd0 | Reserved
    key_t::any,              // 0xd1 | Reserved
    key_t::any,              // 0xd2 | Reserved
    key_t::any,              // 0xd3 | Reserved
    key_t::any,              // 0xd4 | Reserved
    key_t::any,              // 0xd5 | Reserved
    key_t::any,              // 0xd6 | Reserved
    key_t::any,              // 0xd7 | Reserved
    key_t::any,              // 0xd8 | Unassigned
    key_t::any,              // 0xd9 | Unassigned
    key_t::any,              // 0xda | Unassigned
    key_t::left_bracket,     // 0xdb | VK_OEM_4
    key_t::back_slash,       // 0xdc | VK_OEM_5
    key_t::right_bracket,    // 0xdd | VK_OEM_6
    key_t::quote,            // 0xde | VK_OEM_7
    key_t::any,              // 0xdf | VK_OEM_8
    key_t::any,              // 0xe0 | Reserved
    key_t::any,              // 0xe1 | OEM specific
    key_t::any,              // 0xe2 | VK_OEM_102
    key_t::any,              // 0xe3 | OEM specific
    key_t::any,              // 0xe4 | OEM specific
    key_t::any,              // 0xe5 | VK_PROCESSKEY
    key_t::any,              // 0xe6 | OEM specific
    key_t::any,              // 0xe7 | VK_PACKET
    key_t::any,              // 0xe8 | Unassigned
    key_t::any,              // 0xe9 | OEM specific
    key_t::any,              // 0xea | OEM specific
    key_t::any,              // 0xeb | OEM specific
    key_t::any,              // 0xec | OEM specific
    key_t::any,              // 0xed | OEM specific
    key_t::any,              // 0xee | OEM specific
    key_t::any,              // 0xef | OEM specific
    key_t::any,              // 0xf0 | OEM specific
    key_t::any,              // 0xf1 | OEM specific
    key_t::any,              // 0xf2 | OEM specific
    key_t::any,              // 0xf3 | OEM specific
    key_t::any,              // 0xf4 | OEM specific
    key_t::any,              // 0xf5 | OEM specific
    key_t::any,              // 0xf6 | VK_ATTN
    key_t::any,              // 0xf7 | VK_CRSEL
    key_t::any,              // 0xf8 | VK_EXSEL
    key_t::any,              // 0xf9 | VK_EREOF
    key_t::any,              // 0xfa | VK_PLAY
    key_t::any,              // 0xfb | VK_ZOOM
    key_t::any,              // 0xfc | VK_NONAME
    key_t::any,              // 0xfd | VK_PA1
    key_t::clear,            // 0xfe | VK_OEM_CLEAR
    key_t::any,              // 0xff | Unassigned
};

key_t map_key(uint8_t key_code)
{
    return win32_keycode_to_key_map[key_code];
}
} // namespace eden::render::internal
