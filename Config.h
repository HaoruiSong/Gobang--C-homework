
#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
extern class Config {
public:
	static int  searchDeep;  //�������
	static int  countLimit; //gen�������صĽڵ��������ޣ�����֮�󽫻ᰴ�շ������нض�
	static int  timeLimit; // ʱ�����ƣ���
	static int  vcxDeep;  //��ɱ���
	static bool  random;// �ڷ�������ʱ���ǲ������ѡ��һ����
	static bool  log;
	static bool opening;
	static int  spreadLimit;// �������� ��������
	static bool  star;
	static bool  cache;
	static bool debug;
	static QString fileName0;
};
#endif // !CONFIG_H
