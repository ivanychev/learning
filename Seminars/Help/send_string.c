


#define BUFSIZE 1024
int main()
{
	char buf[BUFSIZE] = {};
	int cond = getline(buf);
	if (cond == -1)
	{
		printf("String reading got failed\n");
		exit(-1);
	}

	

	return 0;
}

//===========================================================================================
//===========================================================================================


int getline(char* buf)
{
	if (buf == 0)
		return -1;

	printf(	"Hello!\n"
			"Please, type a string 256 characters at maximum\n");
	
	gets(buf);
	int temp = 0;

	if ((temp = strlen(buf)) > 256)
	{
		printf("Bad size of string, got %d characters", temp);
		return -1;
	}

	return 0;
}