#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>

using namespace std;


class ConvertNumber
{
public:
	ConvertNumber(long num) :mNumber(num)
	{
		mResult = "";
	}

	void setData(long num) { mNumber = num; return; }
	void setData(string& strNum) { strNum = atol(strNum.c_str()); return;}

	long getData(void) const { return mNumber; }
	bool transForm() 
	{ 
		int ret = 0;

		mResult.clear();  
		transFormYi(mNumber); 


		if (!mResult.empty())
		{
			ret = strcmp(mResult.c_str() + mResult.size() + 1 - sizeof"零", "零");
		}
		if (!ret && !mResult.empty())
			mResult = mResult.substr(0, mResult.size() + 1 - sizeof"零");

		return true; 
	}
	void printResult() { printf("zn:[%s] \n", mResult.c_str()); }

private:

	//1.检查亿位
	bool transFormYi(long inNumber)
	{
		if ( inNumber/YI )
		{
			transFormWan( inNumber/YI);
			mResult += jinzhi[0];
		}
		
		transFormWan( inNumber%YI );
		
		return true;
	}
	//2.检查万位
	bool transFormWan(long inNumber) 
	{ 
		if ( inNumber/WAN )
		{
			if ((inNumber / WAN) % 10 == 0)
				if (!mResult.empty())
					mResult = mResult.substr(0, mResult.size()+1-sizeof"零");

			transFormQian( inNumber/WAN );
			mResult += jinzhi[1];
		}
		
		transFormQian( inNumber%WAN );
		
		return true; 
	}
	//3.检查千位
	bool transFormQian(long inNumber)
	{ 
		if ( inNumber/QIAN )
		{
			transFormGe( inNumber/QIAN );
			mResult += jinzhi[2];
		}
		
		int ret = 0;
		if (!mResult.empty())
		{
			ret = strcmp(mResult.c_str()+mResult.size()+1 - sizeof"零", "零");
		}
		if (!ret && !mResult.empty())
			mResult = mResult.substr(0, mResult.size()+1 - sizeof"零");

		if((inNumber/QIAN == 0) && (!mResult.empty()))
			mResult += gewei[0];
		transFormBai( inNumber%QIAN );
		
		return true;
	}
	//4.检查百位
	bool transFormBai(long inNumber) 
	{ 
		if ( inNumber/BAI )
		{
			transFormGe( inNumber/BAI );
			mResult += jinzhi[3];
		}

		int ret = 0;

		if (!mResult.empty())
			ret = strcmp(mResult.c_str() + mResult.size() + 1 - sizeof"零", "零");
		if(!ret && !mResult.empty())
			mResult = mResult.substr(0, mResult.size()+1-sizeof"零");

		if ((inNumber / BAI == 0) && (!mResult.empty()))
			mResult += gewei[0];
		transFormShi( inNumber%BAI );
		
		return true;
	}
	//5.检查十位
	bool transFormShi(long inNumber) 
	{ 
		if ( inNumber/SHI )
		{
			transFormGe( inNumber/SHI );
			if (mResult == gewei[1])
				mResult.clear();

			mResult += jinzhi[4];
		}


		int ret = 0;
		if (!mResult.empty())
			ret = strcmp(mResult.c_str() + mResult.size() + 1 - sizeof"零", "零");
		if (!ret && !mResult.empty())
			mResult = mResult.substr(0, mResult.size() + 1 - sizeof"零");

		if ((inNumber / SHI == 0) && (!mResult.empty()))
			mResult += gewei[0];

		transFormGe( inNumber%SHI );
		
		return true;
	}
	//6.检查个位
	bool transFormGe(long inNumber) 
	{ 
		if(inNumber)
			mResult += gewei[inNumber];
		return true;
	}


private:
	long	mNumber;
	string  mResult;

	const long SHI = 10;
	const long BAI = 100;
	const long QIAN = 1000;
	const long WAN = 10000;
	const long YI = WAN*WAN;

	char jinzhi[5][16] = { { "亿" },{ "万" },{ "仟" },{ "佰" },{ "拾" } };
	char gewei[10][16] = { {"零"}, { "壹" },{ "贰" },{ "叁" },{ "肆" },{ "伍" },{ "陆" },{ "柒" },{ "捌" },{ "玖" } };
};


int main()
{
	long  numberInput;
	ConvertNumber *conv = new ConvertNumber(0);

	do
	{
		printf("Please input a number: \t");
		scanf("%ld", &numberInput);
		printf("the input number is [%ld] \n", numberInput);

		conv->setData(numberInput);

		conv->transForm();
		conv->printResult();

	} while (1);

	return 0;
}
