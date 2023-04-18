/* DECLARATIONS START */
#include <iostream>	
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

bool bMenu = true;
int inputConverstion();
void mainMenu();
int get_max_id();
void writeData();
void readData();
void handle_delete_cust();
void showHighscore();
void gameGuessNum();
void gameHeader();
void gameRules();
void sleepFunc();

template <typename K, typename V>
class table 
{
	public:
	
	map<K, V> hashtable;

	void insert_row(K key, V value)
	{
		hashtable.emplace(key, value);
	}

};
class Competitor
{
	public:
	int id;
	string name;
	string city;
	int score;

	//constructor for Competitor class object
	Competitor (int i_ID, string i_name, string i_City, int i_Score)
	:id(i_ID),
	name(i_name),
	city(i_City),
	score(i_Score){};
};

table <int, Competitor> competitorList;
/* DECLARATIONS END */