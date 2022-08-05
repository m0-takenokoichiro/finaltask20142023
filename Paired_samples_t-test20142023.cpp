/*Paired_samples_t-test20142023.cpp*/

#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

/*標本のクラスとメンバ関数を定義*/
struct samples 
{
	double A;
	double B;

	void setA(double newA);
	void setB(double newB);
	void show();
};

void samples::setA(double newA) 
{
	A = newA;
}

void samples::setB(double newB)
{
	B = newB;
}

void samples::show() 
{
	cout << "A：" << A << "\t B:" << B << endl;
}

/*各組の差のベクトルを生成*/
vector<double> dif(vector<samples> S)
{
	vector<double> tempdif;
	tempdif.reserve(S.size());	
	for (int i = 0;i < S.size();++i)
	{
		tempdif.push_back(S[i].A - S[i].B);
	}

	return tempdif;
}


/*差の平均を計算*/
double mean_of_dif(vector<double> dif)
{
	double sum = 0;
	for (int i = 0;i < dif.size();++i)
	{
		sum += dif[i];
	}
	double tempmean_of_dif = sum / dif.size();

	return tempmean_of_dif;
}

/*差の不偏分散を計算*/
double unbiased_variance_of_dif(vector<double> dif,double mean_of_dif)
{
	double sum=0;
	for (int i = 0;i < dif.size();++i)
	{
		sum += (dif[i] - mean_of_dif) * (dif[i] - mean_of_dif);
	}

	return sum / (dif.size() - 1);
}

int main()
{
	vector<samples> S;
	ifstream infile("datalist.txt");
	double A, B;

	while (infile >> A >> B)
	{
		S.emplace_back();
		S[S.size() - 1].setA(A);
		S[S.size() - 1].setB(B);
	}
	infile.close();

	
	vector<double> difference = dif(S);						/*各組の差のベクトル*/
	int n = S.size();										/*各組の総数*/
	double d = mean_of_dif(difference);						/*差の平均*/
	double vd = unbiased_variance_of_dif(difference, d);	/*差の不偏分散*/

	cout << "読み込んだデータを次に示す．(各行のAとBが対応する組)" << endl;
	for (int i = 0;i < S.size();++i) S[i].show();
	cout << endl;

	cout << "これらの差A-Bを次に示す．" << endl;
	auto it = difference.begin();							/*イテレータの使用*/
	for (int j = 0;j < difference.size();++j)
	{
		cout << "A-B:" << *(it + j) << endl;
	}
	cout << endl;

	cout << "計算の結果，二つのグループの差の平均d，差の不偏分散vd，組数nは，以下のようになる．" << endl;
	cout << "d=" << d << ",\t vd=" << vd << ",\t n=" << n << endl;

	int degrees_of_freedom = n - 1;							/*自由度の算出*/
	double t = d / sqrt(vd / n);							/*t値の算出*/

	cout << "したがって，帰無仮説のもとでt値は，自由度φ="<< degrees_of_freedom <<"のt分布に従い，この標本では"<<"t=" << t << "となる．" << endl;
}
