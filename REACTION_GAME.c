#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "INTERFACE.h"

REACTION_OUTPUT_TABLE REACTION_START(REACTION_OUTPUT_TABLE REACTO_TABLE){
    srand((unsigned)time(NULL));
    REACTO_TABLE.RANDOM_NUMBER = rand() % 100 + 1;
    REACTO_TABLE.DISPLAY_NUMBER_1 = 0;
    REACTO_TABLE.DISPLAY_NUMBER_2 = 0;
    REACTO_TABLE.P1_RESULT = -1;
    REACTO_TABLE.P2_RESULT = -1;
    return REACTO_TABLE;
}

REACTION_OUTPUT_TABLE REACTION_UPDATE(REACTION_OUTPUT_TABLE REACTO_TABLE){
        if(REACTO_TABLE.PLAYER1_STATE == 1 && REACTO_TABLE.PLAYER2_STATE == 0){
            if(REACTO_TABLE.tick100us > 1000 ){//0.1s 更新一次
                REACTO_TABLE.DISPLAY_NUMBER_1++;
                REACTO_TABLE.tick100us = 0;
                return REACTO_TABLE;
            }
        }
        else if(REACTO_TABLE.PLAYER1_STATE == 2 && REACTO_TABLE.PLAYER2_STATE == 0){
            REACTO_TABLE.P1_RESULT = REACTO_TABLE.DISPLAY_NUMBER_1 - REACTO_TABLE.RANDOM_NUMBER;
            if(REACTO_TABLE.P1_RESULT < 0){
                REACTO_TABLE.P1_RESULT = 0 - REACTO_TABLE.P1_RESULT;
            }
        }
        else if(REACTO_TABLE.PLAYER1_STATE == 2 && REACTO_TABLE.PLAYER2_STATE == 1){
            if(REACTO_TABLE.tick100us > 1000 ){//0.1s 更新一次
                if(REACTO_TABLE.DISPLAY_NUMBER_2 > 1000){
                    REACTO_TABLE.DISPLAY_NUMBER_2 = 0;
                }
                else{
                    REACTO_TABLE.DISPLAY_NUMBER_2++;
                }
                REACTO_TABLE.tick100us = 0;
                return REACTO_TABLE;
            }
        }
        else if(REACTO_TABLE.PLAYER1_STATE == 2 && REACTO_TABLE.PLAYER2_STATE == 2){
            REACTO_TABLE.P2_RESULT = REACTO_TABLE.DISPLAY_NUMBER_2 - REACTO_TABLE.RANDOM_NUMBER;
            if(REACTO_TABLE.P2_RESULT < 0){
                REACTO_TABLE.P2_RESULT = 0 - REACTO_TABLE.P2_RESULT;
            }
        }
    return REACTO_TABLE;
}

REACTION_OUTPUT_TABLE REACTION_UPDATE_WHO_WIN(REACTION_OUTPUT_TABLE REACTO_TABLE){
    if(REACTO_TABLE.P1_RESULT < REACTO_TABLE.P2_RESULT){
        REACTO_TABLE.WINNER = 1;
    }
    else if(REACTO_TABLE.P1_RESULT > REACTO_TABLE.P2_RESULT){
        REACTO_TABLE.WINNER = 2;
    }
    else{
        REACTO_TABLE.WINNER = 0;
    }

    return REACTO_TABLE;
}
