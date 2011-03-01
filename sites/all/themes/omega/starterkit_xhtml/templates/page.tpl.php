<?php

/**
 * @file 
 * Theme implementation to display a single Drupal page.
 */

?>
<div id="page" class="clearfix">
  <?php if (isset($page['zones_above'])): ?>
  <div id="zones-above" class="clearfix"><?php print render($page['zones_above']); ?></div>
  <?php endif; ?>
  <div id="zones-content" class="clearfix">
    <?php if (isset($action_links)): ?>
      <div id="actions-container" class="container-<?php print $default_container_width; ?> clearfix">
        <div class="grid-<?php print $default_container_width; ?>">
          <ul class="action-links">
            <?php print render($action_links); ?>
          </ul>
        </div>
      </div>
    <?php endif; ?>
    <?php if (isset($messages)): ?>
    <div id="message-container" class="container-<?php print $default_container_width; ?> clearfix">
      <div class="grid-<?php print $default_container_width; ?>">
        <?php print $messages; ?>
      </div>
    </div><!-- /.container-xx -->
    <?php endif; ?>
    <?php if (isset($page['content_zone'])): ?>
      <?php print render($page['content_zone']); ?>
    <?php endif; ?>
  </div>
  
  <?php if (isset($page['zones_below'])): ?>
  <div id="zones-below" class="clearfix"><?php print render($page['zones_below']); ?></div>
  <?php endif; ?>
</div><!-- /#page -->