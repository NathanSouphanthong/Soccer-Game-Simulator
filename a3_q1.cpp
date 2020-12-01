// *****************************************
// Student Name: Nathan Souphanthong
// Student Number: 20880206
// Assignment 3
// a3_q1.cpp
//
// I hereby declare that this code, submitted for credit for the course SYDE121, is a product of my own efforts.
// This coded solution has not been plagiarized from other sources and has not been knowingly plagiarized by others.
//
// Project: Soccer game simulator
// Purpose: simulate a soccer game with two teams based on 20 randomized events
//
//*********************************************
/*
 Test cases:
 
 Testing the program included manually recording results of the game after each event and comparing it with the computer counted result
 I also checked that halftime was being outputted as per my calculations
 Ran the program multiple times and outputted the generatd numbers with cout to ensure proper randomization
 
 ----------------------------- ----------------------------- ----------------------------- ----------------------------- -----------------------------
Manually counted results of the game:
 8 events generated
End game stats
 Team A
 Score:3
 Shots:5
 Misses:1
 Blocks:0
 Fouls:4
 Yellow cards:0
 Red cards:3
 
 Team B
 Score:3
 Shots:3
 Misses:0
 Blocks:1
 Fouls:3
 Yellow cards:1
 Red cards:0
 
 
 Results were same as consle output
 

 FINAL RESULTS
 -----------------------------------
 Team A              Team B
 Score: 3            Score: 3
 Shots: 5            Shots: 3
 Misses: 1           Misses: 0
 Blocks: 0           Blocks: 1
 Fouls: 4            Fouls: 3
 Yellow cards: 0     Yellow cards: 1
 Red cards: 3        Red cards: 0
 -----------------------------------
 Program ended with exit code: 0
 --------------------------------------------------
--> When 8 results were generated halftime occured after 4th event as expected
 -->When 7 results were generated halftime occured after 3rd event as expected
 
 
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

string shot_simulation(int event,int& blocks, int& score, int& shots, int& misses);
//PURPOSE: simulate the outcomes of a soccer shot and return result as a string message
//  INPUTS: event - the integer num to represent the event that caused a shot to occur
//          blocks - the number of blocks of the team against the shot
//          score - the score of the team taking the shot
//          shots - the number of shots of the team taking the shot
//          misses - the numbeer of misses of the team taking the shot
//  OUTPUTS: string message of the result of the event

string penalty_simulation(int& fouls, int& yellow_cards, int& red_cards);
//PURPOSE: simulate the outcomes of a penalty event
//  INPUTS: fouls - the integer number of total fouls of the team who committed the foul
//          yellow_cards -the integer number of total yellow cards of the team who committed the foul
//          red_cards -the integer number of total red cards of the team who committed the foul
//  OUTPUTS: string message of the result of the event

void output_game_results(int team_a_score, int team_b_score ,int team_a_shots , int team_b_shots ,
                         int team_a_misses , int team_b_misses ,int team_a_fouls ,int team_b_fouls ,
                         int team_a_yellow_card , int team_b_yellow_card , int team_a_red_card,
                         int team_b_red_card , int team_a_blocks ,int team_b_blocks);
//PURPOSE: output the statistics of both team a and b in a chart format
//  INPUTS: team_a_score - integer value of team a total score
//          team_b_score- integer value of team b total score
//          team_a_shots - integer value of team b total shots
//          team_b_shots - integer value of team a total shots
//          team_a_misses - integer value of team a total misses
//          team_b_misses- integer value of team b total misses
//          team_a_fouls- integer value of team a total fouls
//          team_b_fouls- integer value of team b total fouls
//          team_a_yellow_card - integer value of team a total yellow cards
//          team_b_yellow_card- integer value of team b total yellow cards
//          team_a_red_card - integer value of team a total red cards
//          team_b_red_card- integer value of team b total red cards
//          team_a_blocks -  integer value of team a total blocks
//          team_b_blocks - integer value of team b total blocks
//  OUTPUTS: string message of the result of the event


void simulate_game(){
    //initialize and declare variables
    const int TEAM_A_SHOT = 1;
    const int TEAM_B_SHOT = 2;
    const int TEAM_A_FK = 3;
    const int TEAM_B_FK = 4;
    const int TEAM_A_PK = 5;
    const int TEAM_B_PK = 6;
    int team_a_score = 0;
    int team_b_score = 0;
    int team_a_shots = 0;
    int team_b_shots = 0;
    int team_a_misses = 0;
    int team_b_misses = 0;
    int team_a_fouls = 0;
    int team_b_fouls = 0;
    int team_a_yellow_card = 0;
    int team_b_yellow_card = 0;
    int team_a_red_card = 0;
    int team_b_red_card = 0;
    int team_a_blocks = 0;
    int team_b_blocks = 0;
    int event_num;
    
    //randomization seed
    srand(time(0));
    
    //generate number of events
    // lowerbound + (rand()% (upper-lower+1)) -- to generate random number 
    int num_of_events = 1 + rand() % (20-1+ 1);
    cout << num_of_events << " Events Generated!";
    cout<<endl;
    cout<<endl;
    
    //generate 20 events
    for(int events = 1; events <= num_of_events; events++){
        //output halftime results before 11th event
        if (events == (num_of_events/2)+1){
            cout<< endl;
            cout<< "HALF-TIME"<< endl;
            
            cout << "-----------------------------------" << endl;
            output_game_results(team_a_score, team_b_score ,team_a_shots , team_b_shots ,
                                team_a_misses , team_b_misses , team_a_fouls , team_b_fouls ,
                                      team_a_yellow_card ,  team_b_yellow_card ,  team_a_red_card,
                                team_b_red_card ,  team_a_blocks , team_b_blocks);
            cout <<endl;
            cout << "-----------------------------------" << endl;
            cout <<endl;
            cout<< endl;
            
        }
        //generate random number for events on range [1,6]
        event_num = 1 + rand() % (6-1+ 1);
        cout << "Event " << events << ":"<<endl;
        cout << "-----------------------------------";
        cout << endl;
        
        if(event_num == TEAM_A_SHOT){
            cout << "TEAM A SHOOTS!" <<endl;
            cout << shot_simulation(TEAM_A_SHOT, team_b_blocks, team_a_score, team_a_shots,team_a_misses)<<endl;
        }
        
        if(event_num == TEAM_B_SHOT){
            cout << "TEAM A SHOOTS!"<<endl;
            cout << shot_simulation(TEAM_B_SHOT, team_a_blocks, team_b_score, team_b_shots,team_b_misses) <<endl;
        }
        
        if(event_num == TEAM_A_FK){
            cout << "Team B has commited a foul, Team A takes a free kick"<< endl;
            cout << penalty_simulation(team_b_fouls, team_b_yellow_card, team_b_red_card) << " to Team B" << endl;
            cout << shot_simulation(TEAM_A_FK, team_b_blocks, team_a_score, team_a_shots,team_a_misses)<< endl;
            
        }
        
        if(event_num == TEAM_B_FK){
            cout << "Team A has commited a foul, Team B takes a free kick" << endl;
            cout << penalty_simulation(team_a_fouls, team_a_yellow_card, team_a_red_card) << " to Team A"<<endl;
            cout << shot_simulation(TEAM_B_FK, team_a_blocks, team_b_score, team_b_shots,team_b_misses) << endl;
            
        }
        
        if(event_num == TEAM_A_PK){
            cout << "Team B has commited a foul close to goal, Team A takes a penalty kick" <<endl;
            cout << penalty_simulation(team_b_fouls, team_b_yellow_card, team_b_red_card) << " to Team B" <<endl;
            cout << shot_simulation(TEAM_A_PK, team_b_blocks, team_a_score, team_a_shots,team_a_misses)<<endl;
            
        }
        
        if(event_num == TEAM_B_PK){
            cout << "Team A has commited a foul, Team B takes a penalty kick"<<endl;
            cout << penalty_simulation(team_a_fouls, team_a_yellow_card, team_a_red_card) << " to Team A"<<endl;
            cout << shot_simulation(TEAM_B_FK, team_b_blocks, team_a_score, team_a_shots,team_a_misses)<<endl;
            
        }
        cout << endl;
        //delay timer for event output
        sleep_for(nanoseconds(10));
        sleep_until(system_clock::now() +seconds(1));
    }
    cout << endl;
    
    //output final results
    cout<< "FINAL RESULTS"<< endl;
    
    cout << "-----------------------------------" << endl;
    output_game_results(team_a_score, team_b_score ,team_a_shots , team_b_shots ,
                        team_a_misses , team_b_misses , team_a_fouls , team_b_fouls ,
                              team_a_yellow_card ,  team_b_yellow_card ,  team_a_red_card,
                        team_b_red_card ,  team_a_blocks , team_b_blocks);
    cout <<endl;
    cout << "-----------------------------------" << endl;
    
    
}

void output_game_results(int team_a_score, int team_b_score ,int team_a_shots , int team_b_shots ,
                         int team_a_misses , int team_b_misses ,int team_a_fouls ,int team_b_fouls ,
                         int team_a_yellow_card , int team_b_yellow_card , int team_a_red_card,
                         int team_b_red_card , int team_a_blocks ,int team_b_blocks){
    
    //format and output game results
    cout << left << setw(20) << setfill(' ') << "Team A";
    cout << left << setw(20) << setfill(' ') << "Team B";
    cout <<endl;
    
    cout << left << setw(20) << setfill(' ') << "Score: " + to_string(team_a_score);
    cout << left << setw(20) << setfill(' ') << "Score: " + to_string(team_b_score);
    
    cout <<endl;
    
    cout << left << setw(20) << setfill(' ') << "Shots: " + to_string(team_a_shots);
    cout << left << setw(20) << setfill(' ') << "Shots: " + to_string(team_b_shots);
    
    cout << endl;
    
    cout << left << setw(20) << setfill(' ') << "Misses: " + to_string(team_a_misses);
    cout << left << setw(20) << setfill(' ') << "Misses: " + to_string(team_b_misses);
    
    cout << endl;
    
    cout << left << setw(20) << setfill(' ') << "Blocks: " + to_string(team_a_blocks);
    cout << left << setw(20) << setfill(' ') << "Blocks: " + to_string(team_b_blocks);
    
    cout << endl;
    
    cout << left << setw(20) << setfill(' ') << "Fouls: " + to_string(team_a_fouls);
    cout << left << setw(20) << setfill(' ') << "Fouls: " + to_string(team_b_fouls);
    
    cout << endl;
    
    cout << left << setw(20) << setfill(' ') << "Yellow cards: " + to_string(team_a_yellow_card);
    cout << left << setw(20) << setfill(' ') << "Yellow cards: " + to_string(team_b_yellow_card);
    
    cout << endl;
    
    cout << left << setw(20) << setfill(' ') << "Red cards: " + to_string(team_a_red_card);
    cout << left << setw(20) << setfill(' ') << "Red cards: " + to_string(team_b_red_card);
}

string penalty_simulation(int& fouls, int& yellow_cards, int& red_cards){
    //declare and initialize constants
    const int NO_CARD = 0;
    const int Y_CARD = 1;
    const int R_CARD = 2;
    
    //generate random number [0,2]
    int outcome = rand() % (2-0 + 1);
    
    if(outcome == NO_CARD){
        fouls++;
        return "No card given";
    }
    
    if(outcome == Y_CARD){
        yellow_cards++;
        fouls++;
        return "Yellow card given";
        
    }
    
    if(outcome == R_CARD){
        red_cards++;
        fouls++;
        return "Red card given";
       
    }
    return 0;
    
}

string shot_simulation(int event,int& blocks, int& score, int& shots, int& misses){
    //declare and initialize variables and constants
    const int SCORE = 0;
    const int SAVED = 1;
    const int MISSED = 2;
    const int BLOCKED = 3;
    const int TEAM_A_PK = 5;
    const int TEAM_B_PK = 6;
    int outcome = 0;
    
    if(event == TEAM_B_PK || event == TEAM_A_PK){
        outcome = rand() % (2-0 + 1); //generate number between [0,2] if it is a penalty kick
        
    }else{
        outcome = rand() % (3-0 + 1);//generate number between [0,3] if not a penalty kick
    }
    
    
    if(outcome == SCORE){
        score++;
        shots++;
        return "GOAL!!!";
 
    }
    
    if(outcome == SAVED){
        blocks++;
        shots++;
        return "Saved by goal keeper or last defender";
        
    }
    
    if(outcome == MISSED){
        misses++;
        shots++;
        return "MISS!!!";
        
    }
    
    if(outcome == BLOCKED){
        shots++;
        blocks++;
        return "Blocked by someone other than last defender";
     
    }
   
    return 0;
}

int main() {
    //call game function
    simulate_game();
    return 0;
}
