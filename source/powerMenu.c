#include "clock.h"
#include "homeMenu.h"
#include "powerMenu.h"
#include "main.h"

int powerMenu()
{
	load_PNG(power, "romfs:/powerMenu.png", SF2D_PLACE_RAM);
	load_PNG(power1, "romfs:/powerSelection.png", SF2D_PLACE_RAM);
	/*power = sf2d_create_texture_mem_RGBA8(power_img.pixel_data, power_img.width, power_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	power1 = sf2d_create_texture_mem_RGBA8(power1_img.pixel_data, power1_img.width, power1_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);*/
	
	robotoPowerMenu = sftd_load_font_mem(Roboto_ttf, Roboto_ttf_size); //Loads font

	while (aptMainLoop())
	{
		hidScanInput();

		u32 kDown = hidKeysDown();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		sf2d_draw_texture(background, 0, 0);
		
		sf2d_draw_texture(ic_launcher_browser, 49, 145);
		sf2d_draw_texture(ic_launcher_messenger, 114, 145);
		sf2d_draw_texture(ic_launcher_apollo, 241, 145);
		sf2d_draw_texture(ic_launcher_settings, 306, 145);
		appDrawerIcon();
		
		dayNightWidget();

		sf2d_draw_texture(power, 62, 90);
		
		sftd_draw_textf(robotoPowerMenu, 140, 108, RGBA8(0, 0, 0, 255), 18, "Power Off");
		
		if (touch.px  >= 62 && touch.px  <= 338 && touch.py >= 70 && touch.py <= 149)
		{
			sf2d_draw_texture(power1, 62, 90);
			sftd_draw_textf(robotoPowerMenu, 140, 108, RGBA8(0, 0, 0, 255), 18, "Power Off");
			if (kDown & KEY_TOUCH)
				break;
		}
		
		navbarControls(0); //Displays navbar
		digitalTime(350, 2); 
		batteryStatus(300, 2);
		cursorController();
		
		sf2d_end_frame();
		
		if (kDown & KEY_B)
		{
			sf2d_free_texture(power);
			sf2d_free_texture(power1);
			return 1;
		}
		
		sf2d_swapbuffers();
	}
	
	sftd_free_font(robotoPowerMenu);
	sf2d_free_texture(power);
	sf2d_free_texture(power1);
	
	return 0;
}
