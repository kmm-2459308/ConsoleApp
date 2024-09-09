//======================================
//	Ou C
//======================================
#include "Stage.h"
#include "Lord.h"
#include "UI.h"
#include "Utility.h"
#include "Chronology.h"
#include <stdio.h>   // printf(),putchar()
#include <stdlib.h>
// Övg^Cv
static void game();
static void DrawGameOver(Stage* stage);
static void DrawEnding(Stage* stage);

int main()
{
    system("chcp 65001");// [6-5-0]ã³ã³ã½ã¼ã«ã®æå­ã»ãããUTF-8ã«è¨­å®ãã
    InitRand();
    int c;
    do {
        game();
        printf("à¤êx(y/n)?");
        while (true) {
            c = GetKey();
            if (c == 'y' || c == 'n') {
                break;
            }
        }
    } while (c == 'y');
    return 0;
}

const int CHRONOLOGY_BUFF_SIZE = 1024;
const int START_YEAR = 196;
extern Castle castles[];

static void game()
{
    Stage stage[1];
    Chronology chro[1];
    InitializeChronology(chro, CHRONOLOGY_BUFF_SIZE);
    InitializeStage(stage, castles, CASTLE_MAX, START_YEAR, chro);

    StartStage(stage);
    CastleId playerCastle = InputPlayerCastle(stage);
    SetPlayerLord(stage, playerCastle);
    IntroStage(stage, playerCastle);

    while (true) {
        // ^[ÌÔðVt
        MakeTurnOrder(stage);
        for (int i = 0; i < stage->castlesSize; i++) {
            // eéÌ^[Às
            ExecTurn(stage, i);
            // v[Ì¯?
            if (IsPlayerLose(stage)) {
                DrawGameOver(stage);
                goto exit;
            }
            // v[Ì¿
            if (IsPlayerWin(stage)) {
                DrawEnding(stage);
                goto exit;
            }
        }
        // Nzµ
        NextYear(stage);
    }
exit:
    FinalizeStage(stage);
    FinalizeChronology(chro);
}

static void DrawGameOver(Stage* stage)
{
    DrawScreen(stage, DM_GameOver, 0);
    // N\ð\¦
    PrintChronology(stage->chro);
    putchar('\n');
    printf("f`ld@nudq\n");
    WaitKey();
}

static void DrawEnding(Stage* stage)
{
    DrawScreen(stage, DM_Ending, 0);
    // N\ð\¦
    PrintChronology(stage->chro);
    int year = stage->year + 3;
    const char* name1 = GetLordFamilyName(stage, stage->playerLord);
    const char* name2 = GetLordFirstName(stage, stage->playerLord);
    printf("%dËñ@ %s %sª@¹¢¢½¢µå¤®ñÉ@Éñºçêé\n", year, name1, name2);
    printf("%dËñ@%s%sª@%sÎ­Óð@Ðç­\n", year, name1, name2, name1);
    putchar('\n');
    printf("sgd@dmc");
    WaitKey();
}