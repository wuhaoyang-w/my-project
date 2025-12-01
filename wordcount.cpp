#include "wordcount.h"
#include <string>
using namespace std;

/*
读取用户通过命令行指定的文本文件（如`input.txt`），支持英文文本即可；
实现 3 类基础统计:
1.总行数（空行不计入，空行定义：仅含空格 / 换行符的行）；
2.总单词数（以空格 / 标点`!,.?;:`分割，如 “hello,”“hello!” 均算 “hello”）；
3.高频单词 Top5（仅统计出现次数≥2 的单词，忽略大小写，如 “Hello” 和 “hello” 视为同一单词）；

将统计结果写入result.txt:
总行数：15
总单词数：280
高频单词Top5：
hello 8次
world 5次
cpp 4次
python 3次
code 2次
*/

void Textfile(string filename)
{

    string content; // 用来读取文件内容
    int countline = 0;
    int countword = 0;
    map<string, int> preserve_word;
    ifstream ifs;
    ifs.open(filename, ios::in);
    // 判断文件是否打开成功
    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }

    while (getline(ifs, content))
    {
        // 基础统计1：判断是否为空行
        bool is_emptyline = true;
        for (int i = 0; i < content.size(); i++)
        {
            char c = content[i];
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            {
                is_emptyline = false;
                break;
            }
        }
        if (!is_emptyline)
        {
            countline++;
        }

        // 基础统计2：判断总单词数
        // 用来拼接单词
        string tmpword;

        for (int i = 0; i < content.size(); i++)
        {
            if (content[i] == ',' || content[i] == '!' || content[i] == '.' || content[i] == '?' || content[i] == ' ' || content[i] == ';' || content[i] == ':')
            {
                string word;
                if (!tmpword.empty())
                {
                    for (int j = 0; j < tmpword.size(); j++)
                    {
                        // 拼接单词并全部转换为小写
                        word += tolower(tmpword[j]);
                    }
                    preserve_word[word]++;
                    countword++;
                    tmpword.clear();
                }
            }
            else
            {
                tmpword += content[i];
            }
        }
        // 可能处理最后一个单词
        if (!tmpword.empty())
        {
            string word;
            for (int i = 0; i < tmpword.size(); i++)
            {
                word += tolower(tmpword[i]);
            }
            preserve_word[word]++;
            countword++;
            tmpword.clear();
        }
    }

    // 将map转换为vector
    vector<pair<string, int>> sort_word;
    for (map<string, int>::iterator it = preserve_word.begin(); it != preserve_word.end(); it++)
    {
        if (it->second >= 2)
        {
            sort_word.push_back(*it);
        }
    }
    // 对vector进行排序
    sort(sort_word.begin(), sort_word.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             return a.second > b.second;
         });
    // 只保留前5个单词
    if (sort_word.size() > 5)
    {
        sort_word.resize(5);
    }
    ifs.close();

    // 将内容写的到result.txt里
    ofstream ofs;
    ofs.open("result.txt", ios::out);
    // ：是中文输入法
    ofs << "总行数：" << countline << endl;
    ofs << "总单词数：" << countword << endl;
    ofs << "高频单词top5：" << endl;

    for (int i = 0; i < sort_word.size(); i++)
    {
        ofs << sort_word[i].first << " " << sort_word[i].second << "次" << endl;
    }

    ofs.close();
}
