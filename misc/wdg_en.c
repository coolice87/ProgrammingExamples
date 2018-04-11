#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char buf[32];
	int len;
	int wdg_en = 1;
	int i;

	fd = open("/proc/gs/wdg_en", O_RDONLY);
	if(fd <= 0)
	{
		printf("open %s failed\n");
		return -1;
	}
	
	len = read(fd, buf, sizeof(buf));
	printf("len:%d, buf:%s\n", len, buf);
	if(len > 0)
	{
		for(i=0; i<len; i++)
		{
			if(buf[i]>='0' && buf[i]<='9')
				break;	
		}
	}

	wdg_en = buf[i] - '0' ? 1 : 0;
	printf("buf:%c, wdg_en:%d\n", buf[i], wdg_en);

	return 0;
}
