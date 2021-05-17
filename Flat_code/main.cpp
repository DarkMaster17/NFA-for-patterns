#include<stdio.h>
#include<string.h>
#define NR_OF_CHARS 256
int getNextState(char *pattern, int A, int state, int x)
{
    if (state < A && x == pattern[state])
        return state+1;
    int nextstate,i;
    for (nextstate = state; nextstate > 0; nextstate--)
    {
        if (pattern[nextstate-1] == x)
        {
            for (i = 0; i < nextstate-1; i++)
                if (pattern[i] != pattern[state-nextstate+1+i])
                    break;
            if (i == nextstate-1)
                return nextstate;
        }
    }
    return 0;
}
void computeTFTable(char *pattern, int A, int TF[][NR_OF_CHARS])
{
    int state, x;
    for (state = 0; state <= A; ++state)
        for (x = 0; x < NR_OF_CHARS; ++x)
            TF[state][x] = getNextState(pattern, A, state, x);
}
void search(char *pattern, char *txt)
{
    int A = strlen(pattern);
    int B = strlen(txt);
    int TF[A+1][NR_OF_CHARS];
    computeTFTable(pattern, A, TF);
    int i, state=0;
    for (i = 0; i < B; i++)
    {
        state = TF[state][txt[i]];
        if (state == A)
            printf ("\n Pattern found at index %d",
                                           i-A+1);
    }
}
int main()
{
    char *txt = "SOMEDAYSOMEONESOMEWHEREWILLTYPESOMETHING";
    char *pat = "SOME";
    search(pat, txt);
    return 0;
}
