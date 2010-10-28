// $Id: sociallinks.js,v 1.1 2010/02/10 23:43:47 greenskin Exp $

Drupal.behaviors.sociallinks = function(){
  Drupal.settings.sociallinks.tabEvent;
  $('#sociallinks li.tab').each(function(i) {
    switch (Drupal.settings.sociallinks.tabEvent) {
      // Hover
      case 1:
        $(this).hover(function() {
          
        });
        break;
      // Click
      case 2:
        $(this).click(function() {
          
        });
        break;
    }
  });
}
