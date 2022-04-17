#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<cstdlib>
#include"Minutiae.h"
#include<cstdio>

using namespace std;

int main()
{

	vector<fp> fpv;

	ifstream infile1("TZ_同指200_乱序后_Data.txt", ios::in);
	if(!infile1)
	{
		cout << "打开文件失败！" << endl;
		exit(1);
	}
	ifstream infile2("TZ_异指.txt", ios::in);
	if(!infile2)
	{
		cout << "打开文件失败！" << endl;
		exit(1);
	}
	string line;
	while(getline(infile1, line)){
		fp myfp;
		int num;
		string tmp;
		int tx, ty, ttheta;
		istringstream record(line);
		getline(record, tmp, ',');
		myfp.serial = tmp;
		getline(record, tmp, ',');
		num = stoi(tmp);
		for(int i = 0; i < num; i++)
		{
			getline(record, tmp, ',');
			tx = stoi(tmp);
			getline(record, tmp, ',');
			ty = stoi(tmp);
			getline(record, tmp, ',');
			ttheta = stoi(tmp);
			myfp.minu.push_back(Minutiae(tx, ty, ttheta));
		}
		fpv.push_back(myfp);
	}

	while(getline(infile2, line)){
		fp myfp;
		int num;
		string tmp;
		int tx, ty, ttheta;
		istringstream record(line);
		getline(record, tmp, ',');
		myfp.serial = tmp;
		getline(record, tmp, ',');
		num = stoi(tmp);
		for(int i = 0; i < num; i++)
		{
			getline(record, tmp, ',');
			tx = stoi(tmp);
			getline(record, tmp, ',');
			ty = stoi(tmp);
			getline(record, tmp, ',');
			ttheta = stoi(tmp);
			myfp.minu.push_back(Minutiae(tx, ty, ttheta));
		}
		fpv.push_back(myfp);
	}

	for(int i = 0; i < 400; i++)
	{

		vector<string> res;
		vector<mr> mrv;
		for(decltype(fpv.size()) j = 0; j < fpv.size(); j++)
		{
			mr tmr;
			tmr.serial = fpv[j].serial;
			tmr.score = matchpair(fpv[2 * i], fpv[j]);
			mrv.push_back(tmr);
		}
		sort(mrv.begin(), mrv.end(), cpmwithscore);
		string outpath1 = "result_90\\" + fpv[i].serial + ".txt";
		ofstream output1(outpath1, ios::out);
		if(!output1)
		{
			cout << "打开文件失败！" << endl;
			exit(1);
		}
		string outpath2 = "result_95\\" + fpv[i].serial + ".txt";
		ofstream output2(outpath2, ios::out);
		if(!output2)
		{
			cout << "打开文件失败！" << endl;
			exit(1);
		}
		string outpath3 = "result_97\\" + fpv[i].serial + ".txt";
		ofstream output3(outpath3, ios::out);
		if(!output3)
		{
			cout << "打开文件失败！" << endl;
			exit(1);
		}
		int count = 0;
		for(int j = 0; j < 1040; j++)
		{
			res.push_back(mrv[j].serial);
		}
		output1 << 1040 << ",";
		output2 << 520 << ",";
		output3 << 312 << ",";
		for(decltype(res.size())j = 0; j < res.size(); j++)
		{
			output1<< res[j] << ",";
		}
		output1 << endl;
		for(decltype(res.size())j = 0; j < 520; j++)
		{
			output2 << res[j] << ",";
		}
		output2 << endl;
		for(decltype(res.size())j = 0; j < 312; j++)
		{
			output3 << res[j] << ",";
		}
		output3 << endl;

	}
	return 0;
}
