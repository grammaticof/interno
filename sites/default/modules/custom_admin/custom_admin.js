(function ($) {
	
	Drupal.behaviors.custom_messages = {
		attach: function(context, settings) {
			// status message hide.
			$('#console .messages.form-status').delay(5000).slideUp('slow');
			$('#message-container .messages, #console .messages').append('<div class="close"></div>');
			
			$('#message-container .close, #console .close').hover(function() {
				$(this).toggleClass('hover');
			});
			
			$('#message-container .close, #console .close').click(function() {
				$('#message-container, #console').slideUp('slow');
			});
			
		}
	};
})(jQuery);
