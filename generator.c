#include "generator.h"

int generate_bean(struct project_config *project, int index);
int generate_dao(struct project_config *project, int index);
int generate_service(struct project_config *project, int index);

int generate(struct project_config *project)
{
	int i, nret;

	for (i = 0; i < project->beans_count; i++)
	{
		nret = generate_bean(project, i);
		if (nret)
		{
			return ERROR_GENERATE_BEAN_FAILED;
		}

		nret = generate_dao(project, i);
		if (nret)
		{
			return ERROR_GENERATE_DAO_FAILED;
		}

		nret = generate_service(project, i);
		if (nret)
		{
			return ERROR_GENERATE_SERVICE_FAILED;
		}
	}

	return 0;
}

int generate_bean(struct project_config *project, int index)
{
	FILE *fp;
	char filename[512];
	int i;
	struct bean *obj;
	char package_path[256];
	char *p, *q;
	char buffer[256];

	obj = &project->beans[index];

	//0. create package folders
	string_replace(project->package, package_path, ".", "/");
	snprintf(filename, 512, "project/%s/src/main/java/%s/bean", project->name, package_path);
	mkdirs(filename);

	//1.open file
	snprintf(filename, 512, "project/%s/src/main/java/%s/bean/%sBean.java", project->name, package_path, obj->name);
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open file [%s] failed.\n", filename);
		return ERROR_OPEN_FILE_FAILED;
	}

	//2.import
	fprintf(fp, "package %s.bean;\n\n", project->package);
	if (obj->import_flag & IMPORT_FLAG_DATE)
	{
		fprintf(fp, "import java.util.Date;\n");
	}
	fprintf(fp, "\n");
	fprintf(fp, "import javax.persistence.Entity;\n");
	fprintf(fp, "import javax.persistence.GeneratedValue;\n");
	fprintf(fp, "import javax.persistence.Id;\n");
	fprintf(fp, "import javax.persistence.Table;\n");
	fprintf(fp, "\n");

	//3.class name
	fprintf(fp, "@Entity\n");
	fprintf(fp, "@Table\n");
	fprintf(fp, "public class %sBean {\n\n", obj->name);

	//4.fields
	for (i = 0; i < obj->field_count; i++)
	{
		fprintf(fp, "\tprivate %s %s;\r\n", obj->fields[i].type, obj->fields[i].name);
	}
	fprintf(fp, "\n");

	//5.getters and setters
	for (i = 0; i < obj->field_count; i++)
	{
		if (strcmp(obj->fields[i].name, "id") == 0)
		{
			fprintf(fp, "\t@Id\n");
			fprintf(fp, "\t@GeneratedValue\n");
		}
		fprintf(fp, "\tpublic %s get%s() {\n", obj->fields[i].type, string_first_char_to_upper_case(obj->fields[i].name, buffer));
		fprintf(fp, "\t\treturn %s;\n", obj->fields[i].name);
		fprintf(fp, "\t}\n\n");

		fprintf(fp, "\tpublic void set%s(%s %s) {\n",
			string_first_char_to_upper_case(obj->fields[i].name, buffer),
			obj->fields[i].type,
			obj->fields[i].name);
		fprintf(fp, "\t\tthis.%s = %s;\n", obj->fields[i].name, obj->fields[i].name);
		fprintf(fp, "\t}\n\n");
	}

	//6.end of class
	fprintf(fp, "}\n");

	fclose(fp);
	printf("Generate source code of bean [%s] finished.\n", obj->name);
	return 0;
}

