#include "dtb_platform.h"
#include "dtb_gl.h"
#include "dtb_math.h"

int main(int argc, char* argv[])
{
	dtb_platform_init("Window Title", 800, 600);
	
	bool err = dtbgl_init();
	
	float verts[] = 
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f, 0.5f,
	};
	
	uint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	while(platform.running)
	{
		dtb_platform_update();
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		printf("X: %i, Y: %i\n", platform.cursorX, platform.cursorY);
		
	}
	
	return 0;
}