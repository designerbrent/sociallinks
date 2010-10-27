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

/*******************************************************************************
 * Social Link RSS tab
 ******************************************************************************/

function sociallinks_rss_configure() {

    $form['feed1_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Feed 1 URL'),
      '#description' => t('The feed to link to.'),
      '#default_value' => variable_get('sociallinks_feed1_url', '')
    );
    $form['feed1_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Feed 1 Title'),
      '#description' => t('Enter the title for this feed.'),
      '#default_value' => variable_get('sociallinks_feed1_title', '')
    );

    $form['feed2_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Feed 2 URL'),
      '#description' => t('The feed to link to.'),
      '#default_value' => variable_get('sociallinks_feed2_url', '')
    );
    $form['feed2_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Feed 2 Title'),
      '#description' => t('Enter the title for this feed.'),
      '#default_value' => variable_get('sociallinks_feed2_title', '')
    );
    return $form;
  }

  function sociallinks_rss_save($edit) {
    variable_set('socialLinks_rss_feed2_title', $edit['feed2_title']);
    variable_set('socialLinks_rss_feed2_url', $edit['feed2_url']);
    variable_set('socialLinks_rss_feed1_title', $edit['feed1_title']);
    variable_set('socialLinks_rss_feed1_url', $edit['feed1_url']);
    
    
  }

  function sociallinks_rss_content() {
    $url1_url = variable_get('socialLinks_rss_feed1_url', '');
    $url1_title = variable_get('socialLinks_rss_feed1_title', '');
    $url2_url = variable_get('socialLinks_rss_feed2_url', '');
    $url2_title = variable_get('socialLinks_rss_feed2_title', '');    

    if (!empty($url1_url) && !empty($url2_url)) {
      $items = array();
      $items[] = array('title' => $url1_title, 'href' => $url1_url);
      $items[] = array('title' => $url2_title, 'href' => $url2_url);

      $output = theme('links', $items, array('class'=>'mylinks'));

    } elseif (!empty($url1_url)) {

      $output = l($url1_title, $url1_url, array('attributes' => array('target' => '_blank', 'class' => 'rss')));
    }
    return $output;
  }

