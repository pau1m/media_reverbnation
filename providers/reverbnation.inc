<?php

// $Id: soundcloud.inc,v 1.2 2010/09/29 14:08:11 joachim Exp $

/**
 * @file
 * This include processes Soundcloud audio files for use by emaudio.module.
 */
// @todo -> find a regular expression to match the href and extract artist
// name -> very easyily broken
//still have to account for entering an artist url 

define('EMAUDIO_REVERBNATION_MAIN_URL', 'http://reverbnation.com');
define('EMAUDIO_REVERBNATION_VERSION', 1);



// default player settings
define('EMAUDIO_REVERBNATION_FONT_COLOR_DEFAULT', '#333333'); //use defaults for
define('EMAUDIO_REVERBNATION_BACKGROUND_COLOR_DEFAULT', '#ffffff'); // indivudiual player
define('EMAUDIO_REVERBNATION_BORDER_COLOR_DEFAULT', '#ffffff');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_DEFAULT', 'PWAS1003');
define('EMAUDIO_REVERBNATION_PLAYER_SIZE_DEFAULT', 'emaudio'); // reverb classic
// change title to minimum
// maybe can remove default from other above
define('EMAUDIO_REVERBNATION_PLAYER_DEFAULT_WIDTH', 180);  // remove this and taken from emfield
define('EMAUDIO_REVERBNATION_PLAYER_DEFAULT_HEIGHT', 60); // take from emfield
//reverb nation players
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_REVERB', 'PWAS1003');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_SEAMLESS', 'PWAS1008');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_TINY', 'PWAS1001');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_STRONG', 'PWAS1002');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_ELECTRO', 'PWAS1004');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_SKETCHED', 'PWAS1005');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_BUTTON', 'PWAS1006');
define('EMAUDIO_REVEBNATION_PLAYER_TYPE_BUTTON _LIGHT', 'PWAS1007');



define('EMAUDIO_SOUNDCLOUD_MAIN_URL', 'http://soundcloud.com/');

/**
 * Implementation of hook emaudio_PROVIDER_info().
 *
 * This returns information relevant to a specific 3rd party audio provider.
 *
 * @return
 *   An array of strings requested by various admin and other forms.
 *   'name' => The translated name of the provider.
 *   'url' => The url to the main page for the provider.
 *   'settings_description' => A description of the provider that will be posted in the admin settings form.
 *   'supported_features' => An array of rows describing the state of certain supported features by the provider.
 *      These will be rendered in a table, with the columns being 'Feature', 'Supported', 'Notes'.
 */
function emaudio_reverbnation_info() {
    $features = array(
        array(t('Autoplay'), t('Yes'), ''),
        array(t('RSS Attachment'), t('No'), ''),
        array(t('Thumbnails'), t('No'), t('')),
        array(t('Duration'), t('Yes'), ''),
        array(t('Full screen mode'), t('No'), t('You may customize the player to enable or disable full screen playback. Full screen mode is enabled by default.')),
        array(t('Use JW FLV Media Player'), t('No'), t("You may opt to use the !flvplayer to play example.com videos if it's installed on your server.", array('!flvplayer' => l(t('JW FLV Media Player'), 'http://www.longtailvideo.com/players/jw-flv-player/')))),
    );
    return array(
        'provider' => 'reverbnation',
        'name' => t('Reverbnation'),
        'url' => EMAUDIO_REVERBNATION_MAIN_URL,
        //@todo fix the following line properly for subsitution
        'settings_description' => t('These settings specifically affect videos displayed from <a href="@example" target="_blank">reverbnation.com</a>.', array('@example' => 'http://reverbnation.com')),
        'supported_features' => $features,
    );
}

/**
 * Implementation of hook emaudio_PROVIDER_settings().
 *
 * This should return a subform to be added to the emaudio_settings() admin settings page.
 * Note that a form field will already be provided, at $form['odeo'] (such as $form['podomatic']).
 * So if you want specific provider settings within that field, you can add the elements to that form field.
 */
