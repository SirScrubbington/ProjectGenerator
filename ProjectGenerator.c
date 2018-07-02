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
		
		//char createC = 0, createCPP = 0, createH = 0, createMain = 0, createMakefile = 0, forceReplace = 0;

		unsigned char properties = 0;
		
		char filename[MAX_FILENAME_LEN],
			 projectname[MAX_FILENAME_LEN],
			 username[MAX_FILENAME_LEN],
			 datetime[MAX_FILENAME_LEN];
		
		// Get System Username
		
		#ifdef _WIN32
			DWORD username_len = MAX_FILENAME_LEN;
			GetUserName(username,&username_len);
		#else
			getlogin_r(username,MAX_FILENAME_LEN);
		#endif
		
		// Get System Date
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		
		strcpy(projectname,argv[1]);
		
		int nfiles=0;
		int files[MAX_FILES];

		for(int i=1;i<argc;i++)
		{
			if(strcmp(argv[i],"-c")==0) properties |= CREATE_C;
			else 
				if(strcmp(argv[i],"-h")==0) properties |= CREATE_H;
			else 
				if(strcmp(argv[i],"-f")==0) properties |= FORCE_REPLACE;
			else 
				if(strcmp(argv[i],"-m")==0) properties |= CREATE_MAKE;
			else 
				if(strcmp(argv[i],"-i")==0) properties |= CREATE_MAIN;
			else
				if(strcmp(argv[i],"-cpp")==0) properties |= CREATE_CPP;
			else
				files[nfiles++]=i;
		}
		
		printf("%i\n",properties);
		
		struct stat st = {0};
		
		FILE * f;
		
		for(int x = 0; x < nfiles; x++){
			
			if(properties & CREATE_H)
			{
				
				strcpy(filename,argv[files[x]]);
				strcat(filename,".h");
				
				f = fopen(filename,"r");
				
				if(f)
				{
					char replace = 0;

					if(properties & FORCE_REPLACE)
						replace = 1;
					
					if(replace)
						freopen(filename,"w",f);
				}
				else
					f = fopen(filename,"w");
				
				if(f)
				{
					char hash[HASH_LEN];
					strcpy(hash,"");
					hashFunc(HASH_LEN,hash);
					
					fprintf(f,"// Filename: %s\n",filename);
					fprintf(f,"// Author: %s\n",username);
					fprintf(f,"// Date: %d-%d-%d\n",tm.tm_year+ 1900,tm.tm_mon + 1,tm.tm_mday);
					fprintf(f,"// Description: %s header file\n\n",filename);
					
					fprintf(f,"#ifndef %s\n",hash);
					fprintf(f,"#define %s\n\n",hash);
					
					if(x==0)
						for(int y=1;y<nfiles;y++)
							fprintf(f,"#include \"%s.h\"\n",argv[files[y]]);
					fprintf(f,"\n");
					
					fprintf(f,"#endif // %s\n",hash);
				}	
			}
			
			if(properties & CREATE_CPP){
				
				strcpy(filename,argv[files[x]]);
				strcat(filename,".cpp");
				
				if(f)
				fclose(f);
			
				f = fopen(filename,"r");
				
				if(f)
				{
					char replace = 0;

					if(properties & FORCE_REPLACE)
						replace = 1;
					
					if(replace)
						freopen(filename,"w",f);
				}
				else
					f = fopen(filename,"w");
				
				if(f)
				{
					char hash[HASH_LEN];
					strcpy(hash,"");
					hashFunc(HASH_LEN,hash);
					
					fprintf(f,"// Filename: %s\n",filename);
					fprintf(f,"// Author: %s\n",username);
					fprintf(f,"// Date: %d-%d-%d\n",tm.tm_year+ 1900,tm.tm_mon + 1,tm.tm_mday);
					fprintf(f,"// Description: %s implementation file\n\n",argv[files[x]]);
					
					fprintf(f,"#ifndef %s\n",hash);
					fprintf(f,"#define %s\n\n",hash);
					
					if(properties & CREATE_H)
						fprintf(f,"#include \"%s.h\"\n\n",argv[files[x]]);
					
					
					if(properties & CREATE_MAIN && x==0){
						fprintf(f,"int main(int argc, char ** argv, char ** envp)\n{\n\n");
					
						fprintf(f,"	return 0;\n");
						fprintf(f,"}\n\n");
					}
					fprintf(f,"#endif // %s\n",hash);
				}	
			}
			
			if(properties & CREATE_C){
				
				strcpy(filename,argv[files[x]]);
				strcat(filename,".c");
				
				if(f)
				fclose(f);
			
				f = fopen(filename,"r");
				
				if(f)
				{
					char replace = 0;

					if(properties & FORCE_REPLACE)
						replace = 1;
					
					if(replace)
						freopen(filename,"w",f);
				}
				else
					f = fopen(filename,"w");
				
				if(f)
				{
					char hash[HASH_LEN];
					strcpy(hash,"");
					hashFunc(HASH_LEN,hash);
					
					fprintf(f,"// Filename: %s\n",filename);
					fprintf(f,"// Author: %s\n",username);
					fprintf(f,"// Date: %d-%d-%d\n",tm.tm_year+ 1900,tm.tm_mon + 1,tm.tm_mday);
					fprintf(f,"// Description: %s implementation file\n\n",argv[files[x]]);
					
					fprintf(f,"#ifndef %s\n",hash);
					fprintf(f,"#define %s\n\n",hash);
					
					if(properties & CREATE_H)
						fprintf(f,"#include \"%s.h\"\n\n",argv[files[x]]);
					
					
					if((properties & CREATE_MAIN) && x==0)
					{
						fprintf(f,"int main(int argc, char ** argv, char ** envp)\n{\n\n");
					
						fprintf(f,"	return 0;\n");
						fprintf(f,"}\n\n");
					}

					fprintf(f,"#endif // %s\n",hash);
				}	
			}
		}
		
		printf("%i\n",properties & CREATE_MAKE);
		
		if(properties & CREATE_MAKE)
		{
			printf("Makefile...\n");
			strcpy(filename,"Makefile");
		
			if(f)
				fclose(f);
			
			f = fopen(filename,"r");
		
			if(f)
			{
				char replace = 0;

				if(properties & FORCE_REPLACE)
					replace = 1;
					
				if(replace)
					freopen(filename,"w",f);
			}
			else
				f = fopen(filename,"w");
			
			if(f)
			{
				
				char hash[HASH_LEN];
				strcpy(hash,"");
				hashFunc(HASH_LEN,hash);
				
				fprintf(f,"# Filename: %s\n",filename);
				fprintf(f,"# Author: %s\n",username);
				fprintf(f,"# Date: %d-%d-%d\n",tm.tm_year+ 1900,tm.tm_mon + 1,tm.tm_mday);
				fprintf(f,"# Description: %s Makefile\n\n",projectname);
				
				fprintf(f,"#Project Name (executable)\nPROJECT = %s\n\n",projectname);
				
				fprintf(f,"#Compiler\nCXX = g++\n\n");
				
				fprintf(f,"#Compiler Directions\nCXXFLAGS=\n\n");
				
				fprintf(f,"#Source Files\nSOURCE = $(wildcard *.c *.cpp)\n\n");
				
				fprintf(f,"#Object Files\nOBJECTS = $(SOURCE:.cpp=.o)\n\n");
				
				fprintf(f,"#Libraries\nLIBDIR=lib\nLIBRARIES = $(wildcard .lib .a $(LIBDIR)/*.a $(LIBDIR)/*.lib)\n\n");
				
				fprintf(f,"#Build Executable\n$(PROJECT): $(OBJECTS)\n\t$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBRARIES) \n\n");
				
				fprintf(f,"#Clean up additional files\n.PHONY: clean\nclean:\n\trm -f $(OBJECT) $(PROJECT)");
			}
		}
	}
	else
		printf("Usage: pgen projectname [subfile(s)] [-f] [-m] [-h] [-c] [-l] \n");
	return 0;
}

#endif // PROJECT_GENERATOR_C