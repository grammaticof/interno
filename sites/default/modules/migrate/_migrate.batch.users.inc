<?php

/**
 * Batch operation for batch 1: load a node.
 * This is the function that is called on each operation in batch 1.
 */
function migrate_batch_users_op(&$context) {
	
	 if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 1;
    $context['sandbox']['current_user'] = 1;
    db_set_active('legacy');
    $context['sandbox']['max'] = db_query('SELECT COUNT(DISTINCT uid) FROM {users} WHERE uid > 1')->fetchField();
    db_set_active('default');
  }
	// 5 per time
	$limit = 5;
	
	db_set_active('legacy');
	$result = db_select('users')
		->fields('users', array('uid', 'name', 'mail', 'created'))
		->condition('uid', $context['sandbox']['current_user'], '>')
		->orderBy('uid')
		->range(0, $limit)
		->execute();
	db_set_active('default');
	
	
  // Store some result for post-processing in the finished callback.
  foreach ($result as $row) {
    $user = _migrate_user($row);
    $context['results'][] = $row->uid . ' : ' . $row->name;
    $context['sandbox']['progress']++;
    $context['sandbox']['current_user'] = $row->uid;
    $context['message'] = $row->name;
  }
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
	
}


function _migrate_user($old_user) {
	
	require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
	
	$uid = db_merge('users') // Table name no longer needs {}
	  ->key(array('uid' => $old_user->uid))
		->fields(array(
		'uid' => $old_user->uid,
		'name' => $old_user->name,
		'pass' => user_hash_password('1nt3rn0'), // default type in drupal 7
		'mail' => $old_user->mail, // default language in drupal 7
		'created' => $old_user->created,
		'status' => 1,
		'init' => $old_user->mail
		))
		->execute();
	
	return 'test';
}


function migrate_batch_users_finished ($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One user processed.', '@count users processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
  // Providing data for the redirected page is done through $_SESSION.
  foreach ($results as $result) {
    $items[] = t('Imported user %name.', array('%name' => $result));
  }
  $_SESSION['my_batch_results'] = $items;
}

