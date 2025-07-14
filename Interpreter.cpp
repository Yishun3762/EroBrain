#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

char memory[30000] = {0}; //内存
char *ptr = memory;
void execute(const string& s) {
    size_t p = 0; // 指向当前解析位置的指针
    vector<size_t> ls; // 用于存储循环的起始位置
    while (p < s.length()) {
        if (s.length() - p >= 3 && s.substr(p, 3) == "嗯") {
            ptr++;
            p += 3;
        } else if (s.length() - p >= 3 && s.substr(p, 3) == "哦") {
            ptr--;
            p += 3;
        } else if (s.length() - p >= 3 && s.substr(p, 3) == "啊") {
            (*ptr)++;
            p += 3;
        } else if (s.length() - p >= 3 && s.substr(p, 3) == "齁") {
            (*ptr)--;
            p += 3;
        } else if (s.length() - p >= 6 && s.substr(p, 6) == "去了") {
            cout << (char)(*ptr);
            p += 6;
        } else if (s.length() - p >= 3 && s.substr(p, 3) == "？") {
            *ptr = getchar();
            p += 3;
        } else if (s.length() - p >= 3 && s.substr(p, 3) == "！") {
            if (*ptr == 0) {
                // 如果指针值为0，则跳到匹配的 '♡'
                int tracker = 1; // 追踪未匹配的 '！' 数量
                size_t tp = p + 3; //我在这里使用一个临时指针来遍历字符串
                while (tracker > 0 && tp < s.length()) {
                    if (s.length() - tp >= 3 && s.substr(tp, 3) == "！") {
                        tracker++;
                        tp += 3;
                    } else if (s.length() - tp >= 3 && s.substr(tp, 3) == "♡") {
                        tracker--;
                        tp += 3;
                    } else {
                        tp++;
                    }
                }
                if (tracker == 0) {
                    p = tp;
                } else {
                    throw runtime_error("未匹配的 '！' 指令。");
                }
            } else {
                // 如果指针值不为0，将当前位置压入栈，然后进入循环
                ls.push_back(p);
                p += 3;
            }
        } else if (s.length() - p >= 3 && s.substr(p, 3) == "♡") {
            if (ls.empty()) {
                throw runtime_error("未匹配的 '♡' 指令。");
            }
            
            if (*ptr != 0) {
                // 如果指针值不为0，跳回循环开始的地方
                p = ls.back();
            } else {
                // 如果指针值为0，弹出栈顶，循环结束
                ls.pop_back();
                p += 3;
            }
        } else {
            p++;
        }
    }
}


int main() {
    string inf = ""; //在这里自行输入文件名（摆烂.jpg
    ifstream file(inf);
    if (!file.is_open()) {
        cerr << "错误: 无法打开文件 " << inf << endl;
        return 1;
    }
    string EbCode((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    try {
        execute(EbCode);
    } catch (const runtime_error& e) {
        cerr << "\n运行时错误: " << e.what() << endl;
        return 1;
    }
    cout << endl;
    return 0;
}
