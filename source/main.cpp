#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include "generate.hpp"

#define TICKS_PER_SEC 268123480.0

int main(int argc, char* argv[])
{
  	gfxInitDefault();
  	consoleInit(GFX_TOP, NULL);

    Result rc = romfsInit();
    if (rc)
    {
        printf("romfsInit: %08lX\n", rc);
    }

  	// Main loop
  	while (aptMainLoop())
  	{
    		gspWaitForVBlank();
    		gfxSwapBuffers();
    		hidScanInput();

    		// Your code goes here
    		u32 kDown = hidKeysDown();
    		if (kDown & KEY_START)
    			 break; // break in order to return to hbmenu
        if (kDown & KEY_A)
        {
            GenerateRandomizer();
        }
        if (kDown & KEY_B)
        {
            BKey();
        }
  	}

  	gfxExit();
  	return 0;
}
