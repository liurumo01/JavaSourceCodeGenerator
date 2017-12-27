function list_init(options) {

	if(!options.target) {
		return false;
	}

	$('div.info').hide();

	$('a#button_add').click(function() {
		$('div.info table tr.id').hide();
		$('div.info a.submit').text('增加');
		$('div.info').show();
	});

	$('a#button_delete').click(function() {

		var ids = [];
		$('input:checkbox[name=id]:checked').each(function(index, item) {
			ids.push($(item).val());
		});

		if(ids.length == 0) {
			alert('未选中任何内容');
			return false;
		}

		if(!confirm('确定要删除选中的' + ids.length + '项内容吗')) {
			return false;
		}

		var url = getContextPath() + '/' + options.target + '/delete.action';
		var args = {
			ids : ids
		};
		post(url, args, function(result) {
			if(result.code == 0) {
				location.reload();
			} else {
				alert(result.text);
			}
		});

	});

	$('a#button_update').click(function() {

		var arr = $('input:checkbox[name=id]:checked');

		if(arr.length == 0) {
			alert('未选中任何内容');
			return false;
		}

		if(arr.length > 1) {
			alert('最多只能选中1项');
			return false;
		}

		var obj = getObjectFromGrid(arr[0]);
		setObjectToGrid(obj, $('div.info table'));
		$('div.info table tr.id').show();
		$('div.info a.submit').text('修改');
		$('div.info').show();

	});

	$('div.info a.submit').click(function() {
		var url = null;
		var obj = getObjectFromGrid($('div.info table'));
		if($(this).text() == '增加') {
			url = getContextPath() + '/' + options.target + '/add.action';
		} else if($(this).text() == '修改') {
			url = getContextPath() + '/' + options.target + '/update.action';
		} else {
			return false;
		}

		if(options.validation && !options.validation(obj)) {
			return false;
		}

		post(url, obj, function(result) {
			if(result.code == 0) {
				location.reload();
			} else {
				alert(result.text);
			}
		});

	});

	$('div.info a.close').click(function() {
		$('div.info').hide();
	});
}