//have to alter validation. don't want the #
//have to sort for # or not #
//change input message / sort validation
function emaudio_reverbnation_settings() {
    $form = array();

    $form['reverbnation']['player'] = array(
        '#type' => 'fieldset',
        '#title' => t('Embedded audio player options'),
        '#description' => t('Styling and playback options for the embedded player.'),
        '#collapsible' => true,
        '#collapsed' => true,
    );

    $form['reverbnation']['player']['type'] = array(
        '#type' => 'fieldset',
        '#title' => 'Embedded media player type',
        '#description' => 'Select the type of player',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['reverbnation']['player']['type']['emaudio_reverbnation_player_type'] = array(
        '#type' => 'radios',
        '#title' => 'Select a player type (add link later and poss help',
        '#description' => t('Choose the type of player'),
        '#default_value' => variable_get('emaudio_reverbnation_player_type', EMAUDIO_REVEBNATION_PLAYER_TYPE_DEFAULT),
        '#options' => array(
            // constants here???
            'PWAS1003' => t('Reverb Classic'),
            'PWAS1008' => t('Seamless'),
            'PWAS1001' => t('Tiny Spaces'),
            'PWAS1002' => t('Standard Strong'),
            'PWAS1004' => t('Electro Green'),
            'PWAS1005' => t('Sketched'),
            'PWAS1006' => t('Big Button'),
            'PWAS1007' => t('Big Button Light'),
        ),
    );

    $form['reverbnation']['player']['color'] = array(
        '#type' => 'fieldset',
        '#title' => t('Embedded audio player color'),
        '#description' => t('If allowed, this color, in hexidecimal form (#RRGGBB), will be used to change the skin of the reverbnation player.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
//    $form['reverbnation']['player']['color']['emaudio_reverbnation_color_override'] = array(
//        '#type' => 'checkbox',
//        '#title' => t('Override player color'),
//        '#default_value' => variable_get('emaudio_reverbnation_color_override', FALSE),
//    );
    $form['reverbnation']['player']['color']['emaudio_reverbnation_font_color'] = array(
        '#type' => 'textfield',
        '#title' => t('Font color'),
        '#default_value' => variable_get('emaudio_reverbnation_font_color', EMAUDIO_REVERBNATION_FONT_COLOR_DEFAULT),
    );

    $form['reverbnation']['player']['color']['emaudio_reverbnation_border_color'] = array(
        '#type' => 'textfield',
        '#title' => t('Border color'),
        '#default_value' => variable_get('emaudio_reverbnation_border_color', EMAUDIO_REVERBNATION_BORDER_COLOR_DEFAULT),
    );

    $form['reverbnation']['player']['color']['emaudio_reverbnation_background_color'] = array(
        '#type' => 'textfield',
        '#title' => t('Background color'),
        '#default_value' => variable_get('emaudio_reverbnation_background_color', EMAUDIO_REVERBNATION_BACKGROUND_COLOR_DEFAULT),
    );


    $form['reverbnation']['player']['size'] = array(
        '#type' => 'fieldset',
        '#title' => 'Embedded audio player size',
        '#description' => 'If allowed, overrides the default emfield size of the player',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    // check box to over ride player defaults
    $form['reverbnation']['player']['size']['emaudio_reverbnation_player_size'] = array(
        '#type' => 'radios',
        '#title' => 'Player size',
        '#description' => 'Choose a size for the player',
        '#default_value' => variable_get('emaudio_reverbnation_player_size', EMAUDIO_REVERBNATION_PLAYER_SIZE_DEFAULT), //@todo variable get and constant in here
        '#options' => array(
            'emaudio' => 'Emaudio (@todo emfield defaults)',
            'standard' => 'Standard (434 x 326)',
            'blog' => 'Blog (180 x 300)',
            'mini' => 'Mini (262 x 200)',
            'micro' => 'Micro (180 x 150)',
            'custom' => 'Custom (specify below)',
        ),
    );

    $form['reverbnation']['player']['size']['emaudio_reverbnation_player_width_custom'] = array(
        '#type' => 'textfield',
        '#title' => 'Custom width',
        '#size' => '5',
        '#description' => 'todo: description in here',
            //@todo ad width and max -- poss add field set
    );

    $form['reverbnation']['player']['size']['emaudio_reverbnation_player_height_custom'] = array(
        '#type' => 'textfield',
        '#title' => 'Custom height',
        '#size' => 5,
        '#description' => 'todo: description in here',
            //@todo ad width and max -- poss add field set perhaps pull default player size
    );

    return $form;
}

/**
 * Implementation of hook emaudio_PROVIDER_extract().
 *
 * This is called to extract the video code from a pasted URL or embed code.
 *
 * @param $embed
 *   An optional string with the pasted URL or embed code.
 * @return
 *   Either an array of regex expressions to be tested, or a string with the
 *   audio code to be used. If the hook tests the code itself, it should return
 *   either the string of the audio code (if matched), or an empty array.
 *   Otherwise, the calling function will handle testing the embed code against
 *   each regex string in the returned array.
 */
//why does this get called twice??
function emaudio_reverbnation_extract($embed = '') {

//at what point here should I check for safe code???


    $embed_code_regex =
            '@(?:http://cache.reverbnation.com/widgets/swf/40/pro_widget.swf)(?:.*)(?:song_ids=)([\d]+)(?:.*)(?:artist_)([\d]+)@is';
    $song_link_regex = array(
        '@http://www\.reverbnation\.com/play_now/song_([\d]+)@i',
        '@http://www\.reverbnation\.com/.*/artist/song_details/([\d]+)@i',
    );
    $artist_link_regex = '';

//
//test for an actual embed code
    if (preg_match($embed_code_regex, $embed, &$matches)) {
        return implode(':', array('song_id', $matches[1], 'artist_id', $matches[2]));
    }

//test for a song link
    foreach ($song_link_regex as $regex) {
        if (preg_match($regex, $embed, &$matches)) {
            return implode(':', array('song_id', $matches[1]));
        }
    }
}

/**
 * The embedded flash displaying the SoundCloud audio.
 */
function theme_emaudio_reverbnation_flash($item, $embed, $width, $height, $autoplay) { // add options = array()
    $output = '';

    $song_id = $item['data']['song_id'];
    $artist_id = $item['data']['artist_id'];
    $player_type = $item['data']['player_type'];
    $height = $item['data']['height'];
    $width = $item['data']['width'];

//setup autoplay
//setup shuffle

    $bg_color = $item['data']['background_color'];
    $font_color = $item['data']['font_color'];
    $border_color = $item['data']['border_color'];


    $output .= <<<RN
<embed type="application/x-shockwave-flash" src="http://cache.reverbnation.com/widgets/swf/40/pro_widget.swf" height="{$height}" width="{$width}" align="top" bgcolor="#{$bg_color}" loop="false" wmode="opaque" quality="best" allowScriptAccess="always" allowNetworking="all" allowFullScreen="true" seamlesstabbing="false"
flashvars="id=artist_{$artist_id}&posted_by=&skin_id={$player_type}&background_color={$bg_color}&border_color={$border_color}&font_color={$font_color}&auto_play=false&shuffle=false&song_ids={$song_id}" /><br />
RN;

    return $output;
}

//}

/**
 * Implementation of hook_PROVIDER_data().
 */
//this just find out the audio_id from
function emaudio_reverbnation_data($field, $item) {
    $data = array();


    //extract the song id and artist id (2nd and 4th elements)
    //from the imploded matched string in $item['value']
    list(/**/, $song_id, /**/, $artist_id) = explode(':', $item['value']);

    //if we have both artist and songs ids
    if (isset($song_id) && isset($artist_id)) {
        $data['song_id'] = $song_id;
        $data['artist_id'] = $artist_id;
        return $data;
    }

    //if we only have the artist id
    if (isset($song_id) && !isset($artist_id)) {

        $url = $item['embed'];
        $artist_regex = '@/artist/artist_songs/([\d]+)@i';
        $response = drupal_http_request($url);

        //request page from original user link
        if ($response->code == 200) {
            //try and find an artist id on this page
            preg_match($artist_regex, $response->data, &$matches);
            $data['song_id'] = $song_id;
            $data['artist_id'] = $matches[1];
            return $data;
        }
    }

    //still need to account for artist id and no song id
}

/**
 * Implementation of hook emaudio_PROVIDER_thumbnail().
 *
 * Returns the external url for a thumbnail of a specific audio.
 * TODO: make the args: ($embed, $field, $item), with $field/$item provided if we need it, but otherwise simplifying things.
 *
 * @param $field
 *   The field of the requesting node.
 * @param $item
 *   The actual content of the field from the requesting node.
 * @return
 *   A URL pointing to the thumbnail.
 */
function emaudio_soundcloud_thumbnail($field, $item, $formatter, $node, $width, $height) {
    return $tn;
}

/**
 * Implementation of hook emaudio_PROVIDER_audio().
 *
 * This actually displays the full/normal-sized video we want, usually on the default page view.
 *
 * @param $embed
 *   The video code for the audio to embed.
 * @param $width
 *   The width to display the audio.
 * @param $height
 *   The height to display the audio.
 * @param $field
 *   The field info from the requesting node.
 * @param $item
 *   The actual content from the field.
 * @return
 *   The html of the embedded audio.
 */
function emaudio_reverbnation_audio($embed, $width, $height, $field, $item, $node, $autoplay) {
// is set???
    $item['data'] = array_merge($item['data'], get_player_parameters($width, $height));

    return theme('emaudio_reverbnation_flash', $item, $embed, $width, $height, $autoplay);
}

// don't really understand why this is here or where it gets called
// shall skip for the moment

/**
 * Implementation of hook emaudio_odeo_preview().
 *
 * This actually displays the preview-sized video we want, commonly for the teaser.
 *
 * @param $embed
 *   The video code for the audio to embed.
 * @param $width
 *   The width to display the audio.
 * @param $height
 *   The height to display the audio.
 * @param $field
 *   The field info from the requesting node.
 * @param $item
 *   The actual content from the field.
 * @return
 *   The html of the embedded audio.
 */
function emaudio_reverbnation_preview($embed, $width, $height, $field, $item, &$node, $autoplay) {
    return theme('emaudio_reverbnation_flash', $item, $embed, $width, $height, $autoplay);
}

/**
 * Implementation of hook_emfield_subtheme.
 */
function emaudio_reverbnation_emfield_subtheme() {
    return array(
        'emaudio_reverbnation_flash' => array(
            'arguments' => array('item' => NULL, 'embed' => NULL, 'width' => NULL, 'height' => NULL, 'autoplay' => NULL),
            'file' => 'providers/reverbnation.inc'
        )
    );
}

/*
 * @return $options()
 *   User selections at @todo location of the settings for this
 */

function get_player_parameters($width, $height, $options = array()) {

    $options['player_type'] = variable_get('emaudio_reverbnation_player_type', EMAUDIO_REVEBNATION_PLAYER_TYPE_DEFAULT);
    $options['font_color'] = variable_get('emaudio_reverbnation_font_color', '#ffffff');
    $options['background_color'] = variable_get('emaudio_reverbnation_background_color', '#ffffff');
    $options['border_color'] = variable_get('emaudio_reverbnation_border_color', '#ffffff');

    $options['player_size'] = variable_get('emaudio_reverbnation_player_size', EMAUDIO_REVERBNATION_PLAYER_SIZE_DEFAULT);

    // set width and height of player
    switch ($options['player_size']) {
//@todo set constants for these and add an inc file for them

        case 'standard':
            $width = '434';
            $height = '326';
            break;

        case 'blog':
            $width = '180';
            $height = '300';
            break;

        case 'mini':
            $width = '262';
            $height = '200';
            break;

        case 'micro':
            $width = '180';
            $height = '150';
            break;
        case 'custom':
            $width = get_variable('emaudio_reverbnation_player_width_custom', EMAUDIO_REVERBNATION_PLAYER_DEFAULT_WIDTH);
            $height = get_variable('emaudio_reverbnation_player_height_custom', EMAUDIO_REVERBNATION_PLAYER_DEFAULT_HEIGHT);
            break;
        // case 'emaudio':
        // width & height already set
    }

    $options['width'] = $width;
    $options['height'] = $height;


// colors have no setting other than our own -> can just set the variables
// should me them red -> standout
// go back and set proper constants

    return $options;
}

//            'emaudio'=> 'Emaudio field settings',
//            'standard' => 'Standard (434 x 326)',
//            'blog' => 'Blog (180 x 300)',
//            'mini' => 'Mini (262 x 200)',
//            'micro' => 'Micro (180 x 150)',
//            'custom' => 'Custom (specify below)',
//$width = variable_get('');
//if ($player_type = 'custom'
//switch($player_type){
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_REVERB:
//        $width =
//    break;
//
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_SEAMLESS:
////          //
//    break;
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_TINY:
//    //
//    break;
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_STRONG:
//    //
//    break;
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_ELECTRO:
//    //
//    break;
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_SKETCHED:
//    //
//    break;
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_BUTTON:
//    //
//    break;
//    case EMAUDIO_REVEBNATION_PLAYER_TYPE_BUTTON _LIGHT:
//    //
//
//}
//            'emaudio'=> 'Emaudio field settings',
//            'standard' => 'Standard (434 x 326)',
//            'blog' => 'Blog (180 x 300)',
//            'mini' => 'Mini (262 x 200)',
//            'micro' => 'Micro (180 x 150)',
//            'custom' => 'Custom (specify below)',
//    define('EMAUDIO_REVEBNATION_PLAYER_TYPE_REVERB', 'PWAS1003');
//define('EMAUDIO_REVEBNATION_PLAYER_TYPE_SEAMLESS', 'PWAS1008');
//define('EMAUDIO_REVEBNATION_PLAYER_TYPE_TINY', 'PWAS1001');
//define('EMAUDIO_REVEBNATION_PLAYER_TYPE_STRONG', 'PWAS1002');
//define('EMAUDIO_REVEBNATION_PLAYER_TYPE_ELECTRO', 'PWAS1004');
//define('EMAUDIO_REVEBNATION_PLAYER_TYPE_SKETCHED', 'PWAS1005');
//define('EMAUDIO_REVEBNATION_PLAYER_TYPE_BUTTON', 'PWAS1006');
//define('EMAUDIO_REVEBNATION_PLAYER_TYPE_BUTTON _LIGHT', 'PWAS1007');
//$width = isset($options['width']) ? $options['width'] : $width;
// implode to options (we might want to recieve this elsewhere}

