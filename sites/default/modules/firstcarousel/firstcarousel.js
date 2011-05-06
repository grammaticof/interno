(function ($) {
	
	Drupal.behaviors.firstcarousel = {
		attach: function(context, settings) {
			var api = $(".scrollable").scrollable({'circular' : true}).navigator().autoscroll({'interval' : 6000}).data('scrollable');
			var $items = api.getItems();
			
			api.onBeforeSeek(function(event, i) {
				$items.eq(i).find('img.lazy').trigger('Foo');
			});
			
			$(".scrollable img.lazy").bind('Foo', {}, function(e) {});
			
			$(".scrollable img.lazy").lazyload({
				placeholder: "sites/default/files/white.gif", 
				event: 'Foo'
			});
		}
	};

})(jQuery);
