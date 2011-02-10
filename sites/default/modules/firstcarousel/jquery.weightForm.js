(function ($) {
	
	Drupal.behaviors.weightForm = {
		attach: function(context, settings) {
			$('#firstcarousel-order tr.draggable').each(function(index) {
				$(this).find('td:last').html(index+1);
			});
			
			if ($('#firstcarousel-order tr.draggable').size() > Drupal.settings.firstcarousel.limit) {
				$('#firstcarousel-order tr.draggable').removeClass('last').last().addClass('last').find('td:last').html('out');
			}
		}
	};

})(jQuery);
