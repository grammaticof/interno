(function($){

  Drupal.behaviors.inthemesf = {
    attach: function(context) {
      $('ul.main-menu').superfish({ 
        /*delay:       1000,                         // one second delay on mouseout 
        animation:   {opacity:'show',height:'show'}, // fade-in and slide-down animation
        speed:       'fast',                         // faster animation speed */
        autoArrows:  false,                          // disable generation of arrow mark-up 
        dropShadows: false                           // disable drop shadows 
      }).find('ul').bgIframe({opacity:false});
    }
  };

})(jQuery);
