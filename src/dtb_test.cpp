#include "dtb_platform.h"
#include "dtb_gl.h"
#include "dtb_math.h"

void render_cube(v3 center_position, float edge_length, bool wire_frame_mode)
{
	float half_side_length = edge_length * 0.5f;
	
	float vertices[] =
	{
		//front face
		center_position.x - half_side_length, center_position.y + half_side_length, center_position.z + half_side_length,
		center_position.x + half_side_length, center_position.y + half_side_length, center_position.z + half_side_length,
		center_position.x + half_side_length, center_position.y - half_side_length, center_position.z + half_side_length,
		center_position.x - half_side_length, center_position.y - half_side_length, center_position.z + half_side_length,
		
		//back face
		center_position.x - half_side_length, center_position.y + half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y + half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y - half_side_length, center_position.z - half_side_length,
		center_position.x - half_side_length, center_position.y - half_side_length, center_position.z - half_side_length,
		
		//left face
		center_position.x - half_side_length, center_position.y + half_side_length, center_position.z + half_side_length,
		center_position.x - half_side_length, center_position.y + half_side_length, center_position.z - half_side_length,
		center_position.x - half_side_length, center_position.y - half_side_length, center_position.z - half_side_length,
		center_position.x - half_side_length, center_position.y - half_side_length, center_position.z + half_side_length,
		
		// right face
		center_position.x + half_side_length, center_position.y + half_side_length, center_position.z + half_side_length,
		center_position.x + half_side_length, center_position.y + half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y - half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y - half_side_length, center_position.z + half_side_length,
		
		// top face
		center_position.x - half_side_length, center_position.y + half_side_length, center_position.z + half_side_length,
		center_position.x - half_side_length, center_position.y + half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y + half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y + half_side_length, center_position.z + half_side_length,
		
		// bottom face
		center_position.x - half_side_length, center_position.y - half_side_length, center_position.z + half_side_length,
		center_position.x - half_side_length, center_position.y - half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y - half_side_length, center_position.z - half_side_length,
		center_position.x + half_side_length, center_position.y - half_side_length, center_position.z + half_side_length,
	};
	
	if (wire_frame_mode == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_QUADS, 0, 24);
	glDisableClientState(GL_VERTEX_ARRAY);
}

int main(int argc, char* argv[])
{
	dtb_platform_init("Window Title", 800, 600);
	
	bool err = dtbgl_init(dtbgl_win32_grab_gl_address);
	
	float HalfScreenWidth = 400;
	float HalfScreenHeight = 300;
	
	float RotateX;
	float RotateY;
	
	while(platform.running)
	{
		dtb_platform_update();
		
		
		glPushMatrix();
		glTranslatef(HalfScreenWidth, HalfScreenHeight, -500);
		//glRotatef(RotateX, 1, 0, 0);
		//glRotatef(RotateY, 0, 1, 0);
		glTranslatef(-HalfScreenWidth, -HalfScreenHeight, 500);
		
		
		render_cube(V3(400.f, 300.f, -500.f), 450, true);
		
		printf("X: %i, Y: %i\n", platform.cursorX, platform.cursorY);
		
	}
	
	return 0;
}