#pragma once
#include <bits/stdc++.h>
#include "Organism.h"
#define N 2                      // Changed it to 2
#define dimension 100            // Changing dimensions to 10k from 1k
#define varieties_in_a_Species 3 // Three different Varieties For now there are three species varying
#define iterationCount 3
#define maxVision 15
#define PlantCount 5
#define InsectCount 10

using namespace std;

// Contains x,y deviation and dist from origin
struct step
{
    int x;
    int y;
    float dist;
};

// Necessary Information to declare a Plant Object
struct biodata_Plant
{
    // struct coordinates2D position; since position decided from the random temporary array
    // int vision_radius; will be equal to zero
    // int speed zero
    int max_energy;
    // unsigned short int aadhar_number Adhaar number is assigned while declaring
};

// Necessary Information to declare an Insect Object
struct biodata_Insect
{
    // struct coordinates2D position; since position decided from the random temporary array
    int vision_radius;
    int speed; // struct speed_structure speed_structure;
    int max_energy;
};

class Universe
{
private:
    Organism *classes[N]; // classes in terms of species ?? then we have only 2 varying species right right now ??

    int organismCount[N]; // Plant(Producer) then Insect(First Trophic Level) Not required since mearely passed as an argument but maybe can store it as an attribute for later use
    biodata_Plant variety_Plant[varieties_in_a_Species] = {{0}, {0}, {0}};
    biodata_Insect variety_Insect[varieties_in_a_Species] = {{0}};
    vector<tuple<int, int>> InsectPosition;

    vector<step> moves;

    void *environment[dimension][dimension];
    int displayEnvironment[dimension * dimension] = {0}; // For a given iteration holds the displayable data, (For now species is number) For now will be a flattened Matrix of the environment
    // vector<int[dimension * dimension]> historyEnvironment; // Hold atleast the layout of the environment at any point in the Iteration
    vector<int *> historyEnvironment;
    vector<struct biodata_Insect> ledgerInsects; // Whether we should change the struct based on what we want to store in the beside vector is what I am thinking,Useful for graphing Traits and creating Histograms

public:
    vector<Insect *> insects;

    void run();
    vector<coordinates2D> adjcent_posns(coordinates2D pos);
    Universe(int maxR, int *organismCount, biodata_Plant variety_Plant[varieties_in_a_Species], biodata_Insect variety_Insect[varieties_in_a_Species]);
    // maxR specifies the maximum vision radius
    // organismCount -> Number of induviduals in each species ([0] for food sources, [1] for first trophic level, [2] for second trophic level...(for now just till first trophic level))
    // plantVarieties list of maxenergies of the different plant sources,
    // insectVarieties the three unique combinations for {vision_radius, speed, and max_energy}
    void printMoves(ofstream& outfile);
    vector<step> getMoves();

    void createMovesVector(int maxR);                                                         // creates the Vision Array
    void initializeVarieties(biodata_Plant *plantVarieties, biodata_Insect *insectVarieties); // A function that takes the varieties as input and creates the variety_Plant/Insect list
    void initializeEnvironment(int *organismCount, int len);                                  // Based on number of organisms create the necessary pointers
    vector<Insect *> getInsects();
    void *getObject(int posX, int posY);                              // Returns the void pointer to the specific location
    int updateUniverse(int initX, int initY, int finalX, int finalY, ofstream& outfile); // Lets us move the initial to the final position, leaving the previous position blank, returns non zero value if an insect was killed, -1 if movement not possible, -2 for death

    void deathOfInsect(int i, int &counter); // Deletes that coordinate and pushes all the other tuples back up once, Also takes a counter/reference as an argument to update the counter as in an iteration we run over the InsectPoition list
    void killInsect(Insect *insect);

    int getNumberOfInsects();           // Returns the length of the InsectPosition list (ie number of organisms) This needs to run aftere every Travel of an organism
    tuple<int, int> getAnInsect(int i); // Returns the Position of the ith Insect in the List InsectPosition

    void creatingAndUpdatingDisplayEnvironmentHistory(ofstream& outfile); // Should create a 1D array(For now) all the rows are flattened
    void writingToFile(ofstream& outfile);

    void printCompleteInfo(int iteration); // Prints the complete information of the Insects in the Universe

    step scanNearestFoodSourceNew(step current_position, int vision_radius, set<pair<int, int>> &ignore_food); // returns the nearest food source from the current position. If none, returns -1,-1. (Can add in another parameter saying levelOfOrganism in case of multiple levels of predators and prey)
    vector<step> movesToLocationNew(step current_position, int number_of_steps, int vision_radius);            // returns the next few moves given current position and destination (shortest path, no diagonal movements)

};
