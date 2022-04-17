#include "Minutiae.h"

Minutiae::Minutiae(int tx, int ty, int ttheta){
	x = tx;
	y = ty;
	theta = ttheta;
}

//double Minutiae::getx(){
//	return x;
//}
//double Minutiae::gety(){
//	return y;
//}
//double Minutiae::gettheta(){
//	return theta;
//}

void Minutiae::move(int mx, int my){
	x = x + mx;
	y = y + my;
}
bool Minutiae::ispaired(Minutiae &b){
	int dtheta =std::abs(this->theta - b.theta);
	if((isin(b.x,this->x- TLRANGE,this->x+TLRANGE))&& (isin(b.y, this->y - TLRANGE, this->y + TLRANGE))&&(dtheta<15))
	{
		return 1;
	}
	return 0;
}

void mychange(fp &tfp, int i){
	int dx = 0, dy = 0;
	switch(i)
	{
		case 0:dx = 0;dy = 0;
			break;
		case 1:dx = TLSTEP;dy = 0;
			break;
		case 2:dx = TLSTEP;dy = TLSTEP;
			break;
		case 3:dx = 0;dy = TLSTEP;
			break;
		case 4:dx = -TLSTEP;dy = TLSTEP;
			break;
		case 5:dx = -TLSTEP;dy = 0;
			break;
		case 6:dx = -TLSTEP;dy = -TLSTEP;
			break;
		case 7:dx = 0;dy = -TLSTEP;
			break;
		case 8:dx = TLSTEP;dy = -TLSTEP;
			break;
	}
	for(decltype(tfp.minu.size()) i = 0; i < tfp.minu.size(); i++){
		tfp.minu[i].move(dx, dy);
	}
};
double matchpair(fp &a, fp &b){
	int count = 0;
	int tcount;
	for(int i = 0; i < 9; i++)
	{
		fp ta(a);
		mychange(ta, i);
		tcount = 0;
		for(decltype(ta.minu.size()) j = 0; j < ta.minu.size(); j++)
		{
			for(decltype(b.minu.size()) k = 0; k < b.minu.size(); k++){
				if(ta.minu[j].ispaired(b.minu[k])){
					tcount++;
					break;
				}
			}
		}
		count = (count > tcount) ? count : tcount;
	}
	return double(count) / double(a.minu.size());
};
bool cpmwithscore(const mr &a, const mr &b){
	return a.score > b.score;
}
bool isin(double t, double l, double r)
	{
		if(t <= r && t >= l)
		{
			return 1;
		}
		return 0;
	}
