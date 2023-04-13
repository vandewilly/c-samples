#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hangman.h"

char secretword[WORD_SIZE];
char tries[26];
int guessed = 0;

int charexists(char c)
{

    for (int j = 0; j < strlen(secretword); j++)
    {
        if (c == secretword[j])
        {
            return 1;
        }
    }

    return 0;
}

int wrongguesses()
{
    int errors = 0;

    for (int i = 0; i < guessed; i++)
    {

        if (!charexists(tries[i]))
        {
            errors++;
        }
    }

    return errors;
}

int lost()
{
    return wrongguesses() >= 5;
}

int win()
{
    for (int i = 0; i < strlen(secretword); i++)
    {
        if (!alreadyguessed(secretword[i]))
        {
            return 0;
        }
    }

    return 1;
}

void open()
{
    printf("/****************/\n");
    printf("/    HANGMAN    */\n");
    printf("/****************/\n\n");
}

void try()
{
    char guess;
    printf("Type a letter? ");
    scanf(" %c", &guess);

    if (charexists(guess))
    {
        printf("Yeah! The word has the letter %c\n\n", guess);
    }
    else
    {
        printf("\nOoops: the letter %c is not in the word\n\n", guess);
    }

    tries[guessed] = guess;
    guessed++;
}

int alreadyguessed(char c)
{
    int found = 0;
    for (int j = 0; j < guessed; j++)
    {
        if (tries[j] == c)
        {
            found = 1;
            break;
        }
    }

    return found;
}

void draw()
{

    int errors = wrongguesses();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (errors >= 1 ? '(' : ' '), (errors >= 1 ? '_' : ' '), (errors >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n", (errors >= 3 ? '\\' : ' '), (errors >= 2 ? '|' : ' '), (errors >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (errors >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (errors >= 4 ? '/' : ' '), (errors >= 4 ? '\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (int i = 0; i < strlen(secretword); i++)
    {

        if (alreadyguessed(secretword[i]))
        {
            printf("%c ", secretword[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void chooseword()
{
    FILE *f;

    f = fopen("words.txt", "r");
    if (f == 0)
    {
        printf("File not available\n\n");
        exit(1);
    }

    int numwords;
    fscanf(f, "%d", &numwords);

    srand(time(0));
    int random = rand() % numwords;

    for (int i = 0; i <= random; i++)
    {
        fscanf(f, "%s", secretword);
    }

    fclose(f);
}

void addword()
{
    char resp;

    printf("Do you want to add a new word? (Y/N)?");
    scanf(" %c", &resp);

    if (resp == 'Y')
    {
        char newword[WORD_SIZE];

        printf("Type a new word (UPPERCASE): ");
        scanf("%s", newword);

        FILE *f;

        f = fopen("words.txt", "r+");
        if (f == 0)
        {
            printf("File not available\n\n");
            exit(1);
        }

        int qt;
        fscanf(f, "%d", &qt);
        qt++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qt);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newword);

        fclose(f);
    }
}

int main()
{

    open();
    chooseword();

    do
    {

        draw();
        try();

    } while (!win() && !lost());

    if (win())
    {
        printf("\nCongratulations!!!!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }
    else
    {
        printf("\nYou lost!\n");
        printf("Secret word **%s**\n\n", secretword);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    addword();
}