//
//  main.cpp
//  Stable Marriage Problem
//
//  Created by Ramavarapu Sreenivas on 8/29/14.
//  Copyright (c) 2014 Ramavarapu Sreenivas. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class stable_marriage_instance
{
    // Private
    int no_of_couples;
    vector <vector <int> > Preference_of_men;
    vector <vector <int> > Preference_of_women;
    vector <int> match_for_men;
    vector <int> match_for_women;
    
    // private member function: checks if anybody is free in boolean "my_array"
    // returns the index of the first-person who is free in "my_array"
    // if no one is free it returns a -1.
    int anybody_free(vector <bool> my_array)
    {
        for (int i=0;i<no_of_couples;i++)
            if (my_array[i]==true)
            {
                return i;
            }
        return -1;
        // fill the necessary code for this function
    }
    
    // private member function: if index1 is ranked higher than index2
    // in a preference array called "my_array" it returns "true"; otherwise
    // it returns "false"
    bool rank_check (vector <int> my_array, int index1, int index2)
    {
        int i,j;
        for (i=0;i<no_of_couples;i++)
            if (my_array[i]==index1)
                return i;
        for (j=0;j<no_of_couples;j++)
            if (my_array[j]==index2)
                return j;
        if (i<j)
            return true;
        else
            return false;
   // fill the necessary code for this function
    }
    
    // private member function: implements the Gale-Shapley algorithm
    void Gale_Shapley()
    {
        vector <bool> is_man_free;
        vector <bool> is_woman_free;
        vector <vector <bool> > has_this_man_proposed_to_this_woman;
        
        int man_index, woman_index;
        
        // initializing everything
        for (int i=0;i<no_of_couples;i++)
        {
            // do the necessary initialization here
            is_man_free.push_back(true);
            is_woman_free.push_back(true);
            match_for_men.push_back(-1);
            match_for_women.push_back(-1);
            vector <bool> vec_temp;
            for (int j=0;j<no_of_couples;j++)
            {
                vec_temp.push_back(false);
            }
            has_this_man_proposed_to_this_woman.push_back(vec_temp);
            
            
        }
        
        // Gale-Shapley Algorithm
        while ( (man_index = anybody_free(is_man_free)) >= 0)//some man M is un-engaged
        {
            // fill the necessary code here
            vector <int> preference_list;
            for (int i=0;i<no_of_couples;i++)
            {
                preference_list.push_back(Preference_of_men[man_index][i]);
            }
            for (int i=0;i<no_of_couples;i++)
                if (has_this_man_proposed_to_this_woman[man_index][preference_list[i]]==true)
                {
                    woman_index=i;//the first woman on M's preference list to whom M has not proposed
                    has_this_man_proposed_to_this_woman[man_index][woman_index]=true;//M has proposed to w
                }
            
            if (is_woman_free[woman_index]==true)//if w is unengaged
            {
                is_man_free[man_index]=false;
                is_woman_free[woman_index]=false;
                match_for_men[man_index]=woman_index;//assign M and w to be engaged to each other
                match_for_women[woman_index]=man_index;
                
            }
            else
                if (rank_check(Preference_of_women[woman_index], man_index, match_for_women[man_index])==true)
                    //if w prefers M to her fiance Mbar
                {
                    is_man_free[match_for_women[man_index]]=true;//declare Mbar to be unengaged
                    is_man_free[man_index]=false;
                    match_for_men[man_index]=woman_index;//assign M and w to be engaged
                    match_for_women[woman_index]=man_index;
                }
        }
    }
    
    // private member function: reads data
    void read_data(int argc, const char * argv[])
    {
        // fill the necessary code here.  The first entry in the input
        // file is the #couples, followed by the preferences of the men
        // and preferences of the women.  Keep in mind all indices start
        // from 0.
        int value_just_read_from_file;
        vector <int> inputfile; //vector of numbers
        
        ifstream input_file("input1.txt"); // The input file name is "Data.txt"
        // It contains the numbers P_1 P_2 ... P_M
        
        if (input_file.is_open()) // If "Data.txt" exists in the local directory
        {
            while(input_file >> value_just_read_from_file) // As long as your are not at the "end-of-file"
            {
                inputfile.push_back(value_just_read_from_file);
            }
        }
        else
            cout << "Input file input1.txt does not exist in PWD" << endl;
        
        no_of_couples=inputfile[0];
       
        vector <int> vec_temp;
        //vector <vector <int>> Preference_of_men;
        for (int j=0;j<no_of_couples;j++)
        {
            for (int i=0;i<no_of_couples;i++)
            vec_temp.push_back(inputfile[j*no_of_couples+i+1]);
            Preference_of_men.push_back(vec_temp);
            vec_temp.clear();
        }
        
        for (int j=0;j<no_of_couples;j++)
        {
            for (int i=0;i<no_of_couples;i++)
                vec_temp.push_back(inputfile[(no_of_couples+j)*no_of_couples+i+1]);
            Preference_of_women.push_back(vec_temp);
            vec_temp.clear();
        }
        
        cout<<"Number of couples="<<no_of_couples<<endl;
        cout<<endl;
        
        cout<<"Preferences of Men"<<endl;
        cout<<"__________________"<<endl;
        for (int j=0;j<no_of_couples;j++)
        {
            cout<<"("<<j<<"):"<<" ";
            for (int i=0;i<no_of_couples;i++)
             {
                 cout<<Preference_of_men[j][i]<< " ";
             }
            cout<<endl;
        }
        cout<<endl;
        
        cout<<"Preferences of Women"<<endl;
        cout<<"____________________"<<endl;
        for (int j=0;j<no_of_couples;j++)
        {
            cout<<"("<<j<<"):"<<" ";
            for (int i=0;i<no_of_couples;i++)
            {
                cout<<Preference_of_women[j][i]<< " ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    
    // private member function: print solution
    void print_soln()
    {
        // write the appropriate code here
        std::cout <<"Matching for Men"<<endl;
        for (int i=0;i<no_of_couples;i++)
            cout<<"Man:"<<i<<" -> "<<"Woman:"<<match_for_men[i] <<endl;
        cout<<endl;
        std::cout <<"Matching for Women"<<endl;
        for (int i=0;i<no_of_couples;i++)
            cout <<"Woman:"<<i<<" -> "<<"Man:"<<match_for_women[i] <<endl;
        cout<<endl;
    }
    
public:
    void solve_it(int argc, const char * argv[])
    {
        read_data(argc, argv);
        
        Gale_Shapley();
        
        print_soln();
    }
};

int main(int argc, const char * argv[])
{
    stable_marriage_instance x;
    x.solve_it(argc, argv);
}

