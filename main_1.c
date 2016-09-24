#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<pwd.h>
#include<unistd.h>

#define BUFFSIZE 256
char pathname[256];

void read_profile(char **profile)                                   //读取profile将每一行存入profile中
{
	static const char profile_path[]="/home/test/profile";      //profile路径
	FILE *file =fopen(profile_path,"r");
	if(file!=NULL)
	{
		char line[128];
		int i=0;
		while(fgets(line,sizeof(line),file)!=NULL)
		{
			profile[i]=(char *)(malloc(sizeof(line)));
			strcpy(profile[i],line);
			i++;
		}
		fclose(file);
	}
	else
		perror(profile_path);
}

char * get_info(char ** profile, char * name)                     //根据name在profile中查找value
{
	char * info = NULL;
	char ** line = profile;
	while (*line)
	{
		char * info_name;
		char * info_value;	
		char *c = *line;
		int i = 0;
		while (c++)
		{
			i++;
			if (*c == '=')
			{
				info_name= (char *) malloc((i + 1) * sizeof(char));
				strncpy(info_name, *line, counter);
				info_name[i] = '\0';

				info_value = (char *) malloc(strlen(c) - 1);
				strncpy(info_value, c + 1, strlen(c) - 1);
				info_value[strlen(c) - 2] = '\0';

		        break;
			}
		}
		if (info_name != NULL)
		{
			if (strcmp(info_name, name) == 0)
			{
				info = info_value;
				return info;
			}
			else
			{
				line++;
				continue;
			}
		}
		else
			break;
	}
	return NULL;
}

void handler_exit(int signal)                                 //ctrl-c退出
{
	char exit_1[256];
	printf("\n");
	while(1)
	{
		printf("Are you sure? ");
		scanf("%s", exit_1);
		if(strcmp(exit_1,"yes")==0)
			exit(0);
		else if (strcmp(exit_1,"no")==0)
			break;
	}
	
}

void init_home(char *profile)                                 //初始化home
{
	char *path=get_info(profile,"HOME");
	if(chdir(path)!=0)
		perror("fail to init");
}

void type_prompt(char *profile)                             //提示符输出
{
	struct passwd *user;
	char *prompt=get_info(profile,"SIGN");
	printf("%s %s ",getcwd(pathname, sizeof(pathname)/sizeof(char)), prompt));
}


int main()
{
	char command[1024];
	char *profile[BUFFSIZE]

	read_profile(profile);
	signal(SIGINT,handler_exit);
	init_home(profile);

	while(strcmp("exit",command)!=0)
	{
		type_prompt(profile);
		scanf("%s",command);
	}
	return 0;
}