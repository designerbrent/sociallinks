<?php
// $Id: sociallinks.tabs.inc,v 1.1 2010/02/10 23:43:47 greenskin Exp $

/*******************************************************************************
 * Social Link Facebook tab
 ******************************************************************************/

function sociallinks_facebook_configure() {
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#description' => t('The Facebook URL to link to.'),
    '#default_value' => variable_get('sociallinks_facebook_url', '')
  );
  $form['url_title'] = array(
    '#type' => 'textfield',
    '#title' => t('URL Title'),
    '#description' => t('Enter the title for your Facebook URL'),
    '#default_value' => variable_get('sociallinks_facebook_url_title', 'Visit our Facebook Page')
  );
  
  return $form;
}

function sociallinks_facebook_save($edit) {
  variable_set('sociallinks_facebook_url_title', $edit['url_title']);
  variable_set('sociallinks_facebook_url', $edit['url']);
}

function sociallinks_facebook_content() {
  if (variable_get('sociallinks_tab_event','hover') == 'click') {
    $url = variable_get('sociallinks_facebook_url', '');
    $url_title = variable_get('sociallinks_facebook_url_title', '');
    return (!empty($url)) ? l($url_title, $url, array('attributes' => array('target' => '_blank', 'class' => 'facebook'))) : '';
  }
}

/*******************************************************************************
 * Social Link Twitter tab
 ******************************************************************************/

function sociallinks_twitter_configure() {
  $form['username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t("The Twitter account's username to link to."),
    '#default_value' => variable_get('sociallinks_twitter_username', '')
  );
  return $form;
}

function sociallinks_twitter_save($edit) {
  variable_set('sociallinks_twitter_username', $edit['username']);
}

function sociallinks_twitter_content() {
  if (variable_get('sociallinks_tab_event','hover') == 'click') {
    $username = variable_get('sociallinks_twitter_username', '');
    return l(t('@@username', array('@username' => $username)), 'http://www.twitter.com/'. $username, array('attributes' => array('target' => '_blank', 'class' => 'twitter')));
  }
}
  


/*******************************************************************************
 * Social Link RSS tab
 ******************************************************************************/

function sociallinks_rss_configure() {

  $form['rss_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Feed URL'),
    '#description' => t('The feed to link to.'),
    '#default_value' => variable_get('sociallinks_rss_url', '')
  );
  $form['rss_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Feed Title'),
    '#description' => t('Enter the title for this feed.'),
    '#default_value' => variable_get('sociallinks_rss_title', '')
  );
  return $form;
}

function sociallinks_rss_save($edit) {
  variable_set('sociallinks_rss_title', $edit['rss_title']);
  variable_set('sociallinks_rss_url', $edit['rss_url']);
}

function sociallinks_rss_content() {
  if (variable_get('sociallinks_tab_event','hover') == 'click') {
    $rss_url = variable_get('sociallinks_rss_url', '');
    $rss_title = variable_get('sociallinks_rss_title', '');
    return l($rss_title, $rss_url, array('attributes' => array('target' => '_blank', 'class' => 'rss')));
  }
}

