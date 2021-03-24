#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //Cycles through all candidates
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        //If candidate name is valid, then records ranking in rank array
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Nested loops used to check every set of pairs
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            //Record the winner and loser in each set of pairs
            if (preferences [i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Use the bubble sort method of for loops/if statements to sort pairs in descending order
    for (int i = pair_count - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            if ((preferences[pairs[j].winner][pairs[j].loser]) < (preferences[pairs[j + i].winner][pairs[j + 1].loser]))
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + i];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

//Test for cycle by checking arrow coming into each candidate
bool cycle(int end, int cycle_start)
{
    //Return true if there is a cycle created (Recursion base case)
    if (end == cycle_start)
    {
        return true;
    }

    //Loop through candidates (Recursive case)
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (locked[end][i])
        {
            if (cycle(i, cycle_start))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Loop through the pairs
    for (int i = 0; i < pair_count; i++)
    {
        //if cycle function returns false, lock the pair
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //Winner is the candidate with no arrows pointing to them
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        int false_count = 0;

        for (int j = 0; j < n; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
                if (false_count == n)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}

