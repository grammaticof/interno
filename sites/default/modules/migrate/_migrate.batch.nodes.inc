<?php

/**
 * Batch operation for batch 1: load a node.
 * This is the function that is called on each operation in batch 1.
 */
function migrate_batch_nodes_op(&$context) {
	$old_type = 'story';
	
	if (empty($context['sandbox'])) {
		$context['sandbox']['progress'] = 0;
		$context['sandbox']['current_node'] = 0;
		db_set_active('legacy');
		$context['sandbox']['max'] = 100; //db_query('SELECT COUNT(DISTINCT n.nid) FROM {node} n INNER JOIN {node_revisions} nr ON n.vid = nr.vid WHERE n.type = :old_type', array(':old_type' => $old_type))->fetchField();
		db_set_active('default');
	}
	// 5 per time
	$limit = 50;
	
	db_set_active('legacy');
	$query = db_select('node', 'n');
	$query->fields('n', array('nid', 'title'));
	$query->innerJoin('node_revisions', 'nr', 'n.vid = nr.vid');
	$query->condition('n.nid', $context['sandbox']['current_node'], '>');
	$query->condition('n.type', $old_type);
	$query->orderBy('n.nid');
	$query->range(0, $limit);

	$result = $query->execute();
	db_set_active('default');
	
	// Store some result for post-processing in the finished callback.
	foreach ($result as $row) {
		$status = _migrate_nodes($row->nid);
		$context['results'][] = $row->nid . ' : ' . $row->title;
		$context['sandbox']['progress']++;
		$context['sandbox']['current_node'] = $row->nid;
		$context['message'] = $row->title . ' - ' . $context['sandbox']['progress'] . '/' . $context['sandbox']['max'];
	}
	if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
		$context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
	}
}

