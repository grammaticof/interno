(function ($) {
	
	Drupal.behaviors.firstcarousel = {
		attach: function(context, settings) {
			$(".scrollable").scrollable({'circular' : true}).navigator().autoscroll({'interval' : 6000});
		}
	};

})(jQuery);
