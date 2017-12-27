<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<html>

	<head>
		
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
		<meta name="viewport" content="width=device-width,initial-scale=1.0, minimum-scale=1.0, maximum-scale=1.0, user-scalable=no"/>
		
		<title>${project_name}</title>
		<link rel="stylesheet" href="${pageContext.request.contextPath}/styles/main.css"/>
		<script type="text/javascript" src="${pageContext.request.contextPath}/scripts/jquery-3.2.1.js"></script>
		<script type="text/javascript" src="${pageContext.request.contextPath}/scripts/main.js"></script>
		<script type="text/javascript" src="${pageContext.request.contextPath}/scripts/menu.js"></script>
		<script type="text/javascript" src="${pageContext.request.contextPath}/scripts/form.js"></script>
		<script type="text/javascript">
			$(function() {
				
				init_menu();
				
			});
		</script>
		
	</head>
	
	<body>

		<h1>JSP模板</h1>
		
		<ul id="menu_main" class="menu"></ul>
		<br>
		<ul id="menu_child" class="menu"></ul>
		
		<br><br>
	
	</body>

</html>
