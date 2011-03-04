<?php


dsm($vars['region']);

switch ($vars['region']) {
	case 'menu':
		if (module_exists('gsearch'))
			$vars['google_search'] = theme('gsearch_form');
			
		// override default menu.
		$vars['main_menu'] = '';
		
		$vars['menu_type'] = $menu_type = omega_theme_get_setting('omega_menu_type') ? omega_theme_get_setting('omega_menu_type') : 'omega';

		// render the Omega Dropdowns. These are set to be phased out, but cannot be removed for sanity on existing sites.
		if (variable_get('menu_main_links_source', 'main-menu') == variable_get('menu_secondary_links_source', 'user-menu') && $menu_type == 'omega') {
			$menu_depth = omega_theme_get_setting('omega_menu_depth') ? omega_theme_get_setting('omega_menu_depth') : 1;
			// render the menus as nested ULs to style up some drop downs.
			$vars['menu_data'] = $menu = omega_menu_structure(menu_tree_page_data(variable_get('menu_main_links_source', 'main-menu'), $menu_depth, FALSE));
			
			// include pathauto
			module_load_include('inc', 'pathauto');
			// change the <li> class
			foreach ($menu as $mid => $data) {
				$title = pathauto_cleanstring($data['title']);
				unset($menu[$mid]);
				$menu[$title] = $data;
			}
			
			$vars['main_menu'] = theme('links', array(
				'links' => $menu,
				'attributes' => array(
				  'class' => array('links', 'main-menu'),
				),
				'heading' => array(
				  'text' => t('Main menu'),
				  'level' => 'h2',
				  'class' => array('element-invisible'),
				)
			));
			$vars['secondary_menu'] = FALSE;
		}		
		
		
	break;
}



