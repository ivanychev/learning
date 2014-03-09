/**
		@file				main.c
		@mainpage
		@author				Ivanychev Sergey, DCAM MIPT, 376 group
		@version			1.01
		@par				Changelog V 1.01
							- There are lots of improvements in this version
							- Used fgetc instead getc, performance increased
							- Two new functions: input_analyse and input_scan are able to analyse and scan only meaning strings and chars
							  of the text. For example:

							  [ - begin of text, ] - end of text

							  [                      \n] <- meaningless string
							  [                \n              \n     \n] - meaningless fragment of text
							  [Hey, Jude             don't be afraid]
							                ^^^ - meaningless chars

							  [Sail to the moon            \n]
							                       ^^^ - meaningless chars
							  So now my program sorts the rubbish out of the text
							 - If there are the same strings, program prints only one
							 - Codestyle enchantments
							 - Structure of code enchantments
							 - New code separator. It's nice

		@par				Changelog V 1.01.1
							- verifications added

		@par				Program requires file input.txt, where the buffer text is located. It creates for it a special memory area.

							MEMORY AREA  == [Pointers to string begins, which are sorted in string ascending order][Strings of text]

							Program scans the input text, creates the pointers to each string, sorts it and prints in dictionary.txt file
**/

#include "Pushkin.h"


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int main()
{

	FILE* fi = fopen("input.txt", "r");
	FILE* fo = fopen("dictionary.txt", "w");
	assert(fi);
	assert(fo);

	text *onegin = (text*) calloc(1, sizeof(text)); 
	assert(onegin);
	int ret = get_text(fi, onegin);

	if (ret == -1)
	{
		printf("Text scanning failed\n");
		return 0;
	}

	string_heapsort(onegin -> str_pointers, onegin -> str_amount, stricmp);

	char** last_printed_string = NULL;

	for (int i = onegin -> str_amount - 1; i >= 0; --i) 
		{
			if ((last_printed_string != NULL) && (stricmp(*(last_printed_string), *(onegin -> str_pointers + i)) == 0))
				continue;
			fprintf(fo, "%s\n", *(onegin -> str_pointers + i));
			last_printed_string = onegin -> str_pointers + i;
		}
	
	free(onegin -> str_pointers);
	onegin -> str_pointers = NULL;
	free(onegin);
	onegin = NULL;

	fclose(fi);
	fclose(fo);
	return 0;
}


