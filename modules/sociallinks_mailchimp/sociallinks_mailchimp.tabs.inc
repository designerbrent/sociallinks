<?php

/*******************************************************************************
 * Social Link Email tab
 ******************************************************************************/

function sociallinks_mailchimp_configure() {
  $form = array();

  if ($q = _mailchimp_get_api_object()) {
    $lists = $q->lists();
    if (!empty($lists)) {
      $options = array();
      foreach ($lists as $list) {
        $options[$list['id']] = check_plain($list['name']);
      }
      $form['lists'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Lists'),
        '#description' => t('Select lists users can subscribe to. At least one list needs to be selected for the tab to be enabled.'),
        '#default_value' => variable_get('sociallinks_mailchimp_lists', array()),
        '#options' => $options
      );
    }
    else {
      $form['message'] = array(
        '#type' => 'item',
        '#value' => t('You do not have any valid MailChimp mailing lists.')
      );
    }
  }
  else {
    $form['configure'] = array(
      '#type' => 'item',
      '#value' => t('MailChimp has not yet been configured. !link to allow lists to be subscribed to.', array('!link' => l(t('Configure MailChimp'), 'admin/settings/mailchimp', array('query' => drupal_get_destination()))))
    );
  }

  return $form;
}

/**
 * Save selected newsletters user can subscribe to.
 *
 * We return FALSE if there were no newsletters selected. This affectively
 * disables the tab.
 */
function sociallinks_mailchimp_save(&$edit) {
  // Ensure at least an empty array is saved.
  $lists = (isset($edit['lists'])) ? $edit['lists'] : array();
  $lists = array_filter($lists);
  variable_set('sociallinks_mailchimp_lists', $lists);

  // Disable the tab if no newsletters are selected for subscribing to.
  if (empty($lists)) return FALSE;
}

function sociallinks_mailchimp_content() {
  module_load_include('inc', 'sociallinks_mailchimp', 'sociallinks_mailchimp.form');
  return drupal_get_form('sociallinks_mailchimp_form');
}
