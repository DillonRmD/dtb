#include "dtb_math.h"

int main(int argc, char* argv[])
{
	
	m4 view = Perspective(90.f, 800.f / 600.f, 0.1f, 100.f);
	m4 model = M4d(1.0f);
	m4 projection = M4d(1.0f);
	
	m4 mvp = view * model + projection;
	
	return 0;
}