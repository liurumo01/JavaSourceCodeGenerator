#include "parser.h"

int load_project_config(struct project_config *project)
{
	char filename[256];
	FILE *fp;
	int nret;

	snprintf(filename, 256, "etc/%s.project", project->name);
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Open file [%s] failed.\n", filename);
		return ERROR_OPEN_FILE_FAILED;
	}

	fscanf(fp, "%s", project->package);

	project->beans_max_count = 10;
	project->beans = malloc(project->beans_max_count * sizeof(struct bean));
	if (project->beans == NULL)
	{
		printf("Malloc [%lu] bytes failed.\n", project->beans_max_count * sizeof(struct bean));
		return ERROR_MALLOC_FAILED;
	}
	memset(project->beans, 0x00, project->beans_max_count * sizeof(struct bean));

	while (1)
	{
		if (project->beans_count == project->beans_max_count)
		{
			project->beans_max_count *= 2;
			project->beans = realloc(project->beans, project->beans_max_count * sizeof(struct bean));
			if (project->beans == NULL)
			{
				printf("Malloc [%lu] bytes failed.\n", project->beans_max_count * sizeof(struct bean));
				return ERROR_MALLOC_FAILED;
			}
		}
		nret = fscanf(fp, "%s", project->beans[project->beans_count].name);
		if (nret != 1)
		{
			break;
		}
		project->beans_count++;
	}

	printf("%d\n", project->beans_count);

	printf("Load project config file finished.\n");
	fclose(fp);
	return 0;
}

int load_bean_config(struct project_config *project, int i)
{
	char filename[256];
	FILE *fp;
	struct bean *obj;
	int nret;

	obj = &project->beans[i];
	snprintf(filename, 255, "etc/%s.object", project->beans[i].name);

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Open file [%s] failed.\n", filename);
		return ERROR_OPEN_FILE_FAILED;
	}

	obj->field_max_count = 10;
	obj->fields = malloc(obj->field_max_count * sizeof(struct field));
	if (obj->fields == NULL)
	{
		printf("Malloc [%lu] bytes failed.\n", obj->field_max_count * sizeof(struct field));
		return ERROR_MALLOC_FAILED;
	}
	memset(obj->fields, 0x00, obj->field_max_count * sizeof(struct field));

	while (1)
	{
		if (obj->field_count == obj->field_max_count)
		{
			obj->field_max_count *= 2;
			obj->fields = realloc(obj->fields, obj->field_max_count * sizeof(struct field));
			if (obj->fields == NULL)
			{
				return ERROR_MALLOC_FAILED;
			}
		}
		nret = fscanf(fp, " %s %s", obj->fields[obj->field_count].type, obj->fields[obj->field_count].name);
		if (nret != 2)
		{
			break;
		}
		if (strcmp(obj->fields[obj->field_count].type, "Date") == 0)
		{
			obj->import_flag = obj->import_flag | IMPORT_FLAG_DATE;
		}
		obj->field_count++;
	}

	printf("Load bean [%s] config file finished.\n", obj->name);
	return 0;
}

int parse(struct project_config *project)
{
	int i, nret;

	nret = load_project_config(project);
	if (nret)
	{
		printf("Load project [%s] config failed, nret = [%d].\n", project->name, nret);
		return nret;
	}

	for (i = 0; i < project->beans_count; i++)
	{
		nret = load_bean_config(project, i);
		if (nret)
		{
			printf("Load bean [%s] config failed.\n", project->beans[i].name);
			return nret;
		}
	}

	return 0;
}
