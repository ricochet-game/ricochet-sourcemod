Menu Background Material

It is also necessary to create background materials for your menu background .BSP. This is the image that is shown when you first launch the game, but before the background .BSP has finished loading. In Half-Life 2, this was a blurred screenshot of the background map (when recreating this, use a 30px Gaussian Blur filter for a 1280x image). When the background .BSP is finished loading, the screen fades from the static background material to the actual 3D background map.

The following two materials are needed:


<game directory>\materials\console\<map name>.vmt

<game directory>\materials\console\<map name>_widescreen.vmt

For example, if you made a background map named sdk_background.bsp, you would need these two materials:

hl2\materials\console\sdk_background.vmt

hl2\materials\console\sdk_background_widescreen.vmt

The background materials are usually a 512x512 screenshot of the background map, blurred in an image-editing application.

You can find the key command to take screen shots under Options -> Keyboard when you run the game. The F5 key is the default screenshot key, and saves a .JPG format screen shot to the <game directory>\screenshots directory. You can also bind a key to the screenshot console command, which will save in the .TGA format.

A menu background material .vmt file should look something like this:

"UnlitGeneric"
{
	"$basetexture" "console/sdk_background"
	"$vertexcolor" 1
	"$vertexalpha" 1
	"$ignorez" 1
	"$no_fullbright" "1"
	"$nolod" "1"
}

For information on how to create these materials, see the Creating Materials doc.

Sample materials for the sdk_background sample map are located in:

\sourcesdk_content\hl2\materialsrc\console (for the source .TGAs)

\half-life 2\hl2\materials\console (for the .VMT and .VTF files). 