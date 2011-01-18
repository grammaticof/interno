(function ($) {
	
	Drupal.behaviors.firstcarousel = {
		attach: function(context, settings) {
			var $carousel = $(".slidetabs", context).tabs(".images > div", {
				event: 'mouseover',
				clickable: false,
				// enable "cross-fading" effect
				effect: 'fade',
				fadeOutSpeed: "fast",

				// start from the beginning after the last tab
				rotate: true

				// use the slideshow plugin. It accepts its own configuration
			}).slideshow({
				interval: 6000,
				// autoplay: true,
				clickable: false
			}).data("tabs");
			
			$carousel.getPanes().click(function(){
				window.location = $('a', $(this)).attr('href');
			});
		}
	};

})(jQuery);
