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

	ifstream infile1("TZ_同指.txt", ios::in);
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
		record >> myfp.serial;
		record >> tmp;
		num = stoi(tmp);
		for(int i = 0; i < num; i++)
		{
			record >> tmp;
			tx = stoi(tmp);
			record >> tmp;
			ty = stoi(tmp);
			record >> tmp;
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
		record >> myfp.serial;
		record >> tmp;
		num = stoi(tmp);
		for(int i = 0; i < num; i++)
		{
			record >> tmp;
			tx = stoi(tmp);
			record >> tmp;
			ty = stoi(tmp);
			record >> tmp;
			ttheta = stoi(tmp);
			myfp.minu.push_back(Minutiae(tx, ty, ttheta));
		}
		fpv.push_back(myfp);
	}


	for(int i =0; i < 5; i++)
	{

		vector<string> res;
		vector<mr> mrv;
		for(decltype(fpv.size()) j = 0; j < fpv.size(); j++)
		{
			mr tmr;
			tmr.serial = fpv[j].serial;
			tmr.score= matchpair(fpv[2*i], fpv[j]);
			mrv.push_back(tmr);
		}
		string outpath = fpv[i].serial + ".txt";
		ofstream output(outpath, ios::out);
		if(!output)
		{
			cout << "打开文件失败！" << endl;
			exit(1);
		}
		for(decltype(mrv.size())j = 0; j < mrv.size(); j++)
		{
			if(mrv[i].score>0.9)
			{
				res.push_back(mrv[i].serial);
			}
		}
		output << res.size() << ",";
		for(decltype(res.size())j = 0; j < res.size(); j++)
		{
			output << res[i] << ",";
		}
		output << endl;

		
	}
	return 0;
}
