<div<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page && $title): ?>
  <h2 <?php print $title_attributes; ?>><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  
  <div class="content clearfix"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
      print render($content['links'])
    ?>
  </div>
</div>
