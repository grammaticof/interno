(function ($) {
	
	Drupal.behaviors.user_toolbar = {
		attach: function(context, settings) {
			var $login = $('#user-toolbar a.login-link').click(function(e) {
				$('#user-toolbar-login').toggle();
				$(this).toggleClass('open');
				return false;
			})
			
			/*
			$('#user-toolbar-login').mouseup(function() {
				return false
			});
			
			$(document).mouseup(function(e) {
				$login.removeClass("open");
				$('#user-toolbar-login').hide();
			});  
			*/
		}
	};

})(jQuery);
