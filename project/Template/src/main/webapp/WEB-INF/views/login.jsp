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
				$('#button_login').click(function() {
					var url = '${pageContext.request.contextPath}/user/login.action';
					var args = get_form_data('form_login');
					post(url, args, function(result) {
						if(result.code == 0) {
							location.href = '${pageContext.request.contextPath}/';
						} else {
							alert(result.text);
						}
					});
				});
				$('#button_register').click(function() {
					location.href = '${pageContext.request.contextPath}/register';
				});
			});
		</script>
		
	</head>
	
	<body>

		<h1>用户登录</h1>
		<form id="form_login">
			<table>
				<tr>
					<td>用户名</td>
					<td><input type="text" name="username"/></td>
				</tr>
				<tr>
					<td>密码</td>
					<td><input type="password" name="password"/></td>
				</tr>
				<tr>
					<td colspan="2">
						<a id="button_login">登录</a>
						<a id="button_register">注册</a>
					</td>
				</tr>
			</table>
		</form>
	
	</body>

</html>
