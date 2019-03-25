#include "dtb_platform.h"

int main(int argc, char* argv[])
{
	dtb_platform_init("Window Title", 800, 600);
	
	while(platform.running)
	{
		dtb_platform_update();

		printf("X: %i, Y: %i\n", platform.cursorX, platform.cursorY);

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	}
	
	return 0;
}