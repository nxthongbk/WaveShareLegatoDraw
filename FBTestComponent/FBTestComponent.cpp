#include "legato.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <errno.h>
#include <ctype.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "paint.h"


#define COLORED      0
#define UNCOLORED    1


COMPONENT_INIT
{
	int fd;
	int screensize, row_size;
	int width,height;

	fd = open("/dev/fb0", O_RDWR);
	if (fd == -1) {

		LE_INFO("Error: cannot open framebuffer device");
		exit(0);
	}

	struct fb_var_screeninfo vinfo;

	if(ioctl(fd, FBIOGET_VSCREENINFO, &vinfo)== -1) {
		perror("Error reading variable information");
		exit (-1);
	}

	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel /8;
	row_size = vinfo.xres * vinfo.bits_per_pixel /8;

	width = vinfo.xres;
	height= vinfo.yres * vinfo.bits_per_pixel /8;

	LE_INFO("screen size is:%d",screensize);
	LE_INFO("Row size is:%d",row_size);

	unsigned char *fbp;
	fbp = (unsigned char *)mmap(0,screensize,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);

	if((int)fbp == -1)
	{
		exit(4);
		LE_INFO("Fail to map FrameBuffer device to memory");
	}
	LE_INFO("The FrameBuffer device was mapped to memory successfully\n");


	unsigned char* frame_buffer = (unsigned char*)malloc(width * height);

	Paint paint(frame_buffer, 0, 0);

	paint.SetWidth(128);
	paint.SetHeight(250);

	paint.Clear(UNCOLORED);

	paint.DrawStringAt(0, 4, "TEMP", &Font24, COLORED);

	paint.DrawStringAt(30, 150, "124", &Font24, COLORED);


	for(int cnt = 0;cnt < screensize;cnt++)
	{
			*(fbp+cnt)=*(frame_buffer+cnt);
	}

	munmap(fbp, screensize);
	close(fd);
}
