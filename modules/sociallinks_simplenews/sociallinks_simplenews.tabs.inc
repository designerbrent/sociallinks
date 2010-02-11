<?php
// $Id: sociallinks_simplenews.tabs.inc,v 1.1 2010/02/10 23:43:47 greenskin Exp $

/*******************************************************************************
 * Social Link Email tab
 ******************************************************************************/

function sociallinks_simplenews_configure() {
  $form = array();
  $tree = taxonomy_get_tree(variable_get('simplenews_vid', ''));
  if (!empty($tree)) {
    $options = array();
    foreach ($tree as $newsletter) {
      $options[$newsletter->tid] = $newsletter->name;
    }
    $form['newsletters'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Newsletters'),
      '#description' => t('Select newsletters users can subscribe to. At least one newsletter needs to be selected for the tab to be enabled.'),
      '#default_value' => variable_get('sociallinks_simplenews_newsletters', array()),
      '#options' => $options
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
function sociallinks_simplenews_save(&$edit) {
  // Ensure at least an empty array is saved.
  $newsletters = (isset($edit['newsletters'])) ? $edit['newsletters'] : array();
  $newsletters = array_filter($newsletters);
  variable_set('sociallinks_simplenews_newsletters', $newsletters);

  // Disable the tab if no newsletters are selected for subscribing to.
  if (empty($newsletters)) return FALSE;
}

function sociallinks_simplenews_content() {
  module_load_include('inc', 'sociallinks_simplenews', 'sociallinks_simplenews.form');
  return drupal_get_form('sociallinks_simplenews_form');
}