function _migrate_nodes($old_nid) {
	$bundle = 'article'; // Default type in Drupal 7
	$entity_type = 'node';
	
	db_set_active('legacy');
	$old_nid_param = array(':old_nid' => $old_nid);
	
	// select only the nodes with a revision.
	$old_node = db_query('SELECT n.uid, n.nid, n.title, n.created, n.changed, n.promote, n.sticky, n.vid, nr.body, nr.teaser FROM {node} n INNER JOIN {node_revisions} nr ON n.vid=nr.vid WHERE n.nid = :old_nid', $old_nid_param)->fetchObject();
	
	$old_node_extra = db_query('SELECT * FROM {content_type_story} WHERE nid = :old_nid', $old_nid_param)->fetchObject();
	
	$old_taxs = db_query('SELECT v.name AS voc_name, td.name AS term_name FROM {term_node} tn INNER JOIN {term_data} td ON tn.tid = td.tid INNER JOIN {vocabulary} v ON td.vid = v.vid WHERE tn.nid = :old_nid ORDER BY v.name ASC', $old_nid_param);
	db_set_active('default');
	
	node_delete($old_nid);
	
	db_insert('node') // Table name no longer needs {}
		->fields(array(
		'nid' => $old_node->nid,
		'vid' => $old_node->nid,
		'type' => $bundle, // default type in drupal 7
		'language' => LANGUAGE_NONE, // default language in drupal 7
		'title' => $old_node->title,
		'uid' => $old_node->uid,
		'status' => '1',
		'created' => $old_node->created,
		'changed' => $old_node->changed,
		'comment' => '0', // 0 for no comment, 2 for allowing commenting
		'promote' => '1',
		'sticky' => '0',
		'tnid' => '0',
		'translate' => '0',
		))
		->execute();

	db_insert('node_revision') // Table name no longer needs {}
		->fields(array(
		'nid' => $old_node->nid,
		'vid' => $old_node->nid,
		'log' => '',
		'title' => $old_node->title,
		'uid' => $old_node->uid,
		'status' => '1',
		'timestamp' => $old_node->changed,
		'comment' => '0',
		'promote' => '1',
		'sticky' => '0',
		))
		->execute();

	$node = node_load($old_nid);
	
	// populate node_comment_statistics
	// comment_node_insert($node);
	
	// field_body
	$node->body[$node->language][0]['value'] = $old_node->body;
	$node->body[$node->language][0]['format'] = 'filtered_html';
	
	if (isset($old_node_extra->nid)) {
		// field_short
		$node->field_short[$node->language][0]['value'] = $old_node_extra->field_sommarietto_value;
	}

	// TAXONOMY
	
	$voc = db_query('SELECT machine_name, vid FROM {taxonomy_vocabulary}')->fetchAllAssoc('machine_name');	
	foreach ($old_taxs as $old_tax) {
		switch ($old_tax->voc_name) {
			case 'Categoria': // field_type
				$field_type_tid = db_query('SELECT tid FROM {taxonomy_term_data} WHERE name=:term_name AND vid=:voc_vid', 
				array(
					':term_name'=>$old_tax->term_name,
					':voc_vid'=>$voc['type']->vid)
				)->fetchField();

				if ($field_type_tid) {
					$node->field_type[$node->language][0]['tid'] = $field_type_tid;
				}
				else {
					$new_term = array(
						'name' => $old_tax->term_name,
						'description' => '',
						'vid' => $voc['type']->vid,
					);
					$term = (object) $new_term;
					taxonomy_term_save($term);
					$node->field_type[$node->language][0]['tid'] = $term->tid;
				}
			break;
			case 'Città': // field_location
				$field_type_tid = db_query('SELECT tid FROM {taxonomy_term_data} WHERE name=:term_name AND vid=:voc_vid', 
				array(
					':term_name'=>$old_tax->term_name,
					':voc_vid'=>$voc['location']->vid)
				)->fetchField();

				if ($field_type_tid) {
					$node->field_location[$node->language][] = array(
						'tid' => $field_type_tid,
					);
				}
				else {
					$new_term = array(
						'name' => $old_tax->term_name,
						'description' => '',
						'vid' => $voc['location']->vid,
					);
					$term = (object) $new_term;
					taxonomy_term_save($term);
					$node->field_location[$node->language][] = array (
						'tid' => $term->tid,
					);
				}
			break;
			case 'Free tag': // field_tags
				$field_type_tid = db_query('SELECT tid FROM {taxonomy_term_data} WHERE name=:term_name AND vid=:voc_vid', 
				array(
					':term_name'=>$old_tax->term_name,
					':voc_vid'=>$voc['tags']->vid)
				)->fetchField();

				if ($field_type_tid) {
					$node->field_tags[$node->language][] = array(
						'tid' => $field_type_tid,
					);
				}
				else {
					$new_term = array(
						'name' => $old_tax->term_name,
						'description' => '',
						'vid' => $voc['tags']->vid,
					);
					$term = (object) $new_term;
					taxonomy_term_save($term);
					$node->field_tags[$node->language][] = array (
						'tid' => $term->tid,
					);
				}
			break;
			case 'Rubrica': // field_tags
				$field_type_tid = db_query('SELECT tid FROM {taxonomy_term_data} WHERE name=:term_name AND vid=:voc_vid', 
				array(
					':term_name'=>$old_tax->term_name,
					':voc_vid'=>$voc['rubric']->vid)
				)->fetchField();

				if ($field_type_tid) {
					$node->field_rubric[$node->language][] = array(
						'tid' => $field_type_tid,
					);
				}
				else {
					$new_term = array(
						'name' => $old_tax->term_name,
						'description' => '',
						'vid' => $voc['rubric']->vid,
					);
					$term = (object) $new_term;
					taxonomy_term_save($term);
					$node->field_rubric[$node->language][] = array (
						'tid' => $term->tid,
					);
				}
			break;
		}
	}
	node_save($node);
	
	return TRUE;
}

function migrate_batch_nodes_finished ($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One node processed.', '@count nodes processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
}
