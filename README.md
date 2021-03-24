# tideman_election

CS50 Problem Set: https://cs50.harvard.edu/x/2021/psets/3/tideman/

This problem set required the implementation of 6 functions (vote, record_preferences, add_pairs, sort_pairs, lock_pairs, print_winner) in the tideman.c file. 

Vote:
The vote function takes the name of the candidate, rank of the candidate, and ranks array as input. A for loop cycles through all of the candidates, checking that 
the candidate name input by the user is a valid candidate in the election. If valid, then the candidates rank will be recorded in the ranks array and the function 
will return true. Otherwise, the function will return false. 

Record_Preferences:
The record_preferences function takes the ranks array as input for each voter. The function loops through each voter, updating the global preferences array with 
each voter's preferences. The preferences array is equal to the number of voters that prefer candidate i over candidate j. 

Add_Pairs:
The add_pairs function will add all pairs of candidates where one candidate is preferred and update the global variable pair_count with the number of candidate 
pairs. If the candidates are tied, they will not be added to the array.

Sort_Pairs:
The sort_pairs function sorts the pairs of candidates is decreasing order by strength of victory through the use of the bubble sort method. 

Lock_Pairs:
The lock_pairs function will create the locked in order of candidate rankings as long as the locked in pairs don't create a cycle with the winners, meaning there 
would be no way to pick a winner. 

Print_Winner:
The print_winner function will print out the name of the candidate the wins the tideman election as the "source" meaning that no other candidate beats them in a 
head to head matchup. 
