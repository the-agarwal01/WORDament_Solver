#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include<algorithm>

#define REP(i,n) for (int i = 1; i <= n; i++)
using namespace std;

set<string> wordList[26];
set<string> foundWords;
string inputArray[5][5];

bool visit[5][5];
int dx[] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};//Specifying All directions in which the  dfs can go
int dy[] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int getIndex(char ch)//getting the position of the first letter so that we can put the whole word in that position
{
	return ch - 'a';
}

void DataStore()
{
	// cout<<"Kindly Wait,Taking the input!"<<endl;
	string word;
	ifstream word_file("corncob_lowercase.txt");//Reading the file
	
	while(word_file>>word)
	{
		int index = getIndex(word[0]);

		wordList[index].insert(word);
	}
	
	word_file.close();
	
	// cout<<"Input Stored Successfully!"<<endl<<endl;
    cout<<"Now,Enter the wordament matrix letter by letter ->"<<endl;
}

void reset()
{
	REP(i , 26) REP(j , 26) visit[i][j] = false;
}

void dfs(int i , int j , string word)
{
	visit[i][j] = true;
	int index = getIndex(word[0]);
	if(wordList[index].find(word) != wordList[index].end())
	{
		foundWords.insert(word);
	}
	
	if(foundWords.size() > 50) return;
	
	REP(index , 8)//Applying 2d dfs and taking all neighbouring letters to the string ,if present we add to the final ans else we continue
	{
		int x = i + dx[index-1];
		int y = j + dy[index-1];
		
		if(x >= 1 && x <= 4 && y >= 1 && y <= 4 && visit[x][y] == false)
		dfs(x , y , word + inputArray[x][y]);
	}
	visit[i][j] = false;
}

bool comp(string a , string b)
{
	return a.size() > b.size();
}

int main()
{
	DataStore();
	
	int code = 1;
	
	while(code)
	{
		foundWords.clear();//Clearing the preiously stored answer
		
		REP(i , 4) REP(j , 4) cin>>inputArray[i][j];//Taking the input
		
		REP(i , 4) REP(j , 4) {
			reset();
			dfs(i , j , inputArray[i][j]);//Running dfs on each and very letter one by one and checking if word possible
		}
		
		cout<<"\nThe total number of words possible are :- "<< foundWords.size()<<endl;

		cout<<endl<<"The words are as follows:-"<<endl;
		
		vector<string> res;
		for(string word : foundWords)
		res.push_back(word);
		
		sort(res.begin() , res.end() , comp);//sorting the words according to their size 
		
		for(string word : res)
		cout<<word<<endl , res.pop_back();
		
		cout<<"enter 0 for exit"<<endl;
		cin>>code;
	}
	
}
