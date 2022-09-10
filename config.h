#ifndef CONFIG_H
#define CONFIG_H

#include "wavfil.h"

struct audWav config(struct audWav wave);
struct audWav chanFileLoc(struct audWav wave);
int chanSampleR(struct audWav wave);
int chanChanNum(struct audWav wave);
#endif
