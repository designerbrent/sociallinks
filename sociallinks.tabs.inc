<?php
// $Id$

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
  $url = variable_get('sociallinks_facebook_url', '');
  $url_title = variable_get('sociallinks_facebook_url_title', '');
  return (!empty($url)) ? l($url_title, $url, array('attributes' => array('target' => '_blank', 'class' => 'facebook'))) : '';
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
  $username = variable_get('sociallinks_twitter_username', '');
  return l(t('@@username', array('@username' => $username)), 'http://www.twitter.com/'. $username, array('attributes' => array('target' => '_blank', 'class' => 'twitter')));
}
