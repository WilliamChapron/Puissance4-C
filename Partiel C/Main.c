#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int Rows;
    int Cols;
    int Grid[7][7];
} Game ;

typedef struct {
    int Choice;
    int Sign;
    int IsWin;
} Player;


void Display(Game* game);
int Input(Player* player, int id);

int PlaceToken(Game* game, int input, int player_sign);
int CheckWin(Game* game, Player* player);

int Player1Manager(Game* game, Player* player1);
int Player2Manager(Game* game, Player* player2);


void Display(Game * game) {

    printf("\n");
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (game->Grid[i][j] == 2)
            {
                printf("|%c|", 'O');
            }
            else if (game->Grid[i][j] == 3)
            {
                printf("|%c|", 'X');
            }
            else {
                printf("|%c|", '-');
            }
        }
        printf("\n");
    }
}

int Input(Player* player,int id)
{

    // Gestion de vidage de cache memoire avec le scanf, imput user

    int error = 0;
    do {
        printf("\n%s %d %s", "Player ", id, ": A quel colonne voulez-vous jouer ?\n");
        error = scanf_s("%d", &player->Choice);

        if (error != 0 && player->Choice < 7) {
            printf("%s %d\n", "Vous avez choisi de jouer a la colonne", player->Choice);
        }

        char c = getchar();
        while (c != '\n') {
            c = getchar();
        };

    } while (error == 0 || player->Choice > 7);


    return player->Choice;
}



// 2 est l'id si un jetons est placé pour le player 1, et 3 est l'id si un jetons est placé pour le player 2

int CheckWin(Game * game,Player * player)
{


    // CHECK HORIZONTAL | Prise en compte des bordure pour ne pas compter si sa sort du tableau 
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (j < 6 && game->Grid[i][j] == player->Sign && game->Grid[i][j+1] == player->Sign)
            {
                //printf("2 token align horizontal\n");
                if (j < 5 && game->Grid[i][j + 2] == player->Sign)
                {
                    //printf("3 token align horizontal\n");
                    if (j < 4 && game->Grid[i][j + 3] == player->Sign)
                    {
                        printf("4 token align horizontal\n");
                        return 1;
                    }
                }
            }
        }
    }


    // CHECK VERTICAL | Prise en compte des bordure pour ne pas compter si sa sort du tableau 
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i < 6 && game->Grid[i][j] == player->Sign && game->Grid[i+1][j] == player->Sign)
            {
                //printf("2 token align vertical\n");
                if (i < 5 && game->Grid[i+2][j] == player->Sign)
                {
                    //printf("3 token align vertical\n");
                    if (i < 4 && game->Grid[i+3][j] == player->Sign)
                    {
                        printf("4 token align vertical\n");
                        return 1;
                    }
                }
            }
        }
    }

    // CHECK DIAGONALE CROISSANTE | Prise en compte des bordure pour ne pas compter si sa sort du tableau 

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i > 0 && j < 6 && game->Grid[i][j] == player->Sign && game->Grid[i-1][j+1] == player->Sign)
            {
                /*printf("2 token align diago croissante\n");*/
                if (i > 1 && j < 5 && game->Grid[i - 2][j + 2] == player->Sign)
                {
                    /*printf("3 token align diago croissante\n");*/
                    if (i > 2 && j < 4 && game->Grid[i - 3][j + 3] == player->Sign)
                    {
                        printf("4 token align diago croissante\n");
                        return 1;
                    }
                }
            }
        }
    }

    // CHECK DIAGONALE INVERSE | Prise en compte des bordure pour ne pas compter si sa sort du tableau 

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i > 0 && j > 0 && game->Grid[i][j] == player->Sign && game->Grid[i-1][j-1] == player->Sign)
            {
                //printf("2 token align diago inverse\n");
                if (i > 1 && j > 1 && game->Grid[i-2][j-2] == player->Sign)
                {
                    //printf("3 token align diago inverse\n");
                    if (i > 2 && j > 2 && game->Grid[i-3][j-3] == player->Sign)
                    {
                        printf("4 token align diago inverse\n");
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

int PlaceToken(Game * game,int input,int player_sign)
{
    int IsPlaced = 0;

    // Gravity
    for (int i = 6; i >= 0; i--)
    {
        if (game->Grid[i][input - 1] != 2 && game->Grid[i][input - 1] != 3)
        {
            game->Grid[i][input - 1] = player_sign;
            IsPlaced = 1;
            return IsPlaced;
        }   
    }
    // Check if cols empty here, else recursive input
    return IsPlaced;
}


int Player1Manager(Game * game, Player * player) 
{
    int input = Input(player,1);
    int IsPlaced = PlaceToken(game, input,player->Sign);
    if (!IsPlaced)
    {
        Player1Manager(game, player);
    }

    Display(game);
    int IsWin = CheckWin(game, player);
    return IsWin;
}

int Player2Manager(Game* game, Player* player)
{
    int input = Input(player, 2);
    int isPlaced = PlaceToken(game,input,player->Sign);
    if (!isPlaced)
    {
        Player2Manager(game, player);
    }

    Display(game);
    int IsWin = CheckWin(game, player);
    return IsWin;

}



int main() {
    // Init game 

    Game game;
    game.Rows = 7;
    game.Cols = 6;


    Player player1;
    player1.Choice = 0;
    player1.IsWin = 0;
    player1.Sign = 2;

    Player player2;
    player2.Choice = 0;
    player2.IsWin = 0;
    player2.Sign = 3;

    

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            game.Grid[i][j] = -2;
        }
    }

    Display(&game);

    while (1) {
        int FullGrid = 1;
        if (Player1Manager(&game, &player1) == 1)
        {
            printf("Player 1 Win\n");
        }
        if (Player2Manager(&game, &player2) == 1)
        {
            printf("Player 2 Win\n");
        }

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (game.Grid[i][j] != player1.Sign || game.Grid[i][j] != player2.Sign)
                {
                    FullGrid = 0;
                }
            }
        }
        if (FullGrid)
        {
            printf("Personne n'a gagner, la grille est remplie !\n");
        }
    }
    return 0;
}












// Ici ce trouve le code que j'utilisais pour verifier horizontalement et verticalement, a la fois je verifiais en + mais aussi en - mais j'ai pas besoin de verifier en - si je verifie en + donc voila 

//if (j > 0 && game->Grid[i][j] == player->Sign && game->Grid[i][j-1] == player->Sign)
            //{
            //    //printf("2 token align horizontal\n");
            //    if (j > 1 && game->Grid[i][j-2] == player->Sign)
            //    {
            //        //printf("3 token align horizontal\n");
            //        if (j > 2 && game->Grid[i][j-3] == player->Sign)
            //        {
            //            printf("4 token align horizontal\n");
            //            return 1;
            //        }
            //    }
            //} 


//if (i > 0 && game->Grid[i][j] == player->Sign && game->Grid[i-1][j] == player->Sign)
            //{
            //    //printf("2 token align vertical\n");
            //    if (i > 1 && game->Grid[i-2][j] == player->Sign)
            //    {
            //        //printf("3 token align vertical\n");
            //        if (i > 2 && game->Grid[i-3][j] == player->Sign)
            //        {
            //            printf("4 token align vertical\n");
            //            return 1;
            //        }
            //    }
            //}