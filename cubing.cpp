#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
#define LEN 3300
using namespace std;
void outputfn(string);
string inputfn(),cubing_key(),cubing_en(string);
vector<vector<char> > shuffle(vector<vector<char> >);
time_t timer;//経過時間を表示する為の宣言 
struct tm *t_st;
//メモ
//g++ -std=c++1z temp.cpp
string InputFileName="input.txt",OutputFileName="output.txt";
int main(void){
    int pos,gyosu;
    string s;
    s=inputfn();
    s=cubing_en(s);
    outputfn(s);//文字出力関数
    return 0;
}
string inputfn(){//文字入力関数
    string s="",buf;
    char c;
    ifstream reading_file(InputFileName);
    while (!reading_file.eof()){
        getline(reading_file, buf);
        s += buf + "\n";
    }
    s=s.substr(0,s.length()-1);
    cout<<s<<endl;
    printf("\nが入力されました\n");
	return s;
}
void outputfn(string s){//文字出力関数
	ofstream writing_file;
    writing_file.open(OutputFileName, ios::out);//ファイル読み込み
    writing_file<<s;//ファイル出力
    
    cout<<"ファイルへの出力が完了しました"<<endl;
}
string cubing_key(){
	printf("\n転置鍵を入力してください\n注意点：(1)数字列で３の倍数桁入力してください(例:123)\n余った桁は破棄されます(例:1232なら右側の2は破棄されます)\n⇒");
	string key;
	cin>>key;
	key=key.substr(0,key.length()-key.length()%3);//keyの長さを3の倍数にする
	return key;
}
string cubing_en(string s){
	vector<vector<char> > cubing(s.length()/46+1,vector<char>(54));
	int i,j,k;
	for(i=0;i<s.length()/46+1;i++){//平文をcubing配列に格納
		for(j=0;j<45;j++){
			cubing[i][j]=s[i*45+j];
		}
	}
	for(i=44;i>=s.length()%46;i--)cubing[cubing.size()-1][i]='*';//末尾に＊をつける
	
	for(j=0;j<cubing.size();j++){//ハッシュ計算
		for(i=0;i<5;i++){//5面 
			int sum=0;
			for(int k=0;k<9;k++){//9文字 
				sum+=cubing[j][i*9+k];
			}
			sum=sum%26+97;
			cubing[j][45+i]=sum;//ハッシュ代入
		}
	}
	for(i=0;i<cubing.size();i++){//シーケンス番号
		if(i<26*52) cubing[i][50]='A'+(i/26);
		else cubing[i][50]='a'+(i/26);
		if(i<25) cubing[i][51]='A'+(i%26);
		else cubing[i][51]='a'+(i%26);
	}
	for(i=0;i<cubing.size();i++){//乱数文字付与
		if(rand()%10==0)cubing[i][52]=rand()%26+'A';//小文字or大文字の乱数
		else cubing[i][52]=rand()%26+'a';
		if(rand()%10==0) cubing[i][53]=rand()%26+'A';
		else cubing[i][53]=rand()%26+'a';
	}
	/*
	//Visualizer
	printf("平文\n");
	for(i=0;i<=cubing.size()/45;i++){
		for(j=0;j<54;j++){
			if(j==0||j==3||j==6||j==45||j==48||j==51) printf("   ");
			printf("%c",cubing[i][j]);
			if(j==2||j==5||j==8||j==20||j==32||j==44||j==47||j==50||j==53) printf("\n");
		}
		printf("\n");
	}
	*/
	
	string key=cubing_key();
	for(int n=0;n<key.length();n++){//keyはkey.len回文字を変えて暗号化する
		for(j=0;j<cubing.size();j++){//行数回ループ
			for(i=0;i<key.length();i=i+3){//転置
				int num=2+key[i+2]-'3';//型変換('1'->0,'2'->1)
				char letter;
				if(key[i]=='1'){//方向//縦方向 
					for(k=0;k<3-('3'-key[i+2]);k++){//回数 
						letter=cubing[j][0+num];//numは転値対象列(0~2)
						//ここの変則的な数字は配列にしてもいい
						//が、ネストが増える上にプログラムの意味がわからなくなりそうなので残す
						cubing[j][0+num]=cubing[j][3+num];
						cubing[j][3+num]=cubing[j][6+num];
						cubing[j][6+num]=cubing[j][12+num];
						cubing[j][12+num]=cubing[j][24+num];
						cubing[j][24+num]=cubing[j][36+num];
						cubing[j][36+num]=cubing[j][45+num];
						cubing[j][45+num]=cubing[j][48+num];
						cubing[j][48+num]=cubing[j][51+num];
						cubing[j][51+num]=cubing[j][44-num];
						cubing[j][44-num]=cubing[j][32-num];
						cubing[j][32-num]=cubing[j][20-num];
						cubing[j][20-num]=letter;
					}
				}
				else if(key[i]=='2'){//横方向
					for(k=0;k<3-('3'-key[i+2]);k++){
						letter=cubing[j][9+12*num];
						for(int m=0;m<11;m++) cubing[j][9+12*num+m]=cubing[j][10+12*num+m];
						cubing[j][20+12*num]=letter;
					}
				}
				else if(key[i]=='3'){//回転方向
					for(k=0;k<3-('3'-key[i+2]);k++){
						letter=cubing[j][6-3*num];
						cubing[j][6-3*num]=cubing[j][7-3*num];
						cubing[j][7-3*num]=cubing[j][8-3*num];
						cubing[j][8-3*num]=cubing[j][15+num];
						cubing[j][15+num]=cubing[j][27+num];
						cubing[j][27+num]=cubing[j][39+num];
						cubing[j][39+num]=cubing[j][47+3*num];
						cubing[j][47+3*num]=cubing[j][46+3*num];
						cubing[j][46+3*num]=cubing[j][45+3*num];
						cubing[j][45+3*num]=cubing[j][35-num];
						cubing[j][35-num]=cubing[j][23-num];
						cubing[j][23-num]=cubing[j][11-num];
						cubing[j][11-num]=letter;
					}
				}
			}
		}
		key=key.substr(1)+key[0];//鍵を１文字ずらす
	}
	/*
	//Visualizer	
	printf("暗号文\n");
	for(j=0;j<cubing.size();j++){
		for(int k=0;k<54;k++){
			if(k==0||k==3||k==6||k==45||k==48||k==51) printf("   ");
			printf("%c",cubing[j][k]);
			if(k==2||k==5||k==8||k==20|k==32||k==44||k==47||k==50||k==53) printf("\n");
		}
		printf("\n");
	}
	}*/
	
	//Fisher–Yatesアルゴリズム
	//配列をシャッフルしてくれる
	cubing=shuffle(cubing);

	s="";
	for(i=0;i<cubing.size();i++){//出力用 
		for(j=0;j<54;j++)s+=cubing[i][j];
	}
	return s;
}
vector<vector<char> > shuffle(vector<vector<char> > ary)//Fisher–Yates
{
	char c;
	int i,j,k;
    for(i=ary.size()-1;i>0;i--)
    {
		j = rand()%i;
        for(k=0;k<54;k++){
			c=ary[i][k];
			ary[i][k]=ary[j][k];
			ary[j][k]=c;
		}	
    }
	return ary;
}
