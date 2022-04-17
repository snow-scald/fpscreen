#define _CRT_SECURE_NO_WARNINGS
#ifndef MINUTIAEH
#define MINUTIAEH

#include<cmath>
#include<vector>
#include<string>
#include<algorithm>
#define TLSTEP 50
#define TLRANGE 40

class Minutiae{
public:
	Minutiae(int=0, int=0, int=0);
	void move(int = 0, int = 0);
	bool ispaired(Minutiae &b);

private:
	int x;
	int y;
	int theta;
};

typedef struct FP{
	std::string serial;
	std::vector <Minutiae> minu;
}fp;

typedef struct MATCHRATIO{
	std::string serial;
	double score;
}mr;

void mychange(fp &tfp, int i);

double matchpair(fp &a, fp &b);

bool cpmwithscore(const mr &a, const mr &b);
bool isin(double t, double l, double r);

#endif 

