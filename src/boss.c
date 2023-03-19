/**
 * @file boss.c
 * 
 * @brief 
 * 
 * @author Clément Hibon
 * @date 18 mars
 * @version 1.1
 */





#include <stdio.h>
#include <stdlib.h>

#include "../include/boss.h"





/**
 * @brief 
 * 
 * @return t_boss_flags 
 */
t_boss_flags initialiserBossFlags() {
    t_boss_flags flags;

    flags.lundi = 0;
    flags.mercredi = 0;
    flags.vendredi = 0;


    return flags;
}
