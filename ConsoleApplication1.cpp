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


	int ps=0;
	//double res=matchpair(fpv[82], fpv[83]);
	for(int i =0; i < 100; i++)
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
		sort(mrv.begin(),mrv.end(), cpmwithscore);
		for(int j = 0; j < 330; j++)
		{
			res.push_back(mrv[j].serial);
		}
		for(decltype(res.size()) j = 0; j < res.size(); j++)
		{
			if(res[j] == fpv[2*i + 1].serial)
			{
				ps++;
				break;
			}
		}
	}
	cout << double(ps) << endl;
	return 0;
}
