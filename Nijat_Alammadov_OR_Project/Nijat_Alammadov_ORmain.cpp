 /*
 Nijat Alammadov
 
 N-Queens Problem 
 
 9x9 Board with all the solutions
 
 */
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<sstream>
#include<cstring>
#include<map>
#include<list>
#include<queue>
#include<ctime>

using namespace std;

typedef struct
{
    string arrangement;
    int exp;
} individual;

typedef vector<individual*> population_type;

population_type population;
int BoardSize;
int initialPopulationCount = 10;

int ftnValue(string arrangement)
{
    int ftn=(BoardSize*(BoardSize-1))/2;          
    //removing pairs that lie on the same row and on the same diagonal
    for(int i=0; i<BoardSize; i++)
        for(int j=i+1; j<BoardSize; j++)
            if((arrangement[i] == arrangement[j]) ||  (i-arrangement[i] == j-arrangement[j]) || (i+arrangement[i] == j+arrangement[j]))
                ftn--;
    return ftn;
}

individual* createNode()
{
    individual *newNode  = new individual;
    return newNode;
}

void generatePopulation()
{
    string sampleArrangement="";
    individual *temp;
    for(int i=1; i<=BoardSize; i++)
    {
        ostringstream ostr;
        ostr<<i;
        sampleArrangement += ostr.str();
    }

    //adds entries to population list
    for(int i=0; i<initialPopulationCount; i++)
    {
        random_shuffle( sampleArrangement.begin(), sampleArrangement.end());
        temp   = createNode();
        temp->arrangement = sampleArrangement;
        temp->exp = ftnValue(sampleArrangement);
        population.push_back(temp);
    }
}

individual* reproduce(individual *x, individual *y)
{
    individual *child = createNode();
    int n = BoardSize;
    int c = rand()%n;
    child->arrangement = (x->arrangement).substr(0,c) + (y->arrangement).substr(c,n-c+1);
    child->exp = ftnValue(child->arrangement);
    return child;
}

individual* mutate(individual *child)
{
    int randomQueen = rand()%(BoardSize)+1;
    int randomPosition= rand()%(BoardSize)+1;
    child->arrangement[randomQueen] = randomPosition+48;
    return child;
}

int randomSelection()
{
    int randomPos = rand()%population.size() %2;
    return randomPos;
}

bool isFit(individual *test)
{
    if(ftnValue(test->arrangement)==((BoardSize*(BoardSize-1))/2))
        return true;
    return false;
}

bool comp(individual *a, individual*b)
{
    return(a->exp > b->exp);
}

individual* GA()
{
    int randomNum1,randomNum2;
    individual *individualX,*individualY,*child;
    bool found =0;
    while(!found)
    {
        population_type new_population;
        for(unsigned int i=0; i<population.size(); i++)
        {
            sort(population.begin(),population.end(),comp);

            randomNum1 = randomSelection();
            individualX = population[randomNum1];

            randomNum2 =randomSelection();
            individualY = population[randomNum2];

            child = reproduce(individualX,individualY);

            if(rand()%2==0)     //random probability
                child = mutate(child);

            if(isFit(child))
            {
                found=1;
                return child;
            }
            new_population.push_back(child);
        }
        population = new_population;
    }
    return child;
}

void initialize()
{
    srand(time(0));     //for random
    BoardSize=9;
}

int main()
{
    initialize();
   
    map<string,int> solutionsFound;
    int maxSolutions = 92,numFound=0;     
  
    cout<<"---Here are the solutions of problem:---"<<endl<<endl;
    cout<<"---Waiting a little for see all the possible solution:---"<<endl<<endl;
    while(numFound!=maxSolutions)
    {
        generatePopulation();
        individual *solution = GA();
        if(!solutionsFound[solution->arrangement])
        {
            solutionsFound[solution->arrangement]=1;
            cout<<"Solution number of "<<(++numFound)<<":\t"<<solution->arrangement<<endl;
        }
    }
  

     
    return 0;
}
