#include <cs50.h>
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
void merge_sort(int start, int end);
void merge(int start, int mid, int end);
void lock_pairs(void);
bool creates_cycle(int winner, int loser);
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
// So Rank 1: David puts candidate number that matches david at [1] in ranks
bool vote(int rank, string name, int ranks[])
{
    // If name is a match for the name of a valid candidate,
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        // update the ranks array to indicate that the voter
        // where 0 is the first preference, 1 is the second preference, etc.
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
// so candidate number in [0] is preferred over 1, 2, 3, 4 etc. 
// [1] over , 2, 3, 4 but not over [0]
void record_preferences(int ranks[])
{
    // update the global preferences array to add the current voter’s preferences
    // preferences[i][j] represents number of voters who prefer candidate i over j
    for (int i = 0; i < candidate_count; i++)
    {
        // start at i + 1 to get next candidate and not include self
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
// Updates pair_count to record total number of pairs with a preference
void add_pairs(void)
{
    // ranks[i] voters preference
    // where ranks[0]is the first preference
    // ranks[1] is the second preference
    // check how many think candidate 1 better than 2 with pref[i][j]
    // then how many 2 better than 1 with [j][i]
    // if equal then ignore
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// bubble sort version
// void sort_pairs(void)
// {
//     bool completed = false;
//     while (!completed)
//     {
//         bool swaps = 0;
//         for (int i = 0; i < pair_count - 1; i++)
//         {
//             if (preferences[pairs[i].winner][pairs[i].loser] <
//                 preferences[pairs[i + 1].winner][pairs[i + 1].loser])
//             {
//                 pair temp = pairs[i];
//                 pairs[i] = pairs[i + 1];
//                 pairs[i + 1] = temp;
//                 swaps++;
//             }
//         }
//         if (swaps == 0)
//             completed = true;
//     }
// }

// merge sort version
// Sort pairs array using merge sort
// Strongest victory to weakest
void sort_pairs(void)
{
    merge_sort(0, pair_count - 1);
}

// Recursive merge sort function
void merge_sort(int start, int end)
{
    // Base case
    if (start >= end)
        return;

    int mid = (start + end) / 2;

    // Recursively sort left and right halves
    merge_sort(start, mid);
    merge_sort(mid + 1, end);

    // Merge the sorted halves
    merge(start, mid, end);
}

// Merge two sorted subarrays [start..mid] and [mid+1..end]
void merge(int start, int mid, int end)
{
    int left = start;
    int right = mid + 1;
    int index = 0;

    // Temporary array to hold merged pairs
    pair temp[end - start + 1];

    // Merge by comparing strength of victory in descending order
    while (left <= mid && right <= end)
    {
        int left_strength = preferences[pairs[left].winner][pairs[left].loser];
        int right_strength = preferences[pairs[right].winner][pairs[right].loser];

        if (left_strength > right_strength)
        {
            temp[index++] = pairs[left++];
        }
        else
        {
            temp[index++] = pairs[right++];
        }
    }

    // Copy any remaining elements from the left half
    while (left <= mid)
    {
        temp[index++] = pairs[left++];
    }

    // Copy any remaining elements from the right half
    while (right <= end)
    {
        temp[index++] = pairs[right++];
    }

    // Copy merged result back to the original pairs array
    for (int i = 0; i < index; i++)
    {
        pairs[start + i] = temp[i];
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
// Strongest first, weakeset last order
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!creates_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

// recursively check if a cycle is made
// make sure by chacking graph edges
// need to make sure the candidate has no edges pointing to them
bool creates_cycle(int winner, int loser)
{
    // base case where loser loops to winner
    if (loser == winner)
    {
        return true;
    }

    // e.g. 5, 2
    // flips to 2,5 for locked[loser][i]
    // so then eventually checks if 5,5 if 5,3, 5,4 are also there
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (creates_cycle(winner, i))
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    char *winners[candidate_count];
    int winner_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            // check incoming so reverse them
            if (locked[j][i] == true)
            {
                count++;
            }
        }
        if (count == 0)
        {
            winners[winner_count] = candidates[i];
            winner_count++;
        }
    }

    for (int i = 0; i < winner_count; i++)
    {
        printf("%s\n", winners[i]);
    }
}
