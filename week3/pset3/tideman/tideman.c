#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser int represent candidate index in candidate array
typedef struct
{
    int winner;
    int loser;
} pair;

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
bool is_candidate_exist(string name);
int get_ranked_candidate_index(int ranks[], int candidate_index);
bool does_make_circle(int cycle_start, int loser);

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
    if (!is_candidate_exist(name))
    {
        return false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
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
    for (int i = 0; i < candidate_count; i++)
    {
        int ith_cand_index = get_ranked_candidate_index(ranks, i);
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                preferences[i][j] = 0;
            }
            else
            {
                int jth_cand_index = get_ranked_candidate_index(ranks, j);
                if (ith_cand_index < jth_cand_index)
                {
                    preferences[i][j] += 1;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int k = i; k < candidate_count; k++)
        {
            if (k != i)
            {
                if (preferences[i][k] > preferences[k][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = k;
                    pair_count += 1;
                }
                else if (preferences[k][i] > preferences[i][k])
                {
                    pairs[pair_count].winner = k;
                    pairs[pair_count].loser = i;
                    pair_count += 1;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int winner_cand = pairs[i].winner;
            int loser_cand = pairs[i].loser;

            int next_winner_cand = pairs[i + 1].winner;
            int next_loser_cand = pairs[i + 1].loser;

            int first_strength = preferences[winner_cand][loser_cand] - preferences[loser_cand][winner_cand];
            int second_strength = preferences[next_winner_cand][next_loser_cand] - preferences[next_loser_cand][next_winner_cand];

            if (first_strength < second_strength)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!does_make_circle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int lost = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                lost += 1;
            }
        }

        if (lost == candidate_count)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

bool is_candidate_exist(string name)
{
    bool is_exist = false;

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            is_exist = true;
        }
    }

    return is_exist;
}

int get_ranked_candidate_index(int ranks[], int candidate_index)
{
    int index_in_rank;

    for (int i = 0; i < candidate_count; i++)
    {
        if (ranks[i] == candidate_index)
        {
            index_in_rank = i;
        }
    }

    return index_in_rank;
}

bool does_make_circle(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (does_make_circle(cycle_start, i))
            {
                return true;
            }
        }
    }
    return false;
}

