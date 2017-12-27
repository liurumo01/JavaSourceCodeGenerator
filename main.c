#include <dirent.h>

#include "common.h"
#include "string_utils.h"
#include "file_utils.h"

#include "parser.h"
#include "generator.h"

int PARAMETERED_FILE_COUNT = 9;

char *PARAMETERED_FILE[] = {
	"project/%s/pom.xml",
	"project/%s/.project",
	"project/%s/.classpath",
	"project/%s/.settings/org.eclipse.wst.common.component",
	"project/%s/src/main/resources/spring.xml",
	"project/%s/src/main/webapp/WEB-INF/springmvc-servlet.xml",
	"project/%s/src/main/webapp/WEB-INF/views/template.jsp",
	"project/%s/src/main/webapp/WEB-INF/views/login.jsp",
	"project/%s/src/main/webapp/WEB-INF/views/register.jsp"
};

int prepare(struct project_config *project)
{
	int i, nret;
	char *content;
	char cmd[512], filename[256];
	char buffer_1[65536], buffer_2[65536];

	//1. remove existed project folder
	snprintf(cmd, 512, "rm -rf project/%s", project->name);
	nret = system(cmd);
	if (nret)
	{
		printf("Execute command [%s] failed, nret = [%d].\n", cmd, nret);
		return ERROR_EXECUTE_COMMAND_FAILED;
	}

	//2. copy template folder and named with project name
	snprintf(cmd, 512, "cp -r project/Template/ project/%s", project->name);
	nret = system(cmd);
	if (nret)
	{
		printf("Execute command [%s] failed, nret = [%d].\n", cmd, nret);
		return ERROR_EXECUTE_COMMAND_FAILED;
	}

	//3. replace project parameters
	for (i = 0; i < PARAMETERED_FILE_COUNT; i++)
	{
		snprintf(filename, 256, PARAMETERED_FILE[i], project->name);
		read_file(filename, &content);
		string_replace(content, buffer_1, "${project_name}", project->name);
		string_replace(buffer_1, buffer_2, "${base_package}", project->package);
		write_file(filename, buffer_2, strlen(buffer_2));
		free(content);
	}
}

int main(int argc, char **argv)
{
	int i;
	struct project_config project;

	for (i = 1; i < argc; i++)
	{
		memset(&project, 0x00, sizeof(struct project_config));
		strncpy(project.name, argv[i], 256);

		parse(&project);
		prepare(&project);
		generate(&project);
	}

	return 0;
}
