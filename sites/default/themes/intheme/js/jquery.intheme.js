(function($){

  Drupal.behaviors.inthemesf = {
    attach: function(context) {
      $('ul.main-menu').supersubs({ 
        minWidth:    12,   // minimum width of sub-menus in em units 
        maxWidth:    27,   // maximum width of sub-menus in em units 
        extraWidth:  1     // extra width can ensure lines don't sometimes turn over 
        // due to slight rounding differences and font-family 
      }).superfish({ 
        delay:       1000,                         // one second delay on mouseout 
        animation:   {opacity:'show',height:'show'}, // fade-in and slide-down animation
        speed:       'fast',                         // faster animation speed 
        autoArrows:  false,                          // disable generation of arrow mark-up 
        dropShadows: false                           // disable drop shadows 
      }).find('ul').bgIframe({opacity:false});
    }
  };
  
  Drupal.behaviors.submenu = {
    attach: function(context) {
      var timeInterval = 10000;
      var $active;
      var $next;
      
      function swapInfo() {
        $active = $('#block-user-toolbar-sub-menu ul.current');
        $next = ($('#block-user-toolbar-sub-menu ul.current').next().length > 0) ? $('#block-user-toolbar-sub-menu ul.current').next() : $('#block-user-toolbar-sub-menu ul:first');
        
        $next.fadeIn(function() {
          $active.fadeOut().removeClass('current');
          $next.addClass('current');
        });
      }
      // autoplay
      var interval = setInterval(swapInfo, timeInterval);
      
      // pause/play
      $('#block-user-toolbar-sub-menu').hover(function () {
        clearInterval(interval);
      }, function () {
        interval = setInterval(swapInfo, timeInterval);
      });
      
      /*
      $('ul.main-menu').hover(function () {
        clearInterval(interval);
        $('#block-user-toolbar-sub-menu ul:first').fadeIn( function() {
          $('#block-user-toolbar-sub-menu ul.current').fadeOut().removeClass('current');
          $('#block-user-toolbar-sub-menu ul:first').addClass('current');
        });

      }, function() {
        interval = setInterval(swapInfo, timeInterval);
      });
      */
    }
  };
  

})(jQuery);
