#include <stdio.h>

#include "OCR.h"
#include "GUI/GUI.h"

int main(int argc, char** argv)
{
	if(argc == 2)
	{
		OCR_Debug(argv[1]);
	}	
	else
	{
		StartGUI(argc, argv);
	}

	return 0;
}