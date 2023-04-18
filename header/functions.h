#include "declarations.h"

/*FUNCTIONS START*/
int inputConverstion()
{
    string userInput;
    int inputInt;
    bool is_ok = false;

    while(not is_ok)
    {
        cin>>userInput;

        try
        {
            inputInt = stoi(userInput);	
            is_ok = true;
            return inputInt;
        }
        catch(exception &err)
        {
            cout<<"Conversion failure: "<< err.what() <<endl;
        }
    }
    return 0;
}
void mainMenu()
{
	int userInput;
	while (bMenu)
	{
		system("cls");
		showHighscore();
		cout << "What would you like to do?\n[1] Start session\n[2] End session\n[3] Delete competitor" << endl;
		int userInput = inputConverstion();
		switch (userInput)
		{
			case 1:
				//sends user to the guessing game
				gameGuessNum();
				break;
			
			case 2:
				//exits program
				bMenu = false;
				break;
			
			case 3:
				//sends user to delete function
				handle_delete_cust();
				break;
			
			default:
				cout << "Wrong input!" << endl;
				break;
		}
	}
}
int  get_max_id() 
{
	int max_id = 0;
	for (auto it = competitorList.hashtable.begin(); it != competitorList.hashtable.end(); ++it) 
	{
		if (it->second.id > max_id) 
		{
			max_id = it->second.id;
		}
	}
	return max_id;
}
void writeData() 
{
    ofstream newFile;
    
    newFile.open("competitor.csv", ofstream::trunc);
    for (auto it = competitorList.hashtable.begin(); it != competitorList.hashtable.end(); ++it) 
    {
        newFile << it->first << ',';
        newFile << it->second.name << ',';
        newFile << it->second.city << ',';
        newFile << it->second.score;
        newFile << endl;
    }
    newFile.close();
}
void readData() 
{
    ifstream ifs;
    string line;
    ifs.open("competitor.csv",ios::in);
    while (getline(ifs,line)) 
    {
        stringstream ss(line);
        string id,name,city,score;

        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,city,',');
        getline(ss,score,',');
        
        Competitor new_p(stoi(id), name, city, stoi(score));
        competitorList.insert_row(stoi(id), new_p);
    }
}
void handle_delete_cust() 
{
    int delete_id;
    cout << "Enter Competitor ID to delete: ";
    cin >> delete_id;
    
    auto search = competitorList.hashtable.find(delete_id);
    
    if (search != competitorList.hashtable.end()) 
	{
        cout << "Found Competitor ID " << search->first << " with the following information: " << endl;
        cout << "Name: " << search->second.name << endl;
        cout << "City: " << search->second.city << endl;
        cout << "Score: " << search->second.score << endl;

		cout << "Are you sure you want to delete this Competitor?" << endl;
		cout << "[1] Yes\t[2] No" << endl;
        int awnser = inputConverstion();
        if (awnser == 1) 
		{
            competitorList.hashtable.erase(search->first);
            cout << "Competitor deleted." << endl;
			cout << "Sending you back to main menu...";
			writeData();
			sleepFunc();
        } 
		else 
		{
			cout << "Competitor not deleted." << endl;
			cout << "Sending you back to main menu...";
			sleepFunc();
		}
    } 
	else 
	{
        cout << "No customer ID " +  to_string(delete_id) + " exists." << endl;
		cout << "Sending you back to main menu...";
		sleepFunc();
    }
}
void showHighscore()
{
    string separator = "|-----|--------------------|---------------|----------|\n";
    string h1 = "ID", h2 = "Name", h3 = "City", h4 = "Score";

    cout << "\n|" << setfill ('-') << setw (54) << "|" << endl;
    cout << "|" << setfill (' ') << setw(54) << "|" << endl;
    cout << "|" << setw(40) << "Welcome to Adam's Mini Game" << setw(14) << "|" << endl;
    cout << "|" << setfill (' ') << setw(54) << "|" << endl;
    cout << "|=====|====================|===============|==========|\n";
    cout  
         << "|" << setw(5) << h1 
         << "|" << setw(20) << h2 
         << "|" << setw(15) << h3 
         << "|" << setw(10) << h4 << "|" << endl;
    cout << "|=====|====================|===============|==========|\n";

	for (auto it = competitorList.hashtable.begin(); it != competitorList.hashtable.end(); ++it) 
	{
		cout << "|" << setw(5) << it -> first 
			 << "|" << setw(20) << it->second.name 
			 << "|" << setw(15) << it->second.city
			 << "|" << setw(10) << it->second.score
			 << "|" << endl;
		cout << separator; 
    }
}
void gameGuessNum()
{
	int score = 0, lastID = get_max_id();

	string name, city;
	cout << "Enter player name: ";
	cin.ignore();
	getline(cin, name);
	cout << "Enter player city: ";
	getline(cin, city);

	bool game = true;
    srand(time(0));

    while (game)
    {
        int secretNum, attemptsLeft = 4, countingAttempts = 1;
        const int maxAttempts = 5;
        secretNum = rand() % 10 +1;

		system("cls");

        cout << "Cheat: " << secretNum << endl;
        gameHeader();
		gameRules();
        cout << "Enter your guess: ";
		int guess = inputConverstion();

        while ((secretNum != guess) && (countingAttempts != maxAttempts))
        {   
            system("cls");
            cout << "Cheat: " << secretNum << endl;
			gameHeader();
            if (secretNum < guess) 
			{
				cout << "The number is lower\n";
				cout << "Attempts left: " << attemptsLeft << endl;
			}
			else if (secretNum > guess) 
			{
				cout << "The number is higher\n";
				cout << "Attempts left: " << attemptsLeft << endl;
			}
            cout << "Enter your guess: ";
            guess = inputConverstion();
            attemptsLeft--;
            countingAttempts++;
        }
        
        if (secretNum == guess)
        {
            if (countingAttempts == 1)
			{
				cout << "You guessed right on the first attempt!" << endl;
				cout << "Adding 50 points to your score" << endl;
				score += 50;
			}
			else if (countingAttempts == 2)
			{
				cout << "You guessed right on the second attempt!" << endl;
				cout << "Adding 25 points to your score" << endl;
				score += 25;
			}
			else if (countingAttempts == 3)
			{
				cout << "You guessed right on the third attempt!" << endl;
				cout << "Adding 15 points to your score" << endl;
				score += 15;
			}
			else if (countingAttempts == 4)
			{
				cout << "You guessed right on the fourth attempt!" << endl;
				cout << "Adding 10 points to your score" << endl;
				score += 10;
			}
			else if (countingAttempts == 5)
			{
				cout << "You guessed right on the final attempt!" << endl;
				cout << "Adding 5 points to your score" << endl;
				score += 5;
			}
			cout << "Loading new round...";
			sleepFunc();
        }
        else
        {
    		cout << "You failed! The correct number was " << secretNum << endl;
			cout << "Would you like to play again?" << endl;
			cout << "[1] Yes\n[2] No" << endl;
			int playAgain = inputConverstion();
			if(playAgain == 1)
			{
				game = true;
			}
			else if (playAgain == 2)
			{
				game = false;
			}
        }
    }
	
	//adds player to map 
	Competitor new_player(lastID+1, name, city, score);
	competitorList.insert_row(lastID+1, new_player);
    writeData();
}
void gameHeader()
{
	cout << "|" << setfill ('-') << setw (54) << "|" << endl;
    cout << "|" << setfill (' ') << setw(54) << "|" << endl;
    cout << "|" << setw(41) << "Welcome to the guessing game!" << setw(13) << "|" << endl;
    cout << "|" << setw(54) << "|" << endl;
    cout << "|" << setfill ('-') << setw (54) << "|" << endl;
}
void gameRules()
{
	cout << "Guess a number between 1 and 10" << endl;
	cout << "You have 5 attempts to guess the right number" << endl;
	cout << "The score is depening on which attempt you guess correctly" << endl;
	cout << "If you guess correctly the game continues and you can improve your higscore" << endl;
}
void sleepFunc()
{
	auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(5000ms);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
}
/*FUNCTIONS END*/