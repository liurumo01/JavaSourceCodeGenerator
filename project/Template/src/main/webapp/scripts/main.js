$(function() {

//	$(document).bind("contextmenu", function(e) {
//		return false;
//	});

//	$(document).bind("selectstart", function() {
//		return false;
//	});

	$(document).bind("keydown", function(event) {
		if (event.keyCode == 13) {
			$(".submit").click();
			return false;
		};
		return true;
	});

	$('a.back').click(function() {
		var uri = window.location.pathname;
		uri = uri.substring(0, uri.lastIndexOf('/'));
		location.href = uri;
	});

})

function post(url, args, callback) {
	$.post(url, args, function(data) {
		var result = eval(data);
		if (callback) {
			callback(result);
		}
	});
}

function getObjectFromGrid(dom) {
	var obj = {};
	var arr = [];
	if($(dom).is('input:checkbox')) {
		var tr = $(dom).parent().parent();
		arr = tr.find('input');
	} else if($(dom).is('table')) {
		arr = $(dom).find('input,select');
	}
	$(arr).each(function(index, item) {
		obj[$(item).attr('name')] = $(item).val();
	})
	return obj;
}

function setObjectToGrid(obj, table) {
	if($(table).is('table')) {
		$.each(obj, function(index, item) {
			$(table).find('input[name=' + index + ']').val(item);
		});
	}
}

function getContextPath() {
	var contextPath = location.pathname;
	contextPath = contextPath.substring(1);
	contextPath = '/' + contextPath.substring(0, contextPath.indexOf('/'));
	return contextPath;
}
