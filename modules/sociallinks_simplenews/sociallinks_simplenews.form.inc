<?php
// $Id$

/*******************************************************************************
 * Callback Functions, Forms, and Tables
 ******************************************************************************/

function sociallinks_simplenews_ajax($js) {
  sociallinks_include('sociallinks_simplenews.tabs.inc', drupal_get_path('module', 'sociallinks_simplenews'));
  ctools_include('ajax');
  ctools_include('form');

  $form_state = array(
    'ajax' => $js
  );
  $output = ctools_build_form('sociallinks_simplenews_form', $form_state);

  if (!$js) {
    return $output;
  }

  if ($messages = theme('status_messages')) {
    $output = $messages . $output;
  }

  $commands = array();
  $commands[] = ctools_ajax_command_replace('#sociallinks-simplenews-form', $output);
  ctools_ajax_render($commands);
}

function sociallinks_simplenews_form($form_state) {
  global $user;

  drupal_add_js('misc/jquery.form.js', 'core');
  ctools_add_js('ajax-responder');

  $form_state += array(
    'rerender' => FALSE,
    'no_redirect' => !empty($form_state['ajax'])
  );

  $newsletters = variable_get('sociallinks_simplenews_newsletters', array());
  if (!empty($newsletters)) {
    $options = array();
    foreach (taxonomy_get_tree(variable_get('simplenews_vid', '')) as $newsletter) {
      if (in_array($newsletter->tid, $newsletters)) {
        $options[$newsletter->tid] = $newsletter->name;
      }
    }
    if (count($options) > 1) {
      $form['tids'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Newsletters'),
        '#options' => $options
      );
    }
    else {
      $form['newsletter'] = array(
        '#type' => 'item',
        '#value' => current($options)
      );
      $form['tids'] = array(
        '#type' => 'value',
        '#value' => array_keys($options)
      );
    }
    $form['mail'] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#default_value' => $user->mail,
      '#size' => 30,
      '#maxlength' => 128,
      '#required' => TRUE
    );
    $form['action'] = array(
      '#type' => 'value',
      '#value' => 'subscribe'
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      '#attributes' => array('class' => 'ctools-use-ajax')
    );
    $form['#action'] = url('sociallinks/nojs/simplenews', array('query' => drupal_get_destination()));
  }

  return $form;
}

function sociallinks_simplenews_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['mail'])) {
    form_set_error('mail', t("The email address you supplied is not valid."));
  }
  $tids = array_filter($form_state['values']['tids']);
  if (empty($tids)) {
    form_set_error('tids', t('Select a newsletter to subscribe to.'));
  }
}

function sociallinks_simplenews_form_submit($form, &$form_state) {
  global $user;

  $account = _simplenews_user_load($form_state['values']['mail']);

  // If email belongs to the current registered user, don't send confirmation.
  $confirm = $account->uid && $account->uid == $user->uid ? FALSE : TRUE;

  foreach ($form_state['values']['tids'] as $tid) {
    if (!simplenews_user_is_subscribed($account->mail, $tid)) {
      simplenews_subscribe_user($form_state['values']['mail'], $tid, $confirm);
      $message = TRUE;
    }
    else {
      $newsletter = taxonomy_get_term($tid);
      drupal_set_message(t('The email %mail is already subscribed to %newsletter.', array('%mail' => $account->mail, '%newsletter' => $newsletter->name)), 'warning');
    }
  }

  if ($message) {
    if ($confirm) {
      drupal_set_message(t('You will receive a confirmation email shortly containing further instructions on how to complete your subscription.'));
    }
    else {
      drupal_set_message(t('You have been subscribed.'));
    }
  }
}