int generate_dao(struct project_config *project, int index)
{
	FILE *fp;
	char filename[256];
	char package_path[256];
	struct bean *obj;

	obj = &project->beans[index];

	//0. create package folders
	string_replace(project->package, package_path, ".", "/");
	snprintf(filename, 256, "project/%s/src/main/java/%s/dao", project->name, package_path);
	mkdirs(filename);

	//1.open file
	snprintf(filename, 512, "project/%s/src/main/java/%s/dao/%sDAO.java", project->name, package_path, obj->name);
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open file [%s], failed.\n", filename);
		return ERROR_OPEN_FILE_FAILED;
	}

	//2.import
	fprintf(fp, "package %s.dao;\n\n", project->package);
	fprintf(fp, "import org.springframework.data.jpa.repository.JpaRepository;\n");
	fprintf(fp, "import org.springframework.stereotype.Repository;\n");
	fprintf(fp, "\n");
	fprintf(fp, "import %s.bean.%sBean;\n", project->package, obj->name);
	fprintf(fp, "\n");

	//3.class name
	fprintf(fp, "@Repository\n");
	fprintf(fp, "public interface %sDAO extends JpaRepository<%sBean, Long> {\n", obj->name, obj->name);

	//4.end of class
	fprintf(fp, "\n}\n");

	fclose(fp);
	printf("Generate source code of dao [%s] finished.\n", obj->name);
	return 0;
}

int generate_service(struct project_config *project, int index)
{
	FILE *fp;
	char filename[256];
	char package_path[256];
	char var[256];
	struct bean *obj;

	obj = &project->beans[index];
	string_first_char_to_lower_case(obj->name, var);

	//0. create package folders
	string_replace(project->package, package_path, ".", "/");
	snprintf(filename, 256, "project/%s/src/main/java/%s/service", project->name, package_path);
	mkdirs(filename);

	//1.open file
	snprintf(filename, 512, "project/%s/src/main/java/%s/service/%sService.java", project->name, package_path, obj->name);
	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open file [%s], failed.\n", filename);
		return ERROR_OPEN_FILE_FAILED;
	}

	//2.import
	fprintf(fp, "package %s.service;\n\n", project->package);
	fprintf(fp, "import java.util.List;\n");
	fprintf(fp, "\n");
	fprintf(fp, "import org.springframework.beans.factory.annotation.Autowired;\n");
	fprintf(fp, "import org.springframework.stereotype.Service;\n");
	fprintf(fp, "\n");
	fprintf(fp, "import %s.bean.%sBean;\n", project->package, obj->name);
	fprintf(fp, "import %s.dao.%sDAO;\n", project->package, obj->name);
	fprintf(fp, "\n");

	//3.class name
	fprintf(fp, "@Service\n");
	fprintf(fp, "public class %sService {\n\n", obj->name);

	//4. Autowired DAO
	fprintf(fp, "\t@Autowired\n");
	fprintf(fp, "\tprivate %sDAO %sDAO;\n", obj->name, var);
	fprintf(fp, "\n");

	//4.CURD methods

	//4.1 add
	fprintf(fp, "\tpublic void add(%sBean %s) {\n", obj->name, var);
	fprintf(fp, "\t\t%sDAO.save(%s);\n", var, var);
	fprintf(fp, "\t}\n");
	fprintf(fp, "\n");

	//4.2.1 delete
	fprintf(fp, "\tpublic void delete(%sBean %s) {\n", obj->name, var);
	fprintf(fp, "\t\t%sDAO.delete(%s);\n", var, var);
	fprintf(fp, "\t}\n");
	fprintf(fp, "\n");

	//4.2.1 delete by id
	fprintf(fp, "\tpublic void delete(Long id) {\n");
	fprintf(fp, "\t\t%sDAO.deleteById(id);\n", var);
	fprintf(fp, "\t}\n");
	fprintf(fp, "\n");

	//4.3 update
	fprintf(fp, "\tpublic void update(%sBean %s) {\n", obj->name, var);
	fprintf(fp, "\t\t%sDAO.save(%s);\n", var, var);
	fprintf(fp, "\t}\n");
	fprintf(fp, "\n");

	//4.4.1 get by id
	fprintf(fp, "\tpublic %sBean get(Long id) {\n", obj->name);
	fprintf(fp, "\t\treturn %sDAO.findById(id).orElse(null);\n", var);
	fprintf(fp, "\t}\n");
	fprintf(fp, "\n");

	//4.4.2 get all
	fprintf(fp, "\tpublic List<%sBean> get() {\n", obj->name);
	fprintf(fp, "\t\treturn %sDAO.findAll();\n", var);
	fprintf(fp, "\t}\n");

	//5.end of class
	fprintf(fp, "\n}\n");

	fclose(fp);
	printf("Generate source code of service [%s] finished.\n", obj->name);
	return 0;
}
