<?php
// $Id$

function sociallinks_email_content() {
  return drupal_get_form('sociallinks_email_form');
}

function sociallinks_email_form() {
  global $user;

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail'),
    '#default_value' => $user->mail,
    '#required' => TRUE
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit')
  );
  return $form;
}
