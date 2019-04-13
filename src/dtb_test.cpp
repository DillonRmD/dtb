#include "dtb_platform.h"
#include "dtb_gl.h"
#include "dtb_math.h"

// TODO(DILLON): REMOVE SHADER FILE LOADING

circle draw_circle(float cx, float cy, float r, int num_segments)
{
	circle res = {0};
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < num_segments; i++)
	{
		float theta = TWO_PI * float(i) / float(num_segments);
		
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
	
	
	res.radius = r;
	res.x = cx;
	res.y = cy;
	
	return res;
}

int main(int argc, char* argv[])
{
	dtb_platform_init("Window Title", 800, 600);
	
	bool err = dtbgl_init();
	
	
	dtbgl_setup_view_2d(800, 600, true);
	glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
	while(platform.running)
	{
		dtb_platform_update();
		
		
		//circle c1 = draw_circle(platform.cursorX, platform.cursorY, 50, 25);
		circle c2 = draw_circle(500, 400, 75, 25);
		
		/*
  if(IsCircleColliding(c1, c2))
  {
   glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
  }
  else
  {
   glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
  }
  */
		
		if(IsCirclePointColliding(platform.cursorX, platform.cursorY, c2))
		{
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}
	return 0;
}