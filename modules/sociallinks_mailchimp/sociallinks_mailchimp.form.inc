<?php

/*******************************************************************************
 * Callback Functions, Forms, and Tables
 ******************************************************************************/

function sociallinks_mailchimp_ajax($js) {
  sociallinks_include('sociallinks_mailchimp.tabs.inc', drupal_get_path('module', 'sociallinks_mailchimp'));
  ctools_include('ajax');
  ctools_include('form');

  $form_state = array(
    'ajax' => $js
  );
  $output = ctools_build_form('sociallinks_mailchimp_form', $form_state);

  if (!$js) {
    return $output;
  }

  if ($messages = theme('status_messages')) {
    $output = $messages . $output;
  }

  $commands = array();
  $commands[] = ctools_ajax_command_remove("#sociallinks-content-mailchimp div.messages");
  $commands[] = ctools_ajax_command_replace('#sociallinks-mailchimp-form', $output);
  ctools_ajax_render($commands);
}

function sociallinks_mailchimp_form($form_state) {
  global $user;

  drupal_add_js('misc/jquery.form.js', 'core');
  ctools_add_js('ajax-responder');

  $ajax = !empty($form_state['ajax']);

  $form_state += array(
    'rerender' => $ajax,
    'no_redirect' => $ajax
  );

  $lists = variable_get('sociallinks_mailchimp_lists', array());
  if (!empty($lists)) {
    $options = array();
    foreach (array_intersect_key(variable_get('mailchimp_lists', array()), $lists) as $list) {
      $options[$list->id] = check_plain($list->name);
    }
    if (count($options) > 1) {
      $form['ids'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Lists'),
        '#options' => $options
      );
    }
    else {
      $form['ids'] = array(
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
    $form['subscribe'] = array(
      '#type' => 'submit',
      '#value' => t('Subscribe'),
      '#attributes' => array('class' => 'ctools-use-ajax')
    );
    $form['unsubscribe'] = array(
      '#type' => 'submit',
      '#value' => t('Unsubscribe'),
      '#attributes' => array('class' => 'ctools-use-ajax')
    );
    $form['#action'] = url('sociallinks/nojs/mailchimp', array('query' => drupal_get_destination()));
  }

  return $form;
}

function sociallinks_mailchimp_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['mail'])) {
    form_set_error('mail', t("The email address you supplied is not valid."));
  }
  $ids = array_filter($form_state['values']['ids']);
  if (empty($ids)) {
    $action = ($form_state['clicked_button']['#value'] == t('Subscribe')) ? t('subscribe') : t('unsubscribe');
    form_set_error('ids', t('Select a list to @action to.', array('@action' => $action)));
  }
}

function sociallinks_mailchimp_form_submit($form, &$form_state) {
  global $user;

  if ($q = _mailchimp_get_api_object()) {
    $lists = variable_get('mailchimp_lists', array());
    $account = _sociallinks_user_load($form_state['values']['mail']);
    $action = ($form_state['clicked_button']['#value'] == t('Subscribe')) ? 'subscribe' : 'unsubscribe';

    // If email belongs to the current registered user, don't send confirmation.
    $confirm = FALSE;

    switch ($action) {
      case 'subscribe':
        foreach ($form_state['values']['ids'] as $id) {
          if (!_mailchimp_is_subscribed($id, $account->mail, $q)) {
            $merge_vars = array('EMAIL' => $form_state['values']['mail']);
            _mailchimp_subscribe_user($lists[$id], $account->mail, $merge_vars, FALSE, $q);
            if (!isset($message)) {
              $message = ($confirm) ? t('You will receive a confirmation email shortly containing further instructions on how to complete your subscription.') : t('You have been subscribed.');
            }
          }
          else {
            drupal_set_message(t('The email %mail is already subscribed to %list.', array('%mail' => $account->mail, '%list' => $lists[$id]->name)), 'warning');
          }
        }
        break;
      case 'unsubscribe':
        foreach ($form_state['values']['ids'] as $id) {
          if (_mailchimp_is_subscribed($id, $account->mail, $q)) {
            _mailchimp_unsubscribe_user($lists[$id], $account->mail, FALSE, $q);
            if (!isset($message)) {
              $message = ($confirm) ? t('You will receive a confirmation email shortly containing further instructions on how to complete the unsubscription process.') : t('You have been unsubscribed.');
            }
          }
          else {
            drupal_set_message(t('The email %mail is already unsubscribed to %list.', array('%mail' => $account->mail, '%list' => $lists[$id]->name)), 'warning');
          }
        }
        break;
    }

    if ($message) {
      drupal_set_message($message);
    }
  }
}
