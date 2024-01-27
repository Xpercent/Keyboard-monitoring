#pragma once
#include <iostream>
#include <map>
std::string GetKeyName(int testKeyCode){
    SHORT keyState = GetKeyState(VK_CAPITAL);
    SHORT keyState2 = GetKeyState(VK_SHIFT);
    int Caps_Lk = 0;
    int Shift = 0;
    if (keyState & 1) {
        Caps_Lk = 1;
    }
    if (keyState2 & 0x8000) {
        Shift = 1;
    }
    std::map<int, std::string> virtualKeyCodeMap;
    virtualKeyCodeMap[0x08] = "凹Back凹";
    virtualKeyCodeMap[0x09] = "凹Tab凹";
    virtualKeyCodeMap[0x0C] = "凹Clear凹";
    virtualKeyCodeMap[0x0D] = "凹E凹";
    virtualKeyCodeMap[0x10] = "凹S凹";
    virtualKeyCodeMap[0x11] = "凹C凹";
    //virtualKeyCodeMap[0x12] = "凹Alt凹";
    virtualKeyCodeMap[0x13] = "凹Pause凹";
    virtualKeyCodeMap[0x14] = "凹CAPSLK凹";
    virtualKeyCodeMap[0x1B] = "凹Esc凹";
    virtualKeyCodeMap[0x20] = "凹Space凹";
    virtualKeyCodeMap[0x21] = "凹PgUp凹";
    virtualKeyCodeMap[0x22] = "凹PgDn凹";
    virtualKeyCodeMap[0x23] = "凹End凹";
    virtualKeyCodeMap[0x24] = "凹Home凹";
    virtualKeyCodeMap[0x25] = "←";
    virtualKeyCodeMap[0x26] = "↑";
    virtualKeyCodeMap[0x27] = "→";
    virtualKeyCodeMap[0x28] = "↓";
    virtualKeyCodeMap[0x29] = "凹Select凹";
    virtualKeyCodeMap[0x2A] = "凹Print凹";
    virtualKeyCodeMap[0x2B] = "凹ExeCute凹";
    virtualKeyCodeMap[0x2C] = "凹PrtScn凹";
    virtualKeyCodeMap[0x2D] = "凹INS凹";
    virtualKeyCodeMap[0x2E] = "凹DEL凹";
    virtualKeyCodeMap[0x2F] = "凹HELP凹";
    virtualKeyCodeMap[0x30] = "0";
    virtualKeyCodeMap[0x31] = "1";
    virtualKeyCodeMap[0x32] = "2";
    virtualKeyCodeMap[0x33] = "3";
    virtualKeyCodeMap[0x34] = "4";
    virtualKeyCodeMap[0x35] = "5";
    virtualKeyCodeMap[0x36] = "6";
    virtualKeyCodeMap[0x37] = "7";
    virtualKeyCodeMap[0x38] = "8";
    virtualKeyCodeMap[0x39] = "9";
    virtualKeyCodeMap[0x41] = "a";
    virtualKeyCodeMap[0x42] = "b";
    virtualKeyCodeMap[0x43] = "c";
    virtualKeyCodeMap[0x44] = "d";
    virtualKeyCodeMap[0x45] = "e";
    virtualKeyCodeMap[0x46] = "f";
    virtualKeyCodeMap[0x47] = "g";
    virtualKeyCodeMap[0x48] = "h";
    virtualKeyCodeMap[0x49] = "i";
    virtualKeyCodeMap[0x4A] = "j";
    virtualKeyCodeMap[0x4B] = "k";
    virtualKeyCodeMap[0x4C] = "l";
    virtualKeyCodeMap[0x4D] = "m";
    virtualKeyCodeMap[0x4E] = "n";
    virtualKeyCodeMap[0x4F] = "o";
    virtualKeyCodeMap[0x50] = "p";
    virtualKeyCodeMap[0x51] = "q";
    virtualKeyCodeMap[0x52] = "r";
    virtualKeyCodeMap[0x53] = "s";
    virtualKeyCodeMap[0x54] = "t";
    virtualKeyCodeMap[0x55] = "u";
    virtualKeyCodeMap[0x56] = "v";
    virtualKeyCodeMap[0x57] = "w";
    virtualKeyCodeMap[0x58] = "x";
    virtualKeyCodeMap[0x59] = "y";
    virtualKeyCodeMap[0x5A] = "z";
    virtualKeyCodeMap[0x5B] = "凹W凹";//L
    virtualKeyCodeMap[0x5C] = "凹W凹";
    virtualKeyCodeMap[0x60] = "0";
    virtualKeyCodeMap[0x61] = "1";
    virtualKeyCodeMap[0x62] = "2";
    virtualKeyCodeMap[0x63] = "3";
    virtualKeyCodeMap[0x64] = "4";
    virtualKeyCodeMap[0x65] = "5";
    virtualKeyCodeMap[0x66] = "6";
    virtualKeyCodeMap[0x67] = "7";
    virtualKeyCodeMap[0x68] = "8";
    virtualKeyCodeMap[0x69] = "9";
    virtualKeyCodeMap[0x70] = "Ⅰ";
    virtualKeyCodeMap[0x71] = "Ⅱ";
    virtualKeyCodeMap[0x72] = "Ⅲ";
    virtualKeyCodeMap[0x73] = "Ⅳ";
    virtualKeyCodeMap[0x74] = "Ⅴ";
    virtualKeyCodeMap[0x75] = "Ⅵ";
    virtualKeyCodeMap[0x76] = "Ⅶ";
    virtualKeyCodeMap[0x77] = "Ⅷ";
    virtualKeyCodeMap[0x78] = "Ⅸ";
    virtualKeyCodeMap[0x79] = "Ⅹ";
    virtualKeyCodeMap[0x7A] = "Ⅺ";
    virtualKeyCodeMap[0x7B] = "Ⅻ";
    virtualKeyCodeMap[0x90] = "凹NumLK凹";
    virtualKeyCodeMap[0x91] = "凹ScrollLK凹";
    virtualKeyCodeMap[0xA0] = "凹S凹";//L
    virtualKeyCodeMap[0xA1] = "凹S凹";
    virtualKeyCodeMap[0xA2] = "凹C凹";//L
    virtualKeyCodeMap[0xA3] = "凹C凹";
    //virtualKeyCodeMap[0xA4] = "左 ALT 凹";
    //virtualKeyCodeMap[0xA5] = "右 ALT 凹";
    virtualKeyCodeMap[0xBA] = ";";
    virtualKeyCodeMap[0xBB] = "=";
    virtualKeyCodeMap[0xBC] = "，";
    virtualKeyCodeMap[0xBD] = "-";
    virtualKeyCodeMap[0xBE] = ".";
    virtualKeyCodeMap[0xBF] = "/";
    virtualKeyCodeMap[0xC0] = "`";
    virtualKeyCodeMap[0xDB] = "[";
    virtualKeyCodeMap[0xDC] = "\\";
    virtualKeyCodeMap[0xDD] = "]";
    virtualKeyCodeMap[0xDE] = "'";

    if (Shift == 1) {
        virtualKeyCodeMap[0x30] = ")";
        virtualKeyCodeMap[0x31] = "!";
        virtualKeyCodeMap[0x32] = "@";
        virtualKeyCodeMap[0x33] = "#";
        virtualKeyCodeMap[0x34] = "$";
        virtualKeyCodeMap[0x35] = "%";
        virtualKeyCodeMap[0x36] = "^";
        virtualKeyCodeMap[0x37] = "&";
        virtualKeyCodeMap[0x38] = "*";
        virtualKeyCodeMap[0x39] = "(";

        virtualKeyCodeMap[0xBA] = ":";
        virtualKeyCodeMap[0xBB] = "+";
        virtualKeyCodeMap[0xBC] = "<";
        virtualKeyCodeMap[0xBD] = "_";
        virtualKeyCodeMap[0xBE] = ">";
        virtualKeyCodeMap[0xBF] = "?";
        virtualKeyCodeMap[0xC0] = "~";
        virtualKeyCodeMap[0xDB] = "{";
        virtualKeyCodeMap[0xDC] = "|";
        virtualKeyCodeMap[0xDD] = "}";
        virtualKeyCodeMap[0xDE] = "\"";
    }
    if ( (Shift == 1 && Caps_Lk == 0)  || (Shift == 0 && Caps_Lk == 1) ) { ///大写
        virtualKeyCodeMap[0x41] = "A";
        virtualKeyCodeMap[0x42] = "B";
        virtualKeyCodeMap[0x43] = "C";
        virtualKeyCodeMap[0x44] = "D";
        virtualKeyCodeMap[0x45] = "E";
        virtualKeyCodeMap[0x46] = "F";
        virtualKeyCodeMap[0x47] = "G";
        virtualKeyCodeMap[0x48] = "H";
        virtualKeyCodeMap[0x49] = "I";
        virtualKeyCodeMap[0x4A] = "J";
        virtualKeyCodeMap[0x4B] = "K";
        virtualKeyCodeMap[0x4C] = "L";
        virtualKeyCodeMap[0x4D] = "M";
        virtualKeyCodeMap[0x4E] = "N";
        virtualKeyCodeMap[0x4F] = "O";
        virtualKeyCodeMap[0x50] = "P";
        virtualKeyCodeMap[0x51] = "Q";
        virtualKeyCodeMap[0x52] = "R";
        virtualKeyCodeMap[0x53] = "S";
        virtualKeyCodeMap[0x54] = "T";
        virtualKeyCodeMap[0x55] = "U";
        virtualKeyCodeMap[0x56] = "V";
        virtualKeyCodeMap[0x57] = "W";
        virtualKeyCodeMap[0x58] = "X";
        virtualKeyCodeMap[0x59] = "Y";
        virtualKeyCodeMap[0x5A] = "Z";
    }
    return virtualKeyCodeMap[testKeyCode];
    
}