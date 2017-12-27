var menu_items = {
	/*
	"用户系统" : {
		"个人信息" : "/user/info",
		"退出登录" : "/user/logout",
	},
	"银行系统" : {
		"开户" : "/bank/openAccount",
		"账户余额" : "/bank/accounts",
		"转账" : "/bank/transfer",
		"明细" : "/bank/history",
	},
	"商城系统" : {
		"商品列表" : "/shop/list",
		"购物车" : "/shop/cart",
		"历史纪录" : "/shop/history",
	}
	*/
};

function init_menu(list) {

	if(list == null) {
		list = menu_items;
	}

	for(var i in list) {
		$('#menu_main').append($('<li></li>').text(i).data('childs', list[i]).click(function() {
			var childs = $(this).data('childs');
			$('#menu_child').empty();
			for(var j in childs) {
				$('#menu_child').append($('<li></li>').text(j).data('uri', childs[j]).click(function() {
					trigger_menu($(this).data('uri'));
				}));
			}
			$('#menu_main li').css('color', 'blue');
			$(this).css('color', "red");
		}));
	}

}

function trigger_menu(uri) {
	location.href = getContextPath() + uri;
}
