// $Id: sociallinks.js,v 1.1 2010/02/10 23:43:47 greenskin Exp $

Drupal.Sociallinks = {};

Drupal.behaviors.sociallinks = function(){
  Drupal.Sociallinks.activeTab = $('#sociallinks li.active');
  $('#sociallinks li.tab').each(function(i) {
    var tab = $(this);
    switch (Drupal.settings.sociallinks.tabEvent) {
      // Hover
      case 1:
        $('a', tab).mouseover(function() {
          if (!tab.hasClass('active')) {
            Drupal.Sociallinks.switchActive(tab);
          }
        });
        break;
      // Click
      case 2:
        $('a', $(this)).click(function() {
          if (!tab.hasClass('active')) {
            Drupal.Sociallinks.switchActive(tab);
          }
        });
        break;
    }
  });
}

Drupal.Sociallinks.switchActive = function(tab) {
  var id = Drupal.Sociallinks.activeTab.attr('id');
  $('.tab-content.' + id, $('#sociallinks')).addClass('hide');
  Drupal.Sociallinks.activeTab.removeClass('active');

  Drupal.Sociallinks.activeTab = tab;
  var id = tab.attr('id');
  $('.tab-content.' + id, $('#sociallinks')).removeClass('hide');
  tab.addClass('active');
}
