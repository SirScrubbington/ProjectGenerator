#ifndef PROJECT_GENERATOR_C
#define PROJECT_GENERATOR_C

#include "ProjectGenerator.h"

void hashFunc(int len, char * str)
{
	str[0]='I';
	str[1]='_';
	for(int i=2;i<len-1;i++)
	{
		str[i]=getRandomASCII(rand()%3);
	}
	str[len]='\0';
}

char getRandomASCII(int type)
{
	switch(type)
	{
		case 0: return (char)(rand()%('9'-'0')+'0'); break;
		case 1: return (char)(rand()%('Z'-'A')+'A'); break;
		case 2: return (char)(rand()%('z'-'a')+'a'); break;
		default: return 0; break;
	}
}

int main(int argc, char ** argv, char ** envp)
{
	
	if(argc > 1)
	{
		srand(time(NULL));
		
		char accept=0;
		
		int createMakefile=0,forceReplace=0;
	
		char filename[MAX_FILENAME_LEN],
			 projectname[MAX_FILENAME_LEN],
			 username[MAX_FILENAME_LEN],
			 datetime[MAX_FILENAME_LEN];
		
		// Get System Username
		getlogin_r(username,MAX_FILENAME_LEN);
		
		// Get System Date
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		
		strcpy(projectname,argv[1]);
		
		for(int i=1;i<argc;i++)
		{
			if(strcmp(argv[i],"-f")==0)forceReplace=1;
			if(strcmp(argv[i],"-m")==0)createMakefile=1;
		}
		
		struct stat st = {0};
		
		strcpy(filename,projectname);
		strcat(filename,".h");
		
		FILE * f = fopen(filename,"r");
		
		if(f)
		{
			
			char replace=0;
			if(forceReplace)
			{
				replace=1;
			}
			
			else
			{	
				accept=0;
				while(!(accept == 'y' || accept == 'n'))
				{
					printf("Overwrite existing file '%s'? :",filename);
					accept = getchar();
					switch(accept)
					{
						case 'y': replace=1; break;
						case 'n': replace=0; break;
					}
					printf("\n");
				}
				while ( (accept = getchar()) != '\n' && accept != EOF ) { }
			}
			
			if (replace)
			{
				freopen(filename,"w",f);
			}
		}
		
		else
		{
			f = fopen(filename,"w");
		}
		
		if(f)
		{
			char hash[HASH_LEN];
			strcpy(hash,"");
			hashFunc(HASH_LEN,hash);
			
			fprintf(f,"// Filename: %s\n",filename);
			fprintf(f,"// Author: %s\n",username);
			fprintf(f,"// Date: %d-%d-%d\n",tm.tm_year+ 1900,tm.tm_mon + 1,tm.tm_mday);
			fprintf(f,"// Description: %s header file\n\n",projectname);
			
			fprintf(f,"#ifndef %s\n",hash);
			fprintf(f,"#define %s\n\n",hash);
			
			fprintf(f,"#endif // %s\n",hash);
		}
		
		strcpy(filename,projectname);
		strcat(filename,".cpp");
		
		if(f)
			fclose(f);
		
		f = fopen(filename,"r");
		
		if(f)
		{
			char replace=0;
			if(forceReplace)
			{
				replace=1;
			}
			
			else
			{	
				accept=0;
				while(!(accept == 'y' || accept == 'n'))
				{
					printf("Overwrite existing file '%s'? :",filename);
					accept = getchar();
					switch(accept)
					{
						case 'y': replace=1; break;
						case 'n': replace=0; break;
					}
					printf("\n");
				}
				while ( (accept = getchar()) != '\n' && accept != EOF ) { }
			}
			
			if (replace)
			{
				freopen(filename,"w",f);
			}
		}
		else
		{
			f = fopen(filename,"w");
		}
		
		if(f)
		{
			char hash[HASH_LEN];
			strcpy(hash,"");
			hashFunc(HASH_LEN,hash);
			
			fprintf(f,"// Filename: %s\n",filename);
			fprintf(f,"// Author: %s\n",username);
			fprintf(f,"// Date: %d-%d-%d\n",tm.tm_year+ 1900,tm.tm_mon + 1,tm.tm_mday);
			fprintf(f,"// Description: %s implementation file\n\n",projectname);
			
			fprintf(f,"#ifndef %s\n",hash);
			fprintf(f,"#define %s\n\n",hash);
			
			fprintf(f,"#include \"%s.h\"\n\n",projectname);
			
			fprintf(f,"int main(int argc, char ** argv, char ** envp)\n{\n\n");
			
			fprintf(f,"	return 0;\n");
			fprintf(f,"}\n\n");
			
			fprintf(f,"#endif // %s\n",hash);
		}
		
		if(createMakefile)
		{
			strcpy(filename,"Makefile");
		
			if(f)
				fclose(f);
			
			f = fopen(filename,"r");
			
			if(f)
			{
				char replace=0;
				if(forceReplace)
				{
					replace=1;
				}
				
				else
				{	
					accept=0;
					while(!(accept == 'y' || accept == 'n'))
					{
						printf("Overwrite existing file '%s'? :",filename);
						accept = getchar();
						switch(accept)
						{
							case 'y': replace=1; break;
							case 'n': replace=0; break;
						}
						printf("\n");
					}
					while ( (accept = getchar()) != '\n' && accept != EOF ) { }
				}
				
				if (replace)
				{
					freopen(filename,"w",f);
				}
			}
			else
			{
				f = fopen(filename,"w");
			}
			
			if(f)
			{
				char hash[HASH_LEN];
				strcpy(hash,"");
				hashFunc(HASH_LEN,hash);
				fprintf(f,"# Filename: %s\n",filename);
				fprintf(f,"# Author: %s\n",username);
				fprintf(f,"# Date: %d-%d-%d\n",tm.tm_year+ 1900,tm.tm_mon + 1,tm.tm_mday);
				fprintf(f,"# Description: %s Makefile\n\n",projectname);
				
				fprintf(f,"all: %s\n\n",projectname);
				
				fprintf(f,"pgen:\n	gcc -o %s %s.cpp\n\n",projectname,projectname);
				
				fprintf(f,"clean:\n	rm *.o");
			}
			
			
		}
	}
	else
		printf("Usage: ./a.exe projectname [-f] [-m]\n");
	return 0;
}

#endif // PROJECT_GENERATOR_C