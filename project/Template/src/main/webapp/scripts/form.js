function get_form_data(id) {
	var obj = {};
	$('#' + id + ' input,select').each(function() {
		obj[$(this).attr('name')] = $(this).val();
	});
	return obj;
}
