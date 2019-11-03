
#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
extern class Config {
public:
	static int  searchDeep;  //搜索深度
	static int  countLimit; //gen函数返回的节点数量上限，超过之后将会按照分数进行截断
	static int  timeLimit; // 时间限制，秒
	static int  vcxDeep;  //算杀深度
	static bool  random;// 在分数差不多的时候是不是随机选择一个走
	static bool  log;
	static bool opening;
	static int  spreadLimit;// 单步延伸 长度限制
	static bool  star;
	static bool  cache;
	static bool debug;
	static QString fileName0;
};
#endif // !CONFIG_H
