/*
Let W be the set of Women and M be the set of Men
---------------------------------------------------------------------------------------------
2. Initially, all m ε M and w ε W are free
3. While there is a man m who is free and hasn’t proposed to every woman w :
4. Choose a man m
5. Let w be the highest-ranked woman in m’s preference list to whom m has not yet proposed
6. If w is free then
7. (m, w) become engaged
8. Else w is currently engaged to m’
9. If w prefers m’ to m then
10. m remains free
11. Else w prefers m to m’
12. (m, w) become engaged
13. m’ becomes free
14. End While
15. Return the set S of engaged pairs
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

//Number of men/women
int N = 4;

//Find next preferred option

//Check if W prefers m or m1
bool wPrefersM1(std::vector<std::vector<int>>women, int w, int m1, int m2) {
    //Iterates through woman's preferences until one of the two is found first
    for (size_t i = 0; i < N; i++) {
        if (women[w][i] == m1) {
            return true; //Prefers m1
        }

        if (women[w][i] == m2) {
            return false; //Prefers m2
        }
    }
}

//Print stable matches
//FIXME: Women input is actually for men and vice versa
void stableMarriage(std::vector<std::vector<int>>men, std::vector<std::vector<int>>women) {   //FIXME: Change 4 to N
    //List of women's partners (men)
    std::vector<int>wPartners;

    //Array indicating if men are free
    std::vector<bool>freeMen;

    //Initialize all men to free and size of wPartners
    for (size_t i = 0; i < N; i++) {
        freeMen.push_back(true);
        wPartners.push_back(-1);
    }
    int numFree = N;

    //While there is a free man
    while (numFree > 0) {
        //Pick first free man by iterating through
        int m = 0;
        for (m = 0; m < N; m++) {
            //If free stop searching for next man
            if (freeMen[m])
                break;
        }

        //Find first woman in preference list
        for (size_t i = 0; i < N && freeMen[m]; i++) {
            //Woman to compare
            int w = women[m][i];
            //FIXME: Test Output std::cout << "Woman: " << w << "\tPartner: " << wPartners[w] << std::endl;

            //If free (not found in partners list) then (m,w) get engaged
            if (wPartners[w] == -1) {
                wPartners[w] = m;
                freeMen[m] = false;
                numFree--;
            }
            //If not free check preference
            else {
                //Man to compare
                int m2 = wPartners[w];
                //If m preferred then (m,w) get engaged
                if (wPrefersM1(women, w, m, m2)) {
                    wPartners[w] = m;
                    freeMen[m] = false;
                    freeMen[m2] = true;
                }
            }
            //If not then move to next woman (loop again)
        }

    }
    //Print solution
    std::cout << "Man\tWoman" << std::endl;
    for (size_t i = 0; i < N; i++) {
        std::cout << wPartners[i] << "\t" << i << std::endl;
    }
}


int main() {
/*
    std::string fileName;
    std::cout << "Enter the file name (include .csv)";
    std::cin >> fileName;

    std::vector<std::vector<std::string>>men;
    std::vector<std::string>row;
    std::string line, word;
    std::fstream file (fileName, std::ios::in);
    if (file.is_open()) {
        while(std::getline(file, line)) {
            row.clear();
        }

        std::stringstream str(line);

        while(getline(str, word, ',')) {
            row.push_back(word);
            men.push_back(row);
        }

    } else {
        std::cout << "Error opening file\n";
    }

    for(int i=0;i<men.size();i++)
    {
        for(int j=0;j<men[i].size();j++)
        {
            std::cout<<men[i][j]<<" ";
        }
        std::cout<<"\n";
    }*/


    //Men's preferences


    /* Sample data*/
    std::vector<std::vector<int>>men = {  {3, 1, 2, 0},
                                          {1, 2, 0, 3},
                                          {3, 0, 2, 1},
                                          {3, 1, 2, 0},
    };

    //Women's preferences
    std::vector<std::vector<int>>women = {  {0, 3, 2, 1},
                                            {1, 2, 3, 0},
                                            {0, 1, 2, 3},
                                            {1, 3, 0, 2},
    };

    stableMarriage(women, men);
    return 0;
}
